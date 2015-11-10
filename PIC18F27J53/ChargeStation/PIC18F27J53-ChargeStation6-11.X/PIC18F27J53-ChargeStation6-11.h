/* 
 * File:   PIC18F27J53-ChargeStation6-11.h
 * Author: kerikun11
 *
 * Created on 2015/09/16, 9:35
 */

#ifndef PIC18F27J53_CHARGESTATION6_11_H
#define	PIC18F27J53_CHARGESTATION6_11_H

// Number
#define CUT_CURRENT 100  // [mA]
#define CUT_TIME    6    // [s]

// Hardware Mapping
#define CTMU0 0 // RA0
#define CTMU1 1 // RA1
#define CTMU2 2 // RA2
#define CTMUM 3 // RA3

#define POWER_SW 12 // AN12,PORTBbits.RB0

#define ADC0 8  // AN8
#define ADC1 9  // AN9
#define ADC2 10 // AN10

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATC2

// Port Mapping
#define NUM_PORT    3
#define PORT_L      0
#define PORT_C      1
#define PORT_R      2

typedef enum PRINT_ITEM {
    LOGO,
    PRINT_TIME,
    PRINT_DATA,
    SETTINGS
} print_item_t;

typedef enum DATA_ITEM {
    CURRENT,
    INTEGRATED_CURRENT,
    INTEGRATED_TIME
} data_item_t;

typedef enum SETTINGS_ITEM {
    SELECT,
    ADJUST_TIME,
    TOGGLE_AUTO_STOP,
    TOGGLE_LED_INDICATOR,
    INTEGRATING_RESET
} settings_item_t;

typedef struct {
    button_t ctmu;
    uint16_t ctmu_value;
    uint16_t current;
    uint32_t integrated_current_sec;
    uint32_t integrated_current;
    uint32_t integrated_time;
    uint16_t cut_cnt;

    union {
        uint8_t flags;

        struct {
            uint8_t auto_cut_ON : 1;
            uint8_t led_indicator_ON : 1;
            uint8_t out_flag : 1;
            uint8_t led_flag : 1;
        } flag;
    };
} port_t;

port_t port[NUM_PORT];

button_t ctmu_m;
uint16_t ctmu_value_m;
uint8_t ctmu_ratio;
uint8_t ctmu_sampling_flag;

print_item_t print_item;
data_item_t data_item;
uint8_t print_port;
uint8_t display_flag;
uint8_t integrate_flag;
settings_item_t settings_item;
uint8_t settings_flag = 0;
char display_char[2][20];

uint8_t cut_time_flag;
uint8_t terminal_data_out;
uint8_t terminal_data_out_flag;

// ringbuffer of usb tx/rx
ringbuf_t usb_tx;
ringbuf_t usb_rx;

// Power Output

void OUT(uint8_t b, uint8_t value) {
    port[b].flag.out_flag = value;
    switch (b) {
        case PORT_L:
            OUT0 = value;
            break;
        case PORT_C:
            OUT1 = value;
            break;
        case PORT_R:
            OUT2 = value;
            break;
    }
}
// return analog pin number

uint8_t ANALOG_IN(uint8_t b) {
    switch (b) {
        case PORT_L:
            return ADC0;
        case PORT_C:
            return ADC1;
        case PORT_R:
            return ADC2;
    }
    return 0;
}
// LED Output

void LED_output(uint8_t b, uint8_t value) {
    port[b].flag.led_flag = value;
    switch (b) {
        case PORT_L:
            LED0 = value;
            break;
        case PORT_C:
            LED1 = value;
            break;
        case PORT_R:
            LED2 = value;
            break;
    }
}
// 充電中に充電電流に応じて各ポートのLEDを点滅させる

void LED_indicator(void) {
    uint8_t i;
    static uint8_t cnt[3];
    static uint8_t cntf[3];
    for (i = 0; i < NUM_PORT; i++) {
        // LED_indicatorがONのとき
        if (port[i].flag.led_indicator_ON) {
            cnt[i]++;
            if (cnt[i] % 2 == 1) {//奇数ならLEDは消灯
                LED_output(i, 0);
            } else {//偶数のとき
                if (cnt[i] / 2 <= port[i].current / 100) {//LED点滅回数のほうが電流より少ない間LED点灯
                    LED_output(i, 1);
                    cntf[i] = 0; //フラグリセット
                } else { // LEDの点滅回数のほうが電流より多くなったときフラグ加算
                    cntf[i]++;
                    LED_output(i, 0);
                    if (cntf[i] >= 2) {//フラグが2になったら、元に戻る
                        cnt[i] = 0;
                    }
                }
            }
        }
    }
}
// Auto cut each port

