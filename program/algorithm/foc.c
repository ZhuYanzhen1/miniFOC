/**************************************************************************//**
  \file     foc.c
  \brief    this document is mainly the code implementation of motor
            phase sequence correction and FOC algorithm.
  \author   Lao·Zhu
  \version  V1.0.3
  \date     1. August 2023
 ******************************************************************************/

#include "foc.h"
#include "config.h"
#include "fast_math.h"
#include "encoder.h"
#include "system.h"
#include "timer.h"

/*!
    \brief FOC handler
*/
volatile FOC_Structure_t FOC_Struct;
/*!
    \brief motor phase sequence flag variable
*/
volatile unsigned char phase_sequence = 0;
/*!
    \brief flag variable for FOC parameter availability
*/
unsigned char foc_parameter_available_flag = 1;

/*!
    \brief automatic phase sequence detection and correction
*/
void foc_calibrate_phase(void) {
    unsigned short last_angle = 0, positive_counter = 0;
    float u, v, w, angle = 0;

    /* set that there is only a magnetic field on the straight axis */
    foc_calculate_dutycycle(0, CALI_TORQUE, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
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
        foc_calculate_dutycycle(angle, CALI_TORQUE, 0, &u, &v, &w);
        angle += 0.2f;
        update_pwm_dutycycle(u, v, w);
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
        foc_calculate_dutycycle(angle, CALI_TORQUE, 0, &u, &v, &w);
        angle -= 0.2f;
        update_pwm_dutycycle(u, v, w);
        delayms(20);
    }

    /* zero the torque in all directions to release the motor */
    foc_calculate_dutycycle(0, 0, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
    delayms(300);

    if (positive_counter >= 75)
        phase_sequence = 0;
    else if (positive_counter < 25)
        phase_sequence = 1;
    else
        while (1);
}

/*!
    \brief      calculate the corresponding three-phase PWM duty cycle under the current electrical angle
    \param[in]  elect_angle: electrical angle of motor rotor, in radian system
    \param[in]  d: expected field strength in the direct axis direction of the motor
    \param[in]  q: expected field strength in the quadrature axis direction of the motor
    \param[out] u: calculation results of U-phase duty cycle
    \param[out] v: calculation results of V-phase duty cycle
    \param[out] w: calculation results of W-phase duty cycle
*/
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w) {
    float alpha, beta;

    /* fast calculation of cosine and sine value of electric angle */
    float cf = fast_cos(elect_angle);
    float sf = fast_sin(elect_angle);

#if USE_SVPWM == 0
    /* firstly, the inverse Park transform is calculated */
    alpha = d * cf - q * sf;
    beta = q * cf + d * sf;

    /* secondly, the inverse Clarke transform is calculated */
    *u = 0.5f - alpha / VBUS;
    *v = 0.5f + (alpha * 0.5f - beta * 0.866025404f) / VBUS;
    *w = 1.5f - *u - *v;
#else
    float tmp2, tmp3, Ta, Tb, Tc;
    char vec_sector = 3;

    /* firstly, the inverse Clarke transform is calculated */
    alpha = d * cf - q * sf;
    beta = q * cf + d * sf;
    tmp2 = beta * 0.5f + alpha * 0.8660254f;
    tmp3 = tmp2 - beta;

    /* judge which sector the magnetic vector is in at this time */
    vec_sector = ((*(unsigned int *) &tmp2) >> 31) ? vec_sector : (vec_sector - 1);
    vec_sector = ((*(unsigned int *) &tmp3) >> 31) ? vec_sector : (vec_sector - 1);
    vec_sector = ((*(unsigned int *) &beta) >> 31) ? (7 - vec_sector) : vec_sector;

    /* the proportion of each phase is calculated by six sector modulation method */
    switch (vec_sector) {
        case 1:
        case 4: Ta = tmp2;
            Tb = beta - tmp3;
            Tc = -tmp2;
            break;
        case 2:
        case 5:Ta = tmp3 + tmp2;
            Tb = beta;
            Tc = -beta;
            break;
        default:Ta = tmp3;
            Tb = -tmp3;
            Tc = -(beta + tmp2);
            break;
    }

    /* calculate the duty cycle in center alignment mode */
    *u = (Ta / VBUS) * 0.5f + 0.5f;
    *v = (Tb / VBUS) * 0.5f + 0.5f;
    *w = (Tc / VBUS) * 0.5f + 0.5f;
#endif
}
