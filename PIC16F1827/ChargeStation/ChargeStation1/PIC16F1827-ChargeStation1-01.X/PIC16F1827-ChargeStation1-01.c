// PIC16F1827 Configuration Bit Settings
// 2014.10.29
// RA0~3:adc, RB0~3:output, RA4~7:sw
// ChargeStation Ver.1 金属ケース用
// 安定完成版

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

int i;
int j;
int k;
uint32_t temp[4];
uint32_t v[4];
uint8_t d[4];
uint16_t cnt = 0;
uint16_t cnt0 = 0;
uint16_t cnt1 = 0;
uint16_t cut[4];
uint8_t cutf[4];

unsigned int adc(uint8_t ch);

unsigned int adc(uint8_t ch) {
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = ch;
    __delay_us(20);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

void interrupt isr(void) {
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;

        cnt1++;
        if (cnt1 == 15) {
            cnt1 = 0;

            for (i = 0; i < 4; i++) {
                temp[i] = adc(i);
                v[i] = temp[i] * 2;
            }
        }
    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        cnt0++;
        if (cnt0 == 400) {
            cnt0 = 0;
            for (k = 0; k < 4; k++) {
                if (cutf[k])cut[k]++;
            }
            cnt++;
            if (cnt == 40) {
                cnt = 0;
            }
            for (j = 0; j < 4; j++) {
                d[j] = v[j] / 100;
            }
            if ((cnt % 2) == 1) {
                if (((cnt + 1) / 2) <= d[0]) {
                    PORTBbits.RB4 = 1;
                }
                if (((cnt + 1) / 2) <= d[1]) {
                    PORTBbits.RB5 = 1;
                }
                if (((cnt + 1) / 2) <= d[2]) {
                    PORTBbits.RB6 = 1;
                }
                if (((cnt + 1) / 2) <= d[3]) {
                    PORTBbits.RB7 = 1;
                }
            } else {
                PORTB = PORTB & 0b00001111;
            }
        }
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

    while (1) {
        for (i = 0; i < 4; i++) {
            if (PORTAbits.RA6 == 0) {
                PORTBbits.RB0 = 0;
            }
            if (PORTAbits.RA7 == 0) {
                PORTBbits.RB1 = 0;
            }
            if (PORTAbits.RA4 == 0) {
                PORTBbits.RB2 = 0;
            }
            if (PORTAbits.RA5 == 0) {
                PORTBbits.RB3 = 0;
            }
            if (v[i] < 50) {
                cutf[i] = 1;
            } else {
                cutf[i] = 0;
                cut[i] = 0;
            }

            if (cut[i] == 50) {
                switch (i) {
                    case 0:
                        PORTBbits.RB0 = 1;
                        break;
                    case 1:
                        PORTBbits.RB1 = 1;
                        break;
                    case 2:
                        PORTBbits.RB2 = 1;
                        break;
                    case 3:
                        PORTBbits.RB3 = 1;
                        break;
                }

            }
        }
    }
    return 0;
}
