//
// Created by LaoZhu on 2023/6/27.
//

#ifndef MINIFOC_HARDWARE_PWM_H_
#define MINIFOC_HARDWARE_PWM_H_

#include "stdint.h"

void pwm_config(void);
void pwm_stop(void);
void pwm_start(void);

void pwm_setval(int32_t u, int32_t v, int32_t w);

#endif  //MINIFOC_HARDWARE_PWM_H_
