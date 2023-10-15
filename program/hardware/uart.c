//
// Created by LaoZhu on 2023/6/18.
//

#include "uart.h"
#include "dma.h"
#include "system.h"

typedef struct UART_TRANSMIT_BUFFER_T {
    struct UART_TRANSMIT_BUFFER_T* next_transmit_buffer;
    volatile uint8_t current_buffer[UART_TRANSMIT_BUFFER_SIZE];
    uint8_t length;
} uart_transmit_buffer_t;

static volatile uint32_t dummy_read_byte = 0x00000000UL;
static volatile uint8_t receive_buffer1[UART_RECEIVE_BUFFER_SIZE / 2] = {0};
static volatile uint8_t receive_buffer2[UART_RECEIVE_BUFFER_SIZE / 2] = {0};
static uint8_t receive_buffer_counter[2] = {0, 0}, receive_buffer_available[2] = {0, 1};

static uart_transmit_buffer_t *first_transmit_buffer = NULL, *tail_transmit_buffer = NULL;
static uart_transmit_buffer_t uart_transmit_buffer[UART_TRANSMIT_BUFFER_NUM] = {0};

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void USART1_IRQHandler(void) {
    if (__builtin_expect((USART_GetITStatus(USART1, USART_IT_IDLE) != RESET), 1)) {
        dummy_read_byte = USART1->DATAR;
        uint8_t receive_size = (UART_RECEIVE_BUFFER_SIZE / 2) - DMA1_Channel5->CNTR;
        if (receive_buffer_available[0] == 1) {
            receive_buffer_counter[1] = receive_size;
            uart_dma_receive((uint32_t*)receive_buffer1, UART_RECEIVE_BUFFER_SIZE / 2);
            receive_buffer_available[0] = 0;
        } else if (receive_buffer_available[1] == 1) {
            receive_buffer_counter[0] = receive_size;
            uart_dma_receive((uint32_t*)receive_buffer2, UART_RECEIVE_BUFFER_SIZE / 2);
            receive_buffer_available[1] = 0;
        }
    }
}

void DMA1_Channel4_IRQHandler(void) {
    if (__builtin_expect(DMA_GetITStatus(DMA1_IT_TC4) != RESET, 1)) {
        DMA_ClearFlag(DMA1_FLAG_TC4);
        first_transmit_buffer->length = 0;
        if (__builtin_expect((first_transmit_buffer->next_transmit_buffer != NULL), 0))
            uart_dma_transmit((uint32_t*)first_transmit_buffer->next_transmit_buffer->current_buffer,
                              first_transmit_buffer->next_transmit_buffer->length);
        first_transmit_buffer = first_transmit_buffer->next_transmit_buffer;
    }
}

void __attribute__((weak)) uart_receive_callback(const uint8_t* buffer, uint8_t length) {}

void uart_process_loop(void) {
    if (__builtin_expect((receive_buffer_counter[0] != 0), 0)) {
        uart_receive_callback((uint8_t*)receive_buffer1, receive_buffer_counter[0]);
        receive_buffer_counter[0] = 0;
        receive_buffer_available[0] = 1;
    }
    if (__builtin_expect((receive_buffer_counter[1] != 0), 0)) {
        uart_receive_callback((uint8_t*)receive_buffer2, receive_buffer_counter[1]);
        receive_buffer_counter[1] = 0;
        receive_buffer_available[1] = 1;
    }
}

void uart_transmit_kernel(const uint8_t* buffer, uint8_t length) {
    for (uint8_t counter = 0; counter < length; ++counter) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
        USART_SendData(USART1, buffer[counter]);
    }
}

uint8_t uart_transmit(const uint8_t* buffer, uint8_t length) {
    uart_transmit_buffer_t* available_buffer = NULL;
    for (uint8_t counter = 0; counter < UART_TRANSMIT_BUFFER_NUM; ++counter)
        if (__builtin_expect((uart_transmit_buffer[counter].length == 0), 1)) {
            available_buffer = &(uart_transmit_buffer[counter]);
            break;
        }
    if (__builtin_expect((available_buffer == NULL), 0))
        return 1;

    available_buffer->length = (length > UART_TRANSMIT_BUFFER_SIZE) ? UART_TRANSMIT_BUFFER_SIZE : length;
    for (uint8_t counter = 0; counter < available_buffer->length; ++counter)
        available_buffer->current_buffer[counter] = buffer[counter];
    available_buffer->next_transmit_buffer = NULL;

    if (__builtin_expect((first_transmit_buffer == NULL), 1)) {
        first_transmit_buffer = available_buffer;
        uart_dma_transmit((uint32_t*)first_transmit_buffer->current_buffer, first_transmit_buffer->length);
    } else
        tail_transmit_buffer->next_transmit_buffer = available_buffer;
    tail_transmit_buffer = available_buffer;
    return 0;
}

void usart1_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    USART_InitStructure.USART_BaudRate = DEBUG_SERIAL_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    DMA_Cmd(DMA1_Channel4, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);
    USART_Cmd(USART1, ENABLE);

    uart_dma_receive((uint32_t*)receive_buffer1, UART_RECEIVE_BUFFER_SIZE / 2);

    for (uint8_t counter = 0; counter < UART_TRANSMIT_BUFFER_NUM; ++counter)
        uart_transmit_buffer[counter].length = 0;
}

void usart1_config_kernel(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    USART_DeInit(USART1);
    USART_InitStructure.USART_BaudRate = DEBUG_SERIAL_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
