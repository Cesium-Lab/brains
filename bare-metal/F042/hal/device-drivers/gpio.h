#ifndef __GPIO_H__
#define __GPIO_H__
// Reference Mannual Section 8 p.149-165 

// TODO: CHECK THESE FUNCTIONS AND PULLUP/PULLDOWN
// TODO: HANDLE SPEED FOR DEVICES

#include "stm32f042-pins.h"

#define gpio_panic(msg...) panic(msg)

enum {
    GPIO_MAX_PIN = 16
};

// ****************************************************************************************************
//                  Setup
// ****************************************************************************************************

// Basically just turns on the clock, but for a port
int gpio_init(uint32_t port);

// Configure GPIO <pin> mode (Input, Output, Alt, Analog). Returns -1 if invalid pin/port
int gpio_set_mode(uint32_t port, uint32_t pin, uint32_t mode);

// Configure GPIO <pin> as an output pin. Returns -1 if invalid pin/port
int gpio_set_output(uint32_t port, uint32_t pin);

// Configure GPIO <pin> as an input pin. Returns -1 if invalid pin/port
int gpio_set_input(uint32_t port, uint32_t pin);

// Configure GPIO <pin> as an alternate pin with function. Returns -1 if invalid pin/port
int gpio_set_alt(uint32_t port, uint32_t pin, uint32_t alt_function);


// Configure GPIO <pin> as an analog pin. Returns -1 if invalid pin/port
int gpio_set_analog(uint32_t port, uint32_t pin);

// ****************************************************************************************************
//                  IO
// ****************************************************************************************************

// Set GPIO <pin> on. Returns -1 if invalid pin/port
int gpio_write_on(uint32_t port, uint32_t pin);

// Set GPIO<pin> off. Returns -1 if invalid pin/port
int gpio_write_off(uint32_t port, uint32_t pin);

// Set GPIO <pin> to <v>. On for v > 0. Returns -1 if invalid pin/port
int gpio_write(uint32_t port, uint32_t pin, uint32_t v);

// Read the current value of GPIO <pin>.
// Returns value, or -1 if invalid pin/port
int gpio_read(uint32_t port, uint32_t pin);

// ****************************************************************************************************
//                  GPIO Pullup/Down routines
// ****************************************************************************************************

/**
 * Activate the pullup register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_set_pullup(uint32_t port, uint32_t pin);

/**
 * Activate the pulldown register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_set_pulldown(uint32_t port, uint32_t pin);

/**
 * Deactivate both the pullup and pulldown registers on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_pud_off(uint32_t port, uint32_t pin);


#endif