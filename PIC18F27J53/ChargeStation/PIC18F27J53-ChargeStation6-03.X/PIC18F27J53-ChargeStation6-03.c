// PIC18F27J53
// 2015.04.30
// RTCC
// LCDはI2C小型8x2液晶
// CTMUタッチセンサ装備
// sleep_loop 改善
// charge_time_count充電時間カウント機能
// 試作1号用pinアサイン

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

#define CTMU0 2 // RA0
#define CTMU1 1 // RA1
#define CTMU2 0 // RA2
#define CTMUM 3  // RA3
#define POWER_SW PORTBbits.RB0

//#define ADC0 8
//#define ADC1 9
//#define ADC2 10
//
//#define OUT0 LATA5
//#define OUT1 LATA6
//#define OUT2 LATA7
//
//#define LED0 LATC2
//#define LED1 LATB7
//#define LED2 LATB6
#define ADC0 10
#define ADC1 9
#define ADC2 8

#define OUT0 LATA7
#define OUT1 LATA6
#define OUT2 LATA5

#define LED0 LATC2
#define LED1 LATB6
#define LED2 LATB7

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD
#define CTMU        // Use CTMU

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>
#include <My_stdlib.h>
#include "PIC18F27J53-ChargeStation6-03.h"

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IE && INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        static uint16_t cnt_t0;
        if (cnt_t0) {
            cnt_t0--;
        } else {
            cnt_t0 = 120;
            lchika();
        }
    }
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xC0;
        cut_time_flag = 1;
        display_flag = 1;
        static uint8_t cnt_t1 = 2;
        if (cnt_t1) {
            cnt_t1 = 0;
        } else {
            cnt_t1 = 1;
            integrating();
            charge_time_count();
            display_flag = 1;
        }
    }
    if (PIE2bits.TMR3IE && PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        ctmu_flag = 1;
        delay_timer_interrupt(&delay_display);
    }
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    ctmu_value0 = 4 * CTMU_read(CTMU0) / 5;
    ctmu_value1 = 4 * CTMU_read(CTMU1) / 5;
    ctmu_value2 = 4 * CTMU_read(CTMU2) / 5;
    ctmu_valuem = 4 * CTMU_read(CTMUM) / 5;

    RTCC_from_RTCC(&caltime_now, &epoch_now);
    if (caltime_now.DD == 0) {
        epoch_now = 0;
        RTCC_from_epoch(&caltime_now, &epoch_now);
    }
    print_content = TIME;

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("Charge");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("Station");
    Delay_ms(2000);

    uint8_t i;

    for (i = 0; i < NUM_PORT; i++) {
        OUT(i, 1);
        LED(i, 1);
        cut_cnt[i] = 0;
        auto_cut_ON[i] = 1;
    }

    while (1) {
        if (!sleep_flag) {
            normal_mode_loop();
            RTCC_loop();
        }
        sleep_loop();
    }
    return 0;
}
