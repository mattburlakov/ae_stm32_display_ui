#include "core.h"
#include "hardware.h"

int main( void ) {
     hardware_init();
     core_init();
     
     while( true ) {
          core_run();
     }
}
