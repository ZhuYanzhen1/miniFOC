//
// Created by LaoZhu on 2023/10/5.
//

#ifndef MINIFOC_HARDWARE_DMA_H_
#define MINIFOC_HARDWARE_DMA_H_

#include "stdint.h"

void dma_config(void);
void uart_dma_transmit(const uint32_t* buffer, uint32_t size);
void uart_dma_receive(const uint32_t* buffer, uint32_t size);

#endif  //MINIFOC_HARDWARE_DMA_H_
