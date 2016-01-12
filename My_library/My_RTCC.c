#include "My_RTCC.h"

/** INCLUDES *******************************************************/
#include <stdio.h>
#include <string.h>

/** VALUES *********************************************************/


/** VARIABLES ******************************************************/
const char weekday_3char[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
time_t now;
uint8_t time_change_flag;

/** USER FUNCTIONS *************************************************/

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
    T1CONbits.T1OSCEN = 1;

    RTCC_from_RTCC(&now);
    if (now.DD == 0) {
        now.epoch = 0;
        RTCC_from_epoch(&now);
    }
}

void RTCC_task(void) {
    static uint8_t prev_halfsec;
    if (RTCCFGbits.RTCSYNC)return;
    now.halfsec = RTCCFGbits.HALFSEC;
    if (prev_halfsec != now.halfsec) {
        prev_halfsec = now.halfsec;
        now.colon = now.halfsec;
        time_change_flag = 1;
        RTCC_from_RTCC(&now);
    }
}

/** Transform time User Functions **/

void RTCC_from_RTCC(time_t *tm) {
    RTCC_to_caltime(tm);
    caltime_to_epoch(tm);
}

void RTCC_from_caltime(time_t *tm) {
    caltime_to_epoch(tm);
    epoch_to_caltime(tm);
    caltime_to_RTCC(tm);
}

void RTCC_from_epoch(time_t *tm) {
    epoch_to_caltime(tm);
    caltime_to_RTCC(tm);
}

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

/** LCD display **/

static void display_dec(char *str, uint8_t dec, uint8_t edit) {
    char s[4];
    sprintf(s, "%02d", dec);
    if (edit && now.halfsec)strcat(str, "  ");
    else strcat(str, s);
}

void display_time_0802(time_t *tm, char *line0, char *line1) {
    RTCC_from_RTCC(&now);

    strcpy(line0, "");
    display_dec(line0, tm->YY, tm->edit.flag.YY);
    strcat(line0, "/");
    display_dec(line0, tm->MM, tm->edit.flag.MM);
    strcat(line0, "/");
    display_dec(line0, tm->DD, tm->edit.flag.DD);

    strcpy(line1, "");
    display_dec(line1, tm->hh, tm->edit.flag.hh);
    if (now.colon) strcat(line1, ":");
    else strcat(line1, " ");
    display_dec(line1, tm->mm, tm->edit.flag.mm);
    strcat(line1, "-");
    display_dec(line1, tm->ss, tm->edit.flag.ss);
}

void display_time_1602(time_t *tm, char *line0, char *line1) {
    RTCC_from_RTCC(&now);

    strcpy(line0, "");
    display_dec(line0, 20, tm->edit.flag.YY);
    display_dec(line0, tm->YY, tm->edit.flag.YY);
    strcat(line0, "/");
    display_dec(line0, tm->MM, tm->edit.flag.MM);
    strcat(line0, "/");
    display_dec(line0, tm->DD, tm->edit.flag.DD);
    strcat(line0, "(");
    strcat(line0, weekday_3char[tm->EE]);
    strcat(line0, ")");

    strcpy(line1, "        ");
    display_dec(line1, tm->hh, tm->edit.flag.hh);
    if (tm->colon) strcat(line1, ":");
    else strcat(line1, " ");
    display_dec(line1, tm->mm, tm->edit.flag.mm);
    strcat(line1, "-");
    display_dec(line1, tm->ss, tm->edit.flag.ss);
}

/** adjust the time **/

void RTCC_adjust_time_toggle(time_t *tm) {
    if (tm->edit.flags) {
        tm->edit.flags = 0;
    } else {
        tm->edit.flag.ss = 1;
    }
}

void RTCC_adjust_time_cursor(time_t *tm) {
    if (tm->edit.flag.ss)tm->edit.flags = 0x02;
    else if (tm->edit.flag.mm)tm->edit.flags = 0x04;
    else if (tm->edit.flag.hh)tm->edit.flags = 0x08;
    else if (tm->edit.flag.DD)tm->edit.flags = 0x10;
    else if (tm->edit.flag.MM)tm->edit.flags = 0x20;
    else if (tm->edit.flag.YY)tm->edit.flags = 0x01;
    else tm->edit.flags = 0x00;
}

void RTCC_adjust_time_inc(time_t *tm) {
    RTCC_from_RTCC(tm);
    if (tm->edit.flag.ss) tm->epoch += 1;
    if (tm->edit.flag.mm) tm->epoch += MINUTE;
    if (tm->edit.flag.hh) tm->epoch += HOUR;
    if (tm->edit.flag.DD) tm->epoch += DAY;
    if (tm->edit.flag.MM) tm->epoch += DAY * month_length(tm->YY, tm->MM);
    if (tm->edit.flag.YY) {
        for (uint8_t i = tm->MM; i <= 12; i++) {
            tm->epoch += DAY * month_length(tm->YY, i);
        }
        for (uint8_t i = 1; i < tm->MM; i++) {
            tm->epoch += DAY * month_length(tm->YY + 1, i);
        }
    }

    if (tm->epoch >= 3155760000)tm->epoch -= 3155760000;
    RTCC_from_epoch(&now);
    time_change_flag = 1;
}

