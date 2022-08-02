/**************************************************************************//**
  \file     system.c
  \brief    system basic function source file
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "gd32f1x0.h"
#include "system.h"

/*!
    \brief millisecond delay function count variable
*/
static volatile unsigned long delayms_counter = 1;

/*!
    \brief initialize systick timer to implementation delay function
*/
void systick_config(void) {
    if (SysTick_Config(SystemCoreClock / 1000U))
        while (1);
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief     millisecond delay function, any time time.
    \param[in] count: time to delay (in milliseconds)
*/
void delayms(unsigned long count) {
    delayms_counter = count;
    while (0U != delayms_counter);
}

/*!
    \brief delay counter decrement function, called by systick handler
*/
void delay_decrement(void) {
    if (0U != delayms_counter)
        delayms_counter--;
}

/*!
    \brief         format buffer array to fixed value, replace memset function
    \param[in,out] buf: array to format
    \param[in]     data: value to be formatted as
    \param[in]     num: number of elements to format
*/
void user_memset(void *buf, unsigned char data, unsigned char num) {
    unsigned char *buf_p = (unsigned char *) buf;
    for (unsigned char counter = 0; counter < num; ++counter)
        buf_p[counter] = data;
}

/*!
    \brief     convert floating point numbers to int32 type data
    \param[in] data0: floating point type data to be converted
    \retval    converted int32 type data
*/
unsigned int float_to_int32(float data0) {
    unsigned int uintp32 = (*((unsigned int *) (&data0)));
    return uintp32;
}

/*!
    \brief     convert int32 to floating point numbers type data
    \param[in] data0: int32 type data to be converted
    \retval    converted floating point type data
*/
float int32_to_float(unsigned int data0) {
    float fp32 = (*((float *) (&data0)));
    return fp32;
}
