//
// Created by Lao·Zhu on 2021/9/2.
//

#include "encoder.h"
#include "spi.h"
#include "gd32f1x0.h"
#include "foc.h"
#include "timer.h"
#include "system.h"

#define MECHANGLE_COEFFICIENT 0.0030679f
#define ELECANGLE_COEFFICIENT 0.0214757f
#define SPEED_COEFFICIENT 0.4882812        // rps

unsigned short machine_angle_offset = 0;
unsigned short last_mechanical_angle = 0;
unsigned long total_machine_angle = 0;

unsigned short encoder_readdata(unsigned short TxData) {
    unsigned short data;
    unsigned char counter = 0xff;
    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    while (counter--);
    data = spi_readwrite_halfworld(TxData);
    counter = 0xff;
    while (counter--);
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);
    return data;
}

void encoder_config(void) {
    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    spi_readwrite_halfworld(0x4000 | 0x0700 | 0xCE);
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);

    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    spi_readwrite_halfworld(0x4000 | 0x0500 | 0x20 | (4095 >> 8));
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);

    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    spi_readwrite_halfworld(0x4000 | 0x0400 | (4095 & 0x00ff));
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);

    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    spi_readwrite_halfworld(0x4000 | 0x0800 | 0x14);
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);

    encoder_readdata(0x0000);
}

unsigned short encoder_get_mechanical_angle(void) {
    unsigned short angle = encoder_readdata(0x0000) >> 4;
    total_machine_angle = total_machine_angle + angle - last_mechanical_angle;
    last_mechanical_angle = angle;
    return ((total_machine_angle - machine_angle_offset) % 2048);
}

void encoder_get_electronic_angle(void) {
    unsigned short tmp_mechanical_angle = encoder_get_mechanical_angle();
    float mechanical_angle = (float) tmp_mechanical_angle * MECHANGLE_COEFFICIENT;
    float electric_angle = (float) (tmp_mechanical_angle % 292) * ELECANGLE_COEFFICIENT;
}

void Sensor_Config(void) {
    float u, v, w;
    foc_calculate_dutycycle(0, 0.6f, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
    delayms(250);
    machine_angle_offset = 0;
    total_machine_angle = 0;
    machine_angle_offset = encoder_get_mechanical_angle();
    delayms(250);
    foc_calculate_dutycycle(0, 0, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
}

//unsigned long systick_mechanical_angle_last = 0;
//void Update_AngleSpeed(void) {
//    unsigned short tmp_mechanical_angle_velocity = total_machine_angle - systick_mechanical_angle_last;
//    FOC_Structure.velocity =
//        FirstOrder_Filter_Calculate(&Velocity_f, qfp_fmul(tmp_mechanical_angle_velocity, SPEED_COEFFICIENT));
//    systick_mechanical_angle_last = total_machine_angle;
//}
//
