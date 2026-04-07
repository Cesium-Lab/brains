#include <cstring>
#include "print.h"

namespace Cesium {

Print::Print(Uart& uart) : _uart{uart}, _float_buf{} {}

bool Print::begin() { return _uart.initialize(); }

int Print::putk(const char* cstr) {
    if (cstr == nullptr) return -1;
    return static_cast<int>(_uart.transmit(cstr));
}

uint32_t Print::putfloat(float f, uint32_t base, bool upper_hex, uint32_t precision) {

    memset(_float_buf, 0, FLOAT_BUF_LEN);

    uint32_t count = 0;

    if (base == 10) {
        // Format float into buffer (DO NOT COMPILE RELEASE WITH THIS, IT'S HUGE AND SLOW, BUT GOOD FOR DEBUGGING)
        // TODO: do the function myself (sort of a fun thing)
        snprintf(_float_buf, FLOAT_BUF_LEN, "%.*f", (int)precision, (double)f); // 3 decimal places
        // God cast is annoying but C++ style (maybe I shold do C style)
        return _uart.transmit(
            reinterpret_cast<const uint8_t*>(_float_buf), (uint32_t)strlen(_float_buf));
    }
    else if (base == 16) {
        uint8_t* float_bytes = reinterpret_cast<uint8_t*>(&f);
        count += _uart.transmit("0x"); // keep old behavior of always printing 0x for hex floats
        count += emit_num(float_bytes[3], 16, upper_hex);
        count += emit_num(float_bytes[2], 16, upper_hex);
        count += emit_num(float_bytes[1], 16, upper_hex);
        count += emit_num(float_bytes[0], 16, upper_hex);
    }
    else {
        count += _uart.transmit("BAD FLOAT BASE FORMAT\n");
    }

    return count;
}

// Thanks dawson
uint32_t Print::emit_num(uint32_t num, uint32_t base, bool upper_hex) {
    char buf[33]; // 33 = 32 + 1(bc uint32_t in base 2)
    char* p = buf;

    switch (base) {
    case 2:
        do { *p++ = "01"[num % 2]; } while (num /= 2);
        break;
    case 10:
        do { *p++ = "0123456789"[num % 10]; } while (num /= 10);
        break;
    case 16: // Take care of upper hex
        // if (hex_leading_zero && (num < 16)) { // leading zeros
        //     *p++ = '0';
        // }
        if (upper_hex)
            do { *p++ = "0123456789ABCDEF"[num % 16]; } while (num /= 16);
        else
            do { *p++ = "0123456789abcdef"[num % 16]; } while (num /= 16);
        break;
    default:
        // panic("invalid base=%d\n", base);
        return 0;
    }

    uint32_t nbytes = static_cast<uint32_t>(p - buf);

    while (p > buf) {
        --p;
        nbytes += _uart.transmit(*p);
    }

    return nbytes;
}

int Print::printk(const char* fmt, ...) {
    if (!fmt) return -1;

    va_list ap;
    va_start(ap, fmt);
    int res = vprintk(fmt, ap);
    va_end(ap);
    return res;
}

int Print::vprintk(const char* format, va_list args) {
    if (!format) return -1;

    uint32_t count = 0;

    for (uint32_t i = 0; format[i] != '\0'; i++) {

        // If an escape code
        if (format[i] != '%') {
            count += _uart.transmit(format[i]);
            continue;
        }

        i++;
        
        if (format[i] == '\0') break; // '%' at end -> just break

        // - % for escaping 
        if (format[i] == '%') {
            count += _uart.transmit('%');
            continue;
        }

        switch (format[i]) {
        case 'c': // - c for char
            count += _uart.transmit(static_cast<uint8_t>(va_arg(args, int)));
            break;

        case 'b':  // - b for binary
            count += emit_num(va_arg(args, uint32_t), 2, false);
            break;

        case 'u': // - u for unsigned int
            count += emit_num(va_arg(args, uint32_t), 10, false);
            break;

        case 'x': // - x for lowercase hex
            count += emit_num(va_arg(args, uint32_t), 16, false);
            break;

        case 'X': // - X for uppercase hex
            count += emit_num(va_arg(args, uint32_t), 16, true);
            break;

        case 's': // - s or S for cstring
        case 'S': {
            const char* s = va_arg(args, const char*);
            if (!s) s = "(null)";
            count += _uart.transmit(s);
            break;
        }

        case '0': { // 0x or 0X
            i++;
            if (format[i] == 'x') {
                count += _uart.transmit("0x");
                count += emit_num(va_arg(args, uint32_t), 16, false);
            } else if (format[i] == 'X') {
                count += _uart.transmit("0X"); // keep old behavior
                count += emit_num(va_arg(args, uint32_t), 16, true);
            } else {
                count += _uart.transmit("BAD CSTRING HEX FORMAT\n");
                return -1;
            }
            break;
        }

        case 'd': {
            int d = va_arg(args, int);
            if (d < 0) {
                count += _uart.transmit('-');
                uint32_t ud = static_cast<uint32_t>(-(int64_t)d);
                count += emit_num(ud, 10, false);
            } else {
                count += emit_num(static_cast<uint32_t>(d), 10, false);
            }
            break;
        }

        case 'V':
        case 'v': {
            uint32_t base = 10;
            bool upper_hex = true;
            i++;
            if (format[i] == 'x') { base = 16; upper_hex = false; }
            if (format[i] == 'X') { base = 16; upper_hex = true; }
            // Else float
            
            i++;
            if (format[i] != '3') {
                count += _uart.transmit("BAD VECTOR3F FORMAT (expected %v3)\n");
                return -1;
            }
            const Cesium::Vector3f* v = va_arg(args, const Cesium::Vector3f*);
            if (!v) { count += _uart.transmit("(null)"); break; }

            count += emit_float_vec(*v, base, upper_hex);   // however you access storage
            break;
        }

        case 'f': {
            float f = static_cast<float>(va_arg(args, double)); // floats are promoted to double in varargs
            count += putfloat(f, 10, false, 3); // default precision of 3
            break;
        }

        default:
            count += _uart.transmit("BAD CSTRING FORMAT\n");
            return -1;
        }
    }

    return static_cast<int>(count);
}


} // namespace Cesium



/*


ICM20948:
ID: 0x0
ADXL375:
ID: 0xE5
Acceleration [m/s2]: [5.29, 9.61, 1.44]
LIS2MDL:
ID: 0x40
*/