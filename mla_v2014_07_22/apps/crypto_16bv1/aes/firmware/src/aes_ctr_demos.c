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

#include <xc.h>
#include <crypto_16bv1/crypto_16bv1.h>
#include <stdlib.h>
#include <string.h>

static uint32_t byteCount;

void AES_CTREncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void AES_CTRDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void AES_CTR_Examples(BLOCK_CIPHER_HANDLE handle)
{
    AES_CTREncrypt_header_example1(handle);
    AES_CTRDecrypt_header_example1(handle);
}

void AES_CTREncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //This example is taken from appendix F.5.1 of SP800-38a.
    //  http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.
    static const uint8_t AESKey128[]              = { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static const uint8_t initial_data[]           = { 0xf0, 0xf1, 0xf2, 0xf3, 
                                                    0xf4, 0xf5, 0xf6, 0xf7, 
                                                    0xf8, 0xf9, 0xfa, 0xfb, 
                                                    0xfc, 0xfd, 0xfe, 0xff
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
                                            
    BLOCK_CIPHER_16BV1_CTR_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[AES_BLOCK_SIZE*4];
    BLOCK_CIPHER_STATE state;
    
	// Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CTR_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_CTR_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_OPTION_STREAM_START);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CTR_Encrypt (handle, cipher_text, &byteCount, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_CONTINUE);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Now let's check the results
    {
        static uint8_t expected_result[] = 
                                                      { 0x87, 0x4d, 0x61, 0x91, 
                                                        0xb6, 0x20, 0xe3, 0x26, 
                                                        0x1b, 0xef, 0x68, 0x64, 
                                                        0x99, 0x0d, 0xb6, 0xce,

                                                        0x98, 0x06, 0xf6, 0x6b, 
                                                        0x79, 0x70, 0xfd, 0xff, 
                                                        0x86, 0x17, 0x18, 0x7b, 
                                                        0xb9, 0xff, 0xfd, 0xff, 

                                                        0x5a, 0xe4, 0xdf, 0x3e, 
                                                        0xdb, 0xd5, 0xd3, 0x5e, 
                                                        0x5b, 0x4f, 0x09, 0x02, 
                                                        0x0d, 0xb0, 0x3e, 0xab,
 
                                                        0x1e, 0x03, 0x1d, 0xda, 
                                                        0x2f, 0xbe, 0x03, 0xd1, 
                                                        0x79, 0x21, 0x70, 0xa0, 
                                                        0xf3, 0x00, 0x9c, 0xee                          
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

void AES_CTRDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //This example is taken from appendix F.5.2 of SP800-38a.
    //  http://csrc.nist.gov/publications/nistpubs/800-38a/sp800-38a.pdf
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.
    static const uint8_t AESKey128[]              = { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static const uint8_t initial_data[]           = { 0xf0, 0xf1, 0xf2, 0xf3, 
                                                    0xf4, 0xf5, 0xf6, 0xf7, 
                                                    0xf8, 0xf9, 0xfa, 0xfb, 
                                                    0xfc, 0xfd, 0xfe, 0xff
                                                  };

    static const uint8_t cipher_text[]             = { 
                                                    0x87, 0x4d, 0x61, 0x91, 
                                                    0xb6, 0x20, 0xe3, 0x26, 
                                                    0x1b, 0xef, 0x68, 0x64, 
                                                    0x99, 0x0d, 0xb6, 0xce,
                                                    
                                                    0x98, 0x06, 0xf6, 0x6b, 
                                                    0x79, 0x70, 0xfd, 0xff, 
                                                    0x86, 0x17, 0x18, 0x7b, 
                                                    0xb9, 0xff, 0xfd, 0xff, 
                                                    
                                                    0x5a, 0xe4, 0xdf, 0x3e, 
                                                    0xdb, 0xd5, 0xd3, 0x5e, 
                                                    0x5b, 0x4f, 0x09, 0x02, 
                                                    0x0d, 0xb0, 0x3e, 0xab,
                                                    
                                                    0x1e, 0x03, 0x1d, 0xda, 
                                                    0x2f, 0xbe, 0x03, 0xd1, 
                                                    0x79, 0x21, 0x70, 0xa0, 
                                                    0xf3, 0x00, 0x9c, 0xee  
                                                   };   

    static uint8_t plain_text[sizeof(cipher_text)];

    BLOCK_CIPHER_16BV1_CTR_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[AES_BLOCK_SIZE*4];
    BLOCK_CIPHER_STATE state;
    
	// Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CTR_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_CTR_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_OPTION_STREAM_START);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CTR_Decrypt (handle, plain_text, &byteCount, (void *) cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_CONTINUE);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

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

