/* 
 * File:   My_RTCC.h
 * Author: kerikun11
 *
 * Created on 2015/03/19, 0:02
 */
#include <My_button.h>

#ifndef MY_RTCC_H
#define	MY_RTCC_H
// PIC18F27J53用リアルタイムクロックプログラム
// main_init に RTCC_init(); を書くこと。
// mainループに RTCC_loop(); を書くこと。

typedef struct {

    union {
        uint8_t flags;

        struct {
            uint8_t ss : 1;
            uint8_t mm : 1;
            uint8_t hh : 1;
            uint8_t DD : 1;
            uint8_t MM : 1;
            uint8_t YY : 1;
        } flag;
    };
} edit_flag_t;

typedef struct {
    uint8_t ss;
    uint8_t mm;
    uint8_t hh;
    uint8_t EE;
    uint8_t DD;
    uint8_t MM;
    uint8_t YY;
} caltime_t;
typedef uint32_t epoch_t; // 2000/01/01(6)00:00-00

const char weekday_3char[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
//const char *weekday_char_full[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Fryday", "Saturday"};

epoch_t epoch_now;
caltime_t caltime_now;
edit_flag_t edit_flag;
uint8_t colon;
uint8_t time_change_flag;
uint8_t halfsec;

#define MINUTE ((epoch_t)60)
#define HOUR ((epoch_t)60*60)
#define DAY ((epoch_t)60*60*24)

void RTCC_init(void) {
    RTCCFGbits.RTCWREN = 1;
    if (RTCCFGbits.RTCWREN != 1) {
        EECON2 = 0x55;
        EECON2 = 0xAA;
        RTCCFGbits.RTCWREN = 1;
    }
    RTCCFGbits.RTCEN = 1;
    RTCCFGbits.RTCOE = 0;
    PADCFG1bits.RTSECSEL0 = 1;
    PADCFG1bits.RTSECSEL1 = 1;
    RTCCAL = 0x00;
}

/********************************** necessary functions **********************************/
// from decimal to hex

uint8_t d_to_x(uint8_t dec) {
    // uint8_t quot = dec / 10;
    // return quot * 16 + dec - quot * 10;
    return dec / 10 * 6 + dec;
}

// from hex to decimal

uint8_t x_to_d(uint8_t hex) {
    return 10 * (0x0F & (hex >> 4)) + (0x0F & hex);
}

// return month length

uint8_t month_length(uint8_t year, uint8_t month) {
    if (month == 2) return 28 + !(year & 3)-!(year % 100)+!(year % 400);
    else return 31 - (((-(month & 1)^month)&13) == 4);

    //    switch (month) {
    //        case 1:
    //        case 3:
    //        case 5:
    //        case 7:
    //        case 8:
    //        case 10:
    //        case 12:
    //            return 31;
    //        case 4:
    //        case 6:
    //        case 9:
    //        case 11:
    //            return 30;
    //        case 2:
    //            if (year % 400 == 0)return 29;
    //            else if (year % 100 == 0)return 28;
    //            else if (year % 4 == 0) return 29;
    //            else return 28;
}

epoch_t get_quot_rem(epoch_t *quot, uint8_t div) {
    // num /= div;
    // return rem;
    epoch_t num = *quot;
    return num - (*quot = num / div) * div; // returns rem(余り)
}

/********************************** Transform time **********************************/

void RTCC_to_caltime(caltime_t *ct) {
    while (RTCCFGbits.RTCSYNC);

    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 1;

    ct->YY = x_to_d(RTCVALL); // YY
    uint8_t dumy = RTCVALH; // Reserved
    ct->DD = x_to_d(RTCVALL); // DD
    ct->MM = x_to_d(RTCVALH); // MM
    ct->hh = x_to_d(RTCVALL); // hh
    ct->EE = x_to_d(RTCVALH); // EE
    ct->ss = x_to_d(RTCVALL); // ss
    ct->mm = x_to_d(RTCVALH); // mm
}

void caltime_to_RTCC(caltime_t *ct) {
    while (RTCCFGbits.RTCSYNC);
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 1;
    RTCVALL = d_to_x(ct->YY);
    RTCVALH = 0x00;
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 1;
    RTCVALL = d_to_x(ct->DD);
    RTCVALH = d_to_x(ct->MM);
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = d_to_x(ct->hh);
    RTCVALH = d_to_x(ct->EE);
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = d_to_x(ct->ss);
    RTCVALH = d_to_x(ct->mm);
}

void epoch_to_caltime(caltime_t *ct, epoch_t *ep) {
    // terminalでepoch時間を求めるコマンド
    // echo $(( (`date -d '2015/03/01' '+%s'` - `date -d '2000/01/01' '+%s'`) / 86400 ))
    static uint16_t day_cache = 0; //2015.03.01
    static uint8_t month_cache = 1;
    static uint8_t year_cache = 0;
    uint16_t day_since_epoch;
    uint16_t day;
    uint8_t year = 0;
    uint8_t month = 1; // month is one-based.
    epoch_t num;

    num = *ep;
    ct->ss = get_quot_rem(&num, 60);
    ct->mm = get_quot_rem(&num, 60);
    ct->hh = get_quot_rem(&num, 24);
    day = num;
    day_since_epoch = day;

    num += 6; // 2000.1.1 is Saturday(6).
    ct->EE = get_quot_rem(&num, 7);

    //    if (day == day_cache) {
    //        year = year_cache;
    //        month = month_cache;
    //        day -= day_cache;
    //    }

    // day is zero - based here.
    while (day >= month_length(year, month)) {
        LATB2 = 1;
        day = day - month_length(year, month);
        if (month == 12) {
            month = 1; // month is one-based.
            year++;
            //3155760000 is 2000~2100の100年間の秒数
            if (year >= 100) {
                *ep -= 3155760000;
                year = 0;
            }
        } else {
            month++;
        }
        month_cache = month;
        year_cache = year;
    }
    day_cache = day_since_epoch - day;
    day++; // day is one-based, not zero-based.

    ct->YY = year;
    ct->MM = month;
    ct->DD = day;
}

void caltime_to_epoch(caltime_t *ct, epoch_t *ep) {
    epoch_t epoch = 0;
    for (uint8_t year = 0; year < ct->YY; year++) {
        for (uint8_t month = 1; month <= 12; month++) {
            epoch += DAY * month_length(year, month);
        }
    }
    for (uint8_t month = 1; month < ct->MM; month++) {
        epoch += DAY * month_length(ct->YY, month);
    }
    epoch += DAY * (ct->DD - 1); //day is one-based.
    epoch += HOUR * ct->hh;
    epoch += MINUTE * ct->mm;
    epoch += ct->ss;

    *ep = epoch;
}

/********************************** Transform time User Functions **********************************/

void RTCC_from_RTCC(caltime_t *ct, epoch_t *ep) {
    RTCC_to_caltime(ct);
    caltime_to_epoch(ct, ep);
}

void RTCC_from_caltime(caltime_t *ct, epoch_t *ep) {
    caltime_to_epoch(ct, ep);
    epoch_to_caltime(ct, ep);
    caltime_to_RTCC(ct);
}

void RTCC_from_epoch(caltime_t *ct, epoch_t *ep) {
    epoch_to_caltime(ct, ep);
    caltime_to_RTCC(ct);
}

/********************************** I2C LCD display **********************************/
#ifdef ST7032
#include <My_stdlib.h>

void display_dec(uint8_t dec, uint8_t edit) {
    char str[10];
    my_utoa(str, dec, 2);
    if (edit && halfsec)I2C_LCD_Puts("  ");
    else I2C_LCD_Puts(str);
}

void display_time_0802(caltime_t *ct, epoch_t *ep) {
    RTCC_from_RTCC(ct, ep);

    I2C_LCD_SetCursor(0, 0);
    display_dec(ct->YY, edit_flag.flag.YY);
    I2C_LCD_Putc('/');
    display_dec(ct->MM, edit_flag.flag.MM);
    I2C_LCD_Putc('/');
    display_dec(ct->DD, edit_flag.flag.DD);
    I2C_LCD_Putc('/');
    I2C_LCD_Puts(weekday_3char[ct->EE]);
    I2C_LCD_SetCursor(0, 1);
    display_dec(ct->hh, edit_flag.flag.hh);
    if (colon) I2C_LCD_Putc(':');
    else I2C_LCD_Putc(' ');
    display_dec(ct->mm, edit_flag.flag.mm);
    I2C_LCD_Putc('-');
    display_dec(ct->ss, edit_flag.flag.ss);
}

void display_time_1602(caltime_t *ct, epoch_t *ep) {
    RTCC_from_RTCC(ct, ep);

    I2C_LCD_SetCursor(0, 0);
    display_dec(20, edit_flag.flag.YY);
    display_dec(ct->YY, edit_flag.flag.YY);
    I2C_LCD_Putc('/');
    display_dec(ct->MM, edit_flag.flag.MM);
    I2C_LCD_Putc('/');
    display_dec(ct->DD, edit_flag.flag.DD);
    I2C_LCD_Putc('(');
    I2C_LCD_Puts(weekday_3char[ct->EE]);
    I2C_LCD_Putc(')');
    I2C_LCD_SetCursor(8, 1);
    display_dec(ct->hh, edit_flag.flag.hh);
    if (colon) I2C_LCD_Putc(':');
    else I2C_LCD_Putc(' ');
    display_dec(ct->mm, edit_flag.flag.mm);
    I2C_LCD_Putc('-');
    display_dec(ct->ss, edit_flag.flag.ss);
}
#endif

/********************************** adjust the time **********************************/

void RTCC_adjust_time_toggle(void) {
    if (edit_flag.flags) {
        edit_flag.flags = 0;
    } else {
        edit_flag.flag.ss = 1;
    }
}

void RTCC_adjust_time_cursor(void) {
    if (edit_flag.flag.ss)edit_flag.flags = 0x02;
    else if (edit_flag.flag.mm)edit_flag.flags = 0x04;
    else if (edit_flag.flag.hh)edit_flag.flags = 0x08;
    else if (edit_flag.flag.DD)edit_flag.flags = 0x10;
    else if (edit_flag.flag.MM)edit_flag.flags = 0x20;
    else if (edit_flag.flag.YY)edit_flag.flags = 0x01;
    else edit_flag.flags = 0x00;
}

void RTCC_adjust_time_inc(caltime_t *ct, epoch_t *ep) {
    RTCC_from_RTCC(ct, ep);
    if (edit_flag.flag.ss) *ep += 1;
    if (edit_flag.flag.mm) *ep += MINUTE;
    if (edit_flag.flag.hh) *ep += HOUR;
    if (edit_flag.flag.DD) *ep += DAY;
    if (edit_flag.flag.MM) *ep += DAY * month_length(ct->YY, ct->MM);
    if (edit_flag.flag.YY) {
        for (uint8_t i = ct->MM; i <= 12; i++) {
            *ep += DAY * month_length(ct->YY, i);
        }
        for (uint8_t i = 1; i < ct->MM; i++) {
            *ep += DAY * month_length(ct->YY + 1, i);
        }
    }

    if (*ep >= 3155760000)*ep -= 3155760000;
    RTCC_from_epoch(&caltime_now, &epoch_now);
    time_change_flag = 1;
}

void RTCC_adjust_time_dec(caltime_t *ct, epoch_t *ep) {
    RTCC_from_RTCC(ct, ep);
    if (edit_flag.flag.ss) *ep -= 1;
    if (edit_flag.flag.mm) *ep -= MINUTE;
    if (edit_flag.flag.hh) *ep -= HOUR;
    if (edit_flag.flag.DD) *ep -= DAY;
    if (edit_flag.flag.MM) *ep -= DAY * month_length(ct->YY, ct->MM);
    if (edit_flag.flag.YY) {
        for (uint8_t i = ct->MM; i >= 1; i--) {
            *ep -= DAY * month_length(ct->YY, i);
        }
        for (uint8_t i = 12; i > ct->MM; i--) {
            *ep -= DAY * month_length(ct->YY - 1, i);
        }
    }

    if (*ep >= 3155760000)*ep += 3155760000;
    RTCC_from_epoch(&caltime_now, &epoch_now);
    time_change_flag = 1;
}

void RTCC_adjust_time_button(button_t *mode, button_t *cnt_inc, button_t *cnt_dec) {
    if (mode->flag.long_holding_3) {
        mode->flag.long_holding_3 = 0;
        RTCC_adjust_time_toggle();
        mode->flags = 0;
        cnt_inc->flags = 0;
        cnt_dec->flags = 0;
    }
    if (edit_flag.flags) {
        if (mode->flag.press) {
            mode->flag.press = 0;
            RTCC_adjust_time_cursor();
        }
        if (cnt_inc->flag.press) {
            cnt_inc->flag.press = 0;
            RTCC_adjust_time_inc(&caltime_now, &epoch_now);
        }
        if (cnt_dec->flag.press) {
            cnt_dec->flag.press = 0;
            RTCC_adjust_time_dec(&caltime_now, &epoch_now);
        }
    }
}

void RTCC_loop(void) {
    static uint8_t prev_halfsec;
    while (RTCCFGbits.RTCSYNC);
    halfsec = RTCCFGbits.HALFSEC;
    if (prev_halfsec != halfsec) {
        prev_halfsec = halfsec;
        colon = halfsec;
        time_change_flag = 1;
        RTCC_from_RTCC(&caltime_now, &epoch_now);
    }
}

#endif	/* MY_RTCC_H */
