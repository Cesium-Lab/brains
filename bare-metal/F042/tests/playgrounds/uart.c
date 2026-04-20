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

    // if (uart_init(uart) != STM32_SUCCESS) { // For clocks
    //     return 0;
    // }

    // uart_begin(uart);


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

    // while(1) {
    //     uint32_t isr = GET32(uart->base_reg + UART_ISR_OFFSET);
    //     printk("ISR: 0x%0x ", isr);
        
    //     if (isr & UART_ISR_RXNE) {
    //         printk("RXNE=1! ");
    //     }
    //     if (isr & UART_ISR_FE) {
    //         printk("FE=1! ");
    //     }
    //     if (isr & UART_ISR_ORE) {
    //         printk("ORE=1! ");
    //     }
    //     printk("\n\r");
        
    //     delay(200000);
    // }

    while(1) {

        // Wow it works yayy (never gonna do floats holy hell)
        // printk("Crazy hex: %x %X %0x %0X \n\r", 0xE5, 0xE5, 0xE5, 0xE5);

        // uint32_t isr = GET32(uart->base_reg + UART_ISR_OFFSET);
        
        // // Clear overrun error
        // if (isr & UART_ISR_ORE) {
        //     PUT32(uart->base_reg + UART_ICR_OFFSET, UART_ICR_ORECF);
        //     printk("Overrun cleared!\n\r");
        // }
        
        // // Now check for data
        // if (isr & UART_ISR_RXNE) {
        //     uint8_t c = uart_get8(uart);
        //     printk("RX: %c (0x%02x)\n\r", c, c);
        // }
        printk("Crazy num: %d %u %b %c \n\r", -500, -1, 254, 'c');
        printk("Crazy num: %d %d %u %b %c \n\r", -1, -500, -1, 0b10101011110100011010, 'c');
        printk("also a cstring: %s\n\r\n\r\n\r", "oh wow");
        // while (uart_has_data(uart) > 0) {
            // printk("%0x\n\r", GET32(uart->base_reg + UART_RDR_OFFSET));
            // printk("has data\n\r");
            // printk("%0x\n\r", uart_get8(uart));
        // printk("%0x\n\r", uart_get8(uart));
        // printk("%0x\n\r", uart_get8(uart));
        // printk("%0x\n\r", uart_get8(uart));
        // printk("%0x\n\r", uart_get8(uart));
        //     printk("%0x\n\r", uart_get8(uart));
        // }

        // Clear any errors
        uint32_t isr = GET32(uart->base_reg + UART_ISR_OFFSET);
        if (isr & (UART_ISR_ORE | UART_ISR_FE)) {
            PUT32(uart->base_reg + UART_ICR_OFFSET, 
                  UART_ICR_ORECF | UART_ICR_FECF);
        }
        
        // // Check for data
        // if (uart_has_data(uart)) {
        //     uint8_t c = uart_get8(uart);
            
        //     // Echo back with info
        //     printk("RX: (%0x, %d)\n\r", c, c);
            
        //     // Blink LED
        //     gpio_write_on(GPIO_PORTB, 3);
        //     delay(50000);
        //     gpio_write_off(GPIO_PORTB, 3);
        // }

        // delay(200000);df
    }
}