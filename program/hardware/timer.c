/**************************************************************************//**
  \file     timer.c
  \brief    this file contains the code implementation of timer initialization
            and disable timer function and setting timer comparison value.
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "timer.h"
#include "gd32f1x0.h"
#include "config.h"

/*!
    \brief     update timer1 ch0 1 2 duty-cycle
    \param[in] ch0: duty-cycle of channel0, 0 ~ 1.0f
    \param[in] ch1: duty-cycle of channel1, 0 ~ 1.0f
    \param[in] ch2: duty-cycle of channel2, 0 ~ 1.0f
*/
void update_pwm_dutycycle(float ch0, float ch1, float ch2) {
    /* update the comparison register of timer1 */
    TIMER_CH0CV(TIMER1) = (uint32_t) ((float) PWM_PERIOD * ch0);
    TIMER_CH1CV(TIMER1) = (uint32_t) ((float) PWM_PERIOD * ch1);
    TIMER_CH2CV(TIMER1) = (uint32_t) ((float) PWM_PERIOD * ch2);
}

/*!
    \brief disable timer13 periph and timer2 interrupt
*/
void timer13_disable(void) {
    /* stop TIMER13 and deinit */
    timer_disable(TIMER13);
    timer_deinit(TIMER13);

    /* disable TIMER13 update interrupt and clock*/
    timer_interrupt_disable(TIMER13, TIMER_INT_UP);
    nvic_irq_disable(TIMER13_IRQn);
    rcu_periph_clock_disable(RCU_TIMER13);
}

/*!
    \brief disable timer2 periph and timer2 interrupt
*/
void timer2_disable(void) {
    /* stop TIMER2 and deinit */
    timer_disable(TIMER2);
    timer_deinit(TIMER2);

    /* disable TIMER2 update interrupt and clock */
    timer_interrupt_disable(TIMER2, TIMER_INT_UP);
    nvic_irq_disable(TIMER2_IRQn);
    rcu_periph_clock_disable(RCU_TIMER2);

    /* zero the torque in all directions to release the motor */
    update_pwm_dutycycle(0.5f, 0.5f, 0.5f);
}

/*!
    \brief configure timer2 periph for timing interrupt
*/
void timer2_config(void) {
    timer_parameter_struct timer_initpara;

    /* enable TIMER2 clock*/
    rcu_periph_clock_enable(RCU_TIMER2);
    timer_deinit(TIMER2);

    /* TIMER1CLK = SystemCoreClock / 72 = 1MHz */
    timer_initpara.prescaler = 71;

    /* timer edge alignment up count mode */
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;

    /* Period = 1000 / TIM2_FREQUENCY (kHz) */
    timer_initpara.period = (1000 / TIM2_FREQUENCY) - 1;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER2, &timer_initpara);

    /* enable TIMER2 update interrupt */
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    timer_enable(TIMER2);
    nvic_irq_enable(TIMER2_IRQn, TIM2_PRIORITY, 0);
}

/*!
    \brief configure timer13 periph for timing interrupt
*/
void timer13_config(void) {
    timer_parameter_struct timer_initpara;

    /* enable TIMER13 clock*/
    rcu_periph_clock_enable(RCU_TIMER13);
    timer_deinit(TIMER13);

    /* TIMER1CLK = SystemCoreClock / 72 = 1MHz */
    timer_initpara.prescaler = 71;

    /* timer edge alignment up count mode */
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;

    /* Period = 1000000 / TIM13_FREQUENCY (kHz) */
    timer_initpara.period = (1000000 / TIM13_FREQUENCY) - 1;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER13, &timer_initpara);

    /* enable TIMER13 update interrupt */
    timer_interrupt_enable(TIMER13, TIMER_INT_UP);
    timer_enable(TIMER13);
    nvic_irq_enable(TIMER13_IRQn, TIM13_PRIORITY, 0);
}

/*!
    \brief configure timer1 periph and its gpios
*/
void pwm_config(void) {
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    /* enable GPIO clock and TIMER1 clock*/
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_TIMER1);
    timer_deinit(TIMER1);

    /* configure TIMER1_CH0 as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    /* configure TIMER1_CH1 as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);

    /* configure TIMER1_CH2 as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    /* connect port to TIMER1_CH0 1 2 */
    gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_0);
    gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_1);
    gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_2);

    /* TIMER1CLK = SystemCoreClock / 2 = 18MHz */
    timer_initpara.prescaler = 1;

    /* timer center alignment up count mode */
    timer_initpara.alignedmode = TIMER_COUNTER_CENTER_UP;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;

    /* Period = 36000 / PWM_FREQUENCY */
    timer_initpara.period = PWM_PERIOD;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);

    /* CH1, CH2 and CH3 configuration in PWM0 mode */
    timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocintpara);
    timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);
    timer_channel_output_config(TIMER1, TIMER_CH_2, &timer_ocintpara);

    /* CH0 configuration in PWM mode1,duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, PWM_PERIOD / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    /* CH1 configuration in PWM mode1,duty cycle 25% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, PWM_PERIOD / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    /* CH2 configuration in PWM mode1,duty cycle 12.5% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, PWM_PERIOD / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload and timer enable */
    timer_auto_reload_shadow_enable(TIMER1);
    timer_enable(TIMER1);
}
