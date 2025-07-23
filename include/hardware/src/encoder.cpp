#include "encoder.h"

#include "exti.h"
#include "gpio.h"

#include <stdint.h>

static void signal_handler( void ) {
     enum {
          DEBOUNCE_TIME = 0x0fff,
     };

     static uint8_t prev_state = 0;

     const int8_t state_table[ 16 ] = {
          0,  -1,  +1,   0,
          +1,  0,   0,  -1,
          -1,  0,   0,  +1,
          0,  +1,  -1,   0,
     };

     bool a = gpio_pin_get( GPIO_PIN_ENCODER_A );
     bool b = gpio_pin_get( GPIO_PIN_ENCODER_B );

     for( uint16_t idx = 0; idx < DEBOUNCE_TIME; ++idx ) {
          if( a != gpio_pin_get( GPIO_PIN_ENCODER_A ) ||
               b != gpio_pin_get( GPIO_PIN_ENCODER_B ) ) {
               return;
          }
     }

     uint8_t current_state = ( a << 1 ) | b;
     uint8_t state = ( prev_state << 2 ) | current_state;

     if( state_table[ state ] == 1 ) {  // stub.
          gpio_pin_set( GPIO_PIN_ZUM );
          for( uint16_t idx = 0; idx < 0xff; ++idx ){}
          gpio_pin_reset( GPIO_PIN_ZUM );
     }
}

void encoder_init( void ) {
     exti_set_callback( signal_handler );
}
