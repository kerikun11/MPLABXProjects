/*******************************************************************************
   Company:
    Microchip Technology Inc.

   File Name:
    drv_wifi_config.h

   Summary:
    Module for Microchip TCP/IP Stack
    -Provides access to MRF24W WiFi controller
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard

   Description:
    MRF24W Driver Customization

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


#ifndef __WF_CONFIG_H_
#define __WF_CONFIG_H_

#include <stdint.h>

#include "driver/wifi/mrf24w/drv_wifi_api.h"

/*******************************************************************************
 *                                     DEFINES
 *******************************************************************************/

// NOTE:
//      Wifi comm demo declares  WF_INT_VECTOR as _EXTERNAL_1_VECTOR and used in WF_Eint.c.
//      Wifi G demo adopts generic approach taken by demo/console/ezconfig by defining MRF24W_IN_SPI1.
//                  _EXTERNAL_1_VECTOR  = MRF24W_IN_SPI1
// #define WF_INT_VECTOR       _EXTERNAL_1_VECTOR

// #define WF_EASY_CONFIG_DEMO

#define DEMO_VERSION          "1.05"

#define LED_STOP_BLINKING_IF_CONNECTION_FAILED

/* =WF_CONSOLE =======================================================================*/
/* Customize whether the WiFi Driver supports a serial console application            */
/*  To DISABLE the serial console application: Comment out '#define WF_CONSOLE'       */
/*  To ENABLE the serial console application: Uncomment out '#define WF_CONSOLE'      */
/*====================================================================================*/
//#define WF_CONSOLE                    /* needed for console demo : WFDisplayScanMgr */
//#define WF_CONSOLE_IFCFGUTIL          /* needed for console demo */

#define MY_DEFAULT_DOMAIN                           WF_DOMAIN_FCC

#define CFG_WF_INFRASTRUCTURE 1
#define CFG_WF_ADHOC          2
#define CFG_WF_P2P            3
#define CFG_WF_SOFT_AP        4

#define MY_DEFAULT_NETWORK_TYPE                     CFG_WF_SOFT_AP

//
// Retries
//
#define MY_DEFAULT_LIST_RETRY_COUNT_INFRASTRUCTURE  WF_RETRY_FOREVER
#define RETRY_COUNT    (3)

#define MY_DEFAULT_SSID_NAME                        "MCHP_G_xxxx"

/*--------------------------------------------*/
/*  Default settings for SoftAP mode          */
/*--------------------------------------------*/

/* SoftAP function has the full "EasyConfig" function.
 * Your STA can connect to the SoftAP as a client, get the DHCP IP, run ping, and run web browser to connect to Web Server
 * of SoftAP. It will allow you to re-connect / redirect to another AP in infrastructure mode.
 * The reason this demo sits here is simply A) borrow DHCP server; B) borrow HTTP server.
 *
 * Before starting up as SoftAP, prescan (MY_DEFAULT_CHANNEL_LIST_PRESCAN) will be executed.
 * For SoftAP, default channel is assigned as MY_DEFAULT_CHANNEL_LIST i.e single channel 6. This means SoftAP
 * will start up in channel 6.
 * When scan option is selected in EZConfig web browser in SoftAP mode, the prescan results will be displayed.
 * Repeated selection of this scan option will always display the prescan results. From this prescan list, the user can select
 * an AP to be redirected to.
 * When redirected to another AP, the channel list will change to allow more channel listings in infrastructure mode,
 * i.e all channels MY_DEFAULT_CHANNEL_LIST_POSTSCAN. This means AP will scan MY_DEFAULT_CHANNEL_LIST_POSTSCAN
 * channel list.
 *
 * Also note that this is a very simplified SoftAP. So its function is limited as ,
 * A) no routing supported;
 * B) only 1 client allowed (RF module FW version 0x3107, 0x3109, 0x310B)
 *    4 clients allowed     (RF module FW version 0x3108, 0x310A, 0x310C)
 * C) Only supports security mode: open mode and WEP security.
 *
 * SoftAP's default IP is 192.168.1.3 and its Network Mask is 255.255.0.0
 * SoftAP on certain setups with IP adress 192.168.1.1 has problem with DHCP services assigning new IP address on redirection.
 * 192.168.1.1 is a common IP address with most APs.
 * Conflict arises when there are 2 active DHCP servers in the same network (i.e. AP DHCP server and MRF24W EasyConfig DHCP Server).
 * When network redirection is executed, the TCPIP SW may still have the device DHCP server still active.
 * This may require change in TCPIP SW to be able to disable the local DHCP server after network redirection.
 * For now, assign this as 192.168.1.3
 */

