//
// Created by Lao·Zhu on 2021/8/30.
//

#ifndef MINIFOC_ALGORITHM_FOC_H_
#define MINIFOC_ALGORITHM_FOC_H_

typedef struct {
    float mechanical_angle;
    float rotate_speed;
    float user_expect;
} FOC_Structure_t;

#define MECHANGLE_COEFFICIENT   (6.2831854f / ENCODER_RESO)
#define ELECANGLE_COEFFICIENT   ((6.2831854f * POLAR_PAIRS) / ENCODER_RESO)
#define SPEED_COEFFICIENT       ((6.2831852f * TIM13_FREQUENCY) / ENCODER_RESO)

extern volatile unsigned char phase_sequence;
extern volatile FOC_Structure_t FOC_Struct;
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w);
void foc_calibrate_phase(void);

#endif //MINIFOC_ALGORITHM_FOC_H_
