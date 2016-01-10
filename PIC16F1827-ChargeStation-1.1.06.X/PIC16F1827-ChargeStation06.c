// PIC16F1827 Configuration Bit Settings
//2014.10.29
//RA0~3:adc, RB0~3:output, RA4~7:sw
//LEDインジケータなし、出力とリンク（テスト用）
//一般用
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
#pragma config PLLEN = ON      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF       // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000

uint16_t v[4];
uint16_t cut[4];

unsigned int adc(uint8_t ch);
void OUT(uint8_t b, uint8_t hl);
void LED(uint8_t b, uint8_t hl);
uint8_t SW(uint8_t b);

void interrupt isr(void) {
    uint8_t i;
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
        for (i = 0; i < 4; i++) {
            v[i] = 2 * adc(i);

            if (v[i] < 75) {
                cut[i]++;
                if (cut[i] >= 50) {
                    OUT(i, 0);
                    LED(i, 0);
                }
            } else {
                cut[i] = 0;
            }
        }
    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
    }
}

unsigned int adc(uint8_t ch) {
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = ch;
    __delay_us(20);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

void OUT(uint8_t b, uint8_t hl) {
    if (hl == 0) {
        PORTB = PORTB | (0x01 << b);
    } else {
        PORTB = PORTB & (~(0x01 << b));
    }
}

void LED(uint8_t b, uint8_t hl) {
    if (hl == 1) {
        PORTB = PORTB | (0x01 << (b + 4));
    } else {
        PORTB = PORTB & (~(0x01 << (b + 4)));
    }
}

uint8_t SW(uint8_t b) {
    uint8_t temp;
    temp = PORTA;
    if (temp & (0x01 << (b + 4))) {
        return 0;
    } else {
        return 1;
    }
}

int main(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0xFF; //RA3,4,5 input
    TRISB = 0x00; //all output
    ANSELA = 0x0F; //Use AN3,4
    ANSELB = 0x00; //all digital
    ADCON1 = 0x93; //Use FVR
    FVRCON = 0x83; //4.096V

    PORTB = 0xF0;

    OPTION_REG = 0b10010011; //ps:1/16
    INTCONbits.TMR0IE = 1;

    T1CON = 0x21; //Fosc/4, ps:1/4
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    uint8_t i;
    while (1) {
        for (i = 0; i < 4; i++) {
            if (SW(i)) {
                OUT(i, 1);
                LED(i, 1);
                cut[i] = 0;
            }
        }
    }
    return 0;
}
