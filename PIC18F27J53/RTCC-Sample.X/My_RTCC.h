/* 
 * File:   My_RTCC.h
 * Author: Ryotaro Onuki
 *
 * Created on 2015/03/19, 0:02
 * 
 * PIC18F28J53用リアルタイムクロックプログラム
 * ○概要
 * このプログラムでは、時刻情報を持つ変数が３つある。
 * 1.PICのRTCCモジュールのレジスタ→カレンダー表記、16進法表記（※厳密には10進だが便宜上16進とする。）
 * 2.time_t構造体内のepoch（uint32_t）→2000年1月1日0時00分からの総秒数
 * 3.time_t構造体内のYY,MM,DD,EE,hh,mm,ss→それぞれ、年、月、日、曜日、時、分、秒の10進法表記。
 * 以上３つがある。時刻が変わってもRTCC_loop()関数がすべての値を常に一致させているので安心して使用できる。
 * ○使い方
 * 1.TIOSCのピンに32.768kHzのクリスタルをつなぐ。（12pのコンデンサも）
 * 2.CONFIGを設定する。RTCOSC = T1OSCREF
 * 3.その次に、RTCC_init();を書く。（初期設定関数）
 * 4.mainループ内に、RTCC_loop();を書くこと。（時間の同期関数）
 * 5.任意で時計合わせをする。→時計合わせをしたら、RTCC_from_caltime()かRTCC_from_epoch()を呼んで変更を適用する。
 * 6.時計合わせには、adjust_time_toggle()を呼んでから、adjust_time_cursor()で、好きな項を選択する
 * 7.adjust_time_inc()とadjust_time_dec()で調整するとよい。
 * 8.時計合わせが終わったら、adjust_time_toggle()をもう一度呼ぶと時計合わせ終了。
 */

#ifndef MY_RTCC_H
#define	MY_RTCC_H

#include <xc.h>
#include <stdint.h>
#include "My_button.h"

// epoch型を定義。2000年1月1日0時00分からの総秒数。

typedef uint32_t epoch_t;

// 時刻合わせ用のフラグの構造体を定義。

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
} edit_t;

// RTCC関連すべてを詰めた構造体。実際に使用する。

typedef struct {
    epoch_t epoch;
    uint8_t ss;
    uint8_t mm;
    uint8_t hh;
    uint8_t EE;
    uint8_t DD;
    uint8_t MM;
    uint8_t YY;
    uint8_t colon;
    uint8_t halfsec;
    edit_t edit;
} time_t;

// 表示用の曜日charをconstで定義。
extern const char weekday_3char[7][4];

// 現在時刻
extern time_t now;
// 時間が変わった時だけフラグが経つ。表示器の時刻の更新はこのフラグの監視をして行えばよい。
extern uint8_t time_change_flag;
// main_init()に書くこと。
void RTCC_init(void);
/********************************** necessary functions **********************************/
// from decimal to hex
uint8_t d_to_x(uint8_t dec);
// from hex to decimal
uint8_t x_to_d(uint8_t hex);
// return month length
uint8_t month_length(uint8_t year, uint8_t month);
// quotをdivで割って、余りを返す。よく使うので関数化した。
epoch_t get_quot_rem(epoch_t *quot, uint8_t div);
/********************************** Transform time **********************************/
// RTCCをカレンダタイムに変換、上書き。
void RTCC_to_caltime(time_t *tm);
// カレンダタイムをRTCCに変換、上書き。
void caltime_to_RTCC(time_t *tm);
// Epochをカレンダタイムに変換、上書き。
void epoch_to_caltime(time_t *tm);
// カレンダタイムをエポックに変換、上書き。
void caltime_to_epoch(time_t *tm);
/********************************** Transform time User Functions **********************************/
// 時刻をRTCC基準でそろえる
void RTCC_from_RTCC(time_t *tm);
// 時刻をカレンダータイム基準でそろえる
void RTCC_from_caltime(time_t *tm);
// 時刻をエポック基準でそろえる
void RTCC_from_epoch(time_t *tm);
/********************************** LCD display **********************************/
// 各項目表示用関数。ユーザーは使わない。
void display_dec(char *str, uint8_t dec, uint8_t edit);
// 0802サイズ液晶用、文字列作成関数
void display_time_0802(time_t *tm, char *line0, char *line1);
// 1608サイズ液晶用、文字列作成関数
void display_time_1602(time_t *tm, char *line0, char *line1);
/********************************** adjust the time **********************************/
// 時刻編集モードを切り替える
void RTCC_adjust_time_toggle(time_t *tm);
// 編集中の時刻針を切り替える
void RTCC_adjust_time_cursor(time_t *tm);
// 編集中の時刻針を１つ増やす
void RTCC_adjust_time_inc(time_t *tm);
// 編集中の時刻針を１つ減らす
void RTCC_adjust_time_dec(time_t *tm);
// 3つのボタンで時刻合わせ
void RTCC_adjust_time_button(time_t *tm, button_t *mode, button_t *cnt_inc, button_t *cnt_dec);
// Time sync
void RTCC_loop(void);

#endif	/* MY_RTCC_H */
