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
#include "crypto_16bv1/crypto_16bv1.h"
#include <stdlib.h>
#include <string.h>

void AES_CBCEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void AES_CBCDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void AES_CBCEncrypt_192bit(BLOCK_CIPHER_HANDLE handle);
void AES_CBCDecrypt_192bit(BLOCK_CIPHER_HANDLE handle);

void AES_CBCEncrypt_256bit(BLOCK_CIPHER_HANDLE handle);
void AES_CBCDecrypt_256bit(BLOCK_CIPHER_HANDLE handle);

void AES_CBC_Examples(BLOCK_CIPHER_HANDLE handle)
{
    AES_CBCEncrypt_header_example1(handle);
    AES_CBCDecrypt_header_example1(handle);

    AES_CBCEncrypt_192bit(handle);
    AES_CBCDecrypt_192bit(handle);

    AES_CBCEncrypt_256bit(handle);
    AES_CBCDecrypt_256bit(handle);
}

void AES_CBCEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.2.1 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16,
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0x00, 0x01, 0x02, 0x03, 
                                                    0x04, 0x05, 0x06, 0x07, 
                                                    0x08, 0x09, 0x0a, 0x0b, 
                                                    0x0c, 0x0d, 0x0e, 0x0f
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

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CBC_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x76, 0x49, 0xab, 0xac, 
                                                        0x81, 0x19, 0xb2, 0x46, 
                                                        0xce, 0xe9, 0x8e, 0x9b, 
                                                        0x12, 0xe9, 0x19, 0x7d, 
                                                        0x50, 0x86, 0xcb, 0x9b, 
                                                        0x50, 0x72, 0x19, 0xee, 
                                                        0x95, 0xdb, 0x11, 0x3a, 
                                                        0x91, 0x76, 0x78, 0xb2, 
                                                        0x73, 0xbe, 0xd6, 0xb8, 
                                                        0xe3, 0xc1, 0x74, 0x3b, 
                                                        0x71, 0x16, 0xe6, 0x9e, 
                                                        0x22, 0x22, 0x95, 0x16, 
                                                        0x3f, 0xf1, 0xca, 0xa1, 
                                                        0x68, 0x1f, 0xac, 0x09, 
                                                        0x12, 0x0e, 0xca, 0x30, 
                                                        0x75, 0x86, 0xe1, 0xa7                           
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


