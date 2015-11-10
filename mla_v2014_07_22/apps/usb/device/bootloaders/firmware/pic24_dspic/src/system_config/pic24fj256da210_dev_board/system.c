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

#include <system.h>
#include <system_config.h>
#include <usb/usb.h>
#include <leds.h>
#include <buttons.h>
#include <adc.h>

/** CONFIGURATION Bits **********************************************/
_CONFIG1(
    FWDTEN_OFF &
    ICS_PGx2 &
    GWRP_OFF &
    GCP_OFF &
    JTAGEN_OFF
);

_CONFIG2(
    POSCMOD_HS &
    IOL1WAY_ON &
    OSCIOFNC_ON &
    FCKSM_CSDCMD &
    FNOSC_PRIPLL &
    PLL96MHZ_ON &
    PLLDIV_DIV2 &
    IESO_OFF
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
void __attribute__((interrupt,auto_psv)) _AltUSB1Interrupt()
{
    USBDeviceTasks();
}
#endif


        
