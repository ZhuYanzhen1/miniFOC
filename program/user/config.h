//
// Created by LaoZhu on 2023/6/27.
//

#ifndef MINIFOC_USER_CONFIG_H_
#define MINIFOC_USER_CONFIG_H_

/*! \brief set BLDC polar pairs to 7 */
#define POLAR_PAIRS 7
/*! \brief MT6701 resolution is 2^14 = 16384 */
#define ENCODER_RESO 16384

#define CALIBRATE_TORQUE 0.2

#define TIM1_PRESCALER 1
#define PWM_FREQUENCY 20000

#define UART_RECEIVE_BUFFER_SIZE 256
#define UART_TRANSMIT_BUFFER_SIZE 32
#define UART_TRANSMIT_BUFFER_NUM 8

/*! \brief mechanical angle conversion factor */
#define MECHANGLE_COEFFICIENT (6.2831854f / ENCODER_RESO)
/*! \brief electric angle conversion factor */
#define ELECANGLE_COEFFICIENT ((6.2831854f * POLAR_PAIRS) / ENCODER_RESO)

/*!
  \struct FOC_Structure_t
  \brief  structure of FOC algorithm
 */
typedef struct {
    uint16_t encoder_data;     ///< origin value read from encoder
    int32_t electric_angle;    ///< electric angle read form encoder
    int32_t mechanical_angle;  ///< mechanical angle read form encoder
} foc_structure_t;
extern foc_structure_t foc;

#endif  //MINIFOC_USER_CONFIG_H_
