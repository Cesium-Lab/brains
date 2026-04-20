#ifndef __STM32F042_PINS_H__
#define __STM32F042_PINS_H__

#include <stdint.h>

/*

Reference:
    RM0091 — STM32F0x1/x2/x8 reference manual:
        https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
    DocID025832 - STM32F042x4/x6 Datasheet
        https://www.st.com/resource/en/datasheet/stm32f042c4.pdf

*/




// ****************************************************************************************************
//                      GPIO (AHB2)
// ****************************************************************************************************



// For making function writing easier
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTF 5

// RM Section 8 p.40 
#define GPIOA_BASE      0x48000000
#define GPIOB_BASE      0x48000400
#define GPIOF_BASE      0x48001C00   // Port F (only PF0 and PF1 available on QFP32)
#define GPIO_PORT_STRIDE 0x400          // Each GPIO port offset

#define GPIO_PIN_MODE_INPUT     0b00
#define GPIO_PIN_MODE_OUTPUT    0b01
#define GPIO_PIN_MODE_ALT       0b10
#define GPIO_PIN_MODE_ANALOG    0b11

// **************************************************
//      Registers
// **************************************************

// RM p.140
#define GPIO_MODER_OFFSET   0x00   // GPIO Port mode
#define GPIO_OTYPER_OFFSET  0x04   // GPIO Output type
#define GPIO_OSPEEDR_OFFSET 0x08   // GPIO Output speed
#define GPIO_PUPDR_OFFSET   0x0C   // GPIO Pull-up/pull-down
#define GPIO_IDR_OFFSET     0x10   // GPIO Input data
#define GPIO_ODR_OFFSET     0x14   // GPIO Output data
#define GPIO_BSRR_OFFSET    0x18   // GPIO Bit set/reset
#define GPIO_AFRL_OFFSET    0x20   // GPIO Alternate Function High
#define GPIO_AFRH_OFFSET    0x24   // GPIO Alternate Function Low

// **************************************************
//      Alternate Function Modes
// **************************************************

#define GPIO_UART1_ALT      AF1
#define GPIO_UART2_ALT      AF1
#define UART1_TX_PIN        PA9     // DS p.37
#define UART1_RX_PIN        PA10    // DS p.37
#define UART2_TX_PIN        PA2     // DS p.37
#define UART2_RX_PIN        PA3    // DS p.37
// **************************************************
//      Port A Registers
// **************************************************

#define GPIOA_MODER    (GPIOA_BASE + GPIO_MODER_OFFSET)
#define GPIOA_OTYPER   (GPIOA_BASE + GPIO_OTYPER_OFFSET)
#define GPIOA_OSPEEDR  (GPIOA_BASE + GPIO_OSPEEDR_OFFSET)
#define GPIOA_PUPDR    (GPIOA_BASE + GPIO_PUPDR_OFFSET)
#define GPIOA_IDR      (GPIOA_BASE + GPIO_IDR_OFFSET)
#define GPIOA_ODR      (GPIOA_BASE + GPIO_ODR_OFFSET)
#define GPIOA_BSRR     (GPIOA_BASE + GPIO_BSRR_OFFSET)
#define GPIOA_AFRL     (GPIOA_BASE + GPIO_AFRL_OFFSET)
#define GPIOA_AFRH     (GPIOA_BASE + GPIO_AFRH_OFFSET)

// **************************************************
//      Port B Registers
// **************************************************

#define GPIOB_MODER    (GPIOB_BASE + GPIO_MODER_OFFSET)
#define GPIOB_OTYPER   (GPIOB_BASE + GPIO_OTYPER_OFFSET)
#define GPIOB_OSPEEDR  (GPIOB_BASE + GPIO_OSPEEDR_OFFSET)
#define GPIOB_PUPDR    (GPIOB_BASE + GPIO_PUPDR_OFFSET)
#define GPIOB_IDR      (GPIOB_BASE + GPIO_IDR_OFFSET)
#define GPIOB_ODR      (GPIOB_BASE + GPIO_ODR_OFFSET)
#define GPIOB_BSRR     (GPIOB_BASE + GPIO_BSRR_OFFSET)
#define GPIOB_AFRL     (GPIOB_BASE + GPIO_AFRL_OFFSET)
#define GPIOB_AFRH     (GPIOB_BASE + GPIO_AFRH_OFFSET)

