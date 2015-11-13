#include "settings.h"

#include <string.h>
#include <My_RTCC.h>
#include <My_button.h>
#include "ChargeStation_task.h"
#include "ctmu.h"
#include "LCD_print.h"

settings_item_t settings_item;
uint8_t settings_flag = 0;

uint8_t settings_adjust_time(void) {
    static uint8_t state = 0;
    switch (state) {
        case 0:
            display(PRINT_TIME, "", "");
            RTCC_adjust_time_toggle(&now);
            state = 1;
            break;
        case 1:
            if (port[1].ctmu.flag.press) {
                port[1].ctmu.flag.press = 0;
                RTCC_adjust_time_cursor(&now);
            }
            if (port[2].ctmu.flag.press) {
                port[2].ctmu.flag.press = 0;
                RTCC_adjust_time_inc(&now);
            }
            if (port[0].ctmu.flag.press) {
                port[0].ctmu.flag.press = 0;
                RTCC_adjust_time_dec(&now);
            }
            break;
        default:
            break;
    }
    if (ctmu_m.flag.press) {
        ctmu_m.flags = 0;
        now.edit.flags = 0;
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

void settings_task(void) {
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
            if (ctmu_m.flag.press) {
                ctmu_m.flags = 0;
                settings_state = 0;
                settings_flag = 0;
                display(PRINT_TIME, "", "");
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
