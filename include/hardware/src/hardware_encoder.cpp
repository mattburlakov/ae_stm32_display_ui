#include "hardware_encoder.h"

#include "hardware_beeper.h"
#include "hardware_exti.h"
#include "hardware_gpio.h"

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

     bool a = hardware_gpio_pin_get( GPIO_PIN_ENCODER_A );
     bool b = hardware_gpio_pin_get( GPIO_PIN_ENCODER_B );

     for( uint16_t idx = 0; idx < DEBOUNCE_TIME; ++idx ) {
          if( a != hardware_gpio_pin_get( GPIO_PIN_ENCODER_A ) ||
               b != hardware_gpio_pin_get( GPIO_PIN_ENCODER_B ) ) {
               return;
          }
     }

     uint8_t current_state = ( a << 1 ) | b;
     uint8_t state = ( prev_state << 2 ) | current_state;

     if( state_table[ state ] == 1 ) {  // stub.
          hardware_beeper_beep( 0xff );
     }
}

void hardware_encoder_init( void ) {
     hardware_exti_set_callback( signal_handler );
}
