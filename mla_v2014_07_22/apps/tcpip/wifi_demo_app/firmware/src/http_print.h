/*****************************************************************************
  AUTO-GENERATED CODE:  Microchip MPFS Generator version: 2.2.2

  Microchip TCP/IP Stack Application Demo

  Company:
    Microchip Technology Inc.

  File Name:
    http_print.h

  Summary:
    This file is automatically generated by the MPFS Generator Utility.
    ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR.

  Description:
    Provides callback headers and resolution for user's custom
    HTTP Application.
 *****************************************************************************/

// DOM-IGNORE-BEGIN
/*****************************************************************************
Software License Agreement
Copyright(c) 2014 Microchip Technology Inc. All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital
signal controller that is integrated into your product or third party
product (pursuant to the sublicense terms in the accompanying license
agreement).

You should refer to the license agreement accompanying this Software
for additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
OR OTHER SIMILAR COSTS.
 *****************************************************************************/
// DOM-IGNORE-END

#ifndef __HTTPPRINT_H_
#define __HTTPPRINT_H_

/*****************************************************************************
 * SECTION:  Includes
 *****************************************************************************/
#include "tcpip/tcpip.h"

/*****************************************************************************
 * SECTION:  Global Variables
 *****************************************************************************/
#if defined(STACK_USE_HTTP2_SERVER)

extern HTTP_STUB httpStubs[MAX_HTTP_CONNECTIONS];
extern uint8_t curHTTPID;

/*****************************************************************************
 * SECTION:  Generated Function Prototypes
 *****************************************************************************/
void HTTPPrint(uint32_t callbackID);
void HTTPPrint_hellomsg(void);
void HTTPPrint_cookiename(void);
void HTTPPrint_(void);
void HTTPPrint_builddate(void);
void HTTPPrint_led(uint16_t);
void HTTPPrint_lcdtext(void);
void HTTPPrint_ledSelected(uint16_t,uint16_t);
void HTTPPrint_version(void);
void HTTPPrint_btn(uint16_t);
void HTTPPrint_pot(void);
void HTTPPrint_uploadedmd5(void);
void HTTPPrint_status_fail(void);
void HTTPPrint_config_mac(void);
void HTTPPrint_config_hostname(void);
void HTTPPrint_config_dhcpchecked(void);
void HTTPPrint_config_ip(void);
void HTTPPrint_config_gw(void);
void HTTPPrint_config_subnet(void);
void HTTPPrint_config_dns1(void);
void HTTPPrint_config_dns2(void);
void HTTPPrint_reboot(void);
void HTTPPrint_rebootaddr(void);
void HTTPPrint_status_ok(void);
void HTTPPrint_smtps_en(void);
void HTTPPrint_ddns_status(void);
void HTTPPrint_ddns_status_msg(void);
void HTTPPrint_ddns_service(uint16_t);
void HTTPPrint_ddns_user(void);
void HTTPPrint_ddns_pass(void);
void HTTPPrint_ddns_host(void);

/*****************************************************************************
 * FUNCTION: HTTPPrint
 *
 * RETURNS:  None
 *
 * PARAMS:   callbackID
 *****************************************************************************/
void HTTPPrint(uint32_t callbackID)
{
   switch(callbackID)
   {
        case 0x00000000:
			HTTPIncFile((ROM uint8_t*)"header.inc");
			break;
        case 0x00000001:
			HTTPPrint_hellomsg();
			break;
        case 0x00000002:
			HTTPIncFile((ROM uint8_t*)"footer.inc");
			break;
        case 0x00000003:
			HTTPPrint_cookiename();
			break;
        case 0x00000004:
			HTTPPrint_();
			break;
        case 0x00000005:
			HTTPPrint_builddate();
			break;
        case 0x00000006:
			HTTPPrint_led(7);
			break;
        case 0x00000007:
			HTTPPrint_led(6);
			break;
        case 0x00000008:
			HTTPPrint_led(5);
			break;
        case 0x00000009:
			HTTPPrint_led(4);
			break;
        case 0x0000000a:
			HTTPPrint_led(3);
			break;
        case 0x0000000b:
			HTTPPrint_led(2);
			break;
        case 0x0000000c:
			HTTPPrint_led(1);
			break;
        case 0x0000000d:
			HTTPPrint_lcdtext();
			break;
        case 0x0000000e:
			HTTPPrint_ledSelected(4,true);
			break;
        case 0x0000000f:
			HTTPPrint_ledSelected(4,false);
			break;
        case 0x00000010:
			HTTPPrint_ledSelected(3,true);
			break;
        case 0x00000011:
			HTTPPrint_ledSelected(3,false);
			break;
        case 0x00000012:
			HTTPPrint_ledSelected(2,true);
			break;
        case 0x00000013:
			HTTPPrint_ledSelected(2,false);
			break;
        case 0x00000014:
			HTTPPrint_ledSelected(1,true);
			break;
        case 0x00000015:
			HTTPPrint_ledSelected(1,false);
			break;
        case 0x00000016:
			HTTPPrint_version();
			break;
        case 0x00000017:
			HTTPPrint_led(0);
			break;
        case 0x00000018:
			HTTPPrint_btn(0);
			break;
        case 0x00000019:
			HTTPPrint_btn(1);
			break;
        case 0x0000001a:
			HTTPPrint_btn(2);
			break;
        case 0x0000001b:
			HTTPPrint_btn(3);
			break;
        case 0x0000001c:
			HTTPPrint_pot();
			break;
        case 0x0000001d:
			HTTPPrint_uploadedmd5();
			break;
        case 0x0000001e:
			HTTPPrint_status_fail();
			break;
        case 0x0000001f:
			HTTPPrint_config_mac();
			break;
        case 0x00000020:
			HTTPPrint_config_hostname();
			break;
        case 0x00000021:
			HTTPPrint_config_dhcpchecked();
			break;
        case 0x00000022:
			HTTPPrint_config_ip();
			break;
        case 0x00000023:
			HTTPPrint_config_gw();
			break;
        case 0x00000024:
			HTTPPrint_config_subnet();
			break;
        case 0x00000025:
			HTTPPrint_config_dns1();
			break;
        case 0x00000026:
			HTTPPrint_config_dns2();
			break;
        case 0x00000027:
			HTTPPrint_reboot();
			break;
        case 0x00000028:
			HTTPPrint_rebootaddr();
			break;
        case 0x00000029:
			HTTPPrint_status_ok();
			break;
        case 0x0000002a:
			HTTPPrint_smtps_en();
			break;
        case 0x0000002b:
			HTTPPrint_ddns_status();
			break;
        case 0x0000002c:
			HTTPPrint_ddns_status_msg();
			break;
        case 0x0000002d:
			HTTPPrint_ddns_service(0);
			break;
        case 0x0000002e:
			HTTPPrint_ddns_service(1);
			break;
        case 0x0000002f:
			HTTPPrint_ddns_service(2);
			break;
        case 0x00000030:
			HTTPPrint_ddns_user();
			break;
        case 0x00000031:
			HTTPPrint_ddns_pass();
			break;
        case 0x00000032:
			HTTPPrint_ddns_host();
			break;
       default:
           // Output notification for undefined values
           TCPPutROMArray(sktHTTP, (ROM uint8_t*)"!DEF", 4);
   }

   return;
}

void HTTPPrint_(void)
{
   TCPPut(sktHTTP, '~');
   return;
}

#endif /*STACK_USE_HTTP2_SERVER*/

#endif /*__HTTPPRINT_H_*/
