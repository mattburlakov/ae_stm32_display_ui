#include <stm32g474xx.h>

    // =========== OLED SPI ======================
    // PA5 -- SCK
    // PA7 -- MOSI
    // PA15 -- CS
    // PA14 -- RESET

    // PB12 -- SPI2_NSS --CS
    // PB13 -- SPI2_SCK --SCK
    // PB14 -- RESET OLED
    // PB15 -- SPI2_MOSI --SDO

#define		 CS_LOW 	GPIOB->BSRR = GPIO_BSRR_BR12;
#define 	 CS_HIGH 	GPIOB->BSRR = GPIO_BSRR_BS12;

static inline void write_char(uint8_t x_pos, uint8_t y_pos, const uint32_t *Char)  __attribute__((always_inline));

static inline void Spi_Init(void)
{
    // включаем тактирование PortB
    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOBEN;

    GPIOB->MODER  &= ~(GPIO_MODER_MODE12   | GPIO_MODER_MODE13   | GPIO_MODER_MODE14   | GPIO_MODER_MODE15 ); // PB13, PB15 - альтернативная функция, PB12, PB14 - выход
    GPIOB->MODER  |=  (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE15_1  ); // PB13, PB15 - альтернативная функция, PB12, PB14 - выход
    GPIOB->AFR[1] &= ~( GPIO_AFRH_AFSEL13   | GPIO_AFRH_AFSEL15 ); // AF5 для PB13, PB15
    GPIOB->AFR[1] |=  ( GPIO_AFRH_AFSEL13_2 | GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL15_2 | GPIO_AFRH_AFSEL15_0); // AF5 для PB13, PB15

    GPIOB->BSRR |= GPIO_BSRR_BR14; // шлем сброс на PB14

    // включаем SPI2 на тактирование
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;

    SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI; // включаем режим мастера, полярность тактового сигнала
    SPI2->CR2 |= SPI_CR2_DS_3;  // длина фрейма 9-бит
    SPI2->CR2 &= ~(SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2);

    CS_HIGH

    SPI2->CR1 |= SPI_CR1_SPE; // включаем SPI

    for(uint32_t timer=0;timer<500;timer++) {
        __NOP();
    }

    GPIOB->BSRR |= GPIO_BSRR_BS14; // отключаем сброс
}

uint16_t Spi_Write_Data(uint16_t data)
{
        //ждём пока опустошится Tx буфер
	while(!(SPI2->SR & SPI_SR_TXE));
	//активируем Chip Select
	CS_LOW
        //отправляем данные
	SPI2->DR = data;

        //ждём пока придёт ответ
	while(!(SPI2->SR & SPI_SR_RXNE));
        //считываем полученные данные
	data = SPI2->DR;
	//деактивируем Chip Select
	CS_HIGH
        //возвращаем то, что прочитали
       return data;
}

void SSD1322_SPI_Write_D(uint8_t data) {

    Spi_Write_Data(0x0100 | data);
}

void SSD1322_SPI_Write_C(uint8_t cmd) {

    Spi_Write_Data(cmd);
}

void SSD1322_SPI_Write_CD(uint8_t cmd, uint8_t D0) {

    SSD1322_SPI_Write_C(cmd);
    SSD1322_SPI_Write_D(D0);
}

void SSD1322_SPI_Write_CDD(uint8_t cmd, uint8_t D0, uint8_t D1) {

    SSD1322_SPI_Write_C(cmd);
    SSD1322_SPI_Write_D(D0);
    SSD1322_SPI_Write_D(D1);
}

void SSD1322_SPI_Write_CDDD(uint8_t cmd, uint8_t D0, uint8_t D1, uint8_t D2) {

    SSD1322_SPI_Write_C(cmd);
    SSD1322_SPI_Write_D(D0);
    SSD1322_SPI_Write_D(D1);
    SSD1322_SPI_Write_D(D2);
}

void SSD1322_SPI_Write_CDDDD(uint8_t cmd, uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3) {

    SSD1322_SPI_Write_C(cmd);
    SSD1322_SPI_Write_D(D0);
    SSD1322_SPI_Write_D(D1);
    SSD1322_SPI_Write_D(D2);
    SSD1322_SPI_Write_D(D3);
}


