#include "My_I2C_old.h"

//************************************************************************//
//*************************** PIC's I2C Module ***************************//
//************************************************************************//

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

/***********************************************************************/
/*************************** IC's I2C Module ***************************/
/***********************************************************************/

//*************************** I2C_RTC DS1307 ***************************//
#ifdef DS1307

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
#endif /* DS1307 */

//*************************** I2C_ThermoMeter TM ***************************//
#ifdef MCP9803

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
    return ((0xFF00 & (dataH << 8)) + (0xFF & dataL));
}
#endif /* MCP9803 */

//*************************** I2C_EEPROM ***************************//
#ifdef EEPROM24LC64

void EEP_write(uint8_t Reg_h, uint8_t Reg_l, uint8_t data) {
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

uint8_t EEP_read(uint8_t Reg_h, uint8_t Reg_l) {
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

uint16_t EEP_read16(uint8_t Reg_h, uint8_t Reg_l) {
    uint8_t ans;
    uint8_t d[4];
    uint16_t data;

    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(EEPROM24LC64_ADRES, R_1); // reスタートコンディションを発行する
    if (ans == 0) {
        d[3] = I2C_Receive(0);
        d[2] = I2C_Receive(0);
        d[1] = I2C_Receive(0);
        d[0] = I2C_Receive(1);
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    data = (uint16_t) ((d[1] << 8) + d[0]);
    return data;
}

uint32_t EEP_read32(uint8_t Reg_h, uint8_t Reg_l) {
    uint8_t ans;
    uint8_t d[4];
    uint32_t data;

    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
    }
    ans = I2C_rStart(EEPROM24LC64_ADRES, R_1); // reスタートコンディションを発行する
    if (ans == 0) {
        d[3] = I2C_Receive(0);
        d[2] = I2C_Receive(0);
        d[1] = I2C_Receive(0);
        d[0] = I2C_Receive(1);
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
    return (uint32_t) (d[3] << 24)+(d[2] << 16)+(d[1] << 8) + d[0];
}

void EEP_write16(uint8_t Reg_h, uint8_t Reg_l, uint16_t data) {
    uint8_t ans;
    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
        I2C_Send(data >> 8); // data byte の送信
        I2C_Send(data >> 0); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}

void EEP_write32(uint8_t Reg_h, uint8_t Reg_l, uint32_t data) {
    uint8_t ans;
    ans = I2C_Start(EEPROM24LC64_ADRES, W_0); // スタートコンディションを発行する
    if (ans == 0) {
        // command word の送信
        I2C_Send(Reg_h); // control byte の送信(コマンドを指定)
        I2C_Send(Reg_l); // control byte の送信(コマンドを指定)
        I2C_Send(data >> 24); // data byte の送信
        I2C_Send(data >> 16); // data byte の送信
        I2C_Send(data >> 8); // data byte の送信
        I2C_Send(data >> 0); // data byte の送信
    }
    I2C_Stop(); // ストップコンディションを発行する
    __delay_us(26);
}
#endif /* EEPROM24LC64 */

