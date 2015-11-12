#include "My_I2C_LCD.h"

#define ST7032_ADDRESS 0x3E 
#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1

#define WAIT_0      0
#define WAIT_26US   1
#define WAIT_1MS    2
#define WAIT_40MS   3

i2c_lcd_state_t i2c_lcd_state;
ringbuf_t lcd_tx;
uint8_t i2c_lcd_flag;

void I2C_LCD_command(uint8_t command, uint8_t wait) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0x80); // command mode
    ringbuf_put(&lcd_tx, command); // command data
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, wait); // wait
}

void I2C_LCD_clear(void) {
    I2C_LCD_command(0x01, WAIT_1MS); // Clear Display 
}

void I2C_LCD_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    I2C_LCD_command(0x80 | (col + row_offsets[row]), WAIT_0); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void I2C_LCD_put(char c) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0b11000000); // control byte
    ringbuf_put(&lcd_tx, c); // data byte 
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, WAIT_26US); // wait
}

void I2C_LCD_puts(const uint8_t *s) {
    while (*s) {
        I2C_LCD_put(*s++); // data byte
    }
}

void I2C_LCD_create_char(int p, char *dt) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0x80); // command mode
    ringbuf_put(&lcd_tx, 0x40 | (p << 3));
    ringbuf_put(&lcd_tx, 0x40); // control byte ???(??????)
    for (uint8_t i = 0; i < 7; i++) {
        ringbuf_put(&lcd_tx, *dt++);
        // need wait
    }
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, WAIT_26US); // wait
}

void I2C_LCD_init(void) {
    SSP1STAT = 0b10000000;
    SSP1CON1 = 0b00101000;
    SSP1ADD = 0x13;
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

    I2C_LCD_command(0x38, WAIT_26US);
    I2C_LCD_command(0x39, WAIT_26US);
    I2C_LCD_command(0x14, WAIT_26US);
    I2C_LCD_command(0x70, WAIT_26US);
    I2C_LCD_command(0x56, WAIT_26US);
    I2C_LCD_command(0x6C, WAIT_40MS);
    I2C_LCD_command(0x38, WAIT_26US);
    I2C_LCD_command(0x0C, WAIT_26US);
    I2C_LCD_command(0x06, WAIT_26US);
    I2C_LCD_clear(); // Clear Display
}

void I2C_LCD_ISR(void) {
    if (PIE1bits.SSP1IE && PIR1bits.SSP1IF) {
        PIR1bits.SSP1IF = 0;
        i2c_lcd_flag = 1;
    }
    if (PIE2bits.BCL1IE && PIR2bits.BCL1IF) {
        PIR2bits.BCL1IF = 0;
    }
}

void I2C_LCD_task(void) {
    if ((SSP1CON2 & 0x1F) | (SSP1STAT & 0x05)) {
        // SSP is busy
        return;
    }
    static uint16_t wait;
    static i2c_lcd_state_t i2c_lcd_state = I2C_LCD_IDOLE;

    switch (i2c_lcd_state) {
        case I2C_LCD_IDOLE:
            if (ringbuf_num(&lcd_tx)) {
                i2c_lcd_state = I2C_LCD_START;
            }
            break;
        case I2C_LCD_START:
            i2c_lcd_flag = 1;
            SSP1CON2bits.SEN = 1;
            i2c_lcd_state = I2C_LCD_SEND;
            break;
        case I2C_LCD_SEND:
            if (!i2c_lcd_flag) {
                // no SSPIF
                return;
            }
            char data = ringbuf_pop(&lcd_tx);
            if (data != 0) {
                i2c_lcd_flag = 0;
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
                i2c_lcd_state = I2C_LCD_STOP;
            }
            break;
        case I2C_LCD_STOP:
            SSP1CON2bits.PEN = 1;
            i2c_lcd_state = I2C_LCD_WAIT;
            break;
        case I2C_LCD_WAIT:
            if (wait == 0) i2c_lcd_state = I2C_LCD_IDOLE;
            else wait--;
            break;
    }
}
