/*******************************************************************************
 Simple 4-Wire Resistive Touch Screen Driver for the Microchip Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    drv_touch_resistive_adc.h

  Summary:
    Header file for the 4-wire resistive touch screen driver.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END



#ifndef _DRV_TOUCH_RESISTIVE_ADC_H
#define _DRV_TOUCH_RESISTIVE_ADC_H


// Default calibration points
#define TOUCHCAL_ULX 0x2A
#define TOUCHCAL_ULY 0xE67E
#define TOUCHCAL_URX 0x2A
#define TOUCHCAL_URY 0xE67E
#define TOUCHCAL_LLX 0x2A
#define TOUCHCAL_LLY 0xE67E
#define TOUCHCAL_LRX 0x2A
#define TOUCHCAL_LRY 0xE67E


// use this macro to debug the touch screen panel 
// this will enable the use of debugging functions in the C file.
// It assumes that the graphics portion is working.
//#define ENABLE_DEBUG_TOUCHSCREEN


#endif //_DRV_TOUCH_RESISTIVE_ADC_H
