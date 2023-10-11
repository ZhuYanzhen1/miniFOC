//
// Created by LaoZhu on 2023/10/11.
//

#include "transform.h"
#include "fast_math.h"

/*!
    \brief      calculate the corresponding three-phase PWM duty cycle under the current electrical angle
    \param[in]  elect_angle: electrical angle of motor rotor, in radian system
    \param[in]  d: expected field strength in the direct axis direction of the motor
    \param[in]  q: expected field strength in the quadrature axis direction of the motor
    \param[out] u: calculation results of U-phase duty cycle
    \param[out] v: calculation results of V-phase duty cycle
    \param[out] w: calculation results of W-phase duty cycle
*/
void foc_calculate_dutycycle(float elect_angle, float d, float q, float* u, float* v, float* w) {
    float alpha, beta;

    /* fast calculation of cosine and sine value of electric angle */
    float cf = fast_cos(elect_angle);
    float sf = fast_sin(elect_angle);

    float tmp2, tmp3, Ta, Tb, Tc;
    unsigned int vec_sector = 3;

    /* firstly, the inverse Clarke transform is calculated */
    alpha = d * cf - q * sf;
    beta = q * cf + d * sf;
    tmp2 = beta * 0.5f + alpha * 0.8660254f;
    tmp3 = tmp2 - beta;

    /* judge which sector the magnetic vector is in at this time */
    vec_sector = tmp2 < 0 ? vec_sector : (vec_sector - 1);
    vec_sector = tmp3 < 0 ? vec_sector : (vec_sector - 1);
    vec_sector = beta < 0 ? (7 - vec_sector) : vec_sector;

    /* the proportion of each phase is calculated by six sector modulation method */
    switch (vec_sector) {
        case 1:
        case 4:
            Ta = tmp2;
            Tb = beta - tmp3;
            Tc = -tmp2;
            break;
        case 2:
        case 5:
            Ta = tmp3 + tmp2;
            Tb = beta;
            Tc = -beta;
            break;
        default:
            Ta = tmp3;
            Tb = -tmp3;
            Tc = -(beta + tmp2);
            break;
    }

    /* calculate the duty cycle in center alignment mode */
    *u = (Ta / 12.0f) * 0.5f + 0.5f;
    *v = (Tb / 12.0f) * 0.5f + 0.5f;
    *w = (Tc / 12.0f) * 0.5f + 0.5f;
}