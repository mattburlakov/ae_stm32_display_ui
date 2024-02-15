#include <stdlib.h>
#include <stm32g474xx.h>

#include "include/Canvas.h"  //deal /w capital letters
#include "include/SPI_Connection.h"

#include "include/zero_font.h"

// add timers for animation / update rate

const char* label_voltage = "VOLTAGE";
const char* label_current = "CURRENT";
const char* label_power = "POWER";
const char* label_channel_test = "CHANNEL TEST";
const char* label_error = "ERROR";
const char* extreme = "EXTREMELY LONG STRING OF CHARACTERS";

int main() {
     SPI_Connection connection;  // Create SPI2 connection object

     // TODO: add defines for screen commands.

     connection.SSD1322_write_CD(0xfd, 0x12);  // unlock
     connection.SSD1322_write_C(0xae);         // display off
     connection.SSD1322_write_CD(
         0xb3, 0x91);  // set display clock divide ratio/oscillator frequency
                       // (set clock as 80 frames/sec)
     connection.SSD1322_write_CD(
         0xca,
         0x3f);  // multiplex ratio 1/64 Duty (0x0F~0x3F)
     connection.SSD1322_write_CD(
         0xa2, 0x00);  // display offset, shift mapping ram counter
     connection.SSD1322_write_CD(0xa1, 0x00);  // display start line
     // SSD1322_SPI_Write_CDD(0xa0, 0x14, 0x11);           // Set Re-Map / Dual
     // COM Line Mode SSD1322_SPI_Write_CDD(0xa0, 0x06, 0x11);          // Set
     // Re-Map / Dual COM Line Mode
     connection.SSD1322_write_C2D(
         0xa0, 0x02,
         0x11);  // Set Re-Map / Dual COM Line Mode 02 - reversed | 11 - normal
     connection.SSD1322_write_CD(0xab, 0x01);  // Enable Internal VDD Regulator
     connection.SSD1322_write_C2D(0xb4, 0xa2, 0xfd);  // Display Enhancement A
     connection.SSD1322_write_CD(0xc1, 0xaf);         // contrast
     connection.SSD1322_write_CD(
         0xc7, 0x0f);  // Set Scale Factor of Segment Output Current Control
     connection.SSD1322_write_C(0xb9);  // linear grayscale
     connection.SSD1322_write_CD(
         0xb1,
         0xe2);  // Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment
     connection.SSD1322_write_C2D(0xd1, 0x82 | 0x20,
                                  0x20);       // Display Enhancement B
     connection.SSD1322_write_CD(0xbb, 0x1f);  // precharge  voltage
     connection.SSD1322_write_CD(0xb6, 0x08);  // precharge  period
     connection.SSD1322_write_CD(0xbe, 0x07);  // vcomh
     connection.SSD1322_write_C(0xa6);         // normal display
     connection.SSD1322_write_C(0xa9);         // exit partial display

     connection.SSD1322_write_C(0xaf);  // Включаем экран

     // connection.SSD1322_write_CD(0xfd, 0x12);  // unlock
     // connection.SSD1322_write_C2D(0x15, 28,
     //                              91);  // set column address, start, end
     // connection.SSD1322_write_C(0x5C);  // Запись в RAM
     // connection.SSD1322_write_C(0x5D);  // Чтение из RAM
     // connection.SSD1322_write_C2D(
     //     0x75, 0, 63);  // set row address, moved out of the loop (issue 302)
     // connection.SSD1322_write_C2D(
     //     0xa0, 0x02, 0x11);  // (было 0x02 0x11) Set Re-Map / Dual COM Line
     //     Mode
     // connection.SSD1322_write_CD(0xa1, 0x00);  // display start line
     // connection.SSD1322_write_CD(
     //     0xa2,
     //     0x00);  // display offset, shift mapping ram counter
     // connection.SSD1322_write_C(
     //     0xa6);  // normal display
     //             // connection.SSD1322_write_C2D(0xa8, 0x00, 0x3f);
     //             // //enable partial display
     // connection.SSD1322_write_C(0xa9);         // exit partial display
     // connection.SSD1322_write_CD(0xab, 0x01);  // enable internal VDD
     // regulator connection.SSD1322_write_CD(
     //     0xb1,
     //     0xe8);  // Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment
     // connection.SSD1322_write_CD(
     //     0xb3,
     //     0x91);  // set display clock divide ratio/oscillator
     //             // frequency (set clock as 80 frames/sec)
     // connection.SSD1322_write_C2D(0xb4, 0xa2,
     //                              0xfd);       // Display Enhancement A (VSL)
     // connection.SSD1322_write_CD(0xb5, 0x00);  // GPIO
     // connection.SSD1322_write_CD(0xb6, 0x1F);  // precharge current period
     // connection.SSD1322_write_C(0xB8);         // Set Gray Scale Table
     // (ver 3.0) connection.SSD1322_write_D(0);            // Gray Scale Level
     // 1 connection.SSD1322_write_D(0);            // Gray Scale Level 2
     // connection.SSD1322_write_D(0);            // Gray Scale Level 3
     // connection.SSD1322_write_D(3);            // Gray Scale Level 4
     // connection.SSD1322_write_D(6);            // Gray Scale Level 5
     // connection.SSD1322_write_D(16);           // Gray Scale Level 6
     // connection.SSD1322_write_D(29);           // Gray Scale Level 7
     // connection.SSD1322_write_D(42);           // Gray Scale Level 8
     // connection.SSD1322_write_D(55);           // Gray Scale Level 9
     // connection.SSD1322_write_D(70);           // Gray Scale Level 10
     // connection.SSD1322_write_D(88);           // Gray Scale Level 11
     // connection.SSD1322_write_D(106);          // Gray Scale Level 12
     // connection.SSD1322_write_D(127);          // Gray Scale Level 13
     // connection.SSD1322_write_D(150);          // Gray Scale Level 14
     // connection.SSD1322_write_D(180);          // Gray Scale Level 15
     // connection.SSD1322_write_D(0x00);         // Enable Gray Scale Table

     // connection.SSD1322_write_CD(0xbb, 0x0f);         // precharge  voltage
     // connection.SSD1322_write_CD(0xbe, 0x07);         // set VCOMH
     // connection.SSD1322_write_C2D(0xd1, 0x82, 0x20);  //
     // connection.SSD1322_write_CD(0xc1, 0xdf);         // set contrast current
     // connection.SSD1322_write_CD(0xc7,
     //                             0x0f);  // master Contrast current Control
     // connection.SSD1322_write_CD(
     //     0xca, 0x3f);                   // multiplex ratio 1/64 Duty
     //     (0x0F~0x3F)
     // connection.SSD1322_write_C(0xaf);  // Включаем экран (ae=OFF af=ON)

     //-------------------------------------------------------------------------
     uint8_t buffer[256 / 2 * 64];

     Canvas mainCanvas;
     mainCanvas.canvas_set_size(256 / 2, 64);
     mainCanvas.canvas_set_pixel_buffer(buffer);

     mainCanvas.erase();

     mainCanvas.draw_rect(0, 56, 254, 7, DIM);

     // ============================
     uint8_t x_base = 0;

     for (uint8_t i = 0; i < 3; ++i) {
          mainCanvas.draw_rect(x_base, 0, 80, 40,
                               DIM);  // add priority to bright ones.

          mainCanvas.draw_vertical_primitive(x_base + 80, 56, 7, DIM);

          mainCanvas.draw_text(label_voltage, zf::zero_font, 7, x_base + 3, 3,
                               zf::width, zf::height);
          mainCanvas.draw_text(label_current, zf::zero_font, 7, x_base + 3, 13,
                               zf::width, zf::height);
          mainCanvas.draw_text(label_power, zf::zero_font, 5, x_base + 3, 23,
                               zf::width, zf::height);

          mainCanvas.draw_text(label_channel_test, zf::zero_font, 12,
                               x_base + 3, 58, zf::width, zf::height);
          x_base += 80;
     }
     // ============================

     connection.SSD1322_send_graphics(mainCanvas.pixels, 256 / 2 * 64);

     while (true) {
     }

     //-------------------------------------------------------------------------
}
