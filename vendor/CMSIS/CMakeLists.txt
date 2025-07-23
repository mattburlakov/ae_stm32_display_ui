cmake_minimum_required(VERSION 3.16)
project(cmsis C)

set(HEADER_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/CoreSupport/core_cm3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h
)

set(SOURCE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/CoreSupport/core_cm3.c
)

add_library(${PROJECT_NAME} OBJECT ${SOURCE_LIST} ${HEADER_LIST})

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m3
    -mfloat-abi=soft

    -DSTM32F103xx
    -DSTM32F10X_HD
    -DSTM32F103RCT
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/DeviceSupport/ST/STM32F10x/
    ${CMAKE_CURRENT_SOURCE_DIR}/CM3/CoreSupport/
)