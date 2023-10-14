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