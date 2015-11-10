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

#include <xc.h>
#include <system.h>
#include "usb/usb.h"

/** CONFIGURATION Bits **********************************************/
#pragma config WDTPS = PS1
#pragma config FWPSA = PR32
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config ICS = PGx1
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config JTAGEN = OFF

#pragma config POSCMOD = HS
#pragma config I2C1SEL = PRI
#pragma config IOL1WAY = OFF
#pragma config OSCIOFNC = ON
#pragma config FCKSM = CSDCMD
#pragma config FNOSC = PRIPLL
#pragma config PLL96MHZ = ON
#pragma config PLLDIV = DIV2
#pragma config IESO = OFF

#pragma config WPFP = WPFP0
#pragma config SOSCSEL = SOSC
#pragma config WUTSEL = LEG
#pragma config WPDIS = WPDIS
#pragma config WPCFG = WPCFGDIS
#pragma config WPEND = WPENDMEM

#pragma config DSWDTPS = DSWDTPS3
#pragma config DSWDTOSC = LPRC
#pragma config RTCOSC = SOSC
#pragma config DSBOREN = OFF
#pragma config DSWDTEN = OFF
 
/*********************************************************************
* Function: void SYS_Initialize(void)
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  None
*
* Output: None
*
********************************************************************/
void SYS_Initialize()
{
    //On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
    //by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
    //This allows the device to power up at a lower initial operating frequency, which can be
    //advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
    //operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
    //power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }

    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    LED_Enable(LED_USB_HOST_MSD_DATA_LOGGER);
    LED_Off(LED_USB_HOST_MSD_DATA_LOGGER);
    BUTTON_Enable(BUTTON_USB_HOST_MSD_DATA_LOGGER);
}

/* Interrupt handler for USB host. */
void __attribute__((interrupt,auto_psv)) _USB1Interrupt()
{
    USB_HostInterruptHandler();
}