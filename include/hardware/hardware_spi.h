#ifndef HARDWARE_SPI_H
#define HARDWARE_SPI_H

#include <stdint.h>
#include <stdlib.h>

/// @brief Initialize SPI peripheral. 
void spi_init( void );

/// @brief Write buffer to SPI interface line.
/// @param[in] buffer Buffer to write.
/// @param[in] size Data size.
void spi_write( const uint8_t* buffer, size_t size );

/// @brief Read into buffer from SPI line.
/// @param[out] buffer Buffer to write to.
/// @param[in] size Data size.
void spi_read( uint8_t* buffer, size_t size );

#endif
