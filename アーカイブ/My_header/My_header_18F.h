/* 
 * File:   My_hedaer_18F.h
 * Author: kerikun11
 *
 * Created on 2015/02/23, 12:45
 */

#ifndef MY_HEDAER_18F_H
#define	MY_HEDAER_18F_H

//*************************** timer0 ***************************//

void timer0_init(uint8_t prescaler) { // prescaler is 0~8
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 1; // 8-bit timer
    T0CONbits.T0CS = 0; // use intOSC
    if (prescaler == 0) {
        T0CONbits.PSA = 1; // Not use prescaler
    } else {
        T0CONbits.PSA = 0; // use prescaler
        T0CONbits.T0PS = prescaler - 1; // 1 => 1:4
    }
    INTCONbits.T0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 0; // low priority
    INTCONbits.PEIE = 1;
}

//*************************** timer1 ***************************//
#define FOSC_4 0 // Fosc/4
#define FOSC 1   // Fosc
#define T1OSC 2  // Timer 1 OSC

void timer1_init(uint8_t prescaler, uint8_t clock_select) { // prescaler is 0~3
    T1CONbits.TMR1CS = clock_select;
    if (clock_select == T1OSC) T1CONbits.T1OSCEN = 1; // Drive Crystal
    else T1CONbits.T1OSCEN = 0;
    T1CONbits.T1CKPS = prescaler;
    T1CONbits.nT1SYNC = 1; // No Sync
    T1CONbits.RD16 = 0; //Timer1=16bit timer
    T1CONbits.TMR1ON = 1; //enable
    IPR1bits.TMR1IP = 0; // low priority
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
}
//*************************** timer3 ***************************//

void timer3_init(uint8_t prescaler) { // prescaler is 0~3
    T3CONbits.TMR3CS = 0; //Clock = Fosc/4
    T3CONbits.T3OSCEN = 1; // Drive Crystal
    T3CONbits.T3CKPS = prescaler;
    T3CONbits.RD163 = 0; //Timer1=16bit timer
    T3CONbits.TMR3ON = 1; //enable
    IPR2bits.TMR3IP = 0; // low priority
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;
    INTCONbits.PEIE = 1;
}

//*************************** timer5 ***************************//
#ifdef PIC18F27J53

void timer5_init(uint8_t prescaler) { // prescaler is 0~3
    T5CONbits.TMR5CS = 0; //Clock = Fosc/4
    T5CONbits.T5OSCEN = 1; // Drive Crystal
    T5CONbits.T5CKPS = prescaler;
    T5CONbits.RD165 = 0; //Timer1=16bit timer
    T5CONbits.TMR5ON = 1; //enable
    IPR5bits.TMR5IP = 0; // low priority
    PIR5bits.TMR5IF = 0;
    PIE5bits.TMR5IE = 1;
    INTCONbits.PEIE = 1;
}
#endif /* PIC18F27J53 */

//*************************** OSC ***************************//
#ifdef PIC18F26K22
// freq = 0 ~ 6 : 1MHz ~ 64MHz

void OSC_init(uint8_t freq) {
    if (freq > 4) {
        OSCCONbits.IRCF = freq + 1; // 6 => 8MHz
        OSCCON2bits.PLLRDY = 1;
        OSCTUNEbits.PLLEN = 1; // clock x 4
    } else {
        OSCCONbits.IRCF = freq + 3; // 6 => 8MHz
        OSCCON2bits.PLLRDY = 0;
        OSCTUNEbits.PLLEN = 0; // clock x 4
    }
}
#endif /* PIC18F26K22 */

#ifdef PIC18F27J53
//Fosc = 48MHz
//CONFIG : #pragma config OSC = INTOSCPLL

void OSC_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
}
#endif /* PIC18F27J53 */
//*************************** ADC ***************************//
#define VDD 0
#define VREFP 1
#define VSS 0
#define VREFN 1
#define FVR 3

#ifdef PIC18F27J53

void ADC_init(uint8_t p_ref) {
    ADCON0bits.VCFG1 = 0; // Vref- = Vss
    ADCON0bits.VCFG0 = p_ref; // Vref+

    ADCON1bits.ADFM = 1; //H + L = 4 + 8
    ADCON1bits.ADCAL = 0; // normal ADC
    ADCON1bits.ADCS = 2; // clock is Fosc/32
}
#endif /* PIC18F27J53 */

#if defined(PIC16F1827) || defined(PIC12F1822)

