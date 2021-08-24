//
// Created by Lao·Zhu on 2021/8/20.
//

#include "main.h"

int main(void) {
    /* configure systick timer for delay_ms() function */
    systick_config();
    /* configure led gpio */
    led_config();
    /* configure uart for data transmit */
    uart_config();
    /* send test data from uart */
    uart_sendbyte(0xFF);
    while (1) {
        led_toggle();
        delayms(500);
    }
}
