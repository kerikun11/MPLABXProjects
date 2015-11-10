// PIC16F1827 Configuration Bit Settings
//2014.9.27
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
#pragma config PLLEN = ON      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000

unsigned char i;
unsigned char j;
unsigned char ji;
unsigned char fu;
unsigned char p[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};
unsigned char q[10] = {0x02, 0x9E, 0x24, 0x0C, 0x98, 0x48, 0x40, 0x1A, 0x00, 0x08};
unsigned char r[10] = {0xFF, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};
unsigned int cnt1m = 0;
unsigned int temp;
unsigned long v;

void interrupt isr(void) {
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
    }

    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;

        i++;
        switch (i) {
            case 1:
                PORTB = 0xFF;
                PORTA = 0x01;
                PORTB = p[(v % 10) / 1];
                break;
            case 2:
                PORTB = 0xFF;
                PORTA = 0x02;
                PORTB = p[(v % 100) / 10];
                break;
            case 3:
                PORTB = 0xFF;
                PORTA = 0x04;
                PORTB = p[(v % 1000) / 100];
                break;
            case 4:
                PORTB = 0xFF;
                PORTA = 0x08;
                PORTB = q[(v % 10000) / 1000];
                break;
            default:
                PORTB = 0xFF;
                i = 0;
                break;
        }
    }
}

unsigned int adc(void) {
    ADCON0 = (ADCON0 & 0b10000010) + 0b00010001;
    __delay_us(20);
    ADCON0 = (ADCON0 & 0b11111101) + 0b00000010;
    while (ADCON0 & 0b00000010);
    return (ADRESH << 8)+ADRESL;
}

int main(void) {
    OSCCON = 0x70;
    ANSELA = 0x10;
    ANSELB = 0x00;
    TRISA = 0xF0;
    TRISB = 0x00;
    ADCON1 = 0b10000000;

    OPTION_REG = 0b10010011;
    INTCONbits.TMR0IE = 1;

    T1CON = 0x01;
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1) {
        temp = adc();
        v = temp*50/1024;
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);
    }
    return 0;
}
