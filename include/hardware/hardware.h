#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include <stdlib.h> 

/// @brief Hardware delay function. Blocking.
/// @param[in] delay Delay in NOPs.
void hardware_delay( size_t delay );

/// @brief Initialize device hardware.
void hardware_init( void );

#endif
