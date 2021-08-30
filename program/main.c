//
// Created by Lao·Zhu on 2021/8/20.
//

#include "main.h"

void mdtp_callback_handler(unsigned char pid, unsigned char *data) {
    /* send package back directly for testing */
    mdtp_data_transmit(pid, data);
}

int main(void) {
    float u, v, w;
    /* 4 bits for preemption priority 0 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    /* configure systick timer for delay_ms() function */
    systick_config();
    /* configure led gpio */
    led_config();
    /* configure uart for data transmit */
    uart_config();
    /* configure timer1 for pwm output */
    pwm_config();
    /* send test data from uart */
    uart_sendbyte(0xFF);
    foc_calculate_dutycycle(0.314f, 0, 1.0f, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
    while (1) {
        led_toggle();
        delayms(500);
    }
}
