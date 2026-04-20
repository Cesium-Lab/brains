#ifndef __STM32_H__
#define __STM32_H__

#include <stdint.h>

#include "gpio.h"
#include "uart.h"
#include "clock.h"

#define STM32_SUCCESS 1
#define STM32_ERROR -1

#define SYSTEM_CORE_CLOCK 48000000

// Is this a valid pin on the specific MCU package?
int pin_valid(uint32_t port, uint32_t pin);

static inline void delay(int count) {
    while(count--) { __asm("nop"); }
}

// ****************************************************************************************************
//                  Lowest level (defined in startup.s)
// ****************************************************************************************************

void PUT32(uint32_t addr, uint32_t v);
void put32(const volatile void *addr, uint32_t v);

// void put32chk(const volatile void* addr, uint32_t v);
// void PUT32CHK(uint32_t addr, uint32_t v);

uint32_t GET32(uint32_t addr);
uint32_t get32(const volatile void *addr);

// check port fn

#endif