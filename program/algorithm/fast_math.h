//
// Created by LaoZhu on 2023/10/11.
//

#ifndef MINIFOC_ALGORITHM_FAST_MATH_H_
#define MINIFOC_ALGORITHM_FAST_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 设定IQMATH库默认精度(Q精度)，范围： 1 <= GLOBAL_Q <= 30 */
#ifndef GLOBAL_Q
#define GLOBAL_Q 24
#endif

#include "limits.h"
#include "stdint.h"

/* 常量宏定义 */
#define Q30 30
#define Q29 29
#define Q28 28
#define Q27 27
#define Q26 26
#define Q25 25
#define Q24 24
#define Q23 23
#define Q22 22
#define Q21 21
#define Q20 20
#define Q19 19
#define Q18 18
#define Q17 17
#define Q16 16
#define Q15 15
#define Q14 14
#define Q13 13
#define Q12 12
#define Q11 11
#define Q10 10
#define Q9 9
#define Q8 8
#define Q7 7
#define Q6 6
#define Q5 5
#define Q4 4
#define Q3 3
#define Q2 2
#define Q1 1

#define MAX_IQ_POS int32_t_MAX
#define MAX_IQ_NEG int32_t_MIN
#define MIN_IQ_POS 1
#define MIN_IQ_NEG -1

/* 将浮点数转换成各种IQ格式的数 */
#define IQ30(A) ((int32_t)((A) * (1 << 30)))
#define IQ29(A) ((int32_t)((A) * (1 << 29)))
#define IQ28(A) ((int32_t)((A) * (1 << 28)))
#define IQ27(A) ((int32_t)((A) * (1 << 27)))
#define IQ26(A) ((int32_t)((A) * (1 << 26)))
#define IQ25(A) ((int32_t)((A) * (1 << 25)))
#define IQ24(A) ((int32_t)((A) * (1 << 24)))
#define IQ23(A) ((int32_t)((A) * (1 << 23)))
#define IQ22(A) ((int32_t)((A) * (1 << 22)))
#define IQ21(A) ((int32_t)((A) * (1 << 21)))
#define IQ20(A) ((int32_t)((A) * (1 << 20)))
#define IQ19(A) ((int32_t)((A) * (1 << 19)))
#define IQ18(A) ((int32_t)((A) * (1 << 18)))
#define IQ17(A) ((int32_t)((A) * (1 << 17)))
#define IQ16(A) ((int32_t)((A) * (1 << 16)))
#define IQ15(A) ((int32_t)((A) * (1 << 15)))
#define IQ14(A) ((int32_t)((A) * (1 << 14)))
#define IQ13(A) ((int32_t)((A) * (1 << 13)))
#define IQ12(A) ((int32_t)((A) * (1 << 12)))
#define IQ11(A) ((int32_t)((A) * (1 << 11)))
#define IQ10(A) ((int32_t)((A) * (1 << 10)))
#define IQ9(A) ((int32_t)((A) * (1 << 9)))
#define IQ8(A) ((int32_t)((A) * (1 << 8)))
#define IQ7(A) ((int32_t)((A) * (1 << 7)))
#define IQ6(A) ((int32_t)((A) * (1 << 6)))
#define IQ5(A) ((int32_t)((A) * (1 << 5)))
#define IQ4(A) ((int32_t)((A) * (1 << 4)))
#define IQ3(A) ((int32_t)((A) * (1 << 3)))
#define IQ2(A) ((int32_t)((A) * (1 << 2)))
#define IQ1(A) ((int32_t)((A) * (1 << 1)))
/*******************************************************************************
* Function Name  : IQ
* Description    : 将浮点数转换成IQ格式数
* Input          : float类型数值
* Return         : 返回转换后的IQ格式数，与GLOBAL_Q指定的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQ(A) IQ30(A)
#endif
#if GLOBAL_Q == 29
#define IQ(A) IQ29(A)
#endif
#if GLOBAL_Q == 28
#define IQ(A) IQ28(A)
#endif
#if GLOBAL_Q == 27
#define IQ(A) IQ27(A)
#endif
#if GLOBAL_Q == 26
#define IQ(A) IQ26(A)
#endif
#if GLOBAL_Q == 25
#define IQ(A) IQ25(A)
#endif
#if GLOBAL_Q == 24
#define IQ(A) IQ24(A)
#endif
#if GLOBAL_Q == 23
#define IQ(A) IQ23(A)
#endif
#if GLOBAL_Q == 22
#define IQ(A) IQ22(A)
#endif
#if GLOBAL_Q == 21
#define IQ(A) IQ21(A)
#endif
#if GLOBAL_Q == 20
#define IQ(A) IQ20(A)
#endif
#if GLOBAL_Q == 19
#define IQ(A) IQ19(A)
#endif
#if GLOBAL_Q == 18
#define IQ(A) IQ18(A)
#endif
#if GLOBAL_Q == 17
#define IQ(A) IQ17(A)
#endif
#if GLOBAL_Q == 16
#define IQ(A) IQ16(A)
#endif
#if GLOBAL_Q == 15
#define IQ(A) IQ15(A)
#endif
#if GLOBAL_Q == 14
#define IQ(A) IQ14(A)
#endif
#if GLOBAL_Q == 13
#define IQ(A) IQ13(A)
#endif
#if GLOBAL_Q == 12
#define IQ(A) IQ12(A)
#endif
#if GLOBAL_Q == 11
#define IQ(A) IQ11(A)
#endif
#if GLOBAL_Q == 10
#define IQ(A) IQ10(A)
#endif
#if GLOBAL_Q == 9
#define IQ(A) IQ9(A)
#endif
#if GLOBAL_Q == 8
#define IQ(A) IQ8(A)
#endif
#if GLOBAL_Q == 7
#define IQ(A) IQ7(A)
#endif
#if GLOBAL_Q == 6
#define IQ(A) IQ6(A)
#endif
#if GLOBAL_Q == 5
#define IQ(A) IQ5(A)
#endif
#if GLOBAL_Q == 4
#define IQ(A) IQ4(A)
#endif
#if GLOBAL_Q == 3
#define IQ(A) IQ3(A)
#endif
#if GLOBAL_Q == 2
#define IQ(A) IQ2(A)
#endif
#if GLOBAL_Q == 1
#define IQ(A) IQ1(A)
#endif

/*******************************************************************************
* Function Name  : IQtoF
* Description    : 将IQ格式的数转换成单精度浮点数
* Input          : IQ类型数据
* Return         : 转换后的float类型的数据
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQtoF(A) IQ30toF(A)
#endif
#if GLOBAL_Q == 29
#define IQtoF(A) IQ29toF(A)
#endif
#if GLOBAL_Q == 28
#define IQtoF(A) IQ28toF(A)
#endif
#if GLOBAL_Q == 27
#define IQtoF(A) IQ27toF(A)
#endif
#if GLOBAL_Q == 26
#define IQtoF(A) IQ26toF(A)
#endif
#if GLOBAL_Q == 25
#define IQtoF(A) IQ25toF(A)
#endif
#if GLOBAL_Q == 24
#define IQtoF(A) IQ24toF(A)
#endif
#if GLOBAL_Q == 23
#define IQtoF(A) IQ23toF(A)
#endif
#if GLOBAL_Q == 22
#define IQtoF(A) IQ22toF(A)
#endif
#if GLOBAL_Q == 21
#define IQtoF(A) IQ21toF(A)
#endif
#if GLOBAL_Q == 20
#define IQtoF(A) IQ20toF(A)
#endif
#if GLOBAL_Q == 19
#define IQtoF(A) IQ19toF(A)
#endif
#if GLOBAL_Q == 18
#define IQtoF(A) IQ18toF(A)
#endif
#if GLOBAL_Q == 17
#define IQtoF(A) IQ17toF(A)
#endif
#if GLOBAL_Q == 16
#define IQtoF(A) IQ16toF(A)
#endif
#if GLOBAL_Q == 15
#define IQtoF(A) IQ15toF(A)
#endif
#if GLOBAL_Q == 14
#define IQtoF(A) IQ14toF(A)
#endif
#if GLOBAL_Q == 13
#define IQtoF(A) IQ13toF(A)
#endif
#if GLOBAL_Q == 12
#define IQtoF(A) IQ12toF(A)
#endif
#if GLOBAL_Q == 11
#define IQtoF(A) IQ11toF(A)
#endif
#if GLOBAL_Q == 10
#define IQtoF(A) IQ10toF(A)
#endif
#if GLOBAL_Q == 9
#define IQtoF(A) IQ9toF(A)
#endif
#if GLOBAL_Q == 8
#define IQtoF(A) IQ8toF(A)
#endif
#if GLOBAL_Q == 7
#define IQtoF(A) IQ7toF(A)
#endif
#if GLOBAL_Q == 6
#define IQtoF(A) IQ6toF(A)
#endif
#if GLOBAL_Q == 5
#define IQtoF(A) IQ5toF(A)
#endif
#if GLOBAL_Q == 4
#define IQtoF(A) IQ4toF(A)
#endif
#if GLOBAL_Q == 3
#define IQtoF(A) IQ3toF(A)
#endif
#if GLOBAL_Q == 2
#define IQtoF(A) IQ2toF(A)
#endif
#if GLOBAL_Q == 1
#define IQtoF(A) IQ1toF(A)
#endif

/*******************************************************************************
* Function Name  : IQtoD
* Description    : 将IQ格式的数转换成双精度浮点数
* Input          : IQ类型数据
* Return         : 转换后的double类型的数据
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQtoD(A) IQ30toD(A)
#endif
#if GLOBAL_Q == 29
#define IQtoD(A) IQ29toD(A)
#endif
#if GLOBAL_Q == 28
#define IQtoD(A) IQ28toD(A)
#endif
#if GLOBAL_Q == 27
#define IQtoD(A) IQ27toD(A)
#endif
#if GLOBAL_Q == 26
#define IQtoD(A) IQ26toD(A)
#endif
#if GLOBAL_Q == 25
#define IQtoD(A) IQ25toD(A)
#endif
#if GLOBAL_Q == 24
#define IQtoD(A) IQ24toD(A)
#endif
#if GLOBAL_Q == 23
#define IQtoD(A) IQ23toD(A)
#endif
#if GLOBAL_Q == 22
#define IQtoD(A) IQ22toD(A)
#endif
#if GLOBAL_Q == 21
#define IQtoD(A) IQ21toD(A)
#endif
#if GLOBAL_Q == 20
#define IQtoD(A) IQ20toD(A)
#endif
#if GLOBAL_Q == 19
#define IQtoD(A) IQ19toD(A)
#endif
#if GLOBAL_Q == 18
#define IQtoD(A) IQ18toD(A)
#endif
#if GLOBAL_Q == 17
#define IQtoD(A) IQ17toD(A)
#endif
#if GLOBAL_Q == 16
#define IQtoD(A) IQ16toD(A)
#endif
#if GLOBAL_Q == 15
#define IQtoD(A) IQ15toD(A)
#endif
#if GLOBAL_Q == 14
#define IQtoD(A) IQ14toD(A)
#endif
#if GLOBAL_Q == 13
#define IQtoD(A) IQ13toD(A)
#endif
#if GLOBAL_Q == 12
#define IQtoD(A) IQ12toD(A)
#endif
#if GLOBAL_Q == 11
#define IQtoD(A) IQ11toD(A)
#endif
#if GLOBAL_Q == 10
#define IQtoD(A) IQ10toD(A)
#endif
#if GLOBAL_Q == 9
#define IQtoD(A) IQ9toD(A)
#endif
#if GLOBAL_Q == 8
#define IQtoD(A) IQ8toD(A)
#endif
#if GLOBAL_Q == 7
#define IQtoD(A) IQ7toD(A)
#endif
#if GLOBAL_Q == 6
#define IQtoD(A) IQ6toD(A)
#endif
#if GLOBAL_Q == 5
#define IQtoD(A) IQ5toD(A)
#endif
#if GLOBAL_Q == 4
#define IQtoD(A) IQ4toD(A)
#endif
#if GLOBAL_Q == 3
#define IQtoD(A) IQ3toD(A)
#endif
#if GLOBAL_Q == 2
#define IQtoD(A) IQ2toD(A)
#endif
#if GLOBAL_Q == 1
#define IQtoD(A) IQ1toD(A)
#endif

#define IQsat(A, Pos, Neg) (((A) > (Pos)) ? (Pos) : (((A) < (Neg)) ? (Neg) : (A)))

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

/*******************************************************************************
* Function Name  : IQdiv
* Description    : IQ格式数的除法运算:A/B
* Input          : A为被除数，B为除数，A与B为相同IQ格式的数
* Return         : A除以B的商，与参数的IQ格式相同
*******************************************************************************/
#if DIV_FAST == 0
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

