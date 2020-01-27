#ifndef _UART_H
#define _UART_H

#ifndef _UART_C
#define _UART_C

extern void uart_config(unsigned int baud);
extern void uart_write(unsigned char *buf);
extern void uart_read(unsigned char *buf);
extern void uart_monitor();

extern bit rxd_flag;
extern bit rxd_overflow,rxd_complete;

#endif

#define RXD_MAX 30

#endif