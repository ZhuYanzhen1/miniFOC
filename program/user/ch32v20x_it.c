#include "ch32v20x_it.h"
#include "main.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

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

extern adc_sample_t adc_sample;
void ADC1_2_IRQHandler(void) {
    if ((ADC1->STATR & ADC_FLAG_JEOC) == ADC_FLAG_JEOC) {
        read_adc_current(&adc_sample);
        //        //读取采样电流
        //        StatCurr3S_M = Current_Cal_2R(&ADC_M, ADC1);
        //        //AB电流转换成电流转换成alpha、beta电流
        //        StatCurr2S_M = Clark_TransForm(&StatCurr3S_M);
        //        //获取角度的正弦和余弦值
        //        Struct_Cossin_M = TrigonoMetric_Function(HALL_Cal_M.PosiElecPU);
        //        //两相旋转坐标系电流计算
        //        StatCurr2R_M = Park_TransForm(&StatCurr2S_M, &Struct_Cossin_M);
        //        //d轴电流调节
        //        StatVoltRef2R_M.cd = PID_Calculaion(StatCurrRef2R_M.cd, StatCurr2R_M.cd, &dCurrRegStruc_M);
        //        //q轴电流调节
        //        StatVoltRef2R_M.cq = PID_Calculaion(StatCurrRef2R_M.cq, StatCurr2R_M.cq, &qCurrRegStruc_M);
        //        //d、q轴给定电压和限幅
        //        StatVoltRef2R_M =
        //            ComponentLimit_2Ror2S(&StatVoltRef2R_M, MAX_MODULATION, &(SVPWM_Cal_M.VoltLimMark), Magnitude_table);
        //        //alpha、beta轴给定电压值计算
        //        StatVoltRef2S_M = Rev_Park_TransForm(&StatVoltRef2R_M, &Struct_Cossin_M);
        //        //SVPWM计算，开始电流调节
        //        SVPWM_Calculation(&SVPWM_Cal_M, &StatVoltRef2S_M, TIM1);
        //        //ADC触发时刻计算
        //        ADC_Trigger(&SVPWM_Cal_M, ADC1, TIM1);

        ADC1->STATR = ~(uint32_t)ADC_FLAG_JEOC;  //清除注入转换完成标志，下次中断做准备
    }
}