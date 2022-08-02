/**************************************************************************//**
  \file     foc.h
  \brief    this is the header file of foc.c, which defines the structure
            of FOC algorithm and angle conversion factor.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC_ALGORITHM_FOC_H_
#define MINIFOC_ALGORITHM_FOC_H_

/*!
  \struct FOC_Structure_t
  \brief  structure of FOC algorithm
 */
typedef struct {
    float mechanical_angle;     ///< mechanical angle read form encoder
    float rotate_speed;         ///< motor rotate speed calculate from timer
    float user_expect;          ///< user expect value of miniFOC
} FOC_Structure_t;

/*! \brief mechanical angle conversion factor */
#define MECHANGLE_COEFFICIENT   (6.2831854f / ENCODER_RESO)
/*! \brief electric angle conversion factor */
#define ELECANGLE_COEFFICIENT   ((6.2831854f * POLAR_PAIRS) / ENCODER_RESO)
/*! \brief mechanical rotate speed conversion factor */
#define SPEED_COEFFICIENT       ((6.2831852f * TIM13_FREQUENCY) / ENCODER_RESO)

extern unsigned char foc_parameter_available_flag;
extern volatile unsigned char phase_sequence;
extern volatile FOC_Structure_t FOC_Struct;
void foc_calculate_dutycycle(float elect_angle, float d, float q, float *u, float *v, float *w);
void foc_calibrate_phase(void);

#endif //MINIFOC_ALGORITHM_FOC_H_
