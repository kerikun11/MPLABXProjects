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

#include <xc.h>
#if 0
	// Note : SYS_FREQ denotes the System clock frequency
		#define SYS_FREQ 32000000UL

		// Note : FCY denotes the instruction cycle clock frequency (SYS_FREQ/2)"
		#define FCY (SYS_FREQ/2)
#endif


/*********************************************************************
* Macro: #define	SYS_CLK_FrequencySystemGet()
*
* Overview: This macro returns the system clock frequency in Hertz.
*			* value is 8 MHz x 4 PLL for PIC24
*
********************************************************************/
#define SYS_CLK_FrequencySystemGet() (32000000ul)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyInstructionGet()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz.
*			* value for PIC24 is <PRE>(SYS_CLK_FrequencySystemGet()/2) </PRE>
*
********************************************************************/
#define SYS_CLK_FrequencyInstructionGet()   (SYS_CLK_FrequencySystemGet() / 2)


#define FCY             (SYS_CLK_FrequencyInstructionGet())

		



/*********************************************************************
* Board Port pin initialization
*********************************************************************/
void BoardConfig(void);
void UartConfig(void);

#endif




