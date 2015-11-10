// PIC18F27J53 Configuration Bit Settings
// 2015.03.05
#include <xc.h>
#include <stdint.h>

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 2       // PLL Prescaler Selection (Divide by 2 (8 MHz oscillator input))
#pragma config CFGPLLEN = ON    // PLL Enable Configuration Bit (PLL Enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset (Disabled)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = INTOSCPLL  // Oscillator (INTOSCPLL)
#pragma config SOSCSEL = LOW    // T1OSC/SOSC Power Selection Bits (Low Power T1OSC/SOSC circuit selected)
#pragma config CLKOEC = OFF     // EC Clock Out Enable Bit  (CLKO output disabled on the RA6 pin)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF// DSWDT Clock Select (DSWDT uses T1OSC/T1CKI)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config ADCSEL = BIT12   // ADC 10 or 12 Bit Select (12 - Bit ADC Enabled)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_127  // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 127)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region  (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<6:0>/WPEND region ignored)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select bit (valid when WPDIS = 0) (Pages WPFP<6:0> through Configuration Words erase/write protected)
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock bit (System clock at 48 MHz USB CLKEN divide-by is set to 8)

#define _XTAL_FREQ 48000000
#define SW PORTAbits.RA6

#include <My_hedaer_18F.h>
#include <My_button.h>
#include <My_UART_18F.h>
#include <My_I2C_18F.h>
#include <My_I2C.h>
#include <My_PIC18F27J53.h>

button_t sw;

void interrupt ISR(void) {
    interrupt_TXIF();
    if (PIR1bits.RC1IF) {
        PIR1bits.RC1IF = 0;
        uint8_t ascii = RCREG1;
        tx_send(ascii);
    }
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    }
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x80;
    }
    if (PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
    }
}

int main(void) {
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    OSCCONbits.SCS = 0;
    TRISA = 0b01000011;
    TRISB = 0b00110000;
    TRISC = 0b10000010;
    ANCON0 = 0b11111100;
    ANCON1 = 0b00011111;
    INTCON2bits.nRBPU = 0;
    UCFGbits.UOEMON = 0; //USB‚Ì‹@”\‚ðOFF

    timer0_init(8);
    timer1_init(0, FOSC_4);
    timer3_init(2); // button—p
    I2C_init();
    I2C_LCD_init();
    ADC_init(VDD);

    UART_init(1);
    uint8_t txbuf[200];
    ringbuf_init(&tx_buf, txbuf, sizeof (txbuf));

    INTCONbits.GIE = 1;

    I2C_LCD_Clear();
    I2C_LCD_SetCursor(0, 0);
    I2C_LCD_Puts("18F27J53");
    I2C_LCD_SetCursor(0, 1);
    I2C_LCD_Puts("ADC");

    while (1) {
        I2C_LCD_Clear();
        char data[100];
        utoa(data, ADC(0), 4);
        tx_sends(data);
        I2C_LCD_SetCursor(0, 0);
        I2C_LCD_Puts(data);
        tx_send(' ');
        utoa(data, ADC(1), 4);
        tx_sends(data);
        I2C_LCD_SetCursor(0, 1);
        I2C_LCD_Puts(data);
        tx_send('\n');
        Delay_ms(100);
    }
    return 0;
}
