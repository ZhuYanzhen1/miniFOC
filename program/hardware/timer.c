//
// Created by Lao·Zhu on 2021/8/29.
//

#include "timer.h"
#include "gd32f1x0.h"
#include "config.h"

unsigned int pwm_period = 0;

/*!
    \brief      update timer1 ch0 1 2 duty-cycle
    \param[in]  ch0: duty-cycle of channel0, 0 ~ 1.0f
    \param[in]  ch1: duty-cycle of channel1, 0 ~ 1.0f
    \param[in]  ch2: duty-cycle of channel2, 0 ~ 1.0f
    \param[out] none
    \retval     none
*/
void update_pwm_dutycycle(float ch0, float ch1, float ch2) {
    /* update the comparison register of timer1 */
    TIMER_CH0CV(TIMER1) = (uint32_t) ((float) pwm_period * ch0);
    TIMER_CH1CV(TIMER1) = (uint32_t) ((float) pwm_period * ch1);
    TIMER_CH2CV(TIMER1) = (uint32_t) ((float) pwm_period * ch2);
}

/*!
    \brief      configure timer1 periph and its gpios
    \param[in]  none
    \param[out] none
    \retval     none
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

    /* TIMER1CLK = SystemCoreClock / 72 = 1MHz */
    timer_initpara.prescaler = 71;
    /* timer center alignment up count mode */
    timer_initpara.alignedmode = TIMER_COUNTER_CENTER_UP;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    /* Period = 36000 / PWM_FREQUENCY */
    pwm_period = 36000 / PWM_FREQUENCY;
    timer_initpara.period = pwm_period;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    /* initialize the relevant registers of timer1 */
    timer_init(TIMER1, &timer_initpara);

    /* CH1, CH2 and CH3 configuration in PWM0 mode */
    timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocintpara);
    timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);
    timer_channel_output_config(TIMER1, TIMER_CH_2, &timer_ocintpara);

    /* CH0 configuration in PWM mode1,duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, pwm_period / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    /* CH1 configuration in PWM mode1,duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, pwm_period / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    /* CH2 configuration in PWM mode1,duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, pwm_period / 2);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
    /* auto-reload preload enable */
    timer_enable(TIMER1);
}