void Auto_cut(void) {
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        // ADC sampling
        port[i].current = 13 * ADC(ANALOG_IN(i)) / 16; // *13/16
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
// integrate currents of each port

void integrate_current(void) {
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        if (port[i].current > CUT_CURRENT) {
            port[i].integrated_current_sec += (uint32_t) (port[i].current);
            port[i].integrated_current = (uint32_t) (port[i].integrated_current_sec) / 3600;
        }
    }
}

void integrate_time(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        if (port[i].current > CUT_CURRENT)port[i].integrated_time++;
    }
}

void display(print_item_t item, const char *str0, const char *str1) {
    print_item = item;
    uint8_t i;
    // もしヌル文字だけなら書きかえない
    if (*str0) {
        for (i = 0; *str0; i++) {
            display_char[0][i] = *str0++;
        }
        display_char[0][i] = '\0';
    }
    if (*str1) {
        for (i = 0; *str1; i++) {
            display_char[1][i] = *str1++;
        }
        display_char[1][i] = '\0';
    }
    display_flag = 1;
}

void display_LCD(void) {
    I2C_LCD_Clear();
    switch (print_item) {
        case LOGO:
        case SETTINGS:
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts(display_char[0]);
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts(display_char[1]);
            break;
        case PRINT_TIME:
            display_time_1602(&caltime_now, &epoch_now);
            break;
        case PRINT_DATA:
        {
            char str[20];
            static const char port_char[2][3][20] = {
                {"LEFT   PORT", "CENTER PORT", "RIGHT  PORT"},
                {"Left   Port", "Center Port", "Right  Port"}
            };
            static const char onoff[2][5] = {" OFF", " ON "};
            sprintf(str, "%s %s", port_char[port[print_port].flag.auto_cut_ON][print_port],
                    onoff[(port[print_port].current > CUT_CURRENT)]);
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts(str);
            switch (data_item) {
                case CURRENT://Port Name, x.xxxA
                    sprintf(str, "%01d.%03dA", port[print_port].current / 1000, port[print_port].current % 1000);
                    break;
                case INTEGRATED_CURRENT://Port Name, xxxxxmAh
                    sprintf(str, "%06ldmAh", port[print_port].integrated_current);
                    break;
                case INTEGRATED_TIME://Port Name, xxxxxmAh
                    sprintf(str, "%02dd %02dh %02dm %02ds",
                            port[print_port].integrated_time / 3600 / 24,
                            (port[print_port].integrated_time / 3600) % 24,
                            (port[print_port].integrated_time / 60) % 60,
                            port[print_port].integrated_time % 60);
                    break;
            }
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts(str);
        }
            break;
    }
}

//void display_reserve(print_item_t next_item, uint16_t time) {
//    next_print_item = next_item;
//}
//
//void display_now(print_item_t pres_item) {
//    print_item = pres_item;
//    display_flag = 1;
//}

void ctmu_set_ratio(uint8_t percentage) {
    port[0].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU0) / 100;
    port[1].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU1) / 100;
    port[2].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU2) / 100;
    ctmu_value_m = (uint16_t) percentage * CTMU_read(CTMUM) / 100;
}

void command_get_data(ringbuf_t *tx, data_item_t item, uint8_t i) {
    switch (item) {
        case CURRENT:
            ringbuf_put_str(tx, "\t");
            ringbuf_put(tx, (port[i].current % 10000) / 1000 + '0');
            ringbuf_put(tx, '.');
            ringbuf_put(tx, (port[i].current % 1000) / 100 + '0');
            ringbuf_put(tx, (port[i].current % 100) / 10 + '0');
            ringbuf_put(tx, (port[i].current % 10) / 1 + '0');
            ringbuf_put_str(tx, "A\n");
            break;
        case INTEGRATED_CURRENT:
            ringbuf_put_str(tx, "\t");
            ringbuf_put_num(tx, port[i].integrated_current, 5);
            ringbuf_put_str(tx, "mAh\n");
            break;
        case INTEGRATED_TIME:
            ringbuf_put_str(tx, "\t");
            char str[10];
            my_utoa(str, port[i].integrated_time / 3600 / 24, 2);
            ringbuf_put_str(tx, str);
            ringbuf_put_str(tx, "d ");
            my_utoa(str, (port[i].integrated_time / 3600) % 24, 2);
            ringbuf_put_str(tx, str);
            ringbuf_put_str(tx, "h ");
            my_utoa(str, (port[i].integrated_time / 60) % 60, 2);
            ringbuf_put_str(tx, str);
            ringbuf_put_str(tx, "m ");
            my_utoa(str, port[i].integrated_time % 60, 2);
            ringbuf_put_str(tx, str);
            ringbuf_put_str(tx, "s");
            break;
    }
}
// Go to bootloader program

