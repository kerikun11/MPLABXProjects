/* 
 * File:   My_header.h
 * Author: kerikun11
 *
 * Created on 2015/01/09, 9:44
 */
#include <xc.h>
#include <stdint.h>

#ifndef MY_HEADER_H
#define	MY_HEADER_H

//*************************** timer0 ***************************//

void timer0_init(uint8_t prescaler) { // prescaler is 0~8
    if (prescaler == 0) {
        OPTION_REGbits.PSA = 1;
    } else {
        OPTION_REGbits.PSA = 0;
        OPTION_REGbits.PS = prescaler - 1;
    }
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.TMR0SE = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.PEIE = 1;
}
//*************************** timer1 ***************************//

void timer1_init(uint8_t prescaler) { // prescaler is 0~3
    T1CONbits.TMR1ON = 1;
    T1CONbits.TMR1CS = 0; //Fosc/4
    T1CONbits.T1CKPS = prescaler;
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
}

//*************************** adc ***************************//
#define FVR 3
#define VDD 0

void adc_init(uint8_t p_ref) {
    ADCON1bits.ADFM = 1; //H + L = 8 + 2
    ADCON1bits.ADCS = 6; // clock is Fosc/4
    ADCON1bits.ADNREF = 0; //Vref- = Vss
    ADCON1bits.ADPREF = p_ref; //Vref+ = p_ref
    if (p_ref == 3) FVRCON = 0x83; //4.096V
}

uint16_t adc(uint8_t ch) {
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = ch;
    __delay_us(20);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

//*************************** button ***************************//
//タイマー割り込み関数にbutton_timer_interrupt(&button_t,!SW)を書いておくこと。
// 32MHz, 16bit, prescaler=1:4
#define PRESS_LEVEL 2
#define LONG_HOLD_LEVEL1  30
#define LONG_HOLD_LEVEL2  75
#define LONG_HOLD_LEVEL3  150

typedef struct button {
    uint16_t cnt_sw;

    union {
        uint8_t flags;

        struct {
            uint8_t press : 1;
            uint8_t long_hold_1 : 1;
            uint8_t long_hold_2 : 1;
            uint8_t long_hold_3 : 1;
            uint8_t pressing : 1;
            uint8_t long_holding_1 : 1;
            uint8_t long_holding_2 : 1;
            uint8_t long_holding_3 : 1;
        } flag;
    };
} button_t;

void button_timer_interrupt(button_t *bt, uint8_t sw_value) {
    if (sw_value) {
        if (bt->cnt_sw < LONG_HOLD_LEVEL3 + 1) bt->cnt_sw++;
        if (bt->cnt_sw == LONG_HOLD_LEVEL3)bt->flag.long_holding_3 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL2)bt->flag.long_holding_2 = 1;
        if (bt->cnt_sw == LONG_HOLD_LEVEL1)bt->flag.long_holding_1 = 1;
        if (bt->cnt_sw == PRESS_LEVEL)bt->flag.pressing = 1;
    } else {
        if (bt->cnt_sw >= LONG_HOLD_LEVEL3)bt->flag.long_hold_3 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL2)bt->flag.long_hold_2 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL1)bt->flag.long_hold_1 = 1;
        else if (bt->cnt_sw >= PRESS_LEVEL)bt->flag.press = 1;
        bt->cnt_sw = 0;
        bt->flags &= 0x0F;
    }
}
//*************************** ringbuf ***************************//
//ringbuf_init()を行うこと。

typedef struct ringbuf {
    uint8_t *buf;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
} ringbuf_t;

void ringbuf_init(ringbuf_t *rb, uint8_t internal_buf[], uint8_t bufsize) {
    rb->buf = internal_buf;
    rb->size = bufsize;
    rb->head = 0;
    rb->tail = 0;
}

void ringbuf_push(ringbuf_t *rb, uint8_t asciicode) {
    rb->buf[rb->head] = asciicode;
    rb->head++;
    if (rb->head >= rb->size) {
        rb->head = 0;
    }
}

uint8_t ringbuf_pop(ringbuf_t * rb) {
    uint8_t ret = rb->buf[rb->tail];
    rb->tail++;
    if (rb->tail >= rb->size) {
        rb->tail = 0;
    }
    return ret;
}

