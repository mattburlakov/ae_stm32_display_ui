#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>

#include "font.h"

/// @brief Pixel brightenss level [0..14].
enum GraphicsBrightness {
     GRAPHICS_BRIGHTNESS_0,
     GRAPHICS_BRIGHTNESS_1,
     GRAPHICS_BRIGHTNESS_2,
     GRAPHICS_BRIGHTNESS_3,
     GRAPHICS_BRIGHTNESS_4,
     GRAPHICS_BRIGHTNESS_5,
     GRAPHICS_BRIGHTNESS_6,
     GRAPHICS_BRIGHTNESS_7,
     GRAPHICS_BRIGHTNESS_8,
     GRAPHICS_BRIGHTNESS_9,
     GRAPHICS_BRIGHTNESS_10,
     GRAPHICS_BRIGHTNESS_11,
     GRAPHICS_BRIGHTNESS_12,
     GRAPHICS_BRIGHTNESS_13,
     GRAPHICS_BRIGHTNESS_14,
};

/// @brief Line type.
enum GraphicsLine {
     GRAPHICS_LINE_VERTICAL,
     GRAPHICS_LINE_HORIZONTAL,
};

/// @brief Clear active buffer. 
void graphics_clear_buffer( void );

/// @brief Set active buffer to draw on.
/// @param[in] buffer Buffer.
/// @param[in] buffer_width Buffer width.
/// @param[in] buffer_height Buffer height.
void graphics_set_buffer( uint8_t* buffer, 
                              uint16_t buffer_width, uint16_t buffer_height );

/// @brief Set text drawing font.
/// @param font_data Font data.
void graphics_set_font( const struct FontData* font_data );

/// @brief Set brightness of pixels to be drawn on an active buffer.
/// @param[in] level Level of brightness of pixels.
void graphics_set_drawing_brightness( enum GraphicsBrightness level );

/// @brief Put another buffer on an active buffer.
/// @param buffer Buffer to put.
/// @param x_pos Put origin along X-axis.
/// @param y_pos Put origin along Y-axis.
/// @param width Put buffer width.
/// @param height Put buffer height.
void graphics_draw_buffer( const uint8_t* buffer, 
                              uint16_t pos_x, uint16_t pos_y, 
                              uint16_t width, uint16_t height );

/// @brief Draw a pixel on an active buffer.
/// @param[in] pos_x Position of the pixel along X-axis.
/// @param[in] pos_y Position of the pixel along Y-axis.
void graphics_draw_pixel( uint16_t pos_x, uint16_t pos_y );

/// @brief Draw a line on an active buffer.
/// @param[in] pos_x Position of the line origin along X-axis.
/// @param[in] pos_y Position of the line origin along Y-axis.
/// @param[in] length Line length in pixels.
/// @param[in] line_type GRAPHICS_LINE_VERTICAL or GRAPHICS_LINE_HORIZONTAL.
void graphics_draw_line( uint16_t pos_x, uint16_t pos_y, uint16_t length,
                              enum GraphicsLine line_type );

/// @brief Draw a rectangle on an active buffer.
/// @param[in] pos_x Rectangle origin along X-axis.
/// @param[in] pos_y Rectangle origin along Y-axis.
/// @param[in] width Rectangle width.
/// @param[in] height Rectangle height.
/// @param[in] fill true - rectangle is filled, false - rectangle outline only.
void graphics_draw_rectangle( uint16_t pos_x, uint16_t pos_y,
                              uint16_t width, uint16_t height, bool fill );

/// @brief Draw text on an active buffer.
/// @param text Text string to draw.
/// @param size Size of text string in characters.
/// @param pos_x Position origin along X-axis.
/// @param pos_y Position origin along Y-axis.
/// @param font Font data.
/// TODO: Fix x-axis positioning.
void graphics_draw_text( const char* text, uint16_t size,
                              uint16_t pos_x, uint16_t pos_y, 
                              uint16_t max_length );

#endif
