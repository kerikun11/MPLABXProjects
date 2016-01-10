#include <xc.h>
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

void interrupt InterFunction(void);
void I2C_IdleCheck(char mask);
void InterI2C(void);
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
int AckCheck;
char heart[7] = {
    0b01010,
    0b11011,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
};

/*******************************************************************************
 *  InterFunction()   割り込みの処理                                            *
 *******************************************************************************/
void interrupt InterFunction(void) {
    // Ｉ２Ｃ関連の割り込み処理
    InterI2C();
}
/*******************************************************************************
 *  skI2Clib - Ｉ２Ｃ関数ライブラリ(PIC12F/16F18xxシリーズ用)                   *
 *             このライブラリはI2Cデバイス(RTC/EEPROM等)と接続を行う為の関数集  *
 *                                                                              *
 *    InterI2C       - Ｉ２Ｃ関連の割り込み処理                                 *
 *    InitI2C_Master - Ｉ２Ｃ通信のマスターモードで初期化を行う処理             *
 *    I2C_Start      - スレーブにスタートコンディションを発行する処理           *
 *    I2C_rStart     - スレーブにリピート・スタートコンディションを発行する処理 *
 *    I2C_Stop       - スレーブにストップコンディションを発行する処理           *
 *    I2C_Send       - スレーブにデータを１バイト送信する処理                   *
 *    I2C_Receive    - スレーブからデータを１バイト受信する処理                 *
 *                                                                              *
 *    メモ：SDA/SCLピンは必ず「デジタル入力ピン」に設定を行って下さい。         *
 *          通信クロックは100KHz(CPU8MHz)での初期化です。                       *
 * ============================================================================ *
 *  VERSION DATE        BY                    CHANGE/COMMENT                    *
 * ---------------------------------------------------------------------------- *
 *  1.00    2012-01-20  きむ茶工房(きむしげ)  Create                            *
 *  1.01    2013-02-16  きむ茶工房(きむしげ)  XC8 C Compiler 対応に変更         *
 * ============================================================================ *
 *  PIC 12F1822 16F18xx (16F1827はSSP2利用不可)(16F19xxは利用不可)              *
 *  MPLAB IDE(V8.84)                                                            *
 *  MPLAB(R) XC8 C Compiler Version 1.00                                        *
 *******************************************************************************/
// アイドル状態のチェック
// ACKEN RCEN PEN RSEN SEN R/W BF が全て０ならＯＫ

void I2C_IdleCheck(char mask) {
    while ((SSP1CON2 & 0x1F) | (SSP1STAT & mask));
}

/*******************************************************************************
 *  InterI2C( void )                                                            *
 *    Ｉ２Ｃ関連の割り込み処理                                                  *
 *     この関数はメインプログラムの割込み関数で呼びます                         *
 *******************************************************************************/
void InterI2C(void) {
    if (SSP1IF == 1) { // SSP(I2C)割り込み発生か？
        if (AckCheck == 1) AckCheck = 0;
        SSP1IF = 0; // フラグクリア
    }
    if (BCL1IF == 1) { // MSSP(I2C)バス衝突割り込み発生か？
        BCL1IF = 0; // 今回はフラグのみクリアする(無処理)
    }
}

/*******************************************************************************
 *  InitI2C_Master()                                                            *
 *    Ｉ２Ｃ通信のマスターモードで初期化を行う処理                              *
 *                                                                              *
 *    注)クロック8MHzでの設定です、他のクロックはSSP1ADDを変更する必要が有ります*
 *******************************************************************************/
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

/*******************************************************************************
 *  ans = I2C_Start(adrs,rw)                                                    *
 *    スレーブにスタートコンディションを発行する処理                            *
 *                                                                              *
 *    adrs : スレーブのアドレスを指定します                                     *
 *    rw   : スレーブに対する動作の指定をします                                 *
 *           0=スレーブに書込みなさい要求　1=スレーブに送信しなさい要求         *
 *    ans  : 0=正常　1=異常(相手からACKが返ってこない)                          *
 *******************************************************************************/
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

