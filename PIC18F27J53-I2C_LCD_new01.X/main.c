// PIC18F27J53 I2C LCD New Program
// PIC18F27J53
// 2015.11.11
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

#include <xc.h>
#include <stdint.h>
#include <My_PIC.h>
#include <My_button.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include <My_ringbuf.h>
#include <My_usb_cdc.h>
#include <My_terminal.h>
#include <My_UART.h>

#define LED0 LATAbits.LATA0
#define LED1 LATAbits.LATA1
#define LED2 LATBbits.LATB6
#define LED3 LATBbits.LATB7

void interrupt ISR(void) {
    USB_ISR();
    UART_ISR();
    ST7032_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        LED0 = !LED0;
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
    }
}

void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!strcmp(op0, "help") || !strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\t******************************\n"
                "\t**** PIC18F27J53 template ****\n"
                "\t**** Made by @Ryokeri14   ****\n"
                "\t******************************\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\n\tfor Developper\n"
                "\tRESET();\n"
                "\tbootload\n"
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
    TRISA = 0b00010000; // x,x,x,Vcap,x,x,x,x
    TRISB = 0b00110001; // x,x,SDA,SCL,x,x,x,x
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,LED,T1OSI,T1OSO
    ANCON0 = 0b11111111; // xxx,xxx,xxx,RA5,RA3,RA2,RA1,RA0
    ANCON1 = 0b00011111; // VBG,xxx,xxx,RB0,RC2,RB1,RB3,RB2
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(6);
    timer1_init(0, T1OSC);
    timer3_init(2); // button
    ST7032_init();
    RTCC_init();

    USB_init();
    static uint8_t usbtx[1000];
    ringbuf_init(&usb_tx, usbtx, sizeof (usbtx));
    static uint8_t usbrx[100];
    ringbuf_init(&usb_rx, usbrx, sizeof (usbrx));

    UART_init();
    static uint8_t uarttx[1000];
    ringbuf_init(&uart_tx, uarttx, sizeof (uarttx));
    static uint8_t uartrx[100];
    ringbuf_init(&uart_rx, uartrx, sizeof (uartrx));
}

int main(void) {
    main_init();

    ST7032_clear();
    ST7032_cursor(0, 0);
    ST7032_puts("18F27J53");
    ST7032_cursor(0, 1);
    ST7032_puts("Template");

    INTCONbits.GIE = 1;

    while (1) {
        INTCONbits.GIE = 0;
        USB_task();
        UART_task();
        RTCC_task();
        ST7032_task();
        terminal_task(&usb_tx, &usb_rx);
        INTCONbits.GIE = 1;
        LED1 = !LED1;
        INTCONbits.GIE = 0;
        if (time_change_flag) {
            time_change_flag = 0;
            char s[2][20];
            display_time_0802(&now, s[0], s[1]);
            ST7032_clear();
            ST7032_cursor(0, 0);
            ST7032_puts(s[0]);
            ST7032_cursor(0, 1);
            ST7032_puts(s[1]);
        }
        INTCONbits.GIE = 1;
    }
    return 0;
}
