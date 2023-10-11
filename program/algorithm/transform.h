//
// Created by LaoZhu on 2023/10/11.
//

#ifndef MINIFOC_ALGORITHM_TRANSFORM_H_
#define MINIFOC_ALGORITHM_TRANSFORM_H_

#include "stdint.h"

void foc_calculate_dutycycle(int32_t elect_angle, int32_t d, int32_t q, int32_t* u, int32_t* v, int32_t* w);

#endif  //MINIFOC_ALGORITHM_TRANSFORM_H_
