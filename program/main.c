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
    /* calibrate BLDC motor phase if pack1 first byte is 0xa5 */
    if (pid == 1 && data[0] == 0xA5)
        minifoc_fsm_state = 1;
    else if (pid == 1 && data[1] == 0xA5)
        minifoc_fsm_state = 2;
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
    /* zero the encoder for foc algorithm */
    flash_read_parameters();
    while (1) {
        unsigned char buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        switch (minifoc_fsm_state) {
            case 1:foc_calibrate_phase();
                encoder_zeroing();
                flash_write_parameters();
                minifoc_fsm_state = 0;
                break;
            case 2:
                /* configure timer2 for foc calculate loop */
                timer2_config();
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
