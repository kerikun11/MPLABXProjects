// skI2CLCDlib.h
// Ｉ２Ｃ接続ＬＣＤ関数ライブラリ用インクルードファイル
#ifndef _SKI2CLCDLIB_H_
#define _SKI2CLCDLIB_H_

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 8000000    // 使用するPIC等により動作周波数値を設定する
#endif
#define ST7032_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス

void LCD_Clear(void) ;
void LCD_SetCursor(int col, int row) ;
void LCD_Putc(char c) ;
void LCD_Puts(const char * s) ;
void LCD_CreateChar(int p,char *dt) ;
void LCD_Init() ;

#endif
