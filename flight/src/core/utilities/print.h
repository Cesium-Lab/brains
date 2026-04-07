// https://github.com/Cesium-Lab/csos/blob/main/F042/libc/print.c


#pragma once

#include <stdint.h>
#include <stdarg.h>
#include "core/isolation-layer/peripherals/uart.h"


namespace Cesium {

// C++ version of your old global print utils.
// Owns nothing 
class Print {
  public:

    Print(Uart& uart);

    bool begin();

    // bool ready();

    int putk(const char* cstr);

    // upper_hex for hex digits, false for lowercase, true for uppercase
    uint32_t emit_num(uint32_t num, uint32_t base, bool upper_hex = false);


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
    int printk(const char* fmt, ...);
    int vprintk(const char* fmt, va_list args);

    // Optional accessor
    const Uart& uart() const { return _uart; }

  private:
    Uart& _uart;
};

} // namespace Cesium