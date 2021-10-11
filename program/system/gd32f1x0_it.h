/**************************************************************************//**
  \file     gd32f1x0_it.h
  \brief    gd32f1x0 interrupt handler function header file
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC_SYSTEM_GD32F1X0_IT_H
#define MINIFOC_SYSTEM_GD32F1X0_IT_H

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
void TIMER2_IRQHandler(void);
void TIMER13_IRQHandler(void);

#endif // MINIFOC_SYSTEM_GD32F1X0_IT_H
