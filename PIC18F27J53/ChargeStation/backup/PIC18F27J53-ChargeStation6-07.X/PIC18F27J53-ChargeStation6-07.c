// PIC18F27J53
// 2015.06.04
// RTCC
// LCDはI2C小型1602液晶
// CTMUタッチセンサ装備
// charge_time_count充電時間カウント機能
// ケース組み込み1号用pinアサイン 切削基板
// USB CDC
// port構造体にまとめた
// SLEEP ok
// I2C EEPROM NG
// bootloader

// default,-0-FFF,-1006-1007,-1016-1017
#include <xc.h>
#include <stdint.h>
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

#define _XTAL_FREQ 48000000

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD
#define EEPROM24LC64// EEPROM

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>
#include <My_stdlib.h>
#include <My_usb_cdc.h>
#include "PIC18F27J53-ChargeStation6-07.h"

void interrupt ISR(void) {
    //UART_ISR();
    USB_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
        static uint16_t cnt_t0;
        if (cnt_t0) {
            cnt_t0--;
        } else {
            cnt_t0 = 120;
            LED_indicator();
        }
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        cut_time_flag = 1;
        static uint8_t cnt_t1 = 0;
        if (cnt_t1) {
            cnt_t1 = 0;
        } else {
            cnt_t1 = 1;
            integrating();
            charge_time_count();
            display_flag = 1;
        }
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
        ctmu_flag = 1;
        delay_timer_interrupt(&delay_display);
    }
}

void main_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,ctl,ctc,ctr
    TRISB = 0b00111111; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11110000; // all digital
    ANCON1 = 0b00001000; // AN8,AN9,AN10,AN12 is analog
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(6); // LED-chika
    timer1_init(0, T1OSC); // Integrate
    timer3_init(2); // button
    I2C_init();
    I2C_LCD_init();
    RTCC_init();
    ADC_init(VDD);
    CTMU_init();
    USB_init();

    //UART_init();
    static uint8_t txbuf[2000];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[100];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();

    ctmu_ratio = 90;
    ctmu_set_ratio(ctmu_ratio);

    RTCC_from_RTCC(&caltime_now, &epoch_now);
    if (caltime_now.DD == 0) {
        epoch_now = 0;
        RTCC_from_epoch(&caltime_now, &epoch_now);
    }
    print_content = LOGO;
    next_print_content = TIME;
    delay_set(&delay_display, 120);

    for (uint8_t i = 0; i < NUM_PORT; i++) {
        OUT(i, 1);
        LED_OUT(i, 1);
        port[i].integrated_current_sec = EEP_read32(0, i);
        port[i].integrated_time = EEP_read32(1, i);
        port[i].cut_cnt = 0;
        port[i].flag.auto_cut_ON = 1;
        port[i].flag.led_indicater_ON = 1;
    }

    INTCONbits.GIE = 1;

    while (1) {
        INTCONbits.GIE = 0;
        USB_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        rx_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        normal_mode_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        RTCC_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        ctmu_loop();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        sleep_loop();
        INTCONbits.GIE = 1;
    }
    return 0;
}
