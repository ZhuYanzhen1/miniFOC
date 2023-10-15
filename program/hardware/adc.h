//
// Created by LaoZhu on 2023/10/6.
//

#ifndef MINIFOC_HARDWARE_ADC_H_
#define MINIFOC_HARDWARE_ADC_H_

#include "stdint.h"

typedef struct {
    int16_t adc1_offset;
    int16_t adc2_offset;
    uint16_t ch1_offset;
    uint16_t ch3_offset;
    int32_t phase1_current;
    int32_t phase2_current;
    int32_t phase3_current;
} adc_sample_t;

void adc_start(void);
void adc_stop(void);
void adc_config(adc_sample_t* adc_sample);
void adc_read_offset(adc_sample_t* adc_sample);
void read_adc_current(adc_sample_t* adc_sample);
int16_t get_adc_calibrate(int16_t adc_offset, int16_t data);

#endif  //MINIFOC_HARDWARE_ADC_H_
