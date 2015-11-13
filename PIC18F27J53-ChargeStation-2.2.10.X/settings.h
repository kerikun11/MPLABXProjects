/* 
 * File:   settings.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 9:23
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include <xc.h>
#include <stdint.h>

typedef enum SETTINGS_ITEM {
    SELECT,
    ADJUST_TIME,
    TOGGLE_AUTO_STOP,
    TOGGLE_LED_INDICATOR,
    INTEGRATING_RESET
} settings_item_t;

extern settings_item_t settings_item;
extern uint8_t settings_flag;

uint8_t settings_adjust_time(void);
uint8_t settings_auto_stop(void);
uint8_t settings_led_indicator(void);
uint8_t settings_integrating_reset(void);
void settings_task(void);

#endif	/* SETTINGS_H */
