// PIC18F26K22
//2014.12.25
//縦マイナス:RB0~7
//横プラス:RA2,RA3,RC0~5
//TX:RB7  RX:RB6
//eeprom 1024byte RC2~5
//プットとポップの構造体一般化完成版
//UART送信バッファtx_buf完成版
//aitendo 8x8 dot x2 = 8x16 dot 用
//行:PORTA、列:RB0,1,2,3 ; 4,5,RC0,1 の順4個ずつ2進法出力74HC138AP使用仮定
//display_matrix関数に名前変更
//list[]使用廃止、アスキー配列をそのまま分解する
//return_reset搭載
//eepromに4種類書き込み仮完成、「M0」などの表示付、cnt_sw[]改良
//eepromへのプリセット機能（これの説明）
//pending_charをscroll_charに変更、整理
#include <xc.h>
#include <stdint.h>
// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator multiplied by 4)
#pragma config PRICLKEN = OFF   // Primary clock enable bit (Primary clock can be disabled by software)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)
// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = OFF     // HFINTOSC Fast Start-up (HFINTOSC output and ready status are delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTB5   // ECCP2 B output mux bit (P2B is on RB5)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)
//define
#define _XTAL_FREQ 32000000
#define LENGTH 255
#define CHAR_WIDTH 5 // 5
#define DISPLAY_WIDTH 16 // 16
#define SCROLL_SPEED 6 // 12
#define LONG_HOLD_LEVEL 75 // 75
//リングバッファ構造体

typedef struct ringbuf {
    uint8_t *buf;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
} ringbuf_t;
//使用変数定義
uint8_t dinamic;
uint8_t scrollON;
uint8_t scroll_char[LENGTH];
uint8_t memory_char[4][LENGTH];
uint8_t scroll_char_pointer = 0;
uint16_t scroll_pointer = 0;
uint8_t printON;
uint8_t print_char[2];
uint8_t cnt_t1 = 0;
uint8_t cnt_sw[4];
uint8_t long_hold_flag;
uint8_t return_reset = 1;
ringbuf_t tx_buf;
//プロトタイプ宣言
void interrupt isr(void);
void intrrupt_RCIF(void);
void intrrupt_TXIF(void);
void intrrupt_TMR0IF(void);
void intrrupt_TMR1IF(void);
void intrrupt_TMR3IF(void);
void tx_send(uint8_t asciicode);
void ringbuf_put(ringbuf_t *rb, uint8_t asciicode);
void ringbuf_init(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize);
uint8_t ringbuf_pop(ringbuf_t *rb);
uint8_t ringbuf_num(ringbuf_t *rb);
uint8_t encode(uint8_t asciicode);
void display_scroll(uint8_t column);
void display_print(uint8_t column);
void display_matrix(uint8_t column, uint8_t data);
void matrix_column(uint8_t i);
uint8_t sw(uint8_t i);
void scroll(uint8_t value);
void print(uint8_t value);
//パターンを定義

