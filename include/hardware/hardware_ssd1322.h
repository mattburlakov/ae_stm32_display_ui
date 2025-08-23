#ifndef HARDWARE_SSD1322_H
#define HARDWARE_SSD1322_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef void ( *Ssd1322Write )( const uint8_t*, size_t );
typedef void ( *Ssd1322Read )( uint8_t*, size_t );
typedef void ( *Ssd1322Delay )( size_t );
typedef void ( *Ssd1322Reset )( bool );
typedef void ( *Ssd1322DC )( bool );

struct Ssd1322Interface {
     Ssd1322Write   write;         ///< Write function.
     Ssd1322Read    read;          ///< Read function. Unavailable in serial mode.
     Ssd1322Delay   delay;         ///< Delay function.
     Ssd1322Reset   reset;         ///< Reset pin.

     // Data/Command mode selection.
     // true - data mode, false - command mode.
     Ssd1322DC      data_command;  
};

/// @brief Initialize Winstar SSD1322 Display.
/// @param[in] interface Device interface.
void ssd1322_init( struct Ssd1322Interface* interface_ptr );

/// @brief Draw a buffer to SSD1322 screen.
/// @param buffer Buffer.
/// @param size Buffer length.
void ssd1322_draw( uint8_t* buffer, size_t size );

#endif
