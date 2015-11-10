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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <usb/usb_host_msd_scsi.h>

/*********************************************************************
* Function: void APP_HostMSDSimpleInitialize(void);
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
void APP_HostMSDSimpleInitialize();

/*********************************************************************
* Function: void APP_MountDrive (uint8_t address);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: address - Address of the USB device to mount
*
* Output: None
*
********************************************************************/
void APP_MountDrive(uint8_t address);

/*********************************************************************
* Function: void APP_HostMSDSimpleTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_HostMSDSimpleInitialize() and APP_HostMSDSimpleStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostMSDSimpleTasks();

