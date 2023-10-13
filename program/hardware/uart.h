//
// Created by LaoZhu on 2023/6/18.
//

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

#ifdef DEBUG
#include "stdio.h"

#define DEBUG_INFO(format, ...)                                                                                     \
    {                                                                                                               \
        unsigned char tmp_transmit_buffer[UART_TRANSMIT_BUFFER_SIZE] = {0};                                         \
        unsigned short unLen = snprintf((char*)tmp_transmit_buffer, UART_TRANSMIT_BUFFER_SIZE, "[INFO]: ");         \
        unLen +=                                                                                                    \
            snprintf((char*)tmp_transmit_buffer + unLen, UART_TRANSMIT_BUFFER_SIZE - unLen, format, ##__VA_ARGS__); \
        uart_transmit(tmp_transmit_buffer, unLen);                                                                  \
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

#define UART_RECEIVE_BUFFER_SIZE 256
#define UART_TRANSMIT_BUFFER_SIZE 32
#define UART_TRANSMIT_BUFFER_NUM 8

typedef struct UART_TRANSMIT_BUFFER_T {
    struct UART_TRANSMIT_BUFFER_T* next_transmit_buffer;
    unsigned char current_buffer[UART_TRANSMIT_BUFFER_SIZE];
    unsigned char length;
} uart_transmit_buffer_t;

extern volatile unsigned char receive_buffer1[UART_RECEIVE_BUFFER_SIZE / 2];
extern volatile unsigned char receive_buffer2[UART_RECEIVE_BUFFER_SIZE / 2];
extern volatile unsigned char receive_buffer_counter[2], receive_buffer_available[2];
extern uart_transmit_buffer_t* first_transmit_buffer;

void usart1_config(void);
void usart1_config_kernel(void);
void uart_receive_callback(unsigned char* buffer, unsigned char length);
unsigned char uart_transmit(const unsigned char* buffer, unsigned char length);
void uart_transmit_kernel(const unsigned char* buffer, unsigned char length);

#endif  // MINIFOC_HARDWARE_UART_H_
