/*********************************************************************
 *
 *                      POLY1305-AES Demo
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    None
 * Processor:       PIC24F
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2014 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *        ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *        used in conjunction with a Microchip ethernet controller for
 *        the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * IMPORTANT:  The implementation and use of third party algorithms,
 * specifications and/or other technology may require a license from
 * various third parties.  It is your responsibility to obtain
 * information regarding any applicable licensing obligations.
 *
 ********************************************************************/

#include "crypto_sw/poly1305_sw.h"
#include <stdint.h>
#include <string.h>
#include <xc.h>

#pragma config IESO = OFF
#pragma config FNOSC = PRIPLL
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config POSCMOD = HS

#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF

POLY1305_SW_CONTEXT context;           // Hash context

// This demo calculates a Poly1305-AES MAC over a set of test vectors from the Poly1305 specification
// http://cr.yp.to/mac/poly1305-20050329.pdf

// Test vector 1

const uint8_t data1[] = {0xf3, 0xf6};
const uint8_t r1[] = {0x85,0x1f,0xc4,0x0c,0x34,0x67,0xac,0x0b,0xe0,0x5c,0xc2,0x04,0x04,0xf3,0xf7,0x00,};
uint8_t key1[] = {0xec,0x07,0x4c,0x83,0x55,0x80,0x74,0x17,0x01,0x42,0x5b,0x62,0x32,0x35,0xad,0xd6,};
uint8_t nonce1[] = {0xfb,0x44,0x73,0x50,0xc4,0xe8,0x68,0xc5,0x2a,0xc3,0x27,0x5c,0xf9,0xd4,0x32,0x7e,};
const uint8_t tag1[] = {0xf4,0xc6,0x33,0xc3,0x04,0x4f,0xc1,0x45,0xf8,0x4f,0x33,0x5c,0xb8,0x19,0x53,0xde,};

// Test vector 2

const uint8_t r2[] = {0xa0,0xf3,0x08,0x00,0x00,0xf4,0x64,0x00,0xd0,0xc7,0xe9,0x07,0x6c,0x83,0x44,0x03,};
uint8_t key2[] = {0x75,0xde,0xaa,0x25,0xc0,0x9f,0x20,0x8e,0x1d,0xc4,0xce,0x6b,0x5c,0xad,0x3f,0xbf,};
uint8_t nonce2[] = {0x61,0xee,0x09,0x21,0x8d,0x29,0xb0,0xaa,0xed,0x7e,0x15,0x4a,0x2c,0x55,0x09,0xcc,};
const uint8_t tag2[] = {0xdd,0x3f,0xab,0x22,0x51,0xf1,0x1a,0xc7,0x59,0xf0,0x88,0x71,0x29,0xcc,0x2e,0xe7,};

// Test vector 3

const uint8_t data3[] = {0x66, 0x3c, 0xea, 0x19, 0x0f, 0xfb, 0x83, 0xd8, 0x95, 0x93, 0xf3, 0xf4, 0x76, 0xb6, 0xbc, 0x24, \
                        0xd7, 0xe6, 0x79, 0x10, 0x7e, 0xa2, 0x6a, 0xdb, 0x8c, 0xaf, 0x66, 0x52, 0xd0, 0x65, 0x61, 0x36,};
const uint8_t r3[] = {0x48,0x44,0x3d,0x0b,0xb0,0xd2,0x11,0x09,0xc8,0x9a,0x10,0x0b,0x5c,0xe2,0xc2,0x08};
uint8_t key3[] = {0x6a,0xcb,0x5f,0x61,0xa7,0x17,0x6d,0xd3,0x20,0xc5,0xc1,0xeb,0x2e,0xdc,0xdc,0x74,};
uint8_t nonce3[] = {0xae,0x21,0x2a,0x55,0x39,0x97,0x29,0x59,0x5d,0xea,0x45,0x8b,0xc6,0x21,0xff,0x0e,};
const uint8_t tag3[] = {0x0e,0xe1,0xc1,0x6b,0xb7,0x3f,0x0f,0x4f,0xd1,0x98,0x81,0x75,0x3c,0x01,0xcd,0xbe,};

