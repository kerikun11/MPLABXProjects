// PIC16F1827 Configuration Bit Settings
// 2015.2.7
// NJW1159D 電子ボリュームIC使用

#include <xc.h>
#include <stdint.h>
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 32000000
#include <My_header_16F.h>

#define CLK LATB3
#define LAT LATB4
#define DAT LATB5
#define SW_P PORTAbits.RA1
#define SW_M PORTAbits.RA2

uint8_t cnt_t1;
uint8_t cnt_clk = 72;
uint16_t serial_data1;
uint16_t serial_data2;

button_t sw_p;
button_t sw_m;

void interrupt ISR(void);
void send_timer_interrupt(void);
void data_set(uint8_t value);
void main_init(void);

void interrupt ISR(void) {
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
        button_timer_interrupt(&sw_p, !SW_P);
        button_timer_interrupt(&sw_m, !SW_M);
    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        send_timer_interrupt();
    }
}

void send_timer_interrupt(void) {
    if (cnt_clk < 32) {
        LAT = 0;
        if (cnt_clk % 2 == 0) {
            CLK = 1;
            DAT = (serial_data1 >> (15 - cnt_clk / 2));
        } else {
            CLK = 0;
        }
    } else if (cnt_clk == 33) {
        CLK = 1;
    } else if (cnt_clk == 34) {
        LAT = 1;
    } else if (cnt_clk == 35) {
        LAT = 0;
    } else if ((cnt_clk - 35) < 32) {
        LAT = 0;
        if ((cnt_clk - 35) % 2 == 0) {
            CLK = 1;
            DAT = (serial_data2 >> (15 - (cnt_clk - 35) / 2));
        } else {
            CLK = 0;
        }
    } else if ((cnt_clk - 35) == 33) {
        CLK = 1;
    } else if ((cnt_clk - 35) == 34) {
        LAT = 1;
    } else if ((cnt_clk - 35) == 35) {
        LAT = 0;
    }
    if ((cnt_clk - 35) < 36)cnt_clk++;
}

void data_set(uint8_t value) {
    serial_data1 = (value << 9) + 0x00;
    serial_data1 = (value << 9) + 0x10;
    cnt_clk = 0;
}

void main_init(void) {
    OSCCON = 0x70; //intosc 8MHz
    TRISA = 0xFF; //0011,0111
    TRISB = 0x00; //0101,1011
    ANSELA = 0x00; //Use AN0,1,2
    ANSELB = 0x00; //all digital
    WPUA = 0xFF;
    WPUB = 0x00;
    OPTION_REGbits.nWPUEN = 0; //pull-up Enable

    timer0_init(8);
    timer1_init(2);

    INTCONbits.PEIE = 1;
}

int main(void) {
    main_init();
    INTCONbits.GIE = 1;

    while (1) {
        if (sw_p.flag.press == 1) {
            sw_p.flag.press = 0;
            data_set(0);
            LATB0 = ~LATB0;
        }
        if (sw_m.flag.press == 1) {
            sw_m.flag.press = 0;
            data_set(48);
            LATB1 = ~LATB1;
        }
    }
    return 0;
}
