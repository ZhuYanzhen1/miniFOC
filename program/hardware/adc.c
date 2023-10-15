//
// Created by LaoZhu on 2023/10/6.
//

#include "adc.h"
#include "system.h"

void adc_stop(void) {
    ADC1->CTLR2 &= 0xFFFFEFFF;
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_T1_TRGO);
}

void adc_start(void) {
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_T1_CC4);
}

int16_t get_adc_calibrate(int16_t adc_offset, int16_t data) {
    int16_t adc_result = (int16_t)(adc_offset + data);
    if (__builtin_expect((adc_result < 0), 0))
        return 0;
    if (__builtin_expect((adc_result > 4095), 0))
        return 4095;
    return adc_result;
}

void adc_config(adc_sample_t* adc_sample) {
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef Timer_OCInitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_OCStructInit(&Timer_OCInitStructure);
    Timer_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    Timer_OCInitStructure.TIM_Pulse = 1;
    Timer_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    Timer_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    Timer_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    Timer_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    Timer_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    Timer_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC4Init(TIM1, &Timer_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ITConfig(TIM1, TIM_IT_CC4, DISABLE);

    ADC_DeInit(ADC1);
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode = ADC_Mode_InjecSimult;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_7Cycles5);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1)) {}
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1)) {}
    adc_sample->adc1_offset = Get_CalibrationValue(ADC1);

    //    ADC_DeInit(ADC2);
    //    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    //    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    //    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    //    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    //    ADC_InitStructure.ADC_NbrOfChannel = 1;
    //    ADC_Init(ADC2, &ADC_InitStructure);
    //
    //    ADC_RegularChannelConfig(ADC2, ADC_Channel_TempSensor, 1, ADC_SampleTime_239Cycles5);
    //    ADC_Cmd(ADC2, ENABLE);
    //
    //    ADC_BufferCmd(ADC2, DISABLE);
    //    adc_sample->adc2_offset = Get_CalibrationValue(ADC2);
    //    ADC_BufferCmd(ADC2, ENABLE);
    //
    //    ADC_TempSensorVrefintCmd(ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM1->CH4CVR = 1;

    /* 2 inject channel, ADC_Channel_6 is No.4, ADC_Channel_7 is No.3 */
    ADC1->ISQR = ((ADC_Channel_7) << 10) | ((ADC_Channel_6) << 15) | 0x00100000;
}

void adc_read_offset(adc_sample_t* adc_sample) {
    adc_sample->ch1_offset = 0;
    adc_sample->ch3_offset = 0;

    ADC_ITConfig(ADC1, ADC_IT_JEOC, DISABLE);
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);

    ADC_InjectedSequencerLengthConfig(ADC1, 2);

    ADC_InjectedChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_7Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_7Cycles5);

    ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
    ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);

    for (unsigned char counter = 0; counter < 16; counter++) {
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC)) {}

        adc_sample->ch1_offset += ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1) & 0x0FFF;
        adc_sample->ch3_offset += ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2) & 0x0FFF;
        adc_sample->ch1_offset += adc_sample->adc1_offset;
        adc_sample->ch3_offset += adc_sample->adc1_offset;

        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
    }

    adc_sample->ch1_offset = adc_sample->ch1_offset >> 4;
    adc_sample->ch3_offset = adc_sample->ch3_offset >> 4;

    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_T1_TRGO);
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);
    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
}

void read_adc_current(adc_sample_t* adc_sample) {
    int16_t adc_channel_6 = get_adc_calibrate(adc_sample->adc1_offset, ADC1->IDATAR1 & 0x0FFF);
    int16_t adc_channel_7 = get_adc_calibrate(adc_sample->adc1_offset, ADC1->IDATAR2 & 0x0FFF);
    adc_sample->phase1_current = (adc_channel_6 - (int16_t)adc_sample->ch1_offset);
    adc_sample->phase3_current = (adc_channel_7 - (int16_t)adc_sample->ch3_offset);
    adc_sample->phase2_current = -(adc_sample->phase1_current + adc_sample->phase3_current);
}
