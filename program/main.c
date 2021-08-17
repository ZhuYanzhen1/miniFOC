#include "gd32f1x0.h"
#include "system.h"
#include "main.h"

int main(void) {
    systick_config();
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    while (1) {
        delayms(500);
        gpio_bit_set(GPIOA, GPIO_PIN_10);
        delayms(500);
        gpio_bit_reset(GPIOA, GPIO_PIN_10);
    }
}
