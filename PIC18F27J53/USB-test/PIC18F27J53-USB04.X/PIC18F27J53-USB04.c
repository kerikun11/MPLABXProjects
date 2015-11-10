// PIC18F27J53
// 2015.06.04
// My_terminal.h
// default,-0-FFF,-1006-1007,-1016-1017

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

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD
#define MY_STDLIB   // my_utoa,my_atoi,my_strcmp

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>
#include <My_ringbuf.h>
#include <My_terminal.h>
#include <my_usb_cdc.h>

#define LED0 LATBbits.LATB7
#define LED1 LATBbits.LATB6
#define LED2 LATAbits.LATA0
#define LED3 LATAbits.LATA1

ringbuf_t usb_tx;
ringbuf_t usb_rx;

void interrupt ISR(void) {
    USB_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
        LED2 = !LED2;
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        LED3 = !LED3;
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
    }
}

void command_operation(ringbuf_t *tx, char *opcode, char *opland1, char *opland2, char *opland3) {
    if (!my_strcmp(opcode, "help") || !my_strcmp(opcode, "?")) {
        ringbuf_put_str(tx,
                "\t**************************\n"
                "\t** USB Sample Program ****\n"
                "\t** Made by @Ryokeri   ****\n"
                "\t**************************\n\n"
                "\tcommand \topeland1\topeland2\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tRESET();\n"
                );
    }
    if (!my_strcmp(opcode, "RESET();")) {
        RESET();
    }
    if (!my_strcmp(opcode, "at") || !my_strcmp(opcode, "adjust_time")) {
        if (!my_strcmp(opland1, "y")) {
            command_at(tx, &caltime_now.YY, 0, 99, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "M")) {
            command_at(tx, &caltime_now.MM, 1, 12, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "d")) {
            command_at(tx, &caltime_now.DD, 1, month_length(caltime_now.YY, caltime_now.MM), my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "h")) {
            command_at(tx, &caltime_now.hh, 0, 23, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "m")) {
            command_at(tx, &caltime_now.mm, 0, 59, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "s")) {
            command_at(tx, &caltime_now.ss, 0, 59, my_atoi(opland2));
        }
    }
    if (!my_strcmp(opcode, "print_time") || !my_strcmp(opcode, "t")) {
        print_time(tx);
    }
}

void USB_loop(void) {
    char str[110];
    uint8_t i;
    int rx_len;
    rx_len = get_string_usb(str, 100);
    for (i = 0; i < rx_len; i++) {
        ringbuf_put(&usb_rx, str[i]);
    }
    uint16_t n = ringbuf_num(&usb_tx);
    if (n) {
        if (n > 100) {
            n = 100;
        }
        for (i = 0; i < n; i++) {
            str[i] = ringbuf_pop(&usb_tx);
        }
        while (put_string_usb(str, n));
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b00010000; // x,x,x,Vcap,x,x,x,x
    TRISB = 0b00110001; // LED0,LED1,SDA,SCL,x,x,x,SW
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,LED,T1OSI,T1OSO
    ANCON0 = 0b11111111; // xxx,xxx,xxx,RA5,RA3,RA2,RA1,RA0
    ANCON1 = 0b00011111; // VBG,xxx,xxx,RB0,RC2,RB1,RB3,RB2
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(6); // LED-chika
    timer1_init(0, T1OSC); // Integrate
    timer3_init(2); // button
    I2C_init();
    I2C_LCD_init();
    RTCC_init();

    USB_init();
    static uint8_t usbtx[1000];
    ringbuf_init(&usb_tx, usbtx, sizeof (usbtx));
    static uint8_t usbrx[100];
    ringbuf_init(&usb_rx, usbrx, sizeof (usbrx));

    //    UART_init();
    //    static uint8_t txbuf[1000];
    //    ringbuf_init(tx_buf, txbuf, sizeof (txbuf));
    //    static uint8_t rxbuf[100];
    //    ringbuf_init(rx_buf, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();

    RTCC_from_RTCC(&caltime_now, &epoch_now);
    if (caltime_now.DD == 0) {
        epoch_now = 0;
        RTCC_from_epoch(&caltime_now, &epoch_now);
    }

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("USB CDC");

    INTCONbits.GIE = 1;

    while (1) {
        INTCONbits.GIE = 0;
        USB_loop();
        RTCC_loop();
        if (time_change_flag) {
            time_change_flag = 0;
            display_time_0802(&caltime_now, &epoch_now);
            LED1 = !LED1;
        }
        if (ringbuf_num(&usb_rx)) {
            LED0 = !LED0;
        }
        my_terminal_loop(&usb_tx, &usb_rx);
        INTCONbits.GIE = 1;
    }
    return 0;
}
