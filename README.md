# Steps
- Install PlatformIO
<!-- - Have docker -->
<!-- - Install `Dev Containers` Extension -->
<!-- # Startup script?
- `source ./resources/setup_environment.sh
- `./resources/setup_esp_idf-mac.sh
- ESP IDF Toolchain
- STM 32 Toolchain -->


# Folder structure?
```

brains/
│
├── core/                        # Hardware-agnostic core logic
│   ├── drivers/                  
│   │   ├── peripherals/          # Abstracted interfaces for later
│   │   │   - "middleware" that currently just calls Arduino framework
│   │   │   ├── spi.h
│   │   │   ├── spi.cpp
│   │   │   ├── i2c.h
│   │   │   ├── i2c.cpp
│   │   │   ├── uart.h
│   │   │   └── uart.cpp
│   │   └── devices/              # Specific device drivers
│   │       ├── icm20948.h
│   │       ├── icm20948.cpp
│   │       ├── lis3mdl.h
│   │       └── lis3mdl.cpp
│   ├── apps/                      # Apps
│   │   ├── NetworkServer/
│   │   ├── Filesystem/
│   │   ├── TelemServer/
│   │   └── Memstore/
│   │
│   ├── data/                      # Shared data processes, types, and configs
│   │   ├── states/
│   │   ├── status/
│   │   ├── logger/
│   │   ├── memstore-framework/
│   │   ├── enums/
│   │   └── filesystem/
│   │
│   └── utilities/
│       ├── math/
│       ├── time/
│       └── misc/
│
├── board-packages/                # MCU-specific low-level implementations
│   ├── esp32/
│   │   ├── spi.h
│   │   ├── spi.cpp
│   │   ├── i2c.h
│   │   ├── i2c.cpp
│   │   ├── uart.h
│   │   └── uart.cpp
│   ├── stm32/
│   │   ├── spi.h
│   │   ├── spi.cpp
│   │   ├── i2c.h
│   │   ├── i2c.cpp
│   │   ├── uart.h
│   │   └── uart.cpp
│   └── atmel/
│       ├── spi.h
│       ├── spi.cpp
│       ├── i2c.h
│       ├── i2c.cpp
│       ├── uart.h
│       └── uart.cpp
│
├── targets/
│   ├── flight-computer/
│   │   - mission sequencing, telemetry, high level logic
│   ├── gnc/
│   │   - gnc sensors, algs, high loop ratk
│   ├── radio/
│   │   - radio/egse networking stack
│   ├── power/
│   │   - monitors power and gives it to other boards
│   ├── switching/
│   │   └── 
│   ├── recovery/
│   │   - altimeters, triggers sep with FETk
│   ├── camera/
│   │   - ESP Cam or small RPi, so may need another framework
│   ├── ground-station/
│   │   - radio receiving and wired egse
│   └── logger/
│       - logs all bus dat
│
├── lib/                           # Third-party libraries
│   ├── tinyusb/
│   └── fatfs/
│
├── resources/                     # Docs, configs, test data, and tools
│   ├── docs/
│   ├── test-data/
│   ├── scripts/
│   └── configs/
│
└── platformio.ini                 # PlatformIO config



core/
├── drivers/
│   ├── peripherals/
│   │   - "middleware" between HAL and software. Currently just calls Arduino framework
│   │   ├── spi.h
│   │   ├── spi.cpp
│   │   ├── i2c.h
│   │   ├── i2c.cpp
│   │   └── uart.h
│   │
│   ├── devices/
│   │   ├── icm20948.h
│   │   ├── icm20948.cpp
│   │   ├── lis3mdl.h
│   │   └── lis3mdl.cpp
│   │
│   └── platform/
│       - probably won't need until switching overall frameworks
│       ├── stm32/
│       │    ├── stm32_spi.cpp
│       │    └── stm32_i2c.cpp
│       └── esp32/
│            ├── esp32_spi.cpp
│            └── esp32_i2c.cpp
├── apps
│   ├── NetworkServer
│   ├── Filesystem
│   ├── TelemServer
│   └── Memstore
├── data
│   ├── states
│   ├── status
│   ├── logger
│   ├── memstore-framework
│   ├── enums?
│   └── filesystem
└── utilities
    ├── math
    ├── time
    └── other stuff

board-packages/
├─── stm32/
│    ├── stm32_spi.cpp
│    └── stm32_i2c.cpp
├─── atmel/
│    ├── atmel_spi.cpp
│    └── atmel_i2c.cpp
└── esp32/
    ├── esp32_spi.cpp
    └── esp32_i2c.cpp

targets/
├─── flight-computer/ 
│    - mission sequencing, telemetry, high level logic
├─── gnc/ 
│    - gnc sensors, algs, high loop ratk
├─── radio/ 
│    - radio/egse networking stack
├─── power/ 
├─── switching/ 
│    - a bunch of FETs for load switches, power sense, and optocoupler sense
├─── recovery/ 
│    - altimeters, triggers sep with FETk
├─── camera/ 
│    - ESP Cam or small RPi, so may need another framework
├─── ground-station/ 
│    - radio receiving and wired egsk
└── logger/ 
     - logs all bus datk

gnc/ ?
(sims)

lib/
(third party libraries)

```