/**************************************************************************//**
  \file     gd32f1x0_it.c
  \brief    gd32f1x0 interrupt handler function source file
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "gd32f1x0_it.h"
#include "main.h"

/*!
    \brief  systick interrupt count variable is used to
            realize the encoder update function.
*/
static unsigned char systick_counter = 0;

/*!
    \brief this function handles NMI exception
*/
void NMI_Handler(void) {
}

/*!
    \brief this function handles HardFault exception
*/
void HardFault_Handler(void) {
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief this function handles MemManage exception
*/
void MemManage_Handler(void) {
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief this function handles BusFault exception
*/
void BusFault_Handler(void) {
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief this function handles UsageFault exception
*/
void UsageFault_Handler(void) {
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief this function handles SVC exception
*/
void SVC_Handler(void) {
}

/*!
    \brief this function handles DebugMon exception
*/
void DebugMon_Handler(void) {
}

/*!
    \brief this function handles PendSV exception
*/
void PendSV_Handler(void) {
}

/*!
    \brief this function handles SysTick exception
*/
void SysTick_Handler(void) {
    /* update millisecond delay counter */
    delay_decrement();
    systick_counter++;

    /* reduce the frequency to SPEED_UP_FREQ, update the current rotor speed */
    if (systick_counter == (1000 / SPEED_UP_FREQ)) {
        systick_counter = 0;
        encoder_update_speed();
    }
}

/*!
    \brief this function handles USART RBNE interrupt request
*/
void USART0_IRQHandler(void) {
    /* judge whether a reception interrupt is generated */
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
        /* receive, process and unzip data */
        unsigned char rcv_data = usart_data_receive(USART0);
        mdtp_receive_handler(rcv_data);
    }
}

/*!
    \brief this function handles TIMER2 TIMER_INT_UP interrupt request
*/
void TIMER2_IRQHandler(void) {
    /* judge whether a timer update interrupt is generated, clear timer interrupt flag bit */
    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_UP)) {
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);

        /* obtain the electric angle at the current time */
        float u, v, w, angle = (float) encoder_get_electronic_angle();

        /* Clarke inverse transform and SVPWM modulation */
        if (phase_sequence == 0)
            foc_calculate_dutycycle(angle, 0, FOC_Struct.user_expect, &u, &v, &w);
        else
            foc_calculate_dutycycle(angle, 0, FOC_Struct.user_expect, &v, &u, &w);
        update_pwm_dutycycle(u, v, w);
    }
}

/*!
    \brief this function handles TIMER13 TIMER_INT_UP interrupt request
*/
void TIMER13_IRQHandler(void) {
    /* judge whether a timer update interrupt is generated, clear timer interrupt flag bit */
    if (SET == timer_interrupt_flag_get(TIMER13, TIMER_INT_UP)) {
        timer_interrupt_flag_clear(TIMER13, TIMER_INT_UP);

        /* judge whether angle closed-loop control is required */
        if (pid_control_mode_flag == ANGLE_LOOP_CONTROL)
            /* the calculated value of the angle loop is taken as the expected value of the speed loop */
            speed_pid_handler.expect =
                pid_calculate_result((PID_Structure_t *) &angle_pid_handler, FOC_Struct.mechanical_angle);

        /* calculate the speed loop PID and obtain the calculated value */
        FOC_Struct.user_expect = pid_calculate_result((PID_Structure_t *) &speed_pid_handler, FOC_Struct.rotate_speed);
    }
}
