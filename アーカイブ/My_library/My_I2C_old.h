/* 
 * File:   My_I2C.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:52
 */

#ifndef MY_I2C_OLD_H
#define	MY_I2C_OLD_H

#include <xc.h>
#include <stdint.h>

#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1

//*************************** PIC's I2C Module ***************************//

void I2C_IdleCheck(char mask);
void I2C_init(void);
uint8_t I2C_Start(uint8_t adrs, uint8_t rw);
uint8_t I2C_rStart(int adrs, int rw);
void I2C_Stop(void);
uint8_t I2C_Send(uint8_t data);
uint8_t I2C_Receive(uint8_t ack);

/*************************** IC's I2C Module ***************************/
//*************************** I2C_RTC DS1307 ***************************//
#ifdef DS1307
#define DS1307_ADRES 0x68

void RTC_Write(uint8_t Reg, uint8_t data);
uint8_t RTC_Read(uint8_t Reg);

#endif /* DS1307 */

//*************************** I2C_ThermoMeter TM ***************************//
#ifdef MCP9803
#define MCP9803_ADRES 0x48

void TM_init(uint8_t config);
uint16_t TM_Read();

#endif /* MCP9803 */

//*************************** I2C_EEPROM ***************************//
#ifdef EEPROM24LC64
#define EEPROM24LC64_ADRES 0x50

void EEP_write(uint8_t Reg_h, uint8_t Reg_l, uint8_t data);
uint8_t EEP_read(uint8_t Reg_h, uint8_t Reg_l);
uint16_t EEP_read16(uint8_t Reg_h, uint8_t Reg_l);
uint32_t EEP_read32(uint8_t Reg_h, uint8_t Reg_l);
void EEP_write16(uint8_t Reg_h, uint8_t Reg_l, uint16_t data);
void EEP_write32(uint8_t Reg_h, uint8_t Reg_l, uint32_t data);

#endif /* EEPROM24LC64 */

#endif	/* MY_I2C_OLD_H */
