/* 
 * File:   My_SPI.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:50
 */

#ifndef MY_SPI_H
#define	MY_SPI_H

#include <xc.h>
#include <stdint.h>

//*************************** PIC's SPI Module ***************************//
#define SPI_MASTER 0
#define SPI_SLAVE 1
void SPI_init(uint8_t mode);
uint8_t SPI_Transfer(uint8_t txdata);

//*************************** SPI_TM ADT7310 ***************************//
#ifdef ADT7310

void SPI_TM_init(void);
int16_t SPI_TM_Read(void);
#endif /* ADT7310 */

//*************************** SPI_LCD ***************************//
#ifdef AQM1248A
// C_SEL, RS を#defineすること。
// #define C_SEL LATAbits.LA0
// #define RS LATAbits.LA1
void SPI_LCD_init(void);
void SPI_LCD_Command(uint8_t comm);
void SPI_LCD_Data(uint8_t data);
void SPI_LCD_Cursor(uint8_t page, uint8_t column);
#endif /* AQM1248A */

#endif	/* MY_SPI_H */
