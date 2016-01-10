/* 
 * Project: RTCC-Sample.X
 * File:    main.c
 * Author:  Ryotaro Onuki
 *
 * Created on 2015/10/06, 14:23
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
// CONFIG1L
#pragma config WDTEN = OFF, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
// CONFIG1H
#pragma config CPUDIV = OSC1, CP0 = OFF
// CONFIG2L
#pragma config OSC = INTOSCPLL, SOSCSEL = HIGH, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
// CONFIG2H
#pragma config WDTPS = 1024
// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF, RTCOSC = T1OSCREF, DSBOREN = OFF, DSWDTEN = OFF, DSWDTPS = G2
// CONFIG3H
#pragma config IOL1WAY = OFF, ADCSEL = BIT12, MSSP7B_EN = MSK7
// CONFIG4L
#pragma config WPFP = PAGE_127, WPCFG = OFF
// CONFIG4H
#pragma config WPDIS = OFF, WPEND = PAGE_WPFP, LS48MHZ = SYS48X8

#define _XTAL_FREQ 48000000

#include "My_RTCC.h"
#include "My_button.h"

// I/O Mapping
#define MODE_BUTTON PORTBbits.RB0
#define INC_BUTTON PORTBbits.RB1
#define DEC_BUTTON PORTBbits.RB2

#define LED0 LATAbits.LATA0

button_t mode;
button_t inc;
button_t dec;

void interrupt ISR(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
    }
    if (PIE2bits.TMR3IE && PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        LED0 = !LED0;
        button_timer_interrupt(&mode, !MODE_BUTTON);
        button_timer_interrupt(&inc, !INC_BUTTON);
        button_timer_interrupt(&dec, !DEC_BUTTON);
    }
    if (PIR1bits.RCIF && PIE1bits.RCIE) {
        while (!PIR1bits.TXIF); // 送信完了まで待つ。
        TXREG1 = RCREG1; // 受信データをそのまま送信
    }
}

void main_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00100000; // IO,IO,Vcap,IO,IO,IO,IO,IO
    TRISB = 0b00110111; // IO,IO,SDA,SCL,IO,IO,IO,IO
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,IO,T1OSI,T1OSO
    ANCON0 = 0b11111111; // x,x,x,AN4,AN3,AN2,AN1,AN0
    ANCON1 = 0b11111111; // x,x,x,x,AN12,AN11,AN10,AN9,AN8
    INTCON2bits.RBPU = 0; // Port:B Pull-up enable
    // Timer 1 init
    T1CONbits.TMR1CS = 2; // Clock = T1OSC
    T1CONbits.T1OSCEN = 1; // Drive Crystal
    T1CONbits.T1CKPS = 0; // No devide
    T1CONbits.nT1SYNC = 1; // No Sync
    T1CONbits.RD16 = 0; // Timer1 = 2 x 8bit timer
    T1CONbits.TMR1ON = 1; // module enable
    IPR1bits.TMR1IP = 0; // low priority
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    // Timer 3 init
    T3CONbits.TMR3CS = 0; // Clock = Fosc/4
    T3CONbits.T3OSCEN = 0; // Not Drive Crystal
    T3CONbits.T3CKPS = 2; // clock/4
    T3CONbits.RD163 = 0; // Timer3=16bit timer
    T3CONbits.TMR3ON = 1; // module enable
    IPR2bits.TMR3IP = 0; // low priority
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1; // interrupt enable
    INTCONbits.PEIE = 1;
    // RTCC init
    RTCC_init();
    // UART init
    TXSTA1bits.TX9 = 0; // 0:8-bit
    TXSTA1bits.TXEN = 1; //1:enable
    TXSTA1bits.SYNC = 0; // 0:Asynchronous mode
    TXSTA1bits.BRGH = 0; // 1:High Speed
    RCSTA1bits.SPEN = 1; // 1:Serial Port enable
    RCSTA1bits.RX9 = 0; // 0:8-bit
    RCSTA1bits.CREN = 1; // 1:continuous receive enable
    BAUDCON1bits.BRG16 = 0; // 1:use 16-bit SPBRG
    SPBRG1 = _XTAL_FREQ / 64 / 9600 - 1;
    SPBRGH1 = 0;
    IPR1bits.RC1IP = 0; //0:low priority
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
}

void delay(uint16_t t) {
    while (t--)__delay_ms(1);
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    while (1) {
        RTCC_task();
        RTCC_adjust_time_button(&now, &mode, &inc, &dec);

        if (time_change_flag) {
            time_change_flag = 0;
            char str[30];
            sprintf(str, "\t20%02d/%02d/%02d(%s)%02d:%02d-%02d\n",
                    now.YY,
                    now.MM,
                    now.DD,
                    weekday_3char[now.EE],
                    now.hh,
                    now.mm,
                    now.ss);
            for (uint8_t i = 0; str[i]; i++) {
                while (!PIR1bits.TXIF); //送信完了まで待つ
                TXREG1 = str[i];
            }
        }
    }

    return 0;
}
