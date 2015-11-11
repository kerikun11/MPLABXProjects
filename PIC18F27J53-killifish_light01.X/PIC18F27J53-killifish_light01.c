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

// CONFIG1L
#pragma config WDTEN = ON, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
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

#define PR_VALUE 255

uint8_t cursor_up[] = {0x1B, 0x5B, 0x41, 0x00};
uint8_t cursor_down[] = {0x1B, 0x5B, 0x42, 0x00};
uint8_t cursor_right[] = {0x1B, 0x5B, 0x43, 0x00};
uint8_t cursor_left[] = {0x1B, 0x5B, 0x44, 0x00};

#define PIC18F27J53

#include <My_header.h>
#include <My_ringbuf.h>
#include <My_button.h>
#include <My_RTCC.h>
#include <My_stdlib.h>

button_t sw_R;
button_t sw_G;
button_t sw_B;
uint8_t display_flag;
uint8_t rx_flag;
uint8_t time_sync;
ringbuf_t rx_buf;

enum {
    TIME_SYNC_mode,
    ADC_mode,
    COMMAND_mode
} light_mode;

void judgement(uint8_t ascii) {
    uint8_t i;
    tx_sends(cursor_down);
    for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_sends(cursor_right);

    switch (ascii) {
        case '\r':
            rx_flag = 1;
            ringbuf_put(&rx_buf, '\0');
            tx_send(' ');
            break;
        case ' ':
            ringbuf_put(&rx_buf, '\0');
            tx_send(' ');
            tx_sends("_\b");
            break;
        case '\b':
            ringbuf_backspace(&rx_buf);
            tx_sends("\b_ \b\b");
            break;
        case 0x7F:
            for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_sends("\b_ \b\b");
            ringbuf_delete(&rx_buf);
            break;
        default:
            if (ascii >= ' ' && ascii <= '~') {
                ringbuf_put(&rx_buf, ascii);
                tx_send(ascii);
                tx_sends("_\b");
            }
            break;
    }
    if (rx_flag) {
        for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_send('\b');
        for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_send(' ');
    }
    for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_send('\b');
    tx_sends(cursor_up);
}

void interrupt ISR(void) {
    UART_ISR();
    if (PIR1bits.RC1IF) {
        PIR1bits.RC1IF = 0;
        uint8_t ascii = RCREG1;
        judgement(ascii);
    }
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
    switch (color) {
        case 0:
            CCP1CONbits.DC1B = 0;
            CCPR1L = value * 2 / 3;
            break;
        case 1:
            CCP2CONbits.DC2B = 0;
            CCPR2L = value;
            break;
        case 2:
            CCP3CONbits.DC3B = 0;
            CCPR3L = value * 3 / 4;
            break;
        case 3:
            CCP4CONbits.DC4B = 0;
            CCPR4L = value;
            break;
    }
}

void tx_send_dec(uint8_t dec, uint8_t edit) {
    uint8_t str[10];
    my_utoa(&str, dec, 2);
    if (edit && RTCCFGbits.HALFSEC)tx_sends("  ");
    else tx_sends(str);
}

void tx_send_time(void) {
    tx_send_dec(20, edit_flag.flag.YY);
    tx_send_dec(caltime_now.YY, edit_flag.flag.YY);
    tx_sends("/");
    tx_send_dec(caltime_now.MM, edit_flag.flag.MM);
    tx_sends("/");
    tx_send_dec(caltime_now.DD, edit_flag.flag.DD);
    tx_sends(" (");
    tx_sends(weekday_3char[caltime_now.EE]);
    tx_sends(") ");
    tx_send_dec(caltime_now.hh, edit_flag.flag.hh);
    if (colon)tx_send(':');
    else tx_send(' ');
    tx_send_dec(caltime_now.mm, edit_flag.flag.mm);
    tx_sends("-");
    tx_send_dec(caltime_now.ss, edit_flag.flag.ss);
    tx_sends(" ");
}

