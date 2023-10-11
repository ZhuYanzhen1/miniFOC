//
// Created by LaoZhu on 2023/10/11.
//

#ifndef MINIFOC_ALGORITHM_FAST_MATH_H_
#define MINIFOC_ALGORITHM_FAST_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 设定IQMATH库默认精度(Q精度)，范围： 10 <= GLOBAL_Q <= 28 */
#ifndef GLOBAL_Q
#define GLOBAL_Q 24
#endif

#define FAST_IQDIV 0

#include "limits.h"
#include "stdint.h"

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

/*******************************************************************************
* Function Name  : IQ
* Description    : 将浮点数转换成IQ格式数
* Input          : float类型数值
* Return         : 返回转换后的IQ格式数，与GLOBAL_Q指定的IQ格式相同
*******************************************************************************/
#define IQ(A) ((int32_t)((A) * (1 << GLOBAL_Q)))

/*******************************************************************************
* Function Name  : IQtoF
* Description    : 将IQ格式的数转换成单精度浮点数
* Input          : IQ类型数据
* Return         : 转换后的float类型的数据
*******************************************************************************/
#define IQtoF(A) ((float)A / (float)(1 << GLOBAL_Q))

/*******************************************************************************
* Function Name  : IQtoD
* Description    : 将IQ格式的数转换成双精度浮点数
* Input          : IQ类型数据
* Return         : 转换后的double类型的数据
*******************************************************************************/
#define IQtoD(A) ((double)A / (double)(1 << GLOBAL_Q))

#define IQsat(A, Pos, Neg) (((A) > (Pos)) ? (Pos) : (((A) < (Neg)) ? (Neg) : (A)))

/*******************************************************************************
* Function Name  : IQabs
* Description    : IQ格式数的绝对值函数:|A|
* Input          : 参数A为IQ格式的数
* Return         : 返回A的绝对值，与参数的IQ格式相同
*******************************************************************************/
#define IQabs(A) (((A) < 0) ? -(A) : (A))

/* GLOBAL_Q指定的IQ精度的数与指定IQ精度数之间相互转换函数 */
#define IQtoIQ30(A) ((int32_t)(A) << (30 - GLOBAL_Q))
#define IQ30toIQ(A) ((int32_t)(A) >> (30 - GLOBAL_Q))

