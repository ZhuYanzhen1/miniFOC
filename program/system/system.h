/**************************************************************************//**
  \file     system.h
  \brief    system basic function header file
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC_SYSTEM_SYSTEM_H_
#define MINIFOC_SYSTEM_SYSTEM_H_

void systick_config(void);
void delayms(unsigned long count);
void delay_decrement(void);
void user_memset(void *buf, unsigned char data, unsigned char num);
unsigned int float_to_int32(float data0);
float int32_to_float(unsigned int data0);

#endif // MINIFOC_SYSTEM_SYSTEM_H_
