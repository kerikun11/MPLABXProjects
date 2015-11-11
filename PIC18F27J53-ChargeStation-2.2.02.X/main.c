// ChargeStation-2.2.02
// PIC18F27J53
// 2.1.00 試作1号用pinアサイン 切削基板
// 2.1.01 2015.03.12 初版、ChargeStation5からの引き継ぎ
// 2.1.02 2015.03.22 RTCC導入、LCDはI2C小型0802液晶
// 2.1.03 2015.04.30 CTMUタッチセンサ装備、charge_time_count充電時間カウント機能、（試作1号用pinアサイン）
// 2.2.00 ケース組み込み1号用pinアサイン 切削基板
// 2.2.01 2015.06.02 ケース組み込み1号用pinアサイン 切削基板
// 2.2.02 2015.06.04 USB_CDC 導入

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

#define CUT_CURRENT 100  // [mA]
#define CUT_TIME 6       // [s]

#define NUM_PORT 3

#define CTMU0 0 // RA0
#define CTMU1 1 // RA1
#define CTMU2 2 // RA2
#define CTMUM 3 // RA3

#define POWER_SW PORTBbits.RB0

#define ADC0 8  // AN8
#define ADC1 9  // AN9
#define ADC2 10 // AN10

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATC2

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD
#define MY_STDLIB   // my_utoa,my_atoi,my_strcmp

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>
#include <my_usb_cdc.h>
#include "tasks.h"

void interrupt ISR(void) {
    //UART_ISR();
    USB_ISR();
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        static uint16_t cnt_t0;
        if (cnt_t0) {
            cnt_t0--;
        } else {
            cnt_t0 = 120;
            lchika();
        }
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        cut_time_flag = 1;
        display_flag = 1;
        //        colon = !colon;
        //        RTCC_from_RTCC(&caltime_now, &epoch_now);
        static uint8_t cnt_t1 = 0;
        if (cnt_t1) {
            cnt_t1 = 0;
        } else {
            cnt_t1 = 1;
            integrating();
            charge_time_count();
        }
    }
    if (PIR2bits.TMR3IF) {
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
    TRISC = 0b10111010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11110000; // all digital
    ANCON1 = 0b00011000; // AN8,AN9,AN10 is analog
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
    uint8_t txbuf[250];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    uint8_t rxbuf[250];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}

int main(void) {
    main_init();

    ctmu_value0 = 9 * CTMU_read(CTMU0) / 10;
    ctmu_value1 = 9 * CTMU_read(CTMU1) / 10;
    ctmu_value2 = 9 * CTMU_read(CTMU2) / 10;
    ctmu_valuem = 9 * CTMU_read(CTMUM) / 10;

    RTCC_from_RTCC(&caltime_now, &epoch_now);
    if (caltime_now.DD == 0) {
        epoch_now = 0;
        RTCC_from_epoch(&caltime_now, &epoch_now);
    }
    print_content = TIME;

    for (uint8_t i = 0; i < NUM_PORT; i++) {
        OUT(i, 1);
        LED_OUT(i, 1);
        cut_cnt[i] = 0;
        auto_cut_ON[i] = 1;
    }

    INTCONbits.GIE = 1;

    while (1) {
        //CLRWDT();
        INTCONbits.GIE = 0;
        if (!sleep_flag) {
            INTCONbits.GIE = 1;
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
        }
        //sleep_loop();
        INTCONbits.GIE = 1;
    }
    return 0;
}
