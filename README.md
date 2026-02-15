# Steps
- Install PlatformIO
<!-- - Have docker -->
<!-- - Install `Dev Containers` Extension -->
<!-- # Startup script?
- `source ./resources/setup_environment.sh
- `./resources/setup_esp_idf-mac.sh
- ESP IDF Toolchain
- STM 32 Toolchain -->

# PlatformIO

## Native
- Do NOT need to build every time you change code, just press upload, but you have to clear the Upload command terminal first

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
│   ├── board-packages/                # MCU-specific low-level implementations
│   │   │
│   │   ├── esp32-arduino/
│   │   │   ├── hal.cpp          # Linking main(), setup(), loop() if needed
│   │   │   ├── time.cpp          # delay, etc.
│   │   │   ├── os/                 # delay, etc.
│   │   │   └── peripherals/          # Isolation layer interface for linking
│   │   │       ├── spi.cpp
│   │   │       ├── i2c.cpp
│   │   │       └── uart.cpp
│   │   │
│   │   ├── stm32-arduino/
│   │   │   └── ...
│   │   │
│   │   └── atmel/
│   │       └── ... 
│   │
│   ├── core/                        # Hardware-agnostic core logic
│   │   │
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
│   │   ├── device-drivers/        # Specific device drivers
│   │   │   ├── icm20948.h
│   │   │   ├── icm20948.cpp
│   │   │   ├── lis3mdl.h
│   │   │   └── lis3mdl.cpp
│   │   │
│   │   ├── isolation-layer/   # source files are under each board package               
│   │   │   ├── hal.h          # For linking main(), setup(), loop() if needed
│   │   │   ├── time.h          # delay, etc.
│   │   │   ├── os/                 # delay, etc.
│   │   │   └── peripherals/          # Isolation layer interface for linking
│   │   │       ├── spi.h
│   │   │       ├── i2c.h
│   │   │       └── uart.h
│   │   │
│   │   └── utilities/
│   │       ├── math/
│   │       ├── time/
│   │       └── misc/
│   │
│   │
│   └── targets/
│       │
│       ├── flight-computer/
│       │   - mission sequencing, telemetry, high level logic
│       ├── gnc/
│       │   - gnc sensors, algs, high loop ratk
│       ├── radio/
│       │   - radio/egse networking stack
│       ├── power/
│       │   - monitors power and gives it to other boards
│       ├── switching/
│       │   
│       ├── recovery/
│       │   - altimeters, triggers sep with FETk
│       ├── camera/
│       │   - ESP Cam or small RPi, so may need another framework
│       ├── ground-station/
│       │   - radio receiving and wired egse
│       └── logger/
│           - logs all bus dat
│    
├── lib/                            # Third-party libraries
│   ├── GoogleTest/                 # Unit testing
│   ├── Unity/                      # Unit testing
│   ├── tinyusb/
│   └── fatfs/
│
├── gnc/                            # sims
│
├── resources/                      # Docs, configs, test data, and tools
│   ├── docs/
│   ├── test-data/
│   ├── scripts/
│   └── configs/
│
└── platformio.ini                 # PlatformIO config

```