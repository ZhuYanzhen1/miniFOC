#include "main.h"

int main(void) {
    system_config();
    dma_config();
    usart1_config();
    timer_config();
    adc_config();

    //    TIM_Cmd(TIM1, ENABLE);
    //    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    DEBUG_INFO("SystemClk: %lu\r\n", SystemCoreClock);

    while (1) {
        if (__builtin_expect((receive_buffer_counter[0] != 0), 0)) {
            uart_receive_callback((unsigned char*)receive_buffer1, receive_buffer_counter[0]);
            receive_buffer_counter[0] = 0;
            receive_buffer_available[0] = 1;
        }

        if (__builtin_expect((receive_buffer_counter[1] != 0), 0)) {
            uart_receive_callback((unsigned char*)receive_buffer2, receive_buffer_counter[1]);
            receive_buffer_counter[1] = 0;
            receive_buffer_available[1] = 1;
        }
    }
}
