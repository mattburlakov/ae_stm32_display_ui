#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <stm32f10x.h>

enum State {
     STATE_IDLE          = 0,
     STATE_TRANSITION    = 1
};

enum Direction {
     DIRECTION_IDLE                = 0,
     DIRECTION_CLOCKWISE           = 1,
     DIRECTION_COUNTERCLOCKWISE    = 2
};

static uint8_t prev_dir = DIRECTION_IDLE;
static uint8_t state = STATE_IDLE;
static uint8_t encoder_button_primed = 1;
int8_t increment = 0;

static void check_state() {
     if((GPIOB->IDR & GPIO_IDR_IDR6) || (GPIOB->IDR & GPIO_IDR_IDR7)) {
          state = STATE_TRANSITION;
     }
     else {
          state = STATE_IDLE;
     }
}

static void check_dir() {
     if(!(GPIOB->IDR & GPIO_IDR_IDR6) &&
         (GPIOB->IDR & GPIO_IDR_IDR7) && prev_dir == DIRECTION_IDLE) {
          prev_dir = DIRECTION_CLOCKWISE;
     }
     else if((GPIOB->IDR & GPIO_IDR_IDR6) &&
             !(GPIOB->IDR & GPIO_IDR_IDR7) && prev_dir == DIRECTION_IDLE) {
          prev_dir = DIRECTION_COUNTERCLOCKWISE;
     }
     else if(!(GPIOB->IDR & GPIO_IDR_IDR6) &&
             !(GPIOB->IDR & GPIO_IDR_IDR7)) {
          prev_dir = DIRECTION_IDLE;
     }
}

void encoder_update() {
     check_state();
     increment = 0;

     if(state == STATE_IDLE){
          if( prev_dir == DIRECTION_CLOCKWISE ) {
               increment = 1;
          }
          else if( prev_dir == DIRECTION_COUNTERCLOCKWISE ) {
               increment = -1;
          }
     }

     check_dir();
}

uint8_t encoder_button_pressed() {
     if((GPIOB->IDR & GPIO_IDR_IDR3)) {
          encoder_button_primed = 1;    
     }
     else if(encoder_button_primed) {
          encoder_button_primed = 0;
          return 1;
     }

     return 0;
}

uint8_t encoder_state_changed() {
     if( increment != 0 ) {
          return 1;
     }

     return 0;
}

int8_t encoder_get_increment() {
     return increment;
}



#endif