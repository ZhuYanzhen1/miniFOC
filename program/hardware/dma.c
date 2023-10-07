//
// Created by LaoZhu on 2023/10/5.
//

#include "dma.h"
#include "system.h"

void uart_dma_transmit(const unsigned int* buffer, unsigned int size) {
    DMA1_Channel4->CFGR &= (unsigned int)(~DMA_CFGR1_EN);
    DMA1_Channel4->CNTR = size;
    DMA1_Channel4->MADDR = (unsigned int)buffer;
    DMA1_Channel4->CFGR |= DMA_CFGR1_EN;
    USART1->CTLR3 |= USART_DMAReq_Tx;
}

void uart_dma_receive(const unsigned int* buffer, unsigned int size) {
    DMA1_Channel5->CFGR &= (unsigned int)(~DMA_CFGR1_EN);
    DMA1_Channel5->CNTR = size;
    DMA1_Channel5->MADDR = (unsigned int)buffer;
    DMA1_Channel5->CFGR |= DMA_CFGR1_EN;
    USART1->CTLR3 |= USART_DMAReq_Rx;
}

void dma_config(void) {
    DMA_InitTypeDef DMA_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr = 0x00000000UL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 0x00000000UL;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr = 0x00000000UL;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 0x00000000UL;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
