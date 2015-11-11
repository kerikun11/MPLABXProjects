// killifish_light
// PIC18F27J53
// 01 2015.07.05 command operation 原形
// 02 2015.07.18 command operation 発展
// 03 2015.08.26 terminal.h にまとめた
// 04 2015.09.03 teminal operation 改良
// 05 2015.10.07 using My_library .h & .c file
// 06 2015.11.09 using USB CDC instead of UART

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <My_PIC.h>
#include <My_terminal.h>
#include <My_RTCC.h>
#include <My_UART.h>

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

#define RED 0
#define GREEN 1
#define BLUE 2
#define WHITE 3

#define PR_VALUE 250

button_t sw_R;
button_t sw_G;
button_t sw_B;
uint8_t ADC_flag;

enum {
    TIME_SYNC_mode,
    ADC_mode,
    COMMAND_mode
} light_mode;

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x80;
        LATBbits.LATB5 = !LATBbits.LATB5;
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&sw_R, !SWR);
        button_timer_interrupt(&sw_G, !SWG);
        button_timer_interrupt(&sw_B, !SWB);
        ADC_flag = 1;
    }
}

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

    CCP4CONbits.CCP4M = 12; // PWM, single output
    CCPTMRS1bits.C4TSEL = 0;
    CCPR4Lbits.CCPR4L = 0;
    CCP4CONbits.DC4B = 0;

    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 2;
    PR2 = PR - 1;
    T2CONbits.TMR2ON = 1;
}

void PWM_set(uint8_t color, uint16_t value) {
    value = value * value / PR_VALUE;
    value = value * value / PR_VALUE;
    value = value * 3 / 4;
    switch (color) {
        case RED:
            if (value < PR_VALUE / 4) {
                value = value;
            } else {
                value = 2 * (value - PR_VALUE / 4) / 3 + PR_VALUE / 4;
            }
            break;
        case GREEN:
            if (value < PR_VALUE / 4) {
                value = value;
            } else {
                value = value;
            }
            break;
        case BLUE:
            if (value < PR_VALUE / 4) {
                value = value;
            } else {
                value = 3 * (value - PR_VALUE / 4) / 4 + PR_VALUE / 4;
            }
            break;
        case WHITE:
            break;
    }
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
        case WHITE:
            CCP4CONbits.DC4B = 0;
            CCPR4L = value;
            break;
    }
}

void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!strcmp(op0, "help") || !strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\t**************************\n"
                "\t**** Killifish Light  ****\n"
                "\t**** Made by @Ryokeri ****\n"
                "\t**************************\n\n"
                "\tcommand \topeland1\topeland2\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tpwm [color:R,G,B,W] [value(%):0~100]\n"
                "\tpwm clear\n"
                "\tset time_sync_mode(sync)\n"
                "\tset ADC_mode(adc)\n"
                "\tRESET();\n"
                );
    }
    terminal_time(tx, op0, op1, op2);
    if (!strcmp(op0, "RESET();")) {
        RESET();
    }
    if (!strcmp(op0, "en")) {
        char str[30];
        sprintf(str, "WREN=%d,EN=%d\n", RTCCFGbits.RTCWREN, RTCCFGbits.RTCEN);
        ringbuf_put_str(tx, str);
    }
    if (!strcmp(op0, "set")) {
        if (!strcmp(op1, "sync")) {
            light_mode = TIME_SYNC_mode;
        }
        if (!strcmp(op1, "adc") || !strcmp(op1, "ADC")) {
            light_mode = ADC_mode;
        }
    }
    if (!strcmp(op0, "pwm") || !strcmp(op0, "PWM")) {
        if (!strcmp(op1, "r") || !strcmp(op1, "R")) {
            light_mode = COMMAND_mode;
            PWM_set(0, atoi(op2) * PR_VALUE / 100);
        }
        if (!strcmp(op1, "g") || !strcmp(op1, "G")) {
            light_mode = COMMAND_mode;
            PWM_set(1, atoi(op2) * PR_VALUE / 100);
        }
        if (!strcmp(op1, "b") || !strcmp(op1, "B")) {
            light_mode = COMMAND_mode;
            PWM_set(2, atoi(op2) * PR_VALUE / 100);
        }
        if (!strcmp(op1, "w") || !strcmp(op1, "W")) {
            light_mode = COMMAND_mode;
            PWM_set(3, atoi(op2) * PR_VALUE / 100);
        }
        if (!strcmp(op1, "clear")) {
            light_mode = COMMAND_mode;
            PWM_set(0, 0);
            PWM_set(1, 0);
            PWM_set(2, 0);
            PWM_set(3, 0);
        }
    }
}

