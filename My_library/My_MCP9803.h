/* 
 * File:   My_MCP9803.h
 * Author: kerikun11
 *
 * Created on 2015/11/16, 20:37
 */

#ifndef MY_MCP9803_H
#define	MY_MCP9803_H

#ifdef	__cplusplus
extern "C" {
#endif

//*************************** I2C_ThermoMeter MCP9803 ***************************//
#define MCP9803_ADRES 0x48

void TM_init(uint8_t config);
uint16_t TM_Read();

#ifdef	__cplusplus
}
#endif

#endif	/* MY_MCP9803_H */

