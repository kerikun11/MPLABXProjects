#include "My_button.h"

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
