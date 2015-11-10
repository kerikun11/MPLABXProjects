// test

// default,-0-FFF,-1006-1007,-1016-1017
// CONFIG1L
#pragma config WDTEN = OFF, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
// CONFIG1H
#pragma config CPUDIV = OSC1, CP0 = OFF
// CONFIG2L
#pragma config OSC = INTOSCPLL, SOSCSEL = LOW, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
// CONFIG2H
#pragma config WDTPS = 1024
// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF, RTCOSC = T1OSCREF, DSBOREN = OFF, DSWDTEN = OFF, DSWDTPS = G2
// CONFIG3H
#pragma config IOL1WAY = OFF, ADCSEL = BIT12, MSSP7B_EN = MSK7
// CONFIG4L
#pragma config WPFP = PAGE_127, WPCFG = OFF
// CONFIG4H
#pragma config WPDIS = OFF, WPEND = PAGE_WPFP, LS48MHZ = SYS48X8

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <My_PIC.h>
#include <My_I2C.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include <My_usb_cdc.h>
#include <My_terminal.h>

void interrupt ISR(void) {
    USB_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0; // 0xC0 : every 0.5 [s]
        LATAbits.LATA0 = !LATAbits.LATA0;
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
        LATAbits.LATA1 = !LATAbits.LATA1;
    }
}

void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3) {
    if (!strcmp(op0, "help") || !strcmp(op0, "?")) {
        ringbuf_put_str(tx,
                "\t******** PIC18F27J53 ********\n"
                "\tprint_time(t)\n"
                "\tadjust_time(at) [hand:y,M,d,h,m,s] [value(decimal)]\n"
                "\tRESET();\n"
                "\tbootload\n"
                );
    }
    if (!strcmp(op0, "bootload")) {
        I2C_LCD_Clear();
        I2C_LCD_SetCursor(0, 0);
        I2C_LCD_Puts("PIC18F27J53");
        I2C_LCD_SetCursor(0, 1);
        I2C_LCD_Puts("Bootloader mode");
        asm("goto   0x001C");
    }
    terminal_time(tx, op0, op1, op2);
    if (!strcmp(op0, "RESET();")) {
        RESET();
    }
}

void hardware_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00010000; // OUT2,OUT1,OUT0,Vcap,SW,ctl,ctc,ctr
    TRISB = 0b00110000; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b1111111; // all digital
    ANCON1 = 0b1111111; // AN8,AN9,AN10,AN12 is analog
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(0); // Millis
    timer1_init(0, T1OSC); // Integrate
    timer3_init(2); // button,LED_indicator
    I2C_init();
    I2C_LCD_init();
    RTCC_init();

    USB_init();
    static uint8_t usbtx[2000];
    ringbuf_init(&usb_tx, usbtx, sizeof (usbtx));
    static uint8_t usbrx[100];
    ringbuf_init(&usb_rx, usbrx, sizeof (usbrx));
}

void software_init(void) {
    // Get time from RTCC()
    RTCC_from_RTCC(&now);
    if (now.DD == 0) {
        now.epoch = 0;
        RTCC_from_epoch(&now);
    }
    // Initialize display item
    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("USB UART");
}

int main(void) {
    // I/O pin Settings and Enable Modules
    hardware_init();
    // give initial values
    software_init();

    INTCONbits.GIE = 1;

    while (1) {
        INTCONbits.GIE = 0;
        RTCC_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        if (time_change_flag) {
            time_change_flag = 0;
            char str[20];
            I2C_LCD_Clear();
            I2C_LCD_SetCursor(0, 0);
            sprintf(str, "%02d/%02d/%02d", now.YY, now.MM, now.DD);
            I2C_LCD_Puts(str);
            I2C_LCD_SetCursor(0, 1);
            if (now.colon)sprintf(str, "%02d:%02d-%02d", now.hh, now.mm, now.ss);
            else sprintf(str, "%02d %02d-%02d", now.hh, now.mm, now.ss);
            I2C_LCD_Puts(str);
        }
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        USB_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        terminal_loop(&usb_tx, &usb_rx);
        INTCONbits.GIE = 1;
    }
    return 0;
}
