/**************************************************************************//**
  \file     error.h
  \brief    used to check whether the user configured parameters conflict
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC__ERROR_H_
#define MINIFOC__ERROR_H_

#include "config.h"

#if TIM13_FREQUENCY > (SPEED_UP_FREQ / 2)
#error "you can't set pid frequency higher than update frequency"
#endif

#if TIM2_FREQUENCY > PWM_FREQUENCY
#error "you can't set foc loop frequency higher than pwm frequency"
#endif

#if TIM13_FREQUENCY > (TIM2_FREQUENCY * 1000)
#error "you can't set pid frequency higher than foc loop frequency"
#endif

#if FMC_WRITE_START_ADDR < 0x08004000UL
#error "user flash lash takes up too much space, which makes the program space insufficient"
#endif

#endif //MINIFOC__ERROR_H_
