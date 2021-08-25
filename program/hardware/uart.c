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
void mdtp_receive_handler(unsigned char data) {
    switch (dtp_status) {
        case 0:
            /* Judge whether the packet header is received */
            if (data == 0xff) {
                /* Enter the receive state and clear the relevant registers */
                dtp_status = 1;
                dtp_numcounter = 0;
                user_memset(dtp_databuffer, 0x00, sizeof(dtp_databuffer));
            }
            break;
        case 1:
            if (data == 0xff && dtp_numcounter != 9)
                dtp_status = 0;
            if (dtp_numcounter != 10) {
                dtp_databuffer[dtp_numcounter] = data;
                dtp_numcounter = dtp_numcounter + 1;
            } else
                dtp_status = 2;
            break;
        default:dtp_status = 0;
            break;
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
