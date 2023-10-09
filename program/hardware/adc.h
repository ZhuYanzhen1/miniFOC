//
// Created by LaoZhu on 2023/10/6.
//

#ifndef MINIFOC_HARDWARE_ADC_H_
#define MINIFOC_HARDWARE_ADC_H_

typedef struct {
    unsigned short ch1_offset;
    unsigned short ch3_offset;
} adc_sample_t;

void adc_config(void);
void adc_read_offset(adc_sample_t* adc_sample);

#endif  //MINIFOC_HARDWARE_ADC_H_
