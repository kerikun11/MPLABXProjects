/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/
#ifndef __MRF24XA_H
#define __MRF24XA_H

#include "system.h"
#include "system_config.h"
#include "driver/mrf_miwi/drv_mrf_miwi.h"



#define SEC_LEVEL_CTR           4
#define SEC_LEVEL_CBC_MAC_32    1
#define SEC_LEVEL_CBC_MAC_64    2
#define SEC_LEVEL_CBC_MAC_128   3
#define SEC_LEVEL_CCM_32        5
#define SEC_LEVEL_CCM_64        6
#define SEC_LEVEL_CCM_128       7
#define SEC_ECB                 8

#if defined(PROTOCOL_MIWI) 
    #define PROTOCOL_HEADER_SIZE MIWI_HEADER_LEN
#endif

#if defined(PROTOCOL_MIWI_PRO)
    #define PROTOCOL_HEADER_SIZE MIWI_PRO_HEADER_LEN
#endif

#if defined(PROTOCOL_P2P)
    #define PROTOCOL_HEADER_SIZE 0
#endif

#define LONGADDRESSINGMODE_PREFIX           0x80
#define LONGADDRESSINGMODE_WRITEPREFIX      0x10

#define DR_125KBPS          0x02
#define DR_250KBPS          0x03
#define DR_500KBPS          0x04
#define DR_1MBPS            0x05
#define DR_2MBPS            0x06


#define CHANNEL_11 0x00
#define CHANNEL_12 0x10
#define CHANNEL_13 0x20
#define CHANNEL_14 0x30
#define CHANNEL_15 0x40
#define CHANNEL_16 0x50
#define CHANNEL_17 0x60
#define CHANNEL_18 0x70
#define CHANNEL_19 0x80
#define CHANNEL_20 0x90
#define CHANNEL_21 0xa0
#define CHANNEL_22 0xb0
#define CHANNEL_23 0xc0
#define CHANNEL_24 0xd0
#define CHANNEL_25 0xe0
#define CHANNEL_26 0xf0

#define FULL_CHANNEL_MAP        0x07FFF800


typedef union 
{
    DWORD Val;
    BYTE v[4];
    struct
    {
        BYTE    Status1;
        BYTE    TXStatus;
        BYTE    RXStatus;
        BYTE    Status2;
    } bytes;
    struct
    {
        BYTE    RESERVED1:1;
        BYTE    CALHAIF:1;
        BYTE    CALSOIF:1;
        BYTE    RESERVED2:1;
        BYTE    IDLEIF:1;
        BYTE    RDYIF:1;
        BYTE    RESERVED3:1;
        BYTE    VREGIF:1;

        BYTE    FRMIF:1;
        BYTE    TXOVFIF:1;
        BYTE    TXSZIF:1;
        BYTE    TXCSMAIF:1;
        BYTE    TXACKIF:1;
        BYTE    TXMAIF:1;
        BYTE    TXENCIF:1;
        BYTE    TXIF:1;

        BYTE    STRMIF:1;
        BYTE    RXOVFIF:1;
        BYTE    RXFLTIF:1;
        BYTE    RXIDNTIF:1;
        BYTE    RESERVED4:1;
        BYTE    RXTAGIF:1;
        BYTE    RXDECIF:1;
        BYTE    RXIF:1;

        BYTE    GPIO0IF:1;
        BYTE    GPIO1IF:1;
        BYTE    GPIO2IF:1;
        BYTE    EDIF:1;
        BYTE    LVIF:1;
        BYTE    ERRORIF:1;
        BYTE    RXSFDIF:1;
        BYTE    TXSFDIF:1;

    } bits;                  // bit map of interrupts
} MRF24XA_IFREG;


typedef union
{
    BYTE Val;
    struct
    {
        BYTE        RX_BUFFERED         : 1;
        BYTE        SLEEP               : 1;
        BYTE        RADIO_BUFFERED      : 1;
        BYTE        SEC_INPROCESS       : 1;
    } bits;
} MRF24XA_STATUS;


#endif

