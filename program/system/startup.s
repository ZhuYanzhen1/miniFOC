;/********************************** (C) COPYRIGHT *******************************
;* File Name          : startup_ch32v20x_D6.s
;* Author             : WCH
;* Version            : V1.0.0
;* Date               : 2021/06/06
;* Description        :  CH32V203F6-CH32V203F8-CH32V203G6-CH32V203G8-CH32V203K6-CH32V203K8-CH32V203C6-CH32V203C8
;*                    vector table for eclipse toolchain.
;*********************************************************************************
;* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
;* Attention: This software (modified or not) and binary are used for 
;* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

	.section	.init,"ax",@progbits
	.global	_start
	.align	1
_start:
	j	handle_reset
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00100073
    .section    .vector,"ax",@progbits
    .align  1
_vector_base:
    .option norvc;
    .word   _start
    .word   0
    .word   NMI_Handler                /* NMI */
    .word   HardFault_Handler          /* Hard Fault */
    .word   0
    .word   Ecall_M_Mode_Handler       /* Ecall M Mode */
    .word   0
    .word   0
    .word   Ecall_U_Mode_Handler       /* Ecall U Mode */
    .word   Break_Point_Handler        /* Break Point */
    .word   0
    .word   0
    .word   SysTick_Handler            /* SysTick */
    .word   0
    .word   SW_Handler                 /* SW */
    .word   0
    /* External Interrupts */
    .word   WWDG_IRQHandler            /* Window Watchdog */
    .word   PVD_IRQHandler             /* PVD through EXTI Line detect */
    .word   TAMPER_IRQHandler          /* TAMPER */
    .word   RTC_IRQHandler             /* RTC */
    .word   FLASH_IRQHandler           /* Flash */
    .word   RCC_IRQHandler             /* RCC */
    .word   EXTI0_IRQHandler           /* EXTI Line 0 */
    .word   EXTI1_IRQHandler           /* EXTI Line 1 */
    .word   EXTI2_IRQHandler           /* EXTI Line 2 */
    .word   EXTI3_IRQHandler           /* EXTI Line 3 */
    .word   EXTI4_IRQHandler           /* EXTI Line 4 */
    .word   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
    .word   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
    .word   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
    .word   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
    .word   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
    .word   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
    .word   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
    .word   ADC1_2_IRQHandler          /* ADC1_2 */
    .word   USB_HP_CAN1_TX_IRQHandler  /* USB HP and CAN1 TX */
    .word   USB_LP_CAN1_RX0_IRQHandler /* USB LP and CAN1RX0 */
    .word   CAN1_RX1_IRQHandler        /* CAN1 RX1 */
    .word   CAN1_SCE_IRQHandler        /* CAN1 SCE */
    .word   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
    .word   TIM1_BRK_IRQHandler        /* TIM1 Break */
    .word   TIM1_UP_IRQHandler         /* TIM1 Update */
    .word   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
    .word   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
    .word   TIM2_IRQHandler            /* TIM2 */
    .word   TIM3_IRQHandler            /* TIM3 */
    .word   TIM4_IRQHandler            /* TIM4 */
    .word   I2C1_EV_IRQHandler         /* I2C1 Event */
    .word   I2C1_ER_IRQHandler         /* I2C1 Error */
    .word   I2C2_EV_IRQHandler         /* I2C2 Event */
    .word   I2C2_ER_IRQHandler         /* I2C2 Error */
    .word   SPI1_IRQHandler            /* SPI1 */
    .word   SPI2_IRQHandler            /* SPI2 */
    .word   USART1_IRQHandler          /* USART1 */
    .word   USART2_IRQHandler          /* USART2 */
    .word   USART3_IRQHandler          /* USART3 */
    .word   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
    .word   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
    .word   USBWakeUp_IRQHandler       /* USB Wake up from suspend */
    .word   USBHD_IRQHandler           /* USBHD Break */
    .word   USBHDWakeUp_IRQHandler     /* USBHD Wake up from suspend */
    .word   UART4_IRQHandler           /* UART4 */
    .word   DMA1_Channel8_IRQHandler   /* DMA1 Channel8 */

    .option rvc;

    .section    .text.vector_handler, "ax", @progbits
    .weak   NMI_Handler                /* NMI */
    .weak   HardFault_Handler          /* Hard Fault */
    .weak   Ecall_M_Mode_Handler       /* Ecall M Mode */
    .weak   Ecall_U_Mode_Handler       /* Ecall U Mode */
    .weak   Break_Point_Handler        /* Break Point */
    .weak   SysTick_Handler            /* SysTick */
    .weak   SW_Handler                 /* SW */
    .weak   WWDG_IRQHandler            /* Window Watchdog */
    .weak   PVD_IRQHandler             /* PVD through EXTI Line detect */
    .weak   TAMPER_IRQHandler          /* TAMPER */
    .weak   RTC_IRQHandler             /* RTC */
    .weak   FLASH_IRQHandler           /* Flash */
    .weak   RCC_IRQHandler             /* RCC */
    .weak   EXTI0_IRQHandler           /* EXTI Line 0 */
    .weak   EXTI1_IRQHandler           /* EXTI Line 1 */
    .weak   EXTI2_IRQHandler           /* EXTI Line 2 */
    .weak   EXTI3_IRQHandler           /* EXTI Line 3 */
    .weak   EXTI4_IRQHandler           /* EXTI Line 4 */
    .weak   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
    .weak   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
    .weak   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
    .weak   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
    .weak   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
    .weak   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
    .weak   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
    .weak   ADC1_2_IRQHandler          /* ADC1_2 */
    .weak   USB_HP_CAN1_TX_IRQHandler  /* USB HP and CAN1 TX */
    .weak   USB_LP_CAN1_RX0_IRQHandler /* USB LP and CAN1RX0 */
    .weak   CAN1_RX1_IRQHandler        /* CAN1 RX1 */
    .weak   CAN1_SCE_IRQHandler        /* CAN1 SCE */
    .weak   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
    .weak   TIM1_BRK_IRQHandler        /* TIM1 Break */
    .weak   TIM1_UP_IRQHandler         /* TIM1 Update */
    .weak   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
    .weak   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
    .weak   TIM2_IRQHandler            /* TIM2 */
    .weak   TIM3_IRQHandler            /* TIM3 */
    .weak   TIM4_IRQHandler            /* TIM4 */
    .weak   I2C1_EV_IRQHandler         /* I2C1 Event */
    .weak   I2C1_ER_IRQHandler         /* I2C1 Error */
    .weak   I2C2_EV_IRQHandler         /* I2C2 Event */
    .weak   I2C2_ER_IRQHandler         /* I2C2 Error */
    .weak   SPI1_IRQHandler            /* SPI1 */
    .weak   SPI2_IRQHandler            /* SPI2 */
    .weak   USART1_IRQHandler          /* USART1 */
    .weak   USART2_IRQHandler          /* USART2 */
    .weak   USART3_IRQHandler          /* USART3 */
    .weak   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
    .weak   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
    .weak   USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
    .weak   USBHD_IRQHandler           /* USBHD */
    .weak   USBHDWakeUp_IRQHandler     /* USBHD Wake Up */
    .weak   UART4_IRQHandler           /* UART4 */
    .weak   DMA1_Channel8_IRQHandler   /* DMA1 Channel8 */

