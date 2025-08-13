# Steps
- Install PlatformIO
<!-- - Have docker -->
<!-- - Install `Dev Containers` Extension -->
<!-- # Startup script?
- `source ./resources/setup_environment.sh
- `./resources/setup_esp_idf-mac.sh
- ESP IDF Toolchain
- STM 32 Toolchain -->

# ESPIDF
- if sdkconfig.h will not include, then run `pio run --target menuconfig` (then press escape?) 

# Issues
- If VS Code is struggling to make/delete files, etc. run `lsof +D [path_to_brains_repo]` and kill the processes

# Folder structure?
```
brains/
│
├── src/
│   │
│   ├── core/                        # Hardware-agnostic core logic
│   │   ├── device-drivers/                  
│   │   │   └── devices/              # Specific device drivers
│   │   │       ├── icm20948.h
│   │   │       ├── icm20948.cpp
│   │   │       ├── lis3mdl.h
│   │   │       └── lis3mdl.cpp
│   │   ├── isolation-layer/                  
│   │   │   ├── os/          # delay, etc.
│   │   │   └── peripherals/          # Abstracted interfaces for later
│   │   │       - "middleware" that currently just calls Arduino framework
│   │   │       ├── spi.h
│   │   │       ├── spi.cpp
│   │   │       ├── i2c.h
│   │   │       ├── i2c.cpp
│   │   │       ├── uart.h
│   │   │       └── uart.cpp
│   │   ├── apps/                      # Apps
│   │   │   ├── NetworkServer/
│   │   │   ├── Filesystem/
│   │   │   ├── TelemServer/
│   │   │   └── Memstore/
│   │   │
│   │   ├── data/                      # Shared data processes, types, and configs
│   │   │   ├── states/
│   │   │   ├── status/
│   │   │   ├── logger/
│   │   │   ├── memstore-framework/
│   │   │   ├── enums/
│   │   │   └── filesystem/
│   │   │
│   │   └── utilities/
│   │       ├── math/
│   │       ├── time/
│   │       └── misc/
│   │
│   ├── board-packages/                # MCU-specific low-level implementations
│   │   ├── esp32/
│   │   │   ├── spi.h
│   │   │   ├── spi.cpp
│   │   │   ├── i2c.h
│   │   │   ├── i2c.cpp
│   │   │   ├── uart.h
│   │   │   └── uart.cpp
│   │   ├── stm32/
│   │   │   ├── spi.h
│   │   │   ├── spi.cpp
│   │   │   ├── i2c.h
│   │   │   ├── i2c.cpp
│   │   │   ├── uart.h
│   │   │   └── uart.cpp
│   │   └── atmel/
│   │       ├── spi.h
│   │       ├── spi.cpp
│   │       ├── i2c.h
│   │       ├── i2c.cpp
│   │       ├── uart.h
│   │       └── uart.cpp
│   │
│   └── targets/
│       ├── flight-computer/
│       │   - mission sequencing, telemetry, high level logic
│       ├── gnc/
│       │   - gnc sensors, algs, high loop ratk
│       ├── radio/
│       │   - radio/egse networking stack
│       ├── power/
│       │   - monitors power and gives it to other boards
│       ├── switching/
│       │   └── 
│       ├── recovery/
│       │   - altimeters, triggers sep with FETk
│       ├── camera/
│       │   - ESP Cam or small RPi, so may need another framework
│       ├── ground-station/
│       │   - radio receiving and wired egse
│       └── logger/
│           - logs all bus dat
│    
├── lib/                           # Third-party libraries
│   ├── tinyusb/
│   └── fatfs/
│
├── gnc/                            # sims
│
├── resources/                     # Docs, configs, test data, and tools
│   ├── docs/
│   ├── test-data/
│   ├── scripts/
│   └── configs/
│
└── platformio.ini                 # PlatformIO config

```