/* 
 * File:   My_ringbuf.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:21
 */

#ifndef MY_RINGBUF_H
#define	MY_RINGBUF_H

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

void ringbuf_init(ringbuf_t *rb, char *internal_buf, uint16_t bufsize) {
    rb->buf = internal_buf;
    rb->size = bufsize;
    rb->head = 0;
    rb->tail = 0;
}

uint16_t ringbuf_num(ringbuf_t *rb) {
    if (rb->head >= rb->tail) {
        return (rb->head - rb->tail);
    } else {
        return (rb->size + rb->head - rb->tail);
    }
}

void ringbuf_put(ringbuf_t *rb, char asciicode) {
    if (ringbuf_num(rb) < rb->size) {
        rb->buf[rb->head] = asciicode;
        if (rb->head + 1 < rb->size) rb->head++;
        else rb->head = 0;
    }
}

void ringbuf_put_num(ringbuf_t *rb, const uint16_t value, uint8_t digits) {
    while (digits--) {
        uint16_t temp = value;
        for (uint8_t i = 0; i < digits; i++) {
            temp /= 10;
        }
        temp %= 10;
        ringbuf_put(rb, temp + '0');
    }
}

void ringbuf_put_str(ringbuf_t *rb, const char *str) {
    while (*str) {
        ringbuf_put(rb, *str++);
    }
}

char ringbuf_pop(ringbuf_t *rb) {
    if (ringbuf_num(rb)) {
        char ret = rb->buf[rb->tail];
        if (rb->tail + 1 < rb->size) {
            rb->tail++;
        } else {
            rb->tail = 0;
        }
        return ret;
    } else {
        return 0;
    }
}

void ringbuf_backspace(ringbuf_t *rb) {
    if (ringbuf_num(rb)) {
        if (rb->head) rb->head--;
        else rb->head = rb->size - 1;
    }
}

void ringbuf_delete(ringbuf_t *rb) {
    rb->head = rb->tail;
}

#endif	/* MY_RINGBUF_H */