void print_time(uint8_t row) {
    uint8_t i;
    GIE = 0;
    for (i = 0; i < row; i++) tx_sends(cursor_down);
    tx_send_time();
    for (i = 0; i < 26; i++) tx_send('\b');
    for (i = 0; i < row; i++) tx_sends(cursor_up);
    GIE = 1;
}

void print(uint8_t * str, uint8_t row) {
    uint8_t i;
    GIE = 0;
    for (i = 0; i < row; i++) tx_sends(cursor_down);
    tx_sends(str);
    while (*str++)tx_send('\b');
    for (i = 0; i < row; i++) tx_sends(cursor_up);
    GIE = 1;
}

void rx_operation(void) {
    if (rx_flag) {
        uint8_t i;
        rx_flag = 0;
        uint8_t opcode[250];
        uint8_t opland1[250];
        uint8_t opland2[250];

        uint8_t cnt_char = 0;
        uint8_t cmd[250];

        for (i = 0; opcode[i] = ringbuf_pop(&rx_buf); i++) {
            cmd[cnt_char++] = opcode[i];
        }
        opcode[i] = '\0';
        cmd[cnt_char++] = ' ';
        for (i = 0; opland1[i] = ringbuf_pop(&rx_buf); i++) {
            cmd[cnt_char++] = opcode[i];
        }
        opland1[i] = '\0';
        cmd[cnt_char++] = ' ';
        for (i = 0; opland2[i] = ringbuf_pop(&rx_buf); i++) {
            cmd[cnt_char++] = opcode[i];
        }
        opland2[i] = '\0';
        cmd[cnt_char] = '\0';

        if (!my_strcmp(opcode, "ts")) {
            if (!my_strcmp(opland1, "y")) {
                caltime_now.YY = my_atoi(opland2);
            }
            if (!my_strcmp(opland1, "M")) {
                caltime_now.MM = my_atoi(opland2);
            }
            if (!my_strcmp(opland1, "d")) {
                caltime_now.DD = my_atoi(opland2);
            }
            if (!my_strcmp(opland1, "h")) {
                caltime_now.hh = my_atoi(opland2);
            }
            if (!my_strcmp(opland1, "m")) {
                caltime_now.mm = my_atoi(opland2);
            }
            if (!my_strcmp(opland1, "s")) {
                caltime_now.ss = my_atoi(opland2);
            }
            RTCC_from_caltime(&caltime_now, &epoch_now);
            time_change_flag = 1;
        }
        if (!my_strcmp(opcode, "set")) {
            if (!my_strcmp(opland1, "sync")) {
                light_mode = TIME_SYNC_mode;
            }
            if (!my_strcmp(opland1, "adc")) {
                light_mode = ADC_mode;
            }
            if (!my_strcmp(opland1, "r")) {
                light_mode = COMMAND_mode;
                PWM_set(0, my_atoi(opland2));
            }
            if (!my_strcmp(opland1, "g")) {
                light_mode = COMMAND_mode;
                PWM_set(1, my_atoi(opland2));
            }
            if (!my_strcmp(opland1, "b")) {
                light_mode = COMMAND_mode;
                PWM_set(2, my_atoi(opland2));
            }
            if (!my_strcmp(opland1, "w")) {
                light_mode = COMMAND_mode;
                PWM_set(3, my_atoi(opland2));
            }
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

    //timer0_init(6); // 用
    timer1_init(0, T1OSC); // 用
    timer3_init(2); // button用
    ADC_init(VDD);
    RTCC_init();
    PWM_init(PR_VALUE); //250 is 3kHz

    UART_init();
    static uint8_t txbuf[250];
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

    tx_sends("\n\n\n");

    uint16_t i;
    while (1) {
        CLRWDT();
        RTCC_loop();
        rx_operation();
        if (time_change_flag) {
            time_change_flag = 0;
            print_time(2);
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
            if (light_mode == TIME_SYNC_mode)light_mode = ADC_mode;
            else if (light_mode == ADC_mode)light_mode = COMMAND_mode;
            else if (light_mode == COMMAND_mode)light_mode = TIME_SYNC_mode;
        }
        if (light_mode == ADC_mode) {
            for (i = 0; i < 3; i++) {
                uint8_t scan = (ADC(i) >> 4);
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
