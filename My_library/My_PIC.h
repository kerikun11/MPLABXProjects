/* 
 * File:   My_PIC.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 19:59
 */

#ifndef MY_PIC_H
#define	MY_PIC_H

#include <xc.h>
#include <stdint.h>
//#include "My_ringbuf.h"

//*************************** OSC ***************************//
#if defined(__18F27J53)
//Fosc = 48MHz
//CONFIG : #pragma config OSC = INTOSCPLL
#define _XTAL_FREQ 48000000
void OSC_init(void);
#endif /* PIC18F27J53 */

#if defined(__18F26K22)
// freq = 0 ~ 6 : 1MHz ~ 64MHz
#define _XTAL_FREQ 64000000
void OSC_init(uint8_t freq);
#endif /* PIC18F26K22 */

#if defined(__16F1827)
#define _XTAL_FREQ 32000000
#endif /* PIC16F1827 */

//*************************** timer0 ***************************//
#if defined(__18F27J53)
// prescaler is 0~7
void timer0_init(uint8_t prescaler);
#endif /* PIC18F27J53 */

#if defined(__16F1827)
// prescaler is 0~7
void timer0_init(uint8_t prescaler);
#endif /* PIC16F1827 */

//*************************** timer1 ***************************//
#define FOSC_4 0 // Fosc/4
#define FOSC 1   // Fosc
#define T1OSC 2  // Timer 1 OSC

#if defined(__18F27J53)
// prescaler is 0~3
void timer1_init(uint8_t prescaler, uint8_t clock_select);
#endif /* PIC18F27J53 */

#if defined(__16F1827)
// prescaler is 0~3
void timer1_init(uint8_t prescaler);
#endif /* PIC16F1827 */

//*************************** timer3 ***************************//
#if defined(__18F27J53)
// prescaler is 0~3
void timer3_init(uint8_t prescaler);
#endif /* PIC18F27J53 */

//*************************** timer5 ***************************//
#if defined(__18F27J53)
// prescaler is 0~3
void timer5_init(uint8_t prescaler);
#endif /* PIC18F27J53 */

//*************************** ADC ***************************//
#define VDD 0
#define VREFP 1
#define FVR 3

#if defined(__18F27J53)
// p_ref is VDD or VREFP
void ADC_init(uint8_t p_ref);
#endif /* PIC18F27J53 */

#if defined(__16F1827) || defined(__12F1822)
// p_ref is VDD or VREFP or FVR
void ADC_init(uint8_t p_ref);
#endif /* PIC16F1827 || PIC12F1822 */

// Common Function
uint16_t ADC(uint8_t ch);

//*************************** CTMU ***************************//
#define CTMU_AVERAGE_NUMBER 10
#define CTMU_DISCHARGE_TIME 20  // [us]
#define CTMU_CHARGE_TIME 5      // [us]

#if defined(__18F27J53) || defined(__18F26K22)
void CTMU_init(void);
uint16_t CTMU_read(uint8_t ch);
#endif  /* PIC18F27J53 || PIC18F26K22 */

//*************************** Delay_ms ***************************//
#ifdef _XTAL_FREQ
void Delay_ms(uint16_t ms);
#endif

//*************************** millis ***************************//

void millis_timer(void);
uint32_t millis(void);

#endif	/* MY_PIC_H */

