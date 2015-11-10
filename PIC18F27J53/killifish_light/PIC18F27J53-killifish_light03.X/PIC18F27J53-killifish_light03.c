// PIC18F27J53
// 2015.07.12
// RTCC

#include <xc.h>
#include <stdint.h>
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

#define PR_VALUE 100

#define PIC18F27J53

#include <My_header.h>
#include <My_ringbuf.h>
#include <My_button.h>
#include <My_RTCC.h>
#include <My_terminal.h>

button_t sw_R;
button_t sw_G;
button_t sw_B;
uint8_t display_flag;
uint8_t rx_flag;
uint8_t rc_flag;
uint8_t time_sync;

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
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&sw_R, !SWR);
        button_timer_interrupt(&sw_G, !SWG);
        button_timer_interrupt(&sw_B, !SWB);
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

void command_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!my_strcmp(op0, "help") || !my_strcmp(op0, "?")) {
        tx_sends(
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
    if (!my_strcmp(op0, "RESET();")) {
        RESET();
    }
    if (!my_strcmp(op0, "at") || !my_strcmp(op0, "adjust_time")) {
        command_at(tx, op1, op2);
    }
    if (!my_strcmp(op0, "print_time") || !my_strcmp(op0, "t")) {
        print_time(tx, 1);
    }
    if (!my_strcmp(op0, "set")) {
        if (!my_strcmp(op1, "sync")) {
            light_mode = TIME_SYNC_mode;
        }
        if (!my_strcmp(op1, "adc") || !my_strcmp(op1, "ADC")) {
            light_mode = ADC_mode;
        }
    }
    if (!my_strcmp(op0, "pwm") || !my_strcmp(op0, "PWM")) {
        if (!my_strcmp(op1, "r") || !my_strcmp(op1, "R")) {
            light_mode = COMMAND_mode;
            PWM_set(0, my_atoi(op2));
        }
        if (!my_strcmp(op1, "g") || !my_strcmp(op1, "G")) {
            light_mode = COMMAND_mode;
            PWM_set(1, my_atoi(op2));
        }
        if (!my_strcmp(op1, "b") || !my_strcmp(op1, "B")) {
            light_mode = COMMAND_mode;
            PWM_set(2, my_atoi(op2));
        }
        if (!my_strcmp(op1, "w") || !my_strcmp(op1, "W")) {
            light_mode = COMMAND_mode;
            PWM_set(3, my_atoi(op2));
        }
        if (!my_strcmp(op1, "clear")) {
            light_mode = COMMAND_mode;
            PWM_set(0, 0);
            PWM_set(1, 0);
            PWM_set(2, 0);
            PWM_set(3, 0);
        }
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

    //timer0_init(6); // —p
    timer1_init(0, T1OSC); // —p
    timer3_init(2); // button—p
    ADC_init(VDD);
    RTCC_init();
    PWM_init(PR_VALUE); //250 is 3kHz

    UART_init();
    static uint8_t txbuf[1000];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[250];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    //epoch_now = 3155759990; // 2099/13/31/23:59-50
    RTCC_from_RTCC(&caltime_now, &epoch_now);
    if (caltime_now.DD == 0) {
        epoch_now = 0;
        RTCC_from_epoch(&caltime_now, &epoch_now);
    }

    uint16_t i;
    while (1) {
        RTCC_loop();
        my_terminal_loop(&tx_buf, &rx_buf);
        if (ringbuf_num(&tx_buf))PIE1bits.TXIE = 1;
        if (time_change_flag) {
            time_change_flag = 0;
            RTCC_from_RTCC(&caltime_now, &epoch_now);
            if (light_mode == TIME_SYNC_mode) {
                epoch_t temp = (epoch_t) epoch_now % DAY;
                if (temp > DAY / 2)temp = DAY - temp;
                temp = temp * 2 * PR_VALUE / DAY;
                PWM_set(3, temp);
            }
        }
        if (sw_G.flag.press) {
            sw_G.flags = 0;
            light_mode = COMMAND_mode;
            static uint8_t n = 0;
            if (n >= 4) n = 0;
            else n++;
            uint8_t value = PR_VALUE / 4 * n;
            for (i = 0; i < 3; i++) {
                PWM_set(i, value);
            }
        }
        if (sw_B.flag.press) {
            sw_B.flags = 0;
            light_mode = COMMAND_mode;
            static uint8_t n = 0;
            if (n >= 4) n = 0;
            else n++;
            uint8_t value = PR_VALUE / 4 * n;
            PWM_set(3, value);
        }
        if (sw_R.flag.press) {
            sw_R.flags = 0;
            light_mode = TIME_SYNC_mode;
        }
        if (sw_R.flag.long_hold_1) {
            sw_R.flags = 0;
            light_mode = ADC_mode;
        }
        if (light_mode == ADC_mode) {
            for (i = 0; i < 3; i++) {
                uint16_t scan = (ADC(i) >> 4) * PR_VALUE / 255;
                static uint8_t prev_scan[3];
                if (scan != prev_scan[i]) {
                    prev_scan[i] = scan;
                    PWM_set(i, scan);
                }
            }
        }
    }
    return 0;
}