extern int32_t IQ29sin(int32_t A);
extern int32_t IQ28sin(int32_t A);
extern int32_t IQ27sin(int32_t A);
extern int32_t IQ26sin(int32_t A);
extern int32_t IQ25sin(int32_t A);
extern int32_t IQ24sin(int32_t A);
extern int32_t IQ23sin(int32_t A);
extern int32_t IQ22sin(int32_t A);
extern int32_t IQ21sin(int32_t A);
extern int32_t IQ20sin(int32_t A);
extern int32_t IQ19sin(int32_t A);
extern int32_t IQ18sin(int32_t A);
extern int32_t IQ17sin(int32_t A);
extern int32_t IQ16sin(int32_t A);
extern int32_t IQ15sin(int32_t A);
extern int32_t IQ14sin(int32_t A);
extern int32_t IQ13sin(int32_t A);
extern int32_t IQ12sin(int32_t A);
extern int32_t IQ11sin(int32_t A);
extern int32_t IQ10sin(int32_t A);
extern int32_t IQ9sin(int32_t A);
extern int32_t IQ8sin(int32_t A);
extern int32_t IQ7sin(int32_t A);
extern int32_t IQ6sin(int32_t A);
extern int32_t IQ5sin(int32_t A);
extern int32_t IQ4sin(int32_t A);
extern int32_t IQ3sin(int32_t A);
extern int32_t IQ2sin(int32_t A);
extern int32_t IQ1sin(int32_t A);
/*******************************************************************************
* Function Name  : IQsin
* Description    : IQ格式数的正弦函数:sin(A)
* Input          : 输入参数为IQ格式的弧度值
* Return         : 返回A的正弦值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQsin(A) IQ29sin(A)
#endif
#if GLOBAL_Q == 28
#define IQsin(A) IQ28sin(A)
#endif
#if GLOBAL_Q == 27
#define IQsin(A) IQ27sin(A)
#endif
#if GLOBAL_Q == 26
#define IQsin(A) IQ26sin(A)
#endif
#if GLOBAL_Q == 25
#define IQsin(A) IQ25sin(A)
#endif
#if GLOBAL_Q == 24
#define IQsin(A) IQ24sin(A)
#endif
#if GLOBAL_Q == 23
#define IQsin(A) IQ23sin(A)
#endif
#if GLOBAL_Q == 22
#define IQsin(A) IQ22sin(A)
#endif
#if GLOBAL_Q == 21
#define IQsin(A) IQ21sin(A)
#endif
#if GLOBAL_Q == 20
#define IQsin(A) IQ20sin(A)
#endif
#if GLOBAL_Q == 19
#define IQsin(A) IQ19sin(A)
#endif
#if GLOBAL_Q == 18
#define IQsin(A) IQ18sin(A)
#endif
#if GLOBAL_Q == 17
#define IQsin(A) IQ17sin(A)
#endif
#if GLOBAL_Q == 16
#define IQsin(A) IQ16sin(A)
#endif
#if GLOBAL_Q == 15
#define IQsin(A) IQ15sin(A)
#endif
#if GLOBAL_Q == 14
#define IQsin(A) IQ14sin(A)
#endif
#if GLOBAL_Q == 13
#define IQsin(A) IQ13sin(A)
#endif
#if GLOBAL_Q == 12
#define IQsin(A) IQ12sin(A)
#endif
#if GLOBAL_Q == 11
#define IQsin(A) IQ11sin(A)
#endif
#if GLOBAL_Q == 10
#define IQsin(A) IQ10sin(A)
#endif
#if GLOBAL_Q == 9
#define IQsin(A) IQ9sin(A)
#endif
#if GLOBAL_Q == 8
#define IQsin(A) IQ8sin(A)
#endif
#if GLOBAL_Q == 7
#define IQsin(A) IQ7sin(A)
#endif
#if GLOBAL_Q == 6
#define IQsin(A) IQ6sin(A)
#endif
#if GLOBAL_Q == 5
#define IQsin(A) IQ5sin(A)
#endif
#if GLOBAL_Q == 4
#define IQsin(A) IQ4sin(A)
#endif
#if GLOBAL_Q == 3
#define IQsin(A) IQ3sin(A)
#endif
#if GLOBAL_Q == 2
#define IQsin(A) IQ2sin(A)
#endif
#if GLOBAL_Q == 1
#define IQsin(A) IQ1sin(A)
#endif

extern int32_t IQ29asin(int32_t A);
extern int32_t IQ28asin(int32_t A);
extern int32_t IQ27asin(int32_t A);
extern int32_t IQ26asin(int32_t A);
extern int32_t IQ25asin(int32_t A);
extern int32_t IQ24asin(int32_t A);
extern int32_t IQ23asin(int32_t A);
extern int32_t IQ22asin(int32_t A);
extern int32_t IQ21asin(int32_t A);
extern int32_t IQ20asin(int32_t A);
extern int32_t IQ19asin(int32_t A);
extern int32_t IQ18asin(int32_t A);
extern int32_t IQ17asin(int32_t A);
extern int32_t IQ16asin(int32_t A);
extern int32_t IQ15asin(int32_t A);
extern int32_t IQ14asin(int32_t A);
extern int32_t IQ13asin(int32_t A);
extern int32_t IQ12asin(int32_t A);
extern int32_t IQ11asin(int32_t A);
extern int32_t IQ10asin(int32_t A);
extern int32_t IQ9asin(int32_t A);
extern int32_t IQ8asin(int32_t A);
extern int32_t IQ7asin(int32_t A);
extern int32_t IQ6asin(int32_t A);
extern int32_t IQ5asin(int32_t A);
extern int32_t IQ4asin(int32_t A);
extern int32_t IQ3asin(int32_t A);
extern int32_t IQ2asin(int32_t A);
extern int32_t IQ1asin(int32_t A);
/*******************************************************************************
* Function Name  : IQasin
* Description    : IQ格式数的反正弦函数:asin(A)
* Input          : 输入参数为IQ格式的弧度值
* Return         : 返回A的反正弦值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQasin(A) IQ29asin(A)
#endif
#if GLOBAL_Q == 28
#define IQasin(A) IQ28asin(A)
#endif
#if GLOBAL_Q == 27
#define IQasin(A) IQ27asin(A)
#endif
#if GLOBAL_Q == 26
#define IQasin(A) IQ26asin(A)
#endif
#if GLOBAL_Q == 25
#define IQasin(A) IQ25asin(A)
#endif
#if GLOBAL_Q == 24
#define IQasin(A) IQ24asin(A)
#endif
#if GLOBAL_Q == 23
#define IQasin(A) IQ23asin(A)
#endif
#if GLOBAL_Q == 22
#define IQasin(A) IQ22asin(A)
#endif
#if GLOBAL_Q == 21
#define IQasin(A) IQ21asin(A)
#endif
#if GLOBAL_Q == 20
#define IQasin(A) IQ20asin(A)
#endif
#if GLOBAL_Q == 19
#define IQasin(A) IQ19asin(A)
#endif
#if GLOBAL_Q == 18
#define IQasin(A) IQ18asin(A)
#endif
#if GLOBAL_Q == 17
#define IQasin(A) IQ17asin(A)
#endif
#if GLOBAL_Q == 16
#define IQasin(A) IQ16asin(A)
#endif
#if GLOBAL_Q == 15
#define IQasin(A) IQ15asin(A)
#endif
#if GLOBAL_Q == 14
#define IQasin(A) IQ14asin(A)
#endif
#if GLOBAL_Q == 13
#define IQasin(A) IQ13asin(A)
#endif
#if GLOBAL_Q == 12
#define IQasin(A) IQ12asin(A)
#endif
#if GLOBAL_Q == 11
#define IQasin(A) IQ11asin(A)
#endif
#if GLOBAL_Q == 10
#define IQasin(A) IQ10asin(A)
#endif
#if GLOBAL_Q == 9
#define IQasin(A) IQ9asin(A)
#endif
#if GLOBAL_Q == 8
#define IQasin(A) IQ8asin(A)
#endif
#if GLOBAL_Q == 7
#define IQasin(A) IQ7asin(A)
#endif
#if GLOBAL_Q == 6
#define IQasin(A) IQ6asin(A)
#endif
#if GLOBAL_Q == 5
#define IQasin(A) IQ5asin(A)
#endif
#if GLOBAL_Q == 4
#define IQasin(A) IQ4asin(A)
#endif
#if GLOBAL_Q == 3
#define IQasin(A) IQ3asin(A)
#endif
#if GLOBAL_Q == 2
#define IQasin(A) IQ2asin(A)
#endif
#if GLOBAL_Q == 1
#define IQasin(A) IQ1asin(A)
#endif

extern int32_t IQ29cos(int32_t A);
extern int32_t IQ28cos(int32_t A);
extern int32_t IQ27cos(int32_t A);
extern int32_t IQ26cos(int32_t A);
extern int32_t IQ25cos(int32_t A);
extern int32_t IQ24cos(int32_t A);
extern int32_t IQ23cos(int32_t A);
extern int32_t IQ22cos(int32_t A);
extern int32_t IQ21cos(int32_t A);
extern int32_t IQ20cos(int32_t A);
extern int32_t IQ19cos(int32_t A);
extern int32_t IQ18cos(int32_t A);
extern int32_t IQ17cos(int32_t A);
extern int32_t IQ16cos(int32_t A);
extern int32_t IQ15cos(int32_t A);
extern int32_t IQ14cos(int32_t A);
extern int32_t IQ13cos(int32_t A);
extern int32_t IQ12cos(int32_t A);
extern int32_t IQ11cos(int32_t A);
extern int32_t IQ10cos(int32_t A);
extern int32_t IQ9cos(int32_t A);
extern int32_t IQ8cos(int32_t A);
extern int32_t IQ7cos(int32_t A);
extern int32_t IQ6cos(int32_t A);
extern int32_t IQ5cos(int32_t A);
extern int32_t IQ4cos(int32_t A);
extern int32_t IQ3cos(int32_t A);
extern int32_t IQ2cos(int32_t A);
extern int32_t IQ1cos(int32_t A);
/*******************************************************************************
* Function Name  : IQcos
* Description    : IQ格式数的余弦函数:cos(A)
* Input          : 输入参数为IQ格式的弧度值
* Return         : 返回A的余弦值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQcos(A) IQ29cos(A)
#endif
#if GLOBAL_Q == 28
#define IQcos(A) IQ28cos(A)
#endif
#if GLOBAL_Q == 27
#define IQcos(A) IQ27cos(A)
#endif
#if GLOBAL_Q == 26
#define IQcos(A) IQ26cos(A)
#endif
#if GLOBAL_Q == 25
#define IQcos(A) IQ25cos(A)
#endif
#if GLOBAL_Q == 24
#define IQcos(A) IQ24cos(A)
#endif
#if GLOBAL_Q == 23
#define IQcos(A) IQ23cos(A)
#endif
#if GLOBAL_Q == 22
#define IQcos(A) IQ22cos(A)
#endif
#if GLOBAL_Q == 21
#define IQcos(A) IQ21cos(A)
#endif
#if GLOBAL_Q == 20
#define IQcos(A) IQ20cos(A)
#endif
#if GLOBAL_Q == 19
#define IQcos(A) IQ19cos(A)
#endif
#if GLOBAL_Q == 18
#define IQcos(A) IQ18cos(A)
#endif
#if GLOBAL_Q == 17
#define IQcos(A) IQ17cos(A)
#endif
#if GLOBAL_Q == 16
#define IQcos(A) IQ16cos(A)
#endif
#if GLOBAL_Q == 15
#define IQcos(A) IQ15cos(A)
#endif
#if GLOBAL_Q == 14
#define IQcos(A) IQ14cos(A)
#endif
#if GLOBAL_Q == 13
#define IQcos(A) IQ13cos(A)
#endif
#if GLOBAL_Q == 12
#define IQcos(A) IQ12cos(A)
#endif
#if GLOBAL_Q == 11
#define IQcos(A) IQ11cos(A)
#endif
#if GLOBAL_Q == 10
#define IQcos(A) IQ10cos(A)
#endif
#if GLOBAL_Q == 9
#define IQcos(A) IQ9cos(A)
#endif
#if GLOBAL_Q == 8
#define IQcos(A) IQ8cos(A)
#endif
#if GLOBAL_Q == 7
#define IQcos(A) IQ7cos(A)
#endif
#if GLOBAL_Q == 6
#define IQcos(A) IQ6cos(A)
#endif
#if GLOBAL_Q == 5
#define IQcos(A) IQ5cos(A)
#endif
#if GLOBAL_Q == 4
#define IQcos(A) IQ4cos(A)
#endif
#if GLOBAL_Q == 3
#define IQcos(A) IQ3cos(A)
#endif
#if GLOBAL_Q == 2
#define IQcos(A) IQ2cos(A)
#endif
#if GLOBAL_Q == 1
#define IQcos(A) IQ1cos(A)
#endif

#define IQ29acos(A) (_IQ29(1.570796327) - IQ29asin(A))
#define IQ28acos(A) (_IQ28(1.570796327) - IQ28asin(A))
#define IQ27acos(A) (_IQ27(1.570796327) - IQ27asin(A))
#define IQ26acos(A) (_IQ26(1.570796327) - IQ26asin(A))
#define IQ25acos(A) (_IQ25(1.570796327) - IQ25asin(A))
#define IQ24acos(A) (_IQ24(1.570796327) - IQ24asin(A))
#define IQ23acos(A) (_IQ23(1.570796327) - IQ23asin(A))
#define IQ22acos(A) (_IQ22(1.570796327) - IQ22asin(A))
#define IQ21acos(A) (_IQ21(1.570796327) - IQ21asin(A))
#define IQ20acos(A) (_IQ20(1.570796327) - IQ20asin(A))
#define IQ19acos(A) (_IQ19(1.570796327) - IQ19asin(A))
#define IQ18acos(A) (_IQ18(1.570796327) - IQ18asin(A))
#define IQ17acos(A) (_IQ17(1.570796327) - IQ17asin(A))
#define IQ16acos(A) (_IQ16(1.570796327) - IQ16asin(A))
#define IQ15acos(A) (_IQ15(1.570796327) - IQ15asin(A))
#define IQ14acos(A) (_IQ14(1.570796327) - IQ14asin(A))
#define IQ13acos(A) (_IQ13(1.570796327) - IQ13asin(A))
#define IQ12acos(A) (_IQ12(1.570796327) - IQ12asin(A))
#define IQ11acos(A) (_IQ11(1.570796327) - IQ11asin(A))
#define IQ10acos(A) (_IQ10(1.570796327) - IQ10asin(A))
#define IQ9acos(A) (_IQ9(1.570796327) - IQ9asin(A))
#define IQ8acos(A) (_IQ8(1.570796327) - IQ8asin(A))
#define IQ7acos(A) (_IQ7(1.570796327) - IQ7asin(A))
#define IQ6acos(A) (_IQ6(1.570796327) - IQ6asin(A))
#define IQ5acos(A) (_IQ5(1.570796327) - IQ5asin(A))
#define IQ4acos(A) (_IQ4(1.570796327) - IQ4asin(A))
#define IQ3acos(A) (_IQ3(1.570796327) - IQ3asin(A))
#define IQ2acos(A) (_IQ2(1.570796327) - IQ2asin(A))
#define IQ1acos(A) (_IQ1(1.570796327) - IQ1asin(A))
/*******************************************************************************
* Function Name  : IQacos
* Description    : IQ格式数的反余弦函数:acos(A)
* Input          : 输入参数为IQ格式的弧度值
* Return         : 返回A的反余弦值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQacos(A) IQ29acos(A)
#endif
#if GLOBAL_Q == 28
#define IQacos(A) IQ28acos(A)
#endif
#if GLOBAL_Q == 27
#define IQacos(A) IQ27acos(A)
#endif
#if GLOBAL_Q == 26
#define IQacos(A) IQ26acos(A)
#endif
#if GLOBAL_Q == 25
#define IQacos(A) IQ25acos(A)
#endif
#if GLOBAL_Q == 24
#define IQacos(A) IQ24acos(A)
#endif
#if GLOBAL_Q == 23
#define IQacos(A) IQ23acos(A)
#endif
#if GLOBAL_Q == 22
#define IQacos(A) IQ22acos(A)
#endif
#if GLOBAL_Q == 21
#define IQacos(A) IQ21acos(A)
#endif
#if GLOBAL_Q == 20
#define IQacos(A) IQ20acos(A)
#endif
#if GLOBAL_Q == 19
#define IQacos(A) IQ19acos(A)
#endif
#if GLOBAL_Q == 18
#define IQacos(A) IQ18acos(A)
#endif
#if GLOBAL_Q == 17
#define IQacos(A) IQ17acos(A)
#endif
#if GLOBAL_Q == 16
#define IQacos(A) IQ16acos(A)
#endif
#if GLOBAL_Q == 15
#define IQacos(A) IQ15acos(A)
#endif
#if GLOBAL_Q == 14
#define IQacos(A) IQ14acos(A)
#endif
#if GLOBAL_Q == 13
#define IQacos(A) IQ13acos(A)
#endif
#if GLOBAL_Q == 12
#define IQacos(A) IQ12acos(A)
#endif
#if GLOBAL_Q == 11
#define IQacos(A) IQ11acos(A)
#endif
#if GLOBAL_Q == 10
#define IQacos(A) IQ10acos(A)
#endif
#if GLOBAL_Q == 9
#define IQacos(A) IQ9acos(A)
#endif
#if GLOBAL_Q == 8
#define IQacos(A) IQ8acos(A)
#endif
#if GLOBAL_Q == 7
#define IQacos(A) IQ7acos(A)
#endif
#if GLOBAL_Q == 6
#define IQacos(A) IQ6acos(A)
#endif
#if GLOBAL_Q == 5
#define IQacos(A) IQ5acos(A)
#endif
#if GLOBAL_Q == 4
#define IQacos(A) IQ4acos(A)
#endif
#if GLOBAL_Q == 3
#define IQacos(A) IQ3acos(A)
#endif
#if GLOBAL_Q == 2
#define IQacos(A) IQ2acos(A)
#endif
#if GLOBAL_Q == 1
#define IQacos(A) IQ1acos(A)
#endif

extern int32_t IQ29atan2(int32_t A, int32_t B);
extern int32_t IQ28atan2(int32_t A, int32_t B);
extern int32_t IQ27atan2(int32_t A, int32_t B);
extern int32_t IQ26atan2(int32_t A, int32_t B);
extern int32_t IQ25atan2(int32_t A, int32_t B);
extern int32_t IQ24atan2(int32_t A, int32_t B);
extern int32_t IQ23atan2(int32_t A, int32_t B);
extern int32_t IQ22atan2(int32_t A, int32_t B);
extern int32_t IQ21atan2(int32_t A, int32_t B);
extern int32_t IQ20atan2(int32_t A, int32_t B);
extern int32_t IQ19atan2(int32_t A, int32_t B);
extern int32_t IQ18atan2(int32_t A, int32_t B);
extern int32_t IQ17atan2(int32_t A, int32_t B);
extern int32_t IQ16atan2(int32_t A, int32_t B);
extern int32_t IQ15atan2(int32_t A, int32_t B);
extern int32_t IQ14atan2(int32_t A, int32_t B);
extern int32_t IQ13atan2(int32_t A, int32_t B);
extern int32_t IQ12atan2(int32_t A, int32_t B);
extern int32_t IQ11atan2(int32_t A, int32_t B);
extern int32_t IQ10atan2(int32_t A, int32_t B);
extern int32_t IQ9atan2(int32_t A, int32_t B);
extern int32_t IQ8atan2(int32_t A, int32_t B);
extern int32_t IQ7atan2(int32_t A, int32_t B);
extern int32_t IQ6atan2(int32_t A, int32_t B);
extern int32_t IQ5atan2(int32_t A, int32_t B);
extern int32_t IQ4atan2(int32_t A, int32_t B);
extern int32_t IQ3atan2(int32_t A, int32_t B);
extern int32_t IQ2atan2(int32_t A, int32_t B);
extern int32_t IQ1atan2(int32_t A, int32_t B);
/*******************************************************************************
* Function Name  : IQatan2
* Description    : IQ格式数的反正切函数，可计算4个象限内的点:atan2(A,B)
* Input          : A为IQ格式的Y轴坐标值，B为IQ格式的X轴坐标值
* Return         : 返回点(B,A)与X轴的夹角的弧度值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQatan2(A, B) IQ29atan2(A, B)
#endif
#if GLOBAL_Q == 28
#define IQatan2(A, B) IQ28atan2(A, B)
#endif
#if GLOBAL_Q == 27
#define IQatan2(A, B) IQ27atan2(A, B)
#endif
#if GLOBAL_Q == 26
#define IQatan2(A, B) IQ26atan2(A, B)
#endif
#if GLOBAL_Q == 25
#define IQatan2(A, B) IQ25atan2(A, B)
#endif
#if GLOBAL_Q == 24
#define IQatan2(A, B) IQ24atan2(A, B)
#endif
#if GLOBAL_Q == 23
#define IQatan2(A, B) IQ23atan2(A, B)
#endif
#if GLOBAL_Q == 22
#define IQatan2(A, B) IQ22atan2(A, B)
#endif
#if GLOBAL_Q == 21
#define IQatan2(A, B) IQ21atan2(A, B)
#endif
#if GLOBAL_Q == 20
#define IQatan2(A, B) IQ20atan2(A, B)
#endif
#if GLOBAL_Q == 19
#define IQatan2(A, B) IQ19atan2(A, B)
#endif
#if GLOBAL_Q == 18
#define IQatan2(A, B) IQ18atan2(A, B)
#endif
#if GLOBAL_Q == 17
#define IQatan2(A, B) IQ17atan2(A, B)
#endif
#if GLOBAL_Q == 16
#define IQatan2(A, B) IQ16atan2(A, B)
#endif
#if GLOBAL_Q == 15
#define IQatan2(A, B) IQ15atan2(A, B)
#endif
#if GLOBAL_Q == 14
#define IQatan2(A, B) IQ14atan2(A, B)
#endif
#if GLOBAL_Q == 13
#define IQatan2(A, B) IQ13atan2(A, B)
#endif
#if GLOBAL_Q == 12
#define IQatan2(A, B) IQ12atan2(A, B)
#endif
#if GLOBAL_Q == 11
#define IQatan2(A, B) IQ11atan2(A, B)
#endif
#if GLOBAL_Q == 10
#define IQatan2(A, B) IQ10atan2(A, B)
#endif
#if GLOBAL_Q == 9
#define IQatan2(A, B) IQ9atan2(A, B)
#endif
#if GLOBAL_Q == 8
#define IQatan2(A, B) IQ8atan2(A, B)
#endif
#if GLOBAL_Q == 7
#define IQatan2(A, B) IQ7atan2(A, B)
#endif
#if GLOBAL_Q == 6
#define IQatan2(A, B) IQ6atan2(A, B)
#endif
#if GLOBAL_Q == 5
#define IQatan2(A, B) IQ5atan2(A, B)
#endif
#if GLOBAL_Q == 4
#define IQatan2(A, B) IQ4atan2(A, B)
#endif
#if GLOBAL_Q == 3
#define IQatan2(A, B) IQ3atan2(A, B)
#endif
#if GLOBAL_Q == 2
#define IQatan2(A, B) IQ2atan2(A, B)
#endif
#if GLOBAL_Q == 1
#define IQatan2(A, B) IQ1atan2(A, B)
#endif

#define IQ29atan(A) IQ29atan2(A, IQ29(1.0))
#define IQ28atan(A) IQ28atan2(A, IQ28(1.0))
#define IQ27atan(A) IQ27atan2(A, IQ27(1.0))
#define IQ26atan(A) IQ26atan2(A, IQ26(1.0))
#define IQ25atan(A) IQ25atan2(A, IQ25(1.0))
#define IQ24atan(A) IQ24atan2(A, IQ24(1.0))
#define IQ23atan(A) IQ23atan2(A, IQ23(1.0))
#define IQ22atan(A) IQ22atan2(A, IQ22(1.0))
#define IQ21atan(A) IQ21atan2(A, IQ21(1.0))
#define IQ20atan(A) IQ20atan2(A, IQ20(1.0))
#define IQ19atan(A) IQ19atan2(A, IQ19(1.0))
#define IQ18atan(A) IQ18atan2(A, IQ18(1.0))
#define IQ17atan(A) IQ17atan2(A, IQ17(1.0))
#define IQ16atan(A) IQ16atan2(A, IQ16(1.0))
#define IQ15atan(A) IQ15atan2(A, IQ15(1.0))
#define IQ14atan(A) IQ14atan2(A, IQ14(1.0))
#define IQ13atan(A) IQ13atan2(A, IQ13(1.0))
#define IQ12atan(A) IQ12atan2(A, IQ12(1.0))
#define IQ11atan(A) IQ11atan2(A, IQ11(1.0))
#define IQ10atan(A) IQ10atan2(A, IQ10(1.0))
#define IQ9atan(A) IQ9atan2(A, IQ9(1.0))
#define IQ8atan(A) IQ8atan2(A, IQ8(1.0))
#define IQ7atan(A) IQ7atan2(A, IQ7(1.0))
#define IQ6atan(A) IQ6atan2(A, IQ6(1.0))
#define IQ5atan(A) IQ5atan2(A, IQ5(1.0))
#define IQ4atan(A) IQ4atan2(A, IQ4(1.0))
#define IQ3atan(A) IQ3atan2(A, IQ3(1.0))
#define IQ2atan(A) IQ2atan2(A, IQ2(1.0))
#define IQ1atan(A) IQ1atan2(A, IQ1(1.0))
/*******************************************************************************
* Function Name  : IQatan
* Description    : IQ格式数的反正切函数，计算第1、4象限内的点:atan(A)
* Input          : 参数A为IQ格式的数
* Return         : 返回值介于-pi/2和pi/2之间，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 29
#define IQatan(A) IQ29atan2(A, IQ29(1.0))
#endif
#if GLOBAL_Q == 28
#define IQatan(A) IQ28atan2(A, IQ28(1.0))
#endif
#if GLOBAL_Q == 27
#define IQatan(A) IQ27atan2(A, IQ27(1.0))
#endif
#if GLOBAL_Q == 26
#define IQatan(A) IQ26atan2(A, IQ26(1.0))
#endif
#if GLOBAL_Q == 25
#define IQatan(A) IQ25atan2(A, IQ25(1.0))
#endif
#if GLOBAL_Q == 24
#define IQatan(A) IQ24atan2(A, IQ24(1.0))
#endif
#if GLOBAL_Q == 23
#define IQatan(A) IQ23atan2(A, IQ23(1.0))
#endif
#if GLOBAL_Q == 22
#define IQatan(A) IQ22atan2(A, IQ22(1.0))
#endif
#if GLOBAL_Q == 21
#define IQatan(A) IQ21atan2(A, IQ21(1.0))
#endif
#if GLOBAL_Q == 20
#define IQatan(A) IQ20atan2(A, IQ20(1.0))
#endif
#if GLOBAL_Q == 19
#define IQatan(A) IQ19atan2(A, IQ19(1.0))
#endif
#if GLOBAL_Q == 18
#define IQatan(A) IQ18atan2(A, IQ18(1.0))
#endif
#if GLOBAL_Q == 17
#define IQatan(A) IQ17atan2(A, IQ17(1.0))
#endif
#if GLOBAL_Q == 16
#define IQatan(A) IQ16atan2(A, IQ16(1.0))
#endif
#if GLOBAL_Q == 15
#define IQatan(A) IQ15atan2(A, IQ15(1.0))
#endif
#if GLOBAL_Q == 14
#define IQatan(A) IQ14atan2(A, IQ14(1.0))
#endif
#if GLOBAL_Q == 13
#define IQatan(A) IQ13atan2(A, IQ13(1.0))
#endif
#if GLOBAL_Q == 12
#define IQatan(A) IQ12atan2(A, IQ12(1.0))
#endif
#if GLOBAL_Q == 11
#define IQatan(A) IQ11atan2(A, IQ11(1.0))
#endif
#if GLOBAL_Q == 10
#define IQatan(A) IQ10atan2(A, IQ10(1.0))
#endif
#if GLOBAL_Q == 9
#define IQatan(A) IQ9atan2(A, IQ9(1.0))
#endif
#if GLOBAL_Q == 8
#define IQatan(A) IQ8atan2(A, IQ8(1.0))
#endif
#if GLOBAL_Q == 7
#define IQatan(A) IQ7atan2(A, IQ7(1.0))
#endif
#if GLOBAL_Q == 6
#define IQatan(A) IQ6atan2(A, IQ6(1.0))
#endif
#if GLOBAL_Q == 5
#define IQatan(A) IQ5atan2(A, IQ5(1.0))
#endif
#if GLOBAL_Q == 4
#define IQatan(A) IQ4atan2(A, IQ4(1.0))
#endif
#if GLOBAL_Q == 3
#define IQatan(A) IQ3atan2(A, IQ3(1.0))
#endif
#if GLOBAL_Q == 2
#define IQatan(A) IQ2atan2(A, IQ2(1.0))
#endif
#if GLOBAL_Q == 1
#define IQatan(A) IQ1atan2(A, IQ1(1.0))
#endif

extern int32_t IQ30sqrt(int32_t A);
extern int32_t IQ29sqrt(int32_t A);
extern int32_t IQ28sqrt(int32_t A);
extern int32_t IQ27sqrt(int32_t A);
extern int32_t IQ26sqrt(int32_t A);
extern int32_t IQ25sqrt(int32_t A);
extern int32_t IQ24sqrt(int32_t A);
extern int32_t IQ23sqrt(int32_t A);
extern int32_t IQ22sqrt(int32_t A);
extern int32_t IQ21sqrt(int32_t A);
extern int32_t IQ20sqrt(int32_t A);
extern int32_t IQ19sqrt(int32_t A);
extern int32_t IQ18sqrt(int32_t A);
extern int32_t IQ17sqrt(int32_t A);
extern int32_t IQ16sqrt(int32_t A);
extern int32_t IQ15sqrt(int32_t A);
extern int32_t IQ14sqrt(int32_t A);
extern int32_t IQ13sqrt(int32_t A);
extern int32_t IQ12sqrt(int32_t A);
extern int32_t IQ11sqrt(int32_t A);
extern int32_t IQ10sqrt(int32_t A);
extern int32_t IQ9sqrt(int32_t A);
extern int32_t IQ8sqrt(int32_t A);
extern int32_t IQ7sqrt(int32_t A);
extern int32_t IQ6sqrt(int32_t A);
extern int32_t IQ5sqrt(int32_t A);
extern int32_t IQ4sqrt(int32_t A);
extern int32_t IQ3sqrt(int32_t A);
extern int32_t IQ2sqrt(int32_t A);
extern int32_t IQ1sqrt(int32_t A);
/*******************************************************************************
* Function Name  : IQsqrt
* Description    : IQ格式数的平方根函数:A^(1/2)
* Input          : 参数A为IQ格式的数
* Return         : 返回A的平方根值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQsqrt(A) IQ30sqrt(A)
#endif
#if GLOBAL_Q == 29
#define IQsqrt(A) IQ29sqrt(A)
#endif
#if GLOBAL_Q == 28
#define IQsqrt(A) IQ28sqrt(A)
#endif
#if GLOBAL_Q == 27
#define IQsqrt(A) IQ27sqrt(A)
#endif
#if GLOBAL_Q == 26
#define IQsqrt(A) IQ26sqrt(A)
#endif
#if GLOBAL_Q == 25
#define IQsqrt(A) IQ25sqrt(A)
#endif
#if GLOBAL_Q == 24
#define IQsqrt(A) IQ24sqrt(A)
#endif
#if GLOBAL_Q == 23
#define IQsqrt(A) IQ23sqrt(A)
#endif
#if GLOBAL_Q == 22
#define IQsqrt(A) IQ22sqrt(A)
#endif
#if GLOBAL_Q == 21
#define IQsqrt(A) IQ21sqrt(A)
#endif
#if GLOBAL_Q == 20
#define IQsqrt(A) IQ20sqrt(A)
#endif
#if GLOBAL_Q == 19
#define IQsqrt(A) IQ19sqrt(A)
#endif
#if GLOBAL_Q == 18
#define IQsqrt(A) IQ18sqrt(A)
#endif
#if GLOBAL_Q == 17
#define IQsqrt(A) IQ17sqrt(A)
#endif
#if GLOBAL_Q == 16
#define IQsqrt(A) IQ16sqrt(A)
#endif
#if GLOBAL_Q == 15
#define IQsqrt(A) IQ15sqrt(A)
#endif
#if GLOBAL_Q == 14
#define IQsqrt(A) IQ14sqrt(A)
#endif
#if GLOBAL_Q == 13
#define IQsqrt(A) IQ13sqrt(A)
#endif
#if GLOBAL_Q == 12
#define IQsqrt(A) IQ12sqrt(A)
#endif
#if GLOBAL_Q == 11
#define IQsqrt(A) IQ11sqrt(A)
#endif
#if GLOBAL_Q == 10
#define IQsqrt(A) IQ10sqrt(A)
#endif
#if GLOBAL_Q == 9
#define IQsqrt(A) IQ9sqrt(A)
#endif
#if GLOBAL_Q == 8
#define IQsqrt(A) IQ8sqrt(A)
#endif
#if GLOBAL_Q == 7
#define IQsqrt(A) IQ7sqrt(A)
#endif
#if GLOBAL_Q == 6
#define IQsqrt(A) IQ6sqrt(A)
#endif
#if GLOBAL_Q == 5
#define IQsqrt(A) IQ5sqrt(A)
#endif
#if GLOBAL_Q == 4
#define IQsqrt(A) IQ4sqrt(A)
#endif
#if GLOBAL_Q == 3
#define IQsqrt(A) IQ3sqrt(A)
#endif
#if GLOBAL_Q == 2
#define IQsqrt(A) IQ2sqrt(A)
#endif
#if GLOBAL_Q == 1
#define IQsqrt(A) IQ1sqrt(A)
#endif

extern int32_t IQ30isqrt(int32_t A);
extern int32_t IQ29isqrt(int32_t A);
extern int32_t IQ28isqrt(int32_t A);
extern int32_t IQ27isqrt(int32_t A);
extern int32_t IQ26isqrt(int32_t A);
extern int32_t IQ25isqrt(int32_t A);
extern int32_t IQ24isqrt(int32_t A);
extern int32_t IQ23isqrt(int32_t A);
extern int32_t IQ22isqrt(int32_t A);
extern int32_t IQ21isqrt(int32_t A);
extern int32_t IQ20isqrt(int32_t A);
extern int32_t IQ19isqrt(int32_t A);
extern int32_t IQ18isqrt(int32_t A);
extern int32_t IQ17isqrt(int32_t A);
extern int32_t IQ16isqrt(int32_t A);
extern int32_t IQ15isqrt(int32_t A);
extern int32_t IQ14isqrt(int32_t A);
extern int32_t IQ13isqrt(int32_t A);
extern int32_t IQ12isqrt(int32_t A);
extern int32_t IQ11isqrt(int32_t A);
extern int32_t IQ10isqrt(int32_t A);
extern int32_t IQ9isqrt(int32_t A);
extern int32_t IQ8isqrt(int32_t A);
extern int32_t IQ7isqrt(int32_t A);
extern int32_t IQ6isqrt(int32_t A);
extern int32_t IQ5isqrt(int32_t A);
extern int32_t IQ4isqrt(int32_t A);
extern int32_t IQ3isqrt(int32_t A);
extern int32_t IQ2isqrt(int32_t A);
extern int32_t IQ1isqrt(int32_t A);
/*******************************************************************************
* Function Name  : IQisqrt
* Description    : IQ格式数的平方根倒数函数:A^(-1/2)
* Input          : 参数A为IQ格式的数
* Return         : 返回A的平方根倒数值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQisqrt(A) IQ30isqrt(A)
#endif
#if GLOBAL_Q == 29
#define IQisqrt(A) IQ29isqrt(A)
#endif
#if GLOBAL_Q == 28
#define IQisqrt(A) IQ28isqrt(A)
#endif
#if GLOBAL_Q == 27
#define IQisqrt(A) IQ27isqrt(A)
#endif
#if GLOBAL_Q == 26
#define IQisqrt(A) IQ26isqrt(A)
#endif
#if GLOBAL_Q == 25
#define IQisqrt(A) IQ25isqrt(A)
#endif
#if GLOBAL_Q == 24
#define IQisqrt(A) IQ24isqrt(A)
#endif
#if GLOBAL_Q == 23
#define IQisqrt(A) IQ23isqrt(A)
#endif
#if GLOBAL_Q == 22
#define IQisqrt(A) IQ22isqrt(A)
#endif
#if GLOBAL_Q == 21
#define IQisqrt(A) IQ21isqrt(A)
#endif
#if GLOBAL_Q == 20
#define IQisqrt(A) IQ20isqrt(A)
#endif
#if GLOBAL_Q == 19
#define IQisqrt(A) IQ19isqrt(A)
#endif
#if GLOBAL_Q == 18
#define IQisqrt(A) IQ18isqrt(A)
#endif
#if GLOBAL_Q == 17
#define IQisqrt(A) IQ17isqrt(A)
#endif
#if GLOBAL_Q == 16
#define IQisqrt(A) IQ16isqrt(A)
#endif
#if GLOBAL_Q == 15
#define IQisqrt(A) IQ15isqrt(A)
#endif
#if GLOBAL_Q == 14
#define IQisqrt(A) IQ14isqrt(A)
#endif
#if GLOBAL_Q == 13
#define IQisqrt(A) IQ13isqrt(A)
#endif
#if GLOBAL_Q == 12
#define IQisqrt(A) IQ12isqrt(A)
#endif
#if GLOBAL_Q == 11
#define IQisqrt(A) IQ11isqrt(A)
#endif
#if GLOBAL_Q == 10
#define IQisqrt(A) IQ10isqrt(A)
#endif
#if GLOBAL_Q == 9
#define IQisqrt(A) IQ9isqrt(A)
#endif
#if GLOBAL_Q == 8
#define IQisqrt(A) IQ8isqrt(A)
#endif
#if GLOBAL_Q == 7
#define IQisqrt(A) IQ7isqrt(A)
#endif
#if GLOBAL_Q == 6
#define IQisqrt(A) IQ6isqrt(A)
#endif
#if GLOBAL_Q == 5
#define IQisqrt(A) IQ5isqrt(A)
#endif
#if GLOBAL_Q == 4
#define IQisqrt(A) IQ4isqrt(A)
#endif
#if GLOBAL_Q == 3
#define IQisqrt(A) IQ3isqrt(A)
#endif
#if GLOBAL_Q == 2
#define IQisqrt(A) IQ2isqrt(A)
#endif
#if GLOBAL_Q == 1
#define IQisqrt(A) IQ1isqrt(A)
#endif

extern int32_t IQ30exp(int32_t A);
extern int32_t IQ29exp(int32_t A);
extern int32_t IQ28exp(int32_t A);
extern int32_t IQ27exp(int32_t A);
extern int32_t IQ26exp(int32_t A);
extern int32_t IQ25exp(int32_t A);
extern int32_t IQ24exp(int32_t A);
extern int32_t IQ23exp(int32_t A);
extern int32_t IQ22exp(int32_t A);
extern int32_t IQ21exp(int32_t A);
extern int32_t IQ20exp(int32_t A);
extern int32_t IQ19exp(int32_t A);
extern int32_t IQ18exp(int32_t A);
extern int32_t IQ17exp(int32_t A);
extern int32_t IQ16exp(int32_t A);
extern int32_t IQ15exp(int32_t A);
extern int32_t IQ14exp(int32_t A);
extern int32_t IQ13exp(int32_t A);
extern int32_t IQ12exp(int32_t A);
extern int32_t IQ11exp(int32_t A);
extern int32_t IQ10exp(int32_t A);
extern int32_t IQ9exp(int32_t A);
extern int32_t IQ8exp(int32_t A);
extern int32_t IQ7exp(int32_t A);
extern int32_t IQ6exp(int32_t A);
extern int32_t IQ5exp(int32_t A);
extern int32_t IQ4exp(int32_t A);
extern int32_t IQ3exp(int32_t A);
extern int32_t IQ2exp(int32_t A);
extern int32_t IQ1exp(int32_t A);
/*******************************************************************************
* Function Name  : IQexp
* Description    : IQ格式数以e为底的指数函数:e^A
* Input          : 参数A为IQ格式的数
* Return         : 返回A以e为底的指数值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQexp(A) IQ30exp(A)
#endif
#if GLOBAL_Q == 29
#define IQexp(A) IQ29exp(A)
#endif
#if GLOBAL_Q == 28
#define IQexp(A) IQ28exp(A)
#endif
#if GLOBAL_Q == 27
#define IQexp(A) IQ27exp(A)
#endif
#if GLOBAL_Q == 26
#define IQexp(A) IQ26exp(A)
#endif
#if GLOBAL_Q == 25
#define IQexp(A) IQ25exp(A)
#endif
#if GLOBAL_Q == 24
#define IQexp(A) IQ24exp(A)
#endif
#if GLOBAL_Q == 23
#define IQexp(A) IQ23exp(A)
#endif
#if GLOBAL_Q == 22
#define IQexp(A) IQ22exp(A)
#endif
#if GLOBAL_Q == 21
#define IQexp(A) IQ21exp(A)
#endif
#if GLOBAL_Q == 20
#define IQexp(A) IQ20exp(A)
#endif
#if GLOBAL_Q == 19
#define IQexp(A) IQ19exp(A)
#endif
#if GLOBAL_Q == 18
#define IQexp(A) IQ18exp(A)
#endif
#if GLOBAL_Q == 17
#define IQexp(A) IQ17exp(A)
#endif
#if GLOBAL_Q == 16
#define IQexp(A) IQ16exp(A)
#endif
#if GLOBAL_Q == 15
#define IQexp(A) IQ15exp(A)
#endif
#if GLOBAL_Q == 14
#define IQexp(A) IQ14exp(A)
#endif
#if GLOBAL_Q == 13
#define IQexp(A) IQ13exp(A)
#endif
#if GLOBAL_Q == 12
#define IQexp(A) IQ12exp(A)
#endif
#if GLOBAL_Q == 11
#define IQexp(A) IQ11exp(A)
#endif
#if GLOBAL_Q == 10
#define IQexp(A) IQ10exp(A)
#endif
#if GLOBAL_Q == 9
#define IQexp(A) IQ9exp(A)
#endif
#if GLOBAL_Q == 8
#define IQexp(A) IQ8exp(A)
#endif
#if GLOBAL_Q == 7
#define IQexp(A) IQ7exp(A)
#endif
#if GLOBAL_Q == 6
#define IQexp(A) IQ6exp(A)
#endif
#if GLOBAL_Q == 5
#define IQexp(A) IQ5exp(A)
#endif
#if GLOBAL_Q == 4
#define IQexp(A) IQ4exp(A)
#endif
#if GLOBAL_Q == 3
#define IQexp(A) IQ3exp(A)
#endif
#if GLOBAL_Q == 2
#define IQexp(A) IQ2exp(A)
#endif
#if GLOBAL_Q == 1
#define IQexp(A) IQ1exp(A)
#endif

extern int32_t IQ30exp2(int32_t A);
extern int32_t IQ29exp2(int32_t A);
extern int32_t IQ28exp2(int32_t A);
extern int32_t IQ27exp2(int32_t A);
extern int32_t IQ26exp2(int32_t A);
extern int32_t IQ25exp2(int32_t A);
extern int32_t IQ24exp2(int32_t A);
extern int32_t IQ23exp2(int32_t A);
extern int32_t IQ22exp2(int32_t A);
extern int32_t IQ21exp2(int32_t A);
extern int32_t IQ20exp2(int32_t A);
extern int32_t IQ19exp2(int32_t A);
extern int32_t IQ18exp2(int32_t A);
extern int32_t IQ17exp2(int32_t A);
extern int32_t IQ16exp2(int32_t A);
extern int32_t IQ15exp2(int32_t A);
extern int32_t IQ14exp2(int32_t A);
extern int32_t IQ13exp2(int32_t A);
extern int32_t IQ12exp2(int32_t A);
extern int32_t IQ11exp2(int32_t A);
extern int32_t IQ10exp2(int32_t A);
extern int32_t IQ9exp2(int32_t A);
extern int32_t IQ8exp2(int32_t A);
extern int32_t IQ7exp2(int32_t A);
extern int32_t IQ6exp2(int32_t A);
extern int32_t IQ5exp2(int32_t A);
extern int32_t IQ4exp2(int32_t A);
extern int32_t IQ3exp2(int32_t A);
extern int32_t IQ2exp2(int32_t A);
extern int32_t IQ1exp2(int32_t A);
/*******************************************************************************
* Function Name  : IQexp2
* Description    : IQ格式数以2为底的指数函数:2^A
* Input          : 参数A为IQ格式的数
* Return         : 返回A以2为底的指数值，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQexp2(A) IQ30exp2(A)
#endif
#if GLOBAL_Q == 29
#define IQexp2(A) IQ29exp2(A)
#endif
#if GLOBAL_Q == 28
#define IQexp2(A) IQ28exp2(A)
#endif
#if GLOBAL_Q == 27
#define IQexp2(A) IQ27exp2(A)
#endif
#if GLOBAL_Q == 26
#define IQexp2(A) IQ26exp2(A)
#endif
#if GLOBAL_Q == 25
#define IQexp2(A) IQ25exp2(A)
#endif
#if GLOBAL_Q == 24
#define IQexp2(A) IQ24exp2(A)
#endif
#if GLOBAL_Q == 23
#define IQexp2(A) IQ23exp2(A)
#endif
#if GLOBAL_Q == 22
#define IQexp2(A) IQ22exp2(A)
#endif
#if GLOBAL_Q == 21
#define IQexp2(A) IQ21exp2(A)
#endif
#if GLOBAL_Q == 20
#define IQexp2(A) IQ20exp2(A)
#endif
#if GLOBAL_Q == 19
#define IQexp2(A) IQ19exp2(A)
#endif
#if GLOBAL_Q == 18
#define IQexp2(A) IQ18exp2(A)
#endif
#if GLOBAL_Q == 17
#define IQexp2(A) IQ17exp2(A)
#endif
#if GLOBAL_Q == 16
#define IQexp2(A) IQ16exp2(A)
#endif
#if GLOBAL_Q == 15
#define IQexp2(A) IQ15exp2(A)
#endif
#if GLOBAL_Q == 14
#define IQexp2(A) IQ14exp2(A)
#endif
#if GLOBAL_Q == 13
#define IQexp2(A) IQ13exp2(A)
#endif
#if GLOBAL_Q == 12
#define IQexp2(A) IQ12exp2(A)
#endif
#if GLOBAL_Q == 11
#define IQexp2(A) IQ11exp2(A)
#endif
#if GLOBAL_Q == 10
#define IQexp2(A) IQ10exp2(A)
#endif
#if GLOBAL_Q == 9
#define IQexp2(A) IQ9exp2(A)
#endif
#if GLOBAL_Q == 8
#define IQexp2(A) IQ8exp2(A)
#endif
#if GLOBAL_Q == 7
#define IQexp2(A) IQ7exp2(A)
#endif
#if GLOBAL_Q == 6
#define IQexp2(A) IQ6exp2(A)
#endif
#if GLOBAL_Q == 5
#define IQexp2(A) IQ5exp2(A)
#endif
#if GLOBAL_Q == 4
#define IQexp2(A) IQ4exp2(A)
#endif
#if GLOBAL_Q == 3
#define IQexp2(A) IQ3exp2(A)
#endif
#if GLOBAL_Q == 2
#define IQexp2(A) IQ2exp2(A)
#endif
#if GLOBAL_Q == 1
#define IQexp2(A) IQ1exp2(A)
#endif

#define IQ30int(A) ((A) >> 30)
#define IQ29int(A) ((A) >> 29)
#define IQ28int(A) ((A) >> 28)
#define IQ27int(A) ((A) >> 27)
#define IQ26int(A) ((A) >> 26)
#define IQ25int(A) ((A) >> 25)
#define IQ24int(A) ((A) >> 24)
#define IQ23int(A) ((A) >> 23)
#define IQ22int(A) ((A) >> 22)
#define IQ21int(A) ((A) >> 21)
#define IQ20int(A) ((A) >> 20)
#define IQ19int(A) ((A) >> 19)
#define IQ18int(A) ((A) >> 18)
#define IQ17int(A) ((A) >> 17)
#define IQ16int(A) ((A) >> 16)
#define IQ15int(A) ((A) >> 15)
#define IQ14int(A) ((A) >> 14)
#define IQ13int(A) ((A) >> 13)
#define IQ12int(A) ((A) >> 12)
#define IQ11int(A) ((A) >> 11)
#define IQ10int(A) ((A) >> 10)
#define IQ9int(A) ((A) >> 9)
#define IQ8int(A) ((A) >> 8)
#define IQ7int(A) ((A) >> 7)
#define IQ6int(A) ((A) >> 6)
#define IQ5int(A) ((A) >> 5)
#define IQ4int(A) ((A) >> 4)
#define IQ3int(A) ((A) >> 3)
#define IQ2int(A) ((A) >> 2)
#define IQ1int(A) ((A) >> 1)
/*******************************************************************************
* Function Name  : IQint
* Description    : 计算IQ格式数的整数部分
* Input          : 参数A为IQ格式的数
* Return         : 返回A整数部分
*******************************************************************************/
#define IQint(A) ((A) >> GLOBAL_Q)

