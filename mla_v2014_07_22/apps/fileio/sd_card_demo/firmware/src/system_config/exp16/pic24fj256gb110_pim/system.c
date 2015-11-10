/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#include "system_config.h"
#include "system.h"
#include <xc.h>
#include <stdbool.h>

/** CONFIGURATION Bits **********************************************/
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config ICS = PGx2

#pragma config PLL_96MHZ = ON
#pragma config IESO = OFF
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = ON
#pragma config POSCMOD = HS
#pragma config FNOSC = PRIPLL
#pragma config PLLDIV = DIV2
#pragma config IOL1WAY = ON

void SYSTEM_Initialize (void)
{
    AD1PCFGL = 0xFFFF;
}


void USER_SdSpiConfigurePins_1 (void)
{
    //Initialize the SPI
    RPINR20bits.SDI1R = 23;
    RPOR7bits.RP15R = 7;
    RPOR0bits.RP0R = 8;    

    //enable a pull-up for the card detect, just in case the SD-Card isn't attached
    //  then lets have a pull-up to make sure we don't think it is there.
    CNPU5bits.CN68PUE = 1;

    // Deassert the chip select pin
    LATBbits.LATB1 = 1;
    // Configure CS pin as an output
    TRISBbits.TRISB1 = 0;
    // Configure CD pin as an input
    TRISFbits.TRISF0 = 1;
    // Configure WP pin as an input
    TRISFbits.TRISF1 = 1;
}

inline void USER_SdSpiSetCs_1(uint8_t a)
{
    LATBbits.LATB1 = a;
}

inline bool USER_SdSpiGetCd_1(void)
{
    return (!PORTFbits.RF0) ? true : false;
}

inline bool USER_SdSpiGetWp_1(void)
{
    return (PORTFbits.RF1) ? true : false;
}
