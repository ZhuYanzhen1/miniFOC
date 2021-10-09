/**************************************************************************//**
  \file     encoder.h
  \brief    this is the header file of encoder.c.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     10. October 2021
 ******************************************************************************/

#ifndef MINIFOC_ALGORITHM_ENCODER_H_
#define MINIFOC_ALGORITHM_ENCODER_H_

extern volatile unsigned short machine_angle_offset;
void encoder_zeroing(void);
unsigned short encoder_get_mechanical_angle(void);
float encoder_get_electronic_angle(void);
void encoder_update_speed(void);

#endif //MINIFOC_ALGORITHM_ENCODER_H_
