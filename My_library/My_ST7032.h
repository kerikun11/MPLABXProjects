/* 
 * File:   My_ST7032.h
 * Author: kerikun11
 *
 * Created on 2015/11/12, 16:21
 */

#ifndef MY_ST7032_H
#define	MY_ST7032_H

#include <xc.h>
#include <stdint.h>
#include <My_ringbuf.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum ST7032_STATE {
        ST7032_IDOLE,
        ST7032_START,
        ST7032_SEND,
        ST7032_STOP,
        ST7032_WAIT
    } st7032_state_t;

    extern ringbuf_t lcd_tx;
    extern uint8_t st7032_flag;


    void ST7032_command(uint8_t command, uint8_t wait);

    void ST7032_clear(void);

    void ST7032_cursor(uint8_t col, uint8_t row);

    void ST7032_put(char c);

    void ST7032_puts(const uint8_t *s);

    void ST7032_create_char(int p, char *dt);

    void ST7032_init(void);

    void ST7032_ISR(void);

    void ST7032_task(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MY_ST7032_H */

