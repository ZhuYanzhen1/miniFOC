//
// Created by Lao·Zhu on 2021/8/30.
//

#include "foc.h"
#include "config.h"
#include "fast_math.h"
#include "encoder.h"
#include "system.h"
#include "timer.h"

volatile FOC_Structure_t FOC_Struct;
volatile unsigned char phase_sequence = 0;

/*!
    \brief      automatic phase sequence detection and correction
    \param[in]  none
    \param[out] none
    \retval     none
*/
void foc_calibrate_phase(void) {
    unsigned short last_angle = 0, positive_counter = 0;
    float u, v, w, angle = 0;
    /* set that there is only a magnetic field on the straight axis */
    foc_calculate_dutycycle(0, 0.5f, 0, &u, &v, &w);
    /* Apply to PWM */
    update_pwm_dutycycle(u, v, w);
    /* delay to wait for the motor to respond */
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
        foc_calculate_dutycycle(angle, 0.5f, 0, &u, &v, &w);
        angle += 0.2f;
        /* Apply to PWM */
        update_pwm_dutycycle(u, v, w);
        /* delay to wait for the motor to respond */
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
        foc_calculate_dutycycle(angle, 0.5f, 0, &u, &v, &w);
        angle -= 0.2f;
        /* Apply to PWM */
        update_pwm_dutycycle(u, v, w);
        /* delay to wait for the motor to respond */
        delayms(20);
    }
    foc_calculate_dutycycle(0, 0, 0, &u, &v, &w);
    /* Apply to PWM */
    update_pwm_dutycycle(u, v, w);
    /* delay to wait for the motor to respond */
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
    \retval     none
*/
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w) {
    /* fast calculation of cosine and sine value of electric angle */
    float cf = fast_cos(elect_angle);
    float sf = fast_sin(elect_angle);
    float tmp2, tmp3, Ta, Tb, Tc, Alpha, Beta;
    char VecSector = 3;
    /* firstly, the inverse Clarke transform is calculated */
    Alpha = d * cf - q * sf;
    Beta = q * cf + d * sf;
    tmp2 = Beta * 0.5f + Alpha * 0.8660254f;
    tmp3 = tmp2 - Beta;
    /* judge which sector the magnetic vector is in at this time */
    VecSector = ((*(unsigned int *) &tmp2) >> 31) ? VecSector : (VecSector - 1);
    VecSector = ((*(unsigned int *) &tmp3) >> 31) ? VecSector : (VecSector - 1);
    VecSector = ((*(unsigned int *) &Beta) >> 31) ? (7 - VecSector) : VecSector;
    /* the proportion of each phase is calculated by six sector modulation method */
    if (VecSector == 1 || VecSector == 4) {
        Ta = tmp2;
        Tb = Beta - tmp3;
        Tc = -tmp2;
    } else if (VecSector == 2 || VecSector == 5) {
        Ta = tmp3 + tmp2;
        Tb = Beta;
        Tc = -Beta;
    } else {
        Ta = tmp3;
        Tb = -tmp3;
        Tc = -(Beta + tmp2);
    }
    /* calculate the duty cycle in center alignment mode */
    *u = (Ta / VBUS) * 0.5f + 0.5f;
    *v = (Tb / VBUS) * 0.5f + 0.5f;
    *w = (Tc / VBUS) * 0.5f + 0.5f;
}
