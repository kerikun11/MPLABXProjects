/*********************************************************************
 *
 *					SHA-2 Private Function Library Headers
 *
 *********************************************************************
 * FileName:        sha512_private.h
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
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
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

#define SHA2_ROTL(x,n)      ((x << n) | (x >> (64-n)))   
#define SHA2_ROTR(x,n)      ((x >> n) | (x << (64-n)))
#define SHA2_SHR(x,n)       (x >> n)

#define SHA2_SIG_U0(x)      (SHA2_ROTR(x,28) ^ SHA2_ROTR(x,34) ^ SHA2_ROTR(x,39))
#define SHA2_SIG_U1(x)      (SHA2_ROTR(x,14) ^ SHA2_ROTR(x,18) ^ SHA2_ROTR(x,41))
#define SHA2_SIG_L0(x)      (SHA2_ROTR(x,1) ^ SHA2_ROTR(x,8) ^ SHA2_SHR(x,7))
#define SHA2_SIG_L1(x)      (SHA2_ROTR(x,19) ^ SHA2_ROTR(x,61) ^ SHA2_SHR(x,6))

#define SHA2_CH(x,y,z)      ((x & y) ^ ((~x) & z))
#define SHA2_MAJ(x,y,z)     ((x & y) ^ (x & z) ^ (y & z)) 
 
void SHA512_OutputData (uint8_t * output, uint64_t value);
 void SHA512_HashBlock (SHA512_CONTEXT * context);

 