// **************************************************
//      Port F Registers
// **************************************************

#define GPIOF_MODER    (GPIOF_BASE + GPIO_MODER_OFFSET)
#define GPIOF_OTYPER   (GPIOF_BASE + GPIO_OTYPER_OFFSET)
#define GPIOF_OSPEEDR  (GPIOF_BASE + GPIO_OSPEEDR_OFFSET)
#define GPIOF_PUPDR    (GPIOF_BASE + GPIO_PUPDR_OFFSET)
#define GPIOF_IDR      (GPIOF_BASE + GPIO_IDR_OFFSET)
#define GPIOF_ODR      (GPIOF_BASE + GPIO_ODR_OFFSET)
#define GPIOF_BSRR     (GPIOF_BASE + GPIO_BSRR_OFFSET)
#define GPIOF_AFRL     (GPIOF_BASE + GPIO_AFRL_OFFSET)
#define GPIOF_AFRH     (GPIOF_BASE + GPIO_AFRH_OFFSET)

// ****************************************************************************************************
//                      RCC (Reset and Clock Control) (AHB1) - RM Section 6
// ****************************************************************************************************

// RM Section 6, p.136
#define RCC_BASE       0x40021000
#define RCC_CR         (RCC_BASE + 0x00)  // Clock control register
#define RCC_CFGR       (RCC_BASE + 0x04)  // Clock configuration register
#define RCC_CIR        (RCC_BASE + 0x08)  // Clock interrupt register
#define RCC_APB2RSTR   (RCC_BASE + 0x0C)  // APB2 peripheral reset register
#define RCC_APB1RSTR   (RCC_BASE + 0x10)  // APB1 peripheral reset register
#define RCC_AHBENR     (RCC_BASE + 0x14)  // AHB peripheral clock enable register
#define RCC_APB2ENR    (RCC_BASE + 0x18)  // APB2 peripheral clock enable register
#define RCC_APB1ENR    (RCC_BASE + 0x1C)  // APB1 peripheral clock enable register
#define RCC_BDCR       (RCC_BASE + 0x20)  // Backup domain control register
#define RCC_CSR        (RCC_BASE + 0x24)  // Control/status register
#define RCC_CR2        (RCC_BASE + 0x34)  // Control control register 2 (maybe newer?)

// **************************************************
//  AHBENR — AHB Peripheral Clock Enable Bits
//  Only necessary for QFP32 pins, timers, DMA, etc.
// **************************************************

#define RCC_CR2_HSI48ON (1 << 16)
#define RCC_CR2_HSI48RDY (1 << 17)

// **************************************************
//  AHBENR — AHB Peripheral Clock Enable Bits
//  Only necessary for QFP32 pins, timers, DMA, etc.
// **************************************************
// RM Section 6.4.6 p.121
#define RCC_AHB_A_EN  (1u << 17)  // GPIOA clock enable
#define RCC_AHB_B_EN  (1u << 18)  // GPIOB clock enable
#define RCC_AHB_F_EN  (1u << 22)  // GPIOF clock enable (PF0, PF1 only)
#define RCC_AHB_CRC_EN   (1u << 6)   // CRC clock enable (optional for data integrity)

// **************************************************
//  APB1ENR — APB1 Peripheral Clock Enable Bits
//  Needed for timers, UART, I2C, etc.
// **************************************************
// RM Section 6.4.8 p.124
#define RCC_APB1_TIM3_EN   (1u << 1)  // Timer 3 clock enable
#define RCC_APB1_SPI2_EN   (1u << 14) // SPI2 clock enable
#define RCC_APB1_UART2_EN  (1u << 17) // UART2 clock enable
#define RCC_APB1_I2C1_EN   (1u << 21) // I2C1 clock enable
#define RCC_APB1_I2C2_EN   (1u << 22) // I2C2 clock enable (optional)
#define RCC_APB1_I2C2_EN   (1u << 25) // CAN clock enable
#define RCC_APB1_PWR_EN    (1u << 28) // Power interface clock enable (optional)

