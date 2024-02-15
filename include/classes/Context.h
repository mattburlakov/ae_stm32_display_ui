#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

#include "Canvas.h"
#include "Parameter.h"

enum ContextFlag {
     CONTEXT_SHADOW      = 0b00000001,
     CONTEXT_BORDER      = 0b00000010,
     CONTEXT_HAS_LABEL   = 0b00000100,
};

class Context {
     private:
          uint8_t x_pos = 0;
          uint8_t y_pos = 0;
          uint8_t entry_width  = 0;
          uint8_t entry_height = 0;
          uint8_t columns = 1;

          uint8_t flags = 0;

          Parameter* parameter_list = nullptr;
          Parameter* selected_parameter = nullptr;
          uint8_t parameter_number = 0;

          uint8_t selected_parameter_id = 0;

          bool is_targeted = false;
     
     public:
          Context(
                  uint8_t origin_x, uint8_t origin_y,
                  uint8_t entry_w, uint8_t entry_h,
                  uint8_t column_number,
                  uint8_t flag,
                  uint8_t parameter_num,
                  Parameter* parameters) {

               x_pos = origin_x;
               y_pos = origin_y;
               entry_width = entry_w;
               entry_height = entry_h;
               columns = column_number;

               flags = flag;

               parameter_number = parameter_num;
               parameter_list = parameters;
          }

          void select_parameter() { selected_parameter = &parameter_list[ selected_parameter_id ]; }
          void deselect_parameter() { selected_parameter = nullptr; }

          void increment_parameter_id( int8_t i ) {
               if( !( ( selected_parameter_id + i ) > parameter_number - 1 ) && ( selected_parameter_id + i ) > 0 ) {
                    selected_parameter_id += i;
               }
          }

          Parameter* get_selected_parameter() {
               return selected_parameter;
          }

          void target( bool t ) {
               is_targeted = t;
          }

          void draw( Canvas* canvas ) {
               if( is_targeted ) {
                    if( selected_parameter ) {
                         canvas->draw_rect( x_pos, y_pos + entry_height * selected_parameter_id, 
                                       entry_width, entry_height, BRIGHT, FILL );
                    }
                    else
                    {
                         canvas->draw_rect( x_pos, y_pos + entry_height * selected_parameter_id, 
                                        entry_width, entry_height, BRIGHT );
                    }
               }

               for( uint8_t i = 0; i < parameter_number; ++i ) {
                    if( i == selected_parameter_id )
                         parameter_list[ i ].draw( canvas, x_pos, y_pos + entry_height * i );
                    else
                         parameter_list[ i ].draw( canvas, x_pos, y_pos + entry_height * i );
               }
          }
          
};

#endif