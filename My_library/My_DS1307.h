/* 
 * File:   My_DS1307.h
 * Author: kerikun11
 *
 * Created on 2015/11/16, 20:40
 */

#ifndef MY_DS1307_H
#define	MY_DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif

    //*************************** I2C_RTC DS1307 ***************************//
#define DS1307_ADRES 0x68

    void RTC_Write(uint8_t Reg, uint8_t data);
    uint8_t RTC_Read(uint8_t Reg);

#ifdef	__cplusplus
}
#endif

#endif	/* MY_DS1307_H */

