cmake_minimum_required(VERSION 3.16)

project(hardware CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/CMSIS ${CMAKE_BINARY_DIR}/cmsis)

set(HEADER_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/button.h
     ${CMAKE_CURRENT_SOURCE_DIR}/encoder.h
     ${CMAKE_CURRENT_SOURCE_DIR}/exti.h
     ${CMAKE_CURRENT_SOURCE_DIR}/gpio.h
     ${CMAKE_CURRENT_SOURCE_DIR}/hardware.h
     ${CMAKE_CURRENT_SOURCE_DIR}/led.h
     ${CMAKE_CURRENT_SOURCE_DIR}/spi.h
     ${CMAKE_CURRENT_SOURCE_DIR}/ssd1322.h
     ${CMAKE_CURRENT_SOURCE_DIR}/uart.h
)

set(SOURCE_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/src/button.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/encoder.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/exti.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/led.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/spi.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/ssd1322.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/uart.cpp
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
