// PIC18F27J53
// template
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

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>

#define LED0 LATBbits.LATB7
#define LED1 LATBbits.LATB6
#define LED2 LATAbits.LATA0
#define LED3 LATAbits.LATA1

void interrupt ISR(void) {
    UART_ISR();
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

    UART_init();
    static uint8_t txbuf[1000];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[100];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
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
    I2C_LCD_Puts("test");

    INTCONbits.GIE = 1;

    while (1) {
        INTCONbits.GIE = 0;
        RTCC_loop();
        if (ringbuf_num(&rx_buf)) {
            LED0 = !LED0;
        }
        INTCONbits.GIE = 1;
    }
    return 0;
}
