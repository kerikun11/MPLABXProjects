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

void AES_ECBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void AES_ECBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void AES_ECBEncrypt_192bit(BLOCK_CIPHER_HANDLE handle);
void AES_ECBDecrypt_192bit(BLOCK_CIPHER_HANDLE handle);

void AES_ECBEncrypt_256bit(BLOCK_CIPHER_HANDLE handle);
void AES_ECBDecrypt_256bit(BLOCK_CIPHER_HANDLE handle);

void AES_ECB_Examples(BLOCK_CIPHER_HANDLE handle)
{
    AES_ECBEncrypt_header_example1(handle);
    AES_ECBDecrypt_header_example1(handle);

    AES_ECBEncrypt_192bit(handle);
    AES_ECBDecrypt_192bit(handle);

    AES_ECBEncrypt_256bit(handle);
    AES_ECBDecrypt_256bit(handle);
}

void AES_ECBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.1.1 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t plain_text[]     =       { 0x6b, 0xc1, 0xbe, 0xe2, 
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

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey128[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x3a, 0xd7, 0x7b, 0xb4, 
                                                        0x0d, 0x7a, 0x36, 0x60, 
                                                        0xa8, 0x9e, 0xca, 0xf3, 
                                                        0x24, 0x66, 0xef, 0x97, 
                                                        0xf5, 0xd3, 0xd5, 0x85, 
                                                        0x03, 0xb9, 0x69, 0x9d, 
                                                        0xe7, 0x85, 0x89, 0x5a, 
                                                        0x96, 0xfd, 0xba, 0xaf, 
                                                        0x43, 0xb1, 0xcd, 0x7f, 
                                                        0x59, 0x8e, 0xce, 0x23, 
                                                        0x88, 0x1b, 0x00, 0xe3, 
                                                        0xed, 0x03, 0x06, 0x88, 
                                                        0x7b, 0x0c, 0x78, 0x5e, 
                                                        0x27, 0xe8, 0xad, 0x3f, 
                                                        0x82, 0x23, 0x20, 0x71, 
                                                        0x04, 0x72, 0x5d, 0xd4                          
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


void AES_ECBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.1.2 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t cipher_text[]    =       { 0x3a, 0xd7, 0x7b, 0xb4, 
                                                    0x0d, 0x7a, 0x36, 0x60, 
                                                    0xa8, 0x9e, 0xca, 0xf3, 
                                                    0x24, 0x66, 0xef, 0x97,
 
                                                    0xf5, 0xd3, 0xd5, 0x85, 
                                                    0x03, 0xb9, 0x69, 0x9d, 
                                                    0xe7, 0x85, 0x89, 0x5a, 
                                                    0x96, 0xfd, 0xba, 0xaf,
 
                                                    0x43, 0xb1, 0xcd, 0x7f, 
                                                    0x59, 0x8e, 0xce, 0x23, 
                                                    0x88, 0x1b, 0x00, 0xe3, 
                                                    0xed, 0x03, 0x06, 0x88,
 
                                                    0x7b, 0x0c, 0x78, 0x5e, 
                                                    0x27, 0xe8, 0xad, 0x3f, 
                                                    0x82, 0x23, 0x20, 0x71, 
                                                    0x04, 0x72, 0x5d, 0xd4                           
                                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey128[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_ECB_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x6b, 0xc1, 0xbe, 0xe2, 
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

        for(i=0;i<sizeof(cipher_text);i++)
        {
            if(plain_text[i] != expected_result[i])
            {
                //Error: results don't match what was expected
                while(1){};
            }
        }
    }
}

void AES_ECBEncrypt_192bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from ECBMMT192.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = c9c86a51224e5f1916d3f33a602f697afc852a2c44d30d5f
    //    PLAINTEXT = 64145e61e61cd96f796b187464fabbde6f42e693f501f1d73b3c606f00801506
    //    CIPHERTEXT = 502a73e4051cfac8fe6343211a129f5a5f56710c41b32c84da978dda2cec34ad
    static uint8_t AESKey192[]      =       { 0xc9, 0xc8, 0x6a, 0x51, 
                                                    0x22, 0x4e, 0x5f, 0x19, 
                                                    0x16, 0xd3, 0xf3, 0x3a, 
                                                    0x60, 0x2f, 0x69, 0x7a, 
                                                    0xfc, 0x85, 0x2a, 0x2c, 
                                                    0x44, 0xd3, 0x0d, 0x5f
                                                  };

    static uint8_t plain_text[]     =       { 0x64, 0x14, 0x5e, 0x61, 
                                                    0xe6, 0x1c, 0xd9, 0x6f, 
                                                    0x79, 0x6b, 0x18, 0x74, 
                                                    0x64, 0xfa, 0xbb, 0xde, 

                                                    0x6f, 0x42, 0xe6, 0x93, 
                                                    0xf5, 0x01, 0xf1, 0xd7, 
                                                    0x3b, 0x3c, 0x60, 0x6f, 
                                                    0x00, 0x80, 0x15, 0x06
                                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey192[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x50, 0x2a, 0x73, 0xe4, 
                                                        0x05, 0x1c, 0xfa, 0xc8, 
                                                        0xfe, 0x63, 0x43, 0x21, 
                                                        0x1a, 0x12, 0x9f, 0x5a, 

                                                        0x5f, 0x56, 0x71, 0x0c, 
                                                        0x41, 0xb3, 0x2c, 0x84, 
                                                        0xda, 0x97, 0x8d, 0xda, 
                                                        0x2c, 0xec, 0x34, 0xad                      
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


void AES_ECBDecrypt_192bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from ECBMMT192.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = 4bb83429faaaa25265f65c8ebb1caf815916810defe89281
    //    CIPHERTEXT = e741f38ed720877b53264ce81bdf2e5ea5b97163710ba29e9755cd3ba2caf091
    //    PLAINTEXT = 71b805feb56aaca22049073db10ad696751a4818b7005ae35eb3111cfeafcac8
    static uint8_t AESKey192[]      =       { 0x4b, 0xb8, 0x34, 0x29, 
                                                    0xfa, 0xaa, 0xa2, 0x52, 
                                                    0x65, 0xf6, 0x5c, 0x8e, 
                                                    0xbb, 0x1c, 0xaf, 0x81, 
                                                    0x59, 0x16, 0x81, 0x0d, 
                                                    0xef, 0xe8, 0x92, 0x81
                                                  };

    static uint8_t cipher_text[]    =       { 0xe7, 0x41, 0xf3, 0x8e, 
                                                    0xd7, 0x20, 0x87, 0x7b, 
                                                    0x53, 0x26, 0x4c, 0xe8, 
                                                    0x1b, 0xdf, 0x2e, 0x5e, 

                                                    0xa5, 0xb9, 0x71, 0x63, 
                                                    0x71, 0x0b, 0xa2, 0x9e, 
                                                    0x97, 0x55, 0xcd, 0x3b, 
                                                    0xa2, 0xca, 0xf0, 0x91                          
                                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey192[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);
    
    //Decrypt the data
    BLOCK_CIPHER_16BV1_ECB_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x71, 0xb8, 0x05, 0xfe, 
                                                        0xb5, 0x6a, 0xac, 0xa2, 
                                                        0x20, 0x49, 0x07, 0x3d, 
                                                        0xb1, 0x0a, 0xd6, 0x96, 

                                                        0x75, 0x1a, 0x48, 0x18, 
                                                        0xb7, 0x00, 0x5a, 0xe3, 
                                                        0x5e, 0xb3, 0x11, 0x1c, 
                                                        0xfe, 0xaf, 0xca, 0xc8
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
}

void AES_ECBEncrypt_256bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from ECBMMT256.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 4 (encrypt)
    //    KEY = ba42b760bb5a5de21acb9aba214c9783cd71ea841ada018580abc4e1be3b76dd
    //    PLAINTEXT = 4b4b12d6ee6fc0bf987eaafe2634aad464781ff4c83d3f8a61a6af7c0a6d51f0e3855d0e02feb307652a6f562bfebe4604baf1b4e7cdd01603f231bcf7a0c95645a141b704008cd8d62979201a4c84e2
    //    CIPHERTEXT = fa18d25e37ea0ce94f0949efc0edecc6a40fada8f007fd8e760afed0a83ebb350c82b03baaa6ee19f791bb9bd1b44d27a76fc6eb0e1c0017d68776ed69a541851a732e46ef328def064baf6a0a755588

    static uint8_t AESKey256[]      =       { 0xba, 0x42, 0xb7, 0x60, 
                                                    0xbb, 0x5a, 0x5d, 0xe2, 
                                                    0x1a, 0xcb, 0x9a, 0xba, 
                                                    0x21, 0x4c, 0x97, 0x83, 
                                                    0xcd, 0x71, 0xea, 0x84, 
                                                    0x1a, 0xda, 0x01, 0x85, 
                                                    0x80, 0xab, 0xc4, 0xe1, 
                                                    0xbe, 0x3b, 0x76, 0xdd
                                                  };

    static uint8_t plain_text[]     =       { 0x4b, 0x4b, 0x12, 0xd6, 
                                                    0xee, 0x6f, 0xc0, 0xbf, 
                                                    0x98, 0x7e, 0xaa, 0xfe, 
                                                    0x26, 0x34, 0xaa, 0xd4, 

                                                    0x64, 0x78, 0x1f, 0xf4, 
                                                    0xc8, 0x3d, 0x3f, 0x8a, 
                                                    0x61, 0xa6, 0xaf, 0x7c, 
                                                    0x0a, 0x6d, 0x51, 0xf0, 

                                                    0xe3, 0x85, 0x5d, 0x0e, 
                                                    0x02, 0xfe, 0xb3, 0x07, 
                                                    0x65, 0x2a, 0x6f, 0x56, 
                                                    0x2b, 0xfe, 0xbe, 0x46, 

                                                    0x04, 0xba, 0xf1, 0xb4, 
                                                    0xe7, 0xcd, 0xd0, 0x16, 
                                                    0x03, 0xf2, 0x31, 0xbc, 
                                                    0xf7, 0xa0, 0xc9, 0x56, 

                                                    0x45, 0xa1, 0x41, 0xb7, 
                                                    0x04, 0x00, 0x8c, 0xd8, 
                                                    0xd6, 0x29, 0x79, 0x20, 
                                                    0x1a, 0x4c, 0x84, 0xe2
                                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey256[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);
    
    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0xfa, 0x18, 0xd2, 0x5e, 
                                                        0x37, 0xea, 0x0c, 0xe9, 
                                                        0x4f, 0x09, 0x49, 0xef, 
                                                        0xc0, 0xed, 0xec, 0xc6, 

                                                        0xa4, 0x0f, 0xad, 0xa8, 
                                                        0xf0, 0x07, 0xfd, 0x8e, 
                                                        0x76, 0x0a, 0xfe, 0xd0, 
                                                        0xa8, 0x3e, 0xbb, 0x35, 

                                                        0x0c, 0x82, 0xb0, 0x3b, 
                                                        0xaa, 0xa6, 0xee, 0x19, 
                                                        0xf7, 0x91, 0xbb, 0x9b, 
                                                        0xd1, 0xb4, 0x4d, 0x27, 

                                                        0xa7, 0x6f, 0xc6, 0xeb, 
                                                        0x0e, 0x1c, 0x00, 0x17, 
                                                        0xd6, 0x87, 0x76, 0xed, 
                                                        0x69, 0xa5, 0x41, 0x85, 

                                                        0x1a, 0x73, 0x2e, 0x46, 
                                                        0xef, 0x32, 0x8d, 0xef, 
                                                        0x06, 0x4b, 0xaf, 0x6a, 
                                                        0x0a, 0x75, 0x55, 0x88                       
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


void AES_ECBDecrypt_256bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from ECBMMT256.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 4 (decrypt)
    //    KEY = dde079371133ebd68df061b56f0efd3a14c137ced35a30e0eb68422cb924dc3d
    //    CIPHERTEXT = ea1fd2f064548906ad10ce1240758868ed9fb32921dabe18681232a8308b955ad0d28e45c9f34af64bec1d7bfb626dbbf393cc090a8c64f8569b9870f008e801f7001578d8d286b0cc5eebaba2c920e1
    //    PLAINTEXT = 5889ad2c09a6307611e6115a78c13566de05b5892f7850fb917f83898e07486cc9ce746e891db102a0f570d7ad3c2804f40cdfe23bcc8b2c8a3bfba48632892d3df3bb7bbd1029b915cab2faf281c4e6

    static uint8_t AESKey256[]      =       { 0xdd, 0xe0, 0x79, 0x37, 
                                                    0x11, 0x33, 0xeb, 0xd6, 
                                                    0x8d, 0xf0, 0x61, 0xb5, 
                                                    0x6f, 0x0e, 0xfd, 0x3a, 
                                                    0x14, 0xc1, 0x37, 0xce, 
                                                    0xd3, 0x5a, 0x30, 0xe0, 
                                                    0xeb, 0x68, 0x42, 0x2c, 
                                                    0xb9, 0x24, 0xdc, 0x3d
                                                  };

    static uint8_t cipher_text[]    =       { 0xea, 0x1f, 0xd2, 0xf0, 
                                                    0x64, 0x54, 0x89, 0x06, 
                                                    0xad, 0x10, 0xce, 0x12, 
                                                    0x40, 0x75, 0x88, 0x68, 

                                                    0xed, 0x9f, 0xb3, 0x29, 
                                                    0x21, 0xda, 0xbe, 0x18, 
                                                    0x68, 0x12, 0x32, 0xa8, 
                                                    0x30, 0x8b, 0x95, 0x5a, 

                                                    0xd0, 0xd2, 0x8e, 0x45, 
                                                    0xc9, 0xf3, 0x4a, 0xf6, 
                                                    0x4b, 0xec, 0x1d, 0x7b, 
                                                    0xfb, 0x62, 0x6d, 0xbb, 

                                                    0xf3, 0x93, 0xcc, 0x09, 
                                                    0x0a, 0x8c, 0x64, 0xf8, 
                                                    0x56, 0x9b, 0x98, 0x70, 
                                                    0xf0, 0x08, 0xe8, 0x01, 

                                                    0xf7, 0x00, 0x15, 0x78, 
                                                    0xd8, 0xd2, 0x86, 0xb0, 
                                                    0xcc, 0x5e, 0xeb, 0xab, 
                                                    0xa2, 0xc9, 0x20, 0xe1                          
                                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey256[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);
    
    //Decrypt the data
    BLOCK_CIPHER_16BV1_ECB_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x58, 0x89, 0xad, 0x2c, 
                                                        0x09, 0xa6, 0x30, 0x76, 
                                                        0x11, 0xe6, 0x11, 0x5a, 
                                                        0x78, 0xc1, 0x35, 0x66, 

                                                        0xde, 0x05, 0xb5, 0x89, 
                                                        0x2f, 0x78, 0x50, 0xfb, 
                                                        0x91, 0x7f, 0x83, 0x89, 
                                                        0x8e, 0x07, 0x48, 0x6c, 

                                                        0xc9, 0xce, 0x74, 0x6e, 
                                                        0x89, 0x1d, 0xb1, 0x02, 
                                                        0xa0, 0xf5, 0x70, 0xd7, 
                                                        0xad, 0x3c, 0x28, 0x04, 

                                                        0xf4, 0x0c, 0xdf, 0xe2, 
                                                        0x3b, 0xcc, 0x8b, 0x2c, 
                                                        0x8a, 0x3b, 0xfb, 0xa4, 
                                                        0x86, 0x32, 0x89, 0x2d, 

                                                        0x3d, 0xf3, 0xbb, 0x7b, 
                                                        0xbd, 0x10, 0x29, 0xb9, 
                                                        0x15, 0xca, 0xb2, 0xfa, 
                                                        0xf2, 0x81, 0xc4, 0xe6
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
}