uint8_t pattern[][CHAR_WIDTH] = {
    //SP
    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111
    },
    //!
    {
        0b11111111,
        0b11111111,
        0b01000001,
        0b11111111,
        0b11111111
    },
    //"
    {
        0b11111111,
        0b11111001,
        0b11111111,
        0b11111001,
        0b11111111
    },
    //#
    {
        0b11010111,
        0b00000001,
        0b11010111,
        0b00000001,
        0b11010111
    },
    //$
    {
        0b10110111,
        0b10101011,
        0b00000001,
        0b10101011,
        0b11011011
    },
    //%
    {
        0b10110001,
        0b11010101,
        0b00101001,
        0b01010111,
        0b00011011
    },
    //&
    {
        0b10010011,
        0b01101101,
        0b01010011,
        0b10111111,
        0b01011111
    },
    //'
    {
        0b11111111,
        0b11111111,
        0b11111001,
        0b11111111,
        0b11111111
    },
    //(
    {
        0b11111111,
        0b11111111,
        0b11000111,
        0b10111011,
        0b01111101
    },
    //)
    {
        0b01111101,
        0b10111011,
        0b11000111,
        0b11111111,
        0b11111111
    },
    //*
    {
        0b10111011,
        0b11010111,
        0b00000001,
        0b11010111,
        0b10111011
    },
    //+
    {
        0b11101111,
        0b11101111,
        0b10000011,
        0b11101111,
        0b11101111
    },
    //,
    {
        0b11111111,
        0b01011111,
        0b10011111,
        0b11111111,
        0b11111111
    },
    //-
    {
        0b11101111,
        0b11101111,
        0b11101111,
        0b11101111,
        0b11101111
    },
    //.
    {
        0b11111111,
        0b00111111,
        0b00111111,
        0b11111111,
        0b11111111
    },
    // /
    {
        0b10111111,
        0b11011111,
        0b11101111,
        0b11110111,
        0b11111011
    },
    //0
    {
        0b10000011,
        0b01011101,
        0b01101101,
        0b01110101,
        0b10000011
    },
    //1
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
    },
    //5
    {
        0b10100001,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10011101
    },
    //6
    {
        0b10000011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10011011
    },
    //7
    {
        0b11111001,
        0b11111101,
        0b00011101,
        0b11101101,
        0b11110001
    },
    //8
    {
        0b10010011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10010011
    },
    //9
    {
        0b10110011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10000011
    },
    //:
    {
        0b11111111,
        0b10010011,
        0b10010011,
        0b11111111,
        0b11111111
    },
    //;
    {
        0b11111111,
        0b01010011,
        0b10010011,
        0b11111111,
        0b11111111
    },
    //<
    {
        0b11101111,
        0b11010111,
        0b10111011,
        0b01111101,
        0b11111111
    },
    //=
    {
        0b10111011,
        0b10111011,
        0b10111011,
        0b10111011,
        0b10111011
    },
    //>
    {
        0b11111111,
        0b01111101,
        0b10111011,
        0b11010111,
        0b11101111
    },
    //?
    {
        0b11110011,
        0b11111101,
        0b01001101,
        0b11101101,
        0b11110011
    },
    //@
    {
        0b10011011,
        0b01101101,
        0b00011101,
        0b01111101,
        0b10000011
    },
    //A
    {
        0b00000011,
        0b11101101,
        0b11101101,
        0b11101101,
        0b00000011
    },
    //B
    {
        0b00000001,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10010011
    },
    //C
    {
        0b10000011,
        0b01111101,
        0b01111101,
        0b01111101,
        0b10111011
    },
    //D
    {
        0b00000001,
        0b01111101,
        0b01111101,
        0b01111101,
        0b10000011
    },
    //E
    {
        0b00000001,
        0b01101101,
        0b01101101,
        0b01101101,
        0b01111101
    },
    //F
    {
        0b00000001,
        0b11101101,
        0b11101101,
        0b11101101,
        0b11111101
    },
    //G
    {
        0b10000011,
        0b01111101,
        0b01011101,
        0b01011101,
        0b10011011
    },
    //H
    {
        0b00000001,
        0b11101111,
        0b11101111,
        0b11101111,
        0b00000001
    },
    //I
    {
        0b11111111,
        0b01111101,
        0b00000001,
        0b01111101,
        0b11111111
    },
    //J
    {
        0b10011111,
        0b01111111,
        0b01111111,
        0b01111111,
        0b10000001
    },
    //K
    {
        0b00000001,
        0b11101111,
        0b11010111,
        0b10111011,
        0b01111101
    },
    //L
    {
        0b00000001,
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111
    },
    //M
    {
        0b00000001,
        0b11111011,
        0b11110111,
        0b11111011,
        0b00000001
    },
    //N
    {
        0b00000001,
        0b11110111,
        0b11101111,
        0b11011111,
        0b00000001
    },
    //O
    {
        0b10000011,
        0b01111101,
        0b01111101,
        0b01111101,
        0b10000011
    },
    //P
    {
        0b00000001,
        0b11101101,
        0b11101101,
        0b11101101,
        0b11110011
    },
    //Q
    {
        0b10000011,
        0b01111101,
        0b01011101,
        0b10000011,
        0b11011111
    },
    //R
    {
        0b00000001,
        0b11101101,
        0b11001101,
        0b10101101,
        0b01110011
    },
    //S
    {
        0b10110011,
        0b01101101,
        0b01101101,
        0b01101101,
        0b10011011,
    },
    //T
    {
        0b11111101,
        0b11111101,
        0b00000001,
        0b11111101,
        0b11111101,
    },
    //U
    {
        0b10000001,
        0b01111111,
        0b01111111,
        0b01111111,
        0b10000001,
    },
    //V
    {
        0b11000001,
        0b10111111,
        0b01111111,
        0b10111111,
        0b11000001,
    },
    //W
    {
        0b10000001,
        0b01111111,
        0b10011111,
        0b01111111,
        0b10000001
    },
    //X
    {
        0b00111001,
        0b11010111,
        0b11101111,
        0b11010111,
        0b00111001
    },
    //Y
    {
        0b11111001,
        0b11110111,
        0b00001111,
        0b11110111,
        0b11111001,
    },
    //Z
    {
        0b00111101,
        0b01011101,
        0b01101101,
        0b01110101,
        0b01111001
    },
    //[
    {
        0b11111111,
        0b11111111,
        0b00000001,
        0b01111101,
        0b11111111
    },
    //back/
    {
        0b11111011,
        0b11110111,
        0b11101111,
        0b11011111,
        0b10111111
    },
    //]
    {
        0b11111111,
        0b11111111,
        0b00000001,
        0b01111101,
        0b11111111
    },
    //^
    {
        0b11110111,
        0b11111011,
        0b11111101,
        0b11111011,
        0b11110111
    },
    //_
    {
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111
    },
    //`
    {
        0b11111111,
        0b11111101,
        0b11111011,
        0b11111111,
        0b11111111
    },
    //a
    {
        0b10111111,
        0b01010111,
        0b01010111,
        0b01010111,
        0b00001111
    },
    //b
    {
        0b00000001,
        0b01101111,
        0b01110111,
        0b01110111,
        0b10001111
    },
    //c
    {
        0b10001111,
        0b01110111,
        0b01110111,
        0b01110111,
        0b10111111
    },
    //d
    {
        0b10001111,
        0b01110111,
        0b01110111,
        0b01101111,
        0b00000001
    },
    //e
    {
        0b10001111,
        0b01010111,
        0b01010111,
        0b01010111,
        0b11001111
    },
    //f
    {
        0b11101111,
        0b00000011,
        0b11101101,
        0b11111101,
        0b11111011
    },
    //g
    {
        0b11100111,
        0b01011011,
        0b01011011,
        0b01011011,
        0b10000011
    },
    //h
    {
        0b00000001,
        0b11101111,
        0b11110111,
        0b11110111,
        0b00001111
    },
    //i
    {
        0b11111111,
        0b01110111,
        0b00000101,
        0b01111111,
        0b11111111
    },
    //j
    {
        0b10111111,
        0b01111111,
        0b01110111,
        0b10000101,
        0b11111111
    },
    //k
    {
        0b00000001,
        0b11011111,
        0b10101111,
        0b01110111,
        0b11111111
    },
    //l
    {
        0b11111111,
        0b01111101,
        0b00000001,
        0b01111111,
        0b11111111
    },
    //m
    {
        0b00000111,
        0b11110111,
        0b11001111,
        0b11110111,
        0b00001111
    },
    //n
    {
        0b00000111,
        0b11101111,
        0b11110111,
        0b11110111,
        0b00001111
    },
    //o
    {
        0b10001111,
        0b01110111,
        0b01110111,
        0b01110111,
        0b10001111
    },
    //p
    {
        0b00000111,
        0b11010111,
        0b11010111,
        0b11010111,
        0b11101111
    },
    //q
    {
        0b11101111,
        0b11010111,
        0b11010111,
        0b11001111,
        0b00000111
    },
    //r
    {
        0b00000111,
        0b11101111,
        0b11110111,
        0b11110111,
        0b11101111
    },
    //s
    {
        0b01101111,
        0b01010111,
        0b01010111,
        0b01010111,
        0b10111111
    },
    //t
    {
        0b11110111,
        0b10000001,
        0b01110111,
        0b01111111,
        0b10111111
    },
    //u
    {
        0b10000111,
        0b01111111,
        0b01111111,
        0b10111111,
        0b00000111
    },
    //v
    {
        0b11000111,
        0b10111111,
        0b01111111,
        0b10111111,
        0b11000111
    },
    //w
    {
        0b10000111,
        0b01111111,
        0b10011111,
        0b01111111,
        0b10000111
    },
    //x
    {
        0b01110111,
        0b10101111,
        0b11011111,
        0b10101111,
        0b01110111
    },
    //y
    {
        0b11100111,
        0b01011111,
        0b01011111,
        0b01011111,
        0b10000111
    },
    //z
    {
        0b01110111,
        0b00110111,
        0b01010111,
        0b01100111,
        0b01110111
    },
    //{
    {
        0b11111111,
        0b11101111,
        0b10010011,
        0b01111101,
        0b11111111
    },
    //|
    {
        0b11111111,
        0b11111111,
        0b00000001,
        0b11111111,
        0b11111111
    },
    //}
    {
        0b11111111,
        0b01111101,
        0b10010011,
        0b11101111,
        0b11111111
    },
    //~
    {
        0b11111011,
        0b11111101,
        0b11111011,
        0b11110111,
        0b11111011
    }
};
//割り込み関数