// **************************************************
//  APB2ENR — APB2 Peripheral Clock Enable Bits
//  Needed for UART1, SYSCFG, ADC, etc.
// **************************************************
// RM Section 6.4.7 p.123
#define RCC_APB2_SYSCFG_EN  (1u << 0)  // SYSCFG clock enable
#define RCC_APB2_UART1_EN  (1u << 14) // UART1 clock enable (optional)
#define RCC_APB2_ADC1_EN    (1u << 9)  // ADC1 clock enable (if using ADC)
#define RCC_APB2_TIM1_EN    (1u << 11) // Timer 1 clock enable
#define RCC_APB2_SPI1_EN    (1u << 12) // SPI clock enable


// ****************************************************************************************************
//                      UART / UART (APB)
// ****************************************************************************************************

// For making function writing easier
#define UART_1 1
#define UART_2 2

// RM p.49
#define UART1_BASE     0x40013800   
#define UART2_BASE     0x40004400   
// #define UART3_BASE  0x40004800
// #define UART4_BASE  0x40004C00
// #define UART5_BASE  0x40005000
// #define UART6_BASE  0x40011400

// **************************************************
//      Register offsets (RM0091: UART chapter)
// **************************************************
// RM p.765
#define UART_CR1_OFFSET    0x00     // (RM p.744) Control 1 register
#define UART_CR2_OFFSET    0x04     // (RM p.747) Control 2 register
#define UART_CR3_OFFSET    0x08     // (RM p.751) Control 3 register
#define UART_BRR_OFFSET    0x0C     // (RM p.755) Baud Rate register
#define UART_GTPR_OFFSET   0x10     // (RM p.755) Guard time and prescaler register
#define UART_RTOR_OFFSET   0x14     // (RM p.756) Receiver Timeout register
#define UART_RQR_OFFSET    0x18     // (RM p.757) Request register
#define UART_ISR_OFFSET    0x1C     // (RM p.758) Interrupt and Status register
#define UART_ICR_OFFSET    0x20     // (RM p.763) Interrupt flag clear register
#define UART_RDR_OFFSET    0x24     // (RM p.764) Receive Data Buffer register
#define UART_TDR_OFFSET    0x28     // (RM p.764) Transmit Data Buffer register

// **************************************************
//      UART1 registers
// **************************************************
#define UART1_CR1   (UART1_BASE + UART_CR1_OFFSET)
#define UART1_CR2   (UART1_BASE + UART_CR2_OFFSET)
#define UART1_CR3   (UART1_BASE + UART_CR3_OFFSET)
#define UART1_BRR   (UART1_BASE + UART_BRR_OFFSET)
#define UART1_GTPR  (UART1_BASE + UART_GTPR_OFFSET)
#define UART1_RTOR  (UART1_BASE + UART_RTOR_OFFSET)
#define UART1_RQR   (UART1_BASE + UART_RQR_OFFSET)
#define UART1_ISR   (UART1_BASE + UART_ISR_OFFSET)
#define UART1_ICR   (UART1_BASE + UART_ICR_OFFSET)
#define UART1_RDR   (UART1_BASE + UART_RDR_OFFSET)
#define UART1_TDR   (UART1_BASE + UART_TDR_OFFSET)

// **************************************************
//      UART2 registers
// **************************************************
#define UART2_CR1   (UART2_BASE + UART_CR1_OFFSET)
#define UART2_CR2   (UART2_BASE + UART_CR2_OFFSET)
#define UART2_CR3   (UART2_BASE + UART_CR3_OFFSET)
#define UART2_BRR   (UART2_BASE + UART_BRR_OFFSET)
#define UART2_GTPR  (UART2_BASE + UART_GTPR_OFFSET)
#define UART2_RTOR  (UART2_BASE + UART_RTOR_OFFSET)
#define UART2_RQR   (UART2_BASE + UART_RQR_OFFSET)
#define UART2_ISR   (UART2_BASE + UART_ISR_OFFSET)
#define UART2_ICR   (UART2_BASE + UART_ICR_OFFSET)
#define UART2_RDR   (UART2_BASE + UART_RDR_OFFSET)
#define UART2_TDR   (UART2_BASE + UART_TDR_OFFSET)

