cmake_minimum_required(VERSION 3.16)
project(firmware)

set(HEADER_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/FONT_A.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SPI_Connection.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Canvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parameter.h
)

# set(SOURCE_LIST
# )

add_library(${PROJECT_NAME} HEADER_LIST)