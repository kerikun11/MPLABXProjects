/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    

  Description:
    

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

/*******************************************************************************
  System Specific Definitions

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

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

#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_

#include <stdio.h>
#include <string.h>

#include "system.h"

#include "tcpip_config.h"

// Define a macro describing this hardware set up (used in other files)
#define EXPLORER_16

// Hardware I/O pin mappings
//------------------------------------------------------------------------------

// LEDs
#define LED0_TRIS           (TRISAbits.TRISA0)  // Ref D3
#define LED0_IO             (LATAbits.LATA0)
#define LED1_TRIS           (TRISAbits.TRISA1)  // Ref D4
#define LED1_IO             (LATAbits.LATA1)
#define LED2_TRIS           (TRISAbits.TRISA2)  // Ref D5
#define LED2_IO             (LATAbits.LATA2)
#define LED3_TRIS           (TRISAbits.TRISA3)  // Ref D6
#define LED3_IO             (LATAbits.LATA3)
#define LED4_TRIS           (TRISAbits.TRISA4)  // Ref D7
#define LED4_IO             (LATAbits.LATA4)
#define LED5_TRIS           (TRISAbits.TRISA5)  // Ref D8
#define LED5_IO             (LATAbits.LATA5)
#define LED6_TRIS           (TRISAbits.TRISA6)  // Ref D9
#define LED6_IO             (LATAbits.LATA6)
#define LED7_TRIS           (LATAbits.LATA7)    // Ref D10;  Note: This is multiplexed with BUTTON1, so this LED can't be used.  However, it will glow very dimmly due to a weak pull up resistor.
#define LED7_IO             (LATAbits.LATA7)
#define LED_GET()           (*((volatile unsigned char*)(&LATA)))
#define LED_PUT(a)          (*((volatile unsigned char*)(&LATA)) = (a))

// Momentary push buttons
#define BUTTON0_TRIS        (TRISDbits.TRISD13) // Ref S4
#define BUTTON0_IO          (PORTDbits.RD13)
#define BUTTON1_TRIS        (TRISAbits.TRISA7)  // Ref S5;  Note: This is multiplexed with LED7
#define BUTTON1_IO          (PORTAbits.RA7)
#define BUTTON2_TRIS        (TRISDbits.TRISD7)  // Ref S6
#define BUTTON2_IO          (PORTDbits.RD7)
#define BUTTON3_TRIS        (TRISDbits.TRISD6)  // Ref S3
#define BUTTON3_IO          (PORTDbits.RD6)

#define UARTTX_TRIS         (TRISFbits.TRISF5)
#define UARTTX_IO           (PORTFbits.RF5)
#define UARTRX_TRIS         (TRISFbits.TRISF4)
#define UARTRX_IO           (PORTFbits.RF4)

// 25LC256 I/O pins
#define EEPROM_CS_TRIS      (TRISDbits.TRISD12)
#define EEPROM_CS_IO        (LATDbits.LATD12)
#define EEPROM_SCK_TRIS     (TRISGbits.TRISG6)
#define EEPROM_SDI_TRIS     (TRISGbits.TRISG7)
#define EEPROM_SDO_TRIS     (TRISGbits.TRISG8)
#define EEPROM_SPI_IF       (IFS1bits.SPI2RXIF)
#define EEPROM_SSPBUF       (SPI2BUF)
#define EEPROM_SPICON1      (SPI2CON)
#define EEPROM_SPICON1bits  (SPI2CONbits)
#define EEPROM_SPIBRG       (SPI2BRG)
#define EEPROM_SPISTAT      (SPI2STAT)
#define EEPROM_SPISTATbits  (SPI2STATbits)

// LCD Module I/O pins.  NOTE: On the Explorer 16, the LCD is wired to the
// same PMP lines required to communicate with an ENCX24J600 in parallel
// mode.  Since the LCD does not have a chip select wire, if you are using
// the ENC424J600/624J600 in parallel mode, the LCD cannot be used.
// #if !defined(ENC100_INTERFACE_MODE) || (ENC100_INTERFACE_MODE == 0) // SPI only
    #define LCD_DATA_TRIS       (*((volatile unsigned char*)&TRISE))
    #define LCD_DATA_IO         (*((volatile unsigned char*)&LATE))
    #define LCD_RD_WR_TRIS      (TRISDbits.TRISD5)
    #define LCD_RD_WR_IO        (LATDbits.LATD5)
    #define LCD_RS_TRIS         (TRISBbits.TRISB15)
    #define LCD_RS_IO           (LATBbits.LATB15)
    #define LCD_E_TRIS          (TRISDbits.TRISD4)
    #define LCD_E_IO            (LATDbits.LATD4)
// #endif

//----------------------------
// MRF24W WiFi I/O pins
//----------------------------
// If you have a MRF24W WiFi PICtail, you used to have a choice of using
// either SPI1 or SPI2.  SPI1 is the top-most slot in the Explorer 16
// (closer to the LCD and prototyping area) while SPI2 corresponds to
// insertion of the PICtail into the middle of the side edge connector slot.
// But now, there is only code for SPI1 for code cleanness reason.

    // MRF24W in SPI1 slot
    #define WF_CS_TRIS          (TRISDbits.TRISD9)
    #define WF_CS_IO            (LATDbits.LATD9)
    #define WF_SDI_TRIS         (TRISCbits.TRISC4)
    #define WF_SCK_TRIS         (TRISDbits.TRISD10)
    #define WF_SDO_TRIS         (TRISDbits.TRISD0)
    #define WF_RESET_TRIS       (TRISFbits.TRISF0)
    #define WF_RESET_IO         (LATFbits.LATF0)
    #define WF_INT_TRIS         (TRISEbits.TRISE8)  // INT1
    #define WF_INT_IO           (PORTEbits.RE8)
    #define WF_HIBERNATE_TRIS   (TRISFbits.TRISF1)
    #define WF_HIBERNATE_IO     (PORTFbits.RF1)
    #define WF_INT_EDGE         (INTCONbits.INT1EP)
    #define WF_INT_IE           (IEC0bits.INT1IE)
    #define WF_INT_IF           (IFS0bits.INT1IF)
    #define WF_INT_IE_CLEAR     IEC0CLR
    #define WF_INT_IF_CLEAR     IFS0CLR
    #define WF_INT_IE_SET       IEC0SET
    #define WF_INT_IF_SET       IFS0SET
    #define WF_INT_BIT          0x00000080
    #define WF_INT_IPCSET       IPC1SET
    #define WF_INT_IPCCLR       IPC1CLR
    #define WF_INT_IPC_MASK     0xFF000000
    #define WF_INT_IPC_VALUE    0x0C000000

    #define WF_SSPBUF           (SPI1BUF)
    #define WF_SPISTAT          (SPI1STAT)
    #define WF_SPISTATbits      (SPI1STATbits)
    #define WF_SPICON1          (SPI1CON)
    #define WF_SPICON1bits      (SPI1CONbits)
    #define WF_SPI_IE_CLEAR     IEC0CLR
    #define WF_SPI_IF_CLEAR     IFS0CLR
    #define WF_SPI_INT_BITS     0x03800000
    #define WF_SPI_BRG          (SPI1BRG)
    #define WF_MAX_SPI_FREQ     (10000000ul)    // Hz

// Select which UART the STACK_USE_UART and STACK_USE_UART2TCP_BRIDGE
// options will use.  You can change these to U1BRG, U1MODE, etc. if you
// want to use the UART1 module instead of UART2.
#define UBRG                U2BRG
#define UMODE               U2MODE
#define USTA                U2STA
#define BusyUART()          BusyUART2()
#define CloseUART()         CloseUART2()
#define ConfigIntUART(a)    ConfigIntUART2(a)
#define DataRdyUART()       DataRdyUART2()
#define OpenUART(a,b,c)     OpenUART2(a,b,c)
#define ReadUART()          ReadUART2()
#define WriteUART(a)        WriteUART2(a)
#define getsUART(a,b,c)     getsUART2(a,b,c)
#define putsUART(a)         putsUART2(a)
#define getcUART()          getcUART2()
#define putcUART(a)         do{while( BusyUART()); WriteUART(a); while(BusyUART()); }while(0)
#define putrsUART(a)        putrsUART2(a)

//------------------------------------------------------------------------------
// End of /* Hardware I/O pin mappings */


// Compiler information
//------------------------------------------------------------------------------

// Include proper device header file
#include <p32xxxx.h>
#include <plib.h>

// Base RAM and ROM pointer types for given architecture
#define PTR_BASE        unsigned long
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

// Definitions that apply to all 16-bit and 32-bit products
// (PIC24F, PIC24H, dsPIC30F, dsPIC33F, and PIC32)
#define ROM    const

// 32-bit specific defines (PIC32)
#define far
#define FAR
#define Reset()     SoftReset()
#define ClrWdt()    (WDTCONSET = _WDTCON_WDTCLR_MASK)

//------------------------------------------------------------------------------
// End of /* Compiler information */

#endif /* __SYSTEM_CONFIG_H_ */
