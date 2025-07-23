#ifndef CORE_FONT_H
#define CORE_FONT_H

#include <stdint.h>

#define FONT_CHAR_OFFSET 48

/// @brief Font details and data.
struct FontData {
     uint8_t width;                ///< Font data width in bytes.
     uint8_t height;               ///< Font data height in bytes.
     const uint8_t** font_data;    ///< Font data.
};

#endif
