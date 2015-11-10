/* 
 * File:   PIC18F27J53-ChargeStation6-07.h
 * Author: kerikun11
 *
 * Created on 2015/06/15, 18:31
 */

#ifndef PIC18F27J53_CHARGESTATION6_07_H
#define	PIC18F27J53_CHARGESTATION6_07_H

#define CUT_CURRENT 100  // [mA]
#define CUT_TIME 6       // [s]

#define NUM_PORT 3

#define CTMU0 0 // RA0
#define CTMU1 1 // RA1
#define CTMU2 2 // RA2
#define CTMUM 3 // RA3

#define POWER_SW 12//PORTBbits.RB0

#define ADC0 8  // AN8
#define ADC1 9  // AN9
#define ADC2 10 // AN10

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATC2

typedef enum PRINT_CONTENT {
    LOGO,
    TIME,
    START_CHARGING,
    CURRENT,
    INTEGRATING,
    CHARGE_TIME,
    RESET_,
    RESETED,
    TOGGLE_STOP_,
    ALWAYS_ON,
    AUTO_STOP,
    TOGGLE_LED_,
    LED_ON,
    LED_OFF,
    NOTHING_DONE
} print_content_t;

typedef struct {
    button_t ctmu;
    uint16_t ctmu_value;
    uint16_t current;
    uint32_t integrated_current;
    uint32_t integrated_current_sec;
    uint32_t integrated_time;
    uint16_t cut_cnt;

    union {
        uint8_t flags;

        struct {
            uint8_t auto_cut_ON : 1;
            uint8_t led_indicater_ON : 1;
            uint8_t out_flag : 1;
            uint8_t led_flag : 1;
        } flag;
    };
} port_t;

port_t port[NUM_PORT];

button_t ctmu_m;
uint16_t ctmu_value_m;
uint8_t ctmu_ratio;
uint8_t ctmu_flag;

print_content_t print_content;
print_content_t next_print_content;
uint8_t print_port;
uint8_t display_flag;
delay_t delay_display;

uint8_t cut_time_flag;

ringbuf_t usb_tx;
ringbuf_t usb_rx;

uint8_t sleep_flag = 0;

void OUT(uint8_t b, uint8_t value) {
    port[b].flag.out_flag = value;
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

void LED_OUT(uint8_t b, uint8_t value) {
    port[b].flag.led_flag = value;
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

void LED_indicator(void) {
    uint8_t i;
    static uint8_t cnt[3];
    static uint8_t cntf[3];
    for (i = 0; i < NUM_PORT; i++) {
        if (port[i].flag.led_indicater_ON) {
            cnt[i]++;
            if (cnt[i] % 2 == 1) {//奇数ならLEDは消灯
                LED_OUT(i, 0);
            } else {//偶数のとき
                if (cnt[i] / 2 <= port[i].current / 100) {//LED点滅回数のほうが電流より少ない間LED点灯
                    LED_OUT(i, 1);
                    cntf[i] = 0; //フラグリセット
                } else { // LEDの点滅回数のほうが電流より多くなったときフラグ加算
                    cntf[i]++;
                    LED_OUT(i, 0);
                    if (cntf[i] >= 2) {//フラグが2になったら、元に戻る
                        cnt[i] = 0;
                    }
                }
            }
        }
    }
}

void Auto_cut(void) {
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        port[i].current = 13 * ADC(IN(i)) / 16; // 7/12, 13/16
        if (port[i].flag.auto_cut_ON) {
            if (port[i].current < CUT_CURRENT) { //もし一定電流を下回ったらカウントアップスタート
                port[i].cut_cnt++;
                if (port[i].cut_cnt > CUT_TIME) { //一定時間たったら、出力シャットアウト
                    OUT(i, 0);
                }
            } else { //経過時間カウントリセット
                port[i].cut_cnt = 0;
            }
        }
    }
}

void integrating(void) {
    static uint32_t ic_cache[NUM_PORT];
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        port[i].integrated_current_sec += port[i].current;
        port[i].integrated_current = port[i].integrated_current_sec / 3600;
        if (port[i].integrated_current_sec != ic_cache[i]) {
            ic_cache[i] = port[i].integrated_current_sec;
            EEP_write32(0, i, port[i].integrated_current_sec);
        }
    }
}

void charge_time_count(void) {
    uint8_t i;
    static uint32_t it_cache[NUM_PORT];
    for (i = 0; i < NUM_PORT; i++) {
        if (port[i].current > CUT_CURRENT)port[i].integrated_time++;
        if (port[i].integrated_time != it_cache[i]) {
            it_cache[i] = port[i].integrated_time;
            EEP_write32(0, i, port[i].integrated_time);
        }
    }
}

