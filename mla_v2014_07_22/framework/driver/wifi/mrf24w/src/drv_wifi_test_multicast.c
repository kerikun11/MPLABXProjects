/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    drv_wifi_test_multicast.c

  Summary:
    Module for Microchip TCP/IP Stack

  Description:
    Testing Tools to Verify Multi-cast Filter

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

#include "tcpip/tcpip.h"

#if defined(STACK_USE_WF_MCAST_TEST)

enum mCast_SM_t{
    MDNS_RESPONDER_INIT = 0,
    MDNS_RESPONDER_LISTEN,
};

struct mCast_testing_context_t
{
    uint8_t           test_ID;
    uint8_t           filter_Id;
    enum mCast_SM_t StateMachine;
    UDP_SOCKET      socket;
    uint8_t           mCast_MacAddr[6];
    uint8_t           mCast_IPAddr[4];
    UDP_PORT        port;
    NODE_INFO       Remote;

};

struct mCast_testing_context_t  mCast_testing_context_1 = {
    1,
    WF_MULTICAST_FILTER_1,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF0},
    {224,0,0,240},
    5353
};

struct mCast_testing_context_t  mCast_testing_context_2 = {
    2,
    WF_MULTICAST_FILTER_2,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF1},
    {224,0,0,241},
    80
};

#if defined(MRF24WG)
struct mCast_testing_context_t  mCast_testing_context_3 = {
    3,
    WF_MULTICAST_FILTER_3,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF2},
    {224,0,0,242},
    25
};

struct mCast_testing_context_t  mCast_testing_context_4 = {
    4,
    WF_MULTICAST_FILTER_4,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF3},
    {224,0,0,243},
    10000
};

struct mCast_testing_context_t  mCast_testing_context_5 = {
    5,
    WF_MULTICAST_FILTER_5,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF4},
    {224,0,0,244},
    10001
};

struct mCast_testing_context_t  mCast_testing_context_6 = {
    6,
    WF_MULTICAST_FILTER_6,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF5},
    {224,0,0,245},
    9000
};

struct mCast_testing_context_t  mCast_testing_context_7 = {
    7,
    WF_MULTICAST_FILTER_7,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF6},
    {224,0,0,246},
    5358
};

struct mCast_testing_context_t  mCast_testing_context_8 = {
    8,
    WF_MULTICAST_FILTER_8,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF7},
    {224,0,0,247},
    5356
};

struct mCast_testing_context_t  mCast_testing_context_9 = {
    9,
    WF_MULTICAST_FILTER_9,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF8},
    {224,0,0,248},
    10001
};

struct mCast_testing_context_t  mCast_testing_context_10 = {
    10,
    WF_MULTICAST_FILTER_10,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xF9},
    {224,0,0,249},
    10002
};

struct mCast_testing_context_t  mCast_testing_context_11 = {
    11,
    WF_MULTICAST_FILTER_11,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFA},
    {224,0,0,250},
    10003
};

struct mCast_testing_context_t  mCast_testing_context_12 = {
    12,
    WF_MULTICAST_FILTER_12,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFB},
    {224,0,0,251},
    10004
};

struct mCast_testing_context_t  mCast_testing_context_13 = {
    13,
    WF_MULTICAST_FILTER_13,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFC},
    {224,0,0,252},
    10005
};

struct mCast_testing_context_t  mCast_testing_context_14 = {
    14,
    WF_MULTICAST_FILTER_14,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFD},
    {224,0,0,253},
    10006
};

struct mCast_testing_context_t  mCast_testing_context_15 = {
    15,
    WF_MULTICAST_FILTER_15,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFE},
    {224,0,0,254},
    10007
};

struct mCast_testing_context_t  mCast_testing_context_16 = {
    16,
    WF_MULTICAST_FILTER_16,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xEF},
    {224,0,0,239},
    10008
};
#endif


