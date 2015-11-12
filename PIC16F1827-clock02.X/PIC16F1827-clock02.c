// PIC16F1827 Configuration Bit Settings
//2014.9.27
// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = HS    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
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
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 19660800

unsigned char i;
unsigned char ji;
unsigned char fu;
unsigned char p[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};
unsigned char q[10] = {0x02, 0x9E, 0x24, 0x0C, 0x98, 0x48, 0x40, 0x1A, 0x00, 0x08};
unsigned char r[10] = {0xFF, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};
unsigned int cnt1m;
unsigned char tim1m;

void interrupt isr(void) {
    PIR1bits.TMR1IF = 0;

    cnt1m++;
    if (cnt1m == 18000) {
        cnt1m = 0;

        if (fu == 59) {
            fu = 0;
            if (ji == 23) {
                ji = 0;
            } else {
                ji++;
            }
        } else {
            fu++;
        }
    }
}

void main(void) {
    OSCCON = 0x00;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0xF0;
    TRISB = 0x00;

    T1CON = 0x01;
    TMR1H = 0b11100000;
    TMR1L = 0b00000100;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1) {
        i++;
        switch (i) {
            case 1:
                PORTA = 0x01;
                PORTB = p[fu % 10];
                __delay_ms(2);
                PORTB = 0xFF;
                break;
            case 2:
                PORTA = 0x02;
                PORTB = p[(fu - (fu % 10)) / 10];
                __delay_ms(2);
                PORTB = 0xFF;
                break;
            case 3:
                PORTA = 0x04;
                PORTB = q[ji % 10];
                __delay_ms(2);
                PORTB = 0xFF;
                break;
            case 4:
                PORTA = 0x08;
                PORTB = r[(ji - (ji % 10)) / 10];
                __delay_ms(2);
                PORTB = 0xFF;
                break;
            default:
                i = 0;
                break;
        }

        while (RA4 == 0) {
            if (fu == 59) {
                fu = 0;
            } else {
                fu++;
            }
            __delay_ms(200);
        }
        while (RA5 == 0) {
            if (ji == 23) {
                ji = 0;
            } else {
                ji++;
            }
            __delay_ms(200);
        }
    }
}
