//
// Created by Lao·Zhu on 2021/9/5.
//

#include "flash.h"
#include "gd32f1x0.h"
#include "config.h"

/*!
    \brief      erase fmc page in last sector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_erase_pages(void) {
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
    \brief      program fmc word to address
    \param[in]  addr: address to write to
    \param[in]  data: data to be written
    \param[out] none
    \retval     none
*/
void fmc_program(unsigned int addr, unsigned int data) {
    /* unlock the flash program/erase controller */
    fmc_unlock();
    /* program flash */
    fmc_word_program(addr + FMC_WRITE_START_ADDR, data);
    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* lock the main FMC after the program operation */
    fmc_lock();
}

/*!
    \brief      read fmc word from address
    \param[in]  addr: address to read from
    \param[out] none
    \retval     data read from address
*/
unsigned int fmc_readword(unsigned int addr) {
    /* redirect the address to access memory */
    addr = FMC_WRITE_START_ADDR + addr;
    unsigned int *ptrd = (unsigned int *) addr;
    return (*ptrd);
}