void display_port(void) {
    I2C_LCD_SetCursor(0, 0);
    //const char port_char[][]={};
    switch (print_port) {
        case 0:
            if (port[print_port].flag.auto_cut_ON) I2C_LCD_Puts("Left Port");
            else I2C_LCD_Puts("LEFT PORT");
            break;
        case 1:
            if (port[print_port].flag.auto_cut_ON) I2C_LCD_Puts("Center Port");
            else I2C_LCD_Puts("CENTER PORT");
            break;
        case 2:
            if (port[print_port].flag.auto_cut_ON) I2C_LCD_Puts("Right Port");
            else I2C_LCD_Puts("RIGHT PORT");
            break;
    }
}

void display_LCD(void) {
    I2C_LCD_Clear();
    switch (print_content) {
        case LOGO:
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts("Charge Station 6");
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Made by KERI");
            break;
        case TIME:
            display_time_1602(&caltime_now, &epoch_now);
            break;
        case START_CHARGING://Port Name, Start Charging?
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Start Charging");
            break;
        case CURRENT://Port Name, x.xxxA
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Putc((port[print_port].current % 10000) / 1000 + '0');
            I2C_LCD_Putc('.');
            I2C_LCD_Putc((port[print_port].current % 1000) / 100 + '0');
            I2C_LCD_Putc((port[print_port].current % 100) / 10 + '0');
            I2C_LCD_Putc((port[print_port].current % 10) / 1 + '0');
            I2C_LCD_Putc('A');
            break;
        case INTEGRATING://Port Name, xxxxxmAh
            display_port();
            I2C_LCD_SetCursor(0, 1);
            uint8_t str[10];
            my_utoa(str, port[print_port].integrated_current, 5);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("mAh");
            break;
        case CHARGE_TIME://Port Name, xxxxxmAh
            display_port();
            uint8_t str[10];
            I2C_LCD_SetCursor(0, 1);
            my_utoa(str, port[print_port].integrated_time / 3600 / 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("d ");
            my_utoa(str, (port[print_port].integrated_time / 3600) % 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("h ");
            my_utoa(str, (port[print_port].integrated_time / 60) % 60, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("m ");
            my_utoa(str, port[print_port].integrated_time % 60, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("s");
            break;
        case RESET_://Port Name, Reset?
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Integrat Reset?");
            break;
        case RESETED://Port Name, Reseted
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Integrat Reseted");
            break;
        case TOGGLE_STOP_://Port Name, Toggle AutoStop?
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Toggle AutoStop?");
            break;
        case ALWAYS_ON://Port Name, alwaysON
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Always Charging");
            break;
        case AUTO_STOP://Port Name, alwaysOFF
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Auto Stop ON");
            break;
        case TOGGLE_LED_://Port Name, Toggle AutoStop?
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Toggle LED?");
            break;
        case LED_ON://Port Name, alwaysON
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("LED ON");
            break;
        case LED_OFF://Port Name, alwaysOFF
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("LED OFF");
            break;
        case NOTHING_DONE://Port Name, Nothing done
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Nothing done.");
            break;
    }
}

void tx_send_dec(uint8_t dec, uint8_t edit) {
    uint8_t str[10];
    my_utoa(&str, dec, 2);
    if (edit && halfsec)tx_sends("  ");
    else tx_sends(str);
}

void print_time(void) {
    GIE = 0;
    tx_sends("\t");
    tx_send_dec(20, edit_flag.flag.YY);
    tx_send_dec(caltime_now.YY, edit_flag.flag.YY);
    tx_sends("/");
    tx_send_dec(caltime_now.MM, edit_flag.flag.MM);
    tx_sends("/");
    tx_send_dec(caltime_now.DD, edit_flag.flag.DD);
    tx_sends(" (");
    tx_sends(weekday_3char[caltime_now.EE]);
    tx_sends(") ");
    tx_send_dec(caltime_now.hh, edit_flag.flag.hh);
    if (colon)tx_send(':');
    else tx_send(' ');
    tx_send_dec(caltime_now.mm, edit_flag.flag.mm);
    tx_sends("-");
    tx_send_dec(caltime_now.ss, edit_flag.flag.ss);
    tx_send('\n');
    GIE = 1;
}

void ctmu_set_ratio(uint8_t percentage) {
    port[0].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU0) / 100;
    port[1].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU1) / 100;
    port[2].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU2) / 100;
    ctmu_value_m = (uint16_t) percentage * CTMU_read(CTMUM) / 100;
}

void comm_at(uint8_t *hand, uint8_t min, uint8_t max, uint8_t value) {
    if (value >= min && value <= max) {
        *hand = value;
        RTCC_from_caltime(&caltime_now, &epoch_now);
        time_change_flag = 1;
        print_time();
    } else {
        tx_sends("\terror\n");
    }
}

void comm_disp(uint8_t content, uint8_t i) {
    switch (content) {
        case 0:
            tx_sends("\t");
            tx_send((port[i].current % 10000) / 1000 + '0');
            tx_send('.');
            tx_send((port[i].current % 1000) / 100 + '0');
            tx_send((port[i].current % 100) / 10 + '0');
            tx_send((port[i].current % 10) / 1 + '0');
            tx_sends("A\n");
            break;
        case 1:
            tx_sends("\t");
            tx_sendn(port[i].integrated_current, 5);
            tx_sends("mAh\n");
            break;
        case 2:
            tx_sends("\t");
            char str[10];
            my_utoa(str, port[i].integrated_time / 3600 / 24, 2);
            tx_sends(str);
            tx_sends("d ");
            my_utoa(str, (port[i].integrated_time / 3600) % 24, 2);
            tx_sends(str);
            tx_sends("h ");
            my_utoa(str, (port[i].integrated_time / 60) % 60, 2);
            tx_sends(str);
            tx_sends("m ");
            my_utoa(str, port[i].integrated_time % 60, 2);
            tx_sends(str);
            tx_sends("s");
            break;
    }
}

void command_operation(char *opcode, char *opland1, char *opland2, char *opland3) {
    if (!my_strcmp(opcode, "help") || !my_strcmp(opcode, "?")) {
        tx_sends(
                "\t****************************\n"
                "\t**** Charge Station 6.7 ****\n"
                "\t**** Made by @Ryokeri   ****\n"
                "\t****************************\n\n"
                "\tcommand \topeland1\topeland2\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tsettings(set) [port:left(l),center(c),right(r)]\n\t\t[auto_stop(as),always_on(ao),integrating_reset(ir)]\n"
                "\tdisplay(d) [port:left(l),center(c),right(r)]\n\t\t[content:current(c),integrated_current(ic),integrated_time(it)]\n"
                "\ttouch [reset(r),initialize(init)] [value(%)]\n"
                "\tRESET();\n"
                );
    }
    if (!my_strcmp(opcode, "settings") || !my_strcmp(opcode, "set")) {
        if (!my_strcmp(opland1, "auto_stop")) {
        }
    }
    if (!my_strcmp(opcode, "RESET();")) {
        RESET();
    }
    if (!my_strcmp(opcode, "bootload")) {
        asm("goto   0x001C");
    }
    if (!my_strcmp(opcode, "at") || !my_strcmp(opcode, "adjust_time")) {
        if (!my_strcmp(opland1, "y")) {
            comm_at(&caltime_now.YY, 0, 99, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "M")) {
            comm_at(&caltime_now.MM, 1, 12, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "d")) {
            comm_at(&caltime_now.DD, 1, month_length(caltime_now.YY, caltime_now.MM), my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "h")) {
            comm_at(&caltime_now.hh, 0, 23, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "m")) {
            comm_at(&caltime_now.mm, 0, 59, my_atoi(opland2));
        }
        if (!my_strcmp(opland1, "s")) {
            comm_at(&caltime_now.ss, 0, 59, my_atoi(opland2));
        }
    }
    if (!my_strcmp(opcode, "touch")) {
        if (!my_strcmp(opland1, "initialize") || !my_strcmp(opland1, "init")) {
            uint8_t percentage = my_atoi(opland2);
            if (percentage <= 100) {
                ctmu_ratio = percentage;
                ctmu_set_ratio(ctmu_ratio);
                tx_sends("\tinitializing complete\n");
            } else {
                tx_sends("\tinvalid data\n\tinitializing failed\n");
            }
        }
        if (!my_strcmp(opland1, "reset") || !my_strcmp(opland1, "r")) {
            ctmu_set_ratio(ctmu_ratio);
            tx_sends("\tseting complete\n");
        }
    }
    if (!my_strcmp(opcode, "display") || !my_strcmp(opcode, "d")) {
        if (!my_strcmp(opland1, "left") || !my_strcmp(opland1, "l")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_disp(0, 0);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_disp(1, 0);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_disp(2, 0);
            }

        }
        if (!my_strcmp(opland1, "center") || !my_strcmp(opland1, "c")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_disp(0, 1);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_disp(1, 1);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_disp(2, 1);
            }
        }
        if (!my_strcmp(opland1, "right") || !my_strcmp(opland1, "r")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_disp(0, 2);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_disp(1, 2);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_disp(2, 2);
            }
        }
    }
    if (!my_strcmp(opcode, "print_time") || !my_strcmp(opcode, "t")) {
        print_time();
    }
}

