#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"
#include "libc/print.h"

uart_t* uart = &UART2;

int main(void) {
    clock_init_48mhz();

    // 1) Enable GPIOB clock
    gpio_init(GPIO_PORTB);

    
    uart->instance = 2;
    uart->baud = 115200;

    print_begin(uart);


    if (gpio_set_output(GPIO_PORTB, 3) < 0)    
        return 0;

    printk("UART_CR1_OFFSET    0x00: %0x\n\r", GET32(uart->base_reg + UART_CR1_OFFSET));
    printk("UART_CR2_OFFSET    0x04: %0x\n\r", GET32(uart->base_reg + UART_CR2_OFFSET));
    printk("UART_CR3_OFFSET    0x08: %0x\n\r", GET32(uart->base_reg + UART_CR3_OFFSET));
    printk("UART_BRR_OFFSET    0x0C: %0x\n\r", GET32(uart->base_reg + UART_BRR_OFFSET));
    printk("UART_GTPR_OFFSET   0x10: %0x\n\r", GET32(uart->base_reg + UART_GTPR_OFFSET));
    printk("UART_RTOR_OFFSET   0x14: %0x\n\r", GET32(uart->base_reg + UART_RTOR_OFFSET));
    printk("UART_RQR_OFFSET    0x18: %0x\n\r", GET32(uart->base_reg + UART_RQR_OFFSET));
    printk("UART_ISR_OFFSET    0x1C: %0x\n\r", GET32(uart->base_reg + UART_ISR_OFFSET));
    printk("UART_ICR_OFFSET    0x20: %0x\n\r", GET32(uart->base_reg + UART_ICR_OFFSET));
    printk("UART_RDR_OFFSET    0x24: %0x\n\r", GET32(uart->base_reg + UART_RDR_OFFSET));
    printk("UART_TDR_OFFSET    0x28: %0x\n\r", GET32(uart->base_reg + UART_TDR_OFFSET));


    printk("Crazy num: %d %u %b %c \n\r", -500, -1, 254, 'c');
    printk("Crazy num: %d %d %u %b %c \n\r", -1, -500, -1, 0b10101011110100011010, 'c');
    printk("also a cstring: %s\n\r\n\r\n\r", "oh wow");

    while (1)
        ;
}