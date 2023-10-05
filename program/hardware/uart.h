//
// Created by LaoZhu on 2023/6/18.
//

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

#ifdef DEBUG
#include "stdio.h"

#define DEBUG_LOG_MAX_SIZE 512
extern char log_buffer[DEBUG_LOG_MAX_SIZE];

#define DEBUG_INFO(format, ...) do{\
    unsigned short unLen = 0;\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE, "[INFO]: ");\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE - unLen, format, ## __VA_ARGS__ );\
    send_buffer((unsigned char *)log_buffer, unLen);\
}while(0)

#define DEBUG_WARN(format, ...) do{\
    unsigned short unLen = 0;\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE, "[WARN][%s() %d]: ",__FUNCTION__, __LINE__);\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE - unLen, format, ## __VA_ARGS__ );\
    send_buffer((unsigned char *)log_buffer, unLen);\
}while(0)

#define DEBUG_ERR(format, ...) do{\
    unsigned short unLen = 0;\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE, "[ERR][%s() %d]: ",__FUNCTION__, __LINE__);\
    unLen += snprintf(log_buffer + unLen, DEBUG_LOG_MAX_SIZE - unLen, format, ## __VA_ARGS__ );\
    send_buffer((unsigned char *)log_buffer, unLen);\
}while(0)

#else

#define DEBUG_INFO(...)
#define DEBUG_WARN(...)
#define DEBUG_ERR(...)

#endif

void usart1_config(void);
void send_buffer(unsigned char *buf, unsigned short length);

#endif  // MINIFOC_HARDWARE_UART_H_
