cmake_minimum_required(VERSION 3.16)

include(${CMAKE_SOURCE_DIR}/cmake/arm_none_eabi.cmake)

project(display_driver)

enable_language(C ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_subdirectory(${CMAKE_SOURCE_DIR}/include/hardware)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/core)

add_executable(${EXECUTABLE}
    ${CMAKE_SOURCE_DIR}/source.cpp
    ${CMAKE_SOURCE_DIR}/startup_stm32f103rctx.s
)
target_link_libraries(${EXECUTABLE} hardware core)

target_include_directories(${EXECUTABLE} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_options(${EXECUTABLE} PUBLIC
    -T${CMAKE_SOURCE_DIR}/STM32F103RCTX_FLASH.ld
    -mcpu=cortex-m3

    -mthumb
    -mfloat-abi=soft
    -msoft-float 

    -specs=nosys.specs
    -specs=nano.specs

    -lc
    -lm
    -lnosys

    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)

target_compile_options(${EXECUTABLE} PUBLIC
    -mcpu=cortex-m3

    -mthumb
    -mfloat-abi=soft
    -msoft-float 

    -DSTM32F103xx
    -DSTM32F10X_HD
    -DSTM32F103RCT

    -fdata-sections
    -ffunction-sections

    -Wall

    -O
)

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${EXECUTABLE}
)

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -Oihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -Obinary ${EXECUTABLE} ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-objdump -D ${EXECUTABLE} > ${PROJECT_NAME}.txt
    COMMAND 
)
