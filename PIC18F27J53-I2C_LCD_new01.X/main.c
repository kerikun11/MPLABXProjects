// PIC18F27J53 I2C LCD New Program

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
#include <My_ST7032.h>
#include <My_ringbuf.h>

#define LED0 LATAbits.LATA0
#define LED1 LATAbits.LATA1
#define LED2 LATAbits.LATA2
#define LED3 LATAbits.LATA3

uint8_t one_second_flag;

void interrupt ISR(void) {
    ST7032_ISR();
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        one_second_flag = 1;
        LED0 = !LED0;
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
    ST7032_init();
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    while (1) {
        ST7032_task();
        // メインループの表示
        LED1 = !LED1;
        // 1秒ごとに液晶表示
        if (one_second_flag) {
            one_second_flag = 0;
            ST7032_clear();
            ST7032_cursor(0, 0);
            ST7032_puts("18F27J53");
            ST7032_cursor(0, 1);
            ST7032_puts("I2C_new");
        }
    }
    return 0;
}
