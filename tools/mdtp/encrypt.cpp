//
// Created by Lao·Zhu on 2021/9/4.
//

#include "mainwindow.h"

/*!
    \brief      medium capacity data transmission protocol packing function
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \param[out]   none
    \retval     none
*/
void MainWindow::mdtp_data_transmit(unsigned char pid, const unsigned char *data) {
    unsigned char temp_buf[12] = {0xAA, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0xAA};
    unsigned char mdtp_pack_counter;
    /* traverse the array to determine whether there are bytes to be adjusted */
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 8; mdtp_pack_counter++) {
        /* judge whether this byte need to be adjusted */
        if (data[mdtp_pack_counter] == 0xAA) {
            temp_buf[2 + mdtp_pack_counter] = 0x00;
            /* modify the corresponding bit of the adjustment byte */
            temp_buf[10] = (temp_buf[10] | (1 << mdtp_pack_counter));
        } else
            /* copy data directly to transmit buffer array */
            temp_buf[2 + mdtp_pack_counter] = data[mdtp_pack_counter];
    }
    /* judge whether adjust frame is 0xAA */
    if (temp_buf[10] == 0xAA) {
        temp_buf[10] = 0x80;
        temp_buf[9] = 0xA5;
    }
    /* load self checking packet id byte */
    temp_buf[1] = pid << 4 | ((~pid) & 0x0f);
    /* transmit 12 bytes through general sendbyte function */
    serial->write((const char *)temp_buf, 12);
}
