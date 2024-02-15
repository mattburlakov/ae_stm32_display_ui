#ifndef SSD1322_H
#define SSD1322_H

#include <stdint.h>
#include <stm32f10x.h>

#include "hardware.h"
#include "spi.h"

static void ssd1322_write_D(uint8_t data) {
     hardware_dc_high();
     spi__write_data(0x0100 | data);
}

static void ssd1322_write_C(uint8_t cmd) { 
     hardware_dc_low();
     spi__write_data(cmd); 
}

static void ssd1322_write_CD(uint8_t cmd, uint8_t D0) {
     ssd1322_write_C(cmd);
     ssd1322_write_D(D0);
}

static void ssd1322_write_C2D(uint8_t cmd, uint8_t D0, uint8_t D1) {
     ssd1322_write_C(cmd);
     ssd1322_write_D(D0);
     ssd1322_write_D(D1);
}

static void ssd1322_write_C3D(uint8_t cmd, uint8_t D0, uint8_t D1, uint8_t D2) {
     ssd1322_write_C(cmd);
     ssd1322_write_D(D0);
     ssd1322_write_D(D1);
     ssd1322_write_D(D2);
}

static void ssd1322_write_C4D(uint8_t cmd,
                         uint8_t D0,
                         uint8_t D1,
                         uint8_t D2,
                         uint8_t D3) {
     ssd1322_write_C(cmd);
     ssd1322_write_D(D0);
     ssd1322_write_D(D1);
     ssd1322_write_D(D2);
     ssd1322_write_D(D3);
}

/// @brief Init Winstar SSD1322 display.
void ssd1322_init() {
     ssd1322_write_CD(0xfd, 0x12);  // unlock
     ssd1322_write_C2D(0x15, 28, 91);  // set column address, start, end
     ssd1322_write_C2D(0x75, 0, 63);  // set row address, moved out of the loop (issue 302)
     ssd1322_write_C2D(0xa0, 0x02, 0x11);  // (было 0x10 0x11) Set Re-Map / Dual COM Line Mode
     ssd1322_write_CD(0xa1, 0x00);  // display start line
     ssd1322_write_CD(0xa2, 0x00);  // display offset, shift mapping ram counter
     ssd1322_write_C(0xa6);  // normal display
     //ssd1322_write_C2D(0xa8, 0x00, 0x3f);  //enable partial display
     ssd1322_write_C(0xa9);         // exit partial display
     ssd1322_write_CD(0xab, 0x01);  // enable internal VDD regulator
     ssd1322_write_CD(0xb1, 0xe8);  // Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment
     ssd1322_write_CD(0xb3, 0x91);  // set display clock divide ratio/oscillator frequency (set clock as 80 frames/sec)
     ssd1322_write_C2D(0xb4, 0xa0, 0xfd);       // Display Enhancement A (VSL)
     ssd1322_write_CD(0xb5, 0x00);  // GPIO
     ssd1322_write_CD(0xb6, 0x1F);  // precharge current period
     ssd1322_write_C(0xB8);         // Set Gray Scale Table(ver 3.0)
     ssd1322_write_D(0);            // Gray Scale Level 1 
     ssd1322_write_D(0);            // Gray Scale Level 2
     ssd1322_write_D(0);            // Gray Scale Level 3
     ssd1322_write_D(3);            // Gray Scale Level 4
     ssd1322_write_D(6);            // Gray Scale Level 5
     ssd1322_write_D(16);           // Gray Scale Level 6
     ssd1322_write_D(29);           // Gray Scale Level 7
     ssd1322_write_D(42);           // Gray Scale Level 8
     ssd1322_write_D(55);           // Gray Scale Level 9
     ssd1322_write_D(70);           // Gray Scale Level 10
     ssd1322_write_D(88);           // Gray Scale Level 11
     ssd1322_write_D(106);          // Gray Scale Level 12
     ssd1322_write_D(127);          // Gray Scale Level 13
     ssd1322_write_D(150);          // Gray Scale Level 14
     ssd1322_write_D(180);          // Gray Scale Level 15
     ssd1322_write_D(0x00);         // Enable Gray Scale Table

     ssd1322_write_CD(0xbb, 0x0f);         // precharge  voltage
     ssd1322_write_CD(0xbe, 0x07);         // set VCOMH
     ssd1322_write_C2D(0xd1, 0x82, 0x20);  //
     ssd1322_write_CD(0xc1, 0xdf);         // set contrast current
     ssd1322_write_CD(0xc7, 0x0f);  // master Contrast current Control
     ssd1322_write_CD(0xca, 0x3f);                   // multiplex ratio 1/64 Duty (0x0F~0x3F)
     ssd1322_write_C(0xaf);         // Включаем экран (ae=OFF af=ON)

     for(uint32_t i = 0; i<1000; i++) {
        __NOP();
     }
}

/// @brief Send a buffer to SPI line.
/// @param buf Buffer pointer.
/// @param size Buffer size.
void ssd1322_send_graphics(uint8_t* buf, uint16_t size) {
     ssd1322_write_C2D(0x15, 28, 91);  // set column address, start, end
     ssd1322_write_C2D(0x75, 0, 63);  // set row address, moved out of the loop (issue 302)
     ssd1322_write_C(0x5C);  // Запись в RAM

     for (uint16_t i = size - 1; i >= 2; i--) {
          ssd1322_write_D(buf[i - 1]);
          ssd1322_write_D(buf[i]);
          i--;
     }
}

#endif
