//
// Created by LaoZhu on 2023/10/15.
//

#include "mdtp_process.h"
#include "string.h"
#include "uart.h"

static unsigned char mdtp_receive_status = 0;
static unsigned char mdtp_receive_number_counter = 0;
static unsigned char mdtp_receive_data_buffer[10] = {0};

void __attribute__((weak)) mdtp_callback_handler(uint8_t pid, uint8_t* buffer) {}

void uart_receive_callback(const unsigned char* buffer, unsigned char length) {
    for (int counter = 0; counter < length; ++counter) { /* data receiving finite state machine */
        switch (mdtp_receive_status) {
            case 0:
                /* judge whether the packet header is received */
                if (buffer[counter] == 0xAA) {
                    /* enter the receive state */
                    mdtp_receive_status = 1;
                    /* clear receive array counter */
                    mdtp_receive_number_counter = 0;
                    /* clear the value in the buffer array */
                    memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
                }
                break;
            case 1:
                /* judge whether the end of the packet is mistakenly recognized as the header */
                if (buffer[counter] == 0xAA && mdtp_receive_number_counter != 0) {
                    /* an unexpected data had been received */
                    /* reset to receive start of package state */
                    mdtp_receive_status = 0;
                    /* clear receive array counter */
                    mdtp_receive_number_counter = 0;
                    /* clear the value in the buffer array */
                    memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
                } else if (buffer[counter] != 0xAA) {
                    /* judge whether the reception is completed or the error data is received */
                    if (mdtp_receive_number_counter < 10) {
                        /* receive the data into the array in turn */
                        mdtp_receive_data_buffer[mdtp_receive_number_counter] = buffer[counter];
                        mdtp_receive_number_counter = mdtp_receive_number_counter + 1;
                        if (mdtp_receive_number_counter == 10)
                            mdtp_receive_status = 2;
                    }
                }
                break;
            case 2:
                if (buffer[counter] == 0xAA) {
                    /* ready to receive the next packet */
                    mdtp_receive_status = 0;
                    /* verify whether the pid byte is correct*/
                    if ((mdtp_receive_data_buffer[0] >> 4) == (~mdtp_receive_data_buffer[0] & 0x0f)) {
                        static unsigned char tmp_rcv_buffer[8], adj_counter = 0;
                        /* judge whether the adjust frame is all 0xAA */
                        if (mdtp_receive_data_buffer[8] == 0xA5 && mdtp_receive_data_buffer[9] == 0x80)
                            /* set adjust frame to with 0xAA */
                            mdtp_receive_data_buffer[9] = 0xAA;
                        /* traverse the data byte to be adjusted */
                        for (adj_counter = 0; adj_counter < 8; ++adj_counter) {
                            /* judge whether the adjustment bit is 1 */
                            if (((mdtp_receive_data_buffer[9] >> adj_counter) & 0x01) == 0x01)
                                /* fill the data byte with 0xAA */
                                tmp_rcv_buffer[adj_counter] = 0xAA;
                            else
                                /* copy data directly to the receiving array */
                                tmp_rcv_buffer[adj_counter] = mdtp_receive_data_buffer[adj_counter + 1];
                        }
                        /* call user callback function to complete the next step */
                        mdtp_callback_handler(mdtp_receive_data_buffer[0] >> 4, tmp_rcv_buffer);
                    }
                } else { /* an unexpected data had been received */
                    /* reset to receive start of package state */
                    mdtp_receive_status = 0;
                    /* clear receive array counter */
                    mdtp_receive_number_counter = 0;
                    /* clear the value in the buffer array */
                    memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
                }
                break;
            default:
                /* reset to receive start of package state */
                mdtp_receive_status = 0;
                /* clear receive array counter */
                mdtp_receive_number_counter = 0;
                /* clear the value in the buffer array */
                memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
                break;
        }
    }
}

void mdtp_data_transmit(uint8_t pid, const uint8_t* data) {
    uint8_t temp_buf[12] = {0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA};
    /* traverse the array to determine whether there are bytes to be adjusted */
    for (uint8_t mdtp_pack_counter = 0; mdtp_pack_counter < 8; mdtp_pack_counter++) {
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
    uart_transmit(temp_buf, 12);
}
