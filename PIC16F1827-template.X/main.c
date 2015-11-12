// PIC16F1827

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

#include <xc.h>
#include <stdint.h>
#include <My_PIC.h>
#include <My_UART.h>
#include <My_I2C.h>

void interrupt isr(void) {
    UART_ISR();
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
    }
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
    }
}

void main_init(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0x37; //0011,0111
    TRISB = 0x5B; //0101,1011
    ANSELA = 0x00; //
    ANSELB = 0x00; //
    WPUA = TRISA;
    WPUB = TRISB;
    OPTION_REGbits.nWPUEN = 0;

    I2C_init();
    UART_init();
    
}

int main(void) {
    main_init();

    INTCONbits.GIE = 1;

    while (1) {
        UART_task();
    }

    return 0;
}
