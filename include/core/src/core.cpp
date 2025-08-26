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
     { "BUTTON 1", 8 },                      //< CORE_UI_BUTTON_1
     { "BUTTON 2", 8 },                      //< CORE_UI_BUTTON_2
     { "BUTTON 3", 8 },                      //< CORE_UI_BUTTON_3
     { "BUTTON 4", 8 },                      //< CORE_UI_BUTTON_4
     { "BUTTON 5", 8 },                      //< CORE_UI_BUTTON_5
};

static CoreUIButton button_row[] = {
     { 0, 53, 51, 11,                        //< CORE_UI_BUTTON_1
          &button_label[ CORE_UI_BUTTON_1 ], 
          CORE_SIGNAL_BUTTON_1, HARDWARE_BUTTON_1 },
     { 51, 53, 51, 11,                       //< CORE_UI_BUTTON_2
          &button_label[ CORE_UI_BUTTON_2 ], 
          CORE_SIGNAL_BUTTON_2, HARDWARE_BUTTON_2 },
     { 102, 53, 52, 11,                      //< CORE_UI_BUTTON_3
          &button_label[ CORE_UI_BUTTON_3 ], 
          CORE_SIGNAL_BUTTON_3, HARDWARE_BUTTON_3 },
     { 154, 53, 51, 11,                      //< CORE_UI_BUTTON_4
          &button_label[ CORE_UI_BUTTON_4 ], 
          CORE_SIGNAL_BUTTON_4, HARDWARE_BUTTON_4 },
     { 205, 53, 51, 11,                      //< CORE_UI_BUTTON_5
          &button_label[ CORE_UI_BUTTON_5 ], 
          CORE_SIGNAL_BUTTON_5, HARDWARE_BUTTON_5 },
};

enum {
     CANVAS_WIDTH   = 256 / 2, // 1 byte per two pixels.
     CANVAS_HEIGHT  = 64,

     CANVAS_SIZE    = CANVAS_WIDTH * CANVAS_HEIGHT,
};

uint8_t canvas[ CANVAS_SIZE ] = { 0 };

// BUTTON HANDLING =========================================================== /

static void button_handler( uint8_t button ) {
     switch( button ) {
          case CORE_SIGNAL_BUTTON_1: {
               break;
          }
          case CORE_SIGNAL_BUTTON_2: {
               break;
          }
          case CORE_SIGNAL_BUTTON_3: {
               break;
          }
          case CORE_SIGNAL_BUTTON_4: {
               break;
          }
          case CORE_SIGNAL_BUTTON_5: {
               break;
          }
          default: {
               break;
          }
     }
}

static void init_button_row( void ) {
     for( uint8_t idx = 0; idx < CORE_UI_BUTTON_COUNT; ++idx ) {
          button_row[ idx ].set_callback( button_handler );
     }
}

static void render_button_row( void ) {
     for( uint8_t idx = 0; idx < CORE_UI_BUTTON_COUNT; ++idx ) {
          button_row[ idx ].render();
     }
}

static void update_button_row( void ) {
     for( uint8_t idx = 0; idx < CORE_UI_BUTTON_COUNT; ++idx ) {
          button_row[ idx ].update();
     }
}

// ENCODER HANDLING ========================================================== /

// LED HANDLING ============================================================== /

// MAIN LOGIC ================================================================ /

void core_init( void ) {
     graphics_set_buffer( canvas, CANVAS_WIDTH, CANVAS_HEIGHT );
     graphics_set_font( &font_zero );

     init_button_row();
}

void core_run( void ) {
     hardware_led_null();
     hardware_button_update();

     graphics_clear_buffer();

     render_button_row();
     update_button_row();

     hardware_ssd1322_draw( canvas, CANVAS_SIZE );

     hardware_led_update();
}
