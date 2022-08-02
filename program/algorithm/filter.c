/**************************************************************************//**
  \file     filter.c
  \brief    this file contains the code implementation of first-order digital
            RC low-pass filter algorithm and the code implementation of low-pass
            filter coefficient calculation.
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "filter.h"
#include "system.h"
#include "foc.h"
#include "config.h"

/*!
    \brief motor rotation speed low pass filter handle
*/
volatile Filter_Structure_t velocity_filter;

/*!
    \brief     configure low-pass filter parameters
    \param[in] param: first order low pass filter parameter handler
    \param[in] cutoff_freq: cut off frequency in Hz
    \param[in] sample_freq: sample frequency in Hz
    \param[in] coefficient: input data weight, usually is 1
*/
void filter_coefficient_config(Filter_Structure_t *param, float cutoff_freq, float sample_freq, float coefficient) {
    /* clear the value of the first order low pass filter parameter handler */
    user_memset(param, 0x00, sizeof(Filter_Structure_t));

    /* the RC time constant is calculated from the cut-off frequency */
    float time_const = 1.0f / (6.2831852f * cutoff_freq);

    /* calculation of digital low-pass filter coefficients */
    param->coefficient1 = (1.0f / (1.0f + time_const * sample_freq)) * coefficient;
    param->coefficient2 = (time_const * sample_freq) / (1.0f + time_const * sample_freq);
    param->current_result = 0;
    param->last_result = 0;
}

/*!
    \brief configure low-pass filter parameters
*/
void filter_config(void) {
    filter_coefficient_config((Filter_Structure_t *) &velocity_filter,
                              TIM13_FREQUENCY, SPEED_UP_FREQ, SPEED_COEFFICIENT);
}

/*!
    \brief     update the output value of the first-order low-pass filter
    \param[in] param: first order low pass filter parameter handler
    \param[in] value: the sampled value to be filtered at this moment
    \retval    current calculation results of low-pass filter
*/
float filter_update_value(Filter_Structure_t *param, short value) {
    /* judge whether the input parameters are abnormal,
     * calculate the output value of the first-order low-pass filter */
    if (value < 200 && value > -200)
        param->current_result = param->coefficient1 * (float) value + param->coefficient2 * param->last_result;

    /* update the output value of the previous time */
    param->last_result = param->current_result;
    return param->current_result;
}