void AES_CBCDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.2.2 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16,
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0x00, 0x01, 0x02, 0x03, 
                                                    0x04, 0x05, 0x06, 0x07, 
                                                    0x08, 0x09, 0x0a, 0x0b, 
                                                    0x0c, 0x0d, 0x0e, 0x0f
                                                  };

    static uint8_t cipher_text[]    =       { 0x76, 0x49, 0xab, 0xac,
                                                    0x81, 0x19, 0xb2, 0x46, 
                                                    0xce, 0xe9, 0x8e, 0x9b, 
                                                    0x12, 0xe9, 0x19, 0x7d, 

                                                    0x50, 0x86, 0xcb, 0x9b, 
                                                    0x50, 0x72, 0x19, 0xee, 
                                                    0x95, 0xdb, 0x11, 0x3a, 
                                                    0x91, 0x76, 0x78, 0xb2, 

                                                    0x73, 0xbe, 0xd6, 0xb8, 
                                                    0xe3, 0xc1, 0x74, 0x3b, 
                                                    0x71, 0x16, 0xe6, 0x9e, 
                                                    0x22, 0x22, 0x95, 0x16, 

                                                    0x3f, 0xf1, 0xca, 0xa1, 
                                                    0x68, 0x1f, 0xac, 0x09, 
                                                    0x12, 0x0e, 0xca, 0x30, 
                                                    0x75, 0x86, 0xe1, 0xa7                           
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
        
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CBC_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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

void AES_CBCEncrypt_192bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from CBCMMT192.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = eab3b19c581aa873e1981c83ab8d83bbf8025111fb2e6b21
    //    IV = f3d6667e8d4d791e60f7505ba383eb05
    //    PLAINTEXT = 9d4e4cccd1682321856df069e3f1c6fa391a083a9fb02d59db74c14081b3acc4
    //    CIPHERTEXT = 51d44779f90d40a80048276c035cb49ca2a47bcb9b9cf7270b9144793787d53f
    static uint8_t AESKey192[]      =       { 0xea, 0xb3, 0xb1, 0x9c,
                                                    0x58, 0x1a, 0xa8, 0x73, 
                                                    0xe1, 0x98, 0x1c, 0x83, 
                                                    0xab, 0x8d, 0x83, 0xbb, 
                                                    0xf8, 0x02, 0x51, 0x11, 
                                                    0xfb, 0x2e, 0x6b, 0x21
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0xf3, 0xd6, 0x66, 0x7e, 
                                                    0x8d, 0x4d, 0x79, 0x1e, 
                                                    0x60, 0xf7, 0x50, 0x5b, 
                                                    0xa3, 0x83, 0xeb, 0x05
                                                  };

    static uint8_t plain_text[]     =       { 0x9d, 0x4e, 0x4c, 0xcc,
                                                    0xd1, 0x68, 0x23, 0x21, 
                                                    0x85, 0x6d, 0xf0, 0x69, 
                                                    0xe3, 0xf1, 0xc6, 0xfa, 

                                                    0x39, 0x1a, 0x08, 0x3a, 
                                                    0x9f, 0xb0, 0x2d, 0x59, 
                                                    0xdb, 0x74, 0xc1, 0x40, 
                                                    0x81, 0xb3, 0xac, 0xc4
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CBC_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x51, 0xd4, 0x47, 0x79, 
                                                        0xf9, 0x0d, 0x40, 0xa8, 
                                                        0x00, 0x48, 0x27, 0x6c, 
                                                        0x03, 0x5c, 0xb4, 0x9c, 

                                                        0xa2, 0xa4, 0x7b, 0xcb, 
                                                        0x9b, 0x9c, 0xf7, 0x27, 
                                                        0x0b, 0x91, 0x44, 0x79, 
                                                        0x37, 0x87, 0xd5, 0x3f                          
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


void AES_CBCDecrypt_192bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from CBCMMT192.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = 0ac0d2add273d1a260c432c662b4be4d8d366edc3f402e40
    //    IV = 0cc3744fa9cef13fe04a5ab6ac9b8de4
    //    CIPHERTEXT = 2cd57dce7465d5ecde153e87ce45e62286c6b023a446dae3ec0fdc0648f29308
    //    PLAINTEXT = 854e97e19b5c4fbd7a2ac7f8ddccdc8eac1a166832b58f05ae5088d7caba8fee
    static uint8_t AESKey192[]      =       { 0x0a, 0xc0, 0xd2, 0xad,
                                                    0xd2, 0x73, 0xd1, 0xa2, 
                                                    0x60, 0xc4, 0x32, 0xc6, 
                                                    0x62, 0xb4, 0xbe, 0x4d, 
                                                    0x8d, 0x36, 0x6e, 0xdc, 
                                                    0x3f, 0x40, 0x2e, 0x40
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0x0c, 0xc3, 0x74, 0x4f, 
                                                    0xa9, 0xce, 0xf1, 0x3f, 
                                                    0xe0, 0x4a, 0x5a, 0xb6, 
                                                    0xac, 0x9b, 0x8d, 0xe4
                                                  };

    static uint8_t cipher_text[]    =       { 0x2c, 0xd5, 0x7d, 0xce,
                                                    0x74, 0x65, 0xd5, 0xec, 
                                                    0xde, 0x15, 0x3e, 0x87, 
                                                    0xce, 0x45, 0xe6, 0x22, 

                                                    0x86, 0xc6, 0xb0, 0x23, 
                                                    0xa4, 0x46, 0xda, 0xe3, 
                                                    0xec, 0x0f, 0xdc, 0x06, 
                                                    0x48, 0xf2, 0x93, 0x08                          
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CBC_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x85, 0x4e, 0x97, 0xe1, 
                                                        0x9b, 0x5c, 0x4f, 0xbd, 
                                                        0x7a, 0x2a, 0xc7, 0xf8, 
                                                        0xdd, 0xcc, 0xdc, 0x8e, 

                                                        0xac, 0x1a, 0x16, 0x68, 
                                                        0x32, 0xb5, 0x8f, 0x05, 
                                                        0xae, 0x50, 0x88, 0xd7, 
                                                        0xca, 0xba, 0x8f, 0xee
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

void AES_CBCEncrypt_256bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from CBCMMT256.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = dce26c6b4cfb286510da4eecd2cffe6cdf430f33db9b5f77b460679bd49d13ae
    //    IV = fdeaa134c8d7379d457175fd1a57d3fc
    //    PLAINTEXT = 50e9eee1ac528009e8cbcd356975881f957254b13f91d7c6662d10312052eb00
    //    CIPHERTEXT = 2fa0df722a9fd3b64cb18fb2b3db55ff2267422757289413f8f657507412a64c
    static uint8_t AESKey256[]      =       { 0xdc, 0xe2, 0x6c, 0x6b,
                                                    0x4c, 0xfb, 0x28, 0x65, 
                                                    0x10, 0xda, 0x4e, 0xec, 
                                                    0xd2, 0xcf, 0xfe, 0x6c, 
                                                    0xdf, 0x43, 0x0f, 0x33, 
                                                    0xdb, 0x9b, 0x5f, 0x77, 
                                                    0xb4, 0x60, 0x67, 0x9b, 
                                                    0xd4, 0x9d, 0x13, 0xae
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0xfd, 0xea, 0xa1, 0x34, 
                                                    0xc8, 0xd7, 0x37, 0x9d, 
                                                    0x45, 0x71, 0x75, 0xfd, 
                                                    0x1a, 0x57, 0xd3, 0xfc
                                                  };

    static uint8_t plain_text[]     =       { 0x50, 0xe9, 0xee, 0xe1,
                                                    0xac, 0x52, 0x80, 0x09, 
                                                    0xe8, 0xcb, 0xcd, 0x35, 
                                                    0x69, 0x75, 0x88, 0x1f, 

                                                    0x95, 0x72, 0x54, 0xb1, 
                                                    0x3f, 0x91, 0xd7, 0xc6, 
                                                    0x66, 0x2d, 0x10, 0x31, 
                                                    0x20, 0x52, 0xeb, 0x00
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CBC_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x2f, 0xa0, 0xdf, 0x72, 
                                                        0x2a, 0x9f, 0xd3, 0xb6, 
                                                        0x4c, 0xb1, 0x8f, 0xb2, 
                                                        0xb3, 0xdb, 0x55, 0xff, 

                                                        0x22, 0x67, 0x42, 0x27, 
                                                        0x57, 0x28, 0x94, 0x13, 
                                                        0xf8, 0xf6, 0x57, 0x50, 
                                                        0x74, 0x12, 0xa6, 0x4c                         
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


void AES_CBCDecrypt_256bit(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from CBCMMT256.rsp of the MMT KAT files available
    //  the NIST website: 
    //  http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesmmt.zip
    //    COUNT = 1
    //    KEY = addf88c1ab997eb58c0455288c3a4fa320ada8c18a69cc90aa99c73b174dfde6
    //    IV = 60cc50e0887532e0d4f3d2f20c3c5d58
    //    CIPHERTEXT = 6cb4e2f4ddf79a8e08c96c7f4040e8a83266c07fc88dd0074ee25b00d445985a
    //    PLAINTEXT = 98a8a9d84356bf403a9ccc384a06fe043dfeecb89e59ce0cb8bd0a495ef76cf0
    static uint8_t AESKey256[]      =       { 0xad, 0xdf, 0x88, 0xc1,
                                                    0xab, 0x99, 0x7e, 0xb5, 
                                                    0x8c, 0x04, 0x55, 0x28, 
                                                    0x8c, 0x3a, 0x4f, 0xa3, 
                                                    0x20, 0xad, 0xa8, 0xc1, 
                                                    0x8a, 0x69, 0xcc, 0x90, 
                                                    0xaa, 0x99, 0xc7, 0x3b, 
                                                    0x17, 0x4d, 0xfd, 0xe6
                                                  };

    static uint8_t initialization_vector[] =
                                                  { 0x60, 0xcc, 0x50, 0xe0, 
                                                    0x88, 0x75, 0x32, 0xe0, 
                                                    0xd4, 0xf3, 0xd2, 0xf2, 
                                                    0x0c, 0x3c, 0x5d, 0x58
                                                  };

    static uint8_t cipher_text[]    =       { 0x6c, 0xb4, 0xe2, 0xf4,
                                                    0xdd, 0xf7, 0x9a, 0x8e, 
                                                    0x08, 0xc9, 0x6c, 0x7f, 
                                                    0x40, 0x40, 0xe8, 0xa8, 

                                                    0x32, 0x66, 0xc0, 0x7f, 
                                                    0xc8, 0x8d, 0xd0, 0x07, 
                                                    0x4e, 0xe2, 0x5b, 0x00, 
                                                    0xd4, 0x45, 0x98, 0x5a                         
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CBC_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x98, 0xa8, 0xa9, 0xd8, 
                                                        0x43, 0x56, 0xbf, 0x40, 
                                                        0x3a, 0x9c, 0xcc, 0x38, 
                                                        0x4a, 0x06, 0xfe, 0x04, 

                                                        0x3d, 0xfe, 0xec, 0xb8, 
                                                        0x9e, 0x59, 0xce, 0x0c, 
                                                        0xb8, 0xbd, 0x0a, 0x49, 
                                                        0x5e, 0xf7, 0x6c, 0xf0
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


