// PIC16F1827
// 2015.04.29
// Inverted Pendulum
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
#define ML1 LATA6
#define ML2 LATA7
#define MR1 LATA2
#define MR2 LATA3
#define LEDL LATB4
#define LEDR LATB5
#define PR 20

#define PIC16F1827
#include <My_header.h>

void interrupt isr(void) {
    interrupt_TXIF();
    if (TMR0IF) {
        TMR0IF = 0;
    }
    if (TMR1IF) {
        TMR1IF = 0;
        //LEDL = !LEDL;
        //LEDR = !LEDR;
    }
    if (RCIF) {
        RCIF = 0;
        char ascii = RCREG;
        tx_send(ascii);
    }
}

void PWM_init(void) {
    CCP1CONbits.CCP1M = 12; // PWM, single output
    CCP1CONbits.P1M = 0; // single output
    CCPTMRSbits.C1TSEL = 0;
    CCPR1Lbits.CCPR1L = 0;
    CCP1CONbits.DC1B = 0;

    CCP2CONbits.CCP2M = 12; // PWM, single output
    CCP2CONbits.P2M = 0; // single output
    CCPTMRSbits.C2TSEL = 0;
    CCPR2Lbits.CCPR2L = 0;
    CCP2CONbits.DC2B = 0;

    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 2;
    PR2 = PR - 1;
    T2CONbits.TMR2ON = 1;
}

void PWM_set(uint8_t value) {
    CCP1CONbits.DC1B = 0;
    CCPR1L = value;
    CCP2CONbits.DC2B = 0;
    CCPR2L = value;
}

void drive(uint8_t dir) {
    switch (dir) {
        case 0:// free
            ML1 = 0;
            ML2 = 0;
            MR1 = 0;
            MR2 = 0;
            break;
        case 1:// positive
            ML1 = 1;
            ML2 = 0;
            MR1 = 1;
            MR2 = 0;
            break;
        case 2:// negative
            ML1 = 0;
            ML2 = 1;
            MR1 = 0;
            MR2 = 1;
            break;
        case 3:// brake
            ML1 = 1;
            ML2 = 1;
            MR1 = 1;
            MR2 = 1;
            break;
    }
}

int main(void) {
    OSCCON = 0x70;
    ANSELA = 0x01;
    ANSELB = 0x00;
    TRISA = 0x01;
    TRISB = 0x02;

    UART_init();
    ADC_init(VDD);
    timer0_init(2);
    timer1_init(2);
    PWM_init();

    char buf[40];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    INTCONbits.GIE = 1;

    uint8_t i;

    while (1) {
        uint16_t scan = ADC(0);
        static uint16_t last_scan = 127;
        int16_t sub = scan - last_scan;
        last_scan = scan;
        if (sub > 0) {
            drive(1);
            PWM_set(sub);
            LEDL = 1;
            LEDR = 0;
        } else if (sub < 0) {
            drive(2);
            PWM_set(-sub);
            LEDL = 0;
            LEDR = 1;
        } else {
            drive(0);
            LEDL = 0;
            LEDR = 0;
        }
        __delay_ms(10);
    }
    return 0;
}
