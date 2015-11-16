#include "My_MCP9803.h"

#include <My_I2C.h>

//*************************** I2C_ThermoMeter MCP9803 ***************************//

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
