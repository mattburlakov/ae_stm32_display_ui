#ifndef HARDWARE_BEEPER_H
#define HARDWARE_BEEPER_H

#include <stdint.h>

/// @brief Produce beeper sound.
/// @param time_ms Pitch time in ms.
void hardware_beeper_beep( uint16_t time_ms );

#endif
