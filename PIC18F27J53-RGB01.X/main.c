// PIC18F27J53

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <My_PIC.h>
#include <My_terminal.h>
#include <My_RTCC.h>
#include <My_usb_cdc.h>

// default,-0-FFF,-1006-1007,-1016-1017
// CONFIG1L
#pragma config WDTEN = OFF, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
// CONFIG1H
#pragma config CPUDIV = OSC1, CP0 = OFF
// CONFIG2L
#pragma config OSC = INTOSCPLL, SOSCSEL = LOW, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
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

#define SWR PORTAbits.RA5
#define SWG PORTAbits.RA6
#define SWB PORTAbits.RA7

#define RED     0
#define GREEN   1
#define BLUE    2

#define PR_VALUE 255

button_t sw_R;
button_t sw_G;
button_t sw_B;
uint8_t ADC_flag;
uint8_t t0f;

void PWM_init(uint8_t PR) {
    PPSCONbits.IOLOCK = 0;
    if (PPSCONbits.IOLOCK != 0) {
        EECON2 = 0x55;
        EECON2 = 0xAA;
        PPSCONbits.IOLOCK = 0;
    }

    RPOR3 = 14;
    RPOR4 = 18;
    RPOR5 = 22;

    CCP1CONbits.CCP1M = 12; // PWM, single output
    CCP1CONbits.P1M = 0; // single output
    CCPTMRS0bits.C1TSEL = 0;
    CCPR1Lbits.CCPR1L = 0;
    CCP1CONbits.DC1B = 0;

    CCP2CONbits.CCP2M = 12; // PWM, single output
    CCP2CONbits.P2M = 0; // single output
    CCPTMRS0bits.C2TSEL = 0;
    CCPR2Lbits.CCPR2L = 0;
    CCP2CONbits.DC2B = 0;

    CCP3CONbits.CCP3M = 12; // PWM, single output
    CCP3CONbits.P3M = 0; // single output
    CCPTMRS0bits.C3TSEL = 0;
    CCPR3Lbits.CCPR3L = 0;
    CCP3CONbits.DC3B = 0;

    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 2;
    PR2 = PR - 1;
    T2CONbits.TMR2ON = 1;
}

void PWM_set(uint8_t color, uint16_t value) {
    switch (color) {
        case RED:
            CCP1CONbits.DC1B = 0;
            CCPR1L = value;
            break;
        case GREEN:
            CCP2CONbits.DC2B = 0;
            CCPR2L = value;
            break;
        case BLUE:
            CCP3CONbits.DC3B = 0;
            CCPR3L = value;
            break;
    }
}

void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!strcmp(op0, "help") || !strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tRESET();\n"
                );
    }
    terminal_time(tx, op0, op1, op2);
    if (!strcmp(op0, "RESET();")) {
        RESET();
    }
    if (!strcmp(op0, "bootload")) {
        asm("goto   0x001C");
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b11100111; // SWB,SWG,SWR,Vcap,x,ADCB,ADCG,ADCR
    TRISB = 0b00000000; // PGD,PGC,x,PWMW,x,PWMB,PWMG,PWMR
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,x,T1OSI,T1OSO
    ANCON0 = 0b11111000; // AN2,AN1,AN0 is analog
    ANCON1 = 0b00011111; // all digital
    INTCON2bits.RBPU = 0; // PORTB Pull-Up Enable

    timer0_init(8); // ?
    timer1_init(0, T1OSC); // ?
    timer3_init(2); // button?
    RTCC_init();
    PWM_init(PR_VALUE); //250 is 3kHz

    USB_CDC_init();
}

int main(void) {
    main_init();

    while (1) {
        INTCONbits.GIE = 0;
        USB_CDC_task();
        INTCONbits.GIE = 1;

        INTCONbits.GIE = 0;
        RTCC_task();
        INTCONbits.GIE = 1;

        INTCONbits.GIE = 0;
        terminal_task(&usb_tx, &usb_rx);
        INTCONbits.GIE = 1;
    }
    return 0;
}

void interrupt ISR(void) {
    USB_CDC_ISR();
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        static uint8_t cnt = 0;
        switch (cnt) {
            case 0:
                PWM_set(RED, 255);
                PWM_set(GREEN, 0);
                PWM_set(BLUE, 0);
                cnt++;
                break;
            case 1:
                PWM_set(RED, 80);
                PWM_set(GREEN, 80);
                PWM_set(BLUE, 80);
                cnt++;
                break;
            case 2:
                PWM_set(RED, 0);
                PWM_set(GREEN, 0);
                PWM_set(BLUE, 255);
                cnt++;
                break;
            case 3:
                PWM_set(RED, 80);
                PWM_set(GREEN, 80);
                PWM_set(BLUE, 80);
                cnt = 0;
                break;
        }
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&sw_R, !SWR);
        button_timer_interrupt(&sw_G, !SWG);
        button_timer_interrupt(&sw_B, !SWB);
    }
}
