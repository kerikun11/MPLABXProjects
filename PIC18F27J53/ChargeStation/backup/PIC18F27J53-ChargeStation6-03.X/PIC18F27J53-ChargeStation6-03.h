/* 
 * File:   PIC18F27J53-ChargeStation6-03.h
 * Author: kerikun11
 *
 * Created on 2015/04/30, 10:15
 */

#ifndef PIC18F27J53_CHARGESTATION6_03_H
#define	PIC18F27J53_CHARGESTATION6_03_H

enum PRINT_CONTENT {
    LOGO,
    TIME,
    CURRENT,
    INTEGRATING,
    CHARGE_TIME,
    RESET,
    RESETED,
    ALWAYS_ON,
    AUTO_STOP
} print_content;

button_t ct0;
button_t ct1;
button_t ct2;
button_t ctm;
delay_t delay_display;
uint8_t print_port;
uint8_t display_flag;
uint16_t I[NUM_PORT];
uint16_t cut_cnt[NUM_PORT];
uint8_t auto_cut_ON[NUM_PORT];
uint8_t cut_time_flag;
uint32_t S[NUM_PORT];
uint32_t s[NUM_PORT];
uint8_t out_flag[NUM_PORT];
uint32_t charge_time[NUM_PORT];
uint8_t sleep_flag = 0;
uint8_t ctmu_flag;
uint16_t ctmu_value0;
uint16_t ctmu_value1;
uint16_t ctmu_value2;
uint16_t ctmu_valuem;

