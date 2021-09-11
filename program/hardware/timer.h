//
// Created by Lao·Zhu on 2021/8/29.
//

#ifndef MINIFOC_HARDWARE_TIMER_H_
#define MINIFOC_HARDWARE_TIMER_H_

#define PWM_PERIOD  18000 / PWM_FREQUENCY

void update_pwm_dutycycle(float ch0, float ch1, float ch2);
void timer2_disable(void);
void timer13_disable(void);
void timer2_config(void);
void timer13_config(void);
void pwm_config(void);

#endif //MINIFOC_HARDWARE_TIMER_H_
