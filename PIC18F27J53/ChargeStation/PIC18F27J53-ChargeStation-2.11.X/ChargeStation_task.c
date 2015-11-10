#include "ChargeStation_task.h"

#include <stdio.h>
#include <stdlib.h>

#include <My_PIC.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include <My_usb_cdc.h>
#include <My_terminal.h>
#include "ctmu.h"
#include "io.h"
#include "LCD_print.h"
#include "settings.h"

port_t port[NUM_PORT];
uint8_t terminal_data_out;
uint8_t terminal_data_out_flag;

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
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        if (port[i].current > CUT_CURRENT)port[i].integrated_time++;
    }
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

void normal_loop(void) {
    // Settings or Port button
    if (settings_flag) {
        settings_loop();
    } else {
        if (ctmu_m.flag.press) {
            ctmu_m.flags = 0;
            display(PRINT_TIME, "", "");
        }
        if (ctmu_m.flag.long_holding_2) {
            ctmu_m.flags = 0;
            settings_flag = 1;
        }
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
        data_out(&usb_tx);
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
        I2C_LCD_Clear();
        I2C_LCD_SetCursor(0, 0);
        I2C_LCD_Puts("Charge Station 6");
        I2C_LCD_SetCursor(0, 1);
        I2C_LCD_Puts("SLEEPING NOW");
    }
    while (sleep_flag) {
        if (ADC(POWER_SW) > 2048) {
            sleep_flag = 0;
            display(LOGO, "Charge Station", "Welcome back!");
            break;
        }
        SLEEP();
        NOP();
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

void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!strcmp(op0, "help") || !strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\t*****************************\n"
                "\t**** Charge Station 6.12 ****\n"
                "\t**** Made by @Ryokeri14  ****\n"
                "\t*****************************\n\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tsettings(set) [port:left(l),center(c),right(r)]\n\t\t[auto_stop(as),always_on(ao),integrating_reset(ir)]\n"
                "\toutput_data(od) <- stopped by pressing the Enter key\n"
                "\ttouch [reset(r),initialize(init)] [value(%)]\n"
                "\n\tfor Developper\n"
                "\tRESET();\n"
                "\tbootload\n"
                );
    }
    terminal_time(tx, op0, op1, op2);
    if (!strcmp(op0, "RESET();")) {
        RESET();
    }
    if (!strcmp(op0, "bootload")) {
        bootload();
    }
    if (!strcmp(op0, "od") || !strcmp(op0, "output_data")) {
        terminal_data_out = 1;
    }
    if (!strcmp(op0, "")) {
        terminal_data_out = 0;
    }
    if (!strcmp(op0, "touch")) {
        if (!strcmp(op1, "initialize") || !strcmp(op1, "init")) {
            uint8_t percentage = atoi(op2);
            if (percentage <= 100) {
                ctmu_ratio = percentage;
                ctmu_set_ratio(ctmu_ratio);
                ringbuf_put_str(tx, "\tinitializing complete\n");
            } else {
                ringbuf_put_str(tx, "\tinvalid data\n\tinitializing failed\n");
            }
        }
        if (!strcmp(op1, "reset") || !strcmp(op1, "r")) {
            ctmu_set_ratio(ctmu_ratio);
            ringbuf_put_str(tx, "\tseting complete\n");
        }
    }
}

void data_out(ringbuf_t *tx) {
    char str[30];
    sprintf(str, "20%02d/%02d/%02d-%02d:%02d-%02d",
            now.YY,
            now.MM,
            now.DD,
            now.hh,
            now.mm,
            now.ss
            );
    ringbuf_put_str(tx, str);
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        static const char p[3][2] = {"L", "C", "R"};
        sprintf(str, " %s:%01d.%03dA,%06ldmAh",
                p[i],
                port[i].current / 1000,
                port[i].current % 1000,
                port[i].integrated_current
                );
        ringbuf_put_str(tx, str);
    }
    ringbuf_put_str(tx, "\n");
}
