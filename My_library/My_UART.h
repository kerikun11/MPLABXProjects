/* 
 * File:   My_UART.h
 * Author: kerikun11
 *
 * Created on 2015/11/11, 9:59
 */

#ifndef MY_UART_H
#define	MY_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include "My_ringbuf.h"

#if defined(__18F27J53)    
#define _XTAL_FREQ 48000000

#define _TXIE   PIE1bits.TXIE
#define _TXIF   PIR1bits.TXIF
#define _TXIP   IPR1bits.TX1IP
#define _TXREG  TXREG1
#define _RCIE   PIE1bits.RCIE
#define _RCIF   PIR1bits.RCIF
#define _RCIP   IPR1bits.RC1IP
#define _RCREG  RCREG1
#define _TX9    TXSTA1bits.TX9
#define _TXEN   TXSTA1bits.TXEN
#define _SYNC   TXSTA1bits.SYNC
#define _BRGH   TXSTA1bits.BRGH
#define _SPEN   RCSTA1bits.SPEN
#define _RX9    RCSTA1bits.RX9
#define _CREN   RCSTA1bits.CREN
#define _BRG16  BAUDCON1bits.BRG16
#define _SPBRGL SPBRG1
#define _SPBRGH SPBRGH1
#define _PEIE   INTCONbits.PEIE

#elif defined(__16F1827)||defined(__12F1822)
#define _XTAL_FREQ 32000000

#define _TXIE   PIE1bits.TXIE
#define _TXIF   PIR1bits.TXIF
#define _TXREG  TXREG
#define _RCIE   PIE1bits.RCIE
#define _RCIF   PIR1bits.RCIF
#define _RCREG  RCREG
#define _TX9    TXSTAbits.TX9
#define _TXEN   TXSTAbits.TXEN
#define _SYNC   TXSTAbits.SYNC
#define _BRGH   TXSTAbits.BRGH
#define _SPEN   RCSTAbits.SPEN
#define _RX9    RCSTAbits.RX9
#define _CREN   RCSTAbits.CREN
#define _BRG16  BAUDCONbits.BRG16
#define _SPBRGL SPBRG
#define _SPBRGH SPBRGH
#define _PEIE   INTCONbits.PEIE
#endif

    //*************************** UART ***************************//
    // UART_ISR();
    // を割り込み関数内に書いておくこと。
    // RCIF,TXIF フラグの回収はレジスタ読み込みまたは上書きにより行われる。
    extern ringbuf_t uart_tx;
    extern ringbuf_t uart_rx;

    void UART_init(void);
    void UART_ISR(void);
    void UART_task(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MY_UART_H */

