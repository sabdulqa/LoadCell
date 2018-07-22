/* Serial LCD support routines */

#define _LCD_I2C_c_

#include    <xc.h>
#include    "LCD_I2C.h"
#include    "I2C_macros.h"
#include <pic16f877a.h>
/* local definitions	*/

BYTE _LCD_build_byte();
void _LCD_write_lower_nibble(BYTE l);
void _LCD_write_upper_nibble(BYTE u);

void LCD_open()
{
    I2C_IDLE
    I2C_OPEN
    I2C_IDLE
    I2C_START
    I2C_IDLE
    I2C_WRITE(LCD_I2C_ADDR)          // Tell all I2C devices you are talking to LCD_PIC_I2C_ADDR
    I2C_ACK
}

void LCD_close()
{
    I2C_IDLE
    I2C_CLOSE   //I2C_close();
}

void LCD_init()
{
    LCD_open();

    // Following bytes are all Command bytes, i.e. address = 0x00
    LCD_write_byte(0x00, 0x1f);   // Write Nibble 0x03 three times (per HD44780U initialization spec)
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x03);   //
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x03);   //
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x02);   // Write Nibble 0x02 once (per HD44780U initialization spec)
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x02);   // Write Nibble 0x02 once (per HD44780U initialization spec)
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x01);   // Set mode: 4-bit, 2+lines, 5x8 dots
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x0C);   // Display ON 0x0C
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x01);   // Clear display
    __delay_ms(5);                // (per HD44780U initialization spec)
    LCD_write_byte(0x00, 0x06);   // Set cursor to increment
    __delay_ms(5);                // (per HD44780U initialization spec)

}

void LCD_BL(BYTE status)
{
    LCD_BL_Status = status;
    LCD_write_byte(0x00, 0x00);
}

void LCD_goto(BYTE x, BYTE y)   //x=col, y=row
{
BYTE address;

   switch(y)
     {
      case 1:
        address = LCD_LINE_1_ADDRESS;
        break;

      case 2:
        address = LCD_LINE_2_ADDRESS;
        break;

      case 3:
        address = LCD_LINE_3_ADDRESS;
        break;

      case 4:
        address = LCD_LINE_4_ADDRESS;
        break;

      default:
        address = LCD_LINE_1_ADDRESS;
        break;
     }

   address += x-1;
   LCD_write_byte(0, 0x80 | address);
}

void LCD_write_string(const char *str)
{
   // Writes a string text[] to LCD via I2C
   pin_RS  = 1;
   pin_RW  = 0;
   pin_E   = 0;
   pin_BL  = LCD_BL_Status;

   while (*str)
   {
        // Send upper nibble
        _LCD_write_upper_nibble(*str);

        // Send lower nibble
        _LCD_write_lower_nibble(*str);

        str++;
   }
}
void LCD_write_byte(BYTE address, BYTE n)
{
    if (address)
    {
        pin_RS=1;   // Data
    }
    else
    {
        pin_RS=0;   // Command
    }

    pin_RW  = 0;
    pin_E   = 0;
    pin_BL  = LCD_BL_Status;

    // Send upper nibble
   _LCD_write_upper_nibble(n);

    // Send lower nibble
   _LCD_write_lower_nibble(n);
}

void LCD_clear()
{
    LCD_write_byte(0x00,0x01);
    __delay_ms(5);
}

void LCD_clear_line(BYTE line)
{
    LCD_goto(1,line);
    for (int i = 0; i<20; i++)
    {
        LCD_write_string(" ");
    }
    LCD_goto(1,line);
}

void _LCD_write_upper_nibble(BYTE u)
{
    // Send upper nibble
    if(bit_test(u,7))
        pin_D7=1;
    else
        pin_D7=0;

    if(bit_test(u,6))
        pin_D6=1;
    else
        pin_D6=0;

    if(bit_test(u,5))
        pin_D5=1;
    else
        pin_D5=0;

    if(bit_test(u,4))
        pin_D4=1;
    else
        pin_D4=0;

   pin_E = 0;
   I2C_WRITE(_LCD_build_byte());
   pin_E = 1;
   I2C_WRITE(_LCD_build_byte());
   pin_E = 0;
   I2C_WRITE(_LCD_build_byte());
}

void _LCD_write_lower_nibble(BYTE l)
{
    // Send lower nibble
    if(bit_test(l,3))
        pin_D7=1;
    else
        pin_D7=0;

    if(bit_test(l,2))
        pin_D6=1;
    else
        pin_D6=0;

    if(bit_test(l,1))
        pin_D5=1;
    else
        pin_D5=0;

    if(bit_test(l,0))
        pin_D4=1;
    else
        pin_D4=0;

    pin_E = 0;
    I2C_WRITE(_LCD_build_byte())
    pin_E = 1;
    I2C_WRITE(_LCD_build_byte())
    pin_E = 0;
    I2C_WRITE(_LCD_build_byte())
}

BYTE _LCD_build_byte()
{
    BYTE ret = 0x00;

    ret |= pin_E    << 2;
    ret |= pin_RW   << 1;
    ret |= pin_RS   << 0;
    ret |= pin_D4   << 4;
    ret |= pin_D5   << 5;
    ret |= pin_D6   << 6;
    ret |= pin_D7   << 7;
    ret |= pin_BL   << 3;

    return ret;
}