extern int32_t IQ30frac(int32_t A);
extern int32_t IQ29frac(int32_t A);
extern int32_t IQ28frac(int32_t A);
extern int32_t IQ27frac(int32_t A);
extern int32_t IQ26frac(int32_t A);
extern int32_t IQ25frac(int32_t A);
extern int32_t IQ24frac(int32_t A);
extern int32_t IQ23frac(int32_t A);
extern int32_t IQ22frac(int32_t A);
extern int32_t IQ21frac(int32_t A);
extern int32_t IQ20frac(int32_t A);
extern int32_t IQ19frac(int32_t A);
extern int32_t IQ18frac(int32_t A);
extern int32_t IQ17frac(int32_t A);
extern int32_t IQ16frac(int32_t A);
extern int32_t IQ15frac(int32_t A);
extern int32_t IQ14frac(int32_t A);
extern int32_t IQ13frac(int32_t A);
extern int32_t IQ12frac(int32_t A);
extern int32_t IQ11frac(int32_t A);
extern int32_t IQ10frac(int32_t A);
extern int32_t IQ9frac(int32_t A);
extern int32_t IQ8frac(int32_t A);
extern int32_t IQ7frac(int32_t A);
extern int32_t IQ6frac(int32_t A);
extern int32_t IQ5frac(int32_t A);
extern int32_t IQ4frac(int32_t A);
extern int32_t IQ3frac(int32_t A);
extern int32_t IQ2frac(int32_t A);
extern int32_t IQ1frac(int32_t A);
/*******************************************************************************
* Function Name  : IQfrac
* Description    : 计算IQ格式数的小数部分
* Input          : 参数A为IQ格式的数
* Return         : 返回A小数部分，与参数的IQ格式相同
*******************************************************************************/
#if GLOBAL_Q == 30
#define IQfrac(A) IQ30frac(A)
#endif
#if GLOBAL_Q == 29
#define IQfrac(A) IQ29frac(A)
#endif
#if GLOBAL_Q == 28
#define IQfrac(A) IQ28frac(A)
#endif
#if GLOBAL_Q == 27
#define IQfrac(A) IQ27frac(A)
#endif
#if GLOBAL_Q == 26
#define IQfrac(A) IQ26frac(A)
#endif
#if GLOBAL_Q == 25
#define IQfrac(A) IQ25frac(A)
#endif
#if GLOBAL_Q == 24
#define IQfrac(A) IQ24frac(A)
#endif
#if GLOBAL_Q == 23
#define IQfrac(A) IQ23frac(A)
#endif
#if GLOBAL_Q == 22
#define IQfrac(A) IQ22frac(A)
#endif
#if GLOBAL_Q == 21
#define IQfrac(A) IQ21frac(A)
#endif
#if GLOBAL_Q == 20
#define IQfrac(A) IQ20frac(A)
#endif
#if GLOBAL_Q == 19
#define IQfrac(A) IQ19frac(A)
#endif
#if GLOBAL_Q == 18
#define IQfrac(A) IQ18frac(A)
#endif
#if GLOBAL_Q == 17
#define IQfrac(A) IQ17frac(A)
#endif
#if GLOBAL_Q == 16
#define IQfrac(A) IQ16frac(A)
#endif
#if GLOBAL_Q == 15
#define IQfrac(A) IQ15frac(A)
#endif
#if GLOBAL_Q == 14
#define IQfrac(A) IQ14frac(A)
#endif
#if GLOBAL_Q == 13
#define IQfrac(A) IQ13frac(A)
#endif
#if GLOBAL_Q == 12
#define IQfrac(A) IQ12frac(A)
#endif
#if GLOBAL_Q == 11
#define IQfrac(A) IQ11frac(A)
#endif
#if GLOBAL_Q == 10
#define IQfrac(A) IQ10frac(A)
#endif
#if GLOBAL_Q == 9
#define IQfrac(A) IQ9frac(A)
#endif
#if GLOBAL_Q == 8
#define IQfrac(A) IQ8frac(A)
#endif
#if GLOBAL_Q == 7
#define IQfrac(A) IQ7frac(A)
#endif
#if GLOBAL_Q == 6
#define IQfrac(A) IQ6frac(A)
#endif
#if GLOBAL_Q == 5
#define IQfrac(A) IQ5frac(A)
#endif
#if GLOBAL_Q == 4
#define IQfrac(A) IQ4frac(A)
#endif
#if GLOBAL_Q == 3
#define IQfrac(A) IQ3frac(A)
#endif
#if GLOBAL_Q == 2
#define IQfrac(A) IQ2frac(A)
#endif
#if GLOBAL_Q == 1
#define IQfrac(A) IQ1frac(A)
#endif

/*******************************************************************************
* Function Name  : IQabs
* Description    : IQ格式数的绝对值函数:|A|
* Input          : 参数A为IQ格式的数
* Return         : 返回A的绝对值，与参数的IQ格式相同
*******************************************************************************/
#define IQabs(A) (((A) < 0) ? -(A) : (A))

#ifdef __cplusplus
}
#endif

#endif

#endif  //MINIFOC_SYSTEM_IQMATH_H_