void interrupt isr(void) {
    //シリアル受信割り込み
    if (RC1IF == 1) {
        RC1IF = 0;
        intrrupt_RCIF();
    }
    //シリアル送信完了割り込み
    if (TX1IF & TX1IE) {
        intrrupt_TXIF();
    }
    //タイマ０割り込み
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        intrrupt_TMR0IF();
    }
    //タイマ１割り込み
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
        intrrupt_TMR1IF();
    }
    //タイマ３割り込み
    if (PIR2bits.TMR3IF == 1) {
        PIR2bits.TMR3IF = 0;
        intrrupt_TMR3IF();
    }
}
//UART受信割り込み

void intrrupt_RCIF(void) {
    uint8_t i;
    uint8_t ascii = RCREG1;
    tx_send(ascii);
    if (ascii == '\b') {// back space
        if (scroll_char_pointer > 0) {
            scroll_char_pointer--;
        }
    } else if (ascii == 0x7F) {// delete
        scroll_char_pointer = 0;
        scroll(0);
    } else if (ascii == '\r') {// carriage return
        if (scroll_char_pointer) {
            tx_send('\n');
            return_reset = 1;
        }
        scroll_pointer = 0;
        scroll(1);
    } else if ((ascii >= 0x20)&(ascii <= 0x7E)) {// character
        if (return_reset == 1) {
            return_reset = 0;
            scroll_char_pointer = 0;
        }
        scroll_char[scroll_char_pointer] = ascii;
        scroll_char_pointer++;
        scroll(1);
    }
}
//UART送信完了割り込み

