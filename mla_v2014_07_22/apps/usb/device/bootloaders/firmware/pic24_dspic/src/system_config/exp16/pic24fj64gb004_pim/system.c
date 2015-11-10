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

#include <p24FJ64GB004.h>
#include <system.h>
#include <system_config.h>
#include <usb/usb.h>
#include <leds.h>
#include <buttons.h>
#include <adc.h>

/** CONFIGURATION Bits **********************************************/
_CONFIG1(
    WDTPS_PS1 &
    FWPSA_PR32 &
    WINDIS_OFF &
    FWDTEN_OFF &
    ICS_PGx1 &
    GWRP_OFF &
    GCP_OFF &
    JTAGEN_OFF
);

_CONFIG2(
    POSCMOD_HS &
    I2C1SEL_PRI &
    IOL1WAY_OFF &
    OSCIOFNC_ON &
    FCKSM_CSDCMD &
    FNOSC_PRIPLL &
    PLL96MHZ_ON &
    PLLDIV_DIV2 &
    IESO_OFF
);

_CONFIG3(
    WPFP_WPFP0 &
    SOSCSEL_SOSC &
    WUTSEL_LEG &
    WPDIS_WPDIS &
    WPCFG_WPCFGDIS &
    WPEND_WPENDMEM
);

_CONFIG4(
    DSWDTPS_DSWDTPS3 &
    DSWDTOSC_LPRC &
    RTCOSC_SOSC &
    DSBOREN_OFF &
    DSWDTEN_OFF
);
 
/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize( SYSTEM_STATE state )
{
    switch(state)
    {
        case SYSTEM_STATE_USB_START:
            //Switch to alternate interrupt vector table for bootloader
            INTCON2bits.ALTIVT = 1;
            BUTTON_Enable(BUTTON_USB_DEVICE_HID_CUSTOM);

            if((BUTTON_IsPressed(BUTTON_USB_DEVICE_HID_CUSTOM)==false) && ((RCON & 0x83) != 0))
            {
                //Switch to app standare IVT for non boot mode
                INTCON2bits.ALTIVT = 0;
                __asm__("goto 0x1800");
            }
            
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
        
            LED_Enable(LED_USB_DEVICE_STATE);
            LED_Enable(LED_USB_DEVICE_HID_CUSTOM);
            
            break;
            
        case SYSTEM_STATE_USB_SUSPEND:
            break;
            
        case SYSTEM_STATE_USB_RESUME:
            break;
    }
}

#if defined(USB_INTERRUPT)
void __attribute__((interrupt,auto_psv)) _USB1Interrupt()
{
    USBDeviceTasks();
}
#endif

