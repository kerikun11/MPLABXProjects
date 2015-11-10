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
#include <buttons.h>
#include <leds.h>
#include <power.h>

/*******************************************************************/
/******** USB stack hardware selection options *********************/
/*******************************************************************/
//This section is the set of definitions required by the MCHPFSUSB
//  framework.  These definitions tell the firmware what mode it is
//  running in, and where it can find the results to some information
//  that the stack needs.
//These definitions are required by every application developed with
//  this revision of the MCHPFSUSB framework.  Please review each
//  option carefully and determine which options are desired/required
//  for your application.

/** USB ************************************************************/
//The PIC18F87J50 FS USB Plug-In Module supports the USE_USB_BUS_SENSE_IO
//feature.  The USE_SELF_POWER_SENSE_IO feature is not implemented on the
//circuit board, so the USE_SELF_POWER_SENSE_IO define should always be
//commented for this hardware platform.

//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2    // Input
#if defined(USE_SELF_POWER_SENSE_IO)
#define self_power          PORTAbits.RA2
#else
#define self_power          1
#endif

//#define USE_USB_BUS_SENSE_IO		//JP1 must be in R-U position to use this feature on this board
#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
#if defined(USE_USB_BUS_SENSE_IO)
#define USB_BUS_SENSE       PORTBbits.RB5
#else
#define USB_BUS_SENSE       1
#endif

//Uncomment this to make the output HEX of this project
//   to be able to be bootloaded using the HID bootloader
#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
