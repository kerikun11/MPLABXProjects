#include "My_ST7032.h"

#define ST7032_ADDRESS 0x3E 
#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1

#define WAIT_0      0
#define WAIT_26US   1
#define WAIT_1MS    2
#define WAIT_40MS   3

st7032_state_t st7032_state;
ringbuf_t lcd_tx;
uint8_t st7032_flag;

void ST7032_command(uint8_t command, uint8_t wait) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0x80); // command mode
    ringbuf_put(&lcd_tx, command); // command data
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, wait); // wait
}

void ST7032_clear(void) {
    ST7032_command(0x01, WAIT_1MS); // Clear Display 
}

void ST7032_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    ST7032_command(0x80 | (col + row_offsets[row]), WAIT_0); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void ST7032_put(char c) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0b11000000); // control byte
    ringbuf_put(&lcd_tx, c); // data byte 
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, WAIT_26US); // wait
}

void ST7032_puts(const uint8_t *s) {
    while (*s) {
        ST7032_put(*s++); // data byte
    }
}

void ST7032_create_char(int p, char *dt) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0x80); // command mode
    ringbuf_put(&lcd_tx, 0x40 | (p << 3));
    ringbuf_put(&lcd_tx, 0x40); // control byte
    for (uint8_t i = 0; i < 7; i++) {
        ringbuf_put(&lcd_tx, *dt++);
        // need wait
    }
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, WAIT_26US); // wait
}

void ST7032_init(void) {
    SSP1STAT = 0b10000000;
    SSP1CON1 = 0b00101000;
    SSP1ADD = 0x13;// 0x77:100kHz 0x13:400kHz
    PIE1bits.SSP1IE = 1;
    IPR1bits.SSP1IP = 0;
    PIR1bits.SSP1IF = 0;
    PIE2bits.BCL1IE = 1;
    IPR2bits.BCL1IP = 0;
    PIR2bits.BCL1IF = 0;
    INTCONbits.PEIE = 1;

    static char buf[200];
    ringbuf_init(&lcd_tx, buf, sizeof (buf));

    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, WAIT_40MS); // wait

    ST7032_command(0x38, WAIT_26US);
    ST7032_command(0x39, WAIT_26US);
    ST7032_command(0x14, WAIT_26US);
    ST7032_command(0x70, WAIT_26US);
    ST7032_command(0x56, WAIT_26US);
    ST7032_command(0x6C, WAIT_40MS);
    ST7032_command(0x38, WAIT_26US);
    ST7032_command(0x0C, WAIT_26US);
    ST7032_command(0x06, WAIT_26US);
    ST7032_clear(); // Clear Display
}

void ST7032_ISR(void) {
    if (PIE1bits.SSP1IE && PIR1bits.SSP1IF) {
        PIR1bits.SSP1IF = 0;
        st7032_flag = 1;
    }
    if (PIE2bits.BCL1IE && PIR2bits.BCL1IF) {
        PIR2bits.BCL1IF = 0;
    }
}

void ST7032_task(void) {
    if ((SSP1CON2 & 0x1F) | (SSP1STAT & 0x05)) {
        // SSP is busy
        return;
    }
    static uint16_t wait;
    static st7032_state_t st7032_state = ST7032_IDOLE;

    switch (st7032_state) {
        case ST7032_IDOLE:
            if (ringbuf_num(&lcd_tx)) {
                st7032_state = ST7032_START;
            }
            break;
        case ST7032_START:
            st7032_flag = 1;
            SSP1CON2bits.SEN = 1;
            st7032_state = ST7032_SEND;
            break;
        case ST7032_SEND:
            if (!st7032_flag) {
                // no SSPIF
                return;
            }
            char data = ringbuf_pop(&lcd_tx);
            if (data != 0) {
                st7032_flag = 0;
                SSP1BUF = data;
            } else {
                wait = ringbuf_pop(&lcd_tx);
                switch (wait) {
                    case WAIT_0:
                        wait = 0;
                        break;
                    case WAIT_26US:
                        wait = 2;
                        break;
                    case WAIT_1MS:
                        wait = 25;
                        break;
                    case WAIT_40MS:
                        wait = 800;
                        break;
                    default:
                        wait = 1;
                        break;
                }
                st7032_state = ST7032_STOP;
            }
            break;
        case ST7032_STOP:
            SSP1CON2bits.PEN = 1;
            st7032_state = ST7032_WAIT;
            break;
        case ST7032_WAIT:
            if (wait == 0) st7032_state = ST7032_IDOLE;
            else wait--;
            break;
    }
}
