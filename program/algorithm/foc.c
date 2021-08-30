//
// Created by Lao·Zhu on 2021/8/30.
//

#include "foc.h"
#include "config.h"
#include "math.h"

void Update_Dq2Phase(float elect_angle, float d, float q, float *u, float *v, float *w) {
    float cf = cosf(elect_angle);
    float sf = sinf(elect_angle);
    float tmp2, tmp3, Ta, Tb, Tc, Alpha, Beta;
    int VecSector = 3;
    Alpha = d * cf - q * sf;
    Beta = q * cf + d * sf;
    tmp2 = Beta * 0.5f + Alpha * 0.8660254f;
    tmp3 = tmp2 - Beta;
    VecSector = ((*(unsigned int *) &tmp2) >> 31) ? VecSector : (VecSector - 1);
    VecSector = ((*(unsigned int *) &tmp3) >> 31) ? VecSector : (VecSector - 1);
    VecSector = ((*(unsigned int *) &Beta) >> 31) ? (7 - VecSector) : VecSector;
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
    *u = (Ta / VBUS) * 0.5f + 0.5f;
    *v = (Tb / VBUS) * 0.5f + 0.5f;
    *w = (Tc / VBUS) * 0.5f + 0.5f;
}
