/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    System level definitions for the specific Microchip Development Board used.

  Description:
      System Specific Definitions

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

#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_

#include <stdio.h>
#include <string.h>

#include "system.h"

#include "tcpip_config.h"

#define MRF24WG

// Define a macro describing this hardware set up (used in other files)
#define PIC18_EXPLORER

// Hardware I/O pin mappings
//------------------------------------------------------------------------------

// LEDs
#define LED0_TRIS           (TRISDbits.TRISD0)  // Ref D1
#define LED0_IO             (LATDbits.LATD0)
#define LED1_TRIS           (TRISDbits.TRISD1)  // Ref D2
#define LED1_IO             (LATDbits.LATD1)
#define LED2_TRIS           (TRISDbits.TRISD2)  // Ref D3
#define LED2_IO             (LATDbits.LATD2)
#define LED3_TRIS           (TRISDbits.TRISD3)  // Ref D4
#define LED3_IO             (LATDbits.LATD3)
#define LED4_TRIS           (TRISDbits.TRISD4)  // Ref D5
#define LED4_IO             (LATDbits.LATD4)
#define LED5_TRIS           (TRISDbits.TRISD5)  // Ref D6
#define LED5_IO             (LATDbits.LATD5)
#define LED6_TRIS           (TRISDbits.TRISD6)  // Ref D7
#define LED6_IO             (LATDbits.LATD6)
#define LED7_TRIS           (TRISDbits.TRISD7)  // Ref D8
#define LED7_IO             (LATDbits.LATD7)
#define LED_GET()           (LATD)
#define LED_PUT(a)          (LATD = (a))

// Momentary push buttons
#define BUTTON0_TRIS        (TRISAbits.TRISA5)
#define BUTTON0_IO          (PORTAbits.RA5)
#define BUTTON1_TRIS        (TRISBbits.TRISB0)
#define BUTTON1_IO          (PORTBbits.RB0)
#define BUTTON2_TRIS        (TRISBbits.TRISB0)  // No Button2 on this board
#define BUTTON2_IO          (1u)
#define BUTTON3_TRIS        (TRISBbits.TRISB0)  // No Button3 on this board
#define BUTTON3_IO          (1u)

// MRF24W I/O pins
#define WF_CS_TRIS          (TRISCbits.TRISC2)
#define WF_SDI_TRIS         (TRISCbits.TRISC4)
#define WF_SCK_TRIS         (TRISCbits.TRISC3)
#define WF_SDO_TRIS         (TRISCbits.TRISC5)
#define WF_RESET_TRIS       (TRISBbits.TRISB1)
#define WF_RESET_IO         (LATBbits.LATB1)
#define WF_INT_TRIS         (TRISBbits.TRISB0)
#define WF_INT_IO           (PORTBbits.RB0)
#define WF_CS_IO            (LATCbits.LATC2)
#define WF_HIBERNATE_TRIS   (TRISBbits.TRISB2)
#define WF_HIBERNATE_IO     (PORTBbits.RB2)
#define WF_INT_EDGE         (INTCON2bits.INTEDG0)
#define WF_INT_IE           (INTCONbits.INT0IE)
#define WF_INT_IF           (INTCONbits.INT0IF)
#define WF_SPI_IF           (PIR1bits.SSPIF)
#define WF_SSPBUF           (SSP1BUF)
#define WF_SPISTAT          (SSP1STAT)
#define WF_SPISTATbits      (SSP1STATbits)
#define WF_SPICON1          (SSP1CON1)
#define WF_SPICON1bits      (SSP1CON1bits)
#define WF_SPICON2          (SSP1CON2)
#define WF_SPI_IE           (PIE1bits.SSPIE)
#define WF_SPI_IP           (IPR1bits.SSPIP)

// 25LC256 I/O pins
#define EEPROM_CS_TRIS      (TRISAbits.TRISA3)
#define EEPROM_CS_IO        (LATAbits.LATA3)
#define EEPROM_SCK_TRIS     (TRISCbits.TRISC3)
#define EEPROM_SDI_TRIS     (TRISCbits.TRISC4)
#define EEPROM_SDO_TRIS     (TRISCbits.TRISC5)
#define EEPROM_SPI_IF       (PIR1bits.SSPIF)
#define EEPROM_SSPBUF       (SSP1BUF)
#define EEPROM_SPICON1      (SSP1CON1)
#define EEPROM_SPICON1bits  (SSP1CON1bits)
#define EEPROM_SPICON2      (SSP1CON2)
#define EEPROM_SPISTAT      (SSP1STAT)
#define EEPROM_SPISTATbits  (SSP1STATbits)

// Register name fix up for certain processors
#define SPBRGH    SPBRGH1
#define ADCON2    ADCON1

// UART mapping functions for consistent API names across 8-bit and 16 or
// 32 bit compilers.  For simplicity, everything will use "UART" instead
// of USART/EUSART/etc.
//#define BusyUART()          BusyUSART()
//#define CloseUART()         CloseUSART()
//#define ConfigIntUART(a)    ConfigIntUSART(a)
//#define DataRdyUART()       DataRdyUSART()
//#define OpenUART(a,b,c)     OpenUSART(a,b,c)
//#define ReadUART()          ReadUSART()
//#define WriteUART(a)        WriteUSART(a)
//#define getsUART(a,b,c)     getsUSART(b,a)
//#define putsUART(a)         putsUSART(a)
//#define getcUART()          ReadUSART()
//#define putcUART(a)         WriteUSART(a)
//#define putrsUART(a)        putrsUSART((far rom char*)a)

//------------------------------------------------------------------------------
// End of /* Hardware I/O pin mappings */


// Compiler information
//------------------------------------------------------------------------------

// Include proper device header file
#include <xc.h>

// Base RAM and ROM pointer types for given architecture
#define PTR_BASE        unsigned short
#define ROM_PTR_BASE    unsigned long

// Definitions that apply to all except Microchip MPLAB C Compiler for PIC18 MCUs (C18)
#define memcmppgm2ram(a,b,c)    memcmp(a,b,c)
#define strcmppgm2ram(a,b)      strcmp(a,b)
#define memcpypgm2ram(a,b,c)    memcpy(a,b,c)
#define strcpypgm2ram(a,b)      strcpy(a,b)
#define strncpypgm2ram(a,b,c)   strncpy(a,b,c)
#define strstrrampgm(a,b)       strstr(a,b)
#define strlenpgm(a)            strlen(a)
#define strchrpgm(a,b)          strchr(a,b)
#define strcatpgm2ram(a,b)      strcat(a,b)

// Compiler specific definitions
#define __attribute__(a)
#define FAR    far
#define ROM    const
#define rom

//------------------------------------------------------------------------------
// End of /* Compiler information */

#endif /* __SYSTEM_CONFIG_H_ */
