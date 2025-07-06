#include "hardware.h"
#include "button.h"
#include "led.h"

#include "ssd1322.h"
#include "graphics.h"

#include "font_zero.h"

#include <memory.h>

uint8_t canvas[ 256 * 32 ] = { 0 };

int main( void ) {
     hardware_init();

     graphics_set_buffer( canvas, 256 / 2, 64 );
     
     while( true ) {
          led_null();
          button_update();

          graphics_clear_buffer();

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_14 );
          graphics_draw_rectangle( 0, 0, 44, 11, true );

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_4 );
          graphics_set_font( &font_zero );
          graphics_draw_text( "CHANNEL", 7, 1, 2, 0 );

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_4 );
          graphics_draw_rectangle( 38, 18, 15, 15, true );

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_14 );
          graphics_draw_rectangle( 40, 20, 5, 5, true );

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_8 );
          graphics_draw_rectangle( 43, 23, 5, 5, true );

          graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_0 );
          graphics_draw_rectangle( 46, 26, 5, 5, true );

          ssd1322_draw( canvas, 256 * 32 );

          led_update();
     }
}
