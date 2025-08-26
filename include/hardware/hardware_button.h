#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

#include <stdbool.h>

/// @brief Button names.
enum Button {
     HARDWARE_BUTTON_1,
     HARDWARE_BUTTON_2,
     HARDWARE_BUTTON_3,
     HARDWARE_BUTTON_4,
     HARDWARE_BUTTON_5,

     HARDWARE_BUTTON_TIMER,
     HARDWARE_BUTTON_SET,
     HARDWARE_BUTTON_MENU,

     HARDWARE_BUTTON_ON,
     HARDWARE_BUTTON_OFF,

     HARDWARE_BUTTON_COUNT,  ///< Total amount of buttons.
};

/// @brief Check button state.
/// @param[in] button button name.
/// @return true - button is pressed, false - button is idle.
bool hardware_button_check_state( enum Button button );

/// @brief Update button states.
void hardware_button_update( void );

#endif
