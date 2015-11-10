/* 
 * File:   My_button.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:19
 */

#ifndef MY_BUTTON_H
#define	MY_BUTTON_H

//*************************** button ***************************//
//タイマー割り込み関数にbutton_timer_interrupt(&button_t,!SW)を書いておくこと。
// 48MHz, 16bit, prescaler=1:4

#define PRESS_LEVEL 2
#define LONG_HOLD_LEVEL1  16
#define LONG_HOLD_LEVEL2  60
#define LONG_HOLD_LEVEL3  150
#define LONG_HOLD_LEVEL4  300
#define LONG_HOLD_LEVEL5  500
#define LONG_HOLD_LEVEL6  700
#define LONG_HOLD_LEVEL7  900

typedef struct button {
    uint16_t cnt_sw;

    union {
        uint16_t flags;

        struct {
            uint8_t press : 1;
            uint8_t long_hold_1 : 1;
            uint8_t long_hold_2 : 1;
            uint8_t long_hold_3 : 1;
            uint8_t long_hold_4 : 1;
            uint8_t long_hold_5 : 1;
            uint8_t long_hold_6 : 1;
            uint8_t long_hold_7 : 1;
            uint8_t pressing : 1;
            uint8_t long_holding_1 : 1;
            uint8_t long_holding_2 : 1;
            uint8_t long_holding_3 : 1;
            uint8_t long_holding_4 : 1;
            uint8_t long_holding_5 : 1;
            uint8_t long_holding_6 : 1;
            uint8_t long_holding_7 : 1;
        } flag;
    };
} button_t;

void button_timer_interrupt(button_t *bt, uint8_t sw_value) {
    if (sw_value) {
        if (bt->cnt_sw == LONG_HOLD_LEVEL7)bt->flag.long_holding_7 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL6)bt->flag.long_holding_6 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL5)bt->flag.long_holding_5 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL4)bt->flag.long_holding_4 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL3)bt->flag.long_holding_3 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL2)bt->flag.long_holding_2 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL1)bt->flag.long_holding_1 = 1;
        if (bt->cnt_sw == PRESS_LEVEL)bt->flag.pressing = 1;
        if (bt->cnt_sw < LONG_HOLD_LEVEL7 + 1) bt->cnt_sw++;
    } else {
        if (bt->cnt_sw >= LONG_HOLD_LEVEL7)bt->flag.long_hold_7 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL6)bt->flag.long_hold_6 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL5)bt->flag.long_hold_5 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL4)bt->flag.long_hold_4 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL3)bt->flag.long_hold_3 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL2)bt->flag.long_hold_2 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL1)bt->flag.long_hold_1 = 1;
        else if (bt->cnt_sw >= PRESS_LEVEL)bt->flag.press = 1;
        bt->cnt_sw = 0;
        bt->flags &= 0x00FF;
    }
}

#endif	/* MY_BUTTON_H */

