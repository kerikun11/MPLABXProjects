/* 
 * File:   My_ST7032.h
 * Author: kerikun11
 *
 * Created on 2015/11/12, 16:21
 */

#ifndef MY_ST7032_H
#define	MY_ST7032_H

#include <stdint.h>
#include <My_ringbuf.h>
#include <My_I2C.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum ST7032_STATE {
        ST7032_IDLE,
        ST7032_START,
        ST7032_SEND,
        ST7032_STOP,
        ST7032_WAIT
    } st7032_state_t;

    extern ringbuf_t lcd_tx;

    void ST7032_command(uint8_t command, uint8_t wait);

    void ST7032_clear(void);

    void ST7032_cursor(uint8_t col, uint8_t row);

    void ST7032_put(char c);

    void ST7032_puts(const uint8_t *s);

    void ST7032_create_char(int p, char *dt);

    void ST7032_init(void);

    void ST7032_task(void);

    /*************************** old functions ***************************/
#if I2C_OLD_FUNCTIONS

#define I2C_LCD_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス

    void I2C_LCD_Command(uint8_t c);
    void I2C_LCD_Clear(void);
    void I2C_LCD_SetCursor(uint8_t col, uint8_t row);
    void I2C_LCD_Putc(uint8_t c);
    void I2C_LCD_Puts(const uint8_t * s);
    void I2C_LCD_CreateChar(int p, char *dt);
    void I2C_LCD_init(void);

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MY_ST7032_H */

