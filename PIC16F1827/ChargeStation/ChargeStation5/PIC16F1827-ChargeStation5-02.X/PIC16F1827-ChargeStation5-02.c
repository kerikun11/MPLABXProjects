// PIC16F1827 Configuration Bit Settings
// 2015.5.25
// adc:RA 0,1,2, OUTPUT:RB 2,5,7, SW(shield):RB 0,3,6, SW(button):RA4,5, LED:RA 3,6,7, SCL:RB4, SDA:RB1
// ChargeStation Ver.5　出力3つ用
// スイッチフリーUSB差し込むと自動スタート
// pinアサイン一掃
// 押しボタンスイッチは２個だけ
// I2C小型液晶へ出力
// 積算機能追加
// defineでI/Oピンを一般化

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
#define PIC16F1827  // Device
#define ST7032      // I2C_LCD
#define EEPROM24LC64// EEPROM

#include <My_header.h>
#include <My_I2C.h>
#include <My_button.h>

#define CUT_current 100    // 単位は[mA]
#define CUT_time 6       // 単位は[s]

#define LED0 LATA3
#define LED1 LATA6
#define LED2 LATA7
#define OUT0 LATB2
#define OUT1 LATB5
#define OUT2 LATB7
#define SH0 RB0
#define SH1 RB3
#define SH2 RB6
#define SW0 RA4
#define SW1 RA5

uint16_t v[3];
uint16_t s[3];
uint16_t sp[3];
uint32_t ss[3];
uint16_t cut[3];
uint8_t auto_cut_ON[3];
uint8_t cut_flag[3];
uint8_t change_flag[3];
uint8_t cnt[3];
uint8_t cntf[3];
uint16_t cnt0;
uint16_t cnt1s;
uint8_t print_port;
uint8_t print_content;
button_t sh_0;
button_t sh_1;
button_t sh_2;
button_t sw_0;
button_t sw_1;

void interrupt isr(void);
void display(uint8_t i, uint8_t co);
void lchika(void);
void OUT(uint8_t b, uint8_t value);
void LED(uint8_t b, uint8_t value);
uint8_t sh_flag_read(uint8_t port, uint8_t bit_and);
void sh_flag_clear(uint8_t port, uint8_t bit_and);
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
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        button_timer_interrupt(&sh_0, !SH0);
        button_timer_interrupt(&sh_1, !SH1);
        button_timer_interrupt(&sh_2, !SH2);
        button_timer_interrupt(&sw_0, !SW0);
        button_timer_interrupt(&sw_1, !SW1);
        for (i = 0; i < 3; i++) {
            if (auto_cut_ON[i]) {
                v[i] = 2 * ADC(i)*4 / 5; // *3/4 tyousetsu

                if (v[i] < CUT_current) { //もし一定電流を下回ったらカウントアップスタート
                    cut[i]++;
                    if (cut[i] >= 30 * CUT_time) { //一定時間たったら、出力シャットアウト
                        cut_flag[i] = 1;
                    }
                } else { //経過時間カウントリセット
                    cut[i] = 0;
                }
            }
        }
    }
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        cnt0++;
        if (cnt0 == 400) {
            cnt0 = 0;
            lchika();
            display(print_port, print_content);
        }
        cnt1s++;
        if (cnt1s == 1953) {
            cnt1s = 0;
            for (i = 0; i < 3; i++) {
                ss[i] += v[i];
                s[i] = ss[i] / 3600;
                if (s[i] != sp[i]) {
                    change_flag[i] = 1;
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
    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("Charge Station 5");
    I2C_LCD_SetCursor(0, 1);
    if (auto_cut_ON[print_port]) {
        switch (i) {
            case 0:
                I2C_LCD_Puts("Right");
                break;
            case 1:
                I2C_LCD_Puts("Center");
                break;
            case 2:
                I2C_LCD_Puts("Left");
                break;
        }
    } else {
        switch (i) {
            case 0:
                I2C_LCD_Puts("RIGHT");
                break;
            case 1:
                I2C_LCD_Puts("CENTER");
                break;
            case 2:
                I2C_LCD_Puts("LEFT");
                break;
        }
    }
    switch (co) {
        case 0://Port Name, x.xxxA
            I2C_LCD_SetCursor(8, 1);
            I2C_LCD_Putc((v[i] % 10000) / 1000 + '0');
            I2C_LCD_Putc('.');
            I2C_LCD_Putc((v[i] % 1000) / 100 + '0');
            I2C_LCD_Putc((v[i] % 100) / 10 + '0');
            I2C_LCD_Putc((v[i] % 10) / 1 + '0');
            I2C_LCD_Putc('A');
            break;
        case 1://Port Name, xxxxxmAh
            I2C_LCD_SetCursor(7, 1);
            I2C_LCD_Putc((s[i] % 1000000) / 100000 + '0');
            I2C_LCD_Putc((s[i] % 100000) / 10000 + '0');
            I2C_LCD_Putc((s[i] % 10000) / 1000 + '0');
            I2C_LCD_Putc((s[i] % 1000) / 100 + '0');
            I2C_LCD_Putc((s[i] % 100) / 10 + '0');
            I2C_LCD_Putc((s[i] % 10) / 1 + '0');
            I2C_LCD_Puts("mAh");
            break;
        case 2://Port Name, Reset?
            I2C_LCD_SetCursor(8, 1);
            I2C_LCD_Puts("Reset?");
            break;
        case 3://Port Name, Reseted
            I2C_LCD_SetCursor(8, 1);
            I2C_LCD_Puts("Reseted");
            break;
        case 4://Port Name, alwaysON
            I2C_LCD_SetCursor(7, 1);
            I2C_LCD_Puts("Always ON");
            break;
        case 5://Port Name, alwaysOFF
            I2C_LCD_SetCursor(7, 1);
            I2C_LCD_Puts("Auto Stop");
            break;
    }
}

void OUT(uint8_t b, uint8_t value) {
    switch (b) {
        case 0:
            if (value) {
                OUT0 = 0;
            } else {
                OUT0 = 1;
            }
            break;
        case 1:
            if (value) {
                OUT1 = 0;
            } else {
                OUT1 = 1;
            }
            break;
        case 2:
            if (value) {
                OUT2 = 0;
            } else {
                OUT2 = 1;
            }
            break;
    }
}

void LED(uint8_t b, uint8_t value) {
    switch (b) {
        case 0:
            LED0 = value;
            break;
        case 1:
            LED1 = value;
            break;
        case 2:
            LED2 = value;
            break;
        default:
            break;
    }
}

uint8_t sh_flag_read(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 0:
            return (sh_0.flags) & bit_and;
        case 1:
            return (sh_1.flags) & bit_and;
        case 2:
            return (sh_2.flags) & bit_and;
        default:
            return 0;
    }
}

void sh_flag_clear(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 0:
            sh_0.flags &= bit_and;
            break;
        case 1:
            sh_1.flags &= bit_and;
            break;
        case 2:
            sh_2.flags &= bit_and;
            break;
        default:
            break;
    }
}

