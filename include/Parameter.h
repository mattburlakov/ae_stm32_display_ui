#ifndef PARAMETER_H
#define PARAMETER_H

#include <stdint.h>

enum { UNIT_VOLTS, UNIT_AMPERES, UNIT_WATTS };
enum { TYPE_INTEGER, TYPE_FLOAT };

const char* unit_u = "U";
const char* unit_i = "I";
const char* unit_w = "W";
const char* resolution_mil = "m";   // unavailable in font atm.
const char* resolution_kilo = "k";  // unavailable in font atm.
const char* resolution_mega = "M";
template <typename T>
class Parameter {
     public:
     const char* name;
     const char* unit;
     const char* resolution;
     T value = 0;

     uint8_t width = 0;
     uint8_t height = 0;
     uint8_t x_pos = 0;
     uint8_t y_pos = 0;

     uint8_t cursor_increment = 1;

     bool selected = false;

     /// @brief Initialize a parameter. @todo redo /w templated parameters.
     /// @param[in] n Parameter display name.
     /// @param[in] u Parameter measure units.
     /// @param[in] r Measure unit resolution.
     /// @param[in] x X position on screen.
     /// @param[in] y Y position on screen.
     /// @param[in] w Parameter width.
     /// @param[in] h Parameter height.
     Parameter(const char* n,
               const char* u,
               const char* r,
               uint8_t x,
               uint8_t y,
               uint8_t w,
               uint8_t h) {
          name = n;
          unit = u;
          resolution = r;

          x_pos = x;
          y_pos = y;
          width = w;
          height = h;
     }

     ~Parameter() {}
};

#endif