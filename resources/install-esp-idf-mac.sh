#!/usr/bin/env bash
set -e
echo -e "Executing with '$ROOT_DIR' as the repository root directory\n"
# Commands taken from https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html

# Install prerequisites
# bash update
# bash install -y git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
brew install cmake ninja dfu-util

# # Clone ESP-IDF
mkdir -p "$ROOT_DIR/board-packages/esp"
cd "$ROOT_DIR/board-packages/esp"
if [ ! -d "$ROOT_DIR/board-packages/esp/esp-idf" ]; then
    git clone --recursive https://github.com/espressif/esp-idf.git
fi
cd esp-idf

# Install tools

./install.sh esp32 # EDIT THS TO CHANGE THE BOARD TYPE FOR IMPORTING

# Export alias to start the esp shell
alias start_esp_idf=". $ROOT_DIR/board-packages/esp/esp-idf/export.sh"
echo -e "\nRun 'start_esp_idf' to open the esp-idf shell" 
echo -e "Installed ESP32 tools (edit this script to install for other board types)\n"