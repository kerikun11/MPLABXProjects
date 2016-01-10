/*
 * PIC18F27J53用USB-CDCサンプルプログラム 
 * Date:	2016.01.08
 * Author:	@Ryokeri
 */

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
#include <My_USB_CDC.h>

void interrupt ISR(void) {
    USB_CDC_ISR();
}

void main(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00010000; // RA7, RA6, RA5, Vcap, RA3, RA2, RA1,  RA0
    TRISB = 0b00111111; // RB7, RB6, SDA, SCL,  RB3, RB2, RB1,  RB0
    TRISC = 0b10111010; // RXD, TXD, D+,  D-,   Vusb,RC2, T1OSI,T1OSO
    ANCON0 = 0b11111111; // x,x,x,AN4(RA5),AN3(RA3),AN2(RA2),AN1(RA1),AN0(RA0)
    ANCON1 = 0b00011111; // VBG,x,x,AN12(RB0),AN11(RC2),AN10(RB1),AN9(RB3),AN8(RB2)
    INTCON2bits.RBPU = 0; // PORTB Pull-up Pnable

    USB_CDC_init();

    while (1) {
        // 受信したデータをそのまま送信する。
        if (ringbuf_num(&usb_rx)) {
            uint8_t data = ringbuf_pop(&usb_rx);
            ringbuf_put(&usb_tx, data);
        }
        USB_CDC_task();
    }
}