void rx_loop(void) {
    static ringbuf_t comm_buf;
    static uint8_t comm_buf_init = 1;
    if (comm_buf_init) {
        comm_buf_init = 0;
        char buf[100];
        ringbuf_init(&comm_buf, buf, sizeof (buf));
    }
    if (ringbuf_num(&rx_buf)) {
        char ascii = ringbuf_pop(&rx_buf);
        switch (ascii) {
            case '\r':
                ringbuf_put(&comm_buf, '\0');
                tx_send('\t');
                tx_sendn(ringbuf_num(&comm_buf) - 1, 2);
                tx_sends("\n");
                char opcode[100];
                char opland1[100];
                char opland2[100];
                char opland3[100];
                uint8_t i;
                for (i = 0; opcode[i] = ringbuf_pop(&comm_buf); i++);
                opcode[i] = '\0';
                for (i = 0; opland1[i] = ringbuf_pop(&comm_buf); i++);
                opland1[i] = '\0';
                for (i = 0; opland2[i] = ringbuf_pop(&comm_buf); i++);
                opland2[i] = '\0';
                for (i = 0; opland3[i] = ringbuf_pop(&comm_buf); i++);
                opland3[i] = '\0';
                command_operation(opcode, opland1, opland2, opland3);
                break;
            case ' ':
                ringbuf_put(&comm_buf, '\0');
                tx_send(' ');
                break;
            case '\b':
                ringbuf_backspace(&comm_buf);
                tx_sends("\b \b");
                break;
            case 0x7F: // Del
                for (uint8_t i = 0; i < ringbuf_num(&comm_buf); i++) tx_sends("\b \b");
                ringbuf_delete(&comm_buf);
                break;
            default:
                if (ascii >= ' ' && ascii <= '~') {
                    ringbuf_put(&comm_buf, ascii);
                    tx_send(ascii);
                }
                break;
        }
    }
}

