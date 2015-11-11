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
#elif defined(__16F1827)||defined(__12F1822)
#define _XTAL_FREQ 32000000
#endif

    //*************************** UART ***************************//
    // UART_ISR();
    // を割り込み関数内に書いておくこと。
    // RCIF,TXIF フラグの回収はレジスタ読み込みまたは上書きにより行われる。
    extern ringbuf_t uart_tx;
    extern ringbuf_t uart_rx;

    void UART_init(void);
    void UART_ISR(void);
    void UART_task();

#ifdef	__cplusplus
}
#endif

#endif	/* MY_UART_H */

