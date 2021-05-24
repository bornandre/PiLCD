#include <stdlib.h>
#include <wiringPi.h>

void ST7036_write_byte( char data );
void ST7036_write_command_byte( char data );
void ST7036_write_data_byte( char data );
void ST7036_reset(void);
void ST7036_init(void);
void ST7036_putsf( char * string );
void ST7036_puts( char * string );
void ST7036_putc( char zeichen );
void ST7036_goto_xy(unsigned char xwert, unsigned char ywert);
void ST7036_clearline( unsigned char zeile );
void ST7036_clear( void );