// ****************************************************************************************************
// Optional: useful bit definitions (RM0091 UART register bitfields)
// ****************************************************************************************************

// ---- CR1 bits ----
#define UART_CR1_UE        (1 << 0)   // UART enable
#define UART_CR1_RE        (1 << 2)   // Receiver enable
#define UART_CR1_TE        (1 << 3)   // Transmitter enable
#define UART_CR1_RXNEIE    (1 << 5)   // RXNE interrupt enable
#define UART_CR1_TCIE      (1 << 6)   // TC interrupt enable
#define UART_CR1_TXEIE     (1 << 7)   // TXE interrupt enable
#define UART_CR1_M0        (1 << 12)  // Word length bit 0
#define UART_CR1_PCE       (1 << 10)  // Parity control enable
#define UART_CR1_PS        (1 << 9)   // Parity selection
#define UART_CR1_OVER8     (1 << 15)  // Oversampling mode

// ---- CR2 bits ----
#define UART_CR2_STOP_Pos  12
#define UART_CR2_STOP_Msk  (3 << UART_CR2_STOP_Pos)  // STOP[1:0]
#define UART_STOP_1        (0 << UART_CR2_STOP_Pos)
#define UART_STOP_0_5      (1 << UART_CR2_STOP_Pos)
#define UART_STOP_2        (2 << UART_CR2_STOP_Pos)
#define UART_STOP_1_5      (3 << UART_CR2_STOP_Pos)

// ---- CR3 bits ----
#define UART_CR3_DMAT      (1 << 7)   // DMA enable transmitter
#define UART_CR3_DMAR      (1 << 6)   // DMA enable receiver

// ---- ISR bits ----
#define UART_ISR_PE        (1 << 0)
#define UART_ISR_FE        (1 << 1)
#define UART_ISR_NE        (1 << 2)
#define UART_ISR_ORE       (1 << 3)
#define UART_ISR_IDLE      (1 << 4)
#define UART_ISR_RXNE      (1 << 5)
#define UART_ISR_TC        (1 << 6)
#define UART_ISR_TXE       (1 << 7)
#define UART_ISR_CTSIF     (1 << 9)
#define UART_ISR_CTS       (1 << 10)
#define UART_ISR_BUSY      (1 << 16)

// ---- ICR bits (write 1 to clear corresponding flag) ----
#define UART_ICR_PECF      (1 << 0)
#define UART_ICR_FECF      (1 << 1)
#define UART_ICR_NECF      (1 << 2)
#define UART_ICR_ORECF     (1 << 3)
#define UART_ICR_IDLECF    (1 << 4)
#define UART_ICR_TCCF      (1 << 6)


// ****************************************************************************************************
// RCC pieces you will need for UART clocking (RM0091 RCC chapter)
// (Minimal set; define more if you want.)
// ****************************************************************************************************


// Typical encodings (check RM0091 table for exact mapping):
#define UARTxSW_PCLK        0U
#define UARTxSW_SYSCLK      1U
#define UARTxSW_LSE         2U
#define UARTxSW_HSI         3U

// ****************************************************************************************************
//  Pin Numbers and Alt functions
//  (Useful for assembly or bit-shifts)
// ****************************************************************************************************
#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7
#define PA8 8
#define PA9 9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7
#define PB8 8
#define PB9 9
#define PB10 10
#define PB11 11
#define PB12 12
#define PB13 13
#define PB14 14
#define PB15 15

#define PF0 0
#define PF1 1

#define AF0 0
#define AF1 1
#define AF2 2
#define AF3 3
#define AF4 4
#define AF5 5
#define AF6 6
#define AF7 7

#endif