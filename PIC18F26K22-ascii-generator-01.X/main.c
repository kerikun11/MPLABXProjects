// PIC18F23K22
// 2014.12.29
//ascii_generator
//とりあえず完成版

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
#define DISPLAY_WIDTH 8
#define LONG_HOLD_LEVEL1 75
#define LONG_HOLD_LEVEL2 200
//リングバッファ構造体

typedef struct ringbuf {
    uint8_t *buf;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
} ringbuf_t;
//使用変数定義
uint8_t cnt_sw;
uint8_t long_hold_flag1;
uint8_t long_hold_flag2;
uint8_t press_flag;
uint8_t printON;
uint8_t dinamic;
ringbuf_t tx_buf;
uint8_t print_char;
//プロトタイプ宣言
void interrupt isr(void);
void intrrupt_RCIF(void);
void intrrupt_TXIF(void);
void intrrupt_TMR0IF(void);
void intrrupt_TMR1IF(void);
void tx_send(uint8_t asciicode);
void ringbuf_init(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize);
void ringbuf_push(ringbuf_t *rb, uint8_t asciicode);
uint8_t ringbuf_pop(ringbuf_t *rb);
uint8_t ringbuf_num(ringbuf_t *rb);
uint8_t encode(uint8_t asciicode);
void display_print(uint8_t column);
void display_matrix(uint8_t column, uint8_t data);
void matrix_column(uint8_t column);
void print(uint8_t value);
void Delay_ms(uint16_t ms);
//パターンを定義
uint8_t pattern[][5] = {
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
    },
    //\b backspace
    {
        0b11101111,
        0b11000111,
        0b10101011,
        0b11101111,
        0b11101111
    },
    //\\r carriage return
    {
        0b11011111,
        0b10001111,
        0b01010111,
        0b11011111,
        0b11000001
    },
    //DEL
    {
        0b00000001,
        0b00000001,
        0b00000001,
        0b00000001,
        0b11111111
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
}
//UART受信割り込み

void intrrupt_RCIF(void) {
    //tx_send(RCREG1);
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
    if (printON) {
        display_print(dinamic);
        dinamic++;
        if (dinamic >= DISPLAY_WIDTH)dinamic = 0;
    }
}
//タイマー１割り込み

void intrrupt_TMR1IF(void) {
    if (PORTCbits.RC4 == 0) {
        if (cnt_sw < LONG_HOLD_LEVEL2 + 1) cnt_sw++;
    } else {
        if (cnt_sw >= LONG_HOLD_LEVEL2)long_hold_flag2 = 1;
        else if (cnt_sw >= LONG_HOLD_LEVEL1 && cnt_sw < LONG_HOLD_LEVEL2)long_hold_flag1 = 1;
        else if (cnt_sw >= 4 && cnt_sw < LONG_HOLD_LEVEL1)press_flag = 1;
        cnt_sw = 0;
    }
}
//引数をtx_bufに格納して順に送信

void tx_send(uint8_t asciicode) {
    ringbuf_push(&tx_buf, asciicode);
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

void ringbuf_push(ringbuf_t *rb, uint8_t asciicode) {
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
    if (asciicode == '\b')return 0x5E + 1;
    if (asciicode == '\r')return 0x5E + 2;
    if (asciicode == 0x7F)return 0x5E + 3;
    else if ((asciicode >= ' ')&(asciicode <= '~')) return asciicode - 0x20;
    else return 0;
}
//左からi列目にchar_bufのデータを表示

void display_print(uint8_t column) {
    if (column == 2)display_matrix(column, ~(pattern[encode(print_char)][0]));
    else if (column == 3)display_matrix(column, ~(pattern[encode(print_char)][1]));
    else if (column == 4)display_matrix(column, ~(pattern[encode(print_char)][2]));
    else if (column == 5)display_matrix(column, ~(pattern[encode(print_char)][3]));
    else if (column == 6)display_matrix(column, ~(pattern[encode(print_char)][4]));
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
    if ((column & 0x01) == 0)LATCbits.LATC0 = 0;
    else LATCbits.LATC0 = 1;
    if ((column & 0x02) == 0)LATCbits.LATC1 = 0;
    else LATCbits.LATC1 = 1;
    if ((column & 0x04) == 0)LATCbits.LATC2 = 0;
    else LATCbits.LATC2 = 1;
    if ((column & 0x08) == 0)LATCbits.LATC3 = 0;
    else LATCbits.LATC3 = 1;
}
//printON

void print(uint8_t value) {
    if (value) {
        printON = 1;
    } else {
        printON = 0;
        display_print(0x08);
    }
}
// Delay

void Delay_ms(uint16_t ms) {
    uint16_t i;
    for (i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}
//メイン関数

int main(void) {
    //pin設定
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    TRISA = 0x00;
    TRISB = 0xFF;
    TRISC = 0x90;

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

    TXSTA1bits.TX9 = 0; // 8-bit
    TXSTA1bits.TXEN = 1; //enable
    TXSTA1bits.SYNC = 0; // Asynchronous mode
    TXSTA1bits.BRGH = 0;
    RCSTA1bits.SPEN = 1; // Serial Port enable
    RCSTA1bits.RX9 = 0; // 8-bit
    RCSTA1bits.CREN = 1; // continuous receive enable
    BAUDCON1bits.BRG16 = 0; // use 8bit SPBRG
    SPBRG1 = 51;
    //IPR1bits.RC1IP = 0; //low priority
    //PIE1bits.RC1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 0;

    uint8_t buf[255];
    ringbuf_init(&tx_buf, buf, sizeof (buf));

    uint8_t i;
    INTCONbits.GIE = 1;
    print(1);
    while (1) {
        if (cnt_sw > LONG_HOLD_LEVEL2)print_char = '\r';
        else if (cnt_sw > LONG_HOLD_LEVEL1)print_char = '\b';
        else print_char = PORTB;

        if (long_hold_flag1) {
            long_hold_flag1 = 0;
            tx_send('\b');
        }
        if (long_hold_flag2) {
            long_hold_flag2 = 0;
            tx_send('\r');
        }
        if (press_flag) {
            press_flag = 0;
            tx_send(PORTB);
        }
    }
    return 0;
}
