// PIC16F1827 Configuration Bit Settings
// 2014.12.12
// RA 0,1,2:adc, RB 0,3,4:output, RA 3,4,5:sw, RB5,RA6,7:LED
// UARTテスト用
// ChargeStation Ver.3　出力3つ用
// 点滅LED完成版
// UART scrollboardへ出力のみ→pinアサインそのまま

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
#define CUT_current 50          // 単位は[mA]
#define CUT_time 6              // 単位は[s]

typedef struct ringbuf {
    uint8_t *buf;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
} ringbuf_t;

uint16_t v[3];
uint16_t cut[3];
uint8_t cnt[3];
uint8_t cntf[3];
uint16_t cnt0;
ringbuf_t tx_buf;

void interrupt isr(void);
void display(uint8_t i);
void lchika(void);
void tx_send(uint8_t asciicode);
void ringbuf_put(ringbuf_t *rb, uint8_t asciicode);
uint8_t ringbuf_pop(ringbuf_t *rb);
uint8_t ringbuf_num(ringbuf_t *rb);
void init_ringbuf(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize);
uint16_t adc(uint8_t ch);
void OUT(uint8_t b, uint8_t value);
void LED(uint8_t b, uint8_t value);
uint8_t SW(uint8_t b);
void main_init(void);
void delay(uint16_t ms);

void interrupt isr(void) {
    uint8_t i;
    if (PIR1bits.RCIF == 1) {
        PIR1bits.RCIF = 0;
        if (RCREG == 'E') {
            tx_send('C');
            tx_send('h');
            tx_send('a');
            tx_send('r');
            tx_send('g');
            tx_send('e');
            tx_send(' ');
            tx_send('S');
            tx_send('t');
            tx_send('a');
            tx_send('t');
            tx_send('i');
            tx_send('o');
            tx_send('n');
            tx_send(' ');
            tx_send('3');
            tx_send(0x0D);
        }
    }
    if (PIR1bits.TXIF & PIE1bits.TXIE) {
        if (ringbuf_num(&tx_buf)) {
            TXREG = ringbuf_pop(&tx_buf);
        } else {
            PIE1bits.TXIE = 0;
        }
    }
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
        for (i = 0; i < 3; i++) {
            v[i] = 2 * adc(2-i) * 3 / 4;

            if (v[i] < CUT_current) { //もし一定電流を下回ったらカウントアップスタート
                cut[i]++;
                if (cut[i] >= 8 * CUT_time) { //一定時間たったら、出力シャットアウト
                    OUT(i, 0);
                }
            } else { //経過時間カウントリセット
                cut[i] = 0;
            }
        }
    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        cnt0++;
        if (cnt0 == 400) {
            cnt0 = 0;
            lchika();
        }
    }
}

void lchika(void) {
    uint8_t i;
    for (i = 0; i < 3; i++) {
        cnt[i]++;
        //奇数ならLEDは消灯
        if (cnt[i] % 2 == 1) {
            LED(i, 0);
        } else {//偶数のとき
            if (cnt[i] / 2 <= v[i] / 100) {//LED点滅回数のほうが電流より少ない間LED点灯
                LED(i, 1);
                cntf[i] = 0; //フラグリセット
            } else {//LEDの点滅回数のほうが電流より多くなったときフラグ加算
                cntf[i]++;
                LED(i, 0);
                if (cntf[i] >= 2) {//フラグが2になったら、元に戻る
                    cnt[i] = 0;
                }
            }
        }
    }
}

void display(uint8_t i) {
    tx_send((v[i] % 10000) / 1000 + '0');
    tx_send('.');
    tx_send((v[i] % 1000) / 100 + '0');
    tx_send((v[i] % 100) / 10 + '0');
    tx_send('A');
    tx_send(0x0D);
}

void tx_send(uint8_t asciicode) {
    ringbuf_put(&tx_buf, asciicode);
    PIE1bits.TXIE = 1;
}

void ringbuf_put(ringbuf_t *rb, uint8_t asciicode) {
    rb->buf[rb->head] = asciicode;
    rb->head++;
    if (rb->head >= rb->size) {
        rb->head = 0;
    }
}

uint8_t ringbuf_pop(ringbuf_t * rb) {
    uint8_t ret = rb->buf[rb->tail];
    rb->tail++;
    if (rb->tail >= rb->size) {
        rb->tail = 0;
    }
    return ret;
}

uint8_t ringbuf_num(ringbuf_t * rb) {
    if (rb->head >= rb->tail) {
        return (rb->head - rb->tail);
    } else {
        return (rb->size + rb->head - rb->tail);
    }
}

void init_ringbuf(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize) {
    rb->buf = internal_buf;
    rb->size = bufsize;
    rb->head = 0;
    rb->tail = 0;
}

uint16_t adc(uint8_t ch) {
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 2 - ch;
    __delay_us(20);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

void OUT(uint8_t b, uint8_t value) {
    switch (b) {
        case 0:
            if (value) {
                LATB0 = 0;
            } else {
                LATB0 = 1;
            }
            break;
        case 1:
            if (value) {
                LATB3 = 0;
            } else {
                LATB3 = 1;
            }
            break;
        case 2:
            if (value) {
                LATB4 = 0;
            } else {
                LATB4 = 1;
            }
            break;
        default:
            break;
    }
}

void LED(uint8_t b, uint8_t value) {
    switch (b) {
        case 0:
            LATB5 = value;
            break;
        case 1:
            LATA6 = value;
            break;
        case 2:
            LATA7 = value;
            break;
        default:
            break;
    }
}

uint8_t SW(uint8_t b) {
    uint8_t temp;
    temp = PORTA;
    if (temp & (0x01 << (2 - b + 3))) {
        return 0;
    } else {
        return 1;
    }
}

void delay(uint16_t ms) {
    uint16_t i;
    for (i = 0; i < ms; i++)__delay_ms(1);
}

void main_init(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0x3F; //0011,1111
    TRISB = 0x02; //xx00,0010
    ANSELA = 0x07; //Use AN0,1,2
    ANSELB = 0x00; //all digital
    ADCON1 = 0x93; //Use FVR
    FVRCON = 0x83; //4.096V

    SPEN = 1;
    RCSTA = 0x90;
    BRG16 = 0;
    SPBRGH = 0;
    SPBRGL = 207;
    TXSTA = 0x24;
    PIE1bits.RCIE = 1;

    OPTION_REG = 0b10010011; //ps:1/16
    INTCONbits.TMR0IE = 1;

    T1CON = 0x21; //Fosc/4, ps:1/4
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

int main(void) {
    main_init();

    OUT(0, 1);
    OUT(1, 1);
    OUT(2, 1);
    LED(0, 1);
    LED(1, 1);
    LED(2, 1);

    uint8_t ringbuf[50];
    init_ringbuf(&tx_buf, ringbuf, sizeof (ringbuf));

    uint8_t i;

    while (1) {
        for (i = 0; i < 3; i++) {
            if (SW(i)) {
                OUT(i, 1);
                LED(i, 1);
                display(i);
                cut[i] = 0;
            }
        }
    }
    return 0;
}
