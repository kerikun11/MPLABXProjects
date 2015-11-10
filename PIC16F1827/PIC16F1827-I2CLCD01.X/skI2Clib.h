// skI2Clib.h
// Ｉ２Ｃ関数ライブラリ用インクルードファイル
#ifndef _SKI2CLIB_H_
#define _SKI2CLIB_H_

#define ACK   0
#define NOACK 1
#define RW_0  0
#define RW_1  1

void InterI2C( void ) ;
void InitI2C_Master() ;
int  I2C_Start(int adrs,int rw) ;
int  I2C_rStart(int adrs,int rw) ;
void I2C_Stop() ;
int  I2C_Send(char dt) ;
char I2C_Receive(int ack) ;


#endif
