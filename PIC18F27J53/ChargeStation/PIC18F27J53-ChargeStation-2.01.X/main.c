// ChargeStation-2
// PIC18F27J53
// 2.00 2015.03.12 初版(LCDはI2C小型8x2液晶)
// 2.01 2015.03.05 RTCC

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
#define CUT_TIME 6      // [s]

#define NUM_PORT 3

#define SW0 PORTAbits.RA0
#define SW1 PORTAbits.RA1
#define SW2 PORTAbits.RA2
#define SW PORTAbits.RA3
#define POWER_SW PORTBbits.RB0

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATC2
#define LED1 LATB7
#define LED2 LATB6

#define PIC18F27J53 // Device
#define ST7032      // I2C_LCD

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>
#include <My_RTCC.h>
#include "tasks.h"

void interrupt ISR(void) {
    UART_ISR();
    if (PIE1bits.RC1IE && PIR1bits.RC1IF) {
        PIR1bits.RC1IF = 0;
        uint8_t ascii = RCREG1;
        tx_send(ascii);
    }
    if (INTCONbits.T0IE && INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        static uint16_t cnt_t0;
        if (cnt_t0) {
            cnt_t0--;
        } else {
            cnt_t0 = 120;
            lchika();
            display_flag = 1;
        }
        cut_flag = 1;
    }
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x80;
        integrating();
    }
    if (PIE2bits.TMR3IE && PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&sw, !SW);
        button_timer_interrupt(&sw0, !SW0);
        button_timer_interrupt(&sw1, !SW1);
        button_timer_interrupt(&sw2, !SW2);
        delay_timer_interrupt(&d_display);
    }
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    //epoch_now = 3155759990; // 2099/13/31/23:59-50
    //get_caltime_since_epoch();
    RTCC_from_RTCC(&caltime_now, &epoch_now);
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
            if (!edit_flag.flags) {
                nomal_mode_loop();
                if (sw.flag.press) {
                    sw.flag.press = 0;
                    if (print_content == CURRENT)print_content = INTEGRATING;
                    else if (print_content == INTEGRATING)print_content = TIME;
                    else print_content = CURRENT;
                }
            }
            if (cut_flag) {
                cut_flag = 0;
                Auto_cut();
            }
            RTCC_loop();
            if (time_change_flag) {
                time_change_flag = 0;
                display_flag = 1;
            }
            if (print_content == TIME)RTCC_adjust_time_button(&sw, &sw0, &sw1);
            if (display_flag) {
                display_flag = 0;
                display_LCD();
            }
        }
        sleep_loop();
    }
    return 0;
}
