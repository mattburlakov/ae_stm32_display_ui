#include "core_ui_label.h"

#include "core_graphics.h"

CoreUILabel::CoreUILabel( const char* name, uint16_t length ) {
     this->text          = name;
     this->text_length   = length;
}

void CoreUILabel::render( void ) {
     if( this->text ) {
          graphics_draw_text( this->text, this->text_length, 
               this->origin_x + this->offset_x, this->origin_y + this->offset_y, 0 );
     }
}

void CoreUILabel::set_offset( uint16_t x, uint16_t y ) {
     this->offset_x = x;
     this->offset_y = y;
}
