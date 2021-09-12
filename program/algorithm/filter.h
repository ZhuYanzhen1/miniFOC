//
// Created by Lao·Zhu on 2021/9/5.
//

#ifndef MINIFOC_ALGORITHM_FILTER_H_
#define MINIFOC_ALGORITHM_FILTER_H_

typedef struct {
    unsigned short pointer;
    short buffer[3];
    float current_result;
    float coefficient;
} Filter_Structure_t;

extern volatile Filter_Structure_t velocity_filter;
float filter_update_value(Filter_Structure_t *param, short value);
void filter_config(void);

#endif //MINIFOC_ALGORITHM_FILTER_H_
