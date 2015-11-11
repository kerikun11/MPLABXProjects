// ChargeStation-2.1.01
// PIC18F27J53
// 2.1.00 試作1号用pinアサイン 切削基板
// 2.1.01 2015.03.12 初版、ChargeStation5からの引き継ぎ

#include <xc.h>
#include <stdint.h>
// CONFIG1L
#pragma config WDTEN = ON, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
// CONFIG1H
#pragma config CPUDIV = OSC1, CP0 = OFF
// CONFIG2L
#pragma config OSC = INTOSCPLL, SOSCSEL = LOW, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
// CONFIG2H
#pragma config WDTPS = 256
// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF, RTCOSC = T1OSCREF, DSBOREN = OFF, DSWDTEN = OFF, DSWDTPS = G2
// CONFIG3H
#pragma config IOL1WAY = OFF, ADCSEL = BIT12, MSSP7B_EN = MSK7
// CONFIG4L
#pragma config WPFP = PAGE_127, WPCFG = OFF
// CONFIG4H
#pragma config WPDIS = OFF, WPEND = PAGE_WPFP, LS48MHZ = SYS48X8

#define _XTAL_FREQ 48000000

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>

#define CUT_CURRENT 100  // [mA]
#define CUT_TIME 5      // [s]

#define NUM_PORT 3

#define SW0 PORTAbits.RA0
#define SW1 PORTAbits.RA1
#define SW2 PORTAbits.RA2
#define SW PORTAbits.RA3

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATC2

enum PRINT_CONTENT {
    CURRENT,
    INTEGRATING,
    RESET,
    RESETED,
    ALWAYS_ON,
    AUTO_STOP
} print_content;

button_t sw0;
button_t sw1;
button_t sw2;
button_t sw;
uint8_t print_port;
uint8_t display_flag;
uint16_t I[NUM_PORT];
uint16_t cut_cnt[NUM_PORT];
uint8_t auto_cut_ON[NUM_PORT];
uint32_t S[NUM_PORT];
uint32_t ss[NUM_PORT];

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
    }
}

uint8_t sw_flag_read(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 0:
            return (sw0.flags) & bit_and;
        case 1:
            return (sw1.flags) & bit_and;
        case 2:
            return (sw2.flags) & bit_and;
        default:
            return 0;
    }
}

void sw_flag_clear(uint8_t port, uint8_t bit_and) {
    switch (port) {
        case 0:
            sw0.flags &= bit_and;
            break;
        case 1:
            sw1.flags &= bit_and;
            break;
        case 2:
            sw2.flags &= bit_and;
            break;
    }
}