uint8_t ringbuf_num(ringbuf_t * rb) {
    if (rb->head >= rb->tail) {
        return (rb->head - rb->tail);
    } else {
        return (rb->size + rb->head - rb->tail);
    }
}
//*************************** UART ***************************//
#define PIC16F1827 0
ringbuf_t tx_buf;

void UART_init(uint8_t device) {
    if (device == PIC16F1827) {
        SPEN = 1;
        RCSTA = 0x90;
        BRG16 = 0;
        SPBRGH = 0;
        SPBRGL = 207;
        TXSTA = 0x24;
        PIE1bits.RCIE = 1;
        INTCONbits.PEIE = 1;
    }
}

void tx_send(uint8_t asciicode) {
    ringbuf_push(&tx_buf, asciicode);
    PIE1bits.TXIE = 1;
}

void tx_sends(const uint8_t asciicode[]) {
    uint8_t i;
    for (i = 0; asciicode[i]; i++) {
        ringbuf_push(&tx_buf, asciicode[i]);
    }
    PIE1bits.TXIE = 1;
}

void interrupt_TXIF(void) {
    if (TXIE && TXIF) {
        TXIF = 0;
        if (ringbuf_num(&tx_buf) > 0) {
            TXREG = ringbuf_pop(&tx_buf);
        } else {
            PIE1bits.TXIE = 0;
        }
    }
}

//*************************** Delay_ms ***************************//

