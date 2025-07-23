#include "exti.h"

#include <stm32f10x.h>

enum {
     EXTI_IRQN_ENCODER_A = 7,
     EXTI_IRQN_ENCODER_B = 6,
};

enum Exti {
     EXTI_ENCODER_A,
     EXTI_ENCODER_B,

     EXTI_COUNTER,
};

struct ExtiConfig {
     uint32_t afio;

     uint32_t interrupt_mask;
     IRQn_Type irqn;
     uint32_t falling_edge_mask;
};

static const struct ExtiConfig exti[] = {
     [ EXTI_ENCODER_A ] = {
          .afio               = AFIO_EXTICR2_EXTI7_PB,
          .interrupt_mask     = EXTI_IMR_MR7,
          .irqn               = EXTI9_5_IRQn,
          .falling_edge_mask  = EXTI_FTSR_TR7,
     },
     [ EXTI_ENCODER_B ] = {
          .afio               = AFIO_EXTICR2_EXTI6_PB,
          .interrupt_mask     = EXTI_IMR_MR6,
          .irqn               = EXTI9_5_IRQn,
          .falling_edge_mask  = EXTI_FTSR_TR6,
     },
};

volatile HandlerCallback handler_callback = nullptr;

static void init_exti( const struct ExtiConfig* instance ) {
     NVIC_EnableIRQ( instance->irqn );

     AFIO->EXTICR[ 1 ]   |= instance->afio;
     EXTI->IMR           |= instance->interrupt_mask;
     EXTI->FTSR          |= instance->falling_edge_mask;

     EXTI->PR = instance->interrupt_mask;
}

void exti_init( void ) {
     RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

     for( uint8_t idx = 0; idx < EXTI_COUNTER; ++idx ) {
          init_exti( &exti[ idx ] );
     }
}

void exti_set_callback( HandlerCallback function ) {
     handler_callback = function;
}

extern "C" void EXTI9_5_IRQHandler( void ) {
     if( EXTI->PR & ( 0x01 << EXTI_IRQN_ENCODER_A ) ) {
          EXTI->PR = ( 0x01 << EXTI_IRQN_ENCODER_A );

          if( handler_callback ) {
               handler_callback();
          }
     }
     else if( EXTI->PR & ( 0x01 << EXTI_IRQN_ENCODER_B ) ) {
          EXTI->PR = ( 0x01 << EXTI_IRQN_ENCODER_B);

          if( handler_callback ) {
               handler_callback();
          }
     }
}
