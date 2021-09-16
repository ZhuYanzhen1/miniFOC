//
// Created by Lao·Zhu on 2021/9/5.
//

#ifndef MINIFOC_ALGORITHM_FILTER_H_
#define MINIFOC_ALGORITHM_FILTER_H_

typedef struct {
    float coefficient1;
    float coefficient2;
    float last_result;
    float current_result;
} Filter_Structure_t;

extern volatile Filter_Structure_t velocity_filter;
float filter_update_value(Filter_Structure_t *param, short value);
void filter_config(void);

#endif //MINIFOC_ALGORITHM_FILTER_H_
