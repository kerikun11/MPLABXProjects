/* 
 * File:   My_ST7032.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 21:10
 */

#ifndef MY_ST7032_H
#define	MY_ST7032_H

#include <stdint.h>

/*************************** I2C_LCD ST7032 ***************************/
#define ST7032_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス

void I2C_LCD_Command(uint8_t c);
void I2C_LCD_Clear(void);
void I2C_LCD_SetCursor(uint8_t col, uint8_t row);
void I2C_LCD_Putc(uint8_t c);
void I2C_LCD_Puts(const uint8_t * s);
void I2C_LCD_CreateChar(int p, char *dt);
void ST7032_init(void);

#endif	/* MY_ST7032_H */

