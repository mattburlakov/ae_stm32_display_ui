#include <stm32g474xx.h>

#include "include/ScreenControl.h"

#include "include/FONT_A.h"  //test font

#include "include/Font.h"
#include "include/Label.h"
#include "include/ScreenControl.h"

#include "include/SPI_Connection.h"

int main() {
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER1) | GPIO_MODER_MODER1_0;
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER7) | GPIO_MODER_MODER7_0;

  SPI_Connection connection;          // Create SPI2 connection object
  ScreenControl screen(&connection);  // Create Screen control handler and bind
                                      // to SPI2 connection obj

  connection.SSD1322_write_CD(0xfd, 0x12);  // unlock
  connection.SSD1322_write_C(0xae);         // display off
  connection.SSD1322_write_CD(
      0xb3, 0x91);  // set display clock divide ratio/oscillator frequency (set
                    // clock as 80 frames/sec)
  connection.SSD1322_write_CD(0xca,
                              0x3f);  // multiplex ratio 1/64 Duty (0x0F~0x3F)
  connection.SSD1322_write_CD(
      0xa2, 0x00);  // display offset, shift mapping ram counter
  connection.SSD1322_write_CD(0xa1, 0x00);  // display start line
  // SSD1322_SPI_Write_CDD(0xa0, 0x14, 0x11);           // Set Re-Map / Dual COM
  // Line Mode
  // SSD1322_SPI_Write_CDD(0xa0, 0x06, 0x11);          // Set Re-Map / Dual COM
  // Line Mode
  connection.SSD1322_write_C2D(0xa0, 0x02,
                               0x11);       // Set Re-Map / Dual COM Line Mode
  connection.SSD1322_write_CD(0xab, 0x01);  // Enable Internal VDD Regulator
  connection.SSD1322_write_C2D(0xb4, 0xa0,
                               0x05 | 0xfd);  // Display Enhancement A
  connection.SSD1322_write_CD(0xc1, 0xAf);    // contrast
  connection.SSD1322_write_CD(
      0xc7, 0x0f);  // Set Scale Factor of Segment Output Current Control
  connection.SSD1322_write_C(0xb9);  // linear grayscale
  connection.SSD1322_write_CD(
      0xb1, 0xe2);  // Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment
  connection.SSD1322_write_C2D(0xd1, 0x82 | 0x20,
                               0x20);       // Display Enhancement B
  connection.SSD1322_write_CD(0xbb, 0x1f);  // precharge  voltage
  connection.SSD1322_write_CD(0xb6, 0x08);  // precharge  period
  connection.SSD1322_write_CD(0xbe, 0x07);  // vcomh
  connection.SSD1322_write_C(0xa6);         // normal display
  connection.SSD1322_write_C(0xa9);         // exit partial display

  connection.SSD1322_write_C(0xAF);  // Включаем экран

  // Predetermined points \/\/\/
  Point p1;
  p1.xPos = 64;
  p1.yPos = 32;

  Point p11;
  p11.xPos = 64;
  p11.yPos = 54;

  Point p2;
  p2.xPos = 128;
  p2.yPos = 40;

  Point p22;
  p22.xPos = 96;
  p22.yPos = 63;

  Point p3;
  p3.xPos = 128;
  p3.yPos = 48;

  Point p4;
  p4.xPos = 128;
  p4.yPos = 54;

  Point p5;
  p5.xPos = 128;
  p5.yPos = 63;

  Point zero;
  zero.xPos = 0;
  zero.yPos = 0;

  Point p6;
  p6.xPos = 128;
  p6.yPos = 8;

  Point separator;
  separator.xPos = 100;
  separator.yPos = 63;

  // Predetermined points /\/\/\

  while (true) {
    // draw grid \/\/\/
    screen.assembleFrame();

    screen.draw_rect(p1, p2);
    screen.draw_rect(p1, p3);
    screen.draw_rect(p1, p4);
    screen.draw_rect(p1, p5);

    screen.draw_rect(p1, p2);

    screen.draw_vertical(p1, separator);

    screen.draw_rect(zero, p6);

    screen.draw_rect_fill(p11, p22);
    // draw grid /\/\/\

    // draw text
    screen.draw();
  }
}
