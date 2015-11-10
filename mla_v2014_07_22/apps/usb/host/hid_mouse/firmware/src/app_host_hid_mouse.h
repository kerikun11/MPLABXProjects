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

#include <usb/usb_host_hid.h>

/*********************************************************************
* Function: void APP_HostHIDMouseInitialize(void);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostHIDMouseInitialize();

/*********************************************************************
* Function: void APP_HostHIDMouseTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized via
*   the APP_HostHIDMouseInitialize() function
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostHIDMouseTasks();

/*********************************************************************
* Function: bool APP_HostHIDMouseReportParser(void);
*
* Overview: parses the HID report to determine if this device is supported
*
* PreCondition: None
*
* Input: None
*
* Output: true if supported, false otherwise
*
********************************************************************/
bool APP_HostHIDMouseReportParser(void);