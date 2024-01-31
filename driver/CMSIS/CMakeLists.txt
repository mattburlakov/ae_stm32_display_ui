cmake_minimum_required(VERSION 3.16)
project(cmsis C)

set(HEADER_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32G4xx/Include/stm32g4xx.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32G4xx/Include/system_stm32g4xx.h
)

set(SOURCE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c
)

add_library(${PROJECT_NAME} OBJECT ${SOURCE_LIST} ${HEADER_LIST})

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4
    -mfloat-abi=hard
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32G4xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
)