//
// Created by LaoZhu on 2023/6/27.
//

#ifndef MINIFOC_HARDWARE_PWM_H_
#define MINIFOC_HARDWARE_PWM_H_

void pwm_config(void);
void pwm_stop(void);
void pwm_start(void);

void pwm_setval(float u, float v, float w);

#endif  //MINIFOC_HARDWARE_PWM_H_
