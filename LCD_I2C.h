
#ifndef LCD_I2C_h
#define LCD_I2C_h

#define BYTE    unsigned char
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_CLRSCR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x00
#define LCD_NOBACKLIGHT 0x80

/* Original adapter
 * RS --- P5
 * E ---- P4
 * D4 --- P0
 * D5 --- P1
 * D6 --- P2
 * D7 --- P3
*/
#define En B00010000  // Enable bit
#define Rw B00100000  // Read/Write bit
#define Rs B01000000  // Register select bit

#define RS	0x01		// P0 (RS pin was 04)
#define RW  0x02        // P1
#define	E	0x04		// P2 (E pin was 08)

#define SET_RS	LCDpins |= RS
#define	CLR_RS	LCDpins &= ~RS
#define SET_RW	LCDpins |= RW
#define	CLR_RW	LCDpins &= ~RW
#define	SET_E	LCDpins	|= E
#define	CLR_E	LCDpins &= ~E

#define LCD_I2C_ADDR  (BYTE)0x4E

// Line addresses for LCDs which use
// the Hitachi HD44780U controller chip
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x40
#define LCD_LINE_3_ADDRESS 0x14
#define LCD_LINE_4_ADDRESS 0x54

BYTE  LCD_BL_Status = 1;     // 1 for POSITIVE control, 0 for NEGATIVE control

BYTE  pin_E;//   =    I2C_BYTE.2
BYTE  pin_RW;//  =    I2C_BYTE.1
BYTE  pin_RS;//  =    I2C_BYTE.0
BYTE  pin_D4;//  =    I2C_BYTE.4
BYTE  pin_D5;//  =    I2C_BYTE.5
BYTE  pin_D6;//  =    I2C_BYTE.6
BYTE  pin_D7;//  =    I2C_BYTE.7
BYTE  pin_BL;//  =    I2C_BYTE.3

#define  testbit(var, bit)   ((var) & (1 <<(bit)))
#define bit_test    testbit
#define  setbit(var, bit)    ((var) |= (1 << (bit)))
#define  clrbit(var, bit)    ((var) &= ~(1 << (bit)))

#define LCD_sendcmd(a)  CLR_RS; LCD_sendbyte(a);

#define LCD_sendchar(a) SET_RS; LCD_sendbyte(a);

BYTE _LCD_build_byte();
void _LCD_write_lower_nibble(BYTE l);
void _LCD_write_upper_nibble(BYTE u);
void LCD_BL(BYTE status);
void LCD_clear_line(BYTE line);
void LCD_clear();
void LCD_close( void );
void LCD_goto(BYTE x, BYTE y);
//void LCD_home( void );
void LCD_init( void );
void LCD_open( void );
//void LCD_second_row( void );
//void LCD_send_hexbyte ( BYTE data );
//void LCD_sendbyte( BYTE tosend );
//void LCD_send_string( const char *str_ptr );
//void LCD_send_ram_string (char *str_ptr);
void LCD_write_byte(BYTE address, BYTE n);
void LCD_write_string(const char *str);

#endif