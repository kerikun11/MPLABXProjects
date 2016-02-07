#include "My_terminal.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "My_RTCC.h"

void terminal_task(ringbuf_t *tx, ringbuf_t *rx) {
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
                terminal_operation(tx, op0, op1, op2, op3);
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
    sprintf(str, "%02d", dec);
    if (now.edit.flags && now.halfsec)ringbuf_put_str(tx, "  ");
    else ringbuf_put_str(tx, str);
}

void print_time(ringbuf_t *tx) {
    RTCC_from_RTCC(&now);
    char str[30];
    sprintf(str, "\t20%02d/%02d/%02d(%s)%02d:%02d-%02d\n",
            now.YY,
            now.MM,
            now.DD,
            weekday_3char[now.EE],
            now.hh,
            now.mm,
            now.ss);
    ringbuf_put_str(tx, str);
}

void terminal_at_hand(ringbuf_t *tx, uint8_t *hand, uint8_t min, uint8_t max, uint8_t value) {
    if (value >= min && value <= max) {
        *hand = value;
        RTCC_from_caltime(&now);
        time_change_flag = 1;
        print_time(tx);
    } else {
        ringbuf_put_str(tx, "\terror\n");
    }
}

void terminal_time(ringbuf_t *tx, char *op0, char *op1, char *op2) {
    if (!strcmp(op0, "print_time") || !strcmp(op0, "t") || !strcmp(op0, "")) {
        print_time(tx);
    }
    if (!strcmp(op0, "at") || !strcmp(op0, "adjust_time")) {
        if (!strcmp(op1, "y") || !strcmp(op1, "year")) {
            terminal_at_hand(tx, &now.YY, 0, 99, atoi(op2));
        }
        if (!strcmp(op1, "M") || !strcmp(op1, "month")) {
            terminal_at_hand(tx, &now.MM, 1, 12, atoi(op2));
        }
        if (!strcmp(op1, "d") || !strcmp(op1, "day")) {
            terminal_at_hand(tx, &now.DD, 1, month_length(now.YY, now.MM), atoi(op2));
        }
        if (!strcmp(op1, "h") || !strcmp(op1, "hour")) {
            terminal_at_hand(tx, &now.hh, 0, 23, atoi(op2));
        }
        if (!strcmp(op1, "m") || !strcmp(op1, "minute")) {
            terminal_at_hand(tx, &now.mm, 0, 59, atoi(op2));
        }
        if (!strcmp(op1, "s") || !strcmp(op1, "second")) {
            terminal_at_hand(tx, &now.ss, 0, 59, atoi(op2));
        }
    }
}