#define MY_DEFAULT_WIFI_SECURITY_MODE       WF_SECURITY_OPEN
#define MY_DEFAULT_SCAN_TYPE                WF_ACTIVE_SCAN          /* Dummy, Not used                  */
#define MY_DEFAULT_LIST_RETRY_COUNT         ADHOC_RETRY_COUNT       /* Dummy, Not used                  */
#define MY_DEFAULT_CHANNEL_LIST             {6}                     /* Set SoftAP network channel       */
#define MY_DEFAULT_CHANNEL_LIST_PRESCAN     {}                      /* SoftAP: Pre-scan channel list WF_PRESCAN */
#define MY_DEFAULT_CHANNEL_LIST_POSTSCAN    {}                      /* SoftAP: Post-scan channel list           */
#define MY_DEFAULT_BEACON_TIMEOUT           (40)                    /* Dummy, Not used                  */
#define MY_DEFAULT_PS_POLL                  WF_DISABLED             /* Dummy, Not used                  */
#define SOFTAP_CHECK_LINK_STATUS            WF_DISABLED
#define SOFTAP_LINK_FAILURE_THRESHOLD       40                      /* Consecutive null packet transmission failures
                                                                     * for this amount of times.
                                                                     * Then Softap considers the client has gone away.
                                                                     * This is only effective when SOFTAP_CHECK_LINK_STATUS
                                                                     * is enabled.
                                                                     */

#define MY_DEFAULT_EVENT_NOTIFICATION_LIST  (WF_NOTIFY_CONNECTION_ATTEMPT_SUCCESSFUL  |         \
                                             WF_NOTIFY_CONNECTION_ATTEMPT_FAILED      |         \
                                             WF_NOTIFY_CONNECTION_TEMPORARILY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_PERMANENTLY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_REESTABLISHED)

#define STACK_USE_EZ_CONFIG
#define EZ_CONFIG_SCAN
#define EZ_CONFIG_STALL
#define EZ_CONFIG_STORE

/* Warning !!! Please note that :
 * RF Module FW has a built-in connection manager, and it is enabled by default.
 * So if you want to run your own connection manager in host stack application side,
 * then you should disable the module connection manager to avoid some possible conflict
 * between the two.  Especially these two APIs can be affected if you do not disable it.
 * A) uint16_t WF_CMDisconnect(void)
 * B) uint16_t WF_Scan(uint8_t CpId)
 * If some conflict occurs then these APIs will return failure.
 * Furthermore if you use old MRF24WB FW version, older than 120C, then
 * it can cause fatal issue in module FW side such as FW crash.
 * So for simplicity, if you want to run your own connection manager actively,
 * we strongly recommend to disable the module connection manager, and this
 * #define is make that thing possible. Just un-comment it to do so !
 */
//#define DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE

/*****************************************************************************/
/*****************************************************************************/
/*                             WIFI SECURITY COMPILE-TIME DEFAULTS           */
/*****************************************************************************/
/*****************************************************************************/
// Security modes available on WiFi network:
//   WF_SECURITY_OPEN                      : No security
//   WF_SECURITY_WEP_40                    : WEP Encryption using 40 bit keys
//   WF_SECURITY_WEP_104                   : WEP Encryption using 104 bit keys
//   WF_SECURITY_WPA_WITH_KEY              : WPA-PSK Personal where binary key is given to MRF24W
//   WF_SECURITY_WPA_WITH_PASS_PHRASE      : WPA-PSK Personal where passphrase is given to MRF24W and it calculates the binary key
//   WF_SECURITY_WPA2_WITH_KEY             : WPA2-PSK Personal where binary key is given to MRF24W
//   WF_SECURITY_WPA2_WITH_PASS_PHRASE     : WPA2-PSK Personal where passphrase is given to MRF24W and it calculates the binary key
//   WF_SECURITY_WPA_AUTO_WITH_KEY         : WPA-PSK Personal or WPA2-PSK Personal where binary key is given and MRF24W will
//                                             connect at highest level AP supports (WPA or WPA2)
//   WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE : WPA-PSK Personal or WPA2-PSK Personal where passphrase is given to MRF24W and it
//                                             calculates the binary key and connects at highest level AP supports (WPA or WPA2)

