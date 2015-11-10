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

void AES_CFBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void AES_CFBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void AES_CFBEncrypt_cfb8mmt_encrypt_count1(BLOCK_CIPHER_HANDLE handle);
void AES_CFBEncrypt_cfb8mmt_decrypt_count1(BLOCK_CIPHER_HANDLE handle);

void AES_CFBEncrypt_cfb128mmt_encrypt_count1(BLOCK_CIPHER_HANDLE handle);
void AES_CFBEncrypt_cfb128mmt_decrypt_count1(BLOCK_CIPHER_HANDLE handle);

void AES_CFB_Examples(BLOCK_CIPHER_HANDLE handle)
{
    AES_CFBEncrypt_header_example1(handle);
    AES_CFBDecrypt_header_example1(handle);

    AES_CFBEncrypt_cfb8mmt_encrypt_count1(handle);
    AES_CFBEncrypt_cfb8mmt_decrypt_count1(handle);

    AES_CFBEncrypt_cfb128mmt_encrypt_count1(handle);
    AES_CFBEncrypt_cfb128mmt_decrypt_count1(handle);
}


void AES_CFBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.3.1 of the 
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

    static uint8_t plain_text[]     =       { 0b11010110, 0b10000011
                                                  };

    BLOCK_CIPHER_16BV1_CFB1_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB1_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB1_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0b00010110, 0b11001101                        
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


void AES_CFBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from Appendix F.3.2 of the 
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

    static uint8_t cipher_text[]    =       { 0b00010110, 0b11001101
                                                  };

    BLOCK_CIPHER_16BV1_CFB1_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB1_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB1_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0b11010110, 0b10000011
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

void AES_CFBEncrypt_cfb8mmt_encrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example is from the KAT CFB8MMT128.rsp file, encrypt count 1
    //  KEY = 0d8f3dc3edee60db658bb97faf46fba3
    //  IV = e481fdc42e606b96a383c0a1a5520ebb
    //  PLAINTEXT = aacd
    //  CIPHERTEXT = 5066

    static uint8_t AESKey128[]      =       { 0x0d, 0x8f, 0x3d, 0xc3, 
                                                    0xed, 0xee, 0x60, 0xdb, 
                                                    0x65, 0x8b, 0xb9, 0x7f, 
                                                    0xaf, 0x46, 0xfb, 0xa3
                                                  };

    static uint8_t initialization_vector[] = 
                                                  { 0xe4, 0x81, 0xfd, 0xc4, 
                                                    0x2e, 0x60, 0x6b, 0x96, 
                                                    0xa3, 0x83, 0xc0, 0xa1, 
                                                    0xa5, 0x52, 0x0e, 0xbb
                                                  };

    static uint8_t plain_text[]     =       { 0xaa, 0xcd
                                                  };

    BLOCK_CIPHER_16BV1_CFB8_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB8_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB8_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x50, 0x66
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


void AES_CFBEncrypt_cfb8mmt_decrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example is from the KAT CFB8MMT128.rsp file, decrypt count 1
    //  KEY = 38cf776750162edc63c3b5dbe311ab9f
    //  IV = 98fbbd288872c40f1926b16ecaec1561
    //  CIPHERTEXT = 4878
    //  PLAINTEXT = eb24
    static uint8_t AESKey128[]      =       { 0x38, 0xcf, 0x77, 0x67, 
                                                    0x50, 0x16, 0x2e, 0xdc, 
                                                    0x63, 0xc3, 0xb5, 0xdb, 
                                                    0xe3, 0x11, 0xab, 0x9f
                                                  };

    static uint8_t initialization_vector[] = 
                                                  { 0x98, 0xfb, 0xbd, 0x28, 
                                                    0x88, 0x72, 0xc4, 0x0f, 
                                                    0x19, 0x26, 0xb1, 0x6e, 
                                                    0xca, 0xec, 0x15, 0x61
                                                  };

    static uint8_t cipher_text[]    =       { 0x48, 0x78
                                                  };

    BLOCK_CIPHER_16BV1_CFB8_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB8_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB8_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0xeb, 0x24
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

