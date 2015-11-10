// PIC18F27J53
// 2015.05.28

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
// Define
#define _XTAL_FREQ 48000000
#define A_PULSE PORTBbits.RB0
#define B_PULSE PORTBbits.RB1
// Device
#define PIC18F27J53
// Includes
#include <My_header.h>
// Global
int16_t encoder = 0;

void interrupt ISR(void) {
    interrupt_TXIF();
    if (PIR1bits.RC1IF) {
        char ascii = RCREG1;
        tx_send(ascii);
    }
    if(INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        static uint8_t prev_A;
        static uint8_t prev_B;
        LATB7 = !LATB7;
        if (A_PULSE != prev_A) {
            prev_A = A_PULSE;
            if (A_PULSE) {
                if (B_PULSE) {
                    encoder--;
                } else {
                    encoder++;
                }
            } else {
                if (B_PULSE) {
                    //encoder++;
                } else {
                    //encoder--;
                }
            }
        }
        if (B_PULSE != prev_B) {
            prev_B = B_PULSE;
            if (B_PULSE) {
                if (A_PULSE) {
                    //encoder++;
                } else {
                    //encoder--;
                }
            } else {
                if (A_PULSE) {
                    //encoder--;
                } else {
                    //encoder++;
                }
            }
        }
    }
}

int main(void) {
    OSC_init();
    TRISA = 0b00000000;
    TRISB = 0b00000011;
    TRISC = 0b10000000;
    ANCON0 = 0b11111111;
    ANCON1 = 0b00011111;
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(3);

    UART_init();
    uint8_t txbuf[100];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));

    INTCONbits.GIE = 1;

    while (1) {
        static int16_t prev_e;
        if (encoder != prev_e) {
            prev_e = encoder;
            if (encoder < 0) {
                tx_send('-');
                tx_sendn(-encoder, 5);
                tx_send('\n');
            } else {
                tx_sendn(encoder, 5);
                tx_send('\n');
            }
        }
    }
    return 0;
}
