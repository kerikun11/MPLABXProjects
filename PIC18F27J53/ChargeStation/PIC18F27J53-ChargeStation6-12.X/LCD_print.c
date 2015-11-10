#include "LCD_print.h"

#include <stdio.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include "ChargeStation_task.h"

print_item_t print_item;
data_item_t data_item;
uint8_t print_port;
uint8_t display_flag;
uint8_t integrate_flag;
char display_char[2][20];

void display(print_item_t item, const char *str0, const char *str1) {
    print_item = item;
    uint8_t i;
    // ‚à‚µƒkƒ‹•¶Žš‚¾‚¯‚È‚ç‘‚«‚©‚¦‚È‚¢
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
        {
            char str[2][20];
            display_time_1602(&now, str[0], str[1]);
            I2C_LCD_SetCursor(0, 0);
            I2C_LCD_Puts(str[0]);
            I2C_LCD_SetCursor(0, 1);
            I2C_LCD_Puts(str[1]);
        }
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
                case INTEGRATED_TIME://Port Name, 
                    sprintf(str, "%02ldd %02ldh %02ldm %02lds",
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