/*******************************************************************************
 *  ans = I2C_rStart(adrs,rw)                                                   *
 *    スレーブにリピート・スタートコンディションを発行する処理                  *
 *                                                                              *
 *    adrs : スレーブのアドレスを指定します                                     *
 *    rw   : スレーブに対する動作の指定をします                                 *
 *           0=スレーブに書込みなさい要求　1=スレーブに送信しなさい要求         *
 *    ans  : 0=正常　1:異常(相手からACKが返ってこない)                          *
 *******************************************************************************/
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

/*******************************************************************************
 *  I2C_Stop()                                                                  *
 *    スレーブにストップコンディションを発行する処理                            *
 *******************************************************************************/
void I2C_Stop(void) {
    // ストップ(STOP CONDITION)
    I2C_IdleCheck(0x5);
    SSP1CON2bits.PEN = 1;
}

/*******************************************************************************
 *  ans = I2C_Send(dt)                                                          *
 *    スレーブにデータを１バイト送信する処理                                    *
 *                                                                              *
 *    dt  : 送信するデータを指定します                                          *
 *    ans  : 0=正常　1=異常(相手からACKが返ってこない又はNOACKを返した)         *
 *******************************************************************************/
int I2C_Send(char dt) {
    I2C_IdleCheck(0x5);
    AckCheck = 1;
    SSP1BUF = dt; // データを送信
    while (AckCheck); // 相手からのACK返答を待つ
    return SSP1CON2bits.ACKSTAT;
}

/*******************************************************************************
 *  ans = I2C_Receive(ack)                                                      *
 *    スレーブからデータを１バイト受信する処理                                  *
 *                                                                              *
 *    ack  : スレーブへの返答データを指定します                                 *
 *           0:ACKを返す　1:NOACKを返す(受信データが最後なら1)                  *
 *    ans  : 受信したデータを返す                                               *
 *******************************************************************************/
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
/*******************************************************************************
 *  skI2CLCDlib - Ｉ２Ｃ接続ＬＣＤ関数ライブラリ                                *
 *             このライブラリは、秋月電子Ｉ２Ｃ接続小型ＬＣＤモジュール用です。 *
 *                                                                              *
 *    LCD_Init      - ＬＣＤの初期化を行う処理                                  *
 *    LCD_Clear     - ＬＣＤモジュールの画面を消す処理                          *
 *    LCD_SetCursor - ＬＣＤモジュール画面内のカーソル位置を移動する処理        *
 *    LCD_Putc      - ＬＣＤにデータを１バイト出力する処理                      *
 *    LCD_Puts      - ＬＣＤに文字列データを出力する処理                        *
 *    LCD_CreateChar - オリジナルのキャラクタを登録します                       *
 *                                                                              *
 *    メモ：__delay_us() and __delay_ms() を使用しているので "skI2CLCDlib.h" に *
 *         "#define _XTAL_FREQ 8000000"が記述されています、                     *
 *         8MHz以外のCPUクロックにする人は書き換えましょう。                    *
 * ============================================================================ *
 *  VERSION DATE        BY                    CHANGE/COMMENT                    *
 * ---------------------------------------------------------------------------- *
 *  1.00    2013-07-25  きむ茶工房(きむしげ)  Create                            *
 * ============================================================================ *
 *  PIC 12F1822 16F1827 (このライブラリ自体は他のＰＩＣでもＯＫと思います)      *
 *  MPLAB IDE(V8.84)                                                            *
 *  MPLAB(R) XC8 C Compiler Version 1.00                                        *
 *******************************************************************************/
// ＬＣＤにコマンドを発行する処理

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

/*******************************************************************************
 *  LCD_Clear( )                                                                *
 *    ＬＣＤモジュールの画面を消す処理                                          *
 *******************************************************************************/
