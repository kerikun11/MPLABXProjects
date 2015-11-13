/* 
 * File:   My_I2C_LCD.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 21:10
 */

#ifndef MY_I2C_LCD_H
#define	MY_I2C_LCD_H

#include <stdint.h>

/*************************** I2C_LCD I2C_LCD ***************************/
#define I2C_LCD_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス

void I2C_LCD_Command(uint8_t c);
void I2C_LCD_Clear(void);
void I2C_LCD_SetCursor(uint8_t col, uint8_t row);
void I2C_LCD_Putc(uint8_t c);
void I2C_LCD_Puts(const uint8_t * s);
void I2C_LCD_CreateChar(int p, char *dt);
void I2C_LCD_init(void);

#endif	/* MY_I2C_LCD_H */

