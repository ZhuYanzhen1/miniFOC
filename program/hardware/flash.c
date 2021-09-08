//
// Created by Lao·Zhu on 2021/9/5.
//

#include "flash.h"
#include "gd32f1x0.h"
#include "config.h"

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
