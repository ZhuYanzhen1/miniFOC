//
// Created by Lao·Zhu on 2021/8/24.
//

#include "uart.h"
#include "config.h"
#include "gd32f1x0.h"
#include "system.h"

volatile static unsigned char mdtp_receive_status = 0;
volatile static unsigned char mdtp_receive_number_counter = 0;
static unsigned char mdtp_receive_data_buffer[10] = {0};

/*!
    \brief        medium capacity data transmission protocol unpacking handler
    \param[in]    data: data received from UART peripheral
    \param[out]   none
    \retval       none
*/
void mdtp_receive_handler(unsigned char data) {
    /* data receiving finite state machine */
    switch (mdtp_receive_status) {
        case 0:
            /* judge whether the packet header is received */
            if (data == 0xff) {
                /* enter the receive state */
                mdtp_receive_status = 1;
                /* clear receive array counter */
                mdtp_receive_number_counter = 0;
                /* clear the value in the buffer array */
                user_memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            }
            break;
        case 1:
            /* judge whether the end of the packet is mistakenly recognized as the header */
            if (data == 0xff && mdtp_receive_number_counter != 0) {
                /* an unexpected data had been received */
                /* reset to receive start of package state */
                mdtp_receive_status = 0;
                /* clear receive array counter */
                mdtp_receive_number_counter = 0;
                /* clear the value in the buffer array */
                user_memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            } else if (data != 0xff) {
                /* judge whether the reception is completed or the error data is received */
                if (mdtp_receive_number_counter != 10) {
                    /* receive the data into the array in turn */
                    mdtp_receive_data_buffer[mdtp_receive_number_counter] = data;
                    mdtp_receive_number_counter = mdtp_receive_number_counter + 1;
                    if (mdtp_receive_number_counter == 10)
                        mdtp_receive_status = 2;
                }
            }
            break;
        case 2:
            if (data == 0xff) {
                /* ready to receive the next packet */
                mdtp_receive_status = 0;
                /* verify whether the pid byte is correct*/
                if ((mdtp_receive_data_buffer[0] >> 4) == (~mdtp_receive_data_buffer[0] & 0x0f)) {
                    unsigned char tmp_rcv_buffer[8], counter = 0;
                    /* judge whether the package content is all 0xff */
                    if (mdtp_receive_data_buffer[1] == 0xa5 && mdtp_receive_data_buffer[9] == 0xa5)
                        /* fill all bytes with 0xff */
                        user_memset(tmp_rcv_buffer, 0xff, sizeof(tmp_rcv_buffer));
                    else {
                        /* traverse the data byte to be adjusted */
                        for (; counter < 8; ++counter)
                            /* judge whether the adjustment bit is 1 */
                            if (((mdtp_receive_data_buffer[9] >> counter) & 0x01) == 0x01)
                                /* fill the data byte with 0xff */
                                tmp_rcv_buffer[counter] = 0xff;
                            else
                                /* copy data directly to the receiving array */
                                tmp_rcv_buffer[counter] = mdtp_receive_data_buffer[counter + 1];
                    }
                    /* call user callback function to complete the next step */
                    mdtp_callback_handler(mdtp_receive_data_buffer[0] >> 4, tmp_rcv_buffer);
                }
            } else {      /* an unexpected data had been received */
                /* reset to receive start of package state */
                mdtp_receive_status = 0;
                /* clear receive array counter */
                mdtp_receive_number_counter = 0;
                /* clear the value in the buffer array */
                user_memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            }
            break;
    }
}

/*!
    \brief      medium capacity data transmission protocol packing function
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \param[out]   none
    \retval     none
*/
void mdtp_data_transmit(unsigned char pid, const unsigned char *buffer) {
    unsigned char temp_buf[12] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0xff};
    unsigned char mdtp_pack_counter;
    /* traverse the array to determine whether there are bytes to be adjusted */
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 8; mdtp_pack_counter++) {
        /* judge whether this byte need to be adjusted */
        if (buffer[mdtp_pack_counter] == 0xff) {
            temp_buf[2 + mdtp_pack_counter] = 0x00;
            /* modify the corresponding bit of the adjustment byte */
            temp_buf[10] = (temp_buf[10] | (1 << mdtp_pack_counter));
        } else
            /* copy data directly to transmit buffer array */
            temp_buf[2 + mdtp_pack_counter] = buffer[mdtp_pack_counter];
    }
    /* judge whether the package is all 0xff */
    if (temp_buf[10] == 0xff)
        temp_buf[10] = temp_buf[2] = 0xa5;
    /* load self checking packet id byte */
    temp_buf[1] = pid << 4 | ((~pid) & 0x0f);
    /* traverse the buffer array and send all bytes through UART0 */
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 12; mdtp_pack_counter++) {
        /* transmit single byte through UART0 */
        uart_sendbyte(temp_buf[mdtp_pack_counter]);
    }
}

/*!
    \brief      configure uart0 periph and its gpios
    \param[in]  none
    \param[out] none
    \retval     none
*/
void uart_config(void) {
    /* UART interrupt configuration */
    nvic_irq_enable(USART0_IRQn, UART_PRIORITY, 0);
    /* enable GPIO clock and UART clock*/
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    /* connect port to UARTx_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
    /* connect port to UARTx_Rx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);
    /* configure UART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);
    /* configure UART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_10);
    /* UART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, UART_BAUDRATE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_enable(USART0);
    /* enable UART RBNE interrupt */
    usart_interrupt_enable(USART0, USART_INT_RBNE);
}
