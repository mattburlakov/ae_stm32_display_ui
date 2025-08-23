#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

#include <stdbool.h>

/// @brief Button names.
enum Button {
     BUTTON_1,
     BUTTON_2,
     BUTTON_3,
     BUTTON_4,
     BUTTON_5,

     BUTTON_TIMER,
     BUTTON_SET,
     BUTTON_MENU,

     BUTTON_ON,
     BUTTON_OFF,

     BUTTON_COUNT,  ///< Total amount of buttons.
};

/// @brief Check button state.
/// @param[in] button button name.
/// @return true - button is pressed, false - button is idle.
bool button_check_state( enum Button button );

/// @brief Update button states.
void button_update( void );

#endif
