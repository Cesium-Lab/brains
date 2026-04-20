#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "uart.h"

// Will call `uart_init()` and `uart_begin()`
int print_begin(uart_t* uart);

int putk(const char* cstr);

void emit_num(uint32_t c, uint32_t base, uint8_t upper_hex);



/*
Supports formats

- d for int32_t or less
- u for uint32_t or less
- b for binary
- c for char
- x for lowercase hex
- X for uppercase hex
- 0x for lowercase hex with '0x'
- 0X for uppercase hex with '0x'

- s or S for cstring
- % for escaping 

Will support in the future:
- f for floats

*/
int printk(const char *fmt, ...);

int vprintk(const char* chars, va_list format);



#endif