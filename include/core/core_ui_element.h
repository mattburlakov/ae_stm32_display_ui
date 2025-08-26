#ifndef CORE_UI_ELEMENT_H
#define CORE_UI_ELEMENT_H

#include <stdint.h>
#include <stdbool.h>

class CoreUIElement {
protected:
     uint16_t origin_x = 0;
     uint16_t origin_y = 0;

public:
     void render( void );

     void set_origin( uint16_t x, uint16_t y );

     ~CoreUIElement() = default;
};

#endif