void light_task(void) {
    uint8_t i;
    if (time_change_flag) {
        time_change_flag = 0;
        RTCC_from_RTCC(&now);
        if (light_mode == TIME_SYNC_mode) {
            epoch_t temp = (epoch_t) now.epoch % DAY;
            if (temp > DAY / 2)temp = DAY - temp;
            temp = temp * 2 * PR_VALUE / DAY;
            PWM_set(3, temp);
            for (i = 0; i < 3; i++) {
                PWM_set(i, temp);
            }
        }
    }
    if (sw_G.flag.press) {
        sw_G.flags = 0;
        light_mode = COMMAND_mode;
        static uint8_t n = 0;
        if (n >= 3) n = 0;
        else n++;
        uint8_t value = PR_VALUE / 3 * n;
        for (i = 0; i < 3; i++) {
            PWM_set(i, value);
        }
    }
    if (sw_B.flag.press) {
        sw_B.flags = 0;
        light_mode = COMMAND_mode;
        static uint8_t n = 0;
        if (n >= 3) n = 0;
        else n++;
        uint8_t value = PR_VALUE / 3 * n;
        PWM_set(3, value);
    }
    if (sw_R.flag.press) {
        sw_R.flags = 0;
        light_mode = TIME_SYNC_mode;
    }
    //        if (sw_R.flag.long_hold_1) {
    //            sw_R.flags = 0;
    //            light_mode = ADC_mode;
    //        }
    //        if (light_mode == ADC_mode && ADC_flag == 1) {
    //            ADC_flag = 0;
    //            for (i = 0; i < 3; i++) {
    //                uint16_t scan = (ADC(i) >> 4) * PR_VALUE / 255;
    //                static uint8_t prev_scan[3];
    //                if (scan != prev_scan[i]) {
    //                    prev_scan[i] = scan;
    //                    PWM_set(i, scan);
    //                }
    //            }
    //        }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b11100111; // SWB,SWG,SWR,Vcap,x,ADCB,ADCG,ADCR
    TRISB = 0b00000000; // PGD,PGC,x,PWMW,x,PWMB,PWMG,PWMR
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,x,T1OSI,T1OSO
    ANCON0 = 0b11111000; // AN2,AN1,AN0 is analog
    ANCON1 = 0b00011111; // all digital
    INTCON2bits.RBPU = 0; // PORTB Pull-Up Enable

    timer0_init(8); // 用
    timer1_init(0, T1OSC); // 用
    timer3_init(2); // button用
    ADC_init(VDD);
    RTCC_init();
    PWM_init(PR_VALUE); //250 is 3kHz

    UART_init();
    static uint8_t txbuf[1000];
    ringbuf_init(&uart_tx, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[250];
    ringbuf_init(&uart_rx, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();

    RTCC_from_RTCC(&now);
    if (now.DD == 0) {
        now.epoch = 0;
        RTCC_from_epoch(&now);
    }

    while (1) {
        INTCONbits.GIE = 0;
        RTCC_task();
        terminal_task(&uart_tx, &uart_rx);
        UART_task();
        light_task();
        INTCONbits.GIE = 1;
    }
    return 0;
}
