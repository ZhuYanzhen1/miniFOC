#include "main.h"

int main(void) {
    systick_config();
    led_config();
    while (1) {
        delayms(500);
        led_on();
        delayms(500);
        led_off();
    }
}
