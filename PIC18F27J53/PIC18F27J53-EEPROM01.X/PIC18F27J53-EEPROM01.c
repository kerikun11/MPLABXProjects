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
#pragma config IOL1WAY = OFF, ADCSEL = BIT10, MSSP7B_EN = MSK7
// CONFIG4L
#pragma config WPFP = PAGE_127, WPCFG = OFF
// CONFIG4H
#pragma config WPDIS = OFF, WPEND = PAGE_WPFP, LS48MHZ = SYS48X8

#define _XTAL_FREQ 48000000

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATB3
#define LED3 LATB2

#define PIC18F27J53

#include <My_header.h>
#include <My_button.h>

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
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b00000000; // OUT2,OUT1,OUT0,Vcap,SW,SW2,SW1,SW0
    TRISB = 0b00110000; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11111111; // all digital
    ANCON1 = 0b00011111; // all digital
    INTCON2bits.RBPU = 0;

    timer0_init(6); // 用
    timer1_init(0, T1OSC); // 用
    timer3_init(2); // button用

    UART_init();
    static uint8_t txbuf[250];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[250];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}
// メインの処理

void main() {
    main_init();

    INTCONbits.GIE = 1;

    while (1) {
        if (ringbuf_num(&rx_buf)) {
            char ascii = ringbuf_pop(&rx_buf);
            tx_send(ascii);
            //eeprom_write(0, ascii);
            //Delay_ms(10);
        }
        //tx_send(eeprom_read(0));
        //Delay_ms(2000);
    }
}
