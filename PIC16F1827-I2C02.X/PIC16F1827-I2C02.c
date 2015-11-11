#include <xc.h>
#include <stdint.h>
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
        PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF);
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);
#define _XTAL_FREQ 8000000    // 使用するPIC等により動作周波数値を設定する
#define ST7032_ADRES 0x3E      // 秋月電子のI2C接続小型LCDモジュールのアドレス
#define DS1307_ADRES 0x68
#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1
#define LONG_HOLD_LEVEL1  5
#define LONG_HOLD_LEVEL2  100

typedef struct button {
    uint8_t cnt_sw;
    uint8_t press_flag;
    uint8_t long_hold_flag1;
    uint8_t long_hold_flag2;
} button_t;
button_t sw_RA0;
button_t sw_RA1;
int AckCheck;
unsigned char cnt_t1;
unsigned char ss;
unsigned char mm;
unsigned char hh;
unsigned char EE;
unsigned char DD;
unsigned char MM;
unsigned char YY;

void interrupt InterFunction(void);
void button_timer(button_t *bt, uint8_t sw_value);
void I2C_IdleCheck(char mask);
void InitI2C_Master(void);
int I2C_Start(int adrs, int rw);
int I2C_rStart(int adrs, int rw);
void I2C_Stop(void);
int I2C_Send(char dt);
char I2C_Receive(int ack);
void command(unsigned char c);
void LCD_Clear(void);
void LCD_SetCursor(int col, int row);
void LCD_Putc(char c);
void LCD_Puts(const char * s);
void LCD_CreateChar(int p, char *dt);
void LCD_Init(void);
void RTC_Write(unsigned char Reg, unsigned char c);
unsigned char RTC_Read(unsigned char Reg);
uint8_t month_length(uint8_t year, uint8_t month);
void timeset(uint8_t *value, uint8_t min_num, uint8_t max_num, uint8_t Reg, uint8_t column, uint8_t row);
void display(void);

void interrupt InterFunction(void) {
    if (SSP1IF == 1) { // SSP(I2C)割り込み発生か？
        if (AckCheck == 1) AckCheck = 0;
        SSP1IF = 0; // フラグクリア
    }
    if (BCL1IF == 1) { // MSSP(I2C)バス衝突割り込み発生か？
        BCL1IF = 0; // 今回はフラグのみクリアする(無処理)
    }
    if (TMR1IF == 1) {
        TMR1IF = 0;
        cnt_t1++;
        button_timer(&sw_RA0, !RA0);
        button_timer(&sw_RA1, !RA1);
    }
}

void button_timer(button_t *bt, uint8_t sw_value) {
    if (sw_value) {
        if (bt->cnt_sw < LONG_HOLD_LEVEL2 + 1) bt->cnt_sw++;
    } else {
        if (bt->cnt_sw >= LONG_HOLD_LEVEL2)bt->long_hold_flag2 = 1;
        else if (bt->cnt_sw >= LONG_HOLD_LEVEL1 && bt->cnt_sw < LONG_HOLD_LEVEL2)bt->long_hold_flag1 = 1;
        else if (bt->cnt_sw >= 1 && bt->cnt_sw < LONG_HOLD_LEVEL1)bt->press_flag = 1;
        bt->cnt_sw = 0;
    }
}

void I2C_IdleCheck(char mask) {
    while ((SSP1CON2 & 0x1F) | (SSP1STAT & mask));
}

void InitI2C_Master(void) {
    SSP1STAT = 0b10000000; // 標準速度モードに設定する(100kHz)
    SSP1CON1 = 0b00101000; // SDA/SCLピンはI2Cで使用し、マスターモードとする
    SSP1ADD = 0x13; // クロック=FOSC/((SSPADD + 1)*4) 8MHz/((0x13+1)*4)=0.1(100KHz)
    SSP1IE = 1; // SSP(I2C)割り込みを許可する
    BCL1IE = 1; // MSSP(I2C)バス衝突割り込みを許可する
    PEIE = 1; // 周辺装置割り込みを許可する
    GIE = 1; // 全割り込み処理を許可する
    SSP1IF = 0; // SSP(I2C)割り込みフラグをクリアする
    BCL1IF = 0; // MSSP(I2C)バス衝突割り込みフラグをクリアする
}