void main_init(void) {
    OSCCON = 0x70; //intosc 8MHz
    // adc:RA 0,1,2, OUTPUT:RB 2,5,7, SW(shield):RB 0,3,6, SW(button):RA4,5, LED:RA 3,6,7, SCL:RB4, SDA:RB1
    TRISA = 0x37; //0011,0111
    TRISB = 0x5B; //0101,1011
    ANSELA = 0x07; //Use AN0,1,2
    ANSELB = 0x00; //all digital
    WPUA = 0x30;
    WPUB = 0x5B;
    OPTION_REGbits.nWPUEN = 0;

    ADC_init(FVR);
    timer0_init(4);
    timer1_init(2);

    I2C_init();
    I2C_LCD_init();

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

    GIE = 0;
    uint8_t i;
    for (i = 0; i < 3; i++) {
        ss[i] = (0xFF & EEP_read(i, 1))+(0xFF00 & (EEP_read(i, 0) << 8));
        ss[i] *= 3600;
        auto_cut_ON[i] = 1;
    }
    INTCONbits.GIE = 1;

    while (1) {
        for (i = 0; i < 3; i++) {
            if (sh_flag_read(i, 0x10)) {
                sh_flag_clear(i, 0x00);
                OUT(i, 1);
                LED(i, 1);
                cut[i] = 0;
            }
            if (cut_flag[i]) {
                cut_flag[i] = 0;
                OUT(i, 0);
            }
            if (change_flag[i]) {
                change_flag[i] = 0;
                EEP_write16(i, 0, s[i]);
            }
        }
        if (sw_0.flag.press) {
            sw_0.flag.press = 0;
            for (i = 0; i < 3; i++) {
                OUT(i, 1);
                cut[i] = 0;
            }
            if (print_port >= 2)print_port = 0;
            else print_port++;
        }
        if (sw_1.flag.press) {
            sw_1.flag.press = 0;
            for (i = 0; i < 3; i++) {
                OUT(i, 1);
                cut[i] = 0;
            }
            if (print_content >= 1)print_content = 0;
            else print_content++;
        }
        if (sw_1.flag.long_holding_2) {
            sw_1.flag.long_holding_2 = 0;
            print_content = 2;
        }
        if (sw_1.flag.long_hold_2) {
            sw_1.flag.long_hold_2 = 0;
            print_content = 3;
            ss[print_port] = 0;
        }
        if (sw_1.flag.long_holding_3) {
            sw_1.flag.long_holding_3 = 0;
            if (auto_cut_ON[print_port]) {
                auto_cut_ON[print_port] = 0;
                OUT(print_port, 1);
                print_content = 4;
            } else {
                auto_cut_ON[print_port] = 1;
                print_content = 5;
            }
        }
        if (sw_1.flag.long_hold_3) {
            sw_1.flag.long_hold_3 = 0;
            print_content = 0;
        }
    }
    return 0;
}
