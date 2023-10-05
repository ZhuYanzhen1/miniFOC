#include "ch32v20x_it.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void NMI_Handler(void) {
    while (1);
}

void HardFault_Handler(void) {
    while (1);
}

void TIM1_UP_IRQHandler(void) {
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}
