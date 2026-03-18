/* Ignite */
#ifndef UART_H
#define UART_H

#define UART_BASE 0x10000000
#define UART_THR (UART_BASE+0)
#define UART_RBR (UART_BASE+0)
#define UART_LSR (UART_BASE+5)
#define UART_LSR_DR (1<<0)
#define UART_LSR_ETHR (1<<5)

#define read_reg8(reg)             (*(volatile unsigned char *) (reg))
#define write_reg8(reg, c)         (*(volatile unsigned char *) (reg)) = (c)
#define set_reg_bits8(reg, mask)   write_reg8(reg, read_reg8(reg) |  (mask))
#define clear_reg_bits8(reg, mask) write_reg8(reg, read_reg8(reg) & ~(mask))

#define UART_TX_BUSY()   !(read_reg8(UART_LSR) & UART_LSR_ETHR)
#define UART_RX_AVAIL()   (read_reg8(UART_LSR) & UART_LSR_DR)
#define UART_TX(c)       write_reg8(UART_THR, (c))
#define UART_RX()        read_reg8(UART_RBR)

void uart_init();
void uart_transmit(const unsigned char c);
unsigned char uart_receive();

#endif /* UART_H */
