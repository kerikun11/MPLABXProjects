/* 
 * File:   My_UART_18F.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:22
 */

#ifndef MY_UART_18F_H
#define	MY_UART_18F_H

//*************************** UART ***************************//
// interrupt_TXIF();を割り込み関数内に書いておくこと。
// if(RC1IF){
//      dumy=RCREG1;
// }
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

#endif	/* MY_UART_18F_H */

