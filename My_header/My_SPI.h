/* 
 * File:   My_SPI.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:50
 */

#ifndef MY_SPI_H
#define	MY_SPI_H

//*************************** PIC's SPI Module ***************************//
#define MASTER 0
#define SLAVE 1

void SPI_init(uint8_t mode) {
    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.CKP = 1;
    SSP1STATbits.CKE = 0;
    if (mode == MASTER) {
        SSP1CON1bits.SSPM = 2;
    } else if (mode == SLAVE) {
        SSP1CON1bits.SSPM = 4;
        SSP1STATbits.SMP = 0;
    }
    if (mode == SLAVE) {
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

//*************************** SPI_TM ADT7310 ***************************//
#ifdef ADT7310

void SPI_TM_init(void) {
    uint8_t dumy;

    C_SEL = 0;
    dumy = SPI_Transfer(0x08);
    dumy = SPI_Transfer(0x80);
    dumy = SPI_Transfer(0x54);
    C_SEL = 1;
}

int16_t SPI_TM_Read(void) {
    uint8_t th;
    uint8_t tl;
    C_SEL = 0;
    th = SPI_Transfer(0x00);
    tl = SPI_Transfer(0x00);
    C_SEL = 1;
    return (0xFF00 & (th << 8)) + (0xFF & tl);
}
#endif /* ADT7310 */

//*************************** SPI_LCD ***************************//
#ifdef AQM1248A
// C_SEL, RS を#defineすること。
// #define C_SEL LATAbits.LA0
// #define RS LATAbits.LA1

void SPI_LCD_Command(uint8_t comm) {
    C_SEL = 0;
    RS = 0;
    uint8_t dumy = SPI_Transfer(comm);
    C_SEL = 1;
}

void SPI_LCD_Data(uint8_t data) {
    C_SEL = 0;
    RS = 1;
    uint8_t dumy = SPI_Transfer(data);
    C_SEL = 1;
}

void SPI_LCD_init(void) {
    Delay_ms(100);
    SPI_LCD_Command(0xAE); // display OFF
    SPI_LCD_Command(0xA0); // ADC = normal
    SPI_LCD_Command(0xC8); // Common Output = revers
    SPI_LCD_Command(0xA3); // bias = 1/7

    SPI_LCD_Command(0x2C); // Power Control 1
    __delay_ms(2);
    SPI_LCD_Command(0x2E); // Power Control 2
    __delay_ms(2);
    SPI_LCD_Command(0x2F); // Power Control 3

    SPI_LCD_Command(0x23); // Vo voltage register ratio set
    SPI_LCD_Command(0x81); // Electronic volume mode set
    SPI_LCD_Command(0x16); // Electronic volume value set

    SPI_LCD_Command(0xA4); // display all point = normal
    SPI_LCD_Command(0x40); // display start line = 0
    SPI_LCD_Command(0xA6); // Display normal/revers = normal
    SPI_LCD_Command(0xAF); // display ON
}

void SPI_LCD_Cursor(uint8_t page, uint8_t column) {
    SPI_LCD_Command(0xB0 | (0x0F & page));
    SPI_LCD_Command(0x10 | (0x0F & (column >> 4)));
    SPI_LCD_Command(0x00 | (0x0F & column));
}
#endif /* AQM1248A */

#endif	/* MY_SPI_H */
