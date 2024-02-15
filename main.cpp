#include <stdlib.h>
#include <stm32f10x.h>

#include "classes/Canvas.h"
#include "classes/Context.h"
#include "classes/Parameter.h"

#include "encoder.h"
#include "gpio.h"
#include "hardware.h"
#include "ssd1322.h"
#include "value.h"

Value selected_context = {0, 1, 0};

// INIT FROM FLASH! ============================================================ OK
Parameter channel_ids[] = { //ADD MARKER TYPE
     {"CH: 1",      5,   0,   FLAG_IS_LABEL}, // CHANNEL 1
     {"CH: 2",      5,   0,   FLAG_IS_LABEL}, // CHANNEL 2
};

Parameter channel_1_parameters[] = { // separate into class
     {"U:",         2,   30,   0, UNITS_MILLI_V},
     {"I:",         2,   5,    0, UNITS_A},
     {"P:",         2,   150,  0, UINTS_MILLI_W},
     {"U:",         2,   0,    0, UNITS_V},
     {"U:",         2,   0,    0, UNITS_V},
};

Parameter channel_2_parameters[] = { // separate into class
     {"U:",         2,   10000,    0, UNITS_V},
     {"I:",         2,   5,        0, UNITS_A},
     {"P:",         2,   50000,    0, UNITS_W},
     {"U:",         2,   0,    0, UNITS_V},
     {"U:",         2,   0,    0, UNITS_V},
};

Parameter navbar[] = { // simple labels
     {"SELECT",      6,   0,   FLAG_IS_LABEL}, // BTN 1
     {"BACK",        4,   0,   FLAG_IS_LABEL}, // BTN 2
     {"PULSE:",      6,   0,   FLAG_IS_LABEL}, // BTN 3
     {"LOCK:",       5,   0,   FLAG_IS_LABEL}, // BTN 4
     {"ALT:",        4,   0,   FLAG_IS_LABEL}, // BTN 5
};

Context channel_1(
                  0, 0, 70, 8,
                  1,
                  0, 5,
                  channel_1_parameters
               );

Context channel_2(
                  129, 0, 70, 8,
                  1,
                  0, 5,
                  channel_2_parameters
               );      

Context channel_labels(
                       0, 39, 70, 8,
                       2,
                       0, 2,
                       channel_ids
);        

Context page_0[] = { channel_1, channel_2 }; // a page

Context* active_context = &page_0[0]; // #TODO: main menu
uint8_t page_0_context_id = 0;
// END =========================================================================

int main() {
     active_context->target( true );

     hardware_init();
     ssd1322_init();
    
     // INIT CANVAS ============================================================ OK
     uint8_t buffer[256 / 2 * 64];

     Canvas mainCanvas;

     mainCanvas.canvas_set_size(256 / 2, 64);
     mainCanvas.canvas_set_pixel_buffer(buffer);
     mainCanvas.erase();
     
     // END ====================================================================

     // EXPERIMENTAL AREA ======================================================

     while (true) {
          mainCanvas.erase();
          encoder_update();

     //BTN ROW==================================================================
          
          if( gpio_button_pressed( PANEL_BUTTON_1 ) ) { //SELECT BTN============ OK
               hardware_beep( 5000 );

               if ( active_context )
                    active_context->select_parameter();
               else {
                    active_context = &page_0[ page_0_context_id ];
                    page_0[ page_0_context_id ].target( true );
               }
          }
          if( gpio_button_pressed( PANEL_BUTTON_2 ) ) { //BACK BTN============== OK
               hardware_beep( 5000 );

               if ( active_context ) {
                    if( active_context->get_selected_parameter() ) {
                         active_context->deselect_parameter();
                    }
                    else {
                         active_context = nullptr;
                         page_0[ page_0_context_id ].target( false );
                    }
               }
          }

     // BTN ROW OVER============================================================
     // ENCODER=================================================================
     // #FIXME: ENCODER BTN: remap jtag
          if( encoder_button_pressed() ) {
               hardware_beep( 1000 );

               if ( active_context )
                    active_context->select_parameter();
          }

          if( encoder_state_changed() ) { // ENCODER ROTATE===================== OK
               if( active_context ) {
                    hardware_beep( 1000 );

                    if( active_context->get_selected_parameter() ) {
                         active_context->get_selected_parameter()->increment( encoder_get_increment() );
                    }
                    else {
                         active_context->increment_parameter_id( encoder_get_increment() );
                    }
               }
               else {
                    hardware_beep( 1000 );

                    if( ( page_0_context_id + encoder_get_increment() > 0 ) && //REWORK
                          page_0_context_id + encoder_get_increment() < 2 ) {
                          page_0_context_id += encoder_get_increment();
                    }
               }
          }
     // ENCODER OVER============================================================

     // DRAW UI ================================================================
          for( uint8_t i = 0; i < 2; ++i ) { // draw all contexts on page, if not hidden
               page_0[ i ].draw( &mainCanvas );
          }

     // DRAW GUIDELINES
          mainCanvas.draw_horizontal_primitive( 0, 54, 254, MEDIUM );
          for( uint8_t i = 0; i < 5; ++i ) {
               navbar[ i ].draw( &mainCanvas, 57 * i, 56, false );
          }

          ssd1322_send_graphics( mainCanvas.pixels, 256 / 2 * 64 ); // the only fn to remain
     }
}
