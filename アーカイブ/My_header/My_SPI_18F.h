/* 
 * File:   My_SPI_18F.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:35
 */

#ifndef MY_SPI_18F_H
#define	MY_SPI_18F_H

//*************************** SPI ***************************//
// C_SEL,RSÇ#defineÇµÇƒÇ®Ç≠Ç±Ç∆ÅB

#define Master 0
#define Slave 1

void SPI_init(uint8_t mode) {
    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.CKP = 1;
    SSP1STATbits.CKE = 0;
    if (mode == Master) {
        SSP1CON1bits.SSPM = 2;
    } else if (mode == Slave) {
        SSP1CON1bits.SSPM = 4;
        SSP1STATbits.SMP = 0;
    }
    if (mode==Slave) {
        SSP1IF = 0;
        PIE1bits.SSP1IE = 1;
        INTCONbits.PEIE = 1;
    }
}

uint8_t SPI_Transfer(uint8_t txdata) {
    uint8_t rxdata;

    rxdata = SSP1BUF;
    SSP1IF = 0;
    SSP1BUF = txdata;
    while (!SSP1IF);
    rxdata = SSP1BUF;
    return rxdata;
}

#endif	/* MY_SPI_18F_H */

