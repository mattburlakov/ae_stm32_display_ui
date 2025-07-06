cmake_minimum_required(VERSION 3.16)

project(core CXX)

set(HEADER_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/graphics.h
     ${CMAKE_CURRENT_SOURCE_DIR}/font.h

     ${CMAKE_CURRENT_SOURCE_DIR}/resources/font_zero.h
)

set(SOURCE_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics.cpp

     ${CMAKE_CURRENT_SOURCE_DIR}/resources/src/font_zero.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_NAME} hardware)

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
     ${CMAKE_CURRENT_SOURCE_DIR}/resources
)
