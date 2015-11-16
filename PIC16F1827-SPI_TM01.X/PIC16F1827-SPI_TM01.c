#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000
#define CS LATB0

#define PIC16F1827
#define ADT7310

#define C_SEL LATAbits.LATA0

#include <My_header.h>
#include <My_SPI.h>

void interrupt isr(void) {
    interrupt_TXIF();
    if (TMR0IF) {
        TMR0 = 0;
    }
    if (RCIF) {
        RCIF = 0;
        char ascii = RCREG;
        tx_send(ascii);
    }
}

void main(void) {
    OSCCON = 0x70;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x06;
    WPUA = TRISA;
    WPUB = TRISB;
    OPTION_REGbits.nWPUEN = 0;
    APFCON0bits.RXDTSEL = 1;
    APFCON0bits.SDO1SEL = 1;
    APFCON1bits.TXCKSEL = 1;

    UART_init();
    SPI_init(MASTER);

    char buf[30];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    INTCONbits.GIE = 1;

    SPI_TM_init();
    Delay_ms(240);

    while (1) {
        char cbuf[50];
        int16_t t = SPI_TM_Read();
        sprintf(cbuf, "t=%d\n", t);
        tx_sends(&cbuf);
        Delay_ms(1000);
    }
}
