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

void TDES_SW_OFBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);
void TDES_SW_OFBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle);

void TDES_SW_OFB_Examples(BLOCK_CIPHER_SW_HANDLE handle)
{
    TDES_SW_OFBEncrypt_header_example1(handle);
    TDES_SW_OFBDecrypt_header_example1(handle);
}

void TDES_SW_OFBEncrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //This example comes from count=1[encrypt] of TOFBMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //COUNT = 1
    //KEY1 = 378c89d3b0917080
    //KEY2 = 2af18013c2ef6210
    //KEY3 = 378c89d3b0917080
    //IV = 007817d4bbdc69a1
    //PLAINTEXT = 168260d5faed24b9f73aae088a477528
    //CIPHERTEXT = cfd4e0fadf100f3aa5eec0b30084df47
    static const uint8_t TDESKey[]                = { 0x37, 0x8c, 0x89, 0xd3, 0xb0, 0x91, 0x70, 0x80,
                                                    0x2a, 0xf1, 0x80, 0x13, 0xc2, 0xef, 0x62, 0x10,
                                                    0x37, 0x8c, 0x89, 0xd3, 0xb0, 0x91, 0x70, 0x80
                                                  };

    static const uint8_t initial_data[]           = { 0x00, 0x78, 0x17, 0xd4, 0xbb, 0xdc, 0x69, 0xa1
                                                  };

    static const uint8_t plain_text[]             = { 0x16, 0x82, 0x60, 0xd5, 0xfa, 0xed, 0x24, 0xb9,
                                                    0xf7, 0x3a, 0xae, 0x08, 0x8a, 0x47, 0x75, 0x28
                                                   };   

    static uint8_t cipher_text[sizeof(plain_text)];
                                            
    TDES_SW_ROUND_KEYS round_keys;
    BLOCK_CIPHER_SW_OFB_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[TDES_SW_BLOCK_SIZE*4];
    uint32_t numCipherBytes;
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    TDES_SW_RoundKeysCreate(     &round_keys,
                            (unsigned char*)TDESKey
                       );

    // Initialize the Block Cipher context
    BLOCK_CIPHER_SW_OFB_Initialize (handle, &context, TDES_SW_Encrypt, TDES_SW_Decrypt, TDES_SW_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_SW_OFB_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Encrypt the data
    BLOCK_CIPHER_SW_OFB_Encrypt (handle, cipher_text, &numCipherBytes, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_SW_OPTION_STREAM_CONTINUE);

    //Now let's check the results
    {
        static unsigned char expected_result[] = 
                                                      { 0xcf, 0xd4, 0xe0, 0xfa, 0xdf, 0x10, 0x0f, 0x3a, 
                                                        0xa5, 0xee, 0xc0, 0xb3, 0x00, 0x84, 0xdf, 0x47                        
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

void TDES_SW_OFBDecrypt_header_example1(BLOCK_CIPHER_SW_HANDLE handle)
{
    //This example comes from count=1[decrypt] of TOFBMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //COUNT = 1
    //KEY1 = 8c83f7045bc76267
    //KEY2 = 70b9fd0bc88567a7
    //KEY3 = 8c83f7045bc76267
    //IV = e4149e9fec84f2f7
    //CIPHERTEXT = 1d08eef994bfba036aa60f28cd40312b
    //PLAINTEXT = 62e629f4640d290ff9c382353513682c
    static const uint8_t TDESKey[]                = { 0x8c, 0x83, 0xf7, 0x04, 0x5b, 0xc7, 0x62, 0x67,
                                                    0x70, 0xb9, 0xfd, 0x0b, 0xc8, 0x85, 0x67, 0xa7,
                                                    0x8c, 0x83, 0xf7, 0x04, 0x5b, 0xc7, 0x62, 0x67
                                                  };

    static const uint8_t initial_data[]           = { 0xe4, 0x14, 0x9e, 0x9f, 0xec, 0x84, 0xf2, 0xf7
                                                  };

    static const uint8_t cipher_text[]             = { 
                                                    0x1d, 0x08, 0xee, 0xf9, 0x94, 0xbf, 0xba, 0x03,
                                                    0x6a, 0xa6, 0x0f, 0x28, 0xcd, 0x40, 0x31, 0x2b   
                                                   };   

    static uint8_t plain_text[sizeof(cipher_text)];
                                            
    TDES_SW_ROUND_KEYS round_keys;
    BLOCK_CIPHER_SW_OFB_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[TDES_SW_BLOCK_SIZE*4];
    uint32_t numPlainBytes;
    
    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    TDES_SW_RoundKeysCreate(     &round_keys,
                            (unsigned char*)TDESKey
                       );

    // Initialize the Block Cipher context
    BLOCK_CIPHER_SW_OFB_Initialize (handle, &context, TDES_SW_Encrypt, TDES_SW_Decrypt, TDES_SW_BLOCK_SIZE, (uint8_t *)initial_data, (void *)&keyStream, sizeof (keyStream), &round_keys, CRYPTO_SW_KEY_SOFTWARE_EXPANDED);

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_SW_OFB_KeyStreamGenerate(handle, 4, BLOCK_CIPHER_SW_OPTION_STREAM_START);

    //Encrypt the data
    BLOCK_CIPHER_SW_OFB_Decrypt (handle, plain_text, &numPlainBytes, (void *) cipher_text, sizeof(cipher_text), BLOCK_CIPHER_SW_OPTION_STREAM_CONTINUE);

    //Now let's check the results
    {
        static unsigned char expected_result[] =      { 
                                                        0x62, 0xe6, 0x29, 0xf4, 0x64, 0x0d, 0x29, 0x0f, 
                                                        0xf9, 0xc3, 0x82, 0x35, 0x35, 0x13, 0x68, 0x2c                      
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

