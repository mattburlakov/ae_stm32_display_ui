#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "include/Canvas.h"

// Add pages. Add parameters.

struct GraphicsManager {
     Canvas* canvas;

     /// @brief Set target canvas.
     /// @param c Target canvas.
     void set_target_canvas(Canvas* c) { canvas = c; }

     /// @brief Utility function for drawing basic user interface. WIP
     void draw_user_interface() {}

     /// @brief Draws parameter outline.
     void draw_parameter_outline() {}

     /// @brief Draws parameter text, including parameter name, value and units.
     void draw_parameter_text() {}

     /// @brief Draws the current page.
     void draw_page() {}
};

#endif