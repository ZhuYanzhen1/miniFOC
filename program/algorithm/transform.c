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
void foc_calculate_dutycycle(int32_t elect_angle, int32_t d, int32_t q, int32_t* u, int32_t* v, int32_t* w) {
    int32_t alpha, beta;
    int32_t tmp2, tmp3, Ta, Tb, Tc;
    int32_t vec_sector = 3;

    /* fast calculation of cosine and sine value of electric angle */
    int32_t cf = IQcos(elect_angle);
    int32_t sf = IQsin(elect_angle);

    /* firstly, the inverse Clarke transform is calculated */
    alpha = IQmul(d, cf) - IQmul(q, sf);
    beta = IQmul(q, cf) + IQmul(d, sf);
    tmp2 = (beta >> 1) + IQmul(alpha, IQ(0.8660254));
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
    *u = (IQdiv(Ta, IQ(12.0)) >> 1) + IQ(0.5);
    *v = (IQdiv(Tb, IQ(12.0)) >> 1) + IQ(0.5);
    *w = (IQdiv(Tc, IQ(12.0)) >> 1) + IQ(0.5);
}
