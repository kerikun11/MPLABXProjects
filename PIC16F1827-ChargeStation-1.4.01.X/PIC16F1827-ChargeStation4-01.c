// PIC16F1827 Configuration Bit Settings
// 2014.12.12
// RA 0,1,2:adc, RB 0,3,6:output, RA 3,4,5:sw, RB5,RA6,7:LED
// ChargeStation Ver.3　出力3つ用
// 点滅LED完成版
// I2C小型液晶へ出力
// 積算機能追加
// 安定動作完成版

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
#include <My_header_16F.h>

#define CUT_current 50    // 単位は[mA]
#define CUT_time 6       // 単位は[s]

uint16_t v[3];
uint16_t s[3];
uint16_t sp[3];
uint32_t ss[3];
uint16_t cut[3];
uint8_t cnt[3];
uint8_t cntf[3];
uint16_t cnt0;
uint16_t cnt1s;
uint8_t print_port;
uint8_t print_content;
ringbuf_t tx_buf;
button_t sw_RA3;
button_t sw_RA4;
button_t sw_RA5;

void interrupt isr(void);
void display(uint8_t i, uint8_t co);
void lchika(void);
void tx_send(uint8_t asciicode);
void OUT(uint8_t b, uint8_t value);
void LED(uint8_t b, uint8_t value);
uint8_t flag_read(uint8_t port, uint8_t bit_and);
void flag_clear(uint8_t port, uint8_t bit_and);
void main_init(void);

void interrupt isr(void) {
    uint8_t i;
    if (PIR1bits.RCIF == 1) {
        PIR1bits.RCIF = 0;
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
        button_timer_interrupt(&sw_RA3, !RA3);
        button_timer_interrupt(&sw_RA4, !RA4);
        button_timer_interrupt(&sw_RA5, !RA5);

        for (i = 0; i < 3; i++) {
            v[i] = 2 * adc(2 - i) * 3 / 4;

            if (v[i] < CUT_current) { //もし一定電流を下回ったらカウントアップスタート
                cut[i]++;
                if (cut[i] >= 30 * CUT_time) { //一定時間たったら、出力シャットアウト
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
            display(print_port, print_content);
        }
        cnt1s++;
        // 1秒数える(1953)
        if (cnt1s == 1953) {
            cnt1s = 0;
            for (i = 0; i < 3; i++) {
                ss[i] += v[i];
                s[i] = ss[i] / 3600;
                if (s[i] != sp[i]) {
                    EEP_Write(i, 0, (ss[i]) >> 24);
                    __delay_ms(1);
                    EEP_Write(i, 1, (ss[i]) >> 16);
                    __delay_ms(1);
                    EEP_Write(i, 2, (ss[i]) >> 8);
                    __delay_ms(1);
                    EEP_Write(i, 3, (ss[i]) >> 0);
                    __delay_ms(1);
                    sp[i] = s[i];
                }
            }
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

void display(uint8_t i, uint8_t co) {
    LCD_Clear();
    LCD_SetCursor(0, 0);
    switch (co) {
        case 0:
            LCD_SetCursor(0, 0);
            LCD_Puts("Charge");
            LCD_SetCursor(0, 1);
            LCD_Puts("Station");
            break;
        case 1:
            switch (i) {
                case 0:
                    LCD_Puts("Right");
                    break;
                case 1:
                    LCD_Puts("Center");
                    break;
                case 2:
                    LCD_Puts("Left");
                    break;
            }
            LCD_SetCursor(0, 1);
            LCD_Putc((v[i] % 10000) / 1000 + '0');
            LCD_Putc('.');
            LCD_Putc((v[i] % 1000) / 100 + '0');
            LCD_Putc((v[i] % 100) / 10 + '0');
            LCD_Putc((v[i] % 10) / 1 + '0');
            LCD_Putc('A');
            break;
        case 2:
            switch (i) {
                case 0:
                    LCD_Puts("Right");
                    break;
                case 1:
                    LCD_Puts("Center");
                    break;
                case 2:
                    LCD_Puts("Left");
                    break;
            }
            LCD_SetCursor(0, 1);
            LCD_Putc((s[i] % 100000) / 10000 + '0');
            LCD_Putc((s[i] % 10000) / 1000 + '0');
            LCD_Putc((s[i] % 1000) / 100 + '0');
            LCD_Putc((s[i] % 100) / 10 + '0');
            LCD_Putc((s[i] % 10) / 1 + '0');
            LCD_Puts("mAh");
            break;
        case 3:
            switch (i) {
                case 0:
                    LCD_Puts("Right");
                    break;
                case 1:
                    LCD_Puts("Center");
                    break;
                case 2:
                    LCD_Puts("Left");
                    break;
            }
            LCD_SetCursor(0, 1);
            LCD_Puts("Reseted");
            break;

    }
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
                LATB6 = 0;
            } else {
                LATB6 = 1;
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

uint8_t flag_read(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 2:
            return (sw_RA3.flags) & bit_and;
        case 1:
            return (sw_RA4.flags) & bit_and;
        case 0:
            return (sw_RA5.flags) & bit_and;
        default:
            return 0;
    }
}

void flag_clear(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 2:
            sw_RA3.flags &= bit_and;
            break;
        case 1:
            sw_RA4.flags &= bit_and;
            break;
        case 0:
            sw_RA5.flags &= bit_and;
            break;
        default:
            break;
    }
}

void main_init(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0x3F; //0011,1111
    TRISB = 0x12; //x001,0010
    ANSELA = 0x07; //Use AN0,1,2
    ANSELB = 0x00; //all digital
    WPUB = 0b00010010; // RB1/4は内部プルアップ抵抗を指定する
    OPTION_REGbits.nWPUEN = 0;

    adc_init(FVR);
    timer0_init(4);
    timer1_init(2);

    I2C_init();
    LCD_init();

    INTCONbits.PEIE = 1;
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
    ringbuf_init(&tx_buf, ringbuf, sizeof (ringbuf));

    uint8_t i;
    for (i = 0; i < 3; i++) {
        uint8_t data_0 = EEP_Read(i, 0);
        __delay_ms(1);
        uint8_t data_1 = EEP_Read(i, 1);
        __delay_ms(1);
        uint8_t data_2 = EEP_Read(i, 2);
        __delay_ms(1);
        uint8_t data_3 = EEP_Read(i, 3);
        __delay_ms(1);
        ss[i] = (0xFF000000 & (data_0 << 24)) +(0xFF0000 & (data_1 << 16))+ (0xFF00 & (data_2 << 8))+ (0xFF & (data_3 << 0));
    }

    INTCONbits.GIE = 1;
    while (1) {
        for (i = 0; i < 3; i++) {
            if (flag_read(i, 0x10)) {
                OUT(i, 1);
                LED(i, 1);
                cut[i] = 0;
            }
            if (flag_read(i, 0x10)) {
                print_port = i;
                if (print_content == 2) print_content = 1;
                else print_content++;
                LED(i, 1);
                flag_clear(i, 0x00);
            }
            if (flag_read(i, 0x40)) {
                print_port = i;
                print_content = 0;
                LED(i, 1);
                flag_clear(i, 0x00);
            }
            if (flag_read(i, 0x80)) {
                ss[i] = 0;
                print_content = 3;
                LED(i, 1);
                flag_clear(i, 0x08);
            }
            if (flag_read(i, 0x08)) {
                print_content = 0;
                LED(i, 1);
                flag_clear(i, 0x00);
            }
        }
    }
    return 0;
}
