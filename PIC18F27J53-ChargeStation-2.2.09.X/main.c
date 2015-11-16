// ChargeStation-2.2.09
// PIC18F27J53
// 2.1.00 試作1号用pinアサイン 切削基板
// 2.1.01 2015.03.12 初版、ChargeStation5からの引き継ぎ
// 2.1.02 2015.03.22 RTCC導入、LCDはI2C小型0802液晶
// 2.1.03 2015.04.30 CTMUタッチセンサ装備、charge_time_count充電時間カウント機能、（試作1号用pinアサイン）
// 2.2.00 ケース組み込み1号用pinアサイン 切削基板
// 2.2.01 2015.06.02 ケース組み込み1号用pinアサイン 切削基板
// 2.2.02 2015.06.04 USB_CDC 導入
// 2.2.03 2015.06.09 port構造体にまとめた
// 2.2.04 2015.06.15 SLEEP機能、bootloader導入
// 2.2.05 2015.07.19 tx_bufferを構造体指定形式に統一→USBでもUARTでもOK
// 2.2.06 2015.08.11 settings導入
// 2.2.07 2015.09.06 settingsとりあえず完成版
// 2.2.08 2015.09.16 settings改良
// 2.2.09 2015.09.17 ファイル分割 My_library

// default,-0-FFF,-1006-1007,-1016-1017
// CONFIG1L
#pragma config WDTEN = ON, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
// CONFIG1H
#pragma config CPUDIV = OSC1, CP0 = OFF
// CONFIG2L
#pragma config OSC = INTOSCPLL, SOSCSEL = LOW, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
// CONFIG2H
#pragma config WDTPS = 8
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
#include <My_PIC.h>
#include <My_ST7032.h>
#include <My_RTCC.h>
#include <My_usb_cdc.h>
#include <My_terminal.h>
#include "ChargeStation_task.h"
#include "ctmu.h"
#include "io.h"
#include "LCD_print.h"
#include "settings.h"

void interrupt ISR(void) {
    USB_ISR();
    if (INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;
        millis_timer();
    }
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0; // 0xC0 : every 0.5 [s]
        cut_time_flag = 1;
        static uint8_t cnt_t1 = 0;
        if (cnt_t1) {
            cnt_t1 = 0;
        } else {
            cnt_t1 = 1;
            terminal_data_out_flag = 1;
            integrate_flag = 1;
            if (print_item == PRINT_DATA)display_flag = 1;
        }
    }
    if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
        PIR2bits.TMR3IF = 0;
        ctmu_sampling_flag = 1;
        static uint8_t cnt;
        if (cnt) {
            cnt--;
        } else {
            cnt = 8;
            LED_indicator();
        }
    }
}

void hardware_init(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b00011111; // OUT2,OUT1,OUT0,Vcap,SW,ctl,ctc,ctr
    TRISB = 0b00111111; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11110000; // all digital
    ANCON1 = 0b00001000; // AN8,AN9,AN10,AN12 is analog
    INTCON2bits.RBPU = 0; // Pull-up enable

    timer0_init(0); // Millis
    timer1_init(0, T1OSC); // Integrate
    timer3_init(2); // button,LED_indicator
    I2C_LCD_init();
    RTCC_init();
    ADC_init(VDD);
    CTMU_init();

    USB_init();
    static uint8_t usbtx[1800];
    ringbuf_init(&usb_tx, usbtx, sizeof (usbtx));
    static uint8_t usbrx[100];
    ringbuf_init(&usb_rx, usbrx, sizeof (usbrx));
}

void software_init(void) {
    // initialize CTMU value
    ctmu_ratio = 90;
    ctmu_set_ratio(ctmu_ratio);

    // Initialize display item
    display(LOGO, "Charge Station", "Made by KERI");

    // Initialize each port
    for (uint8_t i = 0; i < NUM_PORT; i++) {
        OUT(i, 0);
        LED_output(i, 0);
        port[i].cut_cnt = 0;
        port[i].flag.auto_cut_ON = 1;
        port[i].flag.led_indicator_ON = 1;
    }

    // Initialize settings
    settings_flag = 0;
}

int main(void) {
    // I/O pin Settings and Enable Modules
    hardware_init();
    // give initial values
    software_init();

    INTCONbits.GIE = 1;

    while (1) {
        //CLRWDT();
        INTCONbits.GIE = 0;
        RTCC_task();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        USB_task();
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        terminal_task(&usb_tx, &usb_rx);
        INTCONbits.GIE = 1;
        INTCONbits.GIE = 0;
        normal_task();
        INTCONbits.GIE = 1;
        // ** temporary *************************
        INTCONbits.GIE = 0;
        ctmu_task();
        if (ctmu_m.flag.pressing &&
                port[0].ctmu.flag.pressing &&
                port[1].ctmu.flag.pressing &&
                port[2].ctmu.flag.pressing) {
            bootload();
        }
        INTCONbits.GIE = 1;
        // **************************************
        INTCONbits.GIE = 0;
        sleep_task();
        INTCONbits.GIE = 1;
    }
    return 0;
}
