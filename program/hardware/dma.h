//
// Created by LaoZhu on 2023/10/5.
//

#ifndef MINIFOC_HARDWARE_DMA_H_
#define MINIFOC_HARDWARE_DMA_H_

void dma_config(void);
void uart_dma_transmit(const unsigned int *buffer, unsigned int size);
void uart_dma_receive(const unsigned int *buffer, unsigned int size);

#endif //MINIFOC_HARDWARE_DMA_H_
