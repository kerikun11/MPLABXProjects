// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

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
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000

void Delay_ms(int t) {
    while (t) {
        __delay_ms(1);
        t--;
    }
}

void interrupt RSI() {
    if (RCIF) {
        RCIF = 0;
        while (!TRMT);
        TXREG = RCREG;
    }
}

void tx(unsigned char t) {
    while (!TRMT);
    TXREG = t;
}

void main(void) {
    TRISA = 0X00;
    TRISB = 0X02;
    ANSELA = 0X00;
    ANSELB = 0X00;

    OSCCON = 0X70;

    SPEN = 1;
    TXCKSEL = 0;
    RXDTSEL = 0;
    RCSTA = 0X90;
    BRG16 = 0;
    SPBRGH = 0;
    SPBRGL = 207;
    TXSTA = 0X24;

    RCIE = 1;
    PEIE = 1;
    GIE = 1;

    while (1) {
        unsigned char a[] = "Hello World!";
        for (int i = 0; i < 12; i++) {
            PORTA = 0x01;
            tx(a[i]);
        }
        Delay_ms(1000);

    }
}