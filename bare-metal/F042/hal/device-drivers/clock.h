#ifndef __CLOCK_H__
#define __CLOCK_H__
// Reference Manual Section 6 p.95-137

// Enables or disables clock with specific state
void clock_set(uint32_t reg, uint32_t clock, uint32_t state);

// 48 MHz clock (BLOCKS until clock is ready, and system clock is ready)
void clock_init_48mhz(void);

#endif