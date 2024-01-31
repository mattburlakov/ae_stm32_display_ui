#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H

// #include <vector>

#include <stm32g474xx.h>

#include "Label.h"
#include "SPI_Connection.h"

struct Point {
  uint8_t xPos = 0;
  uint8_t yPos = 0;
};

// add pages later

uint8_t t = 8 * 32 / 2;
// array is stored as uint8_t reversed pairs
uint8_t testData[8 * 32 / 2];

uint8_t testData2[8 * 32 / 2];

Label l1(testData, t, 48, 8, 0, 0);
Label l2(testData, t, 48, 8, 0, 15);

/// @brief Contains canvas, array of elemnts to display, drawing functions.
/// @brief Make canvas separate class, flip origins.

class ScreenControl {
 private:
  SPI_Connection* connection = nullptr;

  const uint8_t labelNum = 4;
  Label* page_1[4] = {nullptr, nullptr, nullptr, nullptr};

  const uint16_t dataLen = 256 * 64 / 2;
  uint8_t visualData[256 * 64 / 2] = {0};

  const uint8_t screenWidth = 256 / 2;
  const uint8_t screenHeight = 64;

 public:
  ScreenControl(SPI_Connection* c) {
    connection = c;

    // testing

    page_1[0] = &l1;
    page_1[1] = &l2;
  }
  ~ScreenControl() {}

  void placeLabel(Label* label) {
    // uint8_t c = 0;
    for (uint8_t i = 0; i < label->height; i++) {
      for (uint8_t j = 0; j < label->width / 2; j++) {
        visualData[dataLen - 1 -
                   (label->xPos / 2 + label->yPos * screenWidth +
                    i * screenWidth + j)] =
            label->data[i * label->width / 2 + j + 1];
        visualData[dataLen - 1 -
                   (label->xPos / 2 + label->yPos * screenWidth +
                    i * screenWidth + j + 1)] =
            label->data[i * label->width / 2 + j];
        j++;
      }
    }
  }

  void assembleFrame() {  // combine /w placeLabel()
    for (uint16_t i = 0; i < labelNum; i++) {
      placeLabel(page_1[i]);
    }
  }

  void draw() {
    connection->SSD1322_write_C2D(0x15, 28,
                                  91);  // set column address, start, end
    connection->SSD1322_write_C2D(
        0x75, 0, 63);  // set row address, moved out of the loop (issue 302)
    connection->SSD1322_write_C(0x5C);  // Запись в RAM

    for (uint16_t i = 0; i < dataLen; i++) {
      connection->SSD1322_write_D(visualData[i]);
    }
  }

  void clearScreen() {
    for (uint16_t i = 0; i < dataLen; i++) {
      visualData[i] = 0x00;
    }
  }

  /// @brief Draw horizontal line.
  /// @param[in] orig Point 1.
  /// @param[in] dst Point 2.
  /// @todo replace orig and dst with orig and width.
  void draw_horizontal(Point orig, Point dst) {
    if (orig.xPos - dst.xPos < 0)  // right
    {
      for (uint8_t i = orig.xPos; i < dst.xPos; ++i)
        visualData[128 * dst.yPos + i] |= 0xff;
    } else  // left
    {
      for (uint8_t i = orig.xPos; i > dst.xPos; --i)
        visualData[128 * dst.yPos + i] |= 0xff;
    }
  }

  /// @brief Draw vertical line.
  /// @param[in] orig Point 1.
  /// @param[in] dst Point 2.
  /// @todo replace orig and dst with orig and height.
  void draw_vertical(Point orig, Point dst) {
    uint8_t draw_byte = 0x00;

    if (orig.xPos % 2 == 0)
      draw_byte = 0x0f;
    else
      draw_byte = 0xf0;

    if (!(dst.xPos >= 128))  // what
      dst.xPos += 1;
    else {
      draw_byte = 0xf0;
      dst.xPos = 126;
    }

    if (orig.yPos - dst.yPos < 0)  // up
    {
      for (uint8_t i = orig.yPos; i <= dst.yPos; ++i)
        visualData[i * 128 + dst.xPos] |= draw_byte;
    } else  // down
    {
      for (uint8_t i = orig.yPos; i >= dst.yPos; --i)
        visualData[i * 128 + dst.xPos] |= draw_byte;
    }
  }

  /// @brief Draw hollow rectangle.
  /// @param[in] orig Point 1.
  /// @param[in] dst Point 2.
  /// @todo replace orig and dst /w P1 and P2.
  void draw_rect(Point orig, Point dst) {
    Point tmp;
    tmp.xPos = dst.xPos;
    tmp.yPos = dst.yPos;

    draw_horizontal(orig, tmp);
    tmp.yPos = orig.yPos;

    draw_horizontal(orig, tmp);
    tmp.xPos = orig.xPos;
    tmp.yPos = dst.yPos;

    draw_vertical(orig, tmp);
    tmp.xPos = dst.xPos;

    draw_vertical(orig, tmp);
  }

  /// @brief Draw filled rectangle.
  /// @param[in] orig Point 1.
  /// @param[in] dst Point 2.
  /// @todo replace orig and dst /w P1 and P2.
  /// @todo remake fun in a human way.
  void draw_rect_fill(Point orig, Point dst) {
    if (orig.yPos < dst.yPos) {
      Point tmp;
      tmp.xPos = dst.xPos;
      tmp.yPos = orig.yPos;

      for (uint8_t i = orig.yPos; i < dst.yPos; ++i) {
        draw_horizontal(orig, tmp);
        tmp.yPos++;
        orig.yPos++;
      }
    } else {
      Point tmp;
      tmp.xPos = orig.xPos;
      tmp.yPos = dst.yPos;

      for (uint8_t i = dst.yPos; i < orig.yPos; ++i) {
        draw_horizontal(dst, tmp);
        orig.yPos++;
        tmp.yPos++;
      }
    }
  }
};

#endif
