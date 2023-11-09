#include "main.h"

adc_sample_t adc_sample = {0};

void mdtp_callback_handler(uint8_t pid, uint8_t* buffer) {
    DEBUG_INFO("Rcv pid: %d\r\n", pid)
    DEBUG_INFO("%02x %02x %02x %02x %02x %02x %02x %02x\r\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4],
               buffer[5], buffer[6], buffer[7])
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
        spi2_send_data(0x0000);
        uart_process_loop();
        delayms(200);
    }
}