void intrrupt_TXIF(void) {
    if (ringbuf_num(&tx_buf) > 0) {
        TXREG1 = ringbuf_pop(&tx_buf);
    } else {
        PIE1bits.TX1IE = 0;
    }
}
//タイマー０割り込み

void intrrupt_TMR0IF(void) {
    if (scrollON) {
        display_scroll(dinamic);
        dinamic++;
        if (dinamic >= DISPLAY_WIDTH)dinamic = 0;
    }
    if (printON) {
        display_print(dinamic);
        dinamic++;
        if (dinamic >= DISPLAY_WIDTH)dinamic = 0;
    }
}
//タイマー１割り込み

void intrrupt_TMR1IF(void) {
    cnt_t1++;
    if (cnt_t1 >= SCROLL_SPEED) {
        cnt_t1 = 0;
        //displayスクロール＆ループ
        if (scrollON) {
            scroll_pointer++;
            if (scroll_pointer > scroll_char_pointer * 6 + DISPLAY_WIDTH) {
                scroll_pointer = 0;
            }
        }
    }
}
//タイマー３割り込み

void intrrupt_TMR3IF(void) {
    uint8_t i;
    for (i = 0; i < 4; i++) {
        if (sw(i)) {
            if (cnt_sw[i] < LONG_HOLD_LEVEL + 1) cnt_sw[i]++;
            //swを長押ししたらlong_hold_flagが立ち、回収してもボタンを離して再び押されるまでは立たない。
            if (cnt_sw[i] == LONG_HOLD_LEVEL)long_hold_flag |= (1 << i);
        } else cnt_sw[i] = 0;
    }
}
//引数をtx_bufに格納して順に送信

void tx_send(uint8_t asciicode) {
    ringbuf_put(&tx_buf, asciicode);
    PIE1bits.TX1IE = 1;
}
//バッファ初期化

void ringbuf_init(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize) {
    rb->buf = internal_buf;
    rb->size = bufsize;
    rb->head = 0;
    rb->tail = 0;
}
//文字情報をbuf_char[]にプット。headは次にプットするアドレスを示す。

void ringbuf_put(ringbuf_t *rb, uint8_t asciicode) {
    rb->buf[rb->head] = asciicode;
    rb->head++;
    if (rb->head >= rb->size) {
        rb->head = 0;
    }
}
//文字情報をbuf_char[]からポップ。tailは次にポップするアドレスを示す。

uint8_t ringbuf_pop(ringbuf_t *rb) {
    uint8_t ret = rb->buf[rb->tail];
    rb->tail++;
    if (rb->tail >= rb->size) {
        rb->tail = 0;
    }
    return ret;
}
//buf_char[]に入っている要素数を返す

