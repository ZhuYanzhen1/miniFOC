/**************************************************************************//**
  \file     main.c
  \brief    miniFOC main source file, The relevant operations and main function
            after unpacking of medium capacity transmission protocol are implemented
            in this document.
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "main.h"

/*!
    \brief used to indicate the current status of miniFOC
    \param
      1 calibrate motor phase and sensor offset  \n
      2 enable the motor                         \n
      3 disable the motor                        \n
      4 return current parameters
*/
static volatile unsigned char minifoc_fsm_state = 0;

/*!
    \brief     user callback function for unpacking completion of medium capacity transport protocol
    \param[in] pid: medium capacity transport protocol package id
    \param[in] data: received data array of size 8 bytes
*/
void mdtp_callback_handler(unsigned char pid, const unsigned char *data) {
    /* pack0 is the control pack of miniFOC */
    if (pid == 0) {
        unsigned int receive_int32;
        switch (data[0]) {
            case 0x0F:
                /* 0x0F is used to calibrate motor phase and sensor offset */
                minifoc_fsm_state = 1;
                break;

            case 0x1E:
                if (foc_parameter_available_flag == 1) {
                    /* 0x1E used to enable the motor */
                    minifoc_fsm_state = 2;

                    /* configure pid parameters for (torque/speed/angle) loop */
                    if (pid_parameter_available_flag == 1)
                        pid_config(data[1]);
                    else
                        pid_config(TORQUE_LOOP_CONTROL);
                }
                break;

            case 0x2D:
                /* 0x2D used to disable the motor */
                minifoc_fsm_state = 3;
                break;

            case 0x3C:
                /* 0x3C used to set user expect */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                if (pid_parameter_available_flag == 1) {
                    switch (pid_control_mode_flag) {
                        default:
                        case TORQUE_LOOP_CONTROL:FOC_Struct.user_expect = int32_to_float(receive_int32);
                            break;
                        case SPEED_LOOP_CONTROL:speed_pid_handler.expect = int32_to_float(receive_int32);
                            break;
                        case ANGLE_LOOP_CONTROL:angle_pid_handler.expect = int32_to_float(receive_int32);
                            break;
                    }
                } else
                    FOC_Struct.user_expect = int32_to_float(receive_int32);
                break;

            case 0x4B:
                /* 0x4D used to set speed pid kp */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                speed_pid_handler.kp = int32_to_float(receive_int32);
                break;

            case 0x5A:
                /* 0x5A used to set speed pid ki */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                speed_pid_handler.ki = int32_to_float(receive_int32);
                break;

            case 0x69:
                /* 0x69 used to set speed pid kd */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                speed_pid_handler.kd = int32_to_float(receive_int32);
                break;

            case 0x78:
                /* 0x78 used to set speed pid summary maximum */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                speed_pid_handler.sum_maximum = int32_to_float(receive_int32);
                break;

            case 0x87:
                /* 0x87 used to set angle pid kp */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                angle_pid_handler.kp = int32_to_float(receive_int32);
                break;

            case 0x96:
                /* 0x96 used to set angle pid ki */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                angle_pid_handler.ki = int32_to_float(receive_int32);
                break;

            case 0xA5:
                /* 0xA5 used to set angle pid kd */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                angle_pid_handler.kd = int32_to_float(receive_int32);
                break;

            case 0xB4:
                /* 0xB4 used to set angle pid summary maximum */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                angle_pid_handler.sum_maximum = int32_to_float(receive_int32);
                break;

            case 0xC3:
                /* 0xC3 used to return current value */
                minifoc_fsm_state = 4;
                break;

            case 0xD2:
                /* 0xD2 used to write byte to flash */
                minifoc_fsm_state = 5;
                pid_parameter_available_flag = 1;
                break;
            default:break;
        }
    }
}

/*!
    \brief main function
*/
int main(void) {
    /* 4 bits for preemption priority 0 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

    /* configure peripherals */
    led_config();
    uart_config();
    pwm_config();
    spi_config();

    /* configure filter and pid parameters for pid algorithm */
    filter_config();
    pid_config(TORQUE_LOOP_CONTROL);

    /* configure systick timer for delay_ms() function */
    systick_config();

    /* read all parameters from flash */
    flash_read_parameters();

    /* correct the mechanical angle zero deviation */
    encoder_zeroing();

    while (1) {
        switch (minifoc_fsm_state) {
            case 1:
                /* disable timer to stop foc calculate loop */
                timer2_disable();
                timer13_disable();

                /* automatic phase sequence detection and correction */
                foc_calibrate_phase();

                /* correct the mechanical angle zero deviation */
                encoder_zeroing();

                /* re-write the parameters to flash */
                flash_write_parameters();
                minifoc_fsm_state = 0;
                break;

            case 2:
                /* delay to wait for the motor to respond */
                delayms(1000);

                /* configure timer for foc calculate loop */
                timer2_config();
                if (pid_control_mode_flag != TORQUE_LOOP_CONTROL)
                    timer13_config();
                minifoc_fsm_state = 0;
                break;

            case 3:
                /* disable timer to stop foc calculate loop */
                timer2_disable();
                if (pid_control_mode_flag != TORQUE_LOOP_CONTROL)
                    timer13_disable();
                minifoc_fsm_state = 0;
                break;

            case 4:
                /* transmit current value to monitor */
                report_local_variable();
                minifoc_fsm_state = 0;
                break;

            case 5:
                /* disable timer to stop foc calculate loop */
                timer2_disable();
                timer13_disable();

                /* write data to flash */
                flash_write_parameters();
                minifoc_fsm_state = 0;
                break;

            case 0:
            default:
                /* transmit angle and speed to monitor */
                report_angle_speed();
                led_toggle();
                delayms(50);
                break;
        }
    }
}
