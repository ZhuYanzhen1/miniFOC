//
// Created by Lao·Zhu on 2021/8/24.
//

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

#define uart_sendbyte(x);   usart_data_transmit(USART0, (uint8_t) x);\
                            while (RESET ==usart_flag_get(USART0, USART_FLAG_TBE))

void uart_config(void);
void mdtp_data_transmit(unsigned char pid, const unsigned char *buffer);

#endif // MINIFOC_HARDWARE_UART_H_