void port_loop(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        // ボタンが押されていたらLED点灯
        if (port[i].ctmu.flag.pressing) {
            //ctmu[i].flags = 0;
            LED_OUT(i, 1);
        }
        // シングルタップ
        if (port[i].ctmu.flag.press) {
            port[i].ctmu.flags = 0;
            LED_OUT(i, 0);
            // 表示ポートと一致していれば、表示循環
            // 表示ポートと一致していなければ、一致させる
            if (print_port == i) {
                switch (print_content) {
                    case CURRENT:
                        print_content = INTEGRATING;
                        break;
                    case INTEGRATING:
                        print_content = CHARGE_TIME;
                        break;
                    case CHARGE_TIME:
                        print_content = CURRENT;
                        break;
                    default:
                        print_content = CURRENT;
                        break;
                }
            } else {
                print_port = i;
            }
            // 充電状態でなければ、充電開始表示
            if (!port[i].flag.out_flag) {
                print_content = START_CHARGING;
                next_print_content = CURRENT;
                delay_set(&delay_display, 32);
                display_flag = 1;
            }
            // 充電開始
            OUT(i, 1);
            port[i].cut_cnt = 0;
            display_flag = 1;
        }
        // 長押し2 => 積算リセット
        if (port[i].ctmu.flag.long_holding_2) {
            port[i].ctmu.flags = 0;
            print_content = RESET_;
            display_flag = 1;
        }
        if (port[i].ctmu.flag.long_hold_2) {
            port[i].ctmu.flags = 0;
            LED_OUT(i, 0);
            port[i].integrated_current = 0;
            port[i].integrated_current_sec = 0;
            port[i].integrated_time = 0;
            print_content = RESETED;
            next_print_content = INTEGRATING;
            delay_set(&delay_display, 64);
            display_flag = 1;
        }
        // 長押し3 => トグル自動給電ストップ
        if (port[i].ctmu.flag.long_holding_3) {
            port[i].ctmu.flags = 0;
            print_content = TOGGLE_STOP_;
            display_flag = 1;
        }
        if (port[i].ctmu.flag.long_hold_3) {
            port[i].ctmu.flags = 0;
            LED_OUT(i, 0);
            if (port[i].flag.auto_cut_ON) {
                port[i].flag.auto_cut_ON = 0;
                OUT(i, 1);
                print_content = ALWAYS_ON;
                next_print_content = TIME;
                delay_set(&delay_display, 100);
                display_flag = 1;
            } else {
                port[i].flag.auto_cut_ON = 1;
                print_content = AUTO_STOP;
                next_print_content = TIME;
                delay_set(&delay_display, 100);
                display_flag = 1;
            }
        }
        // 長押し4 => トグルLEDインジケーター
        if (port[i].ctmu.flag.long_holding_4) {
            port[i].ctmu.flags = 0;
            print_content = TOGGLE_LED_;
            display_flag = 1;
        }
        if (port[i].ctmu.flag.long_hold_4) {
            port[i].ctmu.flags = 0;
            LED_OUT(i, 0);
            if (port[i].flag.led_indicater_ON) {
                port[i].flag.led_indicater_ON = 0;
                print_content = LED_OFF;
                next_print_content = TIME;
                delay_set(&delay_display, 100);
                display_flag = 1;
            } else {
                port[i].flag.led_indicater_ON = 1;
                print_content = LED_ON;
                next_print_content = TIME;
                delay_set(&delay_display, 100);
                display_flag = 1;
            }
        }
        // 長押し => 何もしない
        if (port[i].ctmu.flag.long_holding_5) {
            port[i].ctmu.flags = 0;
            LED_OUT(i, 0);
            print_content = NOTHING_DONE;
            next_print_content = CURRENT;
            delay_set(&delay_display, 64);
            display_flag = 1;
        }
    }
}
// タッチセンサのサンプリング

