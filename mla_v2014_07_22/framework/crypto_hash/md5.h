/*********************************************************************
 *
 *                    MD5 Function Library Headers
 *
 *********************************************************************
 * FileName:        md5.h
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

#ifndef __MD5_H
#define __MD5_H

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
    uint32_t bytesSoFar;                                    // Total number of bytes hashed so far
    uint8_t partialBlock[64] __attribute__((aligned(4)));   // Beginning of next 64 byte block
} MD5_CONTEXT;

/****************************************************************************
  Section:
    Function Prototypes
  ***************************************************************************/

// *****************************************************************************
/*
  Function:
    void MD5_Initialize(MD5_CONTEXT* context);

  Summary:
    Initializes an MD5 context to perform an MD5 hash.

  Description:
    This routine initializes a hash context for the MD5 hash.
    
  Precondition:
    None.

  Parameters:
    context - The context to initialize.

  Returns:
    None.

  Example:
    <code>
    MD5_CONTEXT context;
    MD5_Initialize (&context);
    </code>

  Remarks:
    You must initialize a context before calculating an MD5 hash.
*/
void MD5_Initialize(MD5_CONTEXT* context);

// *****************************************************************************
/*
  Function:
    void MD5_DataAdd(MD5_CONTEXT* context, uint8_t* data, uint16_t len);

  Summary:
    Adds data to a hash being calculated.

  Description:
    This routine adds data to an MD5 hash being calculated.  When the data 
    length reaches a block size (64 bytes), this function will calculate the hash 
    over that block and store the current hash value in the hash context.
    
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
    uint8_t data[] = "Hello.";
    MD5_CONTEXT context;

    MD5_Initialize (&context);
    MD5_DataAdd (&context, data, 6);
    </code>

  Remarks:
    None.
*/
void MD5_DataAdd(MD5_CONTEXT* context, uint8_t* data, uint16_t len);

// *****************************************************************************
/*
  Function:
    void MD5_Calculate(MD5_CONTEXT* context, uint8_t* result);

  Summary:
    Finishes calculating a hash.

  Description:
    This routine finishes calculating an MD5 hash.  It will automatically add 
    the padding required by the hashing algorithm and return the hash digest.
    
  Precondition:
    The hash context must be initialized with MD5_Initialize.

  Parameters:
    context - The context of the hash being calculated.
    result - A 16-byte buffer to store the calculated hash digest.

  Returns:
    None.

  Example:
    <code>
    uint8_t data[] = "Hello.";
    MD5_CONTEXT context;
    uint8_t digest[16];

    MD5_Initialize (&context);
    MD5_DataAdd (&context, data, 6);
    MD5_Calculate (&context, digest);
    </code>

  Remarks:
    None.
*/
void MD5_Calculate(MD5_CONTEXT* context, uint8_t* result);


#if defined(__18CXX)
// *****************************************************************************
/*
  Function:
    void MD5_ROMDataAdd(MD5_CONTEXT* context, ROM uint8_t* data, uint16_t len);

  Summary:
    Adds rom data to a hash being calculated.

  Description:
    This routine adds data to an MD5 hash being calculated.  When the data 
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
    MD5_CONTEXT context;

    MD5_Initialize (&context);
    MD5_ROMDataAdd (&context, data, 6);
    </code>

  Remarks:
    None.
*/
        void MD5_ROMDataAdd(MD5_CONTEXT* context, ROM uint8_t* data, uint16_t len);
#else
        // Non-ROM variant for C30 / C32
        #define MD5_ROMDataAdd(a,b,c)    MD5_DataAdd(a,(uint8_t*)b,c)
#endif

#endif

