#include "My_I2C.h"

uint8_t I2C_sent_flag;
uint8_t I2C_cfct_flag;
uint8_t I2C_busy;

uint8_t I2C_idole_check(uint8_t mask) {
    return ((SSP1CON2 & 0x1F) | (SSP1STAT & mask));
}

void I2C_start(void) {
    SSP1CON2bits.SEN = 1;
}

void I2C_restart(void) {
    SSP1CON2bits.RSEN = 1;
}

void I2C_stop(void) {
    SSP1CON2bits.PEN = 1;
}

void I2C_send(uint8_t data) {
    SSPBUF = data;
}

uint8_t I2C_ack(void) {
    return SSP1CON2bits.ACKSTAT;
}

void I2C_init_new(void) {
    SSP1STAT = 0b10000000;
    SSP1CON1 = 0b00101000;
    SSP1ADD = 0x13; // 0x77:100kHz 0x13:400kHz
    PIE1bits.SSP1IE = 1;
    IPR1bits.SSP1IP = 0;
    PIR1bits.SSP1IF = 0;
    PIE2bits.BCL1IE = 1;
    IPR2bits.BCL1IP = 0;
    PIR2bits.BCL1IF = 0;
    INTCONbits.PEIE = 1;
}

void I2C_ISR(void) {
    if (PIE1bits.SSP1IE && PIR1bits.SSP1IF) {
        PIR1bits.SSP1IF = 0;
        I2C_sent_flag = 1;
    }
    if (PIE2bits.BCL1IE && PIR2bits.BCL1IF) {
        PIR2bits.BCL1IF = 0;
        I2C_cfct_flag = 1;
    }
}

//*************************** old functions ***************************//
#if I2C_OLD_FUNCTIONS

void I2C_IdleCheck(char mask) {
    while ((SSP1CON2 & 0x1F) | (SSP1STAT & mask));
}

void I2C_init_old(void) {
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

#endif
