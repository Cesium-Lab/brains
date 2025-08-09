#!/usr/bin/env bash
set -e
echo "$ROOT_DIR"
# Commands taken from https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html

# Install prerequisites
sudo apt-get update
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

# Clone ESP-IDF
# mkdir -p "$ROOT_DIR/board-packages/esp"
# cd "$ROOT_DIR/board-packages/esp"
# git clone -b v5.5 --recursive https://github.com/espressif/esp-idf.git
# cd esp-idf

# # Install tools
# ./install.sh esp32

# # Export alias to start the esp terminal
# alias start_esp_idf=". $ROOT_DIR/board-packages/esp/esp-idf/export.sh"