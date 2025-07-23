#ifndef HARDWARE_EXTI_H
#define HARDWARE_EXTI_H

#include <stdbool.h>

typedef void ( *HandlerCallback )( void );

/// @brief Initialize external interrupts.
void exti_init( void );

/// @brief Set external interrupt handler function.
/// @param[in] function handler function.
void exti_set_callback( HandlerCallback function );

#endif
