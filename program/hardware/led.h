//
// Created by Lao·Zhu on 2021/8/23.
//

#ifndef MINIFOC_HARDWARE_LED_H_
#define MINIFOC_HARDWARE_LED_H_

#define led_config()    rcu_periph_clock_enable(RCU_GPIOB);\
                        gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_5);\
                        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5)

#define led_on()        gpio_bit_reset(GPIOB, GPIO_PIN_5)
#define led_off()       gpio_bit_set(GPIOB, GPIO_PIN_5)

#endif //MINIFOC_HARDWARE_LED_H_
