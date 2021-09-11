//
// Created by Lao·Zhu on 2021/8/20.
//

#include "gd32f1x0_it.h"
#include "main.h"

static unsigned char systick_counter = 0;

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void) {
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void) {
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void) {
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void) {
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void) {
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void) {
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void) {
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void) {
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void) {
    /* update millisecond delay counter */
    delay_decrement();
    systick_counter++;
    /* reduce the frequency to 500Hz */
    if (systick_counter == 2) {
        systick_counter = 0;
        /* update the current rotor speed */
        encoder_update_speed();
    }
}

/*!
    \brief      this function handles USART RBNE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void) {
    /* judge whether a reception interrupt is generated */
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) {
        /* receive data */
        unsigned char rcv_data = usart_data_receive(USART0);
        /* process and unzip data */
        mdtp_receive_handler(rcv_data);
    }
}

/*!
    \brief      this function handles TIMER2 TIMER_INT_UP interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER2_IRQHandler(void) {
    /* judge whether a timer update interrupt is generated */
    if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_UP)) {
        /* clear timer interrupt flag bit */
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);
        /* obtain the electric angle at the current time */
        float u, v, w, angle = (float) encoder_get_electronic_angle();
        /* Clarke inverse transform and SVPWM modulation */
        /* judge whether the motor phase is connected reversely */
        if (phase_sequence == 0)
            foc_calculate_dutycycle(angle, 0, FOC_Struct.user_expect, &u, &v, &w);
        else
            foc_calculate_dutycycle(angle, 0, FOC_Struct.user_expect, &v, &u, &w);
        /* Apply to PWM */
        update_pwm_dutycycle(u, v, w);
    }
}

/*!
    \brief      this function handles TIMER13 TIMER_INT_UP interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER13_IRQHandler(void) {
    /* judge whether a timer update interrupt is generated */
    if (SET == timer_interrupt_flag_get(TIMER13, TIMER_INT_UP)) {
        /* clear timer interrupt flag bit */
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
