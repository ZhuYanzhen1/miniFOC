#include "gd32f1x0_it.h"
#include "systick.h"

void NMI_Handler(void) {}

void HardFault_Handler(void) { while (1); }

void MemManage_Handler(void) { while (1); }

void BusFault_Handler(void) { while (1); }

void UsageFault_Handler(void) { while (1); }

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

void SysTick_Handler(void) {
    delay_decrement();
}
