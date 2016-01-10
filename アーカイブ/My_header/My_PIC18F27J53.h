/* 
 * File:   My_PIC18F27J53.h
 * Author: kerikun11
 *
 * Created on 2015/03/22, 19:50
 */

#ifndef MY_PIC18F27J53_H
#define	MY_PIC18F27J53_H

#ifdef PIC18F27J53x
//*************************** ADC ***************************//
#define VDD 0
#define VREFP 1
#define VSS 0
#define VREFN 1

void ADC_init(uint8_t p_ref) {
    ADCON0bits.VCFG1 = 0; // Vref- = Vss
    ADCON0bits.VCFG0 = p_ref; // Vref+

    ADCON1bits.ADFM = 1; //H + L = 4 + 8
    ADCON1bits.ADCAL = 0; // normal ADC
    ADCON1bits.ADCS = 2; // clock is Fosc/32
}

uint16_t ADC(uint8_t ch) {
    ADCON0bits.CHS = ch;
    ADCON0bits.ADON = 1;
    //__delay_us(5);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

//*************************** OSC ***************************//
//Fosc = 48MHz
//CONFIG : #pragma config OSC = INTOSCPLL

void OSC_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
}
//*************************** CTMU ***************************//
#define AVERAGE_NUMBER 10
#define CTMU_DISCHARGE_TIME 20  // [us]
#define CTMU_CHARGE_TIME 5      // [us]

void CTMU_init(void) {
    CTMUCONH = 0x00;
    CTMUCONL = 0x90;
    CTMUICON = 0x01;
    ADCON0 = 0xFB;
    ADCON1 = 0x1F;

    ADCON1bits.ADFM = 1;
    ADCON1bits.ADCAL = 0;
    ADCON1bits.ACQT = 1;
    ADCON1bits.ADCS = 2;

    ADCON0bits.VCFG0 = 0;
    ADCON0bits.VCFG1 = 0;
    ADCON0bits.ADON = 1;
}

uint16_t CTMU_read(uint8_t ch) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < AVERAGE_NUMBER; i++) {
        ADCON0bits.CHS = ch;
        CTMUCONHbits.CTMUEN = 1;
        CTMUCONLbits.EDG1STAT = 0;
        CTMUCONLbits.EDG2STAT = 0;

        // ゼロ電位から開始させる為に電荷を放電させる
        CTMUCONHbits.IDISSEN = 1;
        __delay_us(CTMU_DISCHARGE_TIME);
        CTMUCONHbits.IDISSEN = 0;
        // 電極に充電を行う
        CTMUCONLbits.EDG1STAT = 1;
        __delay_us(CTMU_CHARGE_TIME);
        CTMUCONLbits.EDG1STAT = 0;
        // 電極の電圧(AN0)を読み取る
        PIR1bits.ADIF = 0;
        ADCON0bits.GO = 1;
        while (!PIR1bits.ADIF);
        sum += ADRES;
    }
    return sum / AVERAGE_NUMBER;
}
#endif  /* PIC18F27J53 */

#endif	/* MY_PIC18F27J53_H */

