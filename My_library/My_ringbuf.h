/* 
 * File:   My_ringbuf.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:21
 */

#ifndef MY_RINGBUF_H
#define	MY_RINGBUF_H

#include <stdint.h>

//*************************** ringbuf ***************************//
// buf[100];
// ringbuf_init(&ringbuf, buf, sizeof(buf));
// を行うこと。
// headは次に入れるバッファを指す。tailは次に出すバッファを指す。

typedef struct ringbuf {
    char *buf;
    uint16_t size;
    uint16_t head;
    uint16_t tail;
} ringbuf_t;

void ringbuf_init(ringbuf_t *rb, char *internal_buf, uint16_t bufsize);

uint16_t ringbuf_num(ringbuf_t *rb);

void ringbuf_put(ringbuf_t *rb, char asciicode);

void ringbuf_put_num(ringbuf_t *rb, const uint16_t value, uint8_t digits);

void ringbuf_put_str(ringbuf_t *rb, const char *str);

char ringbuf_pop(ringbuf_t *rb);

void ringbuf_backspace(ringbuf_t *rb);

void ringbuf_delete(ringbuf_t *rb);

#endif	/* MY_RINGBUF_H */
