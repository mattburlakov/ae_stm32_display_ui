#ifndef SPI_CONNECTION_H
#define SPI_CONNECTION_H

#include <stm32g474xx.h>

#ifndef CS_LOW
#define		 CS_LOW 	GPIOB->BSRR = GPIO_BSRR_BR12;
#endif

#ifndef CS_HIGH
#define 	 CS_HIGH 	GPIOB->BSRR = GPIO_BSRR_BS12;
#endif

class SPI_Connection{
private:
public:
    SPI_Connection(){
        RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOBEN;   // включаем тактирование PortB

        GPIOB->MODER  &= ~(GPIO_MODER_MODE12   | GPIO_MODER_MODE13   | GPIO_MODER_MODE14   | GPIO_MODER_MODE15 );       // PB13, PB15 - альтернативная функция, PB12, PB14 - выход
        GPIOB->MODER  |=  (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE15_1  );    // PB13, PB15 - альтернативная функция, PB12, PB14 - выход
        GPIOB->AFR[1] &= ~( GPIO_AFRH_AFSEL13   | GPIO_AFRH_AFSEL15 );                                                  // AF5 для PB13, PB15
        GPIOB->AFR[1] |=  ( GPIO_AFRH_AFSEL13_2 | GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL15_2 | GPIO_AFRH_AFSEL15_0);     // AF5 для PB13, PB15

        GPIOB->BSRR |= GPIO_BSRR_BR14;          // шлем сброс на PB14

        RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;   // включаем SPI2 на тактирование

        SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI; // включаем режим мастера, полярность тактового сигнала
        SPI2->CR2 |= SPI_CR2_DS_3;              // длина фрейма 9-бит
        SPI2->CR2 &= ~(SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2);

        CS_HIGH

        SPI2->CR1 |= SPI_CR1_SPE;               // включаем SPI

        for(uint32_t timer=0;timer<500;timer++) {
            __NOP();
        }

        GPIOB->BSRR |= GPIO_BSRR_BS14;          // отключаем сброс
    }

    ~SPI_Connection(){

    }

    uint16_t write_data(uint16_t data){
        while(!(SPI2->SR & SPI_SR_TXE));    //ждём пока опустошится Tx буфер

        CS_LOW                              //активируем Chip Select

        SPI2->DR = data;                    //отправляем данные

        while(!(SPI2->SR & SPI_SR_RXNE));   //ждём пока придёт ответ

        data = SPI2->DR;                    //считываем полученные данные

        CS_HIGH                             //деактивируем Chip Select

        return data;                        //возвращаем то, что прочитали
    }

    void SSD1322_write_D(uint8_t data){
        write_data(0x0100 | data);          //append data to 0x01
    }

    void SSD1322_write_C(uint8_t cmd){
        write_data(cmd);
    }

    void SSD1322_write_CD(uint8_t cmd, uint8_t D0) {

        SSD1322_write_C(cmd);
        SSD1322_write_D(D0);
    }

    void SSD1322_write_C2D(uint8_t cmd, uint8_t D0, uint8_t D1) {

        SSD1322_write_C(cmd);
        SSD1322_write_D(D0);
        SSD1322_write_D(D1);
    }

    void SSD1322_write_C3D(uint8_t cmd, uint8_t D0, uint8_t D1, uint8_t D2) {

        SSD1322_write_C(cmd);
        SSD1322_write_D(D0);
        SSD1322_write_D(D1);
        SSD1322_write_D(D2);
    }

    void SSD1322_write_C4D(uint8_t cmd, uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3) {

        SSD1322_write_C(cmd);
        SSD1322_write_D(D0);
        SSD1322_write_D(D1);
        SSD1322_write_D(D2);
        SSD1322_write_D(D3);
    }
};

#endif
