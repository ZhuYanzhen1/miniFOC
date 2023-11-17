//
// Created by LaoZhu on 2023/11/18.
//

#include "foc.h"
#include "config.h"
#include "fast_math.h"
#include "pwm.h"
#include "system.h"
#include "transform.h"

/*!
    \brief automatic phase sequence detection and correction
*/
void foc_calibrate_phase(void) {
    unsigned short last_angle = 0, positive_counter = 0;
    int32_t u, v, w, angle = 0;

    /* set that there is only a magnetic field on the straight axis */
    foc_calculate_dutycycle(0, IQ(CALIBRATE_TORQUE), 0, &u, &v, &w);
    pwm_setval(u, v, w);
    delayms(1000);

    for (unsigned char counter = 0; counter < 50; ++counter) {
        /* measure current motor angle */
        unsigned short current_angle = encoder_get_mechanical_angle();

        /* judge whether the current angle increases */
        if (current_angle > last_angle)
            positive_counter++;

        /* update last angle as current angle */
        last_angle = current_angle;

        /* set that there is only a magnetic field on the straight axis */
        foc_calculate_dutycycle(angle, IQ(CALIBRATE_TORQUE), 0, &u, &v, &w);
        angle += IQ(0.2);
        pwm_setval(u, v, w);
        delayms(20);
    }
    for (unsigned char counter = 0; counter < 50; ++counter) {
        /* measure current motor angle */
        unsigned short current_angle = encoder_get_mechanical_angle();

        /* judge whether the current angle decreases */
        if (current_angle < last_angle)
            positive_counter++;

        /* update last angle as current angle */
        last_angle = current_angle;

        /* set that there is only a magnetic field on the straight axis */
        foc_calculate_dutycycle(angle, IQ(CALIBRATE_TORQUE), 0, &u, &v, &w);
        angle -= IQ(0.2);
        pwm_setval(u, v, w);
        delayms(20);
    }

    /* zero the torque in all directions to release the motor */
    foc_calculate_dutycycle(0, 0, 0, &u, &v, &w);
    pwm_setval(u, v, w);
    delayms(300);

    if (positive_counter >= 75)
        phase_sequence = 0;
    else if (positive_counter < 25)
        phase_sequence = 1;
    else
        while (1) {}
}