NMI_Handler:  1:  j 1b
HardFault_Handler:  1:  j 1b
Ecall_M_Mode_Handler:  1:  j 1b
Ecall_U_Mode_Handler:  1:  j 1b
Break_Point_Handler:  1:  j 1b
SysTick_Handler:  1:  j 1b
SW_Handler:  1:  j 1b
WWDG_IRQHandler:  1:  j 1b
PVD_IRQHandler:  1:  j 1b
TAMPER_IRQHandler:  1:  j 1b
RTC_IRQHandler:  1:  j 1b
FLASH_IRQHandler:  1:  j 1b
RCC_IRQHandler:  1:  j 1b
EXTI0_IRQHandler:  1:  j 1b
EXTI1_IRQHandler:  1:  j 1b
EXTI2_IRQHandler:  1:  j 1b
EXTI3_IRQHandler:  1:  j 1b
EXTI4_IRQHandler:  1:  j 1b
DMA1_Channel1_IRQHandler:  1:  j 1b
DMA1_Channel2_IRQHandler:  1:  j 1b
DMA1_Channel3_IRQHandler:  1:  j 1b
DMA1_Channel4_IRQHandler:  1:  j 1b
DMA1_Channel5_IRQHandler:  1:  j 1b
DMA1_Channel6_IRQHandler:  1:  j 1b
DMA1_Channel7_IRQHandler:  1:  j 1b
ADC1_2_IRQHandler:  1:  j 1b
USB_HP_CAN1_TX_IRQHandler:  1:  j 1b
USB_LP_CAN1_RX0_IRQHandler:  1:  j 1b
CAN1_RX1_IRQHandler:  1:  j 1b
CAN1_SCE_IRQHandler:  1:  j 1b
EXTI9_5_IRQHandler:  1:  j 1b
TIM1_BRK_IRQHandler:  1:  j 1b
TIM1_UP_IRQHandler:  1:  j 1b
TIM1_TRG_COM_IRQHandler:  1:  j 1b
TIM1_CC_IRQHandler:  1:  j 1b
TIM2_IRQHandler:  1:  j 1b
TIM3_IRQHandler:  1:  j 1b
TIM4_IRQHandler:  1:  j 1b
I2C1_EV_IRQHandler:  1:  j 1b
I2C1_ER_IRQHandler:  1:  j 1b
I2C2_EV_IRQHandler:  1:  j 1b
I2C2_ER_IRQHandler:  1:  j 1b
SPI1_IRQHandler:  1:  j 1b
SPI2_IRQHandler:  1:  j 1b
USART1_IRQHandler:  1:  j 1b
USART2_IRQHandler:  1:  j 1b
USART3_IRQHandler:  1:  j 1b
EXTI15_10_IRQHandler:  1:  j 1b
RTCAlarm_IRQHandler:  1:  j 1b
USBWakeUp_IRQHandler:  1:  j 1b
USBHD_IRQHandler:  1:  j 1b
USBHDWakeUp_IRQHandler:  1:  j 1b
UART4_IRQHandler:  1:  j 1b
DMA1_Channel8_IRQHandler:  1:  j 1b

	.section	.text.handle_reset,"ax",@progbits
	.weak	handle_reset
	.align	1
handle_reset:
.option push 
.option	norelax 
	la gp, __global_pointer$
.option	pop 
1:
	la sp, _eusrstack 
2:
	/* Load data section from flash to RAM */
	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
	/* Clear bss section */
	la a0, _sbss
	la a1, _ebss
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:
    li t0, 0x1f
    csrw 0xbc0, t0

    /* Enable nested and hardware stack */
	li t0, 0x3
	csrw 0x804, t0

    /* Enable interrupt */
   	li t0, 0x88           
   	csrs mstatus, t0

 	la t0, _vector_base
    ori t0, t0, 3           
	csrw mtvec, t0

    jal  SystemInit
	la t0, main
	csrw mepc, t0
	mret


