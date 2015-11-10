/* 
 * File:   PIC18F27J53-ChargeStation6-02.h
 * Author: kerikun11
 *
 * Created on 2015/03/24, 8:53
 */

#ifndef PIC18F27J53_CHARGESTATION6_02_H
#define	PIC18F27J53_CHARGESTATION6_02_H

enum PRINT_CONTENT {
    LOGO,
    TIME,
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
delay_t d_display;
uint8_t print_port;
uint8_t display_flag;
uint16_t I[NUM_PORT];
uint16_t cut_cnt[NUM_PORT];
uint8_t auto_cut_ON[NUM_PORT];
uint8_t cut_flag;
uint32_t S[NUM_PORT];
uint32_t s[NUM_PORT];
uint8_t sleep_flag = 0;

void OUT(uint8_t b, uint8_t value) {
    switch (b) {
        case 0:
            OUT0 = value;
            break;
        case 1:
            OUT1 = value;
            break;
        case 2:
            OUT2 = value;
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

void display_port(void) {
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
}

void display_LCD(void) {
    I2C_LCD_Clear();
    switch (print_content) {
        case LOGO:
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts("Charge");
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Station");
            break;
        case TIME:
            display_time(&caltime_now, &epoch_now);
            break;
        case CURRENT://Port Name, x.xxxA
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Putc((I[print_port] % 10000) / 1000 + '0');
            I2C_LCD_Putc('.');
            I2C_LCD_Putc((I[print_port] % 1000) / 100 + '0');
            I2C_LCD_Putc((I[print_port] % 100) / 10 + '0');
            I2C_LCD_Putc((I[print_port] % 10) / 1 + '0');
            I2C_LCD_Putc('A');
            break;
        case INTEGRATING://Port Name, xxxxxmAh
            display_port();
            I2C_LCD_SetCursor(0, 1);
            uint8_t str[10];
            utoa(str, S[print_port], 5);
            I2C_LCD_Puts(str);
            //            I2C_LCD_Putc((S[print_port] % 100000) / 10000 + '0');
            //            I2C_LCD_Putc((S[print_port] % 10000) / 1000 + '0');
            //            I2C_LCD_Putc((S[print_port] % 1000) / 100 + '0');
            //            I2C_LCD_Putc((S[print_port] % 100) / 10 + '0');
            //            I2C_LCD_Putc((S[print_port] % 10) / 1 + '0');
            I2C_LCD_Puts("mAh");
            break;
        case RESET://Port Name, Reset?
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Reset?");
            break;
        case RESETED://Port Name, Reseted
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Reseted");
            break;
        case ALWAYS_ON://Port Name, alwaysON
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("AlwaysON");
            break;
        case AUTO_STOP://Port Name, alwaysOFF
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("AutoStop");
            break;
    }
}

void integrating(void) {
    for (uint8_t port = 0; port < NUM_PORT; port++) {
        s[port] += I[port];
        S[port] = s[port] / 3600;
    }
}

void main_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,SW2,SW1,SW0
    TRISB = 0b00111111; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11111111; // all digital
    ANCON1 = 0b00011000; // AN8,AN9,AN10 is analog
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(6); // Lチカ用
    timer1_init(0, T1OSC); // 積算用
    timer3_init(2); // button用
    I2C_init();
    I2C_LCD_init();
    ADC_init(VDD);
    RTCC_init();

    UART_init();
    uint8_t txbuf[200];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
}

void nomal_mode_loop(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        if (sw_flag_read(i, 0x10)) {
            OUT(i, 1);
            LED(i, 1);
            cut_cnt[i] = 0;
            print_port = i;
            if (print_content == AUTO_STOP || print_content == ALWAYS_ON)print_content = CURRENT;
        }
        if (sw_flag_read(i, 0x40)) {
            sw_flag_clear(i, 0x00);
            print_content = RESET;
        }
        if (sw_flag_read(i, 0x04)) {
            sw_flag_clear(i, 0x00);
            print_content = RESETED;
            S[i] = 0;
            s[i] = 0;
            delay_set(&d_display, 64);
        }
        if (sw_flag_read(i, 0x80)) {
            sw_flag_clear(i, 0x00);
            if (auto_cut_ON[i]) {
                print_content = AUTO_STOP;
            } else {
                print_content = ALWAYS_ON;
            }
        }
        if (sw_flag_read(i, 0x08)) {
            sw_flag_clear(i, 0x00);
            if (auto_cut_ON[i]) {
                auto_cut_ON[i] = 0;
                print_content = ALWAYS_ON;
            } else {
                auto_cut_ON[i] = 1;
                print_content = AUTO_STOP;
            }
            delay_set(&d_display, 64);
        }
    }
    if (d_display.flag) {
        d_display.flag=0;
        print_content = CURRENT;
        display_flag = 1;
    }
}

void sleep_loop(void) {
    static uint8_t prev_power_sw = 1;
    if (POWER_SW != prev_power_sw) {
        prev_power_sw = POWER_SW;
        if (!POWER_SW) {
            sleep_flag = 1;
            T0CONbits.TMR0ON = 0;
            T1CONbits.TMR1ON = 1;
            T3CONbits.TMR3ON = 0;
            TXSTA1bits.TXEN = 0;
            RCSTA1bits.CREN = 0;

            INTCONbits.T0IE = 0;
            PIE1bits.TMR1IE = 1;
            PIE2bits.TMR3IE = 0;
            PIE1bits.TX1IE = 0;
            PIE1bits.RC1IE = 0;
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                OUT(i, 0);
                LED(i, 0);
            }
        } else {
            sleep_flag = 0;
            RTCC_from_RTCC(&caltime_now, &epoch_now);
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                LED(i, 1);
            }
            T0CONbits.TMR0ON = 1;
            T1CONbits.TMR1ON = 1;
            T3CONbits.TMR3ON = 1;
            TXSTA1bits.TXEN = 1;
            RCSTA1bits.CREN = 1;

            INTCONbits.T0IE = 1;
            PIE1bits.TMR1IE = 1;
            PIE2bits.TMR3IE = 1;
            PIE1bits.TX1IE = 1;
            PIE1bits.RC1IE = 1;
        }
    }
    if (sleep_flag) {
        SLEEP();
        NOP();
    }
}

#endif	/* PIC18F27J53_CHARGESTATION6_02_H */
