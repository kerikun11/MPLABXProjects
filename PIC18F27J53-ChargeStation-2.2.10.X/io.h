/* 
 * File:   io.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 9:14
 */

#ifndef IO_H
#define	IO_H

#include <xc.h>
#include <stdint.h>

// Number
#define CUT_CURRENT 100  // [mA]
#define CUT_TIME    6    // [s]

// Hardware Mapping
#define CTMU0 0 // RA0
#define CTMU1 1 // RA1
#define CTMU2 2 // RA2
#define CTMUM 3 // RA3

#define POWER_SW 12 // AN12,PORTBbits.RB0

#define ADC0 8  // AN8
#define ADC1 9  // AN9
#define ADC2 10 // AN10

#define OUT0 LATA5
#define OUT1 LATA6
#define OUT2 LATA7

#define LED0 LATB7
#define LED1 LATB6
#define LED2 LATC2

// Port Mapping
#define NUM_PORT    3
#define PORT_L      0
#define PORT_C      1
#define PORT_R      2

// Power Output
void OUT(uint8_t b, uint8_t value);
// return analog pin number
uint8_t ANALOG_IN(uint8_t b);
// LED Output
void LED_output(uint8_t b, uint8_t value);

#endif	/* IO_MAPPING_H */

