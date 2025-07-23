#ifndef HARDWARE_BEEPER_H
#define HARDWARE_BEEPER_H

#include <stdbool.h>

/// @brief Set beeper state.
/// @param state true - beeper is ON, false - beeper is OFF.
void beeper_state_set( bool state );

#endif
