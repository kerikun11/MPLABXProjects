/*******************************************************************************
  System Specific Initializations

  Company:
    Microchip Technology Inc.

  File Name:
    system.c

  Summary:
    System level initializations for the specific Microchip Development Board used.

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

// *****************************************************************************
// Section: Includes
// *****************************************************************************
#include <xc.h>
#include <stdlib.h>
#include <system_config.h>


// *****************************************************************************
// Configuration bits
// *****************************************************************************
// PIC24FJ128B204 Configuration Bit Settings

_CONFIG4( DSBOREN_OFF & DSWDTEN_OFF & DSSWEN_OFF & PLLDIV_4XPLL & I2C1SEL_DISABLE & IOL1WAY_OFF )
//Note: When PLLDIV = 4XPLL, it gives a compilation warning.Hence the above format is used in declaring CONFIG4
//bits
// CONFIG4
//		#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
//		#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
//		#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
//		#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
//		#pragma config DSSWEN = OFF             // DSEN Bit Enable (Deep Sleep operation is always disabled)
////		#pragma config PLLDIV = 4XPLL           // USB 96 MHz PLL Prescaler Select bits (4x PLL selected)
//		#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
//		#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)

// CONFIG3
        #pragma config WPFP = WPFP127       // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
        #pragma config SOSCSEL = ON         // SOSC Selection bits (SOSC circuit selected)
        #pragma config WDTWIN = PS25_0      // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
        #pragma config PLLSS = PLL_PRI      // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
        #pragma config BOREN = ON           // Brown-out Reset Enable (Brown-out Reset Enable)
        #pragma config WPDIS = WPDIS        // Segment Write Protection Disable (Disabled)
        #pragma config WPCFG = WPCFGDIS     // Write Protect Configuration Page Select (Disabled)
        #pragma config WPEND = WPENDMEM     // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
        #pragma config POSCMD = HS          // Primary Oscillator Select (Primary Oscillator Disabled)
        #pragma config WDTCLK = LPRC        // WDT Clock Source Select bits (WDT uses LPRC)
        #pragma config OSCIOFCN = OFF       // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as CLKO (FOSC/2))
        #pragma config FCKSM = CSDCMD       // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
        #pragma config FNOSC = PRIPLL       // Initial Oscillator Select (Fast RC Oscillator with Postscaler (FRCDIV))
        #pragma config ALTCMPI = CxINC_RB   // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
        #pragma config WDTCMX = WDTCLK      // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
        #pragma config VBTBOR = OFF         // VBAT BOR Enable Bit (VBAT BOR is enabled)
        #pragma config IESO = OFF           // Internal External Switchover (Enabled)

// CONFIG1
        #pragma config WDTPS = PS1          // Watchdog Timer Postscaler Select (1:32,768)
        #pragma config FWPSA = PR32         // WDT Prescaler Ratio Select (1:128)
        #pragma config WINDIS = OFF         // Windowed WDT Disable (Standard Watchdog Timer)
        #pragma config FWDTEN = OFF         // Watchdog Timer Enable (WDT enabled in hardware)
        #pragma config ICS = PGx1           // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
        #pragma config LPCFG = OFF          // Low power regulator control (Disabled - regardless of RETEN)
        #pragma config GWRP = OFF           // General Segment Write Protect (Write to program memory allowed)
        #pragma config GCP = OFF            // General Segment Code Protect (Code protection is disabled)
        #pragma config JTAGEN = OFF         // JTAG Port Enable (Enabled)



/*******************************************************************************
  Function:
        void BoardConfig(void)

  Description:
        This function initializes port pins

  Precondition:
        None

  Parameters:
        None

  Return Values:
        None

  Remarks:
        None
 *****************************************************************************/
void BoardConfig(void)
{

    ANSA = 0;
    ANSB = 0;
    ANSC = 0;
}

/*******************************************************************************
  Function:
        void UartConfig(void)

  Description:
        This function initializes Tx port pin

  Precondition:
        None

  Parameters:
        None

  Return Values:
        None

  Remarks:
        None
 *****************************************************************************/
void UartConfig(void)
{
 UART_Tx_REMAP_Reg = 5;  //UART2
}