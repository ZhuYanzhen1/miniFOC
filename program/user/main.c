#include "main.h"

adc_sample_t adc_sample = {0};

int main(void) {
    system_config();
    dma_config();
    usart1_config();
    pwm_config();
    adc_config();
    timer3_config();
    spi2_config();

    adc_read_offset(&adc_sample);

    pwm_start();
    adc_start();

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

        delayms(5);
    }
}
