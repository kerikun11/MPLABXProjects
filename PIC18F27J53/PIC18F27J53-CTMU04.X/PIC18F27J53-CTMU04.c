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

#define AVERAGE_NUMBER 10
#define DISCHARGE_TIME 20
#define CHARGE_TIME 5
#define SW PORTBbits.RB0

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATB3
#define LED3 LATB2

#define PIC18F27J53
#define ST7032

#include <My_header.h>
#include <My_button.h>
#include <My_I2C.h>

button_t ct;
uint16_t ctmu_value;

void interrupt ISR(void) {
    UART_ISR();
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x80;
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        button_timer_interrupt(&ct, !(CTMU_read(0) / ctmu_value));
    }
}

void main_init(void) {
    OSC_init();
    TRISA = 0b11101111; // OUT2,OUT1,OUT0,Vcap,SW,SW2,SW1,SW0
    TRISB = 0b00110001; // LED2,LED1,SDA,SCL,ADC1,ADC0,ADC2,POWER_SW
    TRISC = 0b10110010; // RX,TX,D+,D-,Vusb,LED0,T1OSI,T1OSO
    ANCON0 = 0b11110000; // all digital
    ANCON1 = 0b00011111; // AN8,AN9,AN10 is analog
    INTCON2bits.RBPU = 0;

    timer0_init(6); // 用
    timer1_init(0, T1OSC); // 用
    timer3_init(2); // button用
    I2C_init();
    I2C_LCD_init();

    CTMU_init();

    UART_init();
    static uint8_t txbuf[250];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));
    static uint8_t rxbuf[250];
    ringbuf_init(&rx_buf, rxbuf, sizeof (rxbuf));
}
// メインの処理

void main() {
    main_init();

    INTCONbits.GIE = 1;

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("  CTMU  ");
    Delay_ms(200);
    ctmu_value = 4 * CTMU_read(0) / 5;

    while (1) {
        if (ringbuf_num(&rx_buf)) {
            tx_send(ringbuf_pop(&rx_buf));
        }
        if (ct.flag.pressing)LED0 = 1;
        else LED0 = 0;
        if (ct.flag.long_holding_2)LED1 = 1;
        else LED1 = 0;
        if (ct.flag.long_holding_4)LED2 = 1;
        else LED2 = 0;
        if (ct.flag.long_holding_5)LED3 = 1;
        else LED3 = 0;
    }
}
