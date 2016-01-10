// PIC18F27J53
// 2015.06.04
// default,-0-FFF,-1006-1007,-1016-1017
// USB & UART

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

#include <My_PIC.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include <My_ringbuf.h>
#include <My_usb_cdc.h>
#include <My_UART.h>

#define LED0 LATBbits.LATB7
#define LED1 LATBbits.LATB6
#define LED2 LATAbits.LATA0
#define LED3 LATAbits.LATA1
#define LED4 LATAbits.LATA2
#define LED5 LATAbits.LATA3

#define SW0 PORTBbits.RB0
#define SW1 PORTBbits.RB1
#define SW2 PORTBbits.RB2
#define SW3 PORTBbits.RB3

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        LED2 = !LED2;
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b00010000; // x,x,x,Vcap,x,x,x,SW
    TRISB = 0b00111111; // x,x,SDA,SCL,x,x,x,x
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,LED,T1OSI,T1OSO
    ANCON0 = 0b11111111; // xxx,xxx,xxx,RA5,RA3,RA2,RA1,RA0
    ANCON1 = 0b00011111; // VBG,xxx,xxx,RB0,RC2,RB1,RB3,RB2
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(6);
    timer1_init(0, T1OSC);
    timer3_init(2); // button
    I2C_LCD_init();
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

    RTCC_from_RTCC(&now);
    if (now.DD == 0) {
        now.epoch = 0;
        RTCC_from_epoch(&now);
    }

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("USB UART");

    INTCONbits.GIE = 1;

    while (1) {
        USB_task();
        UART_task();
        RTCC_task();

        if (ringbuf_num(&usb_rx)) {
            ringbuf_put(&usb_tx, ringbuf_pop(&usb_rx));
            LED0 = !LED0;
        }
        if (ringbuf_num(&uart_rx)) {
            ringbuf_put(&uart_tx, ringbuf_pop(&uart_rx));
            LED1 = !LED1;
        }
        if (time_change_flag) {
            time_change_flag = 0;
            char s[2][20];
            display_time_0802(&now, s[0], s[1]);
            I2C_LCD_Clear();
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts(s[0]);
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts(s[1]);
        }
    }
    return 0;
}
