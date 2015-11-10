/* 
 * File:   PIC12F1822-light01.c
 * Author: kerikun11
 *
 * Created on 2014/09/13, 21:22
 */

// PIC12F1822 Configuration Bit Settings
// ソーラーシステム用PWM照明調光器

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

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
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 8000000

unsigned int temp;

unsigned int adc(void) {
    ADCON0 = (ADCON0 & 0b11111110) + 0b00000001;
    __delay_us(20);
    ADCON0 = (ADCON0 & 0b11111101) + 0b00000010;
    while (ADCON0 & 0b00000010);
    return (ADRESH << 8)+ADRESL;
}

int main(int argc, char** argv) {
    OSCCON = 0x70;
    TRISA = 0x01;
    ANSELA = 0x01;
    CCP1CON = 0x0A;
    T2CON = 0x04;
    PR2 = 0b00111111;
    ADCON1 = 0b10000000;
    while (1) {
        CCP1CON = 0b00111100;
        temp = adc();
        CCPR1L = temp >> 4;
    }
    return 0;
}