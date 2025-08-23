#include "core.h"

#include "hardware_button.h"
#include "hardware_led.h"

#include "hardware_ssd1322.h"

#include "core_graphics.h"
#include "core_ui_button.h"
#include "core_ui_label.h"

#include "core_font_zero.h"

enum CoreSignal {
     CORE_SIGNAL_BUTTON_1,
     CORE_SIGNAL_BUTTON_2,
     CORE_SIGNAL_BUTTON_3,
     CORE_SIGNAL_BUTTON_4,
     CORE_SIGNAL_BUTTON_5,
};

enum CoreUIButtonNumber {
     CORE_UI_BUTTON_1,
     CORE_UI_BUTTON_2,
     CORE_UI_BUTTON_3,
     CORE_UI_BUTTON_4,
     CORE_UI_BUTTON_5,

     CORE_UI_BUTTON_COUNT,
};

static CoreUILabel button_label[] = {
     { "BUTTON 1", 8 },                                     //< CORE_UI_BUTTON_1
     { "BUTTON 2", 8 },                                     //< CORE_UI_BUTTON_2
     { "BUTTON 3", 8 },                                     //< CORE_UI_BUTTON_3
     { "BUTTON 4", 8 },                                     //< CORE_UI_BUTTON_4
     { "BUTTON 5", 8 },                                     //< CORE_UI_BUTTON_5
};

// BUTTON ROW
static CoreUIButton button_row[] = {
     { 0, 53, 51, 11, &button_label[ CORE_UI_BUTTON_1 ], CORE_SIGNAL_BUTTON_1 },   //< CORE_UI_BUTTON_1
     { 51, 53, 51, 11, &button_label[ CORE_UI_BUTTON_2 ], CORE_SIGNAL_BUTTON_2 },  //< CORE_UI_BUTTON_2
     { 102, 53, 52, 11, &button_label[ CORE_UI_BUTTON_3 ], CORE_SIGNAL_BUTTON_3 }, //< CORE_UI_BUTTON_3
     { 154, 53, 51, 11, &button_label[ CORE_UI_BUTTON_4 ], CORE_SIGNAL_BUTTON_4 }, //< CORE_UI_BUTTON_4
     { 205, 53, 51, 11, &button_label[ CORE_UI_BUTTON_5 ], CORE_SIGNAL_BUTTON_5 }, //< CORE_UI_BUTTON_5
};

enum {
     CANVAS_WIDTH   = 256 / 2, // 1 byte per two pixels.
     CANVAS_HEIGHT  = 64,

     CANVAS_SIZE    = CANVAS_WIDTH * CANVAS_HEIGHT,
};

uint8_t canvas[ CANVAS_SIZE ] = { 0 };

static void render_buttons( void ) {
     for( uint8_t idx = 0; idx < CORE_UI_BUTTON_COUNT; ++idx ) {
          button_row[ idx ].render();
     }
}

void core_init( void ) {
     graphics_set_buffer( canvas, CANVAS_WIDTH, CANVAS_HEIGHT );
     graphics_set_font( &font_zero );
}

void core_run( void ) {
     led_null();
     button_update();

     graphics_clear_buffer();

     render_buttons();

     graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_14 );
     graphics_draw_line( 0, 0, 32, GRAPHICS_LINE_HORIZONTAL );
     graphics_draw_text( "TEST", 4, 0, 2, 0 );
     graphics_draw_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 37, 32, 2, 0 );
     graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_10 );
     graphics_draw_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 37, 32, 10, 0 );
     graphics_draw_text( "TEST", 4, 1, 10, 0 );
     graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_6 );
     graphics_draw_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 37, 32, 18, 0 );
     graphics_draw_text( "TEST", 4, 2, 18, 0 );
     graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_2 );
     graphics_draw_text( "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 37, 32, 26, 0 );
     graphics_draw_text( "TEST", 4, 3, 26, 0 );

     ssd1322_draw( canvas, CANVAS_SIZE );

     led_update();
}
