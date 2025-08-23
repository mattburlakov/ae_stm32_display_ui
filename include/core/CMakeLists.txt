cmake_minimum_required(VERSION 3.16)

project(core CXX)

set(HEADER_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/core_font_zero.h

     ${CMAKE_CURRENT_SOURCE_DIR}/core_graphics.h
     ${CMAKE_CURRENT_SOURCE_DIR}/core_font.h

     ${CMAKE_CURRENT_SOURCE_DIR}/core_ui_button.h
     ${CMAKE_CURRENT_SOURCE_DIR}/core_ui_element.h
     ${CMAKE_CURRENT_SOURCE_DIR}/core_ui_label.h

     ${CMAKE_CURRENT_SOURCE_DIR}/core.h
)

set(SOURCE_LIST
${CMAKE_CURRENT_SOURCE_DIR}/resources/src/core_font_zero.cpp

     ${CMAKE_CURRENT_SOURCE_DIR}/src/core_graphics.cpp

     ${CMAKE_CURRENT_SOURCE_DIR}/src/core_ui_button.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/core_ui_element.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/core_ui_label.cpp

     ${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp
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
