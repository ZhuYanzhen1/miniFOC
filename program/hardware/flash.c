//
// Created by Lao·Zhu on 2021/9/5.
//

#include "flash.h"
#include "gd32f1x0.h"

#define FMC_WRITE_START_ADDR    ((uint32_t)0x08007C00U)     // use last 1kb flash to store data

/*!
    \brief      erase fmc pages in FMC_WRITE_START_ADDR
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_erase_pages(void) {
    uint32_t EraseCounter;
    /* unlock the flash program/erase controller */
    fmc_unlock();
    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* erase the flash page */
    fmc_page_erase(FMC_WRITE_START_ADDR);
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* lock the main FMC after the erase operation */
    fmc_lock();
}

/*!
    \brief      program fmc word by word from FMC_WRITE_START_ADDR to FMC_WRITE_END_ADDR
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_program(unsigned int addr, unsigned int data) {
    /* unlock the flash program/erase controller */
    fmc_unlock();
    /* program flash */
    fmc_word_program(addr + FMC_WRITE_START_ADDR, data);
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    /* lock the main FMC after the program operation */
    fmc_lock();
}

unsigned int fmc_readword(unsigned int addr) {
    addr = FMC_WRITE_START_ADDR + addr;
    unsigned int *ptrd = (unsigned int *) addr;
    return (*ptrd);
}
