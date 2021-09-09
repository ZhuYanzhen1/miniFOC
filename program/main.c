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
    /* pack1 is the control pack of miniFOC*/
    if (pid == 1) {
        switch (data[0]) {
            /* 0x0f is used to correct motor phase sequence and sensor angle offset */
            case 0x0f:minifoc_fsm_state = 1;
                break;
                /* 0x1E used to enable the motor */
            case 0x1e:minifoc_fsm_state = 2;
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
    /* configure systick timer for delay_ms() function */
    systick_config();
    /* read all parameters from flash */
    flash_read_parameters();
    while (1) {
        unsigned char buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        switch (minifoc_fsm_state) {
            case 1:
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
                /* configure timer2 for foc calculate loop */
                timer2_config();
                /* switch the status back to sending data */
                minifoc_fsm_state = 0;
                break;
            case 0:
            default:buffer[0] = float_to_int16(velocity_filter.current_result) >> 8;
                buffer[1] = float_to_int16(velocity_filter.current_result) & 0x00ff;
                if (velocity_filter.current_result == 0)
                    velocity_filter.current_result = 3.1415926f;
                mdtp_data_transmit(0x00, buffer);
                led_toggle();
                delayms(50);
                break;
        }
    }
}
