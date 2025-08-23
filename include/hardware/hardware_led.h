#ifndef HARDWARE_LED_H
#define HARDWARE_LED_H

#include <stdbool.h>

/// @brief LED names.
enum Led {
     LED_S,
     LED_M,

     LED_UARC,
     LED_ARC,
     LED_LIM,
     LED_RAMP,
     LED_LINK,
     LED_REM,
     LED_ACTRL,
     LED_ERR,

     LED_ON,
     LED_OFF,

     LED_COUNT,     ///< Total amount of LEDs.
};

/// @brief Disable all LED pins. 
void led_null( void );

/// @brief Set corresponding LED state.
/// @param[in] led LED name.
/// @param state new LED state.
void led_set_state( enum Led led, bool state );

/// @brief Set LEDs to their assigned values.
void led_update( void );

#endif
