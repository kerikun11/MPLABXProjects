/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    main.h

  Summary:
    This is the header file for Header for Main Demo App.

  Description:
    This file contains the declaration and Macros for Wi-Fi G Demo App.

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


#ifndef __MAINDEMO_H_
#define __MAINDEMO_H_


// Include all headers for any enabled TCPIP Stack functions
#include "tcpip/tcpip.h"

#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
    #include "tcpip/zero_conf_link_local.h"
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
    #include "tcpip/zero_conf_link_multicast_dns.h"
#endif

#if defined ( EZ_CONFIG_SCAN )
    #include "driver/wifi/mrf24w/src/drv_wifi_easy_config.h"
#endif

#include "drv_wifi_config.h"


#if defined ( EZ_CONFIG_STORE )
    void RestoreWifiConfig(void);
    #define     WF_EEPROM_CFG_VER   0xdeu
#endif

void SaveAppConfig(const APP_CONFIG *AppConfig);


//--------------------------------------------------------------------------------
// These defines use the C preprocessor to create the AppConfig structure elements
//--------------------------------------------------------------------------------
// MDEF(R,N) macro concatenates tokens to form "MY_DEFAULT_<R>uint8_t<N>"
// For example MDEF(IP_ADDR_,4) expands to "MY_DEFAULT_IP_ADDR_BYTE4"

#define MDEF(R,N) MY_DEFAULT_ ## R ## uint8_t ## N

// BUILD_MYDEFAULT32 invokes the MDEF(R,N) macro 4 times to create a 32 bit
// value from 4 byte values.
//
// For example BUILD_MYDEFAULT32(IP_ADDR_) expands to
// (MY_DEFAULT_IP_ADDR_BYTE4<<24|MY_DEFAULT_IP_ADDR_BYTE3<<16
//  |MY_DEFAULT_IP_ADDR_BYTE2<<8|MY_DEFAULT_IP_ADDR_BYTE1)

#define BUILD_MYDEFAULT32(R) (MDEF(R,4)<<24|MDEF(R,3)<<16|MDEF(R,2)<<8|MDEF(R,1))

// MACD(N) expands to MY_DEFAULT_MAC_BYTE<N>
// For example MACD(1) expands to MY_DEFAULT_MAC_BYTE1

#define MACD(N) MY_DEFAULT_MAC_BYTE ## N

// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO


void DoUARTConfig(void);


// Define a header structure for validating the AppConfig data structure in EEPROM/Flash
typedef struct
{
    unsigned short wConfigurationLength;    // Number of bytes saved in EEPROM/Flash (sizeof(APP_CONFIG))
    unsigned short wOriginalChecksum;       // Checksum of the original AppConfig defaults as loaded from ROM (to detect when to wipe the EEPROM/Flash record of AppConfig due to a stack change, such as when switching from Ethernet to Wi-Fi)
    unsigned short wCurrentChecksum;        // Checksum of the current EEPROM/Flash data.  This protects against using corrupt values if power failure occurs while writing them and helps detect coding errors in which some other task writes to the EEPROM in the AppConfig area.
} NVM_VALIDATION_STRUCT;


void DisplayIPValue(IP_ADDR IPVal);

#endif // __MAINDEMO_H_
