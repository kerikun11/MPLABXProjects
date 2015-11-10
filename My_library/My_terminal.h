/* 
 * File:   My_terminal.h
 * Author: kerikun11
 *
 * Created on 2015/07/12, 22:09
 */

#ifndef MY_TERMINAL_H
#define	MY_TERMINAL_H

#include <stdint.h>
#include <My_ringbuf.h>

#define COMMAND_SIZE 100
#define OPCODE_SIZE 25

// é¿ëÃÇÇ«Ç±Ç©Ç…ãLèqÇ∑ÇÈÇ±Ç∆ÅB
void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3);

void terminal_task(ringbuf_t *tx, ringbuf_t *rx);

void print_time_dec(ringbuf_t *tx, uint8_t dec, uint8_t edit);

void print_time(ringbuf_t *tx);

void terminal_at_hand(ringbuf_t *tx, uint8_t *hand, uint8_t min, uint8_t max, uint8_t value);

void terminal_time(ringbuf_t *tx, char *op0, char *op1, char *op2);

#endif	/* MY_TERMINAL_H */

