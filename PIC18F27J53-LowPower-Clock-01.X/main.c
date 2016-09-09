/*
 * PIC18F27J53用サンプルプログラム 
 * Date:	2016.01.08
 * Author:	@Ryokeri
 */

// PIC18F27J53 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 2       // PLL Prescaler Selection (Divide by 2 (8 MHz oscillator input))
#pragma config CFGPLLEN = OFF   // PLL Enable Configuration Bit (PLL Disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset (Disabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = INTOSC     // Oscillator (INTOSC)
#pragma config SOSCSEL = HIGH    // T1OSC/SOSC Power Selection Bits (Low Power T1OSC/SOSC circuit selected)
#pragma config CLKOEC = OFF     // EC Clock Out Enable Bit  (CLKO output disabled on the RA6 pin)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 1024     // Watchdog Postscaler (1:1024)

// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF// DSWDT Clock Select (DSWDT uses T1OSC/T1CKI)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Disabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config ADCSEL = BIT12   // ADC 10 or 12 Bit Select (12 - Bit ADC Enabled)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_127  // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 127)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region  (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<6:0>/WPEND region ignored)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select bit (valid when WPDIS = 0) (Pages WPFP<6:0> through Configuration Words erase/write protected)
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock bit (System clock at 48 MHz USB CLKEN divide-by is set to 8)

#include <xc.h>
#include <stdint.h>

// __delay_ms()関数を使うために周波数を定義
#define _XTAL_FREQ 8000000

// 割り込み関数

void interrupt ISR(void) {
    // タイマ1割り込み処理
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0; // 割り込みフラグをクリア
        TMR1H = 0xC0; // 0.5秒ごとの割り込みにするため
        /* 何らかの処理 */
        LATC6 = !LATC6;
    }
}

uint8_t pattern[12] = {
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00100111, //7
    0b01111111, //8
    0b01101111, //9
    0b00000011, //:
    0b00000000, //
};

#define SEG_A   LATB3
#define SEG_B   LATB5
#define SEG_C   LATA5
#define SEG_D   LATB2
#define SEG_E   LATB1
#define SEG_F   LATC2
#define SEG_G   LATB4
#define SEG_H   LATB0
#define SEG_0   LATA7
#define SEG_1   LATA6
#define SEG_2   LATA2
#define SEG_3   LATA1
#define SEG_4   LATA3

void print_pattern(uint8_t col, uint8_t num) {
    uint8_t pat = pattern[num];
    switch (col) {
        case 0:
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            SEG_A = ~pat >> 0;
            SEG_B = ~pat >> 1;
            SEG_C = ~pat >> 2;
            SEG_D = ~pat >> 3;
            SEG_E = ~pat >> 4;
            SEG_F = ~pat >> 5;
            SEG_G = ~pat >> 6;
            SEG_H = ~pat >> 7;
            SEG_0 = 1;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            break;
        case 1:
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            SEG_A = ~pat >> 0;
            SEG_B = ~pat >> 1;
            SEG_C = ~pat >> 2;
            SEG_D = ~pat >> 3;
            SEG_E = ~pat >> 4;
            SEG_F = ~pat >> 5;
            SEG_G = ~pat >> 6;
            SEG_H = ~pat >> 7;
            SEG_0 = 0;
            SEG_1 = 1;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            break;
        case 2:
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            SEG_A = ~pat >> 0;
            SEG_B = ~pat >> 1;
            SEG_C = ~pat >> 2;
            SEG_D = ~pat >> 3;
            SEG_E = ~pat >> 4;
            SEG_F = ~pat >> 5;
            SEG_G = ~pat >> 6;
            SEG_H = ~pat >> 7;
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 1;
            SEG_3 = 0;
            SEG_4 = 0;
            break;
        case 3:
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            SEG_A = ~pat >> 0;
            SEG_B = ~pat >> 1;
            SEG_C = ~pat >> 2;
            SEG_D = ~pat >> 3;
            SEG_E = ~pat >> 4;
            SEG_F = ~pat >> 5;
            SEG_G = ~pat >> 6;
            SEG_H = ~pat >> 7;
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 1;
            SEG_4 = 0;
            break;
        case 4:
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 0;
            SEG_A = ~pat >> 0;
            SEG_B = ~pat >> 1;
            SEG_C = ~pat >> 2;
            SEG_D = ~pat >> 3;
            SEG_E = ~pat >> 4;
            SEG_F = ~pat >> 5;
            SEG_G = ~pat >> 6;
            SEG_H = ~pat >> 7;
            SEG_0 = 0;
            SEG_1 = 0;
            SEG_2 = 0;
            SEG_3 = 0;
            SEG_4 = 1;
            break;
    }
}

#define FOSC_4 0 // Fosc/4
#define T1OSC  2 // Timer 1 OSC
// prescaler is 0~3
// clock_select is FOSC_4(Fosc/4) or T1OSC(32.768kHz)

void Timer1_init(unsigned char prescaler, unsigned char clock_select) {
    T1CONbits.TMR1CS = clock_select;
    if (clock_select == T1OSC) T1CONbits.T1OSCEN = 1; // Drive Crystal
    else T1CONbits.T1OSCEN = 0;
    T1CONbits.T1CKPS = prescaler;
    T1CONbits.nT1SYNC = 1; // No Sync
    T1CONbits.RD16 = 0; // Timer1=16bit timer
    T1CONbits.TMR1ON = 1; //enable
    IPR1bits.TMR1IP = 0; // low priority
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
}

void RTCC_init() {
    RTCCFGbits.RTCWREN = 1;
    if (RTCCFGbits.RTCWREN != 1) {
        EECON2 = 0x55;
        EECON2 = 0xAA;
        RTCCFGbits.RTCWREN = 1;
    }
    RTCCFGbits.RTCEN = 1;
    RTCCFGbits.RTCOE = 0;
    PADCFG1bits.RTSECSEL0 = 1;
    PADCFG1bits.RTSECSEL1 = 1;
    RTCCAL = 0x00;
    T1CONbits.T1OSCEN = 1;
}

int main(void) {
    // 初期設定
    OSCCONbits.SCS = 1;

    // 0が出力、1が入力
    TRISA = 0b00010001; // RA7, RA6, RA5, Vcap, RA3, RA2, RA1,  RA0
    TRISB = 0b00000000; // RB7, RB6, SDA, SCL,  RB3, RB2, RB1,  RB0
    TRISC = 0b10111010; // RXD, TXD, D+,  D-,   Vusb,RC2, T1OSI,T1OSO
    // 0がアナログ、1がデジタル
    ANCON0 = 0b11111111; // x,x,x,AN4(RA5),AN3(RA3),AN2(RA2),AN1(RA1),AN0(RA0)
    ANCON1 = 0b00011111; // VBG,x,x,AN12(RB0),AN11(RC2),AN10(RB1),AN9(RB3),AN8(RB2)

    
    INTCONbits.GIE = 1;

    while (1) {
        print_pattern(0, 0);
        __delay_ms(1);
        print_pattern(1, 1);
        __delay_ms(1);
        print_pattern(2, 2);
        __delay_ms(1);
        print_pattern(3, 3);
        __delay_ms(1);
        print_pattern(4, 10);
        __delay_ms(1);
    }
    return 0;
}