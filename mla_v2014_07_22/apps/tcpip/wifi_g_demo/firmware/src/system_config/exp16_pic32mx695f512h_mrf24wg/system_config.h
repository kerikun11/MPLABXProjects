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

// ====================================================
//   Hardware mappings
// ====================================================

//----------------------------
// LED and Button I/O pins
//----------------------------
#define LED0_TRIS           (TRISEbits.TRISE0)  // Ref D10 Green
#define LED0_IO             (LATEbits.LATE0)
#define LED1_TRIS           (TRISFbits.TRISF1)  // Ref D9 Yellow
#define LED1_IO             (LATFbits.LATF1)
#define LED2_TRIS           (TRISFbits.TRISF0)  // Ref D8 Red
#define LED2_IO             (LATFbits.LATF0)

#define LEDS_ON()           {LED0_ON(); LED1_ON(); LED2_ON();}
#define LEDS_OFF()          {LED0_OFF(); LED1_OFF(); LED2_OFF();}
#define LED0_ON()           LATESET = BIT_0;
#define LED0_OFF()          LATECLR = BIT_0;
#define LED0_INV()          LATEINV = BIT_0;

#define LED1_ON()           LATFSET = BIT_1;
#define LED1_OFF()          LATFCLR = BIT_1;
#define LED1_INV()          LATFINV = BIT_1;

#define LED2_ON()           LATFSET = BIT_0;
#define LED2_OFF()          LATFCLR = BIT_0;
#define LED2_INV()          LATFINV = BIT_0;

#define SW0_TRIS            (TRISDbits.TRISD9)
#define SW0_IO              (PORTDbits.RD9)

#define VBAT_TRIS           (TRISBbits.TRISB0)     // Battery level ADC input

// Added to support EZ_CONFIG_STORE
// 25LC256 I/O pins
//#define EEPROM_CS_TRIS        (TRISDbits.TRISD12)
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

//----------------------------
// MRF24WG0MA/B WiFi I/O pins
//----------------------------

#define WF_CS_TRIS          (TRISGbits.TRISG9)
#define WF_CS_IO            (LATGbits.LATG9)
#define WF_SDI_TRIS         (TRISGbits.TRISG7)
#define WF_SCK_TRIS         (TRISGbits.TRISG6)
#define WF_SDO_TRIS         (TRISGbits.TRISG8)
#define WF_RESET_TRIS       (TRISDbits.TRISD1)
#define WF_RESET_IO         (LATDbits.LATD1)

// NOTE:
//   Wifi common demos declare WF_INT_VECTOR as _EXTERNAL_1_VECTOR and used in WF_Eint.c.
//   Wifi G demo adopts generic approach taken by demo/console/ezconfig by defining MRF24W_IN_SPI1.
//   _EXTERNAL_1_VECTOR  = MRF24W_IN_SPI1
#define MRF24W_IN_SPI1

#define WF_INT_TRIS         (TRISDbits.TRISD8)  // INT1
#define WF_INT_IO           (PORTDbits.RD8)

#define WF_HIBERNATE_TRIS   (TRISEbits.TRISE4)
#define WF_HIBERNATE_IO     (PORTEbits.RE4)

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

#define WF_SSPBUF           (SPI2BUF)
#define WF_SPISTAT          (SPI2STAT)
#define WF_SPISTATbits      (SPI2STATbits)

#define WF_SPICON1          (SPI2CON)
#define WF_SPICON1bits      (SPI2CONbits)
#define WF_SPI_IE_CLEAR     IEC1CLR
#define WF_SPI_IF_CLEAR     IFS1CLR
#define WF_SPI_INT_BITS     0x000000e0
#define WF_SPI_BRG          (SPI2BRG)
#define WF_MAX_SPI_FREQ     (10000000ul)    // Hz

//----------------------------
// UART to Telnet Mapping
//----------------------------
#define BusyUART()          (TelnetOutFree() ? 0 : (StackTask(), 1))
#define putcUART            putchar
#define putrsUART(a)        fputs((const char*)a,(FILE *)stdout)
#define putsUART(a)         fputs((const char*)a,(FILE *)stdout)
#define DataRdyUART()       TelnetInChars()
#define ReadUART()          TelnetGet()

//----------------------------
// Sensor Port Mapping
//----------------------------
#define SENSOR_UART         UART2

// ====================================================
//   End of Hardware mappings
// ====================================================


// ====================================================
//   Compiler Information
// ====================================================

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

// ====================================================
//   End of Compiler Information
// ====================================================

#endif /* __SYSTEM_CONFIG_H_ */
