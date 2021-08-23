#include "main.h"

int main(void) {
    systick_config();
    led_config();
    while (1) {
        led_toggle();
        delayms(500);
    }
}
