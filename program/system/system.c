//
// Created by Lao·Zhu on 2021/8/20.
//

#include "gd32f1x0.h"
#include "system.h"

static volatile uint32_t delayms_counter = 1;

/*!
    \brief      initialize systick timer to implementation delay function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void) {
    if (SysTick_Config(SystemCoreClock / 1000U))
        while (1);
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief      millisecond delay function, any time time.
    \param[in]    count: time to delay (in milliseconds)
    \param[out]   none
    \retval       none
*/
void delayms(uint32_t count) {
    delayms_counter = count;
    while (0U != delayms_counter);
}

/*!
    \brief      delay counter decrement function, called by systick handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void) {
    if (0U != delayms_counter)
        delayms_counter--;
}

/*!
    \brief      format buffer array to fixed value, replace memset function
    \param[in,out]  buf: array to format
    \param[in]      data: value to be formatted as
    \param[in]      num: number of elements to format
    \retval     none
*/
void user_memset(void *buf, unsigned char data, unsigned char num) {
    unsigned char *buf_p = (unsigned char *) buf;
    for (unsigned char counter = 0; counter < num; ++counter)
        buf_p[counter] = data;
}

/*!
    \brief      convert floating point numbers to int16 type data
    \param[in]  data0: floating point type data to be converted
    \param[out] none
    \retval     converted int16 type data
*/
unsigned short float_to_int16(float data0) {
    if (data0 == 0)
        return 0;
    unsigned int *pfp32 = ((unsigned int *) &data0);
    unsigned short fInt16 = ((*pfp32 >> 16) & 0x8000) |
        ((((*pfp32 >> 23) - 0x7f + 0x0f) & 0x1f) << 10) |
        ((*pfp32 >> 13) & 0x3ff);
    return fInt16;
}

/*!
    \brief      convert int16 to floating point numbers type data
    \param[in]  data0: int16 type data to be converted
    \param[out] none
    \retval     converted floating point type data
*/
float int16_to_float(unsigned short data0) {
    if (data0 == 0)
        return 0;
    unsigned int fInt32 = ((data0 & 0x8000) << 16) |
        (((((data0 >> 10) & 0x1f) - 0x0f + 0x7f) & 0xff) << 23)
        | ((data0 & 0x03FF) << 13);
    float *fp32 = (float *) &fInt32;
    return *fp32;
}
