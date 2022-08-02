/**************************************************************************//**
  \file     fast_math.h
  \brief    this is the header file of fast_math.c, the macros of fast amplitude
            limiting algorithm and cosine function evaluation algorithm are defined.
  \author   Lao·Zhu
  \version  V1.0.1
  \date     10. October 2021
 ******************************************************************************/

#ifndef MINIFOC_ALGORITHM_FAST_MATH_H_
#define MINIFOC_ALGORITHM_FAST_MATH_H_

/*!
    \brief     fast clipping algorithm
    \param[in] x: number of to be clipped
    \param[in] low: minimum number
    \param[in] high: maximum number
    \retval    input value after clipping
*/
#define fast_constrain(x, low, high)    ((x)<(low)?(low):((x) >(high)?(high):(x)))

/*!
    \brief     fast calculation of cosine
    \param[in] x: angle to be calculated
    \retval    cosine value of angle theta
*/
#define fast_cos(x)                     fast_sin(1.5707963f - x);

float fast_sin(float theta);

#endif //MINIFOC_ALGORITHM_FAST_MATH_H_
