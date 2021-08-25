//
// Created by Lao·Zhu on 2021/8/20.
//

#ifndef MINIFOC_SYSTEM_SYSTEM_H_
#define MINIFOC_SYSTEM_SYSTEM_H_

void systick_config(void);
void delayms(uint32_t count);
void delay_decrement(void);
void user_memset(void *buf, unsigned char data, unsigned char num);

#endif // MINIFOC_SYSTEM_SYSTEM_H_
