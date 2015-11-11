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

void interrupt isr(void);

void interrupt isr(void) {
    interrupt_TXIF();
    if (RCIF) {
        RCIF = 0;
        tx_send(RCREG);
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

    uint8_t buf[70];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    while (1) {
        if (sw_RA0.flag.press) {
            sw_RA0.flag.press = 0;
            LCD_Clear();
            LCD_SetCursor(0, 0);
            LCD_Puts("Sassor");
            Delay_ms(5000);
        }
        //tx_sends("Thermo Meter\n");
        int16_t temp = TM_Read();
        uint8_t tmbuf[50];
        sprintf(tmbuf, "%c%d.%02d", '-' * ((temp >> 15)&1) + '+' * (1 - ((temp >> 15)&1)), abs(temp) / 256, abs(temp) / 64 * 100 / 4 % 100);
        LCD_Clear();
        LCD_SetCursor(0, 1);
        LCD_Puts(&tmbuf);
        tx_sends(&tmbuf);
        tx_send('\r');
        Delay_ms(1000);
    }
}
