#include "hardware.h"

#include "encoder.h"
#include "exti.h"
#include "gpio.h"
#include "spi.h"
#include "uart.h"

#include "ssd1322.h"

#include <stm32f10x.h>

struct Ssd1322Interface ssd1322_interface;

static void ssd1322_write( const uint8_t* buffer, size_t size ) {
     gpio_pin_reset( GPIO_PIN_DISPLAY_CHIP_SELECT );
     spi_write( buffer, size );
     gpio_pin_set( GPIO_PIN_DISPLAY_CHIP_SELECT );
}

static void ssd1322_read( uint8_t* buffer, size_t size ) {      // stub.
     __NOP();
}

static void ssd1322_reset( bool reset ) {
     if( reset )
          gpio_pin_reset( GPIO_PIN_DISPLAY_RESET );
     else
          gpio_pin_set( GPIO_PIN_DISPLAY_RESET );
}

static void ssd1322_data_command( bool data ) {
     if( data )
          gpio_pin_set( GPIO_PIN_DISPLAY_DC );
     else
          gpio_pin_reset( GPIO_PIN_DISPLAY_DC );
}

static void init_ssd1322_interface( void ) {
     ssd1322_interface.write            = ssd1322_write;
     ssd1322_interface.read             = ssd1322_read;
     ssd1322_interface.delay            = hardware_delay;
     ssd1322_interface.reset            = ssd1322_reset;
     ssd1322_interface.data_command     = ssd1322_data_command;
}

void hardware_delay( size_t delay ) {
     for ( size_t idx = 0; idx < delay; ++idx ) {
          __NOP();
     }
}

void hardware_init( void ) {
     __disable_irq();

     gpio_init();
     exti_init();
     spi_init();

     gpio_pin_set( GPIO_PIN_DISPLAY_CHIP_SELECT );

     encoder_init();

     init_ssd1322_interface();
     ssd1322_init( &ssd1322_interface );

     __enable_irq();
}

