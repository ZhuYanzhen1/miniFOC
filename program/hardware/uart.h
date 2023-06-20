//
// Created by LaoZhu on 2023/6/18.
//

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

#ifdef DEBUG
#include "stdio.h"

#define LOG(format, ...)    printf(format, ##__VA_ARGS__)
#else
#define LOG(X...)
#endif

void usart1_config(void);

#endif  // MINIFOC_HARDWARE_UART_H_
