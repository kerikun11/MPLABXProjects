// PIC24FJ64GB002 Configuration Bit Settings
// 2015.04.12

#include <xc.h>
#include <stdint.h>

_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
_CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
//_CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
_CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)

#define _XTAL_FREQ 32000000

#include <My_ringbuf.h>
#include <uart.h>

ringbuf_t tx_buf;

void UART_init() {
    U1MODEbits.UARTEN = 1;
    U1MODEbits.UEN = 0;
    U1MODEbits.BRGH = 0;
    U1MODEbits.PDSEL = 0;

    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.URXISEL = 0;

    //U1BRG = 103;
    U1BRG = 51;

    IEC0bits.U1RXIE = 1;

    U1STAbits.UTXEN = 1;

    static char txbuf[250];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
}

void tx_send(char asciicode) {
    ringbuf_push(&tx_buf, asciicode);
    IEC0bits.U1TXIE = 1;
}

void tx_sends(const char *asciicode) {
    while (*asciicode) {
        ringbuf_push(&tx_buf, *asciicode++);
    }
    IEC0bits.U1TXIE = 1;
}

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;
    char ascii = U1RXREG;
    tx_send(ascii);
}

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void) {
    if (IFS0bits.U1TXIF && IEC0bits.U1TXIE) {
        IFS0bits.U1TXIF = 0;
        if (ringbuf_num(&tx_buf) > 0) {
            U1TXREG = ringbuf_pop(&tx_buf);
        } else {
            IEC0bits.U1TXIE = 0;
        }
    }
}

int main(void) {
    OSCCONbits.COSC = 1;
    OSCCONbits.NOSC = 1;
    CLKDIVbits.PLLEN = 1;

    OSCCONbits.IOLOCK = 0;
    if (OSCCONbits.IOLOCK != 0) {
        OSCCON = (OSCCON & 0xFF00) + 0x0046;
        OSCCON = (OSCCON & 0xFF00) + 0x0057;
        OSCCONbits.IOLOCK = 0;
    }
    RPINR18bits.U1RXR = 9;
    RPOR4bits.RP8R = 3;

    AD1PCFG = 0xFFFF;
    TRISA = 0x0000;
    TRISB = 0x0200;

    UART_init();

    uint16_t i;

    while (1) {
        LATAbits.LATA0 = 1;
        i = 0xFFFF;
        while (i--);
        LATAbits.LATA0 = 0;
        i = 0xFFFF;
        while (i--);
    }
    return 0;
}
