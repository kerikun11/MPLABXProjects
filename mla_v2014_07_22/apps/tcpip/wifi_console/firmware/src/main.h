/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    main.h

  Summary:
    

  Description:
    Headers for TCPIP WiFi Console demo application.

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

#ifndef _MAINDEMO_H_
#define _MAINDEMO_H_

#define BAUD_RATE       (19200)     // bps

#if !defined(THIS_IS_STACK_APPLICATION)
    extern uint8_t AN0String[8];
#endif

void DoUARTConfig(void);

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    void SaveAppConfig(const APP_CONFIG *AppConfig);
#else
    #define SaveAppConfig(a)
#endif

void SMTPDemo(void);
void PingDemo(void);
void PingConsole(void);
void GenericTCPClient(void);
void FTPClient(void);
bool    AutoUpdate_UartXMODEM_24G(void);
void AutoUpdate_TCPClient(void);
void CloudTCPClient(void);
int AutoUpdate_UartXMODEM_Roadrunner(void);
void GenericTCPServer(void);
void BerkeleyTCPClientDemo(void);
void BerkeleyTCPServerDemo(void);
void BerkeleyUDPClientDemo(void);

// Define a header structure for validating the AppConfig data structure in EEPROM/Flash
typedef struct
{
    unsigned short wConfigurationLength;    // Number of bytes saved in EEPROM/Flash (sizeof(APP_CONFIG))
    unsigned short wOriginalChecksum;       // Checksum of the original AppConfig defaults as loaded from ROM (to detect when to wipe the EEPROM/Flash record of AppConfig due to a stack change, such as when switching from Ethernet to Wi-Fi)
    unsigned short wCurrentChecksum;        // Checksum of the current EEPROM/Flash data.  This protects against using corrupt values if power failure occurs while writing them and helps detect coding errors in which some other task writes to the EEPROM in the AppConfig area.
} NVM_VALIDATION_STRUCT;

// An actual function defined in main.c for displaying the current IP
// address on the UART and/or LCD.
void DisplayIPValue(IP_ADDR IPVal);

#endif // _MAINDEMO_H_
