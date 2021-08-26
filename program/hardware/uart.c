//
// Created by Lao·Zhu on 2021/8/24.
//

#include "uart.h"
#include "config.h"
#include "gd32f1x0.h"
#include "system.h"

unsigned char dtp_status = 0;
unsigned char dtp_numcounter = 0;
unsigned char dtp_databuffer[10] = {0};

/*!
    \brief        user callback function for unpacking completion of medium capacity transport protocol
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \param[out]   none
    \retval       none
*/
extern void mdtp_callback_handler(unsigned char pid, unsigned char *data);

/*!
    \brief        medium capacity data transmission protocol unpacking handler
    \param[in]    data: data received from UART peripheral
    \param[out]   none
    \retval       none
*/
void mdtp_receive_handler(unsigned char data) {
    /* data receiving finite state machine */
    switch (dtp_status) {
        case 0:
            /* judge whether the packet header is received */
            if (data == 0xff) {
                /* enter the receive state */
                dtp_status = 1;
                /* clear receive array counter */
                dtp_numcounter = 0;
                /* clear the value in the buffer array */
                user_memset(dtp_databuffer, 0x00, sizeof(dtp_databuffer));
            }
            break;
        case 1:
            /* judge whether the end of the packet is mistakenly recognized as the header */
            if (!(data == 0xff && dtp_numcounter == 0)) {
                /* judge whether the reception is completed or the error data is received */
                if (dtp_numcounter != 10 && data != 0xff) {
                    /* receive the data into the array in turn */
                    dtp_databuffer[dtp_numcounter] = data;
                    dtp_numcounter = dtp_numcounter + 1;
                } else if (dtp_numcounter == 10)
                    /* jump to end of package processing */
                    dtp_status = 2;
                else {      /* an unexpected data had been received */
                    /* reset to receive start of package state */
                    dtp_status = 0;
                    /* clear receive array counter */
                    dtp_numcounter = 0;
                    /* clear the value in the buffer array */
                    user_memset(dtp_databuffer, 0x00, sizeof(dtp_databuffer));
                }
            }
        case 2:
            if (data == 0xff) {
                /* ready to receive the next packet */
                dtp_status = 0;
                /* verify whether the pid byte is correct*/
                if ((dtp_databuffer[0] >> 4) == (~dtp_databuffer[0] & 0x0f)) {
                    unsigned char tmp_rcv_buffer[8], counter = 0;
                    /* judge whether the package content is all 0xff */
                    if (dtp_databuffer[1] == 0xa5 && dtp_databuffer[9] == 0xa5)
                        /* fill all bytes with 0xff */
                        user_memset(tmp_rcv_buffer, 0xff, sizeof(tmp_rcv_buffer));
                    else {
                        /* traverse the data byte to be adjusted */
                        for (; counter < 8; ++counter)
                            /* judge whether the adjustment bit is 1 */
                            if (((dtp_databuffer[9] >> counter) & 0x01) == 0x01)
                                /* fill the data byte with 0xff */
                                tmp_rcv_buffer[counter] = 0xff;
                            else
                                /* copy data directly to the receiving array */
                                tmp_rcv_buffer[counter] = dtp_databuffer[counter + 1];
                    }
                    /* call user callback function to complete the next step */
                    mdtp_callback_handler(dtp_databuffer[0] >> 4, tmp_rcv_buffer);
                }
            } else {      /* an unexpected data had been received */
                /* reset to receive start of package state */
                dtp_status = 0;
                /* clear receive array counter */
                dtp_numcounter = 0;
                /* clear the value in the buffer array */
                user_memset(dtp_databuffer, 0x00, sizeof(dtp_databuffer));
            }
            break;
        default:
            /* reset to receive start of package state */
            dtp_status = 0;
            /* clear receive array counter */
            dtp_numcounter = 0;
            break;
    }
}

void mdtp_data_transmit(unsigned char pid, const unsigned char *buffer) {
    unsigned char temp_buf[12] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff};
    unsigned char mdtp_pack_counter;
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 8; mdtp_pack_counter++) {
        if (buffer[mdtp_pack_counter] == 0xff) {
            temp_buf[2 + mdtp_pack_counter] = 0x00;
            temp_buf[10] = (temp_buf[10] | (1 << mdtp_pack_counter));
        } else
            temp_buf[2 + mdtp_pack_counter] = buffer[mdtp_pack_counter];
    }
    temp_buf[1] = pid << 4 | ((~pid) & 0x0f);
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 12; mdtp_pack_counter++) {
        usart_data_transmit(USART0, (uint8_t) temp_buf[mdtp_pack_counter]);
        while (RESET == usart_flag_get(USART0, USART_FLAG_TBE));
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
