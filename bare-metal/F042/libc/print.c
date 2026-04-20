#include "print.h"
#include "stm32.h"
#include "uart.h"

uart_t* _stdout;


int print_begin(uart_t* uart) {
    if (!uart) return STM32_ERROR;
    _stdout = uart;

    if (uart_init(uart) != STM32_SUCCESS) { // For clocks
        return STM32_ERROR;
    }

    if (uart_begin(uart) != STM32_SUCCESS) { // Starting up regs 
        return STM32_ERROR;
    }

    return STM32_SUCCESS;
}


// Thanks dawson
void emit_num(uint32_t num, uint32_t base, uint8_t upper_hex) {
    char buf[33]; // 33 = 32 + 1(bc uint32_t in base 2)
    char* p = buf;

    switch(base) {
    case 2:
        do {
            *p++ = "01"[num % 2];
        } while(num /= 2);
        break;
    case 10:
        do {
            *p++ = "0123456789"[num % 10];
        } while(num /= 10);
        break;
    case 16: // Take care of upper hex
        if (upper_hex)
            do {    
                *p++ = "0123456789ABCDEF"[num % 16];
            } while(num /= 16);
        else 
            do {    
                *p++ = "0123456789abcdef"[num % 16];
            } while(num /= 16);
            
        break;
    default: 
        // panic("invalid base=%d\n", base);
        return;
    }

    // buffered in reverse, so emit backwards
    while(p > buf) {
        p--;
        uart_put8(_stdout, *p);
    }
}

int printk(const char *fmt, ...) {

    if(!_stdout)
        return STM32_ERROR;

    va_list ap;
    va_start(ap, fmt);
        int res = vprintk(fmt, ap);
    va_end(ap);

    return res;
}

int vprintk(const char* format, va_list args) {

    uint32_t i = 0;
    for(; format[i] != 0x00; i++) {

        // If an escape code
        if (format[i] != '%') {
            uart_put8(_stdout, format[i]);
            continue;
        }
        i++;
        // - % for escaping 
        if (format[i] == '%') {
            uart_put8(_stdout, format[i]);
            continue;
        }

        
        switch (format[i]) {

        case 'c': // - c for char
            uart_put8(_stdout, va_arg(args, int));
            break;

        case 'b': // - b for binary
            emit_num(va_arg(args, uint32_t), 2, 0);
            break;

        case 'u': // - u for unsigned int
            emit_num(va_arg(args, uint32_t), 10, 0);
            break;

        case 'x': // - x for lowercase hex
            emit_num(va_arg(args, uint32_t), 16, 0);
            break;

        case 'X': // - X for uppercase hex
            emit_num(va_arg(args, uint32_t), 16, 1);
            break;

        case 's': // - s or S for cstring
        case 'S':
            for(char* c = va_arg(args, char*); *c; c++) 
                uart_put8(_stdout, *c);
            break;


        case '0': // 0x or 0X
            i++; 
            if (format[i] == 'x') { // - 0x for lowercase hex with '0x'
                uart_put8(_stdout, '0');
                uart_put8(_stdout, 'x');
                emit_num(va_arg(args, uint32_t), 16, 0);
                break;
            } else if (format[i] == 'X') { // - 0X for uppercase hex with '0x'
                uart_put8(_stdout, '0');
                uart_put8(_stdout, 'x');
                emit_num(va_arg(args, uint32_t), 16, 1);
                break;
            } else {
                uart_put_cstr(_stdout, "BAD CSTRING HEX FORMAT\n\r");
                return -1;
            }
        case 'd':
            int d = va_arg(args, int);
            if (d < 0) {
                uart_put8(_stdout, '-');
                d = -d;
            }
            emit_num(d, 10, 0);
            break;

        default:
            uart_put_cstr(_stdout, "BAD CSTRING FORMAT\n\r"); while(1) ;
        }
    }
    
    return STM32_SUCCESS;
}