/*
static uint8_t *u8x8_ssd1322_8to32(U8X8_UNUSED u8x8_t *u8x8, uint8_t *ptr)
{
  uint8_t v;
  uint8_t a,b;
  uint8_t i, j;
  uint8_t *dest;

  for( j = 0; j < 4; j++ )
  {
    dest = u8x8_ssd1322_to32_dest_buf;
    dest += j;
    a =*ptr;
    ptr++;
    b = *ptr;
    ptr++;
    for( i = 0; i < 8; i++ )
    {
      v = 0;
      if ( a&1 ) v |= 0xf0;
      if ( b&1 ) v |= 0x0f;
      *dest = v;
      dest+=4;
      a >>= 1;
      b >>= 1;
    }
  }

  return u8x8_ssd1322_to32_dest_buf;
}

void SSD1322_SPI_DrawTile(uint8_t x_pos, uint8_t x_offset, uint8_t y_pos, uint8_t y_offset, uint8_t cnt, uint8_t *Data,  u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    uint8_t x;
    uint8_t y, c;
    uint8_t *ptr;

    x = x_pos;
    x *= 2;		// only every 4th col can be addressed
    x += x_offset;

    y = y_pos;
    y *= 8;

    SSD1322_SPI_Write_CDD(0x75,y, y+7); // set row address, moved out of the loop (issue 302)

    do
    {
        c = cnt;
        ptr = Data;

        do
        {
            SSD1322_SPI_Write_CDD(0x15, x, x+1);	// set column address, start, end
            SSD1322_SPI_Write_C(0x5c);	            // write to ram

            u8x8_cad_SendData(u8x8, 32, u8x8_ssd1322_8to32(u8x8, ptr));

            ptr += 8;
            x += 2;
            c--;
        } while( c > 0 );

        //x += 2;
        arg_int--;
    } while( arg_int > 0 );
}
*/

union PixU8_t {
    struct {
        uint8_t pix0:4;
        uint8_t pix1:4;
        uint8_t pix2:4;
        uint8_t pix3:4;
    };
    uint8_t Data[2];
    uint16_t DataW;
};


const uint16_t OLED_Data_Length = 256*64/4;

PixU8_t OLED_Data[OLED_Data_Length] = {0};

static void write_char(const uint8_t x_pos, const uint8_t y_pos, const uint32_t *Char) {

    uint8_t char_pos = 0;
    // Выводим символ
    for(uint8_t i=0;i<8;i++) {
        uint16_t pos = (256/4)*(7-i+y_pos)+(256/4-x_pos);
        OLED_Data[pos+1].DataW = Char[char_pos]>>16;
        OLED_Data[pos].DataW = Char[char_pos++];
    }
}