void ctmu_loop(void) {
    if (ctmu_flag) {
        ctmu_flag = 0;
        button_timer_interrupt(&port[0].ctmu, !(CTMU_read(CTMU0) / port[0].ctmu_value));
        button_timer_interrupt(&port[1].ctmu, !(CTMU_read(CTMU1) / port[1].ctmu_value));
        button_timer_interrupt(&port[2].ctmu, !(CTMU_read(CTMU2) / port[2].ctmu_value));
        button_timer_interrupt(&ctmu_m, !(CTMU_read(CTMUM) / ctmu_value_m));
    }
}

void normal_mode_loop(void) {
    INTCONbits.GIE = 0;
    if (!edit_flag.flags) {
        port_loop();
        if (ctmu_m.flag.press) {
            ctmu_m.flags = 0;
            display_flag = 1;
            switch (print_content) {
                case CURRENT:
                    print_content = TIME;
                    break;
                case TIME:
                    print_content = LOGO;
                    break;
                case LOGO:
                    print_content = CURRENT;
                    break;
                default:
                    print_content = CURRENT;
                    break;
            }
        }
    }
    if (print_content == TIME)RTCC_adjust_time_button(&ctmu_m, &port[0].ctmu, &port[1].ctmu);
    if (cut_time_flag) {
        cut_time_flag = 0;
        Auto_cut();
    }
    if (time_change_flag) {
        time_change_flag = 0;
        display_flag = 1;
    }
    if (delay_display.flag) {
        delay_display.flag = 0;
        print_content = next_print_content;
        display_flag = 1;
    }
    if (display_flag) {
        display_flag = 0;
        display_LCD();
    }
}

void USB_loop(void) {
    char data;
    int rx_len;
    rx_len = get_string_usb(&data, 1);
    if (rx_len) {
        ringbuf_put(&rx_buf, data);
    }
    if (ringbuf_num(&tx_buf)) {
        data = ringbuf_pop(&tx_buf);
        while (put_string_usb(&data, 1));
    }
}

void sleep_loop(void) {
    if (ADC(POWER_SW) < 2048) {
        sleep_flag = 1;
        INTCONbits.GIE = 0;
        for (uint8_t i = 0; i < NUM_PORT; i++) {
            OUT(i, 0);
            LED_OUT(i, 0);
        }
        UCONbits.USBEN = 0;
        I2C_LCD_Clear();
        I2C_LCD_SetCursor(0, 0);
        I2C_LCD_Puts("Charge Station 6");
        I2C_LCD_SetCursor(0, 1);
        I2C_LCD_Puts("SLEEPING");
    }
    while (sleep_flag) {
        if (ADC(POWER_SW) > 2048) {
            RESET();
        }
        SLEEP();
        NOP();
    }
}

#endif	/* PIC18F27J53_CHARGESTATION6_07_H */
