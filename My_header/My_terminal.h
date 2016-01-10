/* 
 * File:   My_terminal.h
 * Author: kerikun11
 *
 * Created on 2015/07/12, 22:09
 */

#ifndef MY_TERMINAL_H
#define	MY_TERMINAL_H

#include <My_RTCC.h>
#include <My_ringbuf.h>
#include <My_stdlib.h>
#include <stdio.h>

#define COMMAND_SIZE 100
#define OPCODE_SIZE 20

// 実体をどこかに記述すること。
void command_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3);

void my_terminal_loop(ringbuf_t *tx, ringbuf_t *rx) {
    static ringbuf_t command;
    static uint8_t command_init = 0;
    if (command_init == 0) {
        command_init = 1;
        char buf[COMMAND_SIZE];
        ringbuf_init(&command, buf, sizeof (buf));
    }
    if (ringbuf_num(rx)) {
        char ascii = ringbuf_pop(rx);
        switch (ascii) {
            case '\r':
                ringbuf_put(&command, '\0');
                ringbuf_put(tx, '\t');
                ringbuf_put_num(tx, ringbuf_num(&command) - 1, 2);
                ringbuf_put(tx, '\n');
                static char op0[OPCODE_SIZE];
                static char op1[OPCODE_SIZE];
                static char op2[OPCODE_SIZE];
                static char op3[OPCODE_SIZE];
                uint8_t i;
                for (i = 0; op0[i] = ringbuf_pop(&command); i++);
                op0[i] = '\0';
                for (i = 0; op1[i] = ringbuf_pop(&command); i++);
                op1[i] = '\0';
                for (i = 0; op2[i] = ringbuf_pop(&command); i++);
                op2[i] = '\0';
                for (i = 0; op3[i] = ringbuf_pop(&command); i++);
                op3[i] = '\0';
                command_operation(tx, op0, op1, op2, op3);
                break;
            case ' ':
                ringbuf_put(&command, '\0');
                ringbuf_put(tx, ' ');
                break;
            case '\b':
                ringbuf_backspace(&command);
                ringbuf_put_str(tx, "\b \b");
                break;
            case 0x7F: // Del
                for (uint8_t i = 0; i < ringbuf_num(&command); i++) ringbuf_put_str(tx, "\b \b");
                ringbuf_delete(&command);
                break;
            default:
                if (ascii >= ' ' && ascii <= '~') {
                    ringbuf_put(&command, ascii);
                    ringbuf_put(tx, ascii);
                }
                break;
        }
    }
}

void print_time_dec(ringbuf_t *tx, uint8_t dec, uint8_t edit) {
    uint8_t str[10];
    my_utoa(str, dec, 2);
    if (edit && halfsec)ringbuf_put_str(tx, "  ");
    else ringbuf_put_str(tx, str);
}

void print_time(ringbuf_t *tx) {
    RTCC_from_RTCC(&caltime_now, &epoch_now);
    char str[30];
    sprintf(str, "\t20%02d/%02d/%02d(%s)%02d:%02d-%02d\n",
            caltime_now.YY,
            caltime_now.MM,
            caltime_now.DD,
            weekday_3char[caltime_now.EE],
            caltime_now.hh,
            caltime_now.mm,
            caltime_now.ss);
    ringbuf_put_str(tx, str);
}

void command_at_hand(ringbuf_t *tx, uint8_t *hand, uint8_t min, uint8_t max, uint8_t value) {
    if (value >= min && value <= max) {
        *hand = value;
        RTCC_from_caltime(&caltime_now, &epoch_now);
        time_change_flag = 1;
        print_time(tx);
    } else {
        ringbuf_put_str(tx, "\terror\n");
    }
}

void command_time(ringbuf_t *tx, char *op0, char *op1, char *op2) {
    if (!my_strcmp(op0, "print_time") || !my_strcmp(op0, "t")) {
        print_time(tx);
    }
    if (!my_strcmp(op0, "at") || !my_strcmp(op0, "adjust_time")) {
        if (!my_strcmp(op1, "y") || !my_strcmp(op1, "year")) {
            command_at_hand(tx, &caltime_now.YY, 0, 99, my_atoi(op2));
        }
        if (!my_strcmp(op1, "M") || !my_strcmp(op1, "month")) {
            command_at_hand(tx, &caltime_now.MM, 1, 12, my_atoi(op2));
        }
        if (!my_strcmp(op1, "d") || !my_strcmp(op1, "day")) {
            command_at_hand(tx, &caltime_now.DD, 1, month_length(caltime_now.YY, caltime_now.MM), my_atoi(op2));
        }
        if (!my_strcmp(op1, "h") || !my_strcmp(op1, "hour")) {
            command_at_hand(tx, &caltime_now.hh, 0, 23, my_atoi(op2));
        }
        if (!my_strcmp(op1, "m") || !my_strcmp(op1, "minute")) {
            command_at_hand(tx, &caltime_now.mm, 0, 59, my_atoi(op2));
        }
        if (!my_strcmp(op1, "s") || !my_strcmp(op1, "second")) {
            command_at_hand(tx, &caltime_now.ss, 0, 59, my_atoi(op2));
        }
    }
}

#endif	/* MY_TERMINAL_H */

