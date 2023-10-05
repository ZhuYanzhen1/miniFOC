#include "main.h"

int main(void) {
    system_config();
    usart1_config();
    timer_config();

//    TIM_Cmd(TIM1, ENABLE);
//    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    DEBUG_INFO("SystemClk:%lu\r\n", SystemCoreClock);
    DEBUG_INFO("This is printf example\r\n");

    while (1);
}
