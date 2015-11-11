#include "My_UART.h"

//*************************** UART ***************************//
// UART_ISR();
// を割り込み関数内に書いておくこと。
// RCIF,TXIF フラグの回収はレジスタ読み込みまたは上書きにより行われる。
ringbuf_t uart_tx;
ringbuf_t uart_rx;

void UART_init(void) {
    TXSTA1bits.TX9 = 0; // 0:8-bit
    TXSTA1bits.TXEN = 1; //1:enable
    TXSTA1bits.SYNC = 0; // 0:Asynchronous mode
    TXSTA1bits.BRGH = 0; // 1:High Speed
    RCSTA1bits.SPEN = 1; // 1:Serial Port enable
    RCSTA1bits.RX9 = 0; // 0:8-bit
    RCSTA1bits.CREN = 1; // 1:continuous receive enable
    BAUDCON1bits.BRG16 = 1; // 1:use 16-bit SPBRG
    SPBRG1 = _XTAL_FREQ / 16 / 115200 - 1;
    SPBRGH1 = (_XTAL_FREQ / 16 / 115200 - 1) >> 8;
    IPR1bits.RC1IP = 0; //0:low priority
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
}

void UART_ISR(void) {
    if (PIE1bits.TXIE && PIR1bits.TXIF) {
        if (ringbuf_num(&uart_tx)) {
            TXREG1 = ringbuf_pop(&uart_tx);
        } else {
            PIE1bits.TXIE = 0;
        }
    }
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        char ascii = RCREG1;
        ringbuf_put(&uart_rx, ascii);
    }
}

void UART_task(void) {
    if (ringbuf_num(&uart_tx)) {
        PIE1bits.TXIE = 1;
    }
}
