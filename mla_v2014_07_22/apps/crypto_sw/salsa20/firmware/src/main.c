/*********************************************************************
 *
 *                   SALSA20 Library Demo Project
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

#include "crypto_sw/salsa20_sw.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// This file demonstrates the user of this library with a test vector from the EU's ECRYPT
// The vector used and verified is Set 6, Vector 3
// http://www.ecrypt.eu.org/stream/svn/viewcvs.cgi/*checkout*/ecrypt/trunk/submissions/salsa20/full/verified.test-vectors?rev=210

// An encryption context
SALSA20_SW_CONTEXT context;

// A context for decryption
SALSA20_SW_CONTEXT decryptContext;

// The key to use
uint8_t key[] = {0x0F,0x62,0xB5,0x08,0x5B,0xAE,0x01,0x54,0xA7,0xFA,0x4D,0xA0,0xF3,0x46,0x99,0xEC,      \
                    0x3F,0x92,0xE5,0x38,0x8B,0xDE,0x31,0x84,0xD7,0x2A,0x7D,0xD0,0x23,0x76,0xC9,0x1C,};

// The nonce
uint8_t nonce[] = {0x28,0x8F,0xF6,0x5D,0xC4,0x2B,0x92,0xF9,};

// Buffer for input
// Since the result of the encryption primative is simply xor'd with the input to produce the output, there's 
// no real reason to use actual input to verify functionality.  We can use all zeros instead
uint8_t input[512];

// Buffer for output
uint8_t output[512];

// Test vector result for bytes 0-63
const uint8_t res0to63[] = \
    {0x5E,0x5E,0x71,0xF9,0x01,0x99,0x34,0x03,0x04,0xAB,0xB2,0x2A,0x37,0xB6,0x62,0x5B,\
    0xF8,0x83,0xFB,0x89,0xCE,0x3B,0x21,0xF5,0x4A,0x10,0xB8,0x10,0x66,0xEF,0x87,0xDA,\
    0x30,0xB7,0x76,0x99,0xAA,0x73,0x79,0xDA,0x59,0x5C,0x77,0xDD,0x59,0x54,0x2D,0xA2,\
    0x08,0xE5,0x95,0x4F,0x89,0xE4,0x0E,0xB7,0xAA,0x80,0xA8,0x4A,0x61,0x76,0x66,0x3F,};


// Test vector result for bytes 65472-65535
const uint8_t res65472to65535[] = \
    {0x2D,0xA2,0x17,0x4B,0xD1,0x50,0xA1,0xDF,0xEC,0x17,0x96,0xE9,0x21,0xE9,0xD6,0xE2,\
    0x4E,0xCF,0x02,0x09,0xBC,0xBE,0xA4,0xF9,0x83,0x70,0xFC,0xE6,0x29,0x05,0x6F,0x64,\
    0x91,0x72,0x83,0x43,0x6E,0x2D,0x3F,0x45,0x55,0x62,0x25,0x30,0x7D,0x5C,0xC5,0xA5,\
    0x65,0x32,0x5D,0x89,0x93,0xB3,0x7F,0x16,0x54,0x19,0x5C,0x24,0x0B,0xF7,0x5B,0x16,};


// Test vector result for bytes 65536-65599
const uint8_t res65536to65599[] = \
    {0xAB,0xF3,0x9A,0x21,0x0E,0xEE,0x89,0x59,0x8B,0x71,0x33,0x37,0x70,0x56,0xC2,0xFE,\
    0xF4,0x2D,0xA7,0x31,0x32,0x75,0x63,0xFB,0x67,0xC7,0xBE,0xDB,0x27,0xF3,0x8C,0x7C,\
    0x5A,0x3F,0xC2,0x18,0x3A,0x4C,0x6B,0x27,0x7F,0x90,0x11,0x52,0x47,0x2C,0x6B,0x2A,\
    0xBC,0xF5,0xE3,0x4C,0xBE,0x31,0x5E,0x81,0xFD,0x3D,0x18,0x0B,0x5D,0x66,0xCB,0x6C,};


// Test vector result for bytes 131008-131071
const uint8_t res131008to131071[] = \
    {0x1B,0xA8,0x9D,0xBD,0x3F,0x98,0x83,0x97,0x28,0xF5,0x67,0x91,0xD5,0xB7,0xCE,0x23,\
    0x50,0x36,0xDE,0x84,0x3C,0xCC,0xAB,0x03,0x90,0xB8,0xB5,0x86,0x2F,0x1E,0x45,0x96,\
    0xAE,0x8A,0x16,0xFB,0x23,0xDA,0x99,0x7F,0x37,0x1F,0x4E,0x0A,0xAC,0xC2,0x6D,0xB8,\
    0xEB,0x31,0x4E,0xD4,0x70,0xB1,0xAF,0x6B,0x9F,0x8D,0x69,0xDD,0x79,0xA9,0xD7,0x50,};


int main (void)
{
    uint32_t i;

    // Expand the key
    SALSA20_SW_KeyExpand(&context, nonce, key, 32);

    // Set the input buffer to zero
    memset (input, 0x00, 512);

    // Perform the first 64-byte encryption
    SALSA20_SW_Encrypt (&context, output, input, 64);

    // Check the result
    if (memcmp (output, res0to63, 64) != 0)
    {
        while(1);
    }

    // Verify that this data can be decrypted
    SALSA20_SW_KeyExpand(&decryptContext, nonce, key, 32);
    // Decrypt in place
    SALSA20_SW_Decrypt (&decryptContext, output, output, 64);
    // Compare to the input array
    if (memcmp (output, input, 64) != 0)
    {
        while(1);
    }

    // Verify that we can encrypt the same data up to the second test vector reference
    // This should verify that the nonce is correctly incremented
    for (i = 1; i < 8; i++)
    {
        SALSA20_SW_Encrypt (&context, output + (64 * i), input, 64);
    }
    for (i = 1; i < 128; i++)
    {
        SALSA20_SW_Encrypt (&context, output, input, 512);
    }

    // Check the result
    if (memcmp (output + 512 - 64, res65472to65535, 64) != 0)
    {
        while(1);
    }

    // Encrypt and compare the next 64-byte block
    SALSA20_SW_Encrypt (&context, output, input, 64);
    if (memcmp (output, res65536to65599, 64) != 0)
    {
        while(1);
    }

    // Try to skip directly to 131008, the offset of our last test vector reference
    SALSA20_SW_PositionSet (&context, 0, 0, 131008);
    SALSA20_SW_Encrypt (&context, output, input, 64);
    if (memcmp (output, res131008to131071, 64) != 0)
    {
        while(1);
    }

    while(1);
}