uint8_t ringbuf_num(ringbuf_t *rb) {
    if (rb->head >= rb->tail) {
        return (rb->head - rb->tail);
    } else {
        return (rb->size + rb->head - rb->tail);
    }
}
//アスキーコードを解析して数字を返す。

uint8_t encode(uint8_t asciicode) {
    if ((asciicode >= 0x20)&(asciicode <= 0x80)) return asciicode - 0x20;
    else return 0;
}
//左からi列目にchar_bufのデータをdisplaylistに応じてスクロール表示

void display_scroll(uint8_t column) {
    if (scroll_pointer + column < DISPLAY_WIDTH || scroll_pointer + column >= DISPLAY_WIDTH + scroll_char_pointer * 6 || (scroll_pointer + column - DISPLAY_WIDTH) % 6 == 5)display_matrix(column, 0x00);
    else display_matrix(column, ~(pattern[encode(scroll_char[(scroll_pointer + column - DISPLAY_WIDTH) / 6])][(scroll_pointer + column - DISPLAY_WIDTH) % 6]));
}
//左からi列目にchar_bufのデータを表示

void display_print(uint8_t column) {
    if (column == 2)display_matrix(column, ~(pattern[encode(print_char[0])][0]));
    else if (column == 3)display_matrix(column, ~(pattern[encode(print_char[0])][1]));
    else if (column == 4)display_matrix(column, ~(pattern[encode(print_char[0])][2]));
    else if (column == 5)display_matrix(column, ~(pattern[encode(print_char[0])][3]));
    else if (column == 6)display_matrix(column, ~(pattern[encode(print_char[0])][4]));
    else if (column == 9)display_matrix(column, ~(pattern[encode(print_char[1])][0]));
    else if (column == 10)display_matrix(column, ~(pattern[encode(print_char[1])][1]));
    else if (column == 11)display_matrix(column, ~(pattern[encode(print_char[1])][2]));
    else if (column == 12)display_matrix(column, ~(pattern[encode(print_char[1])][3]));
    else if (column == 13)display_matrix(column, ~(pattern[encode(print_char[1])][4]));
    else display_matrix(column, 0x00);
}
//ドットマトリクスをダイナミック点灯

void display_matrix(uint8_t column, uint8_t data) {
    LATA = 0x00;
    matrix_column(column);
    LATA = data;
}
//ドットマトリクスの左からi列に電源供給。i>=16の時すべて消灯

void matrix_column(uint8_t column) {
    if ((column & 0x01) == 0)LATBbits.LATB0 = 0;
    else LATBbits.LATB0 = 1;
    if ((column & 0x02) == 0)LATBbits.LATB1 = 0;
    else LATBbits.LATB1 = 1;
    if ((column & 0x04) == 0)LATBbits.LATB2 = 0;
    else LATBbits.LATB2 = 1;
    if ((column & 0x08) == 0)LATBbits.LATB3 = 0;
    else LATBbits.LATB3 = 1;
    if ((column & 0x01) == 0)LATBbits.LATB4 = 0;
    else LATBbits.LATB4 = 1;
    if ((column & 0x02) == 0)LATBbits.LATB5 = 0;
    else LATBbits.LATB5 = 1;
    if ((column & 0x04) == 0)LATCbits.LATC0 = 0;
    else LATCbits.LATC0 = 1;
    if ((column & 0x08) != 0)LATCbits.LATC1 = 0;
    else LATCbits.LATC1 = 1;
    if ((column & 0x10) != 0) {
        LATBbits.LATB3 = 1;
        LATCbits.LATC1 = 1;
    }
}
//SW(i)が押されていたら1を返す

uint8_t sw(uint8_t i) {
    switch (i) {
        case 0:
            return !PORTCbits.RC5;
        case 1:
            return !PORTCbits.RC4;
        case 2:
            return !PORTCbits.RC3;
        case 3:
            return !PORTCbits.RC2;
    }
    return 2;
}
//scrollON

void scroll(uint8_t value) {
    if (value) {
        scrollON = 1;
    } else {
        scrollON = 0;
        display_scroll(0x10);
    }
}
//printON

void print(uint8_t value) {
    if (value) {
        printON = 1;
    } else {
        printON = 0;
        display_print(0x10);
    }
}
//メイン関数

