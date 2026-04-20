#ifndef __UART_H__
#define __UART_H__
// Reference Manual Section 8 p.149-165 

#include <stdint.h>


typedef struct {
    uint32_t instance; // Like UART1 or UART2
    uint32_t base_reg;
    uint32_t baud;
} uart_t;

// I think
extern uart_t UART1;
extern uart_t UART2;

// ****************************************************************************************************
//                  Setup
// ****************************************************************************************************

// Enables clock and sets defaults
int uart_init(uart_t* uart);

// TODO: init vs begin?
// initialize to baud=115,200
int uart_begin(uart_t* uart);

// Calculation on 27.5.4 p.716
// baud = f_clk / USARTDIV
int uart_brr_from_clk(uint32_t fclk, uint32_t baud);

// disable
// void uart_disable(uart_t* uart); // TODO

// ****************************************************************************************************
//                  TX and RX
// ****************************************************************************************************

// get one byte from the uart. NO ERROR CODES
uint8_t uart_get8(uart_t* uart);

// put one byte on the uart:
// returns < 0 on error.
int uart_put8(uart_t* uart, uint8_t c);
uint32_t uart_put_cstr(uart_t* uart, const char* cstr);
uint32_t uart_putn(uart_t* uart, void* buffer, uint8_t nbytes);
// uint32_t uart_put_hex(uart_t* uart, uint8_t h);

// returns -1 if no byte, the value otherwise.
// int uart_get8_async(uart_t* uart);

// -1 for error, 0 = no data, or bytes returned.
int uart_has_data(uart_t* uart);

// 0 = no space, 1 = space for at least 1 byte
// int uart_can_put8(uart_t* uart);
// int uart_can_putc(uart_t* uart);

// flush out the tx fifo
// void uart_flush_tx(uart_t* uart);

#endif