void bootload(void) {
    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("PIC18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("Bootloader mode");
    asm("goto   0x001C");
}

void command_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!my_strcmp(op0, "help") || !my_strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\t****************************\n"
                "\t**** Charge Station 6.7 ****\n"
                "\t**** Made by @Ryokeri   ****\n"
                "\t****************************\n\n"
                "\tcommand \topeland1\topeland2\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tsettings(set) [port:left(l),center(c),right(r)]\n\t\t[auto_stop(as),always_on(ao),integrating_reset(ir)]\n"
                "\tdisplay(d) [port:left(l),center(c),right(r)]\n\t\t[item:current(c),integrated_current(ic),integrated_time(it)]\n"
                "\toutput_data(od) <- stopped by pressing the Enter key\n"
                "\ttouch [reset(r),initialize(init)] [value(%)]\n"
                "\n\tfor Developper\n"
                "\tRESET();\n"
                "\tbootload\n"
                );
    }
    command_time(tx, op0, op1, op2);
    if (!my_strcmp(op0, "RESET();")) {
        RESET();
    }
    if (!my_strcmp(op0, "bootload")) {
        bootload();
    }
    if (!my_strcmp(op0, "od") || !my_strcmp(op0, "output_data")) {
        terminal_data_out = 1;
    }
    if (!my_strcmp(op0, "")) {
        terminal_data_out = 0;
    }
    if (!my_strcmp(op0, "touch")) {
        if (!my_strcmp(op1, "initialize") || !my_strcmp(op1, "init")) {
            uint8_t percentage = my_atoi(op2);
            if (percentage <= 100) {
                ctmu_ratio = percentage;
                ctmu_set_ratio(ctmu_ratio);
                ringbuf_put_str(tx, "\tinitializing complete\n");
            } else {
                ringbuf_put_str(tx, "\tinvalid data\n\tinitializing failed\n");
            }
        }
        if (!my_strcmp(op1, "reset") || !my_strcmp(op1, "r")) {
            ctmu_set_ratio(ctmu_ratio);
            ringbuf_put_str(tx, "\tseting complete\n");
        }
    }
    if (!my_strcmp(op0, "display") || !my_strcmp(op0, "d")) {
        if (!my_strcmp(op1, "help") || !my_strcmp(op1, "?")) {
            ringbuf_put_str(tx, "\tleft(l) or center(c) or right(r)\n");
        }
        if (!my_strcmp(op1, "left") || !my_strcmp(op1, "l")) {
            if (!my_strcmp(op2, "help") || !my_strcmp(op2, "?")) {
                ringbuf_put_str(tx, "\tcurrent(c) or integrated_current(ic) or integrated_time(it)\n");
            }
            if (!my_strcmp(op2, "current") || !my_strcmp(op2, "c")) {
                command_get_data(tx, CURRENT, PORT_L);
            }
            if (!my_strcmp(op2, "integrated_current") || !my_strcmp(op2, "ic")) {
                command_get_data(tx, INTEGRATED_CURRENT, PORT_L);
            }
            if (!my_strcmp(op2, "integrated_time") || !my_strcmp(op2, "it")) {
                command_get_data(tx, INTEGRATED_TIME, PORT_L);
            }
        }
        if (!my_strcmp(op1, "center") || !my_strcmp(op1, "c")) {
            if (!my_strcmp(op2, "help") || !my_strcmp(op2, "?")) {
                ringbuf_put_str(tx, "\tcurrent(c) or integrated_current(ic) or integrated_time(it)\n");
            }
            if (!my_strcmp(op2, "current") || !my_strcmp(op2, "c")) {
                command_get_data(tx, CURRENT, PORT_C);
            }
            if (!my_strcmp(op2, "integrated_current") || !my_strcmp(op2, "ic")) {
                command_get_data(tx, INTEGRATED_CURRENT, PORT_C);
            }
            if (!my_strcmp(op2, "integrated_time") || !my_strcmp(op2, "it")) {
                command_get_data(tx, INTEGRATED_TIME, PORT_C);
            }
        }
        if (!my_strcmp(op1, "right") || !my_strcmp(op1, "r")) {
            if (!my_strcmp(op2, "help") || !my_strcmp(op2, "?")) {
                ringbuf_put_str(tx, "\tcurrent(c) or integrated_current(ic) or integrated_time(it)\n");
            }
            if (!my_strcmp(op2, "current") || !my_strcmp(op2, "c")) {
                command_get_data(tx, CURRENT, PORT_R);
            }
            if (!my_strcmp(op2, "integrated_current") || !my_strcmp(op2, "ic")) {
                command_get_data(tx, INTEGRATED_CURRENT, PORT_R);
            }
            if (!my_strcmp(op2, "integrated_time") || !my_strcmp(op2, "it")) {
                command_get_data(tx, INTEGRATED_TIME, PORT_R);
            }
        }
    }
}
// タッチセンサのサンプリング

