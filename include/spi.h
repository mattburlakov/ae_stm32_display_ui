#ifndef SPI_CONNECTION_H
#define SPI_CONNECTION_H

#include <stdint.h>
#include <stm32f10x.h>

#define	 CS_LOW 	GPIOA->BSRR |= GPIO_BSRR_BR4
#define 	 CS_HIGH 	GPIOA->BSRR |= GPIO_BSRR_BS4

/// @brief Write 2 bytes of data to SPI line.
/// @param data Data to send.
/// @return Reply data.
uint16_t spi__write_data(uint16_t data) {
     while (!(SPI1->SR & SPI_SR_TXE)) {
     }

     CS_LOW;

     SPI1->DR = data;

     while (!(SPI1->SR & SPI_SR_RXNE)) {
     }

     data = SPI1->DR;

     CS_HIGH;
     return data;
}

#endif
