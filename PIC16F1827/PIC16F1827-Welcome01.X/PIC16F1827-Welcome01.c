// PIC16F1827
// 2015.04.29
// Inverted Pendulum
#include <xc.h>
#include <stdint.h>
// CONFIG1
#pragma config FOSC = INTOSC, WDTE = OFF, PWRTE = OFF, MCLRE = OFF, CP = OFF, CPD = OFF, BOREN = OFF, CLKOUTEN = OFF, IESO = OFF, FCMEN = OFF
// CONFIG2
#pragma config WRT = OFF, PLLEN = ON, STVREN = OFF, BORV = LO, LVP = OFF

#define _XTAL_FREQ 32000000

#define LED_R 0
#define LED_G 1
#define LED_B 2
#define PR 100

void PWM_init(void) {
    CCP1CONbits.CCP1M = 12; // PWM, single output
    CCP1CONbits.P1M = 0; // single output
    CCPTMRSbits.C1TSEL = 0;
    CCPR1Lbits.CCPR1L = 0;
    CCP1CONbits.DC1B = 0;

    CCP2CONbits.CCP2M = 12; // PWM, single output
    CCP2CONbits.P2M = 0; // single output
    CCPTMRSbits.C2TSEL = 0;
    CCPR2Lbits.CCPR2L = 0;
    CCP2CONbits.DC2B = 0;

    CCP3CONbits.CCP3M = 12; // PWM, single output
    CCPTMRSbits.C3TSEL = 0;
    CCPR3Lbits.CCPR3L = 0;
    CCP3CONbits.DC3B = 0;

    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 2;
    PR2 = PR - 1;
    T2CONbits.TMR2ON = 1;
}

void PWM_set(uint8_t color, uint8_t value) {
    switch (color) {
        case LED_R:
            CCP1CONbits.DC1B = 0;
            CCPR1L = value;
            break;
        case LED_G:
            CCP2CONbits.DC2B = 0;
            CCPR2L = value;
            break;
        case LED_B:
            CCP3CONbits.DC3B = 0;
            CCPR3L = value;
            break;
    }
}

int main(void) {
    OSCCON = 0x70;
    TRISA = 0x00;
    TRISB = 0x00;
    ANSELA = 0x00;
    ANSELB = 0x00;

    PWM_init();

    INTCONbits.GIE = 1;

    while (1) {
        PWM_set(LED_R, 100);
        PWM_set(LED_G, 0);
        PWM_set(LED_B, 0);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 0);
        PWM_set(LED_G, 100);
        PWM_set(LED_B, 0);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 0);
        PWM_set(LED_G, 0);
        PWM_set(LED_B, 100);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 50);
        PWM_set(LED_G, 50);
        PWM_set(LED_B, 0);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 0);
        PWM_set(LED_G, 50);
        PWM_set(LED_B, 50);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 50);
        PWM_set(LED_G, 0);
        PWM_set(LED_B, 50);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        PWM_set(LED_R, 33);
        PWM_set(LED_G, 33);
        PWM_set(LED_B, 33);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
        __delay_ms(250);
    }
    return 0;
}