void ctmu_sampling(void) {
    button_timer_interrupt(&port[0].ctmu, !(CTMU_read(CTMU0) / port[0].ctmu_value));
    button_timer_interrupt(&port[1].ctmu, !(CTMU_read(CTMU1) / port[1].ctmu_value));
    button_timer_interrupt(&port[2].ctmu, !(CTMU_read(CTMU2) / port[2].ctmu_value));
    button_timer_interrupt(&ctmu_m, !(CTMU_read(CTMUM) / ctmu_value_m));
}

void ctmu_loop(void) {
    if (ctmu_sampling_flag) {
        ctmu_sampling_flag = 0;
        ctmu_sampling();
    }
}

void data_out(void) {
    char str[30];
    sprintf(str, "20%02d/%02d/%02d-%02d:%02d-%02d",
            caltime_now.YY,
            caltime_now.MM,
            caltime_now.DD,
            caltime_now.hh,
            caltime_now.mm,
            caltime_now.ss
            );
    ringbuf_put_str(&usb_tx, str);
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        static const char p[3][2] = {"L", "C", "R"};
        sprintf(str, " %s:%01d.%03dA,%06ldmAh",
                p[i],
                port[i].current / 1000,
                port[i].current % 1000,
                port[i].integrated_current
                );
        ringbuf_put_str(&usb_tx, str);
    }
    ringbuf_put_str(&usb_tx, "\n");
}

void port_button_loop(void) {
    uint8_t i;
    for (i = 0; i < NUM_PORT; i++) {
        // ボタンが押されていたらLED点灯
        if (port[i].ctmu.flag.pressing) {
            LED_output(i, 1);
        } else if (port[i].flag.led_indicator_ON == 0 && port[i].flag.led_flag == 1) {
            LED_output(i, 0);
        }
        // シングルタップ
        if (port[i].ctmu.flag.press) {
            port[i].ctmu.flags = 0;
            LED_output(i, 0);
            // 表示ポートと一致していれば、表示循環
            // 表示ポートと一致していなければ、一致させる
            if (print_port == i) {
                switch (data_item) {
                    case CURRENT:
                        data_item = INTEGRATED_CURRENT;
                        break;
                    case INTEGRATED_CURRENT:
                        data_item = INTEGRATED_TIME;
                        break;
                    case INTEGRATED_TIME:
                    default:
                        data_item = CURRENT;
                        break;
                }
            } else {
                print_port = i;
            }
            display(PRINT_DATA, "", "");
            // 充電開始
            OUT(i, 1);
            port[i].cut_cnt = 0;
        }
    }
}

uint8_t settings_adjust_time(void) {
    static uint8_t state = 0;
    switch (state) {
        case 0:
            display(PRINT_TIME, "", "");
            RTCC_adjust_time_toggle();
            state = 1;
            break;
        case 1:
            if (port[1].ctmu.flag.press) {
                port[1].ctmu.flag.press = 0;
                RTCC_adjust_time_cursor();
            }
            if (port[2].ctmu.flag.press) {
                port[2].ctmu.flag.press = 0;
                RTCC_adjust_time_inc(&caltime_now, &epoch_now);
            }
            if (port[0].ctmu.flag.press) {
                port[0].ctmu.flag.press = 0;
                RTCC_adjust_time_dec(&caltime_now, &epoch_now);
            }
            break;
        default:
            break;
    }
    if (ctmu_m.flag.press) {
        ctmu_m.flags = 0;
        edit_flag.flags = 0;
        state = 0;
        settings_flag = 0;
        display(PRINT_TIME, "", "");
        return 1;
    }
    return 0;
}

