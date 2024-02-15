#ifndef PARAMETER_H
#define PARAMETER_H

#include <stdint.h>

#include "Canvas.h"
#include "zero_font.h"
#include "dummy_font.h"

// TODO add magic

enum Flag {
     FLAG_IS_LABEL = 0b0000'0001,
};

enum Units {
     UNITS_MILLI_V = 0,
     UNITS_V,
     UNITS_KILO_V,

     UNITS_MILLI_A,
     UNITS_A,
     UNITS_KILO_A,

     UINTS_MILLI_W,
     UNITS_W,
     UINTS_KILO_W,

     UNITS_NONE,
};

const char* units[] = { "mV", "V ", "kV",
                        "mA", "A ", "kA",
                        "mW", "W ", "kW" };

void* ParameterUpdateFunction ();

class Parameter {
     protected:
          char* name = nullptr;
          uint8_t name_length = 0;

          uint16_t value = 0;
          uint8_t flags = 0;

          enum Units unit = UNITS_NONE;

     public:
          Parameter(char* parameter_name, uint8_t parameter_name_length, 
                    uint16_t v,
                    uint8_t flag,
                    enum Units u = UNITS_NONE) {
               name = parameter_name;
               name_length = parameter_name_length;

               value = v;

               flags = flag;

               unit = u;
          }

          ~Parameter() {}

          void set_value(uint16_t v) {
               value = v;
          }

          void increment(int8_t i) {
               if(i < 0 && value == 0) {
                    value = 0;
                    return;
               }
               value += i;
          }

          void draw(Canvas* canvas, uint8_t x_origin, uint8_t y_origin, bool inverted = true ) {
               // ADD FONT AS PARAMETER
               const uint8_t** font = df::dummy_font;
               uint8_t font_w = df::width;
               uint8_t font_h = df::height;

               canvas->draw_text( name, name_length,
                                   x_origin + 2, y_origin + 2,
                                   font,
                                   font_w, font_h, inverted );

               if( !(flags & FLAG_IS_LABEL) ) {
                    // DRAW VALUE===============================================

                    char char_tmp[10];
                    char* val_str = &char_tmp[0];
                    uint8_t val_len = 0;
                    uint16_t val_tmp = value;

                    while(val_tmp > 0) { // separate into utility
                         val_len++;
                         val_tmp /= 10;
                    }

                    val_tmp = value;

                    uint8_t counter = val_len - 1;
                    for(uint8_t i = 0; i < val_len; ++i) {
                         char_tmp[counter] = val_tmp % 10 + 48;
                         val_tmp /= 10;
                         counter--;
                    }

                    canvas->draw_text( char_tmp, val_len,
                                        x_origin + 24, y_origin + 2,
                                        font,
                                        font_w, font_h, inverted );
                    // DRAW UNITS ==============================================
                    if ( unit != UNITS_NONE ) {
                         canvas->draw_text( units[ unit ], 2,
                                             x_origin + 60, y_origin + 2,
                                             font,
                                             font_w, font_h, inverted );
                    }
               }
     }
};

#endif