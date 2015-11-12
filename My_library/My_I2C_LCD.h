/* 
 * File:   My_I2C_LCD.h
 * Author: kerikun11
 *
 * Created on 2015/11/12, 16:21
 */

#ifndef MY_I2C_LCD_H
#define	MY_I2C_LCD_H

#include <xc.h>
#include <stdint.h>
#include <My_ringbuf.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum I2C_LCD_STATE {
        I2C_LCD_IDOLE,
        I2C_LCD_START,
        I2C_LCD_SEND,
        I2C_LCD_STOP,
        I2C_LCD_WAIT
    } i2c_lcd_state_t;

    extern ringbuf_t lcd_tx;
    extern uint8_t i2c_lcd_flag;


    void I2C_LCD_command(uint8_t command, uint8_t wait);

    void I2C_LCD_clear(void);

    void I2C_LCD_cursor(uint8_t col, uint8_t row);

    void I2C_LCD_put(char c);

    void I2C_LCD_puts(const uint8_t *s);

    void I2C_LCD_create_char(int p, char *dt);

    void I2C_LCD_init(void);

    void I2C_LCD_ISR(void);

    void I2C_LCD_task(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MY_I2C_LCD_H */

