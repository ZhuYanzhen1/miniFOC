//
// Created by Lao·Zhu on 2021/8/20.
//

#include "main.h"

static volatile unsigned char minifoc_fsm_state = 0;

/*!
    \brief        user callback function for unpacking completion of medium capacity transport protocol
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \param[out]   none
    \retval       none
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
                /* 0x1E used to enable the motor */
                minifoc_fsm_state = 2;
                /* configure pid parameters for (torque/speed/angle) loop */
                pid_config(data[1]);
                break;
            case 0x2D:
                /* 0x2D used to disable the motor */
                minifoc_fsm_state = 3;
                break;
            case 0x3C:
                /* 0x3C used to set user expect */
                receive_int32 = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
                switch (pid_control_mode_flag) {
                    default:
                    case TORQUE_LOOP_CONTROL:FOC_Struct.user_expect = int32_to_float(receive_int32);
                        break;
                    case SPEED_LOOP_CONTROL:speed_pid_handler.expect = int32_to_float(receive_int32);
                        break;
                    case ANGLE_LOOP_CONTROL:angle_pid_handler.expect = int32_to_float(receive_int32);
                        break;
                }
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
            default:break;
        }
    }
}

int main(void) {
    /* 4 bits for preemption priority 0 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    /* configure led gpio */
    led_config();
    /* configure uart for data transmit */
    uart_config();
    /* configure timer1 for pwm output */
    pwm_config();
    /* configure spi0 for encoder communicate */
    spi_config();
    /* configure filter parameters for pid algorithm */
    filter_config();
    /* configure pid parameters for (torque/speed/angle) loop */
    pid_config(DEFAULT_MODE);
    /* configure systick timer for delay_ms() function */
    systick_config();
    /* read all parameters from flash */
    flash_read_parameters();
    while (1) {
        switch (minifoc_fsm_state) {
            case 1:
                /* disable timer2 to stop foc calculate loop */
                timer2_disable();
                /* disable timer13 to stop pid calculate loop */
                timer13_disable();
                /* automatic phase sequence detection and correction */
                foc_calibrate_phase();
                /* correct the mechanical angle zero deviation */
                encoder_zeroing();
                /* re-write the parameters to flash */
                flash_write_parameters();
                /* switch the status back to sending data */
                minifoc_fsm_state = 0;
                break;
            case 2:
                /* delay to wait for the motor to respond */
                delayms(1000);
                /* configure timer2 for foc calculate loop */
                timer2_config();
                if (pid_control_mode_flag != TORQUE_LOOP_CONTROL)
                    /* configure timer13 for velocity or angle closed loop */
                    timer13_config();
                /* switch the status back to sending data */
                minifoc_fsm_state = 0;
                break;
            case 3:
                /* disable timer2 to stop foc calculate loop */
                timer2_disable();
                /* disable timer13 to stop pid calculate loop */
                if (pid_control_mode_flag != TORQUE_LOOP_CONTROL)
                    timer13_disable();
                /* switch the status back to sending data */
                minifoc_fsm_state = 0;
                break;
            case 0:
            default: {
                unsigned char buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                /* converts velocity floating point data to an integer */
                unsigned int velocity = float_to_int32(FOC_Struct.rotate_speed);
                /* converts angle floating point data to an integer */
                unsigned int angle = float_to_int32(FOC_Struct.mechanical_angle);
                /* separates 32-bit velocity integer into 8-bit integers */
                buffer[0] = (unsigned char) ((velocity >> 24UL) & 0x000000ffUL);
                buffer[1] = (unsigned char) ((velocity >> 16UL) & 0x000000ffUL);
                buffer[2] = (unsigned char) ((velocity >> 8UL) & 0x000000ffUL);
                buffer[3] = (unsigned char) (velocity & 0x000000ffUL);
                /* separates 32-bit angle integer into 8-bit integers */
                buffer[4] = (unsigned char) ((angle >> 24UL) & 0x000000ffUL);
                buffer[5] = (unsigned char) ((angle >> 16UL) & 0x000000ffUL);
                buffer[6] = (unsigned char) ((angle >> 8UL) & 0x000000ffUL);
                buffer[7] = (unsigned char) (angle & 0x000000ffUL);
                /* packet and send through medium capacity data transmission protocol */
                mdtp_data_transmit(0x00, buffer);
                led_toggle();
                delayms(50);
            }
                break;
        }
    }
}
