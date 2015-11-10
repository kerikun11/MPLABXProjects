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

#include <stdlib.h>
#include "system_config.h"
#include "crypto_sw/crypto_sw.h"

void AES_SW_CBC_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_CTR_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_ECB_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_OFB_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_CFB_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_GCM_Examples(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_Key_Examples();

#if defined(__C30__) || defined(__C32__)
int main(void)
#else
void main(void)
#endif
{
    SYS_MODULE_OBJ sysObject;
    BLOCK_CIPHER_SW_HANDLE drvHandle;
    
    // Initialize the AES module.  There is no initialization required for the pure software AES module; this function
    // is used in this instance to create code that will be more easily portable to a hardware AES implementation.
    // For the software implementation, BLOCK_CIPHER_SW_INDEX is defined as '0' since there aren't multiple instances of it, as
    // there might be in hardware.  Hardware AES modules may have multiple encryption/decryption engines; in this case,
    // the BLOCK_CIPHER_SW_Initialize function would be used to indicate which one to use, and different macros would be defined
    // by the AES module drivers (e.g. BLOCK_CIPHER_SW_INDEX_0 and BLOCK_CIPHER_SW_INDEX_1 if there were two AES hardware modules).
    sysObject = BLOCK_CIPHER_SW_Initialize(BLOCK_CIPHER_SW_INDEX, NULL);
    if (sysObject != SYS_MODULE_OBJ_STATIC)
    {
        return false;
    }

    drvHandle = BLOCK_CIPHER_SW_Open(BLOCK_CIPHER_SW_INDEX, DRV_IO_INTENT_EXCLUSIVE);
    if (drvHandle == BLOCK_CIPHER_SW_HANDLE_INVALID)
    {
        return false;
    }

    AES_SW_ECB_Examples(drvHandle);

    AES_SW_CBC_Examples(drvHandle);

    AES_SW_CFB_Examples(drvHandle);

    AES_SW_OFB_Examples(drvHandle);

    AES_SW_CTR_Examples(drvHandle);

    AES_SW_GCM_Examples(drvHandle);

    AES_SW_Key_Examples();

    // Close our drive handle and de-initialize the AES module.
    BLOCK_CIPHER_SW_Close (drvHandle);

    BLOCK_CIPHER_SW_Deinitialize (sysObject);

    while(1){}
}
