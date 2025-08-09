# Overview
Basically all the software 



# Folder structure?
```
core/
└── drivers/
    ├── peripherals/
    │   ├── spi.h
    │   ├── spi.cpp
    │   ├── i2c.h
    │   ├── i2c.cpp
    │   └── uart.h
    │
    ├── devices/
    │   ├── icm20948.h
    │   ├── icm20948.cpp
    │   ├── lis3mdl.h
    │   └── lis3mdl.cpp
    │
    └── platform/
        ├── stm32/
        │    ├── stm32_spi.cpp
        │    └── stm32_i2c.cpp
        └── esp32/
             ├── esp32_spi.cpp
             └── esp32_i2c.cpp
```