void LCD_Clear(void) {
    command(0x01); // Clear Display : 画面全体に20Hのスペースで表示、カーソルはcol=0,row=0に移動
    __delay_us(1100); // LCDが処理(1.08ms)するのを待ちます
}

/*******************************************************************************
 *  LCD_SetCursor(col,row)                                                      *
 *    ＬＣＤモジュール画面内のカーソル位置を移動する処理                        *
 *                                                                              *
 *    col : 横(列)方向のカーソル位置(0-7)                                       *
 *    row : 縦(行)方向のカーソル位置(0-1)                                       *
 *******************************************************************************/
void LCD_SetCursor(int col, int row) {
    int row_offsets[] = {0x00, 0x40};

    command(0x80 | (col + row_offsets[row])); // Set DDRAM Adddress : 00H-07H,40H-47H
}

/*******************************************************************************
 *  LCD_Putc(c)                                                                 *
 *    文字列は、NULL(0x00)まで繰返し出力します。                                *
 *                                                                              *
 *    c :  出力する文字データを指定                                             *
 *******************************************************************************/
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

/*******************************************************************************
 *  LCD_Puts(*s)                                                                *
 *    ＬＣＤに文字列データを出力する処理                                        *
 *    文字列は、NULL(0x00)まで繰返し出力します。                                *
 *                                                                              *
 *    *s :  出力する文字列のデータを格納した場所のアドレスを指定                *
 *******************************************************************************/
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

/*******************************************************************************
 *  LCD_CreateChar(p,*dt)                                                       *
 *    オリジナルのキャラクタを登録します                                        *
 *                                                                              *
 *    p   : 登録する場所の指定(０〜５の６ヶ所のみ)                              *
 *    *dt : 登録したいキャラクタのデータを格納したバッファを指定                *
 ********************************************************************************/
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

/*******************************************************************************
 *  LCD_Init( )                                                                 *
 *    ＬＣＤの初期化を行う処理                                                  *
 *******************************************************************************/
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

void RTC_write(unsigned char Reg, unsigned char c) {
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

unsigned char RTC_read(unsigned char Reg, unsigned char c) {
    int ans;
    unsigned char data;

    ans = I2C_Start(DS1307_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg); // control byte の送信(コマンドを指定)
    }
    ans = I2C_Start(DS1307_ADRES, R_1); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        data = I2C_Receive(1); // control byte の送信(コマンドを指定)
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    return data;
}

/*******************************************************************************
 *  メインの処理                                                                *
 *******************************************************************************/
void main(void) {
    OSCCON = 0b01110010; // 内部クロックは８ＭＨｚとする
    OPTION_REG = 0b00000000; // デジタルI/Oに内部プルアップ抵抗を使用する
    ANSELA = 0b00000000; // AN0-AN4は使用しない全てデジタルI/Oとする
    ANSELB = 0b00000000; // AN5-AN11は使用しない全てデジタルI/Oとする
    TRISA = 0b00000000; // ピン(RA)は全て出力に割当てる(RA5は入力のみとなる)
    TRISB = 0b00010010; // ピン(RB)はRB4(SCL1)/RB1(SDA1)のみ入力
    WPUB = 0b00010010; // RB1/4は内部プルアップ抵抗を指定する
    PORTA = 0b00000000; // RA出力ピンの初期化(全てLOWにする)
    PORTB = 0b00000000; // RB出力ピンの初期化(全てLOWにする)

    InitI2C_Master(); // Ｉ２Ｃの初期化処理

    // ＬＣＤモジュールの初期化処理
    LCD_Init();

    LCD_CreateChar(0x00, heart); // 1番にオリジナルキャラクタを登録する

    LCD_SetCursor(0, 0); // 表示位置を設定する
    LCD_Puts("Hello");
    //LCD_Putc(0x00) ;            // 1番に登録したキャラを表示する
    LCD_SetCursor(2, 1); // 表示位置を設定する
    LCD_Puts("World!");

    while (1) {
    }

}