void ADC_init(uint8_t p_ref) {
    ADCON1bits.ADFM = 0; // 0 : H + L = 8 + 2
    ADCON1bits.ADCS = 6; // clock is Fosc/4
    ADCON1bits.ADNREF = 0; //Vref- = Vss
    ADCON1bits.ADPREF = p_ref; //Vref+ = p_ref
    if (p_ref == FVR) FVRCON = 0x83; //4.096V
}
#endif /* PIC16F1827 || PIC12F1822 */

uint16_t ADC(uint8_t ch) {
    ADCON0bits.CHS = ch;
    ADCON0bits.ADON = 1;
    //__delay_us(5);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ADRES;
}

//*************************** UART ***************************//
// interrupt_TXIF();
// if(RC1IF){
//      char ascii = RCREG1;
// }
// を割り込み関数内に書いておくこと。
// RCIF,TXIF フラグの回収はレジスタ読み込みまたは上書きにより行われる。
#include <My_ringbuf.h>

ringbuf_t tx_buf;

void UART_init(uint8_t interrupt_ON) {
    TXSTA1bits.TX9 = 0; // 8-bit
    TXSTA1bits.TXEN = 1; //enable
    TXSTA1bits.SYNC = 0; // Asynchronous mode
    TXSTA1bits.BRGH = 0;
    RCSTA1bits.SPEN = 1; // Serial Port enable
    RCSTA1bits.RX9 = 0; // 8-bit
    RCSTA1bits.CREN = 1; // continuous receive enable
    BAUDCON1bits.BRG16 = 0; // use 8bit SPBRG
    SPBRG1 = _XTAL_FREQ / 64 / 9600 - 1;
    SPBRGH1 = 0;
    if (interrupt_ON) {
        IPR1bits.RC1IP = 0; //low priority
        PIE1bits.RC1IE = 1;
        INTCONbits.PEIE = 1;
    }
}

void interrupt_TXIF(void) {
    if (PIE1bits.TX1IE && PIR1bits.TX1IF) {
        PIR1bits.TX1IF = 0;
        if (ringbuf_num(&tx_buf) > 0) {
            TXREG1 = ringbuf_pop(&tx_buf);
        } else {
            PIE1bits.TX1IE = 0;
        }
    }
}

void tx_send(uint8_t asciicode) {
    ringbuf_push(&tx_buf, asciicode);
    PIE1bits.TX1IE = 1;
}

void tx_sends(const uint8_t *asciicode) {
    while (*asciicode) {
        ringbuf_push(&tx_buf, *asciicode++);
    }
    PIE1bits.TX1IE = 1;
}

void tx_sendn(uint16_t value, uint8_t digits) {
    while (digits--) {
        uint16_t temp = value;
        for (uint8_t i = 0; i < digits; i++) {
            temp /= 10;
        }
        temp %= 10;
        tx_send('0' + temp);
    }
}

//*************************** CTMU ***************************//
#define AVERAGE_NUMBER 10
#define CTMU_DISCHARGE_TIME 20  // [us]
#define CTMU_CHARGE_TIME 5      // [us]

#ifdef PIC18F27J53

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

//*************************** Delay_ms ***************************//
// delay_timer_interrupt(&d);

void Delay_ms(uint16_t ms) {
    while (ms--)__delay_ms(1);
}

typedef struct Delay {
    uint8_t flag;
    uint16_t cnt;
} delay_t;

delay_t d1;

void delay_timer_interrupt(delay_t *d) {
    if (d->cnt)d->cnt--;
    if (d->cnt == 1)d->flag = 1;
}

void delay_set(delay_t *d, uint16_t value) {
    d->cnt = value;
    d->flag = 0;
}

//*************************** stdlib.h ***************************//

void utoa(uint8_t *str, uint16_t value, uint8_t digits) {
    uint16_t v;
    uint8_t d;
    while (digits--) {
        v = value;
        d = digits;
        while (d--) {
            v /= 10;
        }
        v %= 10;
        *str++ = '0' + v;
    }
    *str = '\0';
}

uint8_t atoi(const uint8_t *str) {
    uint8_t ret = 0;
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            ret *= 10;
            ret += *str - '0';
        }
        str++;
    }
    return ret;
}

int8_t strcmp(const uint8_t *str1, const uint8_t *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)return (*str1 - *str2);
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

#endif	/* MY_HEDAER_18F_H */