uint8_t settings_auto_stop(void) {
    static uint8_t state = 0;
    switch (state) {
        case 0:
        {
            char str[20];
            char *strp;
            strp = str;
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                if (port[i].flag.auto_cut_ON)strcpy(strp, " ON  ");
                else strcpy(strp, " OFF ");
                strp += 5;
            }
            display(SETTINGS, "Left Centr Right", str);
            state = 1;
        }
            break;
        case 1:
            for (uint8_t j = 0; j < NUM_PORT; j++) {
                if (port[j].ctmu.flag.press) {
                    port[j].ctmu.flags = 0;
                    port[j].flag.auto_cut_ON = !port[j].flag.auto_cut_ON;
                    char str[20];
                    char *strp;
                    strp = str;
                    for (uint8_t i = 0; i < NUM_PORT; i++) {
                        if (port[i].flag.auto_cut_ON)strcpy(strp, " ON  ");
                        else strcpy(strp, " OFF ");
                        strp += 5;
                    }
                    display(SETTINGS, "", str);
                }
            }
            break;
        default:
            break;
    }
    if (ctmu_m.flag.press) {
        ctmu_m.flags = 0;
        state = 0;
        settings_flag = 0;
        display(PRINT_TIME, "", "");
        return 1;
    }
    return 0;
}

uint8_t settings_led_indicator(void) {
    static uint8_t state = 0;
    switch (state) {
        case 0:
        {
            char str[20];
            char *strp;
            strp = str;
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                if (port[i].flag.led_indicator_ON)strcpy(strp, " ON  ");
                else strcpy(strp, " OFF ");
                strp += 5;
            }
            display(SETTINGS, "Left Centr Right", str);
            state = 1;
        }
            break;
        case 1:
            for (uint8_t j = 0; j < NUM_PORT; j++) {
                if (port[j].ctmu.flag.press) {
                    port[j].ctmu.flags = 0;
                    port[j].flag.led_indicator_ON = !port[j].flag.led_indicator_ON;
                    LED_output(j, 0);
                    char str[20];
                    char *strp;
                    strp = str;
                    for (uint8_t i = 0; i < NUM_PORT; i++) {
                        if (port[i].flag.led_indicator_ON)strcpy(strp, " ON  ");
                        else strcpy(strp, " OFF ");
                        strp += 5;
                    }
                    display(SETTINGS, "", str);
                }
            }
            break;
        default:
            break;
    }
    if (ctmu_m.flag.press) {
        ctmu_m.flags = 0;
        state = 0;
        settings_flag = 0;
        display(PRINT_TIME, "", "");
        return 1;
    }
    return 0;
}

uint8_t settings_integrating_reset(void) {
    static uint8_t state = 0;
    switch (state) {
        case 0:
        {
            char str[20];
            char *strp;
            strp = str;
            for (uint8_t i = 0; i < NUM_PORT; i++) {
                if (port[i].integrated_current)strcpy(strp, " yet ");
                else strcpy(strp, "  0  ");
                strp += 5;
            }
            display(SETTINGS, "Left Centr Right", str);
            state = 1;
        }
            break;
        case 1:
            for (uint8_t j = 0; j < NUM_PORT; j++) {
                if (port[j].ctmu.flag.press) {
                    port[j].ctmu.flags = 0;
                    port[j].integrated_current_sec = 0;
                    port[j].integrated_current = 0;
                    port[j].integrated_time = 0;
                    char str[20];
                    char *strp;
                    strp = str;
                    for (uint8_t i = 0; i < NUM_PORT; i++) {
                        if (port[i].integrated_current)strcpy(strp, " yet ");
                        else strcpy(strp, "  0  ");
                        strp += 5;
                    }
                    display(SETTINGS, "", str);
                }
            }
            break;
        default:
            break;
    }
    if (ctmu_m.flag.press) {
        ctmu_m.flags = 0;
        state = 0;
        settings_flag = 0;
        display(PRINT_TIME, "", "");
        return 1;
    }
    return 0;
}

