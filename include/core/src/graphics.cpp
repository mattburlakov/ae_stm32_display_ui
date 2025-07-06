#include "graphics.h"

#include <memory.h>

#define BITS_PER_PIXEL 4

volatile uint8_t* canvas_buffer = nullptr;
static uint16_t canvas_buffer_width  = 0;
static uint16_t canvas_buffer_height = 0;

static uint8_t brightness = 0;

const struct FontData* font = nullptr;

static void draw_character( const uint8_t* data, 
                              uint8_t pos_x, uint8_t pos_y,
                              uint8_t width, uint8_t height ) {
     enum {
          BYTE_MASK = 0xff,
     };

     for( uint16_t idx = 0; idx < height; ++idx ) {
          for( uint16_t jdx = 0; jdx < width; ++jdx ) {
               uint16_t buffer_pos = pos_x + jdx + ( pos_y + idx ) * canvas_buffer_width;
               canvas_buffer[ buffer_pos ] &= ~data[ jdx + idx * width ];
               canvas_buffer[ buffer_pos ] |= data[ jdx + idx * width ] &
                    ( ( brightness << BITS_PER_PIXEL ) | brightness );
          }
     }
}

void graphics_clear_buffer( void ) {
     if( !canvas_buffer ) {
          return;
     }

     memset( ( void* )canvas_buffer, 0x00, canvas_buffer_width * canvas_buffer_height );
}

void graphics_set_buffer( uint8_t* buffer, 
                              uint16_t buffer_width, uint16_t buffer_height ) {
     canvas_buffer            = buffer;
     canvas_buffer_width      = buffer_width;
     canvas_buffer_height     = buffer_height;
}

void graphics_set_font( const struct FontData* font_data ) {
     font = font_data;
}

void graphics_set_drawing_brightness( enum GraphicsBrightness level ) {
     brightness = level;
}

void graphics_draw_buffer( const uint8_t* buffer, 
                              uint16_t pos_x, uint16_t pos_y, 
                              uint16_t width, uint16_t height ) {
     if( !canvas_buffer || !buffer ) {
          return;
     }

     for( uint16_t idx = 0; idx < height; ++idx ) {
          memcpy( ( void* )( canvas_buffer + ( pos_x + ( pos_y + idx ) * canvas_buffer_width ) ), 
               ( const void* )( buffer + idx * width ), width );
     }
}

void graphics_draw_pixel( uint16_t pos_x, uint16_t pos_y ) {
     if( !canvas_buffer ) {
          return;
     }

     uint8_t offset = ( pos_x % 2 == 0 ) ? BITS_PER_PIXEL : 0;
     uint16_t position = pos_x + pos_y * canvas_buffer_width;

     canvas_buffer[ position ] &= ~( 0x0f << offset );
     canvas_buffer[ position ] |= brightness << offset;
}

void graphics_draw_line( uint16_t pos_x, uint16_t pos_y, uint16_t length,
                              enum GraphicsLine line_type ) {
     if( !canvas_buffer ) {
          return;
     }

     switch( line_type ) {
          case GRAPHICS_LINE_VERTICAL: {
               uint8_t offset = ( pos_x % 2 == 0 ) ? BITS_PER_PIXEL : 0;

               for( uint16_t idx = 0; idx < length; ++idx ) {
                    uint16_t position = pos_x / 2 + ( pos_y + idx ) * canvas_buffer_width;

                    canvas_buffer[ position ] &= ~( 0x0f << offset );
                    canvas_buffer[ position ] |= brightness << offset;
               }

               break;
          }
          case GRAPHICS_LINE_HORIZONTAL: {
               for( uint16_t idx = 0; idx < length; ++idx ) {
                    uint8_t offset = ( ( pos_x + idx ) % 2 == 0 ) ? BITS_PER_PIXEL : 0;

                    uint16_t position = ( ( pos_x + idx ) / 2 ) + pos_y * canvas_buffer_width;

                    canvas_buffer[ position ] &= ~( 0x0f << offset );
                    canvas_buffer[ position ] |= brightness << offset;
               }

               break;
          }
          default: {
               break;
          }
     }
}

void graphics_draw_rectangle( uint16_t pos_x, uint16_t pos_y,
                              uint16_t width, uint16_t height, bool fill ) {
     if( !canvas_buffer ) {
          return;
     }

     if( fill ) {
          for( uint16_t idx = 0; idx < height; ++idx ) {
               graphics_draw_line( pos_x, pos_y + idx, width, GRAPHICS_LINE_HORIZONTAL );
          }
     }
     else {
          graphics_draw_line( pos_x, pos_y, width, GRAPHICS_LINE_HORIZONTAL );
          graphics_draw_line( pos_x, pos_y + height - 1, width, GRAPHICS_LINE_HORIZONTAL );
          graphics_draw_line( pos_x, pos_y, height, GRAPHICS_LINE_VERTICAL );
          graphics_draw_line( pos_x + width - 1, pos_y, height, GRAPHICS_LINE_VERTICAL );
     }
}

void graphics_draw_text( const char* text, uint16_t size,
                              uint16_t pos_x, uint16_t pos_y,
                              uint16_t max_length ) {
     if( !canvas_buffer || !font ) {
          return;
     }

     enum {
          CHAR_CODE_SPACE = 32,
     };

     for( uint8_t idx = 0; idx < size; ++idx ) {
          if( text[ idx ] == CHAR_CODE_SPACE ) {
               continue;
          }

          draw_character( 
               font->font_data[ text[ idx ] - FONT_CHAR_OFFSET ], 
               pos_x + font->width * idx, 
               pos_y, font->width, font->height );
     }
}
