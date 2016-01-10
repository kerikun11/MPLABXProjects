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

#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>

/*** LED Demo Cofinguration Definitions ***************************************/
typedef enum
{
    LED_CONFIGURATION_POWER_OFF,
    LED_CONFIGURATION_DEMO_RUNNING
} DEMO_LED_CONFIGURATION;

/*** LED Demo Usage Definitions ***********************************************/
#define LED_USB_STATUS   LED_D1
#define LED_CAPS_LOCK    LED_D2

/** Demo board specific definitions *********************************/
#define LED_D1        LATDbits.LATD0
#define LED_D2        LATDbits.LATD1
#define LED_D3        LATDbits.LATD2

#define LED_D1_TRIS     TRISDbits.TRISD0
#define LED_D2_TRIS     TRISDbits.TRISD1
#define LED_D3_TRIS     TRISDbits.TRISD2

#define LED_ON  1
#define LED_OFF 0

#define LED_COUNT 3

/*********************************************************************
* Function: void APP_LEDOn(DEMO_LED led);
*
* Overview: Turns requested LED on
*
* PreCondition: LED configured via APP_LEDConfigure()
*
* Input: DEMO_LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - APP_LEDOn(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
//void APP_LEDOn(DEMO_LED led);
#define APP_LEDOn(led) led = LED_ON

/*********************************************************************
* Function: void APP_LEDOff(DEMO_LED led);
*
* Overview: Turns requested LED off
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: DEMO_LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - APP_LEDOff(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
//void APP_LEDOff(DEMO_LED led);
#define APP_LEDOff(led) led = LED_OFF

/*********************************************************************
* Function: void APP_LEDToggle(DEMO_LED led);
*
* Overview: Toggles the state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: DEMO_LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - APP_LEDToggle(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
//void APP_LEDToggle(DEMO_LED led);
#define APP_LEDToggle(led) led ^= 1;

/*********************************************************************
* Function: bool LEDGet(DEMO_LED led);
*
* Overview: Returns the current state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: DEMO_LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LEDGet(LED_CONNECTION_DETECTED);
*
* Output: true if on, false if off
*
********************************************************************/
//bool APP_LEDGet(DEMO_LED led);
#define APP_LEDGet(led) ((led == LED_ON)? true : false)

/*********************************************************************
* Function: bool APP_LEDSet(DEMO_LED led);
*
* Overview: Sets the led to either on/off
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: bool true = on, false = off
*
********************************************************************/
//bool APP_LEDSet(DEMO_LED led);
#define APP_LEDSet(led, bool_setting) {led = bool_setting}

/*********************************************************************
* Function: bool APP_LEDConfigure(DEMO_LED led);
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
* Output: TRUE if successful, FALSE if LED not configured or doesn・スt 
*         exist for this board.
*
********************************************************************/
bool APP_LEDSetConfiguration(DEMO_LED_CONFIGURATION led);

#endif //LEDS_H
#endif //PIC24E_USB_STARTER_KIT
