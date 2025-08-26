#include "hardware_led.h"

#include "hardware_gpio.h"

#include <stdint.h>

struct LedConfig {
     enum GpioPin pin_common;
     enum GpioPin pin_led;
};

static const struct LedConfig leds[] = {
     [ LED_S ] = {
          .pin_common    = GPIO_PIN_COMMON_4,
          .pin_led       = GPIO_PIN_LED_1,
     },
     [ LED_M ] = {
          .pin_common    = GPIO_PIN_COMMON_4,
          .pin_led       = GPIO_PIN_LED_2,
     },
     [ LED_UARC ] = {
          .pin_common    = GPIO_PIN_COMMON_4,
          .pin_led       = GPIO_PIN_LED_3,
     },
     [ LED_ARC ] = {
          .pin_common    = GPIO_PIN_COMMON_4,
          .pin_led       = GPIO_PIN_LED_4,
     },
     [ LED_LIM ] = {
          .pin_common    = GPIO_PIN_COMMON_3,
          .pin_led       = GPIO_PIN_LED_4,
     },
     [ LED_RAMP ] = {
          .pin_common    = GPIO_PIN_COMMON_3,
          .pin_led       = GPIO_PIN_LED_3,
     },
     [ LED_LINK ] = {
          .pin_common    = GPIO_PIN_COMMON_3,
          .pin_led       = GPIO_PIN_LED_2,
     },
     [ LED_REM ] = {
          .pin_common    = GPIO_PIN_COMMON_3,
          .pin_led       = GPIO_PIN_LED_1,
     },
     [ LED_ACTRL ] = {
          .pin_common    = GPIO_PIN_COMMON_2,
          .pin_led       = GPIO_PIN_LED_1,
     },
     [ LED_ERR ] = {
          .pin_common    = GPIO_PIN_COMMON_2,
          .pin_led       = GPIO_PIN_LED_2,
     },
     [ LED_ON ] = {
          .pin_common    = GPIO_PIN_COMMON_1,
          .pin_led       = GPIO_PIN_LED_3,
     },
     [ LED_OFF ] = {
          .pin_common    = GPIO_PIN_COMMON_1,
          .pin_led       = GPIO_PIN_LED_4,
     },
};

static uint16_t bitmask = 0x0000;

void hardware_led_null( void ) {
     hardware_gpio_pin_reset( GPIO_PIN_LED_1 );
     hardware_gpio_pin_reset( GPIO_PIN_LED_2 );
     hardware_gpio_pin_reset( GPIO_PIN_LED_3 );
     hardware_gpio_pin_reset( GPIO_PIN_LED_4 );
}

void hardware_led_set_state( enum Led led, bool state ) {
     if( state ) {
          bitmask |= 1 << led;
     }
     else {
          bitmask &= ~( 1 << led );
     }
}

void hardware_led_update( void ) {
     for( uint8_t idx = 0; idx < LED_COUNT; ++idx ) {
          if( bitmask & ( 1 << idx ) ) {
               hardware_gpio_pin_set( leds[ idx ].pin_common );
               hardware_gpio_pin_set( leds[ idx ].pin_led );
               continue;
          }
          hardware_gpio_pin_reset( leds[ idx ].pin_led );
     }
}