void OUT(uint8_t b, uint8_t value) {
    out_flag[b] = value;
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

uint8_t IN(uint8_t b) {
    switch (b) {
        case 0:
            return ADC0;
        case 1:
            return ADC1;
        case 2:
            return ADC2;
    }
    return 0;
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

uint16_t sw_flag_read(uint8_t port, uint16_t bit_and) {
    switch (port) {
        case 0:
            return (ct0.flags) & bit_and;
        case 1:
            return (ct1.flags) & bit_and;
        case 2:
            return (ct2.flags) & bit_and;
        default:
            return 0;
    }
}

void sw_flag_clear(uint8_t port, uint16_t bit_and) {
    switch (port) {
        case 0:
            ct0.flags &= bit_and;
            break;
        case 1:
            ct1.flags &= bit_and;
            break;
        case 2:
            ct2.flags &= bit_and;
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
        I[i] = 13 * ADC(IN(i)) / 16; // 7/12, 13/16
        if (auto_cut_ON[i]) {
            if (I[i] < CUT_CURRENT) { //もし一定電流を下回ったらカウントアップスタート
                cut_cnt[i]++;
                if (cut_cnt[i] > CUT_TIME) { //一定時間たったら、出力シャットアウト
                    OUT(i, 0);
                }
            } else { //経過時間カウントリセット
                cut_cnt[i] = 0;
            }
        }
    }
}

void integrating(void) {
    for (uint8_t port = 0; port < NUM_PORT; port++) {
        s[port] += I[port];
        S[port] = s[port] / 3600;
    }
}

void charge_time_count(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        if (I[i] > CUT_CURRENT)charge_time[i]++;
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
            display_time_0802(&caltime_now, &epoch_now);
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
            my_utoa(str, S[print_port], 5);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("mAh");
            break;
        case CHARGE_TIME://Port Name, xxxxxmAh
            display_port();
            uint8_t str[10];
            I2C_LCD_SetCursor(6, 0);
            my_utoa(str, charge_time[print_port] / 3600 / 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_SetCursor(0, 1);
            my_utoa(str, (charge_time[print_port] / 3600) % 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Putc(':');
            my_utoa(str, (charge_time[print_port] / 60) % 60, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Putc('-');
            my_utoa(str, charge_time[print_port] % 60, 2);
            I2C_LCD_Puts(str);
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

void main_init(void) {

    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,ctl,ctc,ctr
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
    CTMU_init();

    UART_init();
    uint8_t txbuf[200];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
}

void port_loop(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        if (sw_flag_read(i, 0x0100)) {
            OUT(i, 1);
            LED(i, 1);
            cut_cnt[i] = 0;
            print_port = i;
            if (print_content == AUTO_STOP || print_content == ALWAYS_ON || print_content == RESETED)print_content = CURRENT;
        }
        if (sw_flag_read(i, 0x0400)) {
            sw_flag_clear(i, 0x0000);
            print_content = RESET;
        }
        if (sw_flag_read(i, 0x0004)) {
            sw_flag_clear(i, 0x0000);
            print_content = RESETED;
            S[i] = 0;
            s[i] = 0;
            charge_time[i] = 0;
            delay_set(&delay_display, 64);
        }
        if (sw_flag_read(i, 0x0800)) {
            sw_flag_clear(i, 0x0000);
            if (auto_cut_ON[i]) {
                print_content = AUTO_STOP;
            } else {
                print_content = ALWAYS_ON;
            }
        }
        if (sw_flag_read(i, 0x0008)) {
            sw_flag_clear(i, 0x0000);
            if (auto_cut_ON[i]) {
                auto_cut_ON[i] = 0;
                print_content = ALWAYS_ON;
                OUT(i, 1);
            } else {
                auto_cut_ON[i] = 1;
                print_content = AUTO_STOP;
            }
            delay_set(&delay_display, 64);
        }
        if (sw_flag_read(i, 0x1000)) {
            sw_flag_clear(i, 0x0000);
            print_content = LOGO;
        }
    }
    if (delay_display.flag) {
        delay_display.flag = 0;
        print_content = CURRENT;
        display_flag = 1;
    }
}

void ctmu_loop(void) {
    button_timer_interrupt(&ct0, !(CTMU_read(CTMU0) / ctmu_value0));
    button_timer_interrupt(&ct1, !(CTMU_read(CTMU1) / ctmu_value1));
    button_timer_interrupt(&ct2, !(CTMU_read(CTMU2) / ctmu_value2));
    button_timer_interrupt(&ctm, !(CTMU_read(CTMUM) / ctmu_valuem));
}

void normal_mode_loop(void) {
    if (!edit_flag.flags) {
        port_loop();
        if (ctm.flag.press) {
            ctm.flag.press = 0;
            switch (print_content) {
                case CURRENT:
                    print_content = INTEGRATING;
                    break;
                case INTEGRATING:
                    print_content = CHARGE_TIME;
                    break;
                case CHARGE_TIME:
                    print_content = TIME;
                    break;
                case TIME:
                    print_content = CURRENT;
                    break;
                default:
                    print_content = CURRENT;
                    break;
            }
        }
    }
    if (cut_time_flag) {
        cut_time_flag = 0;
        Auto_cut();
    }
    if (time_change_flag) {
        time_change_flag = 0;
        display_flag = 1;
    }
    if (print_content == TIME)RTCC_adjust_time_button(&ctm, &ct0, &ct1);
    if (display_flag) {
        display_flag = 0;
        display_LCD();
    }
    if (ctmu_flag) {

        ctmu_flag = 0;
        ctmu_loop();
    }
}

void sleep_loop(void) {
    static uint8_t prev_power_sw = 1;
    if (POWER_SW != prev_power_sw) {
        prev_power_sw = POWER_SW;
        if (!POWER_SW) {
            sleep_flag = 1;
            INTCONbits.GIE = 0;
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                OUT(i, 0);
                LED(i, 0);
            }
            I2C_LCD_Clear();
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts("C.S.");
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("SLEEPING");
        } else {
            sleep_flag = 0;
            RTCC_from_RTCC(&caltime_now, &epoch_now);
            print_content = TIME;
            time_change_flag = 1;
            INTCONbits.GIE = 1;
        }
    }
    if (sleep_flag) {
        SLEEP();
        NOP();
    }
}

#endif	/* PIC18F27J53_CHARGESTATION6_03_H */
