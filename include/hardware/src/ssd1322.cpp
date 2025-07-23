#include "ssd1322.h"

#define GRAYSCALE_TABLE_SIZE 15

enum Time {
     TIME_RESET_CYCLE    = 500,
     TIME_LIGHT_ON       = 1000,
};

enum Command {
     COMMAND_ENABLE_GRAYSCALE_TABLE          = 0x00,
     COMMAND_SET_COLUMN_ADDRESS              = 0x15,
     COMMAND_WRITE_RAM                       = 0x5c,
     COMMAND_SET_ROW_ADDRESS                 = 0x75,
     COMMAND_SET_REMAP_MODE                  = 0xa0,
     COMMAND_SET_DISPLAY_START_LINE          = 0xa1,
     COMMAND_SET_DISPLAY_OFFSET              = 0xa2,
     COMMAND_SET_DISPLAY_MODE_ON             = 0xa5,
     COMMAND_SET_DISPLAY_MODE_NORMAL         = 0xa6,
     COMMAND_EXIT_PARTIAL_DISPLAY            = 0xa9,
     COMMAND_FUNCTION_SELECT                 = 0xab,
     COMMAND_SLEEP_MODE_OFF                  = 0xaf,
     COMMAND_SET_PHASE_LENGTH                = 0xb1,
     COMMAND_SET_FRONT_CLOCK_DIVIDER         = 0xb3,
     COMMAND_SET_DISPLAY_ENHANCEMENT_A       = 0xb4,
     COMMAND_SET_GPIO                        = 0xb5,
     COMMAND_SET_SECOND_PRECHARGE_PERIOD     = 0xb6,
     COMMAND_SET_GRAYSCALE_TABLE             = 0xb8,
     COMMAND_SET_PRECHAGE_VOLTAGE            = 0xbb,
     COMMAND_SET_COM_DESELECT_VOLTAGE        = 0xbe,
     COMMAND_SET_CONTRAST_CURRENT            = 0xc1,
     COMMAND_MASTER_CONTRAST_CURRENT_CONTROL = 0xc7,
     COMMAND_SET_MUX_RATIO                   = 0xca,
     COMMAND_SET_DISPLAY_ENHANCEMENT_B       = 0xd1,
     COMMAND_SET_COMMAND_LOCK                = 0xfd,
};

volatile struct Ssd1322Interface* interface = nullptr;

const uint8_t ssd1322_grayscale_table[ GRAYSCALE_TABLE_SIZE ] = 
     { 0, 0, 0, 3, 6, 16, 29, 42, 55, 70, 88, 106, 127, 150, 180 };

static void __attribute__((used)) write_command( const uint8_t data ) { 
     interface->data_command( false );
     interface->write( &data, 1 ); 
}

static void __attribute__((used)) write_data( const uint8_t* data, size_t size ) {
     interface->data_command( true );
     interface->write( data, size );
}

static void __attribute__((used)) write_CD( uint8_t cmd, uint8_t D0 ) {
     write_command( cmd );
     write_data( &D0, 1 );
}

static void __attribute__((used)) write_C2D( uint8_t cmd, uint8_t D0, uint8_t D1 ) {
     write_command( cmd );
     write_data( &D0, 1 );
     write_data( &D1, 1 );
}

static void prepare_buffer( uint8_t* buffer, size_t size ) {
     enum {
          HALFBYTE_SHIFT = 4,
     };

     for( size_t idx = 0; idx < size - 1; ++idx ) {
          uint8_t tmp = buffer[ idx ];

          buffer[ idx ] = ( buffer[ idx + 1 ] << HALFBYTE_SHIFT ) |
               ( buffer[ idx + 1 ] >> HALFBYTE_SHIFT );

          buffer[ idx + 1 ] = ( tmp << HALFBYTE_SHIFT ) | 
               ( tmp >> HALFBYTE_SHIFT);

          ++idx;
     }
}

void ssd1322_init( struct Ssd1322Interface* interface_ptr ) {
     interface = interface_ptr;

     interface->reset( true );
     interface->delay( TIME_RESET_CYCLE );
     interface->reset( false );

     write_CD( COMMAND_SET_COMMAND_LOCK, 0x12 );      // Unlock.

     write_C2D( COMMAND_SET_COLUMN_ADDRESS, 28, 91 ); // Set column address, start, end.
     write_C2D( COMMAND_SET_ROW_ADDRESS, 0, 63 );     // Set row address, moved out of the loop ( issue 302 ).
     write_C2D( COMMAND_SET_REMAP_MODE, 0x10, 0x11 ); // Horizontal increment, EN-remap, EN-dualCOM.
     write_CD( COMMAND_SET_DISPLAY_START_LINE, 0x00 );
     write_CD( COMMAND_SET_DISPLAY_OFFSET, 0x00 );    // Shift mapping ram counter.

     write_command( COMMAND_SET_DISPLAY_MODE_NORMAL );
     
     write_command( COMMAND_EXIT_PARTIAL_DISPLAY );
     write_CD( COMMAND_FUNCTION_SELECT, 0x01 );                      // Enable internal VDD regulator.
     write_CD( COMMAND_SET_PHASE_LENGTH, 0xe8 );                     // Reset & Pre-Charge Period Adjustment.
     write_CD( COMMAND_SET_FRONT_CLOCK_DIVIDER, 0x91 );              // Set clock as 80 frames/sec.
     write_C2D( COMMAND_SET_DISPLAY_ENHANCEMENT_A, 0xa0, 0xfd );     // Display Enhancement A ( VSL ).
     write_CD( COMMAND_SET_GPIO, 0x00 );
     write_CD( COMMAND_SET_SECOND_PRECHARGE_PERIOD, 0x1f );          // Precharge current period.

     write_command( COMMAND_SET_GRAYSCALE_TABLE );                   // Set Gray Scale Table( ver 3.0 ).
     write_data( ssd1322_grayscale_table, GRAYSCALE_TABLE_SIZE );
     write_command( COMMAND_ENABLE_GRAYSCALE_TABLE );                // Enable Gray Scale Table.

     write_CD( COMMAND_SET_PRECHAGE_VOLTAGE, 0x0f );
     write_CD( COMMAND_SET_COM_DESELECT_VOLTAGE, 0x07 );
     write_C2D( COMMAND_SET_DISPLAY_ENHANCEMENT_B, 0x82, 0x20 );     // Display Enhancement B.
     write_CD( COMMAND_SET_CONTRAST_CURRENT, 0xdf );
     write_CD( COMMAND_MASTER_CONTRAST_CURRENT_CONTROL, 0x0f );
     write_CD( COMMAND_SET_MUX_RATIO, 63 );                          // Multiplex ratio 1/64 Duty ( 0x0F~0x3F ).

     write_command( COMMAND_SLEEP_MODE_OFF );                        // Display ON.

     interface->delay( TIME_LIGHT_ON );
}

void ssd1322_draw( uint8_t* buffer, size_t size ) {
     write_C2D( COMMAND_SET_COLUMN_ADDRESS, 28, 91 );  // Set column address, start, end.
     write_C2D( COMMAND_SET_ROW_ADDRESS, 0, 63 );     // Set row address, moved out of the loop ( issue 302 ).
     write_command( COMMAND_WRITE_RAM );              // Write to RAM.

     prepare_buffer( buffer, size );

     write_data( buffer, size );
}