#if defined(__XC32)
/* This option allows host to convert the passphrase to the key by itself instead of relying on RF module FW.
 * Even if you do not use this option, RF module FW will still take care of this key deriviation.
 * However it will take much more time such as 32 seconds for MRF24WB or 25 seconds for MRF24WG.
 * Also note that the reason PIC18/24 are not allowed to use this option is just to save memory space on it.
 * So if you have enough memory on PIC18/24, then you can also use this option with adding WF_pbkdf2.c
 * in your projects.
 */
#define DERIVE_KEY_FROM_PASSPHRASE_IN_HOST
#endif

#if defined (MRF24WG)
/* The module HW has 2 hardware multicast filters. If that is not enough on your application,
 * then you can choose this option to extend it to max 16.  As the macro name indicates this forces
 * the module FW to use software to run the filters instead of hardware.  Downside of this option
 * is the performance can degrade when there are so many multicast packets on air becasue the
 * filtering is done by SW
 */
//#define ENABLE_SOFTWARE_MULTICAST_FILTER
#endif

//-----------------------------------------------------------------------------------
// WPA/WPA2
// If using security mode of WF_SECURITY_WPA_WITH_KEY or WF_SECURITY_WPA2_WITH_KEY, then this section
// must be set to  match the key for MY_DEFAULT_SSID_NAME and MY_DEFAULT_PSK_PHRASE
// combination.  The values below are derived from the SSID "MicrochipDemoAP" and the pass phrase
// "Microchip 802.11 Secret PSK Password".
// The tool at http://www.wireshark.org/tools/wpa-psk.html can be used to generate this field.
//-----------------------------------------------------------------------------------
#define MY_DEFAULT_PSK "\
\x86\xC5\x1D\x71\xD9\x1A\xAA\x49\
\x40\xC8\x88\xC6\xE9\x7A\x4A\xD5\
\xE5\x6D\xDA\x44\x8E\xFB\x9C\x0A\
\xE1\x47\x81\x52\x31\x1C\x13\x7C"

// Default pass phrase used for WF_SECURITY_WPA_WITH_PASS_PHRASE and
// WF_SECURITY_WPA2_WITH_PASS_PHRASE security modes
#define MY_DEFAULT_PSK_PHRASE               "Microchip 802.11 Secret PSK Password"

//-----------------------------------------------------------------------------------
// WEP
// Default WEP keys used in WF_SECURITY_WEP_40  and WF_SECURITY_WEP_104 security mode
// Only WEP key index 0 is valid
//-----------------------------------------------------------------------------------
#define MY_DEFAULT_WEP_PHRASE           "WEP Phrase"

#define MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE  WF_SECURITY_WEP_OPENKEY   /* WF_SECURITY_WEP_OPENKEY (default) or */
                                                                        /* WF_SECURITY_WEP_SHAREDKEY.           */

// string 4 40-bit WEP keys -- corresponding to passphrase of "WEP Phrase"
#define MY_DEFAULT_WEP_KEYS_40 "\
\x5a\xfb\x6c\x8e\x77\
\xc1\x04\x49\xfd\x4e\
\x43\x18\x2b\x33\x88\
\xb0\x73\x69\xf4\x78"

// string containing 4 104-bit WEP keys -- corresponding to passphrase of "WEP Phrase"
#define MY_DEFAULT_WEP_KEYS_104 "\
\x90\xe9\x67\x80\xc7\x39\x40\x9d\xa5\x00\x34\xfc\xaa\
\x77\x4a\x69\x45\xa4\x3d\x66\x63\xfe\x5b\x1d\xb9\xfd\
\x82\x29\x87\x4c\x9b\xdc\x6d\xdf\x87\xd1\xcf\x17\x41\
\xcc\xd7\x62\xde\x92\xad\xba\x3b\x62\x2f\x7f\xbe\xfb"

#endif /* __WF_CONFIG_H_ */
