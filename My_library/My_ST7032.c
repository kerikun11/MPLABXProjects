#include "My_ST7032.h"

#include <My_I2C.h>

#define ST7032_ADDRESS 0x3E 

#define I2C_NULL        0
#define I2C_WAIT_0      0
#define I2C_WAIT_26US   1
#define I2C_WAIT_1MS    2
#define I2C_WAIT_40MS   3

st7032_state_t st7032_state;
ringbuf_t lcd_tx;

void ST7032_command(uint8_t command, uint8_t wait) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0x80); // command mode
    ringbuf_put(&lcd_tx, command); // command data
    ringbuf_put(&lcd_tx, 0); // stop bit
    ringbuf_put(&lcd_tx, wait); // wait
}

void ST7032_clear(void) {
    ST7032_command(0x01, I2C_WAIT_1MS); // Clear Display 
}

void ST7032_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    ST7032_command(0x80 | (col + row_offsets[row]), I2C_WAIT_0); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void ST7032_put(char c) {
    ringbuf_put(&lcd_tx, (ST7032_ADDRESS << 1) + W_0);
    ringbuf_put(&lcd_tx, 0b11000000); // control byte
    ringbuf_put(&lcd_tx, c); // data byte 
    ringbuf_put(&lcd_tx, I2C_NULL); // stop bit
    ringbuf_put(&lcd_tx, I2C_WAIT_26US); // wait
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
    ringbuf_put(&lcd_tx, I2C_NULL); // stop bit
    ringbuf_put(&lcd_tx, I2C_WAIT_26US); // wait
}

void ST7032_init(void) {
    I2C_init_new();

    static char buf[200];
    ringbuf_init(&lcd_tx, buf, sizeof (buf));

    ringbuf_put(&lcd_tx, I2C_NULL); // stop bit
    ringbuf_put(&lcd_tx, I2C_WAIT_40MS); // power ON wait

    ST7032_command(0x38, I2C_WAIT_26US);
    ST7032_command(0x39, I2C_WAIT_26US);
    ST7032_command(0x14, I2C_WAIT_26US);
    ST7032_command(0x70, I2C_WAIT_26US);
    ST7032_command(0x56, I2C_WAIT_26US);
    ST7032_command(0x6C, I2C_WAIT_40MS);
    ST7032_command(0x38, I2C_WAIT_26US);
    ST7032_command(0x0C, I2C_WAIT_26US);
    ST7032_command(0x06, I2C_WAIT_26US);
    ST7032_clear(); // Clear Display
}

void ST7032_task(void) {
    if (I2C_idole_check(0x05)) return;

    static uint16_t wait;
    static st7032_state_t st7032_state = ST7032_IDOLE;

    switch (st7032_state) {
        case ST7032_IDOLE:
            if (ringbuf_num(&lcd_tx)) {
                st7032_state = ST7032_START;
            }
            break;
        case ST7032_START:
            I2C_sent_flag = 1;
            I2C_start();
            st7032_state = ST7032_SEND;
            break;
        case ST7032_SEND:
            if (!I2C_sent_flag) return;
            uint8_t data = ringbuf_pop(&lcd_tx);
            if (data != 0) {
                I2C_sent_flag = 0;
                I2C_send(data);
            } else {
                wait = ringbuf_pop(&lcd_tx);
                switch (wait) {
                    case I2C_WAIT_0:
                        wait = 0;
                        break;
                    case I2C_WAIT_26US:
                        wait = 2;
                        break;
                    case I2C_WAIT_1MS:
                        wait = 25;
                        break;
                    case I2C_WAIT_40MS:
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
            I2C_stop();
            st7032_state = ST7032_WAIT;
            break;
        case ST7032_WAIT:
            if (wait == 0) st7032_state = ST7032_IDOLE;
            else wait--;
            break;
    }
}

/*************************** old_functions ***************************/
#if I2C_OLD_FUNCTIONS
#include <My_PIC.h>

void I2C_LCD_Command(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(I2C_LCD_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void I2C_LCD_Clear(void) {
    I2C_LCD_Command(0x01); // Clear Display : 画面全体に20Hのスペースで表示、カーソルはcol=0,row=0に移動
    __delay_us(1100); // LCDが処理(1.08ms)するのを待ちます
}

void I2C_LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};

    I2C_LCD_Command(0x80 | (col + row_offsets[row])); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void I2C_LCD_Putc(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(I2C_LCD_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b11000000); // control byte の送信(データを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void I2C_LCD_Puts(const uint8_t * s) {
    int ans;

    ans = I2C_Start(I2C_LCD_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        while (*s) {
            I2C_Send(*s++); // data byte の送信(連続送信)
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void I2C_LCD_CreateChar(int p, char *dt) {
    uint8_t ans;

    ans = I2C_Start(I2C_LCD_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        //  LCDにキャラ保存先のアドレスを指示する
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(0x40 | (p << 3));
        __delay_us(26);
        //  LCDにキャラデータを送信する
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        for (uint8_t i = 0; i < 7; i++) {
            I2C_Send(*dt++);
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void I2C_LCD_init(void) {
    I2C_init_old();

    for (uint8_t i = 0; i < 40; i++) __delay_ms(1); // 電源ＯＮ後40msまで待ってから初期化
    I2C_LCD_Command(0x38); // function set           : データ線は8本・表示は２行・フォントは5x8ドット
    I2C_LCD_Command(0x39); // function set           : 拡張コマンドの設定を有効にする
    I2C_LCD_Command(0x14); // Internal OSC frequency : バイアスの選択と内部OSC周波数の調整
    I2C_LCD_Command(0x70); // Contrast set           : コントラスト調整データ(下位4ビット)
    I2C_LCD_Command(0x56); // Contrast set           : 昇圧回路有効、コントラスト調整データ(上位2ビット)
    I2C_LCD_Command(0x6C); // Follower control       : フォロア回路をON、増幅率の調整を行う
    for (uint8_t i = 0; i < 40; i++) __delay_ms(1); // 電力が安定するまで待つ
    I2C_LCD_Command(0x38); // function set           : 拡張コマンドを設定を無効にする
    I2C_LCD_Command(0x0C); // display control        : 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
    I2C_LCD_Command(0x06); // entry mode set         : 文字を表示した次にカーソルを移動するを指示
    I2C_LCD_Clear(); // Clear Display          : 画面を消去する
}

#endif