void AES_CFBEncrypt_cfb128mmt_encrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example is from the KAT CFB128MMT128.rsp file, encrypt count 1
    //  KEY = 701ccc4c0e36e512ce077f5af6ccb957
    //  IV = 5337ddeaf89a00dd4d58d860de968469
    //  PLAINTEXT = cc1172f2f80866d0768b25f70fcf6361aab7c627c8488f97525d7d88949beeea
    //  CIPHERTEXT = cdcf093bb7840df225683b58a479b00d5de5553a7e85eae4b70bf46dc729dd31
    static uint8_t AESKey128[]      =       { 0x70, 0x1c, 0xcc, 0x4c, 
                                                    0x0e, 0x36, 0xe5, 0x12, 
                                                    0xce, 0x07, 0x7f, 0x5a, 
                                                    0xf6, 0xcc, 0xb9, 0x57
                                                  };

    static uint8_t initialization_vector[] = 
                                                  { 0x53, 0x37, 0xdd, 0xea, 
                                                    0xf8, 0x9a, 0x00, 0xdd, 
                                                    0x4d, 0x58, 0xd8, 0x60, 
                                                    0xde, 0x96, 0x84, 0x69
                                                  };

    static uint8_t plain_text[]     =       { 0xcc, 0x11, 0x72, 0xf2, 
                                                    0xf8, 0x08, 0x66, 0xd0, 
                                                    0x76, 0x8b, 0x25, 0xf7, 
                                                    0x0f, 0xcf, 0x63, 0x61,
 
                                                    0xaa, 0xb7, 0xc6, 0x27, 
                                                    0xc8, 0x48, 0x8f, 0x97, 
                                                    0x52, 0x5d, 0x7d, 0x88, 
                                                    0x94, 0x9b, 0xee, 0xea
                                                  };

    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];
       
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0xcd, 0xcf, 0x09, 0x3b, 
                                                        0xb7, 0x84, 0x0d, 0xf2, 
                                                        0x25, 0x68, 0x3b, 0x58, 
                                                        0xa4, 0x79, 0xb0, 0x0d, 

                                                        0x5d, 0xe5, 0x55, 0x3a, 
                                                        0x7e, 0x85, 0xea, 0xe4, 
                                                        0xb7, 0x0b, 0xf4, 0x6d, 
                                                        0xc7, 0x29, 0xdd, 0x31
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


void AES_CFBEncrypt_cfb128mmt_decrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example is from the KAT CFB128MMT128.rsp file, decrypt count 1
    //  KEY = c4666081e0b0eddb10a9a607c807378f
    //  IV = 5f23623288e4a41b03186024755a10ea
    //  CIPHERTEXT = 7138c2b69191cf88702f7d25e9170dd6effdb80416b44f4d54e81fd7090f17e4
    //  PLAINTEXT = 2fd02dab9054248073ebc0b07aed383756ccfa4fa6298722775be6a9b4ed27a5
    static uint8_t AESKey128[]      =       { 0xc4, 0x66, 0x60, 0x81, 
                                                    0xe0, 0xb0, 0xed, 0xdb, 
                                                    0x10, 0xa9, 0xa6, 0x07, 
                                                    0xc8, 0x07, 0x37, 0x8f
                                                  };

    static uint8_t initialization_vector[] = 
                                                  { 0x5f, 0x23, 0x62, 0x32, 
                                                    0x88, 0xe4, 0xa4, 0x1b, 
                                                    0x03, 0x18, 0x60, 0x24, 
                                                    0x75, 0x5a, 0x10, 0xea
                                                  };

    static uint8_t cipher_text[]    =       { 0x71, 0x38, 0xc2, 0xb6, 
                                                    0x91, 0x91, 0xcf, 0x88, 
                                                    0x70, 0x2f, 0x7d, 0x25, 
                                                    0xe9, 0x17, 0x0d, 0xd6,
 
                                                    0xef, 0xfd, 0xb8, 0x04, 
                                                    0x16, 0xb4, 0x4f, 0x4d, 
                                                    0x54, 0xe8, 0x1f, 0xd7, 
                                                    0x09, 0x0f, 0x17, 0xe4
                                                  };

    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    uint32_t num_bytes_decrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text[sizeof(cipher_text)];
        
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, initialization_vector, AESKey128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB_Decrypt (handle, plain_text, &num_bytes_decrypted, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

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
                                                      { 0x2f, 0xd0, 0x2d, 0xab, 
                                                        0x90, 0x54, 0x24, 0x80, 
                                                        0x73, 0xeb, 0xc0, 0xb0, 
                                                        0x7a, 0xed, 0x38, 0x37,
                                                         
                                                        0x56, 0xcc, 0xfa, 0x4f, 
                                                        0xa6, 0x29, 0x87, 0x22, 
                                                        0x77, 0x5b, 0xe6, 0xa9, 
                                                        0xb4, 0xed, 0x27, 0xa5
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


