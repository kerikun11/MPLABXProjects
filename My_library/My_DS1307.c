#include "My_DS1307.h"

#include <My_I2C.h>

//*************************** I2C_RTC DS1307 ***************************//

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
