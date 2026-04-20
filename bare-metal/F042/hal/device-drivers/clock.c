#include "stm32.h"
#include "stm32f042-pins.h"

void clock_init_48mhz(void) {
    // RM0091 p.94 - Enable HSI48 (HSIEON bit)
    #define RCC_CR2_HSI48ON (1 << 16)
    #define RCC_CR2_HSI48RDY (1 << 17)
    
    uint32_t val;
    
    // Turn on HSI48
    val = GET32(RCC_CR2);
    val |= RCC_CR2_HSI48ON;
    PUT32(RCC_CR2, val);
    
    // Wait for ready
    while (!(GET32(RCC_CR2) & RCC_CR2_HSI48RDY)) {
        ;
    }
    
    // Switch system clock to HSI48 (SW = 0b11) (System Clock Switch Status)
    val = GET32(RCC_CFGR);
    val &= ~(0x3 << 0);  // Clear SW[1:0]
    val |= (0x3 << 0);   // Set SW = 11 (HSI48)
    PUT32(RCC_CFGR, val);
    
    // Wait for system clock to stabilite (SWS = 0b11)
    while ((GET32(RCC_CFGR) & (0x3 << 2)) != (0x3 << 2)) {
        ;
    }
}


void clock_set(uint32_t reg, uint32_t clock, uint32_t state) {
    uint32_t value;

    value = GET32(reg);

    if (state)
        value |= clock;
    else
        value &= ~clock;

    PUT32(reg, value);
}