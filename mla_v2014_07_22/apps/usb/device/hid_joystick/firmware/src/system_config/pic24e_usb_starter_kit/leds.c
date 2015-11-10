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

#if defined (PIC24E_USB_STARTER_KIT)

#include <leds.h>
#include <stdbool.h>
#include <p24EP512GU810.h>

/*********************************************************************
* Function: bool APP_LEDConfiguration(DEMO_LED led);
*
* Overview: Configures the LED for use by the other LED API
*
* PreCondition: none
*
* Input: DEMO_LED led - enumeration of the LEDs available in this 
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LEDConfigure(LED_CONNECTION_DETECTED);
*
* Output: TRUE if successful, FALSE if LED not configured or doesn't
*         exist for this board or was unable to be configured.
*
********************************************************************/
bool APP_LEDSetConfiguration(DEMO_LED_CONFIGURATION led)
{
    LED_D1 = 0;
    LED_D2 = 0;
    LED_D3 = 0;
    LED_D1_TRIS = 0;
    LED_D2_TRIS = 0;
    LED_D3_TRIS = 0;

    return true;
}

#endif



