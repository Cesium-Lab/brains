#include "stm32.h"

#include "uart.h"
#include "gpio.h"
#include "libc/print.h"

uart_t UART1;
uart_t UART2;

// ****************************************************************************************************
//                  Setup
// ****************************************************************************************************

int uart_init(uart_t* uart) {

    // Initializing UART1 or UART2
    if (uart->instance != 1 && uart->instance != 2) return -1;

    gpio_init(GPIO_PORTA); // For pins

    // RM p. 136 (for RCC)
    switch (uart->instance) {
        case 1:
            clock_set(RCC_APB2ENR, RCC_APB2_UART1_EN, 1);

            gpio_set_alt(GPIO_PORTA, UART1_TX_PIN, GPIO_UART1_ALT);
            gpio_set_alt(GPIO_PORTA, UART1_RX_PIN, GPIO_UART1_ALT);
            
            uart->base_reg = UART1_BASE;
            break;
        case 2:
            clock_set(RCC_APB1ENR, RCC_APB1_UART2_EN, 1);

            gpio_set_alt(GPIO_PORTA, UART2_TX_PIN, GPIO_UART2_ALT);
            gpio_set_alt(GPIO_PORTA, UART2_RX_PIN, GPIO_UART2_ALT);

            uart->base_reg = UART2_BASE;
            break;
        default:
            // Unhandled instance
            return STM32_ERROR;
    }

    return STM32_SUCCESS;
}

int uart_brr_from_clk(uint32_t fclk, uint32_t baud) {
    // Calculation on 27.5.4 p.716
    // baud = f_clk / USARTDIV
    // BAUD RATE = 480000 / (1152)

    return fclk / baud;
}



int uart_begin(uart_t* uart) {
    // RM p. 988 Example init
    /**
     * (1) Oversampling by 16, 115200 baud
     * `UART1->BRR = 480000 / 96;`
     * (2) 8 data bit, 1 start bit, 1 stop bit, no parity
     * `UART1->CR1 = UART_CR1_TE | UART_CR1_UE;`
     */
    uint32_t val;

    // Disable USART before configuring
    val = GET32(uart->base_reg + UART_CR1_OFFSET);
    val &= ~UART_CR1_UE;
    PUT32(uart->base_reg + UART_CR1_OFFSET, val);

    // ----- CR1 RM p.744 -----
    // 8N1, oversampling by 16, Basically default of 0
    PUT32(uart->base_reg + UART_CR1_OFFSET, 0);

    // ----- CR2 RM p.747 ----- 
    val = GET32(uart->base_reg + UART_CR2_OFFSET);
    // LSB first (would be 1 for MSB)
    PUT32(uart->base_reg + UART_CR2_OFFSET, val); 

    // ----- CR3 RM p.751 (defaults) ----- 
    PUT32(uart->base_reg + UART_CR3_OFFSET, 0); 

    // ----- BRR p.755 (UART baud) -----
    uint32_t fclk = SYSTEM_CORE_CLOCK;
    PUT32(uart->base_reg + UART_BRR_OFFSET, uart_brr_from_clk(fclk, uart->baud));

    // ----- ENABLE EVERYTHING -----
    val = GET32(uart->base_reg + UART_CR1_OFFSET);
    val |= UART_CR1_RE; // Enable Receiver
    // val |= UART_CR1_RXNEIE; // Enable Receiver Interrupt
    val |= UART_CR1_TE; // Enable Transmitter
    // val |= UART_CR1_TXEIE; // Enable Transmitter Interrupt
    PUT32(uart->base_reg + UART_CR1_OFFSET, val);
    val |= UART_CR1_UE; // Enable UART
    PUT32(uart->base_reg + UART_CR1_OFFSET, val);


    // Clear any error flags
    PUT32(uart->base_reg + UART_ICR_OFFSET, 
          UART_ICR_FECF | UART_ICR_ORECF | UART_ICR_PECF);
    

    // TODO: wait for ack?
    return STM32_SUCCESS;
}

// ****************************************************************************************************
//                  TX and RX
// ****************************************************************************************************


int uart_put8(uart_t* uart, uint8_t c) {
    // RM p. 988 Example transmit byte code
    /**
     * Start UART transmission
     * `UART1->TDR = stringtosend[send++];  // Will inititiate TC if TXE is set
     */

    // TODO: put into another function
    while ((GET32(uart->base_reg + UART_ISR_OFFSET) & UART_ISR_TXE) == 0) {
        ;
    }


    PUT32(uart->base_reg + UART_TDR_OFFSET, c);

    return STM32_SUCCESS;
}

uint32_t uart_put_cstr(uart_t* uart, const char* cstr){
    uint32_t i = 0;
    while(cstr[i] != 0x00) {
        uart_put8(uart, cstr[i]);
        i++;
    }

    return i;
}

uint32_t uart_putn(uart_t* uart, void* buffer, uint8_t nbytes) {
    for (uint32_t i = 0; i < nbytes; i++) {
        uart_put8(uart, ((uint8_t*)buffer)[i]);
    }
    return nbytes;
}

int uart_has_data(uart_t* uart) {
    // RM p.758
    uint32_t val = GET32(uart->base_reg + UART_ISR_OFFSET);
    if ((val & UART_ISR_RXNE) == UART_ISR_RXNE)
        return 1;

    
    return 0;
}

uint8_t uart_get8(uart_t* uart) {
    // RM p. 988 Example receiver byte code

    // Read clears RXNE
    uint32_t rdr = GET32(uart->base_reg + UART_RDR_OFFSET);
    return (uint8_t)(rdr & 0xFF);
}

// int uart_hex(uart_t* uart, uint8_t h) {
    
// }