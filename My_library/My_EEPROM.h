/* 
 * File:   My_EEPROM.h
 * Author: kerikun11
 *
 * Created on 2015/11/16, 20:11
 */

#ifndef MY_EEPROM_H
#define	MY_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    //*************************** I2C_EEPROM ***************************//
#define EEPROM24LC64_ADRES 0x50

    void EEP_write(uint8_t Reg_h, uint8_t Reg_l, uint8_t data);
    uint8_t EEP_read(uint8_t Reg_h, uint8_t Reg_l);
    uint16_t EEP_read16(uint8_t Reg_h, uint8_t Reg_l);
    uint32_t EEP_read32(uint8_t Reg_h, uint8_t Reg_l);
    void EEP_write16(uint8_t Reg_h, uint8_t Reg_l, uint16_t data);
    void EEP_write32(uint8_t Reg_h, uint8_t Reg_l, uint32_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* MY_EEPROM_H */

