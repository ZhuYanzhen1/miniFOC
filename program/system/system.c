#include "gd32f1x0.h"
#include "system.h"

volatile static uint32_t delay;

void systick_config(void) {
    if (SysTick_Config(SystemCoreClock / 1000U))
        while (1);
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

void delayms(uint32_t count) {
    delay = count;
    while (0U != delay);
}

void delay_decrement(void) {
    if (0U != delay)
        delay--;
}
