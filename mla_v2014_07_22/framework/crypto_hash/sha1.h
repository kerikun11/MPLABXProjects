/*********************************************************************
 *
 *                    SHA-1 Function Library Headers
 *
 *********************************************************************
 * FileName:        sha1.h
 * Dependencies:    None
 * Processor:       PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2012 Microchip Technology Inc.  All rights
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

#ifndef __SHA1_H
#define __SHA1_H

#include <stdint.h>

/****************************************************************************
  Section:
    Data Types
  ***************************************************************************/

// Context storage for a hash operation
typedef struct
{
    uint32_t h0;                                            // Hash state h0
    uint32_t h1;                                            // Hash state h1
    uint32_t h2;                                            // Hash state h2
    uint32_t h3;                                            // Hash state h3
    uint32_t h4;                                            // Hash state h4
    uint32_t bytesSoFar;                                    // Total number of bytes hashed so far
    uint32_t * workingBuffer;                               // Pointer to a working buffer for hash calculation
    uint8_t partialBlock[64] __attribute__((aligned(4)));   // Beginning of next 64 byte block
} SHA1_CONTEXT;

/****************************************************************************
  Section:
    Function Prototypes
  ***************************************************************************/
  
// *****************************************************************************
/*
  Function:
    void SHA1_Initialize(SHA1_CONTEXT* context, uint8_t * workingBuffer);

  Summary:
    Initializes a SHA-1 context to perform a SHA-1 hash.

  Description:
    This routine initializes a hash context for the SHA-1 hash.
    
  Precondition:
    None.

  Parameters:
    context - The context to initialize.
    workingBuffer - A working buffer used by the module to calculate the hash.  If 
        the CRYPTO_HASH_CONFIG_SHA_SMALL_RAM macro is defined in sha_config.h, this 
        buffer must contain 16 uint32_t words.  Otherwise, this buffer must contain 
        80 32-bit words, but performance will be slightly improved.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint32_t buffer[16];
    SHA1_CONTEXT context;
    SHA1_Initialize (&context, buffer);
    </code>

  Remarks:
    You must initialize a context before calculating a SHA-1 hash.
*/
void SHA1_Initialize (SHA1_CONTEXT* context, uint32_t * workingBuffer);

// *****************************************************************************
/*
  Function:
    void SHA1_DataAdd (SHA1_CONTEXT* context, uint8_t * data, uint16_t len);

  Summary:
    Adds data to a hash being calculated.

  Description:
    This routine adds data to a SHA-1 hash being calculated.  When the data 
    length reaches a block size (64 bytes), this function will calculate the hash 
    over that block and store the current hash value in the hash context.
    
  Precondition:
    The hash context must be initialized with SHA1_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    data - The data being added.
    len - The length of the data being added.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint8_t data[] = "Hello.";
    uint32_t buffer[16];
    SHA1_CONTEXT context;

    SHA1_Initialize (&context, buffer);

    SHA1_DataAdd (&context, data, 6);
    </code>

  Remarks:
    None.
*/
void SHA1_DataAdd (SHA1_CONTEXT* context, uint8_t * data, uint16_t len);

// *****************************************************************************
/*
  Function:
    void SHA1_Calculate(SHA1_CONTEXT* context, uint8_t * result);

  Summary:
    Finishes calculating a hash.

  Description:
    This routine finishes calculating a SHA-1 hash.  It will automatically add 
    the padding required by the hashing algorithm and return the hash digest.
    
  Precondition:
    The hash context must be initialized with SHA1_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    result - A 20-byte buffer to store the calculated hash digest.

  Returns:
    None.

  Example:
    <code>
    // Initialization for CRYPTO_HASH_CONFIG_SHA_SMALL_RAM
    uint8_t data[] = "Hello.";
    uint32_t buffer[16];
    SHA1_CONTEXT context;
    uint8_t digest[20];

    SHA1_Initialize (&context, buffer);

    SHA1_DataAdd (&context, data, 6);
    SHA1_Calculate (&context, digest);
    </code>

  Remarks:
    None.
*/
void SHA1_Calculate(SHA1_CONTEXT* context, uint8_t * result);


#if defined(__18CXX)
// *****************************************************************************
/*
  Function:
    void SHA1_ROMDataAdd(SHA1_CONTEXT* context, ROM uint8_t * data, uint16_t len);
    
  Summary:
    Adds rom data to a hash being calculated.

  Description:
    This routine adds data to a SHA-1 hash being calculated.  When the data 
    length reaches a block size (64 bytes), this function will calculate the hash 
    over that block and store the current hash value in the hash context.
    
    This routine is used when adding ROM data on 8-bit microcontrollers, as they 
    require a different pointer type to address ROM variables.
    
  Precondition:
    The hash context must be initialized with MD5_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    data - The data being added.
    len - The length of the data being added.

  Returns:
    None.

  Example:
    <code>
    rom uint8_t data[] = "Hello.";
    uint32_t buffer[16];
    SHA1_CONTEXT context;

    SHA1_Initialize (&context, buffer);
    SHA1_ROMDataAdd (&context, data, 6);
    </code>

  Remarks:
    None.
*/
    void SHA1_ROMDataAdd(SHA1_CONTEXT* context, ROM uint8_t * data, uint16_t len);
#else
    // Non-ROM variant for C30 / C32
    #define SHA1_ROMDataAdd(a,b,c)    SHA1_DataAdd(a,(uint8_t*)b,c)
#endif

#endif