#if (GLOBAL_Q >= 29)
#define IQtoIQ29(A) ((int32_t)(A) >> (GLOBAL_Q - 29))
#define IQ29toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 29))
#else
#define IQtoIQ29(A) ((int32_t)(A) << (29 - GLOBAL_Q))
#define IQ29toIQ(A) ((int32_t)(A) >> (29 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 28)
#define IQtoIQ28(A) ((int32_t)(A) >> (GLOBAL_Q - 28))
#define IQ28toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 28))
#else
#define IQtoIQ28(A) ((int32_t)(A) << (28 - GLOBAL_Q))
#define IQ28toIQ(A) ((int32_t)(A) >> (28 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 27)
#define IQtoIQ27(A) ((int32_t)(A) >> (GLOBAL_Q - 27))
#define IQ27toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 27))
#else
#define IQtoIQ27(A) ((int32_t)(A) << (27 - GLOBAL_Q))
#define IQ27toIQ(A) ((int32_t)(A) >> (27 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 26)
#define IQtoIQ26(A) ((int32_t)(A) >> (GLOBAL_Q - 26))
#define IQ26toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 26))
#else
#define IQtoIQ26(A) ((int32_t)(A) << (26 - GLOBAL_Q))
#define IQ26toIQ(A) ((int32_t)(A) >> (26 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 25)
#define IQtoIQ25(A) ((int32_t)(A) >> (GLOBAL_Q - 25))
#define IQ25toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 25))
#else
#define IQtoIQ25(A) ((int32_t)(A) << (25 - GLOBAL_Q))
#define IQ25toIQ(A) ((int32_t)(A) >> (25 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 24)
#define IQtoIQ24(A) ((int32_t)(A) >> (GLOBAL_Q - 24))
#define IQ24toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 24))
#else
#define IQtoIQ24(A) ((int32_t)(A) << (24 - GLOBAL_Q))
#define IQ24toIQ(A) ((int32_t)(A) >> (24 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 23)
#define IQtoIQ23(A) ((int32_t)(A) >> (GLOBAL_Q - 23))
#define IQ23toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 23))
#else
#define IQtoIQ23(A) ((int32_t)(A) << (23 - GLOBAL_Q))
#define IQ23toIQ(A) ((int32_t)(A) >> (23 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 22)
#define IQtoIQ22(A) ((int32_t)(A) >> (GLOBAL_Q - 22))
#define IQ22toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 22))
#else
#define IQtoIQ22(A) ((int32_t)(A) << (22 - GLOBAL_Q))
#define IQ22toIQ(A) ((int32_t)(A) >> (22 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 21)
#define IQtoIQ21(A) ((int32_t)(A) >> (GLOBAL_Q - 21))
#define IQ21toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 21))
#else
#define IQtoIQ21(A) ((int32_t)(A) << (21 - GLOBAL_Q))
#define IQ21toIQ(A) ((int32_t)(A) >> (21 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 20)
#define IQtoIQ20(A) ((int32_t)(A) >> (GLOBAL_Q - 20))
#define IQ20toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 20))
#else
#define IQtoIQ20(A) ((int32_t)(A) << (20 - GLOBAL_Q))
#define IQ20toIQ(A) ((int32_t)(A) >> (20 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 19)
#define IQtoIQ19(A) ((int32_t)(A) >> (GLOBAL_Q - 19))
#define IQ19toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 19))
#else
#define IQtoIQ19(A) ((int32_t)(A) << (19 - GLOBAL_Q))
#define IQ19toIQ(A) ((int32_t)(A) >> (19 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 18)
#define IQtoIQ18(A) ((int32_t)(A) >> (GLOBAL_Q - 18))
#define IQ18toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 18))
#else
#define IQtoIQ18(A) ((int32_t)(A) << (18 - GLOBAL_Q))
#define IQ18toIQ(A) ((int32_t)(A) >> (18 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 17)
#define IQtoIQ17(A) ((int32_t)(A) >> (GLOBAL_Q - 17))
#define IQ17toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 17))
#else
#define IQtoIQ17(A) ((int32_t)(A) << (17 - GLOBAL_Q))
#define IQ17toIQ(A) ((int32_t)(A) >> (17 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 16)
#define IQtoIQ16(A) ((int32_t)(A) >> (GLOBAL_Q - 16))
#define IQ16toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 16))
#else
#define IQtoIQ16(A) ((int32_t)(A) << (16 - GLOBAL_Q))
#define IQ16toIQ(A) ((int32_t)(A) >> (16 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 15)
#define IQtoIQ15(A) ((int32_t)(A) >> (GLOBAL_Q - 15))
#define IQ15toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 15))
#else
#define IQtoIQ15(A) ((int32_t)(A) << (15 - GLOBAL_Q))
#define IQ15toIQ(A) ((int32_t)(A) >> (15 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 14)
#define IQtoIQ14(A) ((int32_t)(A) >> (GLOBAL_Q - 14))
#define IQ14toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 14))
#else
#define IQtoIQ14(A) ((int32_t)(A) << (14 - GLOBAL_Q))
#define IQ14toIQ(A) ((int32_t)(A) >> (14 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 13)
#define IQtoIQ13(A) ((int32_t)(A) >> (GLOBAL_Q - 13))
#define IQ13toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 13))
#else
#define IQtoIQ13(A) ((int32_t)(A) << (13 - GLOBAL_Q))
#define IQ13toIQ(A) ((int32_t)(A) >> (13 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 12)
#define IQtoIQ12(A) ((int32_t)(A) >> (GLOBAL_Q - 12))
#define IQ12toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 12))
#else
#define IQtoIQ12(A) ((int32_t)(A) << (12 - GLOBAL_Q))
#define IQ12toIQ(A) ((int32_t)(A) >> (12 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 11)
#define IQtoIQ11(A) ((int32_t)(A) >> (GLOBAL_Q - 11))
#define IQ11toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 11))
#else
#define IQtoIQ11(A) ((int32_t)(A) << (11 - GLOBAL_Q))
#define IQ11toIQ(A) ((int32_t)(A) >> (11 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 10)
#define IQtoIQ10(A) ((int32_t)(A) >> (GLOBAL_Q - 10))
#define IQ10toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 10))
#else
#define IQtoIQ10(A) ((int32_t)(A) << (10 - GLOBAL_Q))
#define IQ10toIQ(A) ((int32_t)(A) >> (10 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 9)
#define IQtoIQ9(A) ((int32_t)(A) >> (GLOBAL_Q - 9))
#define IQ9toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 9))
#else
#define IQtoIQ9(A) ((int32_t)(A) << (9 - GLOBAL_Q))
#define IQ9toIQ(A) ((int32_t)(A) >> (9 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 8)
#define IQtoIQ8(A) ((int32_t)(A) >> (GLOBAL_Q - 8))
#define IQ8toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 8))
#else
#define IQtoIQ8(A) ((int32_t)(A) << (8 - GLOBAL_Q))
#define IQ8toIQ(A) ((int32_t)(A) >> (8 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 7)
#define IQtoIQ7(A) ((int32_t)(A) >> (GLOBAL_Q - 7))
#define IQ7toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 7))
#else
#define IQtoIQ7(A) ((int32_t)(A) << (7 - GLOBAL_Q))
#define IQ7toIQ(A) ((int32_t)(A) >> (7 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 6)
#define IQtoIQ6(A) ((int32_t)(A) >> (GLOBAL_Q - 6))
#define IQ6toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 6))
#else
#define IQtoIQ6(A) ((int32_t)(A) << (6 - GLOBAL_Q))
#define IQ6toIQ(A) ((int32_t)(A) >> (6 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 5)
#define IQtoIQ5(A) ((int32_t)(A) >> (GLOBAL_Q - 5))
#define IQ5toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 5))
#else
#define IQtoIQ5(A) ((int32_t)(A) << (5 - GLOBAL_Q))
#define IQ5toIQ(A) ((int32_t)(A) >> (5 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 4)
#define IQtoIQ4(A) ((int32_t)(A) >> (GLOBAL_Q - 4))
#define IQ4toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 4))
#else
#define IQtoIQ4(A) ((int32_t)(A) << (4 - GLOBAL_Q))
#define IQ4toIQ(A) ((int32_t)(A) >> (4 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 3)
#define IQtoIQ3(A) ((int32_t)(A) >> (GLOBAL_Q - 3))
#define IQ3toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 3))
#else
#define IQtoIQ3(A) ((int32_t)(A) << (3 - GLOBAL_Q))
#define IQ3toIQ(A) ((int32_t)(A) >> (3 - GLOBAL_Q))
#endif

