#ifndef VALUE_H
#define VALUE_H

#include <stdint.h>

struct Value{
     int8_t val;
     int8_t upper_threshold;
     int8_t lower_threshold;
};

uint8_t value_out_of_bounds(Value* value) {
     if(value->val < value->lower_threshold || 
        value->val > value->upper_threshold ) {
          return 1;
     }

     return 0;
}

void value_increment(Value* value, int8_t increment) {
     value->val += increment;

     if(value->val < value->lower_threshold)
          value->val = value->upper_threshold;
     else if (value->val > value->upper_threshold)
          value->val = value->lower_threshold;
}

#endif

