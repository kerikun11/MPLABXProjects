// 2015.09.26
// Welcome Board Light
#include <xc.h>
#include <stdint.h>
// CONFIG1
#pragma config FOSC = INTOSC, WDTE = OFF, PWRTE = OFF, MCLRE = OFF, CP = OFF, CPD = OFF, BOREN = OFF, CLKOUTEN = OFF, IESO = OFF, FCMEN = OFF
// CONFIG2
#pragma config WRT = OFF, PLLEN = ON, STVREN = OFF, BORV = LO, LVP = OFF

#define _XTAL_FREQ 32000000

int main(void) {
    OSCCON = 0x70;
    TRISA = 0x00;
    ANSELA = 0x00;
    while (1) {
        for (uint16_t i = 0; i < 2000; i++) {
            LATAbits.LATA0 = 0;
            LATAbits.LATA1 = 1;
            __delay_us(250);
            LATAbits.LATA0 = 0;
            LATAbits.LATA1 = 1;
            __delay_us(250);
        }
        for (uint16_t i = 0; i < 2000; i++) {
            LATAbits.LATA0 = 1;
            LATAbits.LATA1 = 0;
            __delay_us(125);
            LATAbits.LATA0 = 1;
            LATAbits.LATA1 = 0;
            __delay_us(125);
            LATAbits.LATA0 = 1;
            LATAbits.LATA1 = 0;
            __delay_us(125);
            LATAbits.LATA0 = 0;
            LATAbits.LATA1 = 1;
            __delay_us(125);
        }
    }
    return 0;
}