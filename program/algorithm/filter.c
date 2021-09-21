//
// Created by Lao·Zhu on 2021/9/5.
//

#include "filter.h"
#include "system.h"
#include "foc.h"
#include "config.h"

volatile Filter_Structure_t velocity_filter;

void filter_coefficient_config(Filter_Structure_t *param, float cutoff_freq, float sample_freq, float coefficient) {
    user_memset(param, 0x00, sizeof(Filter_Structure_t));
    float time_const = 1.0f / (6.2831852f * cutoff_freq);
    param->coefficient1 = (1.0f / (1.0f + time_const * sample_freq)) * coefficient;
    param->coefficient2 = (time_const * sample_freq) / (1.0f + time_const * sample_freq);
    param->current_result = 0;
    param->last_result = 0;
}

void filter_config(void) {
    filter_coefficient_config((Filter_Structure_t *) &velocity_filter,
                              TIM13_FREQUENCY, SPEED_UP_FREQ, SPEED_COEFFICIENT);
}

float filter_update_value(Filter_Structure_t *param, short value) {
    if (value < 200 && value > -200)
        param->current_result = param->coefficient1 * (float) value + param->coefficient2 * param->last_result;
    param->last_result = param->current_result;
    return param->current_result;
}
