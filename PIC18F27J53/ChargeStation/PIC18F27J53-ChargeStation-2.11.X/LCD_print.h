/* 
 * File:   LCD_print.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 9:21
 */

#ifndef LCD_PRINT_H
#define	LCD_PRINT_H

#include <xc.h>
#include <stdint.h>

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

extern print_item_t print_item;
extern data_item_t data_item;
extern uint8_t print_port;
extern uint8_t display_flag;
extern uint8_t integrate_flag;
extern char display_char[2][20];

void display(print_item_t item, const char *str0, const char *str1);
void display_LCD(void);

#endif	/* LCD_PRINT_H */
