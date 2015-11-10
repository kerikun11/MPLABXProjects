/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    system.c

  Summary:
    System level initializations for the specific Microchip Development Board used.

  Description:
    System Specific Initializations

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <2014> released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

// Set configuration fuses
// Previously it was applied only in main.c where THIS_IS_STACK_APPLICATION is defined
// Now it is moved to system.c without having #if defined around

// DEVCFG0.CP          Code-protect bit
// DEVCFG1.FNOSC       Oscillator selection bits
// DEVCFG1.FSOSCEN     Secondary oscillator enable bit (Disabled)
// DEVCFG1.POSCMOD     Primary oscillator configuration bits (Disabled)
// DEVCFG1.FPBDIV      Peripheral bus clock divisor
// DEVCFG1.FWDTEN      Watchdog timer enable bit
// DEVCFG2.FPLLIDIV    PLL input divider bits
// DEVCFG2.FPLLMUL     PLL multiplier bits
// DEVCFG2.FPLLODIV    Default postscalar for PLL bits
#pragma config FNOSC = FRCPLL, FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_2, FPBDIV = DIV_1, FWDTEN = OFF, POSCMOD = OFF, FSOSCEN = OFF, CP = OFF
