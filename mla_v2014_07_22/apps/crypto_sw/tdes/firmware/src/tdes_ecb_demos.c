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

#include "crypto_sw/crypto_sw.h"
#include <stdlib.h>
#include <string.h>

void TDES_SW_ECBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);
void TDES_SW_ECBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);

void TDES_SW_ECB_Examples(BLOCK_CIPHER_SW_HANDLE handle)
{
    TDES_SW_ECBEncrypt_header_example1(handle);
    TDES_SW_ECBDecrypt_header_example1(handle);
}

void TDES_SW_ECBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from count=1 of TECBMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    static unsigned char __attribute__((aligned)) TDESKey[]  =   { 
                                            0x25, 0x9d, 0xf1, 0x6e, 0x7a, 0xf8, 0x04, 0xfe,
                                            0x83, 0xb9, 0x0e, 0x9b, 0xf7, 0xc7, 0xe5, 0x57,
                                            0x25, 0x9d, 0xf1, 0x6e, 0x7a, 0xf8, 0x04, 0xfe
                                        };

    static unsigned char __attribute__((aligned)) plain_text[] = {   
                                            0xa4, 0x61, 0x9c, 0x43, 0x3b, 0xbd, 0x67, 0x87,
                                            0xc0, 0x7c, 0x81, 0x72, 0x8f, 0x9a, 0xc9, 0xfa
                                        };



    BLOCK_CIPHER_SW_ECB_CONTEXT context;
    TDES_SW_ROUND_KEYS __attribute__((aligned)) round_keys;
    unsigned long num_bytes_encrypted;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_SW_BLOCK_SIZE
    unsigned char * cipher_text       = (unsigned char*)malloc(sizeof(plain_text));
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    TDES_SW_RoundKeysCreate (    &round_keys,
                            (unsigned char*)TDESKey
                       );
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_SW_ECB_Initialize (handle, &context, TDES_SW_Encrypt, TDES_SW_Decrypt, TDES_SW_BLOCK_SIZE, &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Encrypt the data
    BLOCK_CIPHER_SW_ECB_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Now let's check the results
    {
        static unsigned char expected_result[] = {  
                                                    0x9e, 0x06, 0xde, 0x15, 0x5c, 0x48, 0x3c, 0x6b, 
                                                    0xcf, 0xd8, 0x34, 0xdb, 0xc8, 0xbd, 0x58, 0x30                        
                                                 };

        unsigned int i;

        for(i=0;i<sizeof(plain_text);i++)
        {
            if(cipher_text[i] != expected_result[i])
            {
                //Error: results don't match what was expected
                while(1){};
            }
        }
    }

    free(cipher_text);
}


void TDES_SW_ECBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from count=1[decrypt] of TECBMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    static unsigned char __attribute__((aligned)) TDESKey[]  =   { 
                                            0x02, 0x3d, 0xfb, 0xe6, 0x62, 0x1a, 0xa1, 0x7c,
                                            0xc2, 0x19, 0xea, 0xe9, 0xcd, 0xec, 0xd9, 0x23,
                                            0x02, 0x3d, 0xfb, 0xe6, 0x62, 0x1a, 0xa1, 0x7c
                                        };

    static unsigned char __attribute__((aligned)) cipher_text[] = {   
                                            0x54, 0x04, 0x5d, 0xc7, 0x1d, 0x8d, 0x56, 0x5b, 
                                            0x22, 0x7e, 0xc1, 0x9f, 0x06, 0xfe, 0xf9, 0x12
                                        };

    TDES_SW_ROUND_KEYS round_keys;
    BLOCK_CIPHER_SW_ECB_CONTEXT context;
    unsigned long num_bytes_decrypted;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_SW_BLOCK_SIZE
    unsigned char * plain_text       = (unsigned char*)malloc(sizeof(cipher_text));
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    TDES_SW_RoundKeysCreate (   &round_keys,
                            (unsigned char*)TDESKey
                       );
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_SW_ECB_Initialize (handle, &context, TDES_SW_Encrypt, TDES_SW_Decrypt, TDES_SW_BLOCK_SIZE, &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Decrypt the data
    BLOCK_CIPHER_SW_ECB_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Now let's check the results
    {
        static unsigned char expected_result[] =      { 0x9b, 0x07, 0x16, 0x22, 0x18, 0x1e, 0x64, 0x12, 
                                                        0xde, 0x60, 0x66, 0x42, 0x94, 0x01, 0x41, 0x0d
                                                      };

        unsigned int i;

        for(i=0;i<sizeof(cipher_text);i++)
        {
            if(plain_text[i] != expected_result[i])
            {
                //Error: results don't match what was expected
                while(1){};
            }
        }
    }

    free(plain_text);
}
