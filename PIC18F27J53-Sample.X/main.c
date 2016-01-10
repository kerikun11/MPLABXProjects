/*
PIC18F27J53用サンプルプログラム 
Date:	2016.01.08
Author:	@Ryokeri
 */

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

#include <xc.h>

// __delay_ms()関数を使うために周波数を定義
#define _XTAL_FREQ 48000000

// 自作delay関数

void delay_ms(unsigned int t) {
    while (t--)__delay_ms(1);
}
// OSC Settings

void OSC_init(void) {
    OSCCONbits.IRCF = 7; // 内蔵発振周波数は8MHz
    OSCTUNEbits.PLLEN = 1; // PLL(x6)をEnable
    OSCCONbits.SCS = 0; // クロックソースは内蔵発振or外部クロック
}
// I/O Port Settings

void IO_init(void) {
    // 0が出力、1が入力
    TRISA = 0b00010000; // RA7, RA6, RA5, Vcap, RA3, RA2, RA1,  RA0
    TRISB = 0b00111111; // RB7, RB6, SDA, SCL,  RB3, RB2, RB1,  RB0
    TRISC = 0b10111010; // RXD, TXD, D+,  D-,   Vusb,RC2, T1OSI,T1OSO
    // 0がアナログ、1がデジタル
    ANCON0 = 0b11111111; // x,x,x,AN4(RA5),AN3(RA3),AN2(RA2),AN1(RA1),AN0(RA0)
    ANCON1 = 0b00011111; // VBG,x,x,AN12(RB0),AN11(RC2),AN10(RB1),AN9(RB3),AN8(RB2)
    INTCON2bits.RBPU = 0; // PORTB Pull-up Pnable
}
// prescaler is 0~8

void Timer0_init(unsigned char prescaler) {
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 1; // 8-bit timer
    T0CONbits.T0CS = 0; // use internal-OSC
    if (prescaler == 0) {
        T0CONbits.PSA = 1; // Not use prescaler
    } else {
        T0CONbits.PSA = 0; // use prescaler
        T0CONbits.T0PS = prescaler - 1;
    }
    INTCONbits.T0IE = 1; // Timer 0 Enable
    INTCONbits.TMR0IF = 0; // interrupt Flag clear
    INTCON2bits.TMR0IP = 0; // low priority
    INTCONbits.PEIE = 1;
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
    T1CONbits.RD16 = 0; //Timer1=16bit timer
    T1CONbits.TMR1ON = 1; //enable
    IPR1bits.TMR1IP = 0; // low priority
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
}
// prescaler is 0~3

void Timer3_init(unsigned char prescaler) { // prescaler is 0~3
    T3CONbits.TMR3CS = 0; //Clock = Fosc/4
    T3CONbits.T3OSCEN = 0; // Not Drive Crystal
    T3CONbits.T3CKPS = prescaler;
    T3CONbits.RD163 = 0; //Timer3=16bit timer
    T3CONbits.TMR3ON = 1; //enable
    IPR2bits.TMR3IP = 0; // low priority
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;
    INTCONbits.PEIE = 1;
}
// UART初期化関数

void UART_init(void) {
    TXSTA1bits.TX9 = 0; // 0:8-bit
    TXSTA1bits.TXEN = 1; //1:enable
    TXSTA1bits.SYNC = 0; // 0:Asynchronous mode
    TXSTA1bits.BRGH = 0; // 1:High Speed
    RCSTA1bits.SPEN = 1; // 1:Serial Port enable
    RCSTA1bits.RX9 = 0; // 0:8-bit
    RCSTA1bits.CREN = 1; // 1:continuous receive enable
    BAUDCON1bits.BRG16 = 1; // 1:use 16-bit SPBRG
    SPBRG1 = _XTAL_FREQ / 16 / 115200 - 1;
    SPBRGH1 = (_XTAL_FREQ / 16 / 115200 - 1) >> 8;
    IPR1bits.RCIP = 0;
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
}
// 送信関数

void tx_send(char send_data) {
    while (!PIR1bits.TXIF); // 送信完了まで待つ
    TXREG1 = send_data;
}
// 割り込み関数

void interrupt ISR(void) {
    // UART受信割り込み処理
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        char recv_char = RCREG1; // RCREG1を読み取ることで割り込みフラグはクリアされる
        tx_send(recv_char);
        /* 何らかの処理 */
    }
    // タイマ0割り込み処理
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0; // 割り込みフラグをクリア
        /* 何らかの処理 */
    }
    // タイマ1割り込み処理
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0; // 割り込みフラグをクリア
        TMR1H = 0xC0; // 0.5秒ごとの割り込みにするため
        /* 何らかの処理 */
    }
    // タイマ3割り込み処理
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0; // 割り込みフラグをクリア
        /* 何らかの処理 */
    }
}
// main関数

int main(void) {
    // 初期設定
    OSC_init();
    IO_init();
    Timer0_init(6);
    Timer1_init(0, T1OSC);
    Timer3_init(2);
    UART_init();

    // 割り込み許可
    INTCONbits.GIE = 1;

    while (1) {
        // UART送信
        tx_send('H');
        tx_send('e');
        tx_send('l');
        tx_send('l');
        tx_send('o');
        tx_send('\n');
        delay_ms(1000);
    }
    return 0;
}