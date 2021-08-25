//
// Created by Lao·Zhu on 2021/8/20.
//

#ifndef GD32F1X0_IT_H
#define GD32F1X0_IT_H

#include "gd32f1x0.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART0_IRQHandler(void);

#endif /* GD32F1X0_IT_H */


