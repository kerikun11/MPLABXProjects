/******************************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PICmicro(r) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PICmicro Microcontroller products. The
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
********************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "crypto_sw/crypto_sw.h"

#define NUMBER_OF_ENCRYPTION_ROUNDS     32ul

int main (void)
{
    uint32_t key[4];
    uint32_t testData[2];
    uint32_t num_bytes_encrypted;
    SYS_MODULE_OBJ sysObject;
    BLOCK_CIPHER_SW_HANDLE handle;

    BLOCK_CIPHER_SW_ECB_CONTEXT context;

    // Initialize the XTEA module.
    // For the software implementation, BLOCK_CIPHER_SW_INDEX is defined as '0' since there aren't multiple instances of it, as
    // there might be in hardware.  Hardware XTEA modules may have multiple encryption/decryption engines.
    sysObject = BLOCK_CIPHER_SW_Initialize(BLOCK_CIPHER_SW_INDEX, NULL);
    if (sysObject != SYS_MODULE_OBJ_STATIC)
    {
        return false;
    }

    handle = BLOCK_CIPHER_SW_Open(BLOCK_CIPHER_SW_INDEX, DRV_IO_INTENT_EXCLUSIVE);
    if (handle == BLOCK_CIPHER_SW_HANDLE_INVALID)
    {
        return false;
    }

    testData[0] = 0x01234567;
    testData[1] = 0x89ABCDEF;

    key[0] = 1;
    key[1] = 2;
    key[2] = 3;
    key[3] = 4;

    XTEA_SW_Configure (NUMBER_OF_ENCRYPTION_ROUNDS);

    // Initialize the Block Cipher context
    BLOCK_CIPHER_SW_ECB_Initialize (handle, &context, (void *)XTEA_SW_Encrypt, (void *)XTEA_SW_Decrypt, XTEA_SW_BLOCK_SIZE, key, CRYPTO_SW_KEY_SOFTWARE);

    //Encrypt the data
    BLOCK_CIPHER_SW_ECB_Encrypt (handle, (void *)testData, &num_bytes_encrypted, (void *) testData, sizeof(testData), BLOCK_CIPHER_SW_OPTION_STREAM_START);

    // Decrypt the data
    BLOCK_CIPHER_SW_ECB_Decrypt (handle, (void *)testData, &num_bytes_encrypted, (void *) testData, sizeof(testData), BLOCK_CIPHER_SW_OPTION_STREAM_START);

    if ((testData[0] != 0x01234567) || (testData[1] != 0x89ABCDEF))
    {
        while (1);
    }

    // Close our drive handle and de-initialize the XTEA module.
    BLOCK_CIPHER_SW_Close (handle);

    BLOCK_CIPHER_SW_Deinitialize (sysObject);

    while (1);
}









