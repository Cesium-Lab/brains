// https://github.com/Cesium-Lab/csos/blob/main/F042/libc/print.c


#pragma once

#include <stdint.h>
#include <stdarg.h>
#include "core/isolation-layer/peripherals/uart.h"

#include "core/isolation-layer/Eigen.h"


namespace Cesium {

// C++ version of your old global print utils.
// Owns nothing 
class Print {
  public:
    static constexpr uint8_t FLOAT_BUF_LEN = 50;

    Print(Uart& uart);

    bool begin();

    int putk(const char* cstr);
    uint32_t putfloat(float f, uint32_t base, bool upper_hex, uint32_t precision = 2);

    // upper_hex for hex digits, false for lowercase, true for uppercase
    uint32_t emit_num(uint32_t num, uint32_t base, bool upper_hex = false);

    template <int N>
    uint32_t emit_float_vec(const Cesium::VectorXf<N>& vec, uint32_t base = 10, bool upper_hex = false) {

        uint32_t count = _uart.transmit("[");

        // TODO: FIX THIS TO TAKE FLOATS AND MAKE SOME FUNCTION 
        for (uint32_t i = 0; i < N; i++) {
            count += putfloat(vec[i], base, upper_hex, 3); // default precision of 3

            if (i < N-1)
                count += _uart.transmit(", ");
        }

        count += _uart.transmit("]");

        return count;
    }

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
    - vf3/Vf3 for float vector (only length 3 for now)
    - vX3/vx3/Vx3/VX3 for hex vector (only length 3 for now)

    - s or S for cstring
    - % for escaping 

    Will support in the future:
    - f for floats

    */
    int printk(const char* fmt, ...);
    int vprintk(const char* fmt, va_list args);

    const Uart& uart() const { return _uart; }

  private:
    Uart& _uart;

    char _float_buf[FLOAT_BUF_LEN] = {};       // buffer to hold the formatted float
};

} // namespace Cesium