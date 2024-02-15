#ifndef ZERO_FONT_H
#define ZERO_FONT_H

#include <stdint.h>

// clang-format off

namespace zf {
     const uint8_t width = 2;
     const uint8_t height = 4;

     const uint8_t ch_a[] { // A
          0x2F, 0xF0,
          0xF0, 0xF0,
          0xFF, 0xF0,
          0xF0, 0xF0
     };

     const uint8_t ch_b[] { // B
          0xFF, 0x00,
          0xFF, 0x20,
          0xFF, 0xF0,
          0xFF, 0xF0
     };

     const uint8_t ch_c[] { // C
          0xFF, 0xF0,
          0xF0, 0x00,
          0xF0, 0x00,
          0xFF, 0xF0
     };

     const uint8_t ch_d[] { // D
          0xFF, 0x00,
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xFF, 0x20
     };

     const uint8_t ch_e[] { // E
          0xFF, 0xF0,
          0xFF, 0xF0,
          0xF2, 0x00,
          0xFF, 0xF0
     };

     const uint8_t ch_f[] { // F
          0xFF, 0xF0,
          0xF0, 0x00,
          0xFF, 0xF0,
          0xF0, 0x00
     };

     const uint8_t ch_g[] { // G
          0xFF, 0xF0,
          0xF0, 0x00,
          0xF0, 0xF0,
          0x2F, 0xF0
     };

     const uint8_t ch_h[] { // H
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xFF, 0xF0,
          0xF0, 0xF0
     };

     const uint8_t ch_i[] { // I
          0xFF, 0xF0,
          0x0F, 0x00,
          0x0F, 0x00,
          0xFF, 0xF0
     };

     const uint8_t ch_j[] { // J
          0xFF, 0xF0,
          0x0F, 0x00,
          0x0F, 0x00,
          0xF2, 0x00
     };

     const uint8_t ch_k[] { // K
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xFF, 0x00,
          0xF0, 0xF0
     };

     const uint8_t ch_l[] { // L
          0xF0, 0x00,
          0xF0, 0x00,
          0xF0, 0x00,
          0xFF, 0xF0
     };

     const uint8_t ch_m[] { // M
          0xF0, 0xF0,
          0xFF, 0xF0,
          0xF0, 0xF0,
          0xF0, 0xF0
     };

     const uint8_t ch_n[] { // N
          0x2F, 0xF0,
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xF0, 0xF0
     };

     const uint8_t ch_o[] { // O
          0x2F, 0x20,
          0xF0, 0xF0,
          0xF0, 0xF0,
          0x2F, 0x20
     };

     const uint8_t ch_p[] { // P
          0xFF, 0x20,
          0xF0, 0xF0,
          0xFF, 0xF0,
          0xF0, 0x00
     };

     const uint8_t ch_q[] { // Q
          0xFF, 0xF0,
          0xF0, 0xF0,
          0x2F, 0xF0,
          0x00, 0xF0
     };

     const uint8_t ch_r[] { // R
          0xFF, 0x20,
          0xF0, 0xF0,
          0xFF, 0x00,
          0xF0, 0xF0
     };

     const uint8_t ch_s[] { // S
          0xFF, 0xF0,
          0xF0, 0x00,
          0x0F, 0xF0,
          0xFF, 0x20
     };

     const uint8_t ch_t[] { // T
          0xFF, 0xF0,
          0x0F, 0x00,
          0x0F, 0x00,
          0x0F, 0x00
     };

     const uint8_t ch_u[] { // U
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xF0, 0xF0,
          0x2F, 0x20
     };

     const uint8_t ch_v[] { // V
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xF0, 0xF0,
          0x0F, 0x00
     };

     const uint8_t ch_w[] { // W
          0xF0, 0xF0,
          0xF0, 0xF0,
          0xFF, 0xF0,
          0xF2, 0xF0
     };
     const uint8_t ch_x[] { // X
          0xF0, 0xF0,
          0xF0, 0xF0,
          0x0F, 0x00,
          0xF0, 0xF0
     };
     const uint8_t ch_y[] { // Y
          0xF0, 0xF0,
          0xFF, 0xF0,
          0x02, 0xF0,
          0xFF, 0xF0
     };

     const uint8_t ch_z[] { // Z
          0xFF, 0xF0,
          0xF0, 0x00,
          0x0F, 0x00,
          0xFF, 0xF0
     };

     const uint8_t ch_colon[] { // colon :
          0x00, 0x00,
          0x0F, 0x00,
          0x00, 0x00,
          0x0F, 0x00
     };

     const uint8_t ch_arrow_left[] { // arrow left <
          0x00, 0xF0,
          0x0F, 0x00,
          0xF0, 0x00,
          0x02, 0xF0
     };

     const uint8_t ch_arrow_right[] { // arrow right >
          0xF0, 0x00,
          0x0F, 0x00,
          0x00, 0xF0,
          0x0F, 0x20
     };

     const uint8_t* zero_font[] = {ch_a, ch_b, ch_c, ch_d, ch_e, ch_f, 
                                   ch_g, ch_h, ch_i, ch_j, ch_k, ch_l,
                                   ch_m, ch_n, ch_o, ch_p, ch_q, ch_r,
                                   ch_s, ch_t, ch_u, ch_v, ch_w, ch_x,
                                   ch_y, ch_z};
                                   
                                   
                                   
                                   
}

// clang-format on

#endif