/////////////////////////////////////////
static void WFTestMCast_Process_Sub(struct mCast_testing_context_t *mCast_Context)
{
    unsigned char pcString[30];
    int rc;
    uint16_t i,count;
    char st[80];

    if(mCast_Context->socket == INVALID_UDP_SOCKET)
    {
        mCast_Context->StateMachine = MDNS_RESPONDER_INIT;
    }
    switch(mCast_Context->StateMachine)
    {
        case MDNS_RESPONDER_INIT:
            putsUART("Opening mCast socket \r\n");
            mCast_Context->socket = UDPOpenEx((uint32_t)(PTR_BASE)&(mCast_Context->Remote),UDP_OPEN_NODE_INFO,mCast_Context->port,mCast_Context->port);

            if(mCast_Context->socket == INVALID_UDP_SOCKET)
            {
                sprintf(st,"Can't open mCast UDP-Socket port = %d\r\n",mCast_Context->port);
                putsUART(st);
                //putsUART("Can't open mCast UDP-Socket \r\n");
                return;
            }
            else
                mCast_Context->StateMachine = MDNS_RESPONDER_LISTEN ;
            /* Called from mDNSInitialize. So return immediately */
            break;

        case MDNS_RESPONDER_LISTEN:
        {
            char buf_t[30];
            count = UDPIsGetReady(mCast_Context->socket);
            if(count == 0)return;

            putsUART("[Get MCAST package at <");
            sprintf(buf_t,"%d>  ",mCast_Context->test_ID);
            putsUART(buf_t);

            sprintf(buf_t,"<IP>[%d:%d:%d:%d]:<port>[%d]:",mCast_Context->mCast_IPAddr[0],
                mCast_Context->mCast_IPAddr[1],
                mCast_Context->mCast_IPAddr[2],
                mCast_Context->mCast_IPAddr[3],mCast_Context->port);
            putsUART(buf_t);

            //while(count > 0)
            if(count > 0)
            {
                int num = count > 30? 30:count;
                count -= num;
                rc = UDPGetArray(pcString, num);
                //for(i=0;i<rc;i++)
                for(i=0;i<5;i++)
                {
                    sprintf(buf_t,"%02x ",pcString[i]);
                    putsUART(buf_t);
                }
            }
            putsUART(".....\r\n\r\n");
            break;
        }


        default:
            break;
    }

    return;
}


void WFTestMCast_Process()
{
    if(!MACIsLinked())return;

    WFTestMCast_Process_Sub(&mCast_testing_context_1);
    WFTestMCast_Process_Sub(&mCast_testing_context_2);
#if defined(MRF24WG)
    WFTestMCast_Process_Sub(&mCast_testing_context_3);
    WFTestMCast_Process_Sub(&mCast_testing_context_4);
    WFTestMCast_Process_Sub(&mCast_testing_context_5);
    //WFTestMCast_Process_Sub(&mCast_testing_context_6);
    WFTestMCast_Process_Sub(&mCast_testing_context_7);
#endif
#if 0
    WFTestMCast_Process_Sub(&mCast_testing_context_8);
    WFTestMCast_Process_Sub(&mCast_testing_context_9);
    WFTestMCast_Process_Sub(&mCast_testing_context_10);
    WFTestMCast_Process_Sub(&mCast_testing_context_11);
    WFTestMCast_Process_Sub(&mCast_testing_context_12);
    WFTestMCast_Process_Sub(&mCast_testing_context_13);
    WFTestMCast_Process_Sub(&mCast_testing_context_14);
    WFTestMCast_Process_Sub(&mCast_testing_context_15);
    WFTestMCast_Process_Sub(&mCast_testing_context_16);
#endif

//
    return;
}

static void WFTestMCast_SetFilter_sub(struct mCast_testing_context_t *mCast_Context)
{

    uint8_t *mcast_addr = mCast_Context->mCast_MacAddr;

#ifdef ENABLE_SOFTWARE_MULTICAST_FILTER
        WF_EnableSWMultiCastFilter();
        do {
            tWFMultiCastConfig p_config;

            p_config.filterId = mCast_Context->filter_Id;
            p_config.action = WF_MULTICAST_USE_FILTERS;
            memcpy((void *)p_config.macBytes, (void *)mcast_addr, WF_MAC_ADDRESS_LENGTH);
            p_config.macBitMask = 0x3F; /* each bit corresponds to 6 mac address bytes.
                                            * 1 means to force to compare the byte.
                                            * Conversely 0 means not to compare the byte, and
                                            * accept the byte unconditionally.
                                            */
            WF_MulticastSetConfig(&p_config);
        } while (0);
#else    /* !ENABLE_SOFTWARE_MULTICAST_FILTER */
        WF_SetMultiCastFilter(mCast_Context->filter_Id, mcast_addr);
#endif    /* ENABLE_SOFTWARE_MULTICAST_FILTER */


    return ;
}

void  WFTestMCast_SetFilter(void)
{

   WFTestMCast_SetFilter_sub(&mCast_testing_context_1);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_2);
#if defined(MRF24WG)
   WFTestMCast_SetFilter_sub(&mCast_testing_context_3);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_4);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_5);
   //WFTestMCast_SetFilter_sub(&mCast_testing_context_6);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_7);
#endif
#if 0
   WFTestMCast_SetFilter_sub(&mCast_testing_context_8);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_9);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_10);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_11);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_12);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_13);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_14);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_15);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_16);
#endif
}

#endif
