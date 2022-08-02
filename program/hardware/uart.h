/**************************************************************************//**
  \file     uart.h
  \brief    this is the header file of uart.c.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     10. October 2021
 ******************************************************************************/

#ifndef MINIFOC_HARDWARE_UART_H_
#define MINIFOC_HARDWARE_UART_H_

/*!
    \brief     UART send single byte macro
    \param[in] x: byte to be send from UART
*/
#define uart_sendbyte(x);   usart_data_transmit(USART0, (uint8_t) x);\
                            while (RESET ==usart_flag_get(USART0, USART_FLAG_TBE))

void uart_config(void);
void mdtp_data_transmit(unsigned char pid, const unsigned char *buffer);
void mdtp_receive_handler(unsigned char data);
void mdtp_callback_handler(unsigned char pid, const unsigned char *data);

#endif // MINIFOC_HARDWARE_UART_H_
