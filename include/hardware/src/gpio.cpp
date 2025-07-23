#include "gpio.h"

#include <stm32f10x.h>
#include <stdint.h>

#define CONFIG_REGISTER_MAX_PINS 8

struct Gpio {
     uint32_t rcc;
     GPIO_TypeDef* port;

     uint8_t pin_number;
     uint32_t mode;
     uint32_t cnf;
};

const struct Gpio Pins[] = {
     // < COMMON PINS ======================================================== >
     [ GPIO_PIN_COMMON_1 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 2,
          .mode          = GPIO_CRL_MODE2_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_COMMON_2 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 1,
          .mode          = GPIO_CRL_MODE1_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_COMMON_3 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 0,
          .mode          = GPIO_CRL_MODE0_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_COMMON_4 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 15,
          .mode          = GPIO_CRH_MODE15_1, 
          .cnf           = 0,
     },
     // < BUTTON READ PINS =================================================== >
     [ GPIO_PIN_BUTTON_READ_1 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 10,
          .mode          = 0, 
          .cnf           = GPIO_CRH_CNF10_0,
     },
     [ GPIO_PIN_BUTTON_READ_2 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 11,
          .mode          = 0, 
          .cnf           = GPIO_CRH_CNF11_0,
     },
     [ GPIO_PIN_BUTTON_READ_3 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 12,
          .mode          = 0, 
          .cnf           = GPIO_CRH_CNF12_0,
     },
     [ GPIO_PIN_BUTTON_READ_4 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 3,
          .mode          = 0, 
          .cnf           = GPIO_CRL_CNF3_0,
     },
     // < LED PINS =========================================================== >
     [ GPIO_PIN_LED_1 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 6,
          .mode          = GPIO_CRL_MODE6_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_LED_2 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 7,
          .mode          = GPIO_CRL_MODE7_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_LED_3 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 8,
          .mode          = GPIO_CRH_MODE8_1, 
          .cnf           = 0,
     },
     [ GPIO_PIN_LED_4 ] = {
          .rcc           = RCC_APB2ENR_IOPCEN,
          .port          = GPIOC,
          .pin_number    = 9,
          .mode          = GPIO_CRH_MODE9_1, 
          .cnf           = 0,
     },
     // < ENCODER PINS ======================================================= >
     [ GPIO_PIN_ENCODER_A ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 7,
          .mode          = 0, 
          .cnf           = GPIO_CRL_CNF7_0,
     },
     [ GPIO_PIN_ENCODER_B ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 6,
          .mode          = 0, 
          .cnf           = GPIO_CRL_CNF6_0,
     },
     [ GPIO_PIN_ENCODER_BUTTON ] = {              // TODO: set alternate to clear JTAG.
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 3,
          .mode          = 0, 
          .cnf           = GPIO_CRL_CNF3_0,
     },
     // < Res. 1-2 PINS ====================================================== >
     [ GPIO_PIN_RES_1 ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 13,
          .mode          = 0, 
          .cnf           = GPIO_CRH_CNF13_0,
     },
     [ GPIO_PIN_RES_2 ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 12,
          .mode          = 0, 
          .cnf           = GPIO_CRH_CNF12_0,
     },
     // < SPI PINS =========================================================== >
     [ GPIO_PIN_SPI_SCL ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 10,
          .mode          = GPIO_CRH_MODE10_1, 
          .cnf           = GPIO_CRH_CNF10,
     },
     [ GPIO_PIN_SPI_SDA ] = {
          .rcc           = RCC_APB2ENR_IOPBEN,
          .port          = GPIOB,
          .pin_number    = 11,
          .mode          = GPIO_CRH_MODE11_1, 
          .cnf           = GPIO_CRH_CNF11,
     },
     // < WINSTAR DISPLAY PINS =============================================== >
     [ GPIO_PIN_DISPLAY_RESET ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 3,
          .mode          = GPIO_CRL_MODE3_0, 
          .cnf           = 0,
     },
     [ GPIO_PIN_DISPLAY_CHIP_SELECT ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 4,
          .mode          = GPIO_CRL_MODE4_0, 
          .cnf           = 0,
     },
     [ GPIO_PIN_DISPLAY_SCLK ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 5,
          .mode          = GPIO_CRL_MODE5, 
          .cnf           = GPIO_CRL_CNF5_1,
     },
     [ GPIO_PIN_DISPLAY_SDI ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 7,
          .mode          = GPIO_CRL_MODE7, 
          .cnf           = GPIO_CRL_CNF7_1,
     },
     [ GPIO_PIN_DISPLAY_DC ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 11,
          .mode          = GPIO_CRH_MODE11_0, 
          .cnf           = 0,
     },
     // < BUZZER PIN ========================================================= >
     [ GPIO_PIN_ZUM ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 6,
          .mode          = GPIO_CRL_MODE6_0, 
          .cnf           = 0,
     },
     // < SERIAL PINS ======================================================== >
     [ GPIO_PIN_SERIAL_TX ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 9,
          .mode          = GPIO_CRH_MODE9, 
          .cnf           = GPIO_CRH_CNF9_1,
     },
     [ GPIO_PIN_SERIAL_RX ] = {
          .rcc           = RCC_APB2ENR_IOPAEN,
          .port          = GPIOA,
          .pin_number    = 10,
          .mode          = GPIO_CRH_MODE10, 
          .cnf           = GPIO_CRH_CNF10_1,
     },
};

static void jtag_pin_disable( void ) {
     RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
     AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
}

static void pin_init( const Gpio* instance ) {
     RCC->APB2ENR |= instance->rcc;
     
     if( instance->pin_number < CONFIG_REGISTER_MAX_PINS ) {
          // Clear pin configuration.
          instance->port->CRL &= ~( 0x0000000f << ( instance->pin_number * 4 ) );
          // Configure pin.
          instance->port->CRL |= instance->mode | instance->cnf;
     }
     else {
          // Clear pin configuration.
          instance->port->CRH &= ~( 0x0000000f << ( ( instance->pin_number - 8 ) * 4 ) );

          // Configure pin.
          instance->port->CRH |= instance->mode | instance->cnf;
     }
}

void gpio_init( void ) {
     jtag_pin_disable();

     for( uint8_t idx = 0; idx < GPIO_PIN_COUNT; ++idx ) {
          pin_init( &Pins[ idx ] );
     }
}

bool gpio_pin_get( enum GpioPin pin ) {
     return Pins[ pin ].port->IDR & ( 0x01 << Pins[ pin ].pin_number );
}

void gpio_pin_set( enum GpioPin pin ) {
     Pins[ pin ].port->BSRR |= 0x01 << Pins[ pin ].pin_number;
}

void gpio_pin_reset( enum GpioPin pin ) {
     Pins[ pin ].port->BSRR |= 0x01 << ( Pins[ pin ].pin_number + 0x10 );
}
