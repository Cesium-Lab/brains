/* Minimal linker script */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 16K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 4K
}

/* Sections */
SECTIONS
{
  .text : {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
    _sidata = _etext;    /* flash load address for .data */
  } >FLASH

  .data : AT(_sidata) {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  _stack_start = ORIGIN(RAM) + LENGTH(RAM);   /* what your startup expects */
}