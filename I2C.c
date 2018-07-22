// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

void I2C_Master_Init(const unsigned long c)
{
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0;
    TRISC3 = 1; // SCL
    TRISC4 = 1; // SDA
}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;
}

unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();
    RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    ACKDT = (a)?0:1;
    ACKEN = 1;
    return temp;
}
/*
void main()
{
    nRBPU = 0;
    TRISB = 0xFF;;
    TRISD = 0x00;
    PORTD = 0x00;
    I2C_Master_Init(100000);
    while(1)
    {
        I2C_Master_Start();
        I2C_Master_Write(0x30);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_ms(200);
        I2C_Master_Start();
        I2C_Master_Write(0x31);
        PORTD = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
    }
}*/