int main()
{
    //

// PortInit:

    // PB1 -- Лево
    // PB7 -- Право

    // PB10 -- Кнопка Вверх

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;     /* включаем тактирование PortB */
    /* настраиваем GPIO1 */
    // GPIOB->MODER |=  GPIO_MODER_MODER1_0;    /* MODE1=01 */
    // GPIOB->MODER &= ~GPIO_MODER_MODER1_1;    /* MODE1=01 */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER1) | GPIO_MODER_MODER1_0;    /* MODE1=01 */

    /* настраиваем GPI10 */
    GPIOB->MODER &= ~GPIO_MODER_MODER10;      /* MODE10=00 */
    GPIOB->PUPDR |=  GPIO_PUPDR_PUPD10_0;    /* PUPD10=01 */


    Spi_Init();

    SSD1322_SPI_Write_CD(0xfd, 0x12);                 // unlock
    SSD1322_SPI_Write_C(0xae);                        // display off
    SSD1322_SPI_Write_CD(0xb3, 0x91);                 // set display clock divide ratio/oscillator frequency (set clock as 80 frames/sec)
    SSD1322_SPI_Write_CD(0xca, 0x3f);                 // multiplex ratio 1/64 Duty (0x0F~0x3F)
    SSD1322_SPI_Write_CD(0xa2, 0x00);                 // display offset, shift mapping ram counter
    SSD1322_SPI_Write_CD(0xa1, 0x00);                 // display start line
    // SSD1322_SPI_Write_CDD(0xa0, 0x14, 0x11);           // Set Re-Map / Dual COM Line Mode
    //SSD1322_SPI_Write_CDD(0xa0, 0x06, 0x11);          // Set Re-Map / Dual COM Line Mode
    SSD1322_SPI_Write_CDD(0xa0, 0x02, 0x11);          // Set Re-Map / Dual COM Line Mode
    SSD1322_SPI_Write_CD(0xab, 0x01);                 // Enable Internal VDD Regulator
    SSD1322_SPI_Write_CDD(0xb4, 0xa0, 0x05|0xfd);    // Display Enhancement A
    SSD1322_SPI_Write_CD(0xc1, 0xAf);                 // contrast
    SSD1322_SPI_Write_CD(0xc7, 0x0f);                 // Set Scale Factor of Segment Output Current Control
    SSD1322_SPI_Write_C(0xb9);                        // linear grayscale
    SSD1322_SPI_Write_CD(0xb1, 0xe2);                 // Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment
    SSD1322_SPI_Write_CDD(0xd1, 0x82|0x20, 0x20);   // Display Enhancement B
    SSD1322_SPI_Write_CD(0xbb, 0x1f);                 // precharge  voltage
    SSD1322_SPI_Write_CD(0xb6, 0x08);                 // precharge  period
    SSD1322_SPI_Write_CD(0xbe, 0x07);                 // vcomh
    SSD1322_SPI_Write_C(0xa6);                        // normal display
    SSD1322_SPI_Write_C(0xa9);                        // exit partial display

    SSD1322_SPI_Write_C(0xAF);                        // Включаем экран

    for(uint32_t i = 0; i<1000; i++) {
        __NOP();
    }

    SSD1322_SPI_Write_CDD(0x15, 28, 91);// set column address, start, end
    SSD1322_SPI_Write_CDD(0x75, 0, 63); // set row address, moved out of the loop (issue 302)
    SSD1322_SPI_Write_C(0x5C); // Запись в RAM


    for(uint16_t pos=0;pos<OLED_Data_Length;pos++) {
        SSD1322_SPI_Write_D(OLED_Data[pos].Data[1]); // Пишем два пикселя
        SSD1322_SPI_Write_D(OLED_Data[pos].Data[0]); // Пишем два пикселя
    }

    // SSD1322_SPI_Write_C(0xAF);                        // Включаем экран

    /*
    for(uint16_t pos=0;pos<sizeof(OLED_Data_t);pos++) {
        OLED_Data[pos].pix
    }
    */
    // Точки по углам
    OLED_Data[0].pix0 = 0x0F;
    OLED_Data[0].pix1 = 0x09;
    OLED_Data[0].pix2 = 0x05;
    OLED_Data[0].pix3 = 0x01;
    OLED_Data[256/4-1].pix3 = 0x0F;
    OLED_Data[256/4].pix0 = 0x09;
    OLED_Data[2*256/4].pix0 = 0x05;
    OLED_Data[3*256/4].pix0 = 0x01;
    //OLED_Data[(256/4)*63].pix0 = 0x0F;
    //OLED_Data[(256/4)*64-1].pix3 = 0x0F;


    for(uint8_t x=0;x<256/4;x++) {
        uint16_t pos_x = (256/4)*10;
        OLED_Data[pos_x + x].pix0 = 0x0F;
        OLED_Data[pos_x + x].pix1 = 0x0F;
        OLED_Data[pos_x + x].pix2 = 0x0F;
        OLED_Data[pos_x + x].pix3 = 0x0F;
    }

    for(uint8_t x=0;x<256/4;x++) {
        uint16_t pos_x = (256/4)*0;
        OLED_Data[pos_x + x].pix0 = 0x0F;
        OLED_Data[pos_x + x].pix1 = 0x0F;
        OLED_Data[pos_x + x].pix2 = 0x0F;
        OLED_Data[pos_x + x].pix3 = 0x0F;
    }


    for(uint8_t x=0;x<10;x++) {
        uint16_t pos = (256/4)*x;
        OLED_Data[pos].pix0 = 0x0F;
        OLED_Data[pos+12].pix0 = 0x0F;
        OLED_Data[pos+25].pix0 = 0x0F;
        OLED_Data[pos+38].pix0 = 0x0F;
        OLED_Data[pos+51].pix3 = 0x0F;
        OLED_Data[pos+63].pix3 = 0x0F;
    }

    const uint32_t Char_R[] = {
        0x00000000,
        0xFFFF0000,
        0xF000F000,
        0xF000F000,
        0xFFFF0000,
        0xF0F00000,
        0xF00F0000,
        0xF000F000
    };

    const uint32_t Char_E[] = {
        0x00000000,
        0xFFFFF000,
        0xF0000000,
        0xF0000000,
        0xFFFFF000,
        0xF0000000,
        0xF0000000,
        0xFFFFF000
    };

    const uint32_t Char_G[] = {
        0x00000000,
        0x0FFF0000,
        0xF000F000,
        0xF0000000,
        0xF0000000,
        0xF00FF000,
        0xF000F000,
        0x0FFF0000
    };

    const uint32_t Char_CLN[] = {
        0x00000000,
        0x00000000,
        0x00FF0000,
        0x00FF0000,
        0x00000000,
        0x00FF0000,
        0x00FF0000,
        0x00000000
    };

    const uint32_t Char_U[] = {
        0x00000000,
        0xF000F000,
        0xF000F000,
        0xF000F000,
        0xF000F000,
        0xF000F000,
        0xF000F000,
        0x0FFF0000
    };

    const uint32_t Char_I[] = {
        0x00000000,
        0x0FFF0000,
        0x00F00000,
        0x00F00000,
        0x00F00000,
        0x00F00000,
        0x00F00000,
        0x0FFF0000
    };

    const uint32_t Char_P[] = {
        0x00000000,
        0xFFFF0000,
        0xF000F000,
        0xF000F000,
        0xFFFF0000,
        0xF0000000,
        0xF0000000,
        0xF0000000
    };

    write_char(3,2, Char_R);
    write_char(5,2, Char_E);
    write_char(7,2, Char_G);
    write_char(9,2, Char_CLN);
    write_char(11,2, Char_I);
    write_char(13, 2, Char_P);

    static uint32_t Top = 50000;

Work:

    /* переключаем выход PORTA8 в единицу */
    // GPIOB->BSRR |= GPIO_BSRR_BS1;
    GPIOB->ODR |= GPIO_ODR_OD1;

    for(uint32_t i = 0; i<Top; i++) {
        __NOP();
    }

    /* переключаем выход PORTA8 в ноль */
    //GPIOB->BSRR |= GPIO_BSRR_BR1;
    GPIOB->ODR &= ~GPIO_ODR_OD1;

    for(uint32_t i = 0; i<Top; i++) {
        __NOP();
    }

    if (GPIOB->IDR & GPIO_IDR_ID10) {
        Top = 50000;
    }
    else {
        Top = 10000;
    }

    //static uint16_t tmp = 0;
    //tmp++;
    //Spi_Write_Data(tmp);
    //SSD1322_SPI_Write_D(0xFF); // Полная засветка дисплея

    SSD1322_SPI_Write_CDD(0x15, 28, 91);// set column address, start, end
    SSD1322_SPI_Write_CDD(0x75, 0, 63); // set row address, moved out of the loop (issue 302)
    SSD1322_SPI_Write_C(0x5C); // Запись в RAM

    for(uint16_t pos=0;pos<OLED_Data_Length;pos++) {
        SSD1322_SPI_Write_D(OLED_Data[pos].Data[1]); // Пишем два пикселя
        SSD1322_SPI_Write_D(OLED_Data[pos].Data[0]); // Пишем два пикселя
    }

    goto Work; //replace with while?

}
