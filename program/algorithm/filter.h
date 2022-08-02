/**************************************************************************//**
  \file     filter.h
  \brief    this is the header file of filter.c, which defines the structure of filter algorithm.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     9. October 2021
 ******************************************************************************/

#ifndef MINIFOC_ALGORITHM_FILTER_H_
#define MINIFOC_ALGORITHM_FILTER_H_

/*!
  \struct Filter_Structure_t
  \brief  structure of low-pass filter algorithm
 */
typedef struct {
    float coefficient1;     ///< low-pass filter coefficient 1
    float coefficient2;     ///< low-pass filter coefficient 2
    float last_result;      ///< previous calculation results of low-pass filter
    float current_result;   ///< current calculation results of low-pass filter
} Filter_Structure_t;

extern volatile Filter_Structure_t velocity_filter;
float filter_update_value(Filter_Structure_t *param, short value);
void filter_config(void);

#endif //MINIFOC_ALGORITHM_FILTER_H_
