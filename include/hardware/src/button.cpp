#include "button.h"

#include "gpio.h"

#include <stdint.h>

struct ButtonConfig {
     enum GpioPin pin_common;
     enum GpioPin pin_button;
};

static const struct ButtonConfig buttons[] = {
     [ BUTTON_1 ] = {
          .pin_common = GPIO_PIN_COMMON_4,
          .pin_button = GPIO_PIN_BUTTON_READ_1,
     },
     [ BUTTON_2 ] = {
          .pin_common = GPIO_PIN_COMMON_4,
          .pin_button = GPIO_PIN_BUTTON_READ_2,
     },
     [ BUTTON_3 ] = {
          .pin_common = GPIO_PIN_COMMON_4,
          .pin_button = GPIO_PIN_BUTTON_READ_3,
     },
     [ BUTTON_4 ] = {
          .pin_common = GPIO_PIN_COMMON_4,
          .pin_button = GPIO_PIN_BUTTON_READ_4,
     },
     [ BUTTON_5 ] = {
          .pin_common = GPIO_PIN_COMMON_3,
          .pin_button = GPIO_PIN_BUTTON_READ_4,
     },
     [ BUTTON_TIMER ] = {
          .pin_common = GPIO_PIN_COMMON_3,
          .pin_button = GPIO_PIN_BUTTON_READ_3,
     },
     [ BUTTON_SET ] = {
          .pin_common = GPIO_PIN_COMMON_3,
          .pin_button = GPIO_PIN_BUTTON_READ_2,
     },
     [ BUTTON_MENU ] = {
          .pin_common = GPIO_PIN_COMMON_3,
          .pin_button = GPIO_PIN_BUTTON_READ_1,
     },
     [ BUTTON_ON ] = {
          .pin_common = GPIO_PIN_COMMON_1,
          .pin_button = GPIO_PIN_BUTTON_READ_3,
     },
     [ BUTTON_OFF ] = {
          .pin_common = GPIO_PIN_COMMON_1,
          .pin_button = GPIO_PIN_BUTTON_READ_4,
     },
};

static uint16_t bitmask = 0x0000;

static uint16_t pin_state( uint8_t idx ) {
     return ( gpio_pin_get( buttons[ idx ].pin_button ) == 0 ) ? 1 : 0;
}

bool button_check_state( enum Button button ) {
     return bitmask & ( 0x0001 << button );
}

void button_update( void ) {
     bitmask = 0x0000;
     for( uint8_t idx = 0; idx < BUTTON_COUNT; ++idx ) {
          gpio_pin_set( buttons[ idx ].pin_common );
          bitmask |= ( uint16_t )( pin_state( idx ) << idx );
          gpio_pin_reset( buttons[ idx ].pin_common );
     }
}
