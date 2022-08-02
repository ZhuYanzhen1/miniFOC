/**************************************************************************//**
  \file     encoder.c
  \brief    this file contains the code implementation of angle acquisition
            and initialization functions of sc60228 and sc60224.
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "encoder.h"
#include "spi.h"
#include "gd32f1x0.h"
#include "foc.h"
#include "timer.h"
#include "system.h"
#include "config.h"
#include "filter.h"

/*!
    \brief mechanical angle offset, which is used to align the mechanical
           angle with the zero point of the electrical angle.
*/
volatile unsigned short machine_angle_offset = 0;
/*!
    \brief the mechanical angle at the last moment is used to calculate
           the angle differential value and realize the angle measurement
           function.
*/
volatile static unsigned short last_mechanical_angle = 0;
/*!
    \brief the total mechanical angle since power on is used to calculate
           the angle integral value and realize the angle measurement function.
*/
volatile static long long total_machine_angle = 0;
/*!
    \brief the mechanical angle at the last moment is used to calculate
           the rotation speed of the motor rotor.
*/
volatile static long long systick_mechanical_angle_last = 0;

/*!
    \brief delay function for magnetic encoder
*/
void encoder_delay(void) {
    /* use loop functions to delay time */
    unsigned char delay_counter = 0xff;
    while (delay_counter)
        delay_counter--;
}

/*!
    \brief     read data from the register of the magnetic encoder
    \param[in] TxData: data to be sent to magnetic encoder
    \retval    data read from magnetic encoder
*/
unsigned short encoder_read_data(unsigned short TxData) {
    unsigned short data;

    /* pull down the CS pin and prepare to send data */
    gpio_bit_write(GPIOA, GPIO_PIN_4, RESET);
    encoder_delay();

    /* call SPI related functions to send and receive data */
    data = spi_readwrite_halfworld(TxData);
    encoder_delay();

    /* pull up CS pin to end sending data */
    gpio_bit_write(GPIOA, GPIO_PIN_4, SET);
    return data;
}

/*!
    \brief  read mechanical angle directly from encoder
    \retval register raw data reading back
*/
unsigned short encoder_get_mechanical_angle(void) {
    /* read back register raw data */
    unsigned short angle = encoder_read_data(0x0000) >> 4;

    /* statistical total rotation angle */
    total_machine_angle = total_machine_angle + angle - last_mechanical_angle;
    last_mechanical_angle = angle;

    /* returns the result of subtracting the offset. */
    return ((total_machine_angle - machine_angle_offset) % ENCODER_RESO);
}

/*!
    \brief  according to the electrical angle calculated from the mechanical angle,
            this function will call encoder_get_mechanical_angle() function.
    \retval register raw data reading back
*/
float encoder_get_electronic_angle(void) {
    /* read back the mechanical angle directly from the magnetic encoder */
    unsigned short tmp_mechanical_angle = encoder_get_mechanical_angle();

    /* calculate and update the mechanical angle and electric angle */
    FOC_Struct.mechanical_angle = (float) tmp_mechanical_angle * MECHANGLE_COEFFICIENT;
    float electric_angle = (float) (tmp_mechanical_angle % (ENCODER_RESO / POLAR_PAIRS)) * ELECANGLE_COEFFICIENT;
    return electric_angle;
}

/*!
    \brief called every 2 milliseconds to calculate the speed.
*/
void encoder_update_speed(void) {
    /* calculate the difference between this angle and the last angle */
    short tmp_mechanical_angle_velocity = (short) (total_machine_angle - systick_mechanical_angle_last);

    /* send it to low-pass filter for filtering to prevent PID high-frequency oscillation */
    FOC_Struct.rotate_speed =
        filter_update_value((Filter_Structure_t *) &velocity_filter, tmp_mechanical_angle_velocity);
    systick_mechanical_angle_last = total_machine_angle;
}

/*!
    \brief correct the mechanical angle zero deviation between the magnetic encoder and FOC.
*/
void encoder_zeroing(void) {
    float u, v, w;
    /* delay to wait for the power supply voltage to be normal */
    delayms(1000);

    /* set that there is only a magnetic field on the straight axis. */
    foc_calculate_dutycycle(0, CALI_TORQUE, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
    delayms(300);
    machine_angle_offset = 0;
    total_machine_angle = 0;

    /* read the angle at this time as the offset angle */
    machine_angle_offset = encoder_read_data(0x0000) >> 4;

    /* zero the torque in all directions to release the motor */
    foc_calculate_dutycycle(0, 0, 0, &u, &v, &w);
    update_pwm_dutycycle(u, v, w);
    delayms(300);
}