int main(void) {
    //pin設定
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0xBC;

    OSCCONbits.IRCF = 6; // 6 => 8MHz
    OSCCON2bits.PLLRDY = 1;
    OSCTUNEbits.PLLEN = 1; // clock x 4

    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 1; // 8-bit timer
    T0CONbits.T0CS = 0; // use intOSC
    T0CONbits.PSA = 0; // use prescaler
    T0CONbits.T0PS = 2; // 1 => 1:4
    INTCONbits.T0IE = 1;
    INTCON2bits.TMR0IP = 0; // low priority

    T1CONbits.TMR1CS = 0; //Clock = Fosc/4
    T1CONbits.T1CKPS = 0; //PreScaler is 1:1
    T1CONbits.T1RD16 = 1; //Timer1=16bit timer
    T1CONbits.TMR1ON = 1; //enable
    IPR1bits.TMR1IP = 0; //low priority
    PIE1bits.TMR1IE = 1;

    T3CONbits.TMR3CS = 0; //Clock = Fosc/4
    T3CONbits.T3CKPS = 0; //PreScaler is 1:1
    T3CONbits.T3RD16 = 1; //Timer1=16bit timer
    T3CONbits.TMR3ON = 1; //enable
    IPR2bits.TMR3IP = 0; //low priority
    PIE2bits.TMR3IE = 1;

    TXSTA1bits.TX9 = 0; // 8-bit
    TXSTA1bits.TXEN = 1; //enable
    TXSTA1bits.SYNC = 0; // Asynchronous mode
    TXSTA1bits.BRGH = 0;
    RCSTA1bits.SPEN = 1; // Serial Port enable
    RCSTA1bits.RX9 = 0; // 8-bit
    RCSTA1bits.CREN = 1; // continuous receive enable
    BAUDCON1bits.BRG16 = 0; // use 8bit SPBRG
    SPBRG1 = 51;
    IPR1bits.RC1IP = 0; //low priority
    PIE1bits.RC1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 0;

    uint8_t buf[LENGTH];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    uint8_t i;
    uint8_t j;
    uint8_t preset_memory_char_0[] = "This is an LED bulletin board.";
    uint8_t preset_memory_char_1[] = "4 sentences can be memorized.";
    uint8_t preset_memory_char_2[] = "When a button is pressed, the sentence which memorized by the button is shown.";
    uint8_t preset_memory_char_3[] = "When a button is pressed for a long time, a sentence is memorized.";
    uint8_t preset_char[] = "Hello World!";
    for (i = 0; preset_char[i]; i++) {
        scroll_char[i] = preset_char[i];
        scroll_char_pointer++;
    }
    for (i = 0; preset_memory_char_0[i]; i++) {
        memory_char[0][i] = preset_memory_char_0[i];
    }
    memory_char[0][i] = '\0';
    for (i = 0; preset_memory_char_1[i]; i++) {
        memory_char[1][i] = preset_memory_char_1[i];
    }
    memory_char[1][i] = '\0';
    for (i = 0; preset_memory_char_2[i]; i++) {
        memory_char[2][i] = preset_memory_char_2[i];
    }
    memory_char[2][i] = '\0';
    for (i = 0; preset_memory_char_3[i]; i++) {
        memory_char[3][i] = preset_memory_char_3[i];
    }
    memory_char[3][i] = '\0';

    scroll_pointer = 0;
    scroll(1);

    INTCONbits.GIE = 1;

    while (1) {
        uint16_t sw_flag = 0;
        for (j = 0; j < 4; j++) {
            if (sw(j))sw_flag = 1;
            if ((long_hold_flag)&(1 << j)) {
                long_hold_flag &= ~(1 << j);
                scroll(0);
                for (i = 0; i < scroll_char_pointer; i++) {
                    memory_char[j][i] = scroll_char[i];
                }
                memory_char[j][i]='\0';
                print_char[0] = 'M';
                print_char[1] = '0' + j + 1;
                print(1);
            }
            if (cnt_sw[j] > 1 && cnt_sw[j] < LONG_HOLD_LEVEL && sw(j) == 0) {
                cnt_sw[j] = 0;
                scroll_char_pointer = 0;
                for (i = 0; memory_char[j][i]; i++) {
                    scroll_char[i] = memory_char[j][i];
                    scroll_char_pointer++;
                }
                scroll_pointer = 0;
                return_reset = 1;
                scroll(1);
            }
        }
        if (sw_flag == 0 && printON == 1) {
            print(0);
            scroll(1);
        }
    }
    return 0;
}
