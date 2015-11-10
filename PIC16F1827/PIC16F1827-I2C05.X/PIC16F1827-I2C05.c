#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

button_t sw_RA0;
button_t sw_RA1;
unsigned char cnt_t1;
char ascii;

void interrupt isr(void);

void interrupt isr(void) {
    interrupt_TXIF();
    if (RCIF) {
        RCIF = 0;
        ascii = RCREG;
        tx_send(ascii);
    }
    if (TMR1IF == 1) {
        TMR1IF = 0;
        cnt_t1++;
        if (cnt_t1 % 16 == 0)LATB0 = ~LATB0;
        button_timer_interrupt(&sw_RA0, !RA0);
        button_timer_interrupt(&sw_RA1, !RA1);
    }
}

void main(void) {
    OSCCON = 0b01110000; // 内部クロックは８ＭＨｚとする
    OPTION_REG = 0b00000000; // デジタルI/Oに内部プルアップ抵抗を使用する
    ANSELA = 0b00000000; // AN0-AN4は使用しない全てデジタルI/Oとする
    ANSELB = 0b00000000; // AN5-AN11は使用しない全てデジタルI/Oとする
    TRISA = 0b00000011; // ピン(RA)は全て出力に割当てる(RA5は入力のみとなる)
    TRISB = 0b00010110; // ピン(RB)はRB4(SCL1)/RB1(SDA1)のみ入力
    WPUB = 0b00010010; // RB1/4は内部プルアップ抵抗を指定する
    PORTA = 0b00000000; // RA出力ピンの初期化(全てLOWにする)
    PORTB = 0b00000000; // RB出力ピンの初期化(全てLOWにする)
    APFCON0bits.RXDTSEL = 1;
    APFCON1bits.TXCKSEL = 1;

    T1CON = 0x21; //Fosc/4, ps:1/4
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;

    I2C_init();
    LCD_init();
    UART_init(PIC16F1827);
    TM_init(0b01100000);

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    uint8_t buf[80];
    ringbuf_init(&tx_buf, buf, sizeof (buf));
#define WAIT 1
#define P 1
    while (1) {
        uint32_t s = 0x87654321;
        EEP_Write(P, 0, (s) >> 24);
        __delay_ms(WAIT);
        EEP_Write(P, 1, (s) >> 16);
        __delay_ms(WAIT);
        EEP_Write(P, 2, (s) >> 8);
        __delay_ms(WAIT);
        EEP_Write(P, 3, (s) >> 0);
        __delay_ms(WAIT);
        uint8_t data_0 = EEP_Read(P, 0);
        __delay_ms(WAIT);
        uint8_t data_1 = EEP_Read(P, 1);
        __delay_ms(WAIT);
        uint8_t data_2 = EEP_Read(P, 2);
        __delay_ms(WAIT);
        uint8_t data_3 = EEP_Read(P, 3);
        __delay_ms(WAIT);
        uint32_t t = (0xFF000000 & (data_0 << 24)) +(0xFF0000 & (data_1 << 16))+ (0xFF00 & (data_2 << 8))+ (0xFF & (data_3 << 0));
        char buf[40];
        sprintf(buf, "%x%x%x%x\n", data_0, data_1, data_2, data_3);
        tx_sends(&buf);
        sprintf(buf, "%x", t >> 16);
        tx_sends(&buf);
        sprintf(buf, "%x\n", t);
        tx_sends(&buf);
        Delay_ms(1000);
    }
}
