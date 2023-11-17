#include "main.h"

adc_sample_t adc_sample = {0};
foc_structure_t foc = {0};

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

    encoder_zeroing();
    foc_calibrate_phase();

    while (1) {
        int32_t u, v, w;
        spi2_send_data(0x0000);
        //        int elec_angle = (int)(IQ16toF(foc.electric_angle) * 100.0f);
        //        int mach_angle = (int)(IQ16toF(foc.mechanical_angle) * 100.0f);
        //        DEBUG_INFO("Ele %d.%d Mac %d.%d\r\n", elec_angle / 100, elec_angle % 100, mach_angle / 100, mach_angle % 100)
        foc_calculate_dutycycle(IQ16toIQ(foc.electric_angle), 0, IQ(0.2), &u, &v, &w);
        pwm_setval(v, u, w);
        uart_process_loop();
        delayus(100);
        //        delayms(100);
    }
}
