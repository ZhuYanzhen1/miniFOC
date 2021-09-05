//
// Created by Lao·Zhu on 2021/8/30.
//

#ifndef MINIFOC_ALGORITHM_FOC_H_
#define MINIFOC_ALGORITHM_FOC_H_

typedef struct {
    float mechanical_angle;
    float rotate_speed;
} FOC_Structure_t;

extern volatile FOC_Structure_t FOC_Struct;
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w);

#endif //MINIFOC_ALGORITHM_FOC_H_
