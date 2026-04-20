# Minimal Makefile for STM32F0 Hello World
# Toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

TTYACM ?= /dev/cu.usbmodem103 
BAUD   ?= 115200

# Source
SRC = startup.s
SRC += hal/device-drivers/clock.c
SRC += hal/device-drivers/gpio.c
SRC += hal/device-drivers/uart.c

SRC += libc/print.c


# Target
TARGET  = hello




# Playgrounds
# SRC += tests/playgrounds/uart.c
# SRC += tests/playgrounds/printk-test.c
SRC += tests/playgrounds/gpio.c

LD      = linker.ld

# Where we are saving
BUILD_DIR = build

# Flags
CFLAGS  = -mcpu=cortex-m0 -mthumb -Wall -O0 -g -ffreestanding  -I. -Ihal -Iinclude -Ihal/device-drivers
LDFLAGS = -T$(LD) -nostartfiles -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
TTYUSB = /dev/ttyUSB0

# Default target
all: $(BUILD_DIR)/$(TARGET).elf \
	 $(BUILD_DIR)/$(TARGET).bin \
     $(BUILD_DIR)/$(TARGET).list

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build ELF
$(BUILD_DIR)/$(TARGET).elf: $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@
	$(SIZE) $@

# Generate binary
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@

# Generate assembly for checking
$(BUILD_DIR)/%.list: $(BUILD_DIR)/%.elf
	$(OBJDUMP) -D $< > $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Flash binary
flash: $(BUILD_DIR)/$(TARGET).bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000
	st-flash reset

reset:
	st-flash reset

run: all flash

serial:
	echo "Press Ctrl+A Ctrl+D to exit"s
	sleep 0.5
	screen $(TTYACM) $(BAUD)

.PHONY: all clean