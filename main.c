/*
 * File:   main.c
 * Author: sabdulqa
 *
 * Created on July 16, 2018, 1:19 PM
 */


#include <xc.h>
#include "i2c.h"
#include    "I2C_macros.h"
#include    "LCD_I2C.h"

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF     // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF       // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000

/*
void LCD_Open()
{
    I2C_Master_Wait();
    I2C_Master_Init(100000);           // Begin transfer, claim I2C BUS
    I2C_Master_Wait();
    I2C_Master_Start();
    I2C_Master_Wait();
}

void LCD_Init()
{
    LCD_Open();
    
    // Following bytes are all Command bytes, i.e. address = 0x00
    I2C_Master_Write(0x03);   // Write Nibble 0x03 three times (per HD44780U initialization spec)
    __delay_ms(10);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x03);   //
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x03);   //
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x02);   // Write Nibble 0x02 once (per HD44780U initialization spec)
    __delay_ms(5);
    I2C_Master_Write(0x02);   // Write Nibble 0x02 once (per HD44780U initialization spec)
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x01);   // Set mode: 4-bit, 2+lines, 5x8 dots
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x0C);   // Display ON 0x0C
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x01);   // Clear display
    __delay_ms(5);                // (per HD44780U initialization spec)
    I2C_Master_Write(0x06);   // Set cursor to increment
    __delay_ms(5);                // (per HD44780U initialization spec)
    
  //  LCD_Close();
}
*/

void main(void) {
    unsigned char portValue,m;

 //   LCD_Open();
    // Port B access
 //   ANSELB = 0x0;  // set to digital I/O (not analog)
    
    // Need pullups for portB inputs
    TRISB = 0x0f;   // set all port bits to be output    
    OPTION_REGbits.nRBPU =0;
    // Port D access
 //   ANSELD = 0x0;  // set to digital I/O (not analog)
    TRISD = 0x0;   // set all port bits to be output

    while(1) {

     //   m=PORTBbits.RB0;
        
        m = PORTBbits.RB0;
        if(m == 0)
        {
        portValue = 0x55;
        PORTD = portValue;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0x55;   // write to port latch - RD[0:3] = LED[0:3]
        _delay(250000);  // delay value change - instruction cycles

        portValue = 0xaa;
        PORTD = portValue;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0xaa;   // write to port latch - RD[0:3] = LED[0:3]]
        _delay(250000);  // delay value change - instruction cycles

 //       for(int x=0;x<254;x++)
   //         eeprom_write(x,3);
        }
        m = PORTBbits.RB1;
        if(m == 0)
        {
        portValue = 0x0f;
        PORTD = portValue;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0x55;   // write to port latch - RD[0:3] = LED[0:3]
        _delay(250000);  // delay value change - instruction cycles

        portValue = 0xf0;
        PORTD = portValue;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0xaa;   // write to port latch - RD[0:3] = LED[0:3]]
        _delay(250000);  // delay value change - instruction cycles

 //       for(int x=0;x<254;x++)
   //         eeprom_write(x,3);
        }
 //           OSCCON = 0b01101011;    //4 MHz
  //  TRISA = 0b00011011;     //RA2, RA5 output
  //  TRISC = 0b00110011;     //RC2, RC3 output
  //  WPUA = 0b00001000;      //Pull-up on RA3
 //   ANSELA = 0b00010000;    //AN3 RA4
 //   ANSELC = 0;
 //   LATA = 0b00000100;      // TXEN OFF
        TRISC3 = 1; // SCL
    TRISC4 = 1; // SDA

   /// I2C_INIT
            
    while(1) {
    LCD_open();
    LCD_init();

    LCD_goto(1,1);
    LCD_write_string("** LCD test **");
    LCD_close();
    __delay_ms(1000);
     portValue = 0x0f;
        PORTD = 0x1;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0x55;   // write to port latch - RD[0:3] = LED[0:3]
        _delay(250000);  // delay value change - instruction cycles

        portValue = 0x0;
        PORTD = portValue;   // write to port latch - RB[0:3] = LED[4:7]
      //  PORTD = 0xaa;   // write to port latch - RD[0:3] = LED[0:3]]
        _delay(250000);  // delay value change - instruction cycles
//    LATA5 ^= 1;
    }          
    }
    
    return;
}
