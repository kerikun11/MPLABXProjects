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
#include <usb/usb_device.h>

/** CONFIGURATION Bits **********************************************/
#pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON      //USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//#pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//#pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
//#pragma config CP2      = OFF
//#pragma config CP3      = OFF
#pragma config CPB      = OFF
//#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
//#pragma config WRT2     = OFF
//#pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
//#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
//#pragma config EBTR2    = OFF
//#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF


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
            LED_Enable(LED_USB_DEVICE_STATE);
            BUTTON_Enable(BUTTON_DEVICE_AUDIO_MICROPHONE_SAMPLE);
            break;
            
        case SYSTEM_STATE_USB_SUSPEND: 
            break;
            
        case SYSTEM_STATE_USB_RESUME:
            break;
    }
}

			
			
#if defined(__XC8) && defined(USB_INTERRUPT)
void interrupt SYS_InterruptHigh(void)
{
    USBDeviceTasks();
}
#endif
