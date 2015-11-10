#include <xc.h>
#include <stdint.h>
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
#include <My_header_16F.h>

#define THRESHOLD_H 0x0D

unsigned int cap; // For calc
unsigned char intFlag; // Interrupt flag
unsigned char cnt; // For UART cnt

void interrupt isr(void) {
    interrupt_TXIF();
    if (TMR0IF) {
        TMR0 = 0;
        INTCONbits.TMR0IF = 0;
        intFlag = 1;
    }
    if (RCIF) {
        RCIF = 0;
        char ascii = RCREG;
    }
}

void mainFunc(void) {
    CPSCON0bits.CPSON = 0;

    cap = (TMR1H << 8) + TMR1L;

    if ((cap >> 8) > THRESHOLD_H) { // Not touch
        LATAbits.LATA1 = 0;
    } else { // Touch
        LATAbits.LATA1 = 1;
    }

    TMR1L = 0;
    TMR1H = 0;
    CPSCON0bits.CPSON = 1;

    if (cnt++ >= 10) { // 10‰ñ‚É1“x(16.384 * 10[ms])‚­‚ç‚¢‚É‚µ‚È‚¢‚Æ‘‚·‚¬‚é
        tx_send(cap >> 8);
        cnt = 0;
    }
}

void main() {
    cap = 0;
    intFlag = 0;

    OSCCON = 0x70; // Internal 8MHz clock
    ANSELA = 0x01; // RA0 for cap sensor
    ANSELB = 0x00;
    TRISA = 0x01;
    TRISB = 0x02;

    UART_init(PIC16F1827);

    char buf[30];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    __delay_ms(100);

    CPSCON0 = 0b00001100; // 11 = Oscillator is in high range. Charge/discharge current is nominally 18 uA.
    CPSCON1 = 0x00; // Port select
    T1CON = 0b11000001; // CAPOSC T1ON
    T1GCONbits.TMR1GE = 0;
    TMR0 = 0;
    OPTION_REG = 0b00000110; // Prescaler Rate Select bits 110 1:128
    OPTION_REGbits.PS = 7;
    INTCON = 0b01100000; // PEIE, TMR0IE = 1

    TMR1L = 0;
    TMR1H = 0;
    //CPSCON0bits.CPSON = 1;
    INTCONbits.GIE = 1;

    while (1) {
        if (intFlag) { // Every 16.384ms
            intFlag = 0;
            mainFunc();
        }
    }
}