void settings_loop(void) {
    static uint8_t settings_state = 0;
    switch (settings_state) {
        case 0:
            settings_item = SELECT;
            display(SETTINGS, "Settings", "<-   Select   ->");
            settings_state += 1;
            break;
        case 1:
        {
            uint8_t item_change_flag = 0;
            if (port[PORT_R].ctmu.flag.press) {
                port[PORT_R].ctmu.flags = 0;
                if (settings_item == INTEGRATING_RESET)settings_item = SELECT;
                else settings_item++;
                item_change_flag = 1;
            }
            if (port[PORT_L].ctmu.flag.press) {
                port[PORT_L].ctmu.flags = 0;
                if (settings_item == SELECT)settings_item = INTEGRATING_RESET;
                else settings_item--;
                item_change_flag = 1;
            }
            if (item_change_flag) {
                switch (settings_item) {
                    case SELECT:
                        display(SETTINGS, "Settings", "<-   Select   ->");
                        break;
                    case ADJUST_TIME:
                        display(SETTINGS, "Settings", "Adjust the Time");
                        break;
                    case TOGGLE_AUTO_STOP:
                        display(SETTINGS, "Settings", "Toggle Auto Stop");
                        break;
                    case TOGGLE_LED_INDICATOR:
                        display(SETTINGS, "Settings", "Toggle LED Lamp");
                        break;
                    case INTEGRATING_RESET:
                        display(SETTINGS, "Settings", "Integrat Reset");
                        break;
                }
            }
            if (port[PORT_C].ctmu.flag.press) {
                port[PORT_C].ctmu.flags = 0;
                settings_state += 1;
            }
        }
            break;
        case 2:
            switch (settings_item) {
                case SELECT:
                    settings_state = 1;
                    break;
                case ADJUST_TIME:
                    if (settings_adjust_time()) {
                        settings_state = 0;
                    }
                    break;
                case TOGGLE_AUTO_STOP:
                    if (settings_auto_stop()) {
                        settings_state = 0;
                    }
                    break;
                case TOGGLE_LED_INDICATOR:
                    if (settings_led_indicator()) {
                        settings_state = 0;
                    }
                    break;
                case INTEGRATING_RESET:
                    if (settings_integrating_reset()) {
                        settings_state = 0;
                    }
                    break;
                default:
                    break;
            }
            break;
    }
}

void normal_loop(void) {
    // Settings or Port button
    if (ctmu_m.flag.long_holding_1) {
        ctmu_m.flags = 0;
        settings_flag = 1;
    }
    if (settings_flag) {
        settings_loop();
    } else {
        port_button_loop();
    }
    // cut_time_flag <- timer1 
    if (cut_time_flag) {
        cut_time_flag = 0;
        Auto_cut();
    }
    // Integrating every 1 second
    if (integrate_flag) {
        integrate_flag = 0;
        integrate_current();
        integrate_time();
    }
    // time_change_flag <- RTCC_loop or adjust_time
    if (time_change_flag) {
        time_change_flag = 0;
        if (print_item == PRINT_TIME)display_flag = 1;
    }
    // display
    if (display_flag) {
        display_flag = 0;
        display_LCD();
    }
    // Serial Data Out
    if (terminal_data_out && terminal_data_out_flag) {
        terminal_data_out_flag = 0;
        data_out();
    }
}

void USB_loop(void) {
    char data;
    int rx_len;
    rx_len = get_string_usb(&data, 1);
    if (rx_len) {
        ringbuf_put(&usb_rx, data);
    }
    if (ringbuf_num(&usb_tx)) {
        data = ringbuf_pop(&usb_tx);
        while (put_string_usb(&data, 1));
    }
}

void sleep_loop(void) {
    static uint8_t sleep_flag = 0;
    if (ADC(POWER_SW) < 2048) {
        sleep_flag = 1;
        INTCONbits.GIE = 0;
        for (uint8_t i = 0; i < NUM_PORT; i++) {
            OUT(i, 0);
            LED_output(i, 0);
        }
        UCONbits.USBEN = 0;
        I2C_LCD_Clear();
        I2C_LCD_SetCursor(0, 0);
        I2C_LCD_Puts("Charge Station 6");
        I2C_LCD_SetCursor(0, 1);
        I2C_LCD_Puts("SLEEPING NOW");
    }
    while (sleep_flag) {
        if (ADC(POWER_SW) > 2048) {
            sleep_flag = 0;
            UCONbits.USBEN = 1;
            display(LOGO, "Charge Station", "Welcome back!");
            break;
        }
        SLEEP();
        NOP();
    }
}

#endif	/* PIC18F27J53_CHARGESTATION6_11_H */

