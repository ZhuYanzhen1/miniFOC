//
// Created by LaoZhu on 2023/10/11.
//

#include "fast_math.h"
#include "math_lut.h"

int32_t IQsin(int32_t angle) {
    while (angle < 0)
        angle += IQ(2.0 * M_PI);
    while (angle >= IQ(2.0 * M_PI))
        angle -= IQ(2.0 * M_PI);
    int32_t index = (angle / IQ_SIN_TABLE_STEP) % IQ_SIN_TABLE_POINT;
    int32_t quadrant = (angle / IQ_SIN_TABLE_STEP) / IQ_SIN_TABLE_POINT;
    index = (quadrant == 1 || quadrant == 3) ? IQ_SIN_TABLE_POINT - index : index;
    int32_t result = (IQ_SIN_TABLE[index] + IQ_SIN_TABLE[index + 1]) >> 1;
    return (quadrant == 2 || quadrant == 3) ? -1 * result : result;
}