void RTCC_adjust_time_dec(time_t *tm) {
    RTCC_from_RTCC(tm);
    if (tm->edit.flag.ss) tm->epoch -= 1;
    if (tm->edit.flag.mm) tm->epoch -= MINUTE;
    if (tm->edit.flag.hh) tm->epoch -= HOUR;
    if (tm->edit.flag.DD) tm->epoch -= DAY;
    if (tm->edit.flag.MM) tm->epoch -= DAY * month_length(tm->YY, tm->MM);
    if (tm->edit.flag.YY) {
        for (uint8_t i = tm->MM; i >= 1; i--) {
            tm->epoch -= DAY * month_length(tm->YY, i);
        }
        for (uint8_t i = 12; i > tm->MM; i--) {
            tm->epoch -= DAY * month_length(tm->YY - 1, i);
        }
    }

    if (tm->epoch >= 3155760000)tm->epoch += 3155760000;
    RTCC_from_epoch(&now);
    time_change_flag = 1;
}

void RTCC_adjust_time_button(time_t *tm, button_t *mode, button_t *cnt_inc, button_t *cnt_dec) {
    if (mode->flag.long_holding_3) {
        mode->flag.long_holding_3 = 0;
        RTCC_adjust_time_toggle(tm);
        mode->flags = 0;
        cnt_inc->flags = 0;
        cnt_dec->flags = 0;
    }
    if (tm->edit.flags) {
        if (mode->flag.press) {
            mode->flag.press = 0;
            RTCC_adjust_time_cursor(tm);
        }
        if (cnt_inc->flag.press) {
            cnt_inc->flag.press = 0;
            RTCC_adjust_time_inc(tm);
        }
        if (cnt_dec->flag.press) {
            cnt_dec->flag.press = 0;
            RTCC_adjust_time_dec(tm);
        }
    }
}

/** FUNCTIONS ******************************************************/

/** en/decode number **/

static uint8_t d_to_x(uint8_t dec) {
    // uint8_t quot = dec / 10;
    // return quot * 16 + dec - quot * 10;
    return dec / 10 * 6 + dec;
}

static uint8_t x_to_d(uint8_t hex) {
    return 10 * (0x0F & (hex >> 4)) + (0x0F & hex);
}

static epoch_t get_quot_rem(epoch_t *quot, uint8_t div) {
    // num /= div;
    // return rem;
    epoch_t num = *quot;
    return num - (*quot = num / div) * div; // returns rem
}

/** Transform time **/

static void RTCC_to_caltime(time_t *tm) {
    while (RTCCFGbits.RTCSYNC);

    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 1;

    tm->YY = x_to_d(RTCVALL); // YY
    uint8_t dumy = RTCVALH; // Reserved
    tm->DD = x_to_d(RTCVALL); // DD
    tm->MM = x_to_d(RTCVALH); // MM
    tm->hh = x_to_d(RTCVALL); // hh
    tm->EE = x_to_d(RTCVALH); // EE
    tm->ss = x_to_d(RTCVALL); // ss
    tm->mm = x_to_d(RTCVALH); // mm
}

static void caltime_to_RTCC(time_t *tm) {
    while (RTCCFGbits.RTCSYNC);
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 1;
    RTCVALL = d_to_x(tm->YY);
    RTCVALH = 0x00;
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 1;
    RTCVALL = d_to_x(tm->DD);
    RTCVALH = d_to_x(tm->MM);
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = d_to_x(tm->hh);
    RTCVALH = d_to_x(tm->EE);
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = d_to_x(tm->ss);
    RTCVALH = d_to_x(tm->mm);
}

static void epoch_to_caltime(time_t *tm) {
    // to get epoch on terminal
    // echo $(( (`date -d '2015/03/01' '+%s'` - `date -d '2000/01/01' '+%s'`) / 86400 ))
    static uint16_t day_cache = 0; //2015.03.01
    static uint8_t month_cache = 1;
    static uint8_t year_cache = 0;
    uint16_t day_since_epoch;
    uint16_t day;
    uint8_t year = 0;
    uint8_t month = 1; // month is one-based.
    epoch_t num;

    num = tm->epoch;
    tm->ss = get_quot_rem(&num, 60);
    tm->mm = get_quot_rem(&num, 60);
    tm->hh = get_quot_rem(&num, 24);
    day = num;
    day_since_epoch = day;

    num += 6; // 2000.1.1 is Saturday(6).
    tm->EE = get_quot_rem(&num, 7);

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
            //3155760000 is 2000~2100?100?????
            if (year >= 100) {
                tm->epoch -= 3155760000;
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

    tm->YY = year;
    tm->MM = month;
    tm->DD = day;
}

static void caltime_to_epoch(time_t *tm) {
    epoch_t epoch = 0;
    for (uint8_t year = 0; year < tm->YY; year++) {
        for (uint8_t month = 1; month <= 12; month++) {
            epoch += DAY * month_length(year, month);
        }
    }
    for (uint8_t month = 1; month < tm->MM; month++) {
        epoch += DAY * month_length(tm->YY, month);
    }
    epoch += DAY * (tm->DD - 1); //day is one-based.
    epoch += HOUR * tm->hh;
    epoch += MINUTE * tm->mm;
    epoch += tm->ss;

    tm->epoch = epoch;
}
