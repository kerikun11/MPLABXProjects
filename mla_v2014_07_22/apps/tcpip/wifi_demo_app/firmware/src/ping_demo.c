/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    ping_demo.c

  Summary:
    

  Description:
    ICMP Client Demo (Ping)

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

#define __PINGDEMO_C_

#include "system_config.h"

#if defined(STACK_USE_ICMP_CLIENT)

#include "tcpip/tcpip.h"
#include "main.h"


#define HOST_TO_PING    "ww1.microchip.com" // Address that ICMP client will ping.  If the DNS client module is not available in the stack, then this hostname is ignored and the local gateway IP address will be pinged instead.

/*****************************************************************************
  Function:
    void PingDemo(void)

  Summary:
    Demonstrates use of the ICMP (Ping) client.

  Description:
    This function implements a simple ICMP client.  The function is called
    periodically by the stack, and it checks if BUTTON0 has been pressed.
    If the button is pressed, the function sends an ICMP Echo Request (Ping)
    to a Microchip web server.  The round trip time is displayed on the UART
    when the response is received.

    This function can be used as a model for applications requiring Ping
    capabilities to check if a host is reachable.

  Precondition:
    TCP is initialized.

  Parameters:
    None

  Returns:
    None
  ***************************************************************************/
void PingDemo(void)
{
    static enum
    {
        SM_HOME = 0,
        SM_GET_ICMP_RESPONSE
    } PingState = SM_HOME;
    static uint32_t Timer;
    int32_t ret;

    switch(PingState)
    {
        case SM_HOME:
            // Send a ping request out if the user pushes BUTTON0 (right-most one)
            if(BUTTON0_IO == 0u)
            {
                // Don't ping flood: wait at least 1 second between ping requests
                if(TickGet() - Timer > 1ul*TICK_SECOND)
                {
                    // Obtain ownership of the ICMP module
                    if(!ICMPBeginUsage())
                        break;

                    // Update anti-ping flood timer
                    Timer = TickGet();

                    // Send ICMP echo request
                    #if defined(STACK_USE_DNS)
                        ICMPSendPingToHostROM((ROM uint8_t*)HOST_TO_PING);
                    #else
                        ICMPSendPing(AppConfig.MyGateway.Val);
                    #endif
                    PingState = SM_GET_ICMP_RESPONSE;
                }
            }
            break;

        case SM_GET_ICMP_RESPONSE:
            // Get the status of the ICMP module
            ret = ICMPGetReply();
            if(ret == -2)
            {
                // Do nothing: still waiting for echo
                break;
            }
            else if(ret == -1)
            {
                // Request timed out
                #if defined(USE_LCD)
                memcpypgm2ram((void*)&LCDText[16], (ROM void *)"Ping timed out", 15);
                LCDUpdate();
                #endif
                PingState = SM_HOME;
            }
            else if(ret == -3)
            {
                // DNS address not resolvable
                #if defined(USE_LCD)
                memcpypgm2ram((void*)&LCDText[16], (ROM void *)"Can't resolve IP", 16);
                LCDUpdate();
                #endif
                PingState = SM_HOME;
            }
            else
            {
                // Echo received.  Time elapsed is stored in ret (Tick units).
                #if defined(USE_LCD)
                memcpypgm2ram((void*)&LCDText[16], (ROM void *)"Reply: ", 7);
                uitoa((uint16_t)TickConvertToMilliseconds((uint32_t)ret), &LCDText[16+7]);
                strcatpgm2ram((char*)&LCDText[16+7], "ms");
                LCDUpdate();
                #endif
                PingState = SM_HOME;
            }

            // Finished with the ICMP module, release it so other apps can begin using it
            ICMPEndUsage();
            break;
    }
}
#endif  //#if defined(STACK_USE_ICMP_CLIENT)
