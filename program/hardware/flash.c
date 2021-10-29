/**************************************************************************//**
  \file     flash.c
  \brief    this file contains the code implementation of on-chip flash
            reading, writing and erasing, as well as storing and reading
            user configurations.
  \author   Lao·Zhu
  \version  V1.0.2
  \date     29. October 2021
 ******************************************************************************/

#include "main.h"

/*!
    \brief  program all parameters to flash
    \retval none
*/
void flash_write_parameters(void) {
    unsigned int buffer[11] = {machine_angle_offset, phase_sequence, 0x00000000UL, 0x00000000UL, 0x00000000UL,
                               0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL};
    buffer[2] = float_to_int32(speed_pid_handler.kp);
    buffer[3] = float_to_int32(speed_pid_handler.ki);
    buffer[4] = float_to_int32(speed_pid_handler.kd);
    buffer[5] = float_to_int32(speed_pid_handler.sum_maximum);
    buffer[6] = float_to_int32(angle_pid_handler.kp);
    buffer[7] = float_to_int32(angle_pid_handler.ki);
    buffer[8] = float_to_int32(angle_pid_handler.kd);
    buffer[9] = float_to_int32(angle_pid_handler.sum_maximum);
    buffer[10] = flash_read_word(0x00000040UL);
    flash_erase_page();
    flash_program_word(0x00000000UL, buffer, 10);
}

/*!
    \brief  read all parameters from flash
    \retval none
*/
void flash_read_parameters(void) {
    machine_angle_offset = flash_read_word(0x00000000UL);
    phase_sequence = flash_read_word(0x00000004UL);
    speed_pid_handler.kp = int32_to_float(flash_read_word(0x00000008UL));
    speed_pid_handler.ki = int32_to_float(flash_read_word(0x00000012UL));
    speed_pid_handler.kd = int32_to_float(flash_read_word(0x00000016UL));
    speed_pid_handler.sum_maximum = int32_to_float(flash_read_word(0x00000020UL));
    angle_pid_handler.kp = int32_to_float(flash_read_word(0x00000024UL));
    angle_pid_handler.ki = int32_to_float(flash_read_word(0x00000028UL));
    angle_pid_handler.kd = int32_to_float(flash_read_word(0x00000032UL));
    angle_pid_handler.sum_maximum = int32_to_float(flash_read_word(0x00000036UL));
    if (machine_angle_offset > 4096 || phase_sequence > 1) {
        led_on();
        while (1);
    }
    if (flash_read_word(0x00000040UL) != 0xA5A5A5A5UL)
        pid_parameter_available_flag = 0;
}

/*!
    \brief  erase flash page in last sector
    \retval none
*/
void flash_erase_page(void) {
    /* unlock the flash program/erase controller */
    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    /* erase the flash page */
    fmc_page_erase(FMC_WRITE_START_ADDR);
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    /* lock the main FMC after the erase operation */
    fmc_lock();
}

/*!
    \brief      program flash word to address
    \param[in]  addr: address to write to
    \param[in]  data: data to be written
    \param[in]  counter: number of bytes to be written to flash
    \retval none
*/
void flash_program_word(unsigned int addr, unsigned int *data, unsigned short counter) {
    /* unlock the flash program/erase controller */
    fmc_unlock();

    /* program flash */
    for (unsigned short data_cnt = 0; data_cnt < counter; data_cnt++) {
        fmc_word_program(addr + FMC_WRITE_START_ADDR + 4 * data_cnt, data[data_cnt]);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    }

    /* lock the main FMC after the program operation */
    fmc_lock();
}

/*!
    \brief      read flash word from address
    \param[in]  addr: address to read from
    \retval     data read from address
*/
unsigned int flash_read_word(unsigned int addr) {
    /* redirect the address to access memory */
    addr = FMC_WRITE_START_ADDR + addr;
    unsigned int *ptrd = (unsigned int *) addr;
    return (*ptrd);
}
