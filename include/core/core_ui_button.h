#ifndef CORE_UI_BUTTON_H
#define CORE_UI_BUTTON_H

#include "core_ui_element.h"
#include "core_ui_label.h"

typedef void ( *CoreButtonCallback )( uint8_t );

class CoreUIButton : public CoreUIElement {
private:
     uint16_t width_px = 0;
     uint16_t height_px = 0;

     CoreUILabel* label = nullptr;
     uint8_t signal = 0;

     CoreButtonCallback press_callback = nullptr;

     bool pressed = false;

public:
     CoreUIButton( uint16_t x, uint16_t y, uint16_t w, uint16_t h, CoreUILabel* label, uint8_t signal );

     void set_callback( CoreButtonCallback callback );

     void press( void );
     void render( void );
};

#endif
