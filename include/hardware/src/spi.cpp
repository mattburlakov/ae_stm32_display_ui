#include "spi.h"

#include <stm32f10x.h>
#include <stdbool.h>

static bool wait_for_transmit_ready( void ) {
     while ( !( SPI1->SR & SPI_SR_TXE ) ) {
     }

     return true;
}

static bool wait_for_receive_ready( void ) {
     while ( !( SPI1->SR & SPI_SR_RXNE ) ) {
     }

     return true;
}

void spi_init( void ) {
     RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
     SPI1->CR1 |= ( SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA |
                    SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_SSM |
                    SPI_CR1_SSI );

     SPI1->CR1 |= SPI_CR1_SPE;
}

void spi_write( const uint8_t* buffer, size_t size ) {
     for( size_t idx = 0; idx < size; ++idx ) {
          wait_for_transmit_ready();
          SPI1->DR = buffer[ idx ];

          wait_for_receive_ready();     // TODO: Investigate.
          SPI1->DR;
     }
}

void spi_read( uint8_t* buffer, size_t size ) {
     wait_for_receive_ready();
     // data = SPI1->DR;
}
