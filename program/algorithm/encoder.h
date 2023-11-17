//
// Created by LaoZhu on 2023/11/10.
//

#ifndef MINIFOC_ALGORITHM_ENCODER_H_
#define MINIFOC_ALGORITHM_ENCODER_H_

#include <stdint.h>

void encoder_zeroing(void);
void update_encoder_angle(uint16_t current_encoder_angle);

#endif  //MINIFOC_ALGORITHM_ENCODER_H_
