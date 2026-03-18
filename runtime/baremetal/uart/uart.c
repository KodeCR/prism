/* Ignite */
#include "uart.h"

void uart_init() {
}

void uart_transmit(const unsigned char c) {
    while(UART_TX_BUSY());
    UART_TX(c);
}

unsigned char uart_receive() {
    while(!UART_RX_AVAIL());
    return UART_RX();
}