#ifndef HARDWARE_GPIO_H
#define HARDWARE_GPIO_H

#include <stdbool.h>

/// @brief Device pin names.
enum GpioPin {
     GPIO_PIN_COMMON_1,            ///< Common line 1. 
     GPIO_PIN_COMMON_2,            ///< Common line 2. 
     GPIO_PIN_COMMON_3,            ///< Common line 3. 
     GPIO_PIN_COMMON_4,            ///< Common line 4. 

     GPIO_PIN_BUTTON_READ_1,       ///< Button read line 1. 
     GPIO_PIN_BUTTON_READ_2,       ///< Button read line 2. 
     GPIO_PIN_BUTTON_READ_3,       ///< Button read line 3. 
     GPIO_PIN_BUTTON_READ_4,       ///< Button read line 4. 

     GPIO_PIN_LED_1,               ///< LED anode line 1. 
     GPIO_PIN_LED_2,               ///< LED anode line 2. 
     GPIO_PIN_LED_3,               ///< LED anode line 3. 
     GPIO_PIN_LED_4,               ///< LED anode line 4. 

     GPIO_PIN_ENCODER_A,           ///< Encoder pin A.
     GPIO_PIN_ENCODER_B,           ///< Encoder pin B.
     GPIO_PIN_ENCODER_BUTTON,      ///< Encoder button pin.

     GPIO_PIN_RES_1,               ///< Res. 1 pin. TODO: change description.
     GPIO_PIN_RES_2,               ///< Res. 2 pin. TODO: change description.

     GPIO_PIN_SPI_SCL,             ///< SPI clocking line.
     GPIO_PIN_SPI_SDA,             ///< SPI data line.

     GPIO_PIN_DISPLAY_RESET,       ///< Winstar display reset pin.
     GPIO_PIN_DISPLAY_CHIP_SELECT, ///< Winstar display chip select pin.
     GPIO_PIN_DISPLAY_SCLK,        ///< Winstar display SCLK line.
     GPIO_PIN_DISPLAY_SDI,         ///< Winstar display SDI line.
     GPIO_PIN_DISPLAY_DC,          ///< Winstar display Data/Command line.

     GPIO_PIN_ZUM,                 ///< Buzzer line.

     GPIO_PIN_SERIAL_TX,           ///< Serial transmission line.
     GPIO_PIN_SERIAL_RX,           ///< Serial reception line.

     GPIO_PIN_COUNT,               ///< Total number of used pins.
};

/// @brief Initialize device GPIOs.
void gpio_init( void );

/// @brief Get pin state.
/// @param[in] pin Pin name.
/// @return true - pin HIGH state, false - pin LOW state.
bool gpio_pin_get( enum GpioPin pin );

/// @brief Set pin to HIGH state.
/// @param[in] pin Pin name.
void gpio_pin_set( enum GpioPin pin );

/// @brief Reset pin to LOW state.
/// @param[in] pin Pin name.
void gpio_pin_reset( enum GpioPin pin );

#endif
