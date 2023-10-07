#include "ch32v20x_it.h"
#include "main.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

void TIM1_UP_IRQHandler(void) {
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}

void USART1_IRQHandler(void) {
    if (__builtin_expect((USART_GetITStatus(USART1, USART_IT_IDLE) != RESET), 1)) {
        USART_ClearFlag(USART1, USART_IT_IDLE);
        unsigned char receive_size = (UART_RECEIVE_BUFFER_SIZE / 2) - DMA1_Channel5->CNTR;
        if (__builtin_expect((receive_size == 0), 1))
            return;
        if (receive_buffer_available[0] == 1) {
            receive_buffer_counter[1] = receive_size;
            uart_dma_receive((unsigned int*)receive_buffer1, UART_RECEIVE_BUFFER_SIZE / 2);
            receive_buffer_available[0] = 0;
        } else if (receive_buffer_available[1] == 1) {
            receive_buffer_counter[0] = receive_size;
            uart_dma_receive((unsigned int*)receive_buffer2, UART_RECEIVE_BUFFER_SIZE / 2);
            receive_buffer_available[1] = 0;
        }
    }
}

void DMA1_Channel4_IRQHandler(void) {
    if (__builtin_expect(DMA_GetITStatus(DMA1_IT_TC4) != RESET, 1)) {
        DMA_ClearFlag(DMA1_FLAG_TC4);
        first_transmit_buffer->length = 0;
        if (__builtin_expect((first_transmit_buffer->next_transmit_buffer != NULL), 0))
            uart_dma_transmit((unsigned int*)first_transmit_buffer->next_transmit_buffer->current_buffer,
                              first_transmit_buffer->next_transmit_buffer->length);
        first_transmit_buffer = first_transmit_buffer->next_transmit_buffer;
    }
}