void Delay_ms(uint16_t ms) {
    uint16_t i;
    for (i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}
//*************************** I2C ***************************//
#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1

void I2C_IdleCheck(char mask) {
    while ((SSP1CON2 & 0x1F) | (SSP1STAT & mask));
}

void I2C_init(void) {
    SSP1STAT = 0b10000000; // 標準速度モードに設定する(100kHz)
    SSP1CON1 = 0b00101000; // SDA/SCLピンはI2Cで使用し、マスターモードとする
    SSP1ADD = 0x13; // クロック=FOSC/((SSPADD + 1)*4) 8MHz/((0x13+1)*4)=0.1(100KHz)
    //SSP1IE = 1; // SSP(I2C)割り込みを許可する
    //BCL1IE = 1; // MSSP(I2C)バス衝突割り込みを許可する
    SSP1IF = 0; // SSP(I2C)割り込みフラグをクリアする
    BCL1IF = 0; // MSSP(I2C)バス衝突割り込みフラグをクリアする
}

uint8_t I2C_Start(uint8_t adrs, uint8_t rw) {
    // スタート(START CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.SEN = 1;
    // [スレーブのアドレス]を送信する
    I2C_IdleCheck(0x5);
    SSP1IF = 0;
    SSP1BUF = (uint8_t) ((adrs << 1) + rw); // アドレス + R/Wを送信
    while (!SSP1IF); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

uint8_t I2C_rStart(int adrs, int rw) {
    // リピート・スタート(REPEATED START CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.RSEN = 1;
    // [スレーブのアドレス]を送信する
    I2C_IdleCheck(0x5);
    SSP1IF = 0;
    SSP1BUF = (char) ((adrs << 1) + rw); // アドレス + R/Wを送信
    while (!SSP1IF); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

void I2C_Stop(void) {
    // ストップ(STOP CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.PEN = 1;
}

uint8_t I2C_Send(uint8_t data) {
    I2C_IdleCheck(0x5);
    SSP1IF = 0;
    SSP1BUF = data; // データを送信
    while (!SSP1IF); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

uint8_t I2C_Receive(uint8_t ack) {
    uint8_t data;

    I2C_IdleCheck(0x5);
    SSP1CON2bits.RCEN = 1; // 受信を許可する
    I2C_IdleCheck(0x4);
    data = SSP1BUF; // データの受信
    I2C_IdleCheck(0x5);
    SSP1CON2bits.ACKDT = ack; // ACKデータのセット
    SSP1CON2bits.ACKEN = 1; // ACKデータを返す
    return data;
}

//*************************** I2C_LCD ***************************//
#define ST7032_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス

void LCD_Command(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void LCD_Clear(void) {
    LCD_Command(0x01); // Clear Display : 画面全体に20Hのｽﾍﾟｰｽで表示、ｶｰｿﾙはcol=0,row=0に移動
    __delay_us(1100); // LCDが処理(1.08ms)するのを待ちます
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};

    LCD_Command(0x80 | (col + row_offsets[row])); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void LCD_Putc(uint8_t c) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b11000000); // control byte の送信(データを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void LCD_Puts(const uint8_t * s) {
    int ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        while (*s) {
            I2C_Send(*s++); // data byte の送信(連続送信)
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void LCD_CreateChar(int p, char *dt) {
    uint8_t ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
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

void LCD_init(void) {
    __delay_ms(40); // 電源ＯＮ後40msまで待ってから初期化
    LCD_Command(0x38); // function set           : データ線は8本・表示は２行・フォントは5x8ドット
    LCD_Command(0x39); // function set           : 拡張コマンドの設定を有効にする
    LCD_Command(0x14); // Internal OSC frequency : バイアスの選択と内部OSC周波数の調整
    LCD_Command(0x70); // Contrast set           : コントラスト調整データ(下位4ビット)
    LCD_Command(0x56); // Contrast set           : 昇圧回路有効、コントラスト調整データ(上位2ビット)
    LCD_Command(0x6C); // Follower control       : フォロア回路をON、増幅率の調整を行う
    __delay_ms(200); // 電力が安定するまで待つ
    LCD_Command(0x38); // function set           : 拡張コマンドを設定を無効にする
    LCD_Command(0x0C); // display control        : 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
    LCD_Command(0x06); // entry mode set         : 文字を表示した次にカーソルを移動するを指示
    LCD_Clear(); // Clear Display          : 画面を消去する
}

//*************************** I2C_RTC ***************************//
#define DS1307_ADRES 0x68

void RTC_Write(uint8_t Reg, uint8_t data) {
    uint8_t ans;

    ans = I2C_Start(DS1307_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg); // control byte の送信(コマンドを指定)
        I2C_Send(data); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

uint8_t RTC_Read(uint8_t Reg) {
    uint8_t ans;
    uint8_t data;

    ans = I2C_Start(DS1307_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(Reg); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(DS1307_ADRES, R_1); // reスタートコンディションを発行する
    if (ans == 0) {
        data = I2C_Receive(1);
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    return data;
}
//*************************** I2C_ThermoMeter TM ***************************//
#define MCP9803_ADRES 0x48

void TM_init(uint8_t config) {
    uint8_t ans;
    ans = I2C_Start(MCP9803_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(0x01); // control byte の送信(コマンドを指定)
        I2C_Send(config);
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

uint16_t TM_Read() {
    uint8_t dataH;
    uint8_t dataL;
    uint8_t ans;
    ans = I2C_Start(MCP9803_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(0x00); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(MCP9803_ADRES, R_1); // スタートコンディションを発行する
    if (ans == 0) {
        dataH = I2C_Receive(0); // control byte の送信(コマンドを指定)
        dataL = I2C_Receive(1); // control byte の送信(コマンドを指定)
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    /*
    if (ans)tx_sends("Failed\n");
    else tx_sends("Successful\n");
     */
    return (dataH << 8) +dataL;
}
//*************************** I2C_EEPROM ***************************//
#define EEPROM24LC64_ADRES 0x50

void EEP_Write(uint8_t Reg_h, uint8_t Reg_l, uint8_t data) {
    uint8_t ans;
    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
        I2C_Send(data); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

uint8_t EEP_Read(uint8_t Reg_h, uint8_t Reg_l) {
    uint8_t ans;
    uint8_t data;

    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(EEPROM24LC64_ADRES, R_1); // reスタートコンディションを発行する
    if (ans == 0) {
        data = I2C_Receive(1);
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    return data;
}

void EEP_Writes(uint8_t Reg_h, uint8_t Reg_l, uint8_t data_0, uint8_t data_1) {
    uint8_t ans;
    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
        I2C_Send(data_0); // data byte の送信
        I2C_Send(data_1); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

#endif	/* MY_HEADER_H */