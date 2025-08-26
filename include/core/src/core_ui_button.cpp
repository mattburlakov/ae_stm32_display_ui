#include "core_ui_button.h"

#include "core_graphics.h"

#include "hardware_beeper.h"

#define BUTTON_LABEL_OFFSET 2

CoreUIButton::CoreUIButton( uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
     CoreUILabel* label, 
     uint8_t signal, enum Button hardware_signal_source ) {
     this->origin_x      = x;
     this->origin_y      = y;

     this->width_px      = w;
     this->height_px     = h;
     this->label         = label;

     this->signal             = signal;
     this->hardware_signal    = hardware_signal_source;

     this->label->set_origin( this->origin_x, this->origin_y );
     this->label->set_offset( BUTTON_LABEL_OFFSET, BUTTON_LABEL_OFFSET );
}

void CoreUIButton::set_callback( CoreButtonCallback callback ) {
     this->press_callback = callback;
}

void CoreUIButton::update( void ) {
     if( hardware_button_check_state( this->hardware_signal ) ) {
          if( this->press_callback && !this->pressed ) {
               hardware_beeper_beep( 0x0fff );
               press_callback( this->signal );
          }

          this->pressed = true;
     }
     else {
          this->pressed = false;
     }
}

void CoreUIButton::render( void ) {
     graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_14 );

     graphics_draw_rectangle( this->origin_x, this->origin_y,
          this->width_px, this->height_px, this->pressed );

     if( this->label ) {
          if( this->pressed ) {
               graphics_set_drawing_brightness( GRAPHICS_BRIGHTNESS_0 );
          }

          this->label->render();
     }
};
