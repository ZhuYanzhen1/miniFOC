#include "ch32v20x_it.h"
#include "main.h"

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SPI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void TIM3_IRQHandler(void) {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

void TIM1_UP_IRQHandler(void) {
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
}

void SPI2_IRQHandler(void) {
    if (__builtin_expect((SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET), 1)) {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        SPI_I2S_ClearFlag(SPI2, SPI_I2S_FLAG_RXNE);
        SPI_I2S_ReceiveData(SPI2);
        SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
    }
}

extern adc_sample_t adc_sample;
void ADC1_2_IRQHandler(void) {
    if ((ADC1->STATR & ADC_FLAG_JEOC) == ADC_FLAG_JEOC) {
        read_adc_current(&adc_sample);
        ADC1->STATR = ~(uint32_t)ADC_FLAG_JEOC;
    }
}