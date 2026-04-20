#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"

void delay(int count) {
    while(count--) { __asm("nop"); }
}

int main(void) {
    // 1) Enable GPIOB clock

    gpio_init(GPIO_PORTB);

    if (gpio_set_output(GPIO_PORTB, 3) < 0)    
        return 0;

    while(1) {
        gpio_write_off(GPIO_PORTB, PB3);
        delay(1000000);
        gpio_write_on(GPIO_PORTB, PB3);
        delay(200000);
    }
}