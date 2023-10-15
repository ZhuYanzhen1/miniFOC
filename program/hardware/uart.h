//
// Created by LaoZhu on 2023/6/18.
//

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

#include "stdint.h"
#include "stdio.h"

#ifdef DEBUG
#define DEBUG_INFO(format, ...)                                                                                        \
    {                                                                                                                  \
        unsigned char tmp_transmit_buffer[UART_TRANSMIT_BUFFER_SIZE] = {0};                                            \
        unsigned short unLen = snprintf((char*)tmp_transmit_buffer, UART_TRANSMIT_BUFFER_SIZE, format, ##__VA_ARGS__); \
        uart_transmit(tmp_transmit_buffer, unLen);                                                                     \
    }

#define DEBUG_WARN(format, ...)                                                                                     \
    {                                                                                                               \
        unsigned char tmp_transmit_buffer[UART_TRANSMIT_BUFFER_SIZE] = {0};                                         \
        unsigned short unLen = snprintf((char*)tmp_transmit_buffer, UART_TRANSMIT_BUFFER_SIZE,                      \
                                        "[WARN][%s() %d]: ", __FUNCTION__, __LINE__);                               \
        unLen +=                                                                                                    \
            snprintf((char*)tmp_transmit_buffer + unLen, UART_TRANSMIT_BUFFER_SIZE - unLen, format, ##__VA_ARGS__); \
        uart_transmit(tmp_transmit_buffer, unLen);                                                                  \
    }

#define DEBUG_ERR(format, ...)                                                                                      \
    {                                                                                                               \
        unsigned char tmp_transmit_buffer[UART_TRANSMIT_BUFFER_SIZE] = {0};                                         \
        unsigned short unLen = snprintf((char*)tmp_transmit_buffer, UART_TRANSMIT_BUFFER_SIZE,                      \
                                        "[ERR][%s() %d]: ", __FUNCTION__, __LINE__);                                \
        unLen +=                                                                                                    \
            snprintf((char*)tmp_transmit_buffer + unLen, UART_TRANSMIT_BUFFER_SIZE - unLen, format, ##__VA_ARGS__); \
        uart_transmit(tmp_transmit_buffer, unLen);                                                                  \
    }

#else

#define DEBUG_INFO(...)
#define DEBUG_WARN(...)
#define DEBUG_ERR(...)

#endif

#define KERNEL_DEBUG_INFO(format, ...)                                                           \
    {                                                                                            \
        unsigned char tmp_transmit_buffer[256] = {0};                                            \
        unsigned short unLen = snprintf((char*)tmp_transmit_buffer, 256, format, ##__VA_ARGS__); \
        uart_transmit_kernel(tmp_transmit_buffer, unLen);                                        \
    }

void usart1_config(void);
void usart1_config_kernel(void);
void uart_process_loop(void);
void uart_receive_callback(const uint8_t* buffer, uint8_t length);
uint8_t uart_transmit(const uint8_t* buffer, uint8_t length);
void uart_transmit_kernel(const uint8_t* buffer, uint8_t length);

#endif  // MINIFOC_HARDWARE_UART_H_
