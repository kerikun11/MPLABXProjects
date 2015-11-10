// PIC18F27J53
// 2015.07.09

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

#define LED0 LATBbits.LATB7
#define LED1 LATBbits.LATB6
#define LED2 LATBbits.LATB3
#define LED3 LATBbits.LATB2
#define LED4 LATBbits.LATB1

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
        LED0 = !LED0;
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        LED1 = !LED1;
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
        LED2 = !LED2;
    }
}

void main_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,ctl,ctc,ctr
    TRISB = 0b00110001; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11111111; // all digital
    ANCON1 = 0b00001111; // AN8,AN9,AN10,AN12 is analog
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(8); // LED-chika
    timer1_init(0, T1OSC); // Integrate
    timer3_init(3); // button
    I2C_init();
    I2C_LCD_init();
    RTCC_init();
    ADC_init(VDD);

    UART_init();
    static uint8_t txbuf[2000];
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

    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("SLEEP");

    INTCONbits.GIE = 1;

    while (1) {
        LED3 = 0;
        SLEEP();
        NOP();
        LED3 = 1;
        INTCONbits.GIE = 0;
        if (ringbuf_num(&rx_buf)) {
            tx_send(ringbuf_pop(&rx_buf));
            LED4 = !LED4;
        }
        INTCONbits.GIE = 1;
    }
    return 0;
}
