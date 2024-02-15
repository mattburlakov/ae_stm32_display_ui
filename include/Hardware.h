#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include <stm32f10x.h>

#include "spi.h"

#define    SSD1322_RESET GPIOA->BSRR |= GPIO_BSRR_BR3
#define    SSD1322_NRESET GPIOA->BSRR |= GPIO_BSRR_BS3

static void hardware_gpio_init(){
     //GPIOA=============================================================== OK
          RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

          GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
          GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);

          GPIOA->CRL |= (GPIO_CRL_MODE3_0 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE6_0);
          GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_MODE7);
          GPIOA->CRH |= (GPIO_CRH_MODE11_0);
          GPIOA->CRH |= (GPIO_CRH_MODE9 | GPIO_CRH_MODE10);

          GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
          GPIOA->CRL |= (GPIO_CRL_CNF5_1 | GPIO_CRL_CNF7_1);

          GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);
          GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1);
          
          //GPIOA END===========================================================
          //GPIOB===============================================================
          RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

          GPIOB->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
          GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13);

          GPIOB->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_MODE11_1);

          GPIOB->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
          GPIOB->CRL |= (GPIO_CRL_CNF3_0 | GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);

          GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12 | GPIO_CRH_CNF13);
          GPIOB->CRH |= (GPIO_CRH_CNF12_0 | GPIO_CRH_CNF13_0);
          GPIOB->CRH |= (GPIO_CRH_CNF10 | GPIO_CRH_CNF11);

          //GPIOB END===========================================================
          //GPIOC=============================================================== OK
          RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

          GPIOC->CRL &= ~(GPIO_CRL_MODE3);
          GPIOC->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12);

          GPIOC->CRL &= ~(GPIO_CRL_CNF3_0);
          GPIOC->CRL |= (GPIO_CRL_CNF3_0);
          GPIOC->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12);
          GPIOC->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0 | GPIO_CRH_CNF12_0);

          GPIOC->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
          GPIOC->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE15);

          GPIOC->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE2_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1);
          GPIOC->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE15_1);

          GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
          GPIOC->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9 | GPIO_CRH_CNF15);

          //GPIOC END===========================================================
}

static void hardware_spi_init() {
     SSD1322_RESET;

     RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
     SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA |
                    SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_SSM |
                    SPI_CR1_SSI);

     CS_HIGH;

     SPI1->CR1 |= SPI_CR1_SPE;

     for (uint32_t timer = 0; timer < 500; timer++) {
          __NOP();
     }

     SSD1322_NRESET;
}

void hardware_init() {
     hardware_gpio_init();
     hardware_spi_init();
}

void hardware_dc_high() {
     GPIOA->BSRR |= GPIO_BSRR_BS11;
}

void hardware_dc_low() {
     GPIOA->BSRR |= GPIO_BSRR_BR11;
}

void hardware_beep(uint16_t ticks) {
     GPIOA->BSRR |= GPIO_BSRR_BS6;
     for(uint16_t i = 0; i < ticks; ++i){
          __NOP();
     }
     GPIOA->BSRR |= GPIO_BSRR_BR6;
}

#endif