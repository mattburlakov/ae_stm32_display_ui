#ifndef CORE_UI_BUTTON_H
#define CORE_UI_BUTTON_H

#include "core_ui_element.h"
#include "core_ui_label.h"

#include "hardware_button.h"

typedef void ( *CoreButtonCallback )( uint8_t );

class CoreUIButton : public CoreUIElement {
private:
     uint16_t width_px = 0;
     uint16_t height_px = 0;

     CoreUILabel* label = nullptr;
     uint8_t signal = 0;
     enum Button hardware_signal;

     CoreButtonCallback press_callback = nullptr;

     bool pressed = false;

public:
     /// @brief Create UI button.
     /// @param x X-axis origin.
     /// @param y Y-axis origin.
     /// @param w Width.
     /// @param h Height.
     /// @param label Button text.
     /// @param signal Button press signal to be emitted.
     /// @param hardware_signal_source Bound hardware button.
     CoreUIButton( uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
          CoreUILabel* label, 
          uint8_t signal, enum Button hardware_signal_source );

     /// @brief Bind UI button signal handler.
     void set_callback( CoreButtonCallback callback );

     /// @brief Update UI button logic.
     void update( void );

     /// @brief Render UI button.
     void render( void );
};

#endif
