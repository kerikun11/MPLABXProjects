// PIC18F27J53
// 2015.03.05
// RTCC
// LCDはI2C小型8x2液晶

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
#define SW PORTAbits.RA6

uint8_t cursor_up[] = {0x1B, 0x5B, 0x41, 0x00};
uint8_t cursor_down[] = {0x1B, 0x5B, 0x42, 0x00};
uint8_t cursor_right[] = {0x1B, 0x5B, 0x43, 0x00};
uint8_t cursor_left[] = {0x1B, 0x5B, 0x44, 0x00};

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>

button_t sw;
uint8_t display_flag;
uint8_t rx_flag;
ringbuf_t rx_buf;

void judgement(uint8_t ascii) {
    uint8_t i;
    tx_sends(cursor_down);
    for (i = 0; i < ringbuf_num(&rx_buf); i++) tx_sends(cursor_right);

    switch (ascii) {
        case '\r':
            rx_flag = 1;
            ringbuf_push(&rx_buf, '\0');
            tx_send(' ');
            break;
        case ' ':
            ringbuf_push(&rx_buf, '\0');
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
                ringbuf_push(&rx_buf, ascii);
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
    interrupt_TXIF();
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
        button_timer_interrupt(&sw, !SW);
        delay_timer_interrupt(&d1);
    }
}

void tx_send_dec(uint8_t dec, uint8_t edit) {
    uint8_t str[10];
    utoa(&str, dec, 2);
    if (edit && RTCCFGbits.HALFSEC)tx_sends("  ");
    else tx_sends(str);
}

void tx_send_time(void) {
    RTCC_from_RTCC(&caltime_now, &epoch_now);

    tx_send_dec(20, edit_flag.flag.YY);
    tx_send_dec(caltime_now.YY, edit_flag.flag.YY);
    tx_sends("/");
    tx_send_dec(caltime_now.MM, edit_flag.flag.MM);
    tx_sends("/");
    tx_send_dec(caltime_now.DD, edit_flag.flag.DD);
    tx_sends(" (");
    tx_sends(weekday_char[caltime_now.EE]);
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

        if (!strcmp(opcode, "ts")) {
            if (!strcmp(opland1, "y")) {
                caltime_now.YY = atoi(opland2);
            }
            if (!strcmp(opland1, "M")) {
                caltime_now.MM = atoi(opland2);
            }
            if (!strcmp(opland1, "d")) {
                caltime_now.DD = atoi(opland2);
            }
            if (!strcmp(opland1, "h")) {
                caltime_now.hh = atoi(opland2);
            }
            if (!strcmp(opland1, "m")) {
                caltime_now.mm = atoi(opland2);
            }
            if (!strcmp(opland1, "s")) {
                caltime_now.ss = atoi(opland2);
            }
            RTCC_from_caltime(&caltime_now, &epoch_now);
            time_change_flag = 1;
        }
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b01000000; // RA7,RA6,RA5,Vcap,RA3,RA2,RA1,RA0
    TRISB = 0b00110000; // RB7,RB6,SDA,SCL, RB3,RB2,RB1,RB0
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,RC2,T1OSI,T1OSO
    ANCON0 = 0b11111000; // all digital
    ANCON1 = 0b00011111; // all digital
    INTCON2bits.RBPU = 0; // PORTB Pull-Up ON

    UCFGbits.UOEMON = 0; //USBの機能をOFF

    //timer0_init(6); // 用
    timer1_init(0, T1OSC); // 用
    timer3_init(2); // button用
    I2C_init();
    I2C_LCD_init();
    RTCC_init();

    UART_init();
    static uint8_t txbuf[250];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[250];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("**RTCC**");

    epoch_now = 3155759990; // 2099/13/31/23:59-50
    RTCC_from_epoch(&caltime_now, &epoch_now);
    tx_sends("\n\n\n");

    while (1) {
        RTCC_loop();
        rx_operation();
        if (time_change_flag) {
            time_change_flag = 0;
            print_time(2);
            display_time(&caltime_now, &epoch_now);
        }
        if (sw.flag.long_holding_3) {
            sw.flags = 0;
            RTCC_time_set_toggle();
        }
        if (edit_flag.flags) {
            if (sw.flag.long_hold_1) {
                sw.flags = 0;
                RTCC_time_set_cursor();
            }
            if (sw.flag.press) {
                sw.flags = 0;
                RTCC_time_set_inc(&caltime_now, &epoch_now);
            }
        }
    }
    return 0;
}