void lchika(void) {
    uint8_t i;
    static uint8_t cnt[3];
    static uint8_t cntf[3];
    for (i = 0; i < 3; i++) {
        cnt[i]++;
        if (cnt[i] % 2 == 1) {//奇数ならLEDは消灯
            LED(i, 0);
        } else {//偶数のとき
            if (cnt[i] / 2 <= I[i] / 100) {//LED点滅回数のほうが電流より少ない間LED点灯
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

void Auto_cut(void) {
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        I[i] = 13 * ADC(i + 8) / 16;
        if (auto_cut_ON[i]) {
            if (I[i] < CUT_CURRENT) { //もし一定電流を下回ったらカウントアップスタート
                cut_cnt[i]++;
                if (cut_cnt[i] >= 46 * CUT_TIME) { //一定時間たったら、出力シャットアウト
                    OUT(i, 0);
                }
            } else { //経過時間カウントリセット
                cut_cnt[i] = 0;
            }
        }
    }
}

void display(void) {
    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    switch (print_port) {
        case 0:
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Right");
            else I2C_LCD_Puts("RIGHT");
            break;
        case 1:
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Center");
            else I2C_LCD_Puts("CENTER");
            break;
        case 2:
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Left");
            else I2C_LCD_Puts("LEFT");
            break;
    }
    I2C_LCD_SetCursor(0, 1);
    switch (print_content) {
        case CURRENT://Port Name, x.xxxA
            I2C_LCD_Putc((I[print_port] % 10000) / 1000 + '0');
            I2C_LCD_Putc('.');
            I2C_LCD_Putc((I[print_port] % 1000) / 100 + '0');
            I2C_LCD_Putc((I[print_port] % 100) / 10 + '0');
            I2C_LCD_Putc((I[print_port] % 10) / 1 + '0');
            I2C_LCD_Putc('A');
            break;
        case INTEGRATING://Port Name, xxxxxmAh
            I2C_LCD_Putc((S[print_port] % 100000) / 10000 + '0');
            I2C_LCD_Putc((S[print_port] % 10000) / 1000 + '0');
            I2C_LCD_Putc((S[print_port] % 1000) / 100 + '0');
            I2C_LCD_Putc((S[print_port] % 100) / 10 + '0');
            I2C_LCD_Putc((S[print_port] % 10) / 1 + '0');
            I2C_LCD_Puts("mAh");
            break;
        case RESET://Port Name, Reset?
            I2C_LCD_Puts("Reset?");
            break;
        case RESETED://Port Name, Reseted
            I2C_LCD_Puts("Reseted");
            break;
        case ALWAYS_ON://Port Name, alwaysON
            I2C_LCD_Puts("AlwaysON");
            break;
        case AUTO_STOP://Port Name, alwaysOFF
            I2C_LCD_Puts("AutoStop");
            break;
    }
}

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        static uint16_t cnt_t0;
        if (cnt_t0) {
            cnt_t0--;
        } else {
            cnt_t0 = 120;
            lchika();
        }
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x80;
        for (uint8_t i = 0; i < NUM_PORT; i++) {
            tx_sends("PORT");
            tx_send('0' + i + 1);
            tx_send('=');
            tx_sendn(I[i], 6);
            tx_sends("\n\n");

            ss[i] += I[i];
            S[i] = ss[i] / 3600;
        }
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&sw, !SW);
        button_timer_interrupt(&sw0, !SW0);
        button_timer_interrupt(&sw1, !SW1);
        button_timer_interrupt(&sw2, !SW2);
        Auto_cut();
        display_flag = 1;
    }
}

int main(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,SW2,SW1,SW0
    TRISB = 0b00111111; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11111111; // all digital
    ANCON1 = 0b00011000; // AN8,AN9,AN10 is analog

    timer0_init(6);
    timer1_init(0, T1OSC);
    timer3_init(2); // button用
    I2C_init();
    I2C_LCD_init();
    ADC_init(VDD);

    UART_init();
    uint8_t txbuf[200];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));

    INTCONbits.GIE = 1;

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("Charge");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("Station");

    uint8_t i;

    for (i = 0; i < NUM_PORT; i++) {
        OUT(i, 1);
        LED(i, 1);
        cut_cnt[i] = 0;
        auto_cut_ON[i] = 1;
    }

    while (1) {
        CLRWDT();
        for (i = 0; i < NUM_PORT; i++) {
            if (sw_flag_read(i, 0x10)) {
                OUT(i, 1);
                LED(i, 1);
                cut_cnt[i] = 0;
            }
            if (sw_flag_read(i, 0x10)) {
                sw_flag_clear(i, 0x00);
                print_port = i;
            }
            if (sw_flag_read(i, 0x40)) {
                sw_flag_clear(i, 0x00);
                print_content = RESET;
            }
            if (sw_flag_read(i, 0x04)) {
                sw_flag_clear(i, 0x00);
                print_content = RESETED;
            }
            if (sw_flag_read(i, 0x80)) {
                sw_flag_clear(i, 0x00);
                if (auto_cut_ON[i]) {
                    auto_cut_ON[i] = 0;
                    print_content = ALWAYS_ON;
                } else {
                    auto_cut_ON[i] = 1;
                    print_content = AUTO_STOP;
                }
            }
        }
        if (sw.flag.press) {
            sw.flag.press = 0;
            if (print_content == CURRENT)print_content = INTEGRATING;
            else print_content = CURRENT;
        }
        if (display_flag) {
            display_flag = 0;
            display();
        }
    }
    return 0;
}