#if (GLOBAL_Q >= 2)
#define IQtoIQ2(A) ((int32_t)(A) >> (GLOBAL_Q - 2))
#define IQ2toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 2))
#else
#define IQtoIQ2(A) ((int32_t)(A) << (2 - GLOBAL_Q))
#define IQ2toIQ(A) ((int32_t)(A) >> (2 - GLOBAL_Q))
#endif

#define IQtoIQ1(A) ((int32_t)(A) >> (GLOBAL_Q - 1))
#define IQ1toIQ(A) ((int32_t)(A) << (GLOBAL_Q - 1))

#define IQmul(A, B) ((int32_t)(((int64_t)A * (int64_t)B) >> GLOBAL_Q))
/*******************************************************************************
* Function Name  : IQdiv
* Description    : IQ格式数的除法运算:A/B
* Input          : A为被除数，B为除数，A与B为相同IQ格式的数
* Return         : A除以B的商，与参数的IQ格式相同
*******************************************************************************/
#if FAST_IQDIV == 1
#if GLOBAL_Q == 30
#define IQdiv(A, B) IQ30div(A, B)
#endif
#if GLOBAL_Q == 29
#define IQdiv(A, B) IQ29div(A, B)
#endif
#if GLOBAL_Q == 28
#define IQdiv(A, B) IQ28div(A, B)
#endif
#if GLOBAL_Q == 27
#define IQdiv(A, B) IQ27div(A, B)
#endif
#if GLOBAL_Q == 26
#define IQdiv(A, B) IQ26div(A, B)
#endif
#if GLOBAL_Q == 25
#define IQdiv(A, B) IQ25div(A, B)
#endif
#if GLOBAL_Q == 24
#define IQdiv(A, B) IQ24div(A, B)
#endif
#if GLOBAL_Q == 23
#define IQdiv(A, B) IQ23div(A, B)
#endif
#if GLOBAL_Q == 22
#define IQdiv(A, B) IQ22div(A, B)
#endif
#if GLOBAL_Q == 21
#define IQdiv(A, B) IQ21div(A, B)
#endif
#if GLOBAL_Q == 20
#define IQdiv(A, B) IQ20div(A, B)
#endif
#if GLOBAL_Q == 19
#define IQdiv(A, B) IQ19div(A, B)
#endif
#if GLOBAL_Q == 18
#define IQdiv(A, B) IQ18div(A, B)
#endif
#if GLOBAL_Q == 17
#define IQdiv(A, B) IQ17div(A, B)
#endif
#if GLOBAL_Q == 16
#define IQdiv(A, B) IQ16div(A, B)
#endif
#if GLOBAL_Q == 15
#define IQdiv(A, B) IQ15div(A, B)
#endif
#if GLOBAL_Q == 14
#define IQdiv(A, B) IQ14div(A, B)
#endif
#if GLOBAL_Q == 13
#define IQdiv(A, B) IQ13div(A, B)
#endif
#if GLOBAL_Q == 12
#define IQdiv(A, B) IQ12div(A, B)
#endif
#if GLOBAL_Q == 11
#define IQdiv(A, B) IQ11div(A, B)
#endif
#if GLOBAL_Q == 10
#define IQdiv(A, B) IQ10div(A, B)
#endif
#if GLOBAL_Q == 9
#define IQdiv(A, B) IQ9div(A, B)
#endif
#if GLOBAL_Q == 8
#define IQdiv(A, B) IQ8div(A, B)
#endif
#if GLOBAL_Q == 7
#define IQdiv(A, B) IQ7div(A, B)
#endif
#if GLOBAL_Q == 6
#define IQdiv(A, B) IQ6div(A, B)
#endif
#if GLOBAL_Q == 5
#define IQdiv(A, B) IQ5div(A, B)
#endif
#if GLOBAL_Q == 4
#define IQdiv(A, B) IQ4div(A, B)
#endif
#if GLOBAL_Q == 3
#define IQdiv(A, B) IQ3div(A, B)
#endif
#if GLOBAL_Q == 2
#define IQdiv(A, B) IQ2div(A, B)
#endif
#if GLOBAL_Q == 1
#define IQdiv(A, B) IQ1div(A, B)
#endif
#else
#define IQdiv(A, B) ((int32_t)((int64_t)A << GLOBAL_Q / (int64_t)B))
#endif

