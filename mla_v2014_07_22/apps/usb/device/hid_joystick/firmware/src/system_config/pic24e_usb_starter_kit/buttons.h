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
#include <stdbool.h>

#ifndef BUTTONS_H
#define BUTTONS_H

/*** Button Definitions *********************************************/
#define BUTTON_CONFIGURATION_ENABLED
#define BUTTON_DEVICE_KEYBOARD_DEMO SW1

#define SW1 PORTDbits.RD6
#define SW2  PORTDbits.RD7
#define SW3  PORTDbits.RD13

#define SW1_TRIS  TRISDbits.TRISD6
#define SW2_TRIS  TRISDbits.TRISD7
#define SW3_TRIS  TRISDbits.TRISD13

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define PIN_INPUT           1
#define PIN_OUTPUT          0

#define PIN_DIGITAL         0
#define PIN_ANALOG          1

/*********************************************************************
* Function: bool APP_ButtonIsPressed(DEMO_BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via APP_ButtonConfigure()
*
* Input: DEMO_BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names 
*        of the buttons on the silkscreen on the board (as the demo 
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: TRUE if pressed; FALSE if not pressed.
*
********************************************************************/
//bool APP_ButtonIsPressed(DEMO_BUTTON button);
#define APP_ButtonIsPressed(button) ((button == BUTTON_PRESSED) ? true : false)

/*********************************************************************
* Function: bool APP_ButtonConfigure(DEMO_BUTTON button);
*
* Overview: Configures the button to be used by the demo.
*
* PreCondition: none
*
* Input: DEMO_BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names 
*        of the buttons on the silkscreen on the board (as the demo 
*        code may be ported to other boards).
*         i.e. - ButtonConfigure(BUTTON_SEND_MESSAGE);
*
* Output: TRUE if successful; FALSE if button can't be initialized or
*         doesn't exist for the target hardware platform.
*
********************************************************************/
//bool APP_ButtonSetConfiguration(DEMO_BUTTON_CONFIGURATION button);
#define APP_ButtonSetConfiguration(configuration)  \
{\
    SW1_TRIS = PIN_INPUT;\
}

#endif //BUTTONS_H
#endif //PIC24E_USB_STARTER_KIT