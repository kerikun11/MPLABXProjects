#include "My_UART.h"

//*************************** UART ***************************//
// UART_ISR();
// を割り込み関数内に書いておくこと。
// RCIF,TXIF フラグの回収はレジスタ読み込みまたは上書きにより行われる。
ringbuf_t uart_tx;
ringbuf_t uart_rx;

void UART_init(void) {
    _TX9 = 0; // 0:8-bit
    _TXEN = 1; //1:enable
    _SYNC = 0; // 0:Asynchronous mode
    _BRGH = 0; // 1:High Speed
    _SPEN = 1; // 1:Serial Port enable
    _RX9 = 0; // 0:8-bit
    _CREN = 1; // 1:continuous receive enable
    _BRG16 = 1; // 1:use 16-bit SPBRG
    _SPBRGL = _XTAL_FREQ / 16 / 115200 - 1;
    _SPBRGH = (_XTAL_FREQ / 16 / 115200 - 1) >> 8;
#if defined(__18F27J53)
    _RCIP = 0; //0:low priority
    _TXIP = 0; //0:low priority
#endif
    _RCIE = 1;
    _PEIE = 1;
    UART_buffer_init();
}

static void UART_buffer_init(void) {
    static uint8_t uarttx[UART_TX_BUFFER_SIZE];
    ringbuf_init(&uart_tx, uarttx, sizeof (uarttx));
    static uint8_t uartrx[UART_RX_BUFFER_SIZE];
    ringbuf_init(&uart_rx, uartrx, sizeof (uartrx));
}

void UART_ISR(void) {
    if (_TXIE && _TXIF) {
        if (ringbuf_num(&uart_tx)) {
            _TXREG = ringbuf_pop(&uart_tx);
        } else {
            _TXIE = 0;
        }
    }
    if (_RCIE && _RCIF) {
        char ascii = _RCREG;
        ringbuf_put(&uart_rx, ascii);
    }
}

void UART_task(void) {
    if (ringbuf_num(&uart_tx)) {
        _TXIE = 1;
    }
}
