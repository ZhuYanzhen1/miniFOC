//
// Created by LaoZhu on 2023/10/6.
//

#ifndef MINIFOC_HARDWARE_ADC_H_
#define MINIFOC_HARDWARE_ADC_H_

#include "stdint.h"

typedef struct {
    uint16_t ch1_offset;
    uint16_t ch3_offset;
    int32_t phase1_current;
    int32_t phase2_current;
    int32_t phase3_current;
} adc_sample_t;

void adc_start(void);
void adc_stop(void);
void adc_config(void);
void adc_read_offset(adc_sample_t* adc_sample);
void read_adc_current(adc_sample_t* adc_sample);

#endif  //MINIFOC_HARDWARE_ADC_H_
