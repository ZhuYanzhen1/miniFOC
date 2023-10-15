#include "main.h"

adc_sample_t adc_sample = {0};

void uart_receive_callback(unsigned char* buffer, unsigned char length) {
    DEBUG_INFO("%s", buffer)
}

int main(void) {
    system_config();
    dma_config();
    usart1_config();
    adc_config(&adc_sample);
    pwm_config();
    timer3_config();
    spi2_config();

    adc_read_offset(&adc_sample);

    pwm_start();
    adc_start();

    while (1) {
        uart_process_loop();
    }
}
