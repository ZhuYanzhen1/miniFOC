#include "main.h"

int main(void) {
    system_config();
    usart1_config();

    LOG("SystemClk:%lu\r\n", SystemCoreClock);
    LOG("This is printf example\r\n");

    while (1);
}
