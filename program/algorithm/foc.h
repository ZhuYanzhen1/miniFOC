//
// Created by Lao·Zhu on 2021/8/30.
//

#ifndef MINIFOC_ALGORITHM_FOC_H_
#define MINIFOC_ALGORITHM_FOC_H_

typedef struct {
    float mechanical_angle;
    float rotate_speed;
} FOC_Structure_t;

#define MECHANGLE_COEFFICIENT   (6.2831854f / ENCODER_RESO)
#define ELECANGLE_COEFFICIENT   ((6.2831854f * POLAR_PAIRS) / ENCODER_RESO)
#define SPEED_COEFFICIENT       (3141.5926535f / ENCODER_RESO)

extern volatile FOC_Structure_t FOC_Struct;
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w);

#endif //MINIFOC_ALGORITHM_FOC_H_
