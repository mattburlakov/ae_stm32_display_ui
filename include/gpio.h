#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stm32f10x.h>

enum Button {
     PANEL_BUTTON_1      = 0,
     PANEL_BUTTON_2      = 1,
     PANEL_BUTTON_3      = 2,
     PANEL_BUTTON_4      = 3,

     PANEL_BUTTON_5      = 4,
     PANEL_BUTTON_MENU   = 5,
     PANEL_BUTTON_SET    = 6,
     PANEL_BUTTON_TIMER  = 7,

     PANEL_BUTTON_ON     = 8,
     PANEL_BUTTON_OFF    = 9
};

enum Led {

};

static uint8_t button_primed[] =
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

static uint8_t get_button_pin_state(enum Button btn) {
     switch(btn) {
          case PANEL_BUTTON_1: {
               return (GPIOC->IDR & GPIO_IDR_IDR10) ? 1 : 0;
          }
          case PANEL_BUTTON_2: {
               return (GPIOC->IDR & GPIO_IDR_IDR11) ? 1 : 0;
          }
          case PANEL_BUTTON_3: {
               return (GPIOC->IDR & GPIO_IDR_IDR12) ? 1 : 0;
          }
          case PANEL_BUTTON_4: {
               return (GPIOC->IDR & GPIO_IDR_IDR3) ? 1 : 0;
          }
          case PANEL_BUTTON_5: {
               return (GPIOC->IDR & GPIO_IDR_IDR3) ? 1 : 0;
          }

          case PANEL_BUTTON_ON: {
               return (GPIOC->IDR & GPIO_IDR_IDR12) ? 1 : 0;
          }
          case PANEL_BUTTON_OFF: {
               return (GPIOC->IDR & GPIO_IDR_IDR3) ? 1 : 0;
          }

          case PANEL_BUTTON_MENU: {
               return (GPIOC->IDR & GPIO_IDR_IDR10) ? 1 : 0;
          }
          case PANEL_BUTTON_SET: {
               return (GPIOC->IDR & GPIO_IDR_IDR11) ? 1 : 0;
          }
          case PANEL_BUTTON_TIMER: {
               return (GPIOC->IDR & GPIO_IDR_IDR12) ? 1 : 0;
          }

          default: {
               return 0;
          }
     }
}

static void set_button_row(enum Button btn) {
     if(btn < 4) {
          GPIOC->BSRR |= GPIO_BSRR_BS15;
     }
     else if(btn < 8) {
          GPIOC->BSRR |= GPIO_BSRR_BS0;
     }
     else {
          GPIOC->BSRR |= GPIO_BSRR_BS2;
     }
}

static void reset_button_row(enum Button btn) {
     if(btn < 4) {
          GPIOC->BSRR |= GPIO_BSRR_BR15;
     }
     else if(btn < 8) {
          GPIOC->BSRR |= GPIO_BSRR_BR0;
     }
     else {
          GPIOC->BSRR |= GPIO_BSRR_BR2;
     }
}

/// @brief Check if the button specified is pressed.
/// @param btn Button to check.
/// @return 1 - button is pressed / 0 - button is not pressed.
uint8_t gpio_button_pressed(enum Button btn) {
     set_button_row(btn);

     if(get_button_pin_state(btn)) {
          button_primed[btn] = 1;
     }
     else if(button_primed[btn]) {
          button_primed[btn] = 0;
          reset_button_row(btn);

          return 1;
     }

     reset_button_row(btn);       

     return 0;
}



#endif