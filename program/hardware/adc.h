//
// Created by LaoZhu on 2023/10/6.
//

#ifndef MINIFOC_HARDWARE_ADC_H_
#define MINIFOC_HARDWARE_ADC_H_

typedef struct {
    unsigned short ch1_offset;
    unsigned short ch3_offset;
    int phase1_current;
    int phase2_current;
    int phase3_current;
} adc_sample_t;

void adc_start(void);
void adc_stop(void);
void adc_config(void);
void adc_read_offset(adc_sample_t* adc_sample);
void read_adc_current(adc_sample_t* adc_sample);

#endif  //MINIFOC_HARDWARE_ADC_H_
