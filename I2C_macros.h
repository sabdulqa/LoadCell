
#ifndef __I2C_MACROS_H
#define __I2C_MACROS_H

#define SDA		RC4			// Pin 9, Data pin for i2c
#define SCK		RC3			// Pin 10, Clock pin for i2c
#define SDA_DIR		TRISC4			// Data pin direction
#define SCK_DIR		TRISC3			// Clock pin direction

#define I2C_SCL	TRISCbits.TRISC3
#define I2C_SDA	TRISCbits.TRISC4
// Define i2c speed
#define _XTAL_FREQ 4000000
#define I2C_SPEED	100				// kbps

#define I2C_OPEN    SSPCON |= 0b00101000;              // enable synchronous serial port
#define I2C_CLOSE   SSPCON &= 0xdf;              // disable synchronous serial port
#define I2C_INIT    SDA_DIR=1; SCK_DIR=1; SSPADD=((_XTAL_FREQ/(4000*I2C_SPEED) - 1)); SSPSTAT=0x0; SSPCON=0b00101000; SSPCON2 = 0;SDA_DIR=1;SCK_DIR=1;
#define I2C_START   SSPCON2bits.SEN = 1; //while(SSP1CON2bits.SEN);
#define I2C_STOP    SSPCON2bits.PEN = 1; //while(SSP1CON2bits.PEN);
#define I2C_ACK     SSPCON2bits.ACKDT=0; SSPCON2bits.ACKEN=1; while(RCEN && SSPCON2bits.ACKEN);
#define I2C_NACK    SSPCON2bits.ACKDT=1; SSPCON2bits.ACKEN=1; while(RCEN && SSPCON2bits.ACKEN);
#define I2C_READ    RCEN=1; while(SSPCON2bits.ACKEN); return SSPBUF;
#define I2C_WRITE(d)    I2C_IDLE SSPBUF=d; while( SSPSTATbits.BF );
#define I2C_WAIT    while(!PIR1bits.SSP1IF); PIR1bits.SSP1IF=0;
#define I2C_IDLE    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));

#endif
