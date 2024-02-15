# Description
Firmware for 256x64 SSD1322 for STM32f103xx MCU. <br/>
Requires [arm-none-eabi](https://developer.arm.com/downloads/-/gnu-rm) toolchain and [CMake](https://cmake.org/) v3.0.0 or higher. <br/>
Currently only supports debug builds.

## Build
Linux:
```
cmake --preset dev
cmake --build --preset dev
```

Windows:
```
cmake --preset dev-win
cmake --build --preset dev
```

## Flash
Flash the MCU using [st-flash](https://github.com/stlink-org/stlink) utility:
```
st-flash --reset write build/dev/apel_display_ex.bin 0x8000000
```