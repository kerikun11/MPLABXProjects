// PIC16F1827
// 2015.02.21
// SPI Sample Program
#include <xc.h>
#include <stdint.h>
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000
#define C_SEL LATA7
#define RS LATA4

#define PIC16F1827
#define AQM1248A

#include <My_header.h>
#include <My_SPI.h>

uint8_t pattern[][5] = {
    //0
    {
        0b10000011,
        0b01011101,
        0b01101101,
        0b01110101,
        0b10000011
    },
    //1
    {
        0b11111111,
        0b01111011,
        0b00000001,
        0b01111111,
        0b11111111
    },
    //2
    {
        0b01111011,
        0b00111101,
        0b01011101,
        0b01101101,
        0b01110011
    },
    //3
    {
        0b10111011,
        0b01111101,
        0b01101101,
        0b01101101,
        0b10010011
    },
    //4
    {
        0b11001111,
        0b11010111,
        0b11011011,
        0b00000001,
        0b11011111
    },
    //5
    {
        0b10100001,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10011101
    },
    //6
    {
        0b10000011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10011011
    },
    //7
    {
        0b11111001,
        0b11111101,
        0b00011101,
        0b11101101,
        0b11110001
    },
    //8
    {
        0b10010011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10010011
    },
    //9
    {
        0b10110011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10000011
    }
};

void interrupt isr(void) {
    interrupt_TXIF();
    if (TMR0IF) {
        TMR0 = 0;
    }
    if (RCIF) {
        RCIF = 0;
        char ascii = RCREG;
        tx_send(ascii);
    }
}

void main(void) {
    OSCCON = 0x70;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x06;
    WPUA = TRISA;
    WPUB = TRISB;
    OPTION_REGbits.nWPUEN = 0;
    APFCON0bits.RXDTSEL = 1;
    APFCON0bits.SDO1SEL = 1;
    APFCON1bits.TXCKSEL = 1;

    UART_init();
    SPI_init(MASTER);
    SPI_LCD_init();

    char buf[30];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    INTCONbits.GIE = 1;

    uint8_t i;
    uint8_t j;
    for (i = 0; i < 6; i++) {
        SPI_LCD_Cursor(i, 0);
        for (j = 0; j < 128; j++) {
            SPI_LCD_Data(0x00);
        }
    }

    while (1) {
        for (i = 0; i < 6; i++) {
            SPI_LCD_Cursor(i, 0x00);
            for (j = 0; j < 10; j++) {
                SPI_LCD_Data(~pattern[j][0]);
                SPI_LCD_Data(~pattern[j][1]);
                SPI_LCD_Data(~pattern[j][2]);
                SPI_LCD_Data(~pattern[j][3]);
                SPI_LCD_Data(~pattern[j][4]);
                SPI_LCD_Data(0x00);
            }
            for (j = 0; j < 10; j++) {
                SPI_LCD_Data(~pattern[j][0]);
                SPI_LCD_Data(~pattern[j][1]);
                SPI_LCD_Data(~pattern[j][2]);
                SPI_LCD_Data(~pattern[j][3]);
                SPI_LCD_Data(~pattern[j][4]);
                SPI_LCD_Data(0x00);
            }
        }
    }
}
