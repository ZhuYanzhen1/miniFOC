//
// Created by LaoZhu on 2023/6/27.
//

#include "timer.h"
#include "system.h"

#define TIMER1_HALF_CYCLE   ((144000000 / (TIM1_PRESCALER + 1)) / PWM_FREQUENCY)

void timer_config(void) {
    // 配置寄存器结构体定义
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    //时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

    //PWM用IO配置
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //定时器1配置
    TIM_DeInit(TIM1);//定时器寄存器复位

    //用于初始化定时器结构体的初始化
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    //预分频配置
    TIM_TimeBaseStructure.TIM_Prescaler = TIM1_PRESCALER;

    //增减计数模式配置
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;

    //周期配置
    TIM_TimeBaseStructure.TIM_Period = TIMER1_HALF_CYCLE;

    //数字滤波器和死区发生器分频比例：2分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;

    //事件更新速率
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 1;

    //配置寄存器实体
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    //比较器初始化用结构体的初始化
    TIM_OCStructInit(&TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//大于于比较寄存器值为有效，否则为无效

    //正向通道比较输出使能
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    //互补通道比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;

    //dummy value
    TIM_OCInitStructure.TIM_Pulse = TIMER1_HALF_CYCLE / 2;

    //正向通道比较输出高电平有效
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;

    //正向通道空闲状态为低电平
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);//捕获比较通道1初始化
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);//捕获比较通道2初始化
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);//捕获比较通道3初始化

    //使能timer1的四路比较输出的预加载功能
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能捕获比较通道1的预装载
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能捕获比较通道1的预装载
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能捕获比较通道1的预装载

    //中断配置
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);//选择更新事件作为外部触发源
    TIM_SetCounter(TIM1, 0);                    //定时器计数器清零
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);      //清除更新事件中断标志
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能更新事件的中断
}