/*******************************************************************************
* Function Name  : IQsin
* Description    : IQ格式数的正弦函数:sin(A)
* Input          : 输入参数为IQ格式的弧度值
* Return         : 返回A的正弦值，与参数的IQ格式相同
*******************************************************************************/
extern int32_t IQsin(int32_t angle);

#define IQ_SIN_TABLE_POINT 256
#define IQ_SIN_TABLE_STEP IQ(M_PI_2 / IQ_SIN_TABLE_POINT)

#if GLOBAL_Q == 28
#define IQ_SIN_TABLE iq28_sin_table
#endif
#if GLOBAL_Q == 27
#define IQ_SIN_TABLE iq27_sin_table
#endif
#if GLOBAL_Q == 26
#define IQ_SIN_TABLE iq26_sin_table
#endif
#if GLOBAL_Q == 25
#define IQ_SIN_TABLE iq25_sin_table
#endif
#if GLOBAL_Q == 24
#define IQ_SIN_TABLE iq24_sin_table
#endif
#if GLOBAL_Q == 23
#define IQ_SIN_TABLE iq23_sin_table
#endif
#if GLOBAL_Q == 22
#define IQ_SIN_TABLE iq22_sin_table
#endif
#if GLOBAL_Q == 21
#define IQ_SIN_TABLE iq21_sin_table
#endif
#if GLOBAL_Q == 20
#define IQ_SIN_TABLE iq20_sin_table
#endif
#if GLOBAL_Q == 19
#define IQ_SIN_TABLE iq19_sin_table
#endif
#if GLOBAL_Q == 18
#define IQ_SIN_TABLE iq18_sin_table
#endif
#if GLOBAL_Q == 17
#define IQ_SIN_TABLE iq17_sin_table
#endif
#if GLOBAL_Q == 16
#define IQ_SIN_TABLE iq16_sin_table
#endif
#if GLOBAL_Q == 15
#define IQ_SIN_TABLE iq15_sin_table
#endif
#if GLOBAL_Q == 14
#define IQ_SIN_TABLE iq14_sin_table
#endif
#if GLOBAL_Q == 13
#define IQ_SIN_TABLE iq13_sin_table
#endif
#if GLOBAL_Q == 12
#define IQ_SIN_TABLE iq12_sin_table
#endif
#if GLOBAL_Q == 11
#define IQ_SIN_TABLE iq11_sin_table
#endif
#if GLOBAL_Q == 10
#define IQ_SIN_TABLE iq10_sin_table
#endif

#define IQcos(A) IQsin(IQ(1.5707963f) - A)

#ifdef __cplusplus
}
#endif

#endif  //MINIFOC_SYSTEM_IQMATH_H_
