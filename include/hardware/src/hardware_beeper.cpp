#include "hardware_beeper.h"

#include "hardware.h"
#include "hardware_gpio.h"

void hardware_beeper_beep( uint16_t time_ms ) {
     hardware_gpio_pin_set( GPIO_PIN_ZUM );
     hardware_delay( time_ms );
     hardware_gpio_pin_reset( GPIO_PIN_ZUM );
}
