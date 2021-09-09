//
// Created by Lao·Zhu on 2021/9/2.
//

#ifndef MINIFOC_ALGORITHM_ENCODER_H_
#define MINIFOC_ALGORITHM_ENCODER_H_

extern volatile unsigned short machine_angle_offset;
void encoder_zeroing(void);
unsigned short encoder_get_mechanical_angle(void);
float encoder_get_electronic_angle(void);
void encoder_update_speed(void);

#endif //MINIFOC_ALGORITHM_ENCODER_H_
