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

#include <string.h>
#include "crypto_16bv1/crypto_16bv1.h"

void TDES_CBC_Examples(BLOCK_CIPHER_HANDLE handle);
void TDES_ECB_Examples(BLOCK_CIPHER_HANDLE handle);
void TDES_OFB_Examples(BLOCK_CIPHER_HANDLE handle);
void TDES_CFB_Examples(BLOCK_CIPHER_HANDLE handle);

int main(void)
{
    SYS_MODULE_OBJ sysObject;
    BLOCK_CIPHER_HANDLE handle;

    //Multiple_Thread_Test ();

    // Initialize the AES module.  There is no initialization required for the pure software AES module; this function
    // is used in this instance to create code that will be more easily portable to a hardware AES implementation.
    // For the software implementation, BLOCK_CIPHER_INDEX is defined as '0' since there aren't multiple instances of it, as
    // there might be in hardware.  Hardware AES modules may have multiple encryption/decryption engines; in this case,
    // the BLOCK_CIPHER_16BV1_Initialize function would be used to indicate which one to use, and different macros would be defined
    // by the AES module drivers (e.g. BLOCK_CIPHER_INDEX_0 and BLOCK_CIPHER_INDEX_1 if there were two AES hardware modules).
    sysObject = BLOCK_CIPHER_16BV1_Initialize(BLOCK_CIPHER_INDEX, NULL);
    if (sysObject != SYS_MODULE_OBJ_STATIC)
    {
        return false;
    }

    handle = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }

    TDES_ECB_Examples(handle);

    TDES_CBC_Examples(handle);

    TDES_OFB_Examples(handle);

    TDES_CFB_Examples(handle);


    while(BLOCK_CIPHER_16BV1_GetState(handle) != BLOCK_CIPHER_STATE_IDLE)
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    // Close our drive handle and de-initialize the AES module.
    BLOCK_CIPHER_16BV1_Close (handle);

    BLOCK_CIPHER_16BV1_Deinitialize (sysObject);

    while(1){}
}

