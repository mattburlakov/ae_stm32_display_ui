cmake_minimum_required(VERSION 3.16)
project(firmware)

set(HEADER_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/FONT_A.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Glyph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Label.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScreenControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SPI_Connection.h
)

# set(SOURCE_LIST
# )

add_library(${PROJECT_NAME} HEADER_LIST)