// Test vector 4

const uint8_t data4[] = {0xab,0x08,0x12,0x72,0x4a,0x7f,0x1e,0x34,0x27,0x42,0xcb,0xed,0x37,0x4d,0x94,0xd1,\
                            0x36,0xc6,0xb8,0x79,0x5d,0x45,0xb3,0x81,0x98,0x30,0xf2,0xc0,0x44,0x91,0xfa,0xf0,\
                            0x99,0x0c,0x62,0xe4,0x8b,0x80,0x18,0xb2,0xc3,0xe4,0xa0,0xfa,0x31,0x34,0xcb,0x67,\
                            0xfa,0x83,0xe1,0x58,0xc9,0x94,0xd9,0x61,0xc4,0xcb,0x21,0x09,0x5c,0x1b,0xf9,};
const uint8_t r4[] = {0x12,0x97,0x6a,0x08,0xc4,0x42,0x6d,0x0c,0xe8,0xa8,0x24,0x07,0xc4,0xf4,0x82,0x07,};
uint8_t key4[] = {0xe1,0xa5,0x66,0x8a,0x4d,0x5b,0x66,0xa5,0xf6,0x8c,0xc5,0x42,0x4e,0xd5,0x98,0x2d,};
uint8_t nonce4[] = {0x9a,0xe8,0x31,0xe7,0x43,0x97,0x8d,0x3a,0x23,0x52,0x7c,0x71,0x28,0x14,0x9e,0x3a,};
const uint8_t tag4[] = {0x51,0x54,0xad,0x0d,0x2c,0xb2,0x6e,0x01,0x27,0x4f,0xc5,0x11,0x48,0x49,0x1f,0x1b,};

// Buffer to hold the resulting tag
uint8_t tag[16];

// Main test program
int main (void)
{
    // Initialize the POLY1305 library
    POLY1305_SW_Initialize();

    // Test vector 1

    // Initialize the context with the given key and nonce values
    POLY1305_SW_ContextInitialize (&context, (uint8_t *)r1);

    // Add additional data
    POLY1305_SW_DataAdd (&context, (uint8_t *)data1, 2);

    // Calculate the final tag
    POLY1305_SW_Calculate (&context, tag, (uint8_t *)key1, (uint8_t *)nonce1);

    // Compare the calculated tag to the test vector's tag
    if (memcmp (tag1, tag, 16) != 0)
    {
        while(1);
    }

    // Test vector 2 (no data)
    POLY1305_SW_ContextInitialize (&context, (uint8_t *)r2);
    POLY1305_SW_Calculate (&context, tag, (uint8_t *)key2, (uint8_t *)nonce2);

    if (memcmp (tag2, tag, 16) != 0)
    {
        while(1);
    }

    // Test vector 3
    POLY1305_SW_ContextInitialize (&context, (uint8_t *)r3);
    POLY1305_SW_DataAdd (&context, (uint8_t *)data3, 32);
    POLY1305_SW_Calculate (&context, tag, (uint8_t *)key3, (uint8_t *)nonce3);

    if (memcmp (tag3, tag, 16) != 0)
    {
        while(1);
    }

    // Test vector 4
    POLY1305_SW_ContextInitialize (&context, (uint8_t *)r4);
    POLY1305_SW_DataAdd (&context, (uint8_t *)data4, 63);
    POLY1305_SW_Calculate (&context, tag, (uint8_t *)key4, (uint8_t *)nonce4);

    if (memcmp (tag4, tag, 16) != 0)
    {
        while(1);
    }

    // Try adding data in chunks that aren't a factor of the block size
    {
        uint8_t i;

        POLY1305_SW_ContextInitialize (&context, (uint8_t *)r4);
        for (i = 0; i < 21; i++)
        {
            POLY1305_SW_DataAdd (&context, (uint8_t *)data4 + (3 * i), 3);
        }
        POLY1305_SW_Calculate (&context, tag, (uint8_t *)key4, (uint8_t *)nonce4);

        if (memcmp (tag4, tag, 16) != 0)
        {
            while(1);
        }

    }

    while(1);
}
















