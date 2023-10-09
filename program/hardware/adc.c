//
// Created by LaoZhu on 2023/10/6.
//

#include "adc.h"
#include "system.h"

void adc_config(void) {
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef Timer_OCInitStructure = {0};

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
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_7Cycles5);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1)) {}
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1)) {}

    TIM1->CH4CVR = 1;

    /* 2 inject channel, ADC_Channel_6 is No.4, ADC_Channel_7 is No.3 */
    ADC1->ISQR = ((ADC_Channel_7) << 10) | ((ADC_Channel_6) << 15) | 0x00100000;
}

void adc_read_offset(adc_sample_t* adc_sample) {
    adc_sample->ch1_offset = 0;
    adc_sample->ch3_offset = 0;

    //禁止自动的注入通道组转换，禁止注入中断
    ADC_ITConfig(ADC1, ADC_IT_JEOC, DISABLE);

    //注入转换外部触发源为软件触发
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);

    //使能外部事件启动注入转换
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);

    //注入序列转换长度为2
    ADC_InjectedSequencerLengthConfig(ADC1, 2);

    ADC_InjectedChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_7Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_7Cycles5);

    ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);  //清除注入转换结束标志位

    ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);  //软件触发注入转换

    //累加16次，即采样结果左移4位，实现注入转换的左对齐(和规则采样一致)
    for (unsigned char counter = 0; counter < 16; counter++) {
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC)) {}

        //采样结果右移3位累加
        adc_sample->ch1_offset += (ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1) >> 3);
        adc_sample->ch3_offset += (ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2) >> 3);

        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);              //清除注入转换结束标志位
        ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);  //再次软件触发
    }

    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_T1_TRGO);
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);
    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
}
