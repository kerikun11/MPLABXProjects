/* 
 * File:   PIC18F27J53-ChargeStation6-05.h
 * Author: kerikun11
 *
 * Created on 2015/06/04, 18:15
 */

#ifndef PIC18F27J53_CHARGESTATION6_05_H
#define	PIC18F27J53_CHARGESTATION6_05_H

enum PRINT_CONTENT {
    LOGO,
    TIME,
    CURRENT,
    INTEGRATING,
    CHARGE_TIME,
    RESET_,
    RESETED,
    ALWAYS_ON,
    AUTO_STOP,
    NOTHING_DONE
} print_content;

//button_t ctmu[NUM_PORT];
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
uint16_t ctmu_value[NUM_PORT];
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

void LED_OUT(uint8_t b, uint8_t value) {
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
            return ((ct0.flags) & bit_and);
        case 1:
            return ((ct1.flags) & bit_and);
        case 2:
            return ((ct2.flags) & bit_and);
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
            LED_OUT(i, 0);
        } else {//偶数のとき
            if (cnt[i] / 2 <= I[i] / 100) {//LED点滅回数のほうが電流より少ない間LED点灯
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
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Left Port");
            else I2C_LCD_Puts("LEFT PORT");
            break;
        case 1:
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Center Port");
            else I2C_LCD_Puts("CENTER PORT");
            break;
        case 2:
            if (auto_cut_ON[print_port]) I2C_LCD_Puts("Right Port");
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
            I2C_LCD_SetCursor(0, 1);
            my_utoa(str, charge_time[print_port] / 3600 / 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("d ");
            my_utoa(str, (charge_time[print_port] / 3600) % 24, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("h ");
            my_utoa(str, (charge_time[print_port] / 60) % 60, 2);
            I2C_LCD_Puts(str);
            I2C_LCD_Puts("m ");
            my_utoa(str, charge_time[print_port] % 60, 2);
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
        case ALWAYS_ON://Port Name, alwaysON
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Always Charging");
            break;
        case AUTO_STOP://Port Name, alwaysOFF
            display_port();
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts("Auto Stop ON");
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

//void print_time() {
//    ringbuf_t t;
//    char tbuf[100];
//    ringbuf_init(&t, tbuf, sizeof (tbuf));
//    ringbuf_pushs(&t, "\t");
//
//    uint8_t str[10];
//    my_utoa(&str, 20, 2);
//    if (edit_flag.flag.YY && halfsec)tx_sends("  ");
//    else tx_sends(str);
//
//    ringbuf_pushs(&t, "/");
//
//    my_utoa(&str, 20, 2);
//    if (edit_flag.flag.YY && halfsec)tx_sends("  ");
//    else tx_sends(str);
//
//    tx_send_dec(20, edit_flag.flag.YY);
//    tx_send_dec(caltime_now.YY, edit_flag.flag.YY);
//    tx_sends("/");
//    tx_send_dec(caltime_now.MM, edit_flag.flag.MM);
//    tx_sends("/");
//    tx_send_dec(caltime_now.DD, edit_flag.flag.DD);
//    tx_sends(" (");
//    tx_sends(weekday_char[caltime_now.EE]);
//    tx_sends(") ");
//    tx_send_dec(caltime_now.hh, edit_flag.flag.hh);
//    if (colon)tx_send(':');
//    else tx_send(' ');
//    tx_send_dec(caltime_now.mm, edit_flag.flag.mm);
//    tx_sends("-");
//    tx_send_dec(caltime_now.ss, edit_flag.flag.ss);
//    tx_send('\n');
//    GIE = 1;
//}

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
    tx_sends(weekday_char[caltime_now.EE]);
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
// command adjust time

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
// opcode opland1 opland2

void comm_d(uint8_t content, uint8_t port) {
    switch (content) {
        case 0:
            tx_sends("\t");
            tx_send((I[port] % 10000) / 1000 + '0');
            tx_send('.');
            tx_send((I[port] % 1000) / 100 + '0');
            tx_send((I[port] % 100) / 10 + '0');
            tx_send((I[port] % 10) / 1 + '0');
            tx_sends("A\n");
            break;
        case 1:
            tx_sends("\t");
            tx_sendn(S[port], 5);
            tx_sends("mAh\n");
            break;
        case 2:
            tx_sends("\t");
            char str[10];
            my_utoa(str, charge_time[port] / 3600 / 24, 2);
            tx_sends(str);
            tx_sends("d ");
            my_utoa(str, (charge_time[port] / 3600) % 24, 2);
            tx_sends(str);
            tx_sends("h ");
            my_utoa(str, (charge_time[port] / 60) % 60, 2);
            tx_sends(str);
            tx_sends("m ");
            my_utoa(str, charge_time[port] % 60, 2);
            tx_sends(str);
            tx_sends("s");
            break;
    }
}

void command_operation(char *opcode, char *opland1, char *opland2) {
    if (!my_strcmp(opcode, "help") || !my_strcmp(opcode, "?")) {
        tx_sends(
                "\t**** Charge Station 6 ---- Made by @Ryokeri ****\n"
                "\tcommand opeland1 opeland2\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tsettings(set) [port:left(l),center(c),right(r)]\n\t\t[auto_stop(as),always_on(ao),integrating_reset(ir)]\n"
                "\tdisplay(d) [port:left(l),center(c),right(r)]\n\t\t[content:current(c),integrated_current(ic),integrated_time(it)]\n"
                );
    }
    if (!my_strcmp(opcode, "settings") || !my_strcmp(opcode, "set")) {
        if (!my_strcmp(opland1, "auto_stop")) {
        }
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
    if (!my_strcmp(opcode, "display") || !my_strcmp(opcode, "d")) {
        if (!my_strcmp(opland1, "left") || !my_strcmp(opland1, "l")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_d(0, 0);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_d(1, 0);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_d(2, 0);
            }

        }
        if (!my_strcmp(opland1, "center") || !my_strcmp(opland1, "c")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_d(0, 1);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_d(1, 1);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_d(2, 1);
            }
        }
        if (!my_strcmp(opland1, "right") || !my_strcmp(opland1, "r")) {
            if (!my_strcmp(opland2, "current") || !my_strcmp(opland2, "c")) {
                comm_d(0, 2);
            }
            if (!my_strcmp(opland2, "integrated_current") || !my_strcmp(opland2, "ic")) {
                comm_d(1, 2);
            }
            if (!my_strcmp(opland2, "integrated_time") || !my_strcmp(opland2, "it")) {
                comm_d(2, 2);
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
                ringbuf_push(&comm_buf, '\0');
                tx_send('\t');
                tx_sendn(ringbuf_num(&comm_buf), 3);
                tx_sends("\n\n");
                char opcode[100];
                char opland1[100];
                char opland2[100];
                uint8_t i;
                for (i = 0; opcode[i] = ringbuf_pop(&comm_buf); i++);
                opcode[i] = '\0';
                for (i = 0; opland1[i] = ringbuf_pop(&comm_buf); i++);
                opland1[i] = '\0';
                for (i = 0; opland2[i] = ringbuf_pop(&comm_buf); i++);
                opland2[i] = '\0';
                command_operation(opcode, opland1, opland2);
                break;
            case ' ':
                ringbuf_push(&comm_buf, '\0');
                tx_send(' ');
                break;
            case '\b':
                ringbuf_backspace(&comm_buf);
                tx_sends("\b \b");
                break;
            case 0x7F:
                for (uint8_t i = 0; i < ringbuf_num(&comm_buf); i++) tx_sends("\b \b");
                ringbuf_delete(&comm_buf);
                break;
            default:
                if (ascii >= ' ' && ascii <= '~') {
                    ringbuf_push(&comm_buf, ascii);
                    tx_send(ascii);
                }
                break;
        }
    }
}

void port_loop(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        if (sw_flag_read(i, 0x0100)) {
            //sw_flag_clear(i, 0x0000);
            OUT(i, 1);
            LED_OUT(i, 1);
            cut_cnt[i] = 0;
            print_port = i;
            if (print_content == AUTO_STOP || print_content == ALWAYS_ON || print_content == RESETED || print_content == LOGO)print_content = CURRENT;
        }
        if (sw_flag_read(i, 0x0800)) {
            sw_flag_clear(i, 0x0000);
            print_content = RESET_;
            display_flag = 1;
        }
        if (sw_flag_read(i, 0x0008)) {
            sw_flag_clear(i, 0x0000);
            print_content = RESETED;
            display_flag = 1;
            S[i] = 0;
            s[i] = 0;
            charge_time[i] = 0;
            delay_set(&delay_display, 64);
        }
        if (sw_flag_read(i, 0x2000)) {
            sw_flag_clear(i, 0x0000);
            if (auto_cut_ON[i]) {
                print_content = AUTO_STOP;
            } else {
                print_content = ALWAYS_ON;
            }
            display_flag = 1;
        }
        if (sw_flag_read(i, 0x0020)) {
            sw_flag_clear(i, 0x0000);
            if (auto_cut_ON[i]) {
                auto_cut_ON[i] = 0;
                print_content = ALWAYS_ON;
                OUT(i, 1);
            } else {
                auto_cut_ON[i] = 1;
                print_content = AUTO_STOP;
            }
            display_flag = 1;
            delay_set(&delay_display, 64);
        }
        if (sw_flag_read(i, 0x8000)) {
            sw_flag_clear(i, 0x0000);
            print_content = NOTHING_DONE;
            display_flag = 1;
            delay_set(&delay_display, 64);
        }
    }
    if (delay_display.flag) {
        delay_display.flag = 0;
        print_content = LOGO;
        display_flag = 1;
    }
}

void ctmu_loop(void) {
    if (ctmu_flag) {
        ctmu_flag = 0;

        button_timer_interrupt(&ct0, !(CTMU_read(CTMU0) / ctmu_value0));
        button_timer_interrupt(&ct1, !(CTMU_read(CTMU1) / ctmu_value1));
        button_timer_interrupt(&ct2, !(CTMU_read(CTMU2) / ctmu_value2));
        button_timer_interrupt(&ctm, !(CTMU_read(CTMUM) / ctmu_valuem));
    }
}

void normal_mode_loop(void) {
    INTCONbits.GIE = 0;
    if (!edit_flag.flags) {
        port_loop();
        if (ctm.flag.press) {
            ctm.flags = 0;
            display_flag = 1;
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
    if (print_content == TIME)RTCC_adjust_time(&ctm, &ct0, &ct1);
    if (cut_time_flag) {
        cut_time_flag = 0;
        Auto_cut();
    }
    if (time_change_flag) {
        time_change_flag = 0;
        display_flag = 1;
    }
    if (display_flag) {
        display_flag = 0;
        display_LCD();
    }
}

void USB_loop(void) {
    //    char str[100];
    //    int rx_len;
    //    rx_len = get_string_usb(str, sizeof (str));
    //    if (rx_len) {
    //        while (put_string_usb(str, rx_len));
    //        rx_len = 0;
    //    }
    char data;
    int rx_len;
    rx_len = get_string_usb(&data, 1);
    if (rx_len) {
        ringbuf_push(&rx_buf, data);
    }
    if (ringbuf_num(&tx_buf)) {
        data = ringbuf_pop(&tx_buf);
        while (put_string_usb(&data, 1));
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
                LED_OUT(i, 0);
            }
            I2C_LCD_Clear();
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts("Charge Station 6");
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

#endif	/* PIC18F27J53_CHARGESTATION6_05_H */

