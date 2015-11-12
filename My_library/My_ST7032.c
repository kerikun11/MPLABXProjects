#include "My_ST7032.h"

#include "My_I2C.h" // for I2C_...()
#include "My_PIC.h" // for _XTAL_FREQ

/*************************** I2C_LCD ST7032 ***************************/

void I2C_LCD_Command(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void I2C_LCD_Clear(void) {
    I2C_LCD_Command(0x01); // Clear Display : 画面全体に20Hのｽﾍﾟｰｽで表示、ｶｰｿﾙはcol=0,row=0に移動
    __delay_us(1100); // LCDが処理(1.08ms)するのを待ちます
}

void I2C_LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};

    I2C_LCD_Command(0x80 | (col + row_offsets[row])); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void I2C_LCD_Putc(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b11000000); // control byte の送信(データを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void I2C_LCD_Puts(const uint8_t * s) {
    int ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        while (*s) {
            I2C_Send(*s++); // data byte の送信(連続送信)
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void I2C_LCD_CreateChar(int p, char *dt) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        //  LCDにキャラ保存先のアドレスを指示する
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(0x40 | (p << 3));
        __delay_us(26);
        //  LCDにキャラデータを送信する
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        for (uint8_t i = 0; i < 7; i++) {
            I2C_Send(*dt++);
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void ST7032_init(void) {
    for (uint8_t i = 0; i < 40; i++) __delay_ms(1); // 電源ＯＮ後40msまで待ってから初期化
    I2C_LCD_Command(0x38); // function set           : データ線は8本・表示は２行・フォントは5x8ドット
    I2C_LCD_Command(0x39); // function set           : 拡張コマンドの設定を有効にする
    I2C_LCD_Command(0x14); // Internal OSC frequency : バイアスの選択と内部OSC周波数の調整
    I2C_LCD_Command(0x70); // Contrast set           : コントラスト調整データ(下位4ビット)
    I2C_LCD_Command(0x56); // Contrast set           : 昇圧回路有効、コントラスト調整データ(上位2ビット)
    I2C_LCD_Command(0x6C); // Follower control       : フォロア回路をON、増幅率の調整を行う
    for (uint8_t i = 0; i < 40; i++) __delay_ms(1); // 電力が安定するまで待つ
    I2C_LCD_Command(0x38); // function set           : 拡張コマンドを設定を無効にする
    I2C_LCD_Command(0x0C); // display control        : 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
    I2C_LCD_Command(0x06); // entry mode set         : 文字を表示した次にカーソルを移動するを指示
    I2C_LCD_Clear(); // Clear Display          : 画面を消去する
}
