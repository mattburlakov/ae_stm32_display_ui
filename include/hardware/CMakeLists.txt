cmake_minimum_required(VERSION 3.16)

project(hardware CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/CMSIS ${CMAKE_BINARY_DIR}/cmsis)

set(HEADER_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_button.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_encoder.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_exti.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_gpio.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_led.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_spi.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_ssd1322.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware_uart.h

     ${CMAKE_CURRENT_SOURCE_DIR}/hardware.h
)

set(SOURCE_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_button.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_encoder.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_exti.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_gpio.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_led.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_spi.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_ssd1322.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_uart.cpp

     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_NAME} cmsis)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m3

    -mthumb
    -mfloat-abi=soft
    -msoft-float 

    -fdata-sections
    -ffunction-sections

    -Wall

    -O
)

target_include_directories(${PROJECT_NAME} PUBLIC 
     ${CMAKE_CURRENT_SOURCE_DIR}/
)
