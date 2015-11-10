
// PIC16F1827 Configuration Bit Settings
// 2014.10.6
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
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 8000000

unsigned char i = 0;
/*
unsigned char n0[5] = {0b00111110, 0b01000101, 0b01001001, 0b01010001, 0b01111110};
unsigned char n1[5] = {0b00010001, 0b00100001, 0b01111111, 0b00000001, 0b00000001};
unsigned char n2[5] = {0b00100001, 0b01000011, 0b01000101, 0b01001001, 0b00110001};
unsigned char n3[5] = {0b00100010, 0b01000001, 0b01001001, 0b01001001, 0b00110110};
unsigned char n4[5] = {0b00001100, 0b00010100, 0b00100100, 0b01111111, 0b00000100};
unsigned char n5[5] = {0b01111010, 0b01001001, 0b01001001, 0b01001001, 0b01000110};
unsigned char n6[5] = {0b00111110, 0b01001001, 0b01001001, 0b01001001, 0b00100110};
unsigned char n7[5] = {0b01100000, 0b01000000, 0b01000111, 0b01001000, 0b01110000};
unsigned char n8[5] = {0b00110110, 0b01001001, 0b01001001, 0b01001001, 0b00110110};
unsigned char n9[5] = {0b00110010, 0b01001001, 0b01001001, 0b01001001, 0b00111110};
 */

unsigned char n[51] = {0b00111110, 0b01000101, 0b01001001, 0b01010001, 0b01111110, 0b00010001, 0b00100001, 0b01111111, 0b00000001, 0b00000001, 0b00100001, 0b01000011, 0b01000101, 0b01001001, 0b00110001, 0b00100010, 0b01000001, 0b01001001, 0b01001001, 0b00110110, 0b00001100, 0b00010100, 0b00100100, 0b01111111, 0b00000100, 0b01111010, 0b01001001, 0b01001001, 0b01001001, 0b01000110, 0b00111110, 0b01001001, 0b01001001, 0b01001001, 0b00100110, 0b01100000, 0b01000000, 0b01000111, 0b01001000, 0b01110000, 0b00110110, 0b01001001, 0b01001001, 0b01001001, 0b00110110, 0b00110010, 0b01001001, 0b01001001, 0b01001001, 0b00111110, 0b00000000};

void interrupt isr(void) {
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;


    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        i++;
        switch (i) {
            case 1:
                PORTA = 0x00;
                PORTB = 0b11111110;
                PORTA = n[0];
                break;
            case 2:
                PORTA = 0x00;
                PORTB = 0b11111101;
                PORTA = n[1];
                break;
            case 3:
                PORTA = 0x00;
                PORTB = 0b11111011;
                PORTA = n[2];
                break;
            case 4:
                PORTA = 0x00;
                PORTB = 0b11110111;
                PORTA = n[3];
                break;
            case 5:
                PORTA = 0x00;
                PORTB = 0b11101111;
                PORTA = n[4];
                break;
            case 6:
                PORTA = 0x00;
                PORTB = 0b11011111;
                PORTA = n[50];
                break;
            case 7:
                PORTA = 0x00;
                PORTB = 0b10111111;
                PORTA = n[50];
                break;
            case 8:
                PORTA = 0x00;
                PORTB = 0b01111111;
                PORTA = n[50];
                break;
            default:
                PORTA = 0x00;
                i = 0;
                break;
        }
    }
}

int main(void) {
    OSCCON = 0x70;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;

    OPTION_REG = 0b10010011;
    INTCONbits.TMR0IE = 1;

    T1CON = 0x01;
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1) {

    }
    return 0;
}