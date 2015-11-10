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

void AES_SW_OFBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);
void AES_SW_OFBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);

void AES_SW_OFB_Examples(BLOCK_CIPHER_SW_HANDLE handle)
{
    AES_SW_OFBEncrypt_header_example1(handle);
    AES_SW_OFBDecrypt_header_example1(handle);
}

void AES_SW_OFBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //This example is taken from appendix F.4.1 of SP800-38a.
    //  http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.
    static const uint8_t AESKey128[]              = { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static const uint8_t initial_data[]           = { 0x00, 0x01, 0x02, 0x03, 
                                                    0x04, 0x05, 0x06, 0x07, 
                                                    0x08, 0x09, 0x0a, 0x0b, 
                                                    0x0c, 0x0d, 0x0e, 0x0f
                                                  };

    static const uint8_t plain_text[]             = { 0x6b, 0xc1, 0xbe, 0xe2, 
                                                    0x2e, 0x40, 0x9f, 0x96, 
                                                    0xe9, 0x3d, 0x7e, 0x11, 
                                                    0x73, 0x93, 0x17, 0x2a,
 
                                                    0xae, 0x2d, 0x8a, 0x57, 
                                                    0x1e, 0x03, 0xac, 0x9c, 
                                                    0x9e, 0xb7, 0x6f, 0xac, 
                                                    0x45, 0xaf, 0x8e, 0x51, 

                                                    0x30, 0xc8, 0x1c, 0x46, 
                                                    0xa3, 0x5c, 0xe4, 0x11, 
                                                    0xe5, 0xfb, 0xc1, 0x19, 
                                                    0x1a, 0x0a, 0x52, 0xef,
 
                                                    0xf6, 0x9f, 0x24, 0x45, 
                                                    0xdf, 0x4f, 0x9b, 0x17, 
                                                    0xad, 0x2b, 0x41, 0x7b, 
                                                    0xe6, 0x6c, 0x37, 0x10
                                                   };   

    static uint8_t cipher_text[sizeof(plain_text)];
                                            
    AES_SW_ROUND_KEYS_128_BIT round_keys;
    BLOCK_CIPHER_SW_OFB_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[AES_SW_BLOCK_SIZE*4];
    uint32_t numCipherBytes;
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    AES_SW_RoundKeysCreate(     &round_keys,
                            (uint8_t*)AESKey128,
                            AES_SW_KEY_SIZE_128_BIT
                       );

	// Initialize the Block Cipher context
    BLOCK_CIPHER_SW_OFB_Initialize (handle, &context, AES_SW_Encrypt, AES_SW_Decrypt, AES_SW_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_SW_OFB_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Encrypt the data
    BLOCK_CIPHER_SW_OFB_Encrypt (handle, cipher_text, &numCipherBytes, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_SW_OPTION_STREAM_CONTINUE);

    //Now let's check the results
    {
        static uint8_t expected_result[] = 
                                                      { 0x3b, 0x3f, 0xd9, 0x2e, 
                                                        0xb7, 0x2d, 0xad, 0x20, 
                                                        0x33, 0x34, 0x49, 0xf8, 
                                                        0xe8, 0x3c, 0xfb, 0x4a, 

                                                        0x77, 0x89, 0x50, 0x8d, 
                                                        0x16, 0x91, 0x8f, 0x03, 
                                                        0xf5, 0x3c, 0x52, 0xda, 
                                                        0xc5, 0x4e, 0xd8, 0x25, 

                                                        0x97, 0x40, 0x05, 0x1e, 
                                                        0x9c, 0x5f, 0xec, 0xf6, 
                                                        0x43, 0x44, 0xf7, 0xa8, 
                                                        0x22, 0x60, 0xed, 0xcc, 

                                                        0x30, 0x4c, 0x65, 0x28, 
                                                        0xf6, 0x59, 0xc7, 0x78, 
                                                        0x66, 0xa5, 0x10, 0xd9, 
                                                        0xc1, 0xd6, 0xae, 0x5e                          
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
}

void AES_SW_OFBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //This example is taken from appendix F.4.2 of SP800-38a.
    //  http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.
    static const uint8_t AESKey128[]              = { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static const uint8_t initial_data[]           = { 0x00, 0x01, 0x02, 0x03, 
                                                    0x04, 0x05, 0x06, 0x07, 
                                                    0x08, 0x09, 0x0a, 0x0b, 
                                                    0x0c, 0x0d, 0x0e, 0x0f
                                                  };

    static const uint8_t cipher_text[]             = { 
                                                    0x3b, 0x3f, 0xd9, 0x2e, 
                                                    0xb7, 0x2d, 0xad, 0x20, 
                                                    0x33, 0x34, 0x49, 0xf8, 
                                                    0xe8, 0x3c, 0xfb, 0x4a, 

                                                    0x77, 0x89, 0x50, 0x8d, 
                                                    0x16, 0x91, 0x8f, 0x03, 
                                                    0xf5, 0x3c, 0x52, 0xda, 
                                                    0xc5, 0x4e, 0xd8, 0x25, 

                                                    0x97, 0x40, 0x05, 0x1e, 
                                                    0x9c, 0x5f, 0xec, 0xf6, 
                                                    0x43, 0x44, 0xf7, 0xa8, 
                                                    0x22, 0x60, 0xed, 0xcc, 

                                                    0x30, 0x4c, 0x65, 0x28, 
                                                    0xf6, 0x59, 0xc7, 0x78, 
                                                    0x66, 0xa5, 0x10, 0xd9, 
                                                    0xc1, 0xd6, 0xae, 0x5e   
                                                   };   

    static uint8_t plain_text[sizeof(cipher_text)];
                                            
    AES_SW_ROUND_KEYS_128_BIT round_keys;
    BLOCK_CIPHER_SW_OFB_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[AES_SW_BLOCK_SIZE*4];
    uint32_t numPlainBytes;
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    AES_SW_RoundKeysCreate(     &round_keys,
                            (uint8_t*)AESKey128,
                            AES_SW_KEY_SIZE_128_BIT
                       );

	// Initialize the Block Cipher context
    BLOCK_CIPHER_SW_OFB_Initialize (handle, &context, AES_SW_Encrypt, AES_SW_Decrypt, AES_SW_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_SW_OFB_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Encrypt the data
    BLOCK_CIPHER_SW_OFB_Decrypt (handle, plain_text, &numPlainBytes, (void *) cipher_text, sizeof(cipher_text), BLOCK_CIPHER_SW_OPTION_STREAM_CONTINUE);

    //Now let's check the results
    {
        static uint8_t expected_result[] =      { 
                                                        0x6b, 0xc1, 0xbe, 0xe2, 
                                                        0x2e, 0x40, 0x9f, 0x96, 
                                                        0xe9, 0x3d, 0x7e, 0x11, 
                                                        0x73, 0x93, 0x17, 0x2a,
     
                                                        0xae, 0x2d, 0x8a, 0x57, 
                                                        0x1e, 0x03, 0xac, 0x9c, 
                                                        0x9e, 0xb7, 0x6f, 0xac, 
                                                        0x45, 0xaf, 0x8e, 0x51, 
    
                                                        0x30, 0xc8, 0x1c, 0x46, 
                                                        0xa3, 0x5c, 0xe4, 0x11, 
                                                        0xe5, 0xfb, 0xc1, 0x19, 
                                                        0x1a, 0x0a, 0x52, 0xef,
     
                                                        0xf6, 0x9f, 0x24, 0x45, 
                                                        0xdf, 0x4f, 0x9b, 0x17, 
                                                        0xad, 0x2b, 0x41, 0x7b, 
                                                        0xe6, 0x6c, 0x37, 0x10                        
                                                      };

        unsigned int i;

        for(i=0;i<sizeof(plain_text);i++)
        {
            if(plain_text[i] != expected_result[i])
            {
                //Error: results don't match what was expected
                while(1){};
            }
        }
    }
}

