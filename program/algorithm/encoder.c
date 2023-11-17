//
// Created by LaoZhu on 2023/11/10.
//

#include "encoder.h"
#include "config.h"
#include "fast_math.h"
#include "pwm.h"
#include "spi.h"
#include "system.h"
#include "transform.h"
#include "uart.h"

int16_t encoder_offset_value = 0;

void update_encoder_angle(uint16_t current_encoder_angle) {
    /* read back the mechanical angle directly from the magnetic encoder */
    uint16_t tmp_mechanical_angle = (current_encoder_angle - encoder_offset_value) % 0x4000;

    /* calculate and update the mechanical angle and electric angle */
    foc.mechanical_angle = IQ16mul(IQ16(tmp_mechanical_angle), IQ16(MECHANGLE_COEFFICIENT));
    foc.electric_angle =
        IQ16mul((IQ16(tmp_mechanical_angle % (ENCODER_RESO / POLAR_PAIRS))), IQ16(ELECANGLE_COEFFICIENT));
}

void encoder_zeroing(void) {
    int32_t u, v, w, total_angle = 0;
    delayms(200);
    foc_calculate_dutycycle(0, IQ(CALIBRATE_TORQUE), 0, &u, &v, &w);
    pwm_setval(u, v, w);
    delayms(300);
    for (uint32_t counter = 0; counter < 10; ++counter) {
        spi2_send_data(0x0000);
        delayms(20);
        total_angle += foc.encoder_data;
    }
    encoder_offset_value = (int16_t)(total_angle / 10);
    encoder_offset_value -= 0x4000;
    pwm_setval(IQ(0.5), IQ(0.5), IQ(0.5));
    delayms(300);
    DEBUG_INFO("Offset value: 0x%x", encoder_offset_value);
}
