#ifndef CANVAS_H
#define CANVAS_H

//[space]!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
// start on 20; 95 chars

#include <stdint.h>

enum Brightness { NONE, LOW = 0x02, DIM = 0x04, MEDIUM = 0x08, BRIGHT = 0x0F };
enum RectangleFill { NOFILL, FILL };
struct Canvas {
     uint8_t width = 0;
     uint8_t height = 0;
     uint8_t* pixels = nullptr;

     /// @brief Init canvas size;
     /// @param[in] w Canvas width;
     /// @param[in] h Canvas height;
     void canvas_set_size(uint8_t w, uint8_t h) {
          width = w;
          height = h;
     }

     /// @brief Bind canvas to pixel buffer;
     /// @param[in] buf Pixel buffer, representing an actual screen.
     /// @todo Add protection against buffers too big for set canvas dimensions.
     void canvas_set_pixel_buffer(uint8_t* buf) { pixels = buf; }

     /// @brief Change brightness of a selected pixel on canvas.
     /// @param[in] x x-position of a pixel to edit.
     /// @param[in] y y-position of a pixel to edit.
     /// @param[in] b Required brightness.
     void draw_pixel(uint8_t x, uint8_t y, uint8_t b) {
          if (x % 2 == 0) {
               x /= 2;
               pixels[x + width * y] &= ~0xF0;
               pixels[x + width * y] |= 0xF0 & (b << 4);
               return;
          }

          x += 1;
          x /= 2;
          x -= 1;
          pixels[x + width * y] &= ~0x0F;
          pixels[x + width * y] |= 0x0F & b;
     }

     /// @brief Draws a vertical line from target point downwards.
     /// @param[in] x x-position of line origin.
     /// @param[in] y y-position of line origin.
     /// @param[in] len Line length.
     /// @param[in] b Line brightness: NONE, LOW, DIM, MEDIUM, BRIGHT.
     void draw_vertical_primitive(uint8_t x,
                                  uint8_t y,
                                  uint8_t len,
                                  enum Brightness b) {
          len += y;  // remove hardcode
          if (len > 63) {
               len = 63;
          }
          for (uint8_t i = y; i <= len; ++i) {
               draw_pixel(x, i, b);
          }
     }

     /// @brief Draws a horizontal line from target point eastwards.
     /// @param[in] x x-position of line origin.
     /// @param[in] y y-position of line origin.
     /// @param[in] len Line length.
     /// @param[in] b Line brightness: NONE, LOW, DIM, MEDIUM, BRIGHT.
     void draw_horizontal_primitive(uint8_t x,
                                    uint8_t y,
                                    uint8_t len,
                                    enum Brightness b) {
          len += x;  // remove hardcode
          if (len > 255) {
               len = 255;
          }
          for (uint8_t i = x; i <= len; ++i) {
               draw_pixel(i, y, b);
          }
     }

     /// @brief Draws a line connectiong two points.
     void draw_line() {}

     /// @brief Draws a rectangle from the required origin point.
     /// @param[in] x x-position of origin point.
     /// @param[in] y y-position of origin point.
     /// @param[in] w Rectangle width.
     /// @param[in] h Rectangle height.
     /// @param[in] b Rectangle brightness: NONE, LOW, DIM, MEDIUM, BRIGHT.
     /// @param[in] f Rectangle fillament: NOFILL(default), FILL.
     void draw_rect(uint8_t x,
                    uint8_t y,
                    uint8_t w,
                    uint8_t h,
                    enum Brightness b,
                    enum RectangleFill f = NOFILL) {
          switch (f) {
               case NOFILL: {
                    draw_horizontal_primitive(x, y, w, b);
                    draw_horizontal_primitive(x, y + h, w, b);
                    draw_vertical_primitive(x, y, h, b);
                    draw_vertical_primitive(x + w, y, h, b);

                    break;
               }

               case FILL: {  // can be used for progress bars
                    for (uint8_t i = 0; i <= h; ++i) {
                         draw_horizontal_primitive(x, y + i, w, b);
                    }
                    break;
               }

               default:
                    break;
          }
     }

     /// @brief Draws a circle from the required origin point.
     void draw_circle() {}

     /// @brief Draw from data buffer.
     /// @param buffer Data buffer.
     /// @param[in] x x-position of origin point.
     /// @param[in] y y-position of origin point.
     /// @param[in] w Data buffer width.
     /// @param[in] h Data buffer height.
     void draw_data(const uint8_t* buffer,
                    uint8_t x,
                    uint8_t y,
                    uint8_t w,
                    uint8_t h,
                    bool invert = false) {
          for (uint8_t i = 0; i < h; ++i) {
               for (uint8_t j = 0; j < w; ++j) {
                    // rework xor, possibly overload
                    if( invert ) {
                         pixels[x / 2 + y * width + j + i * width] ^= buffer[j + i * w];
                    }
                    else{
                         pixels[x / 2 + y * width + j + i * width] |= buffer[j + i * w];
                    }
               }
          }
     }

     /// @brief Draw a text string.
     /// @param[in] label String of ASCII characters.
     /// @param[in] size String length in characters.
     /// @param[in] x X position of string on screen.
     /// @param[in] y Y position of string on screen.
     /// @param[in] font Font. @todo replace /w class/struct.
     /// @param[in] char_w Width of a single characetr. @todo Remove later.
     /// @param[in] char_h Height of a single characetr. @todo Remove later.
     void draw_text(const char* label,
                    uint8_t size,
                    uint8_t x,
                    uint8_t y,

                    const uint8_t** font,
                    uint8_t char_w,
                    uint8_t char_h,

                    bool invert = false) {
          const uint8_t* test_word;
          for (uint8_t i = 0; i < size; ++i) {
               if (label[i] != 32) {
                    test_word = font[label[i] - 48];
                    draw_data( test_word, x + char_w * i * 2, y, char_w, char_h, invert );
               }
          }
     }

     /// @brief Erases canvas.
     void erase() {
          for (uint16_t i = 0; i < width * height; ++i) {
               pixels[i] = 0x00;
          }
     }
};

#endif