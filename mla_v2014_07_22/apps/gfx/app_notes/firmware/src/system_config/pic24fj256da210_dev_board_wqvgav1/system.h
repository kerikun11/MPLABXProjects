/*******************************************************************************
  System Specific Definitions

  Company:
    Microchip Technology Inc.

  File Name:
    system.h

  Summary:
    System level definitions for the specific Microchip Development Board used.

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

#ifndef __SYSTEM_H
#define __SYSTEM_H

/*********************************************************************
* PIC Device Specific includes
*********************************************************************/
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include "system_config.h"
#include "driver/nvm/drv_nvm_flash_spi_sst25vf016.h"
#include "internal_resource_main.h"

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencySystemGet()
*
* Overview: This macro returns the system clock frequency in Hertz.
*			* value is 8 MHz x 4 PLL for PIC24
*
********************************************************************/
#define SYS_CLK_FrequencySystemGet()    (32000000ul)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyPeripheralGet()
*
* Overview: This macro returns the peripheral clock frequency
*			used in Hertz.
*			* value for PIC24 is <PRE>(SYS_CLK_FrequencySystemGet()/2) </PRE>
*
********************************************************************/
#define SYS_CLK_FrequencyPeripheralGet()    (SYS_CLK_FrequencySystemGet() / 2)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyInstructionGet()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz.
*			* value for PIC24 is <PRE>(SYS_CLK_FrequencySystemGet()/2) </PRE>
*
********************************************************************/
#define SYS_CLK_FrequencyInstructionGet()   (SYS_CLK_FrequencySystemGet() / 2)

/**********************************************************************
 * __delay_ms define - FCY must be defined before including
 * libpic30.h
 **********************************************************************/
#define FCY             (SYS_CLK_FrequencyInstructionGet())

#include <libpic30.h>

/*********************************************************************
* Board initialization
*********************************************************************/
void SYSTEM_InitializeBoard(void);

/*********************************************************************
* Tick initialization
*********************************************************************/
void SYSTEM_TickInit(void);

/*********************************************************************
* External Memory Programming
*********************************************************************/
void SYSTEM_ProgramExternalMemory();

// macros and typedefs for code readability
typedef enum
{
    ANSEL_DIGITAL = 0,
    ANSEL_ANALOG = 1
}ANSEL_BIT_STATE;

typedef enum
{
    HW_BUTTON_PRESS = 0,
    HW_BUTTON_RELEASE = 1
}HW_BUTTON_STATE;


#endif 