int I2C_Start(int adrs, int rw) {
    // スタート(START CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.SEN = 1;
    // [スレーブのアドレス]を送信する
    I2C_IdleCheck(0x5);
    AckCheck = 1;
    SSP1BUF = (char) ((adrs << 1) + rw); // アドレス + R/Wを送信
    while (AckCheck); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

int I2C_rStart(int adrs, int rw) {
    // リピート・スタート(REPEATED START CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.RSEN = 1;
    // [スレーブのアドレス]を送信する
    I2C_IdleCheck(0x5);
    AckCheck = 1;
    SSP1BUF = (char) ((adrs << 1) + rw); // アドレス + R/Wを送信
    while (AckCheck); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

void I2C_Stop(void) {
    // ストップ(STOP CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.PEN = 1;
}

int I2C_Send(char dt) {
    I2C_IdleCheck(0x5);
    AckCheck = 1;
    SSP1BUF = dt; // データを送信
    while (AckCheck); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

char I2C_Receive(int ack) {
    char dt;

    I2C_IdleCheck(0x5);
    SSP1CON2bits.RCEN = 1; // 受信を許可する
    I2C_IdleCheck(0x4);
    dt = SSP1BUF; // データの受信
    I2C_IdleCheck(0x5);
    SSP1CON2bits.ACKDT = ack; // ACKデータのセット
    SSP1CON2bits.ACKEN = 1; // ACKデータを返す
    return dt;
}

void command(unsigned char c) {
    int ans;

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
    command(0x01); // Clear Display : 画面全体に20Hのｽﾍﾟｰｽで表示、ｶｰｿﾙはcol=0,row=0に移動
    __delay_us(1100); // LCDが処理(1.08ms)するのを待ちます
}

void LCD_SetCursor(int col, int row) {
    int row_offsets[] = {0x00, 0x40};

    command(0x80 | (col + row_offsets[row])); // Set DDRAM Adddress : 00H-07H,40H-47H
}

void LCD_Putc(char c) {
    int ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(0b11000000); // control byte の送信(データを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void LCD_Puts(const char * s) {
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
    int ans;

    ans = I2C_Start(ST7032_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        //  LCDにキャラ保存先のアドレスを指示する
        I2C_Send(0b10000000); // control byte の送信(コマンドを指定)
        I2C_Send(0x40 | (p << 3));
        __delay_us(26);
        //  LCDにキャラデータを送信する
        I2C_Send(0b01000000); // control byte の送信(データを指定)
        for (int i = 0; i < 7; i++) {
            I2C_Send(*dt++);
            __delay_us(26);
        }
    }
    I2C_Stop(); // ストップコンディションを発行する
}

void LCD_Init(void) {
    __delay_ms(40); // 電源ＯＮ後40msまで待ってから初期化
    command(0x38); // function set           : データ線は8本・表示は２行・フォントは5x8ドット
    command(0x39); // function set           : 拡張コマンドの設定を有効にする
    command(0x14); // Internal OSC frequency : バイアスの選択と内部OSC周波数の調整
    command(0x70); // Contrast set           : コントラスト調整データ(下位4ビット)
    command(0x56); // Contrast set           : 昇圧回路有効、コントラスト調整データ(上位2ビット)
    command(0x6C); // Follower control       : フォロア回路をON、増幅率の調整を行う
    __delay_ms(200); // 電力が安定するまで待つ
    command(0x38); // function set           : 拡張コマンドを設定を無効にする
    command(0x0C); // display control        : 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
    command(0x06); // entry mode set         : 文字を表示した次にカーソルを移動するを指示
    LCD_Clear(); // Clear Display          : 画面を消去する
}

void RTC_Write(unsigned char Reg, unsigned char c) {
    int ans;

    ans = I2C_Start(DS1307_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg); // control byte の送信(コマンドを指定)
        I2C_Send(c); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

unsigned char RTC_Read(unsigned char Reg) {
    int ans;
    unsigned char data;

    ans = I2C_Start(DS1307_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(DS1307_ADRES, R_1); // reスタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        data = I2C_Receive(1); // control byte の送信(コマンドを指定)
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    return data;
}

uint8_t month_length(uint8_t year, uint8_t month) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if (year % 4 == 0) return 29;
            else return 28;
    }
}

void timeset(uint8_t *value, uint8_t min_num, uint8_t max_num, uint8_t Reg, uint8_t column, uint8_t row) {
    sw_RA1.press_flag = 0;
    sw_RA1.long_hold_flag1 = 0;
    sw_RA1.long_hold_flag2 = 0;
    while (!sw_RA0.press_flag) {
        if (cnt_t1 % 4 >= 2) {
            display();
            LCD_SetCursor(column, row); // 表示位置を設定する
            LCD_Puts("  ");
        } else {
            *value = RTC_Read(Reg);
            display();
            LCD_SetCursor(column, row); // 表示位置を設定する
            LCD_Putc(*value / 16 + '0');
            LCD_Putc(*value % 16 + '0');
        }
        if (sw_RA1.press_flag) {
            sw_RA1.press_flag = 0;
            uint8_t t = *value % 16 + (*value / 16)*10;
            if (t >= max_num) {
                t = min_num;
            } else {
                t++;
            }
            *value = t % 10 + (t / 10)* 16;
            RTC_Write(Reg, *value);
        }
        if (sw_RA1.long_hold_flag1) {
            sw_RA1.long_hold_flag1 = 0;
            uint8_t t = *value % 16 + (*value / 16)*10;
            if (t + 9 >= max_num) {
                t = t % 10;
            } else {
                t += 10;
            }
            *value = t % 10 + (t / 10)* 16;
            RTC_Write(Reg, *value);
        }
    }
    sw_RA0.press_flag = 0;
}

void display(void) {
    ss = RTC_Read(0x00);
    mm = RTC_Read(0x01);
    hh = RTC_Read(0x02);
    EE = RTC_Read(0x03);
    DD = RTC_Read(0x04);
    MM = RTC_Read(0x05);
    YY = RTC_Read(0x06);
    LCD_SetCursor(0, 0); // 表示位置を設定する
    LCD_Putc(YY / 16 + '0');
    LCD_Putc(YY % 16 + '0');
    LCD_Putc('/');
    LCD_Putc(MM / 16 + '0');
    LCD_Putc(MM % 16 + '0');
    LCD_Putc('/');
    LCD_Putc(DD / 16 + '0');
    LCD_Putc(DD % 16 + '0');
    LCD_SetCursor(0, 1); // 表示位置を設定する
    LCD_Putc(hh / 16 + '0');
    LCD_Putc(hh % 16 + '0');
    LCD_Putc(':');
    LCD_Putc(mm / 16 + '0');
    LCD_Putc(mm % 16 + '0');
    LCD_Putc('-');
    LCD_Putc(ss / 16 + '0');
    LCD_Putc(ss % 16 + '0');
}

void main(void) {
    OSCCON = 0b01110010; // 内部クロックは８ＭＨｚとする
    OPTION_REG = 0b00000000; // デジタルI/Oに内部プルアップ抵抗を使用する
    ANSELA = 0b00000000; // AN0-AN4は使用しない全てデジタルI/Oとする
    ANSELB = 0b00000000; // AN5-AN11は使用しない全てデジタルI/Oとする
    TRISA = 0b00000011; // ピン(RA)は全て出力に割当てる(RA5は入力のみとなる)
    TRISB = 0b00010010; // ピン(RB)はRB4(SCL1)/RB1(SDA1)のみ入力
    WPUB = 0b00010010; // RB1/4は内部プルアップ抵抗を指定する
    PORTA = 0b00000000; // RA出力ピンの初期化(全てLOWにする)
    PORTB = 0b00000000; // RB出力ピンの初期化(全てLOWにする)

    T1CON = 0x21; //Fosc/4, ps:1/4, 7.62Hz, 131ms
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = 1;

    InitI2C_Master();

    LCD_Init();

    RTC_Write(0x07, 0x00);
    while (1) {
        display();
        if (sw_RA0.press_flag) {
            sw_RA0.press_flag = 0;
            timeset(&YY, 0, 99, 0x06, 0, 0);
            timeset(&MM, 1, 12, 0x05, 3, 0);
            timeset(&DD, 1, month_length(YY, MM), 0x04, 6, 0);
            timeset(&hh, 0, 23, 0x02, 0, 1);
            timeset(&mm, 0, 59, 0x01, 3, 1);
            timeset(&ss, 0, 59, 0x00, 6, 1);
        }
    }
}
