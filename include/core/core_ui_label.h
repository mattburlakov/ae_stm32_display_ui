#ifndef CORE_UI_LABEL_H
#define CORE_UI_LABEL_H

#include "core_ui_element.h"

class CoreUILabel : public CoreUIElement {
private:
     const char* text = nullptr;
     uint16_t text_length = 0;

     uint16_t offset_x = 0;
     uint16_t offset_y = 0;

public:
     CoreUILabel( const char* name, uint16_t length );

     void render( void );

     void set_offset( uint16_t x, uint16_t y );
};

#endif
