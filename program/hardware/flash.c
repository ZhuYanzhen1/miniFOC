//
// Created by Lao·Zhu on 2021/9/5.
//

#include "main.h"

/*!
    \brief      program all parameters to flash
    \param[in]  none
    \param[out] none
    \retval     none
*/
void flash_write_parameters(void) {
    unsigned int buffer[2] = {machine_angle_offset, phase_sequence};
    flash_erase_page();
    flash_program_word(0x00000000UL, buffer, 2);
}

/*!
    \brief      read all parameters from flash
    \param[in]  none
    \param[out] none
    \retval     none
*/
void flash_read_parameters(void) {
    machine_angle_offset = flash_read_word(0x00000000UL);
    phase_sequence = flash_read_word(0x00000004UL);
    if (machine_angle_offset > 4096 || phase_sequence > 1) {
        led_on();
        while (1);
    }
}

/*!
    \brief      erase flash page in last sector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void flash_erase_page(void) {
    /* unlock the flash program/erase controller */
    fmc_unlock();
    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* erase the flash page */
    fmc_page_erase(FMC_WRITE_START_ADDR);
    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* lock the main FMC after the erase operation */
    fmc_lock();
}

/*!
    \brief      program flash word to address
    \param[in]  addr: address to write to
    \param[in]  data: data to be written
    \param[out] none
    \retval     none
*/
void flash_program_word(unsigned int addr, unsigned int *data, unsigned short counter) {
    /* unlock the flash program/erase controller */
    fmc_unlock();
    /* program flash */
    for (unsigned short data_cnt = 0; data_cnt < counter; data_cnt++) {
        fmc_word_program(addr + FMC_WRITE_START_ADDR + 4 * data_cnt, data[data_cnt]);
        /* clear all pending flags */
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    }
    /* lock the main FMC after the program operation */
    fmc_lock();
}

/*!
    \brief      read flash word from address
    \param[in]  addr: address to read from
    \param[out] none
    \retval     data read from address
*/
unsigned int flash_read_word(unsigned int addr) {
    /* redirect the address to access memory */
    addr = FMC_WRITE_START_ADDR + addr;
    unsigned int *ptrd = (unsigned int *) addr;
    return (*ptrd);
}
