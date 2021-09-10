//
// Created by Lao·Zhu on 2021/8/30.
//

#ifndef MINIFOC_ALGORITHM_FAST_MATH_H_
#define MINIFOC_ALGORITHM_FAST_MATH_H_

/*!
    \brief      fast clipping algorithm
    \param[in]  x: number of to be clipped
    \param[in]  low: minimum number
    \param[in]  high: maximum number
    \param[out] none
    \retval     cosine value of angle theta
*/
#define fast_constrain(x, low, high)    ((x)<(low)?(low):((x) >(high)?(high):(x)))

/*!
    \brief      fast calculation of cosine
    \param[in]  theta: angle to be calculated
    \param[out] none
    \retval     cosine value of angle theta
*/
#define fast_cos(x)                     fast_sin(1.5707963f - x);

float fast_sin(float theta);

#endif //MINIFOC_ALGORITHM_FAST_MATH_H_
