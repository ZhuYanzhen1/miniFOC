//
// Created by Lao·Zhu on 2021/9/5.
//

#include "filter.h"
#include "system.h"
#include "foc.h"
#include "config.h"

volatile Filter_Structure_t velocity_filter;

void filter_coefficient_config(Filter_Structure_t *param, float coefficient) {
    user_memset(param, 0x00, sizeof(Filter_Structure_t));
    param->coefficient = coefficient;
}

void filter_config(void) {
    filter_coefficient_config((Filter_Structure_t *) &velocity_filter, SPEED_COEFFICIENT);
}

float filter_update_value(Filter_Structure_t *param, unsigned short value) {
    unsigned long value_summary = 0;
    param->buffer[param->pointer] = value;
    param->pointer++;
    if (param->pointer == 3)
        param->pointer = 0;
    for (unsigned char counter = 0; counter < 3; ++counter)
        value_summary += param->buffer[counter];
    value_summary = value_summary / 3;
    if (value_summary < 10000)
        param->current_result = (float) value_summary * param->coefficient;
    return param->current_result;
}
