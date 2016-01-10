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

uint8_t print_char[4][5] = {
    {
        0b11111111,
        0b01111011,
        0b00000001,
        0b01111111,
        0b11111111
    },
    //2
    {
        0b01111011,
        0b00111101,
        0b01011101,
        0b01101101,
        0b01110011
    },
    //3
    {
        0b10111011,
        0b01111101,
        0b01101101,
        0b01101101,
        0b10010011
    },
    //4
    {
        0b11001111,
        0b11010111,
        0b11011011,
        0b00000001,
        0b11011111
    }
};

void send_serial(uint8_t column) {
    uint8_t n;
    for (n = 0; n < 28; n++) {
        LATB0 = 1; //clock
        LATB1 = (~(print_char[3 - ((n / 7) % 4)][column])) >> (7 - (n % 7));
        LATB0 = 0;
    }
}
/*
void interrupt isr(void) {
    if (TMR1IF) {
        TMR1IF = 0;
    }
}
*/
int main(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0x00; //0011,1111
    TRISB = 0x00; //x001,0010
    ANSELA = 0x00; //Use AN0,1,2
    ANSELB = 0x00; //all digital
    WPUA = 0xFF; // RB1/4は内部プルアップ抵抗を指定する
    OPTION_REGbits.nWPUEN = 0;
    //timer1_init(0);
    //INTCONbits.PEIE = 1;
    //INTCONbits.GIE = 1;
    //LATB = 0xFF;
    uint8_t i;
    while (1) {
        for (i = 0; i < 5; i++) {
            LATB = LATB & 0b00000011;
            send_serial(i);
            LATB = (LATB & 0b00000011) + (1 << (i + 2));
            __delay_ms(1);
        }
    }
    return 0;
}
