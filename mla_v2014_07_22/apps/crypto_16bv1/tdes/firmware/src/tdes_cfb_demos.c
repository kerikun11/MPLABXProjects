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

#include <crypto_16bv1/crypto_16bv1.h>
#include <stdlib.h>
#include <string.h>

void TDES_CFBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void TDES_CFBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void TDESCFB_cfb8mmt3_encrypt_count1(BLOCK_CIPHER_HANDLE handle);
void TDESCFB_cfb8mmt3_decrypt_count1(BLOCK_CIPHER_HANDLE handle);

void TDESCFB_cfb1mmt3_encrypt_count1(BLOCK_CIPHER_HANDLE handle);
void TDESCFB_cfb1mmt3_decrypt_count1(BLOCK_CIPHER_HANDLE handle);

void TDES_CFB_Examples(BLOCK_CIPHER_HANDLE handle)
{
    TDES_CFBEncrypt_header_example1(handle);
    TDES_CFBDecrypt_header_example1(handle);

    TDESCFB_cfb8mmt3_encrypt_count1(handle);
    TDESCFB_cfb8mmt3_decrypt_count1(handle);

//    TDESCFB_cfb1mmt3_encrypt_count1(handle);
//    TDESCFB_cfb1mmt3_decrypt_count1(handle);
}

void TDES_CFBEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[encrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //COUNT = 1
    //KEY1 = fb7a9b894c04bc29
    //KEY2 = e96154a2a8755bfd
    //KEY3 = fb7a9b894c04bc29
    //IV = 2d50d7a19766d426
    //PLAINTEXT = 425c18b6992d6ca73c1f41677f0b9d34
    //CIPHERTEXT = 9561aa74545927336e9ed5ac8451cd5c
    unsigned char __attribute__((aligned)) TDESKey[] =
                                                  { 0xfb, 0x7a, 0x9b, 0x89, 0x4c, 0x04, 0xbc, 0x29,
                                                    0xe9, 0x61, 0x54, 0xa2, 0xa8, 0x75, 0x5b, 0xfd,
                                                    0xfb, 0x7a, 0x9b, 0x89, 0x4c, 0x04, 0xbc, 0x29
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0x2d, 0x50, 0xd7, 0xa1, 0x97, 0x66, 0xd4, 0x26
                                                  };

    unsigned char plain_text[]     =       { 0x42, 0x5c, 0x18, 0xb6, 0x99, 0x2d, 0x6c, 0xa7,
                                                    0x3c, 0x1f, 0x41, 0x67, 0x7f, 0x0b, 0x9d, 0x34
                                                  };

    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numCipherBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    unsigned char cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }
    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB_Encrypt (handle, cipher_text, &numCipherBytes, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START);

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
        static unsigned char expected_result[] =
                                                      { 0x95, 0x61, 0xaa, 0x74, 0x54, 0x59, 0x27, 0x33,
                                                        0x6e, 0x9e, 0xd5, 0xac, 0x84, 0x51, 0xcd, 0x5c
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


void TDES_CFBDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[decrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //COUNT = 1
    //KEY1 = 080440aef1c1fdef
    //KEY2 = 7ccdfeb5980bcbf8
    //KEY3 = 080440aef1c1fdef
    //IV = 1dce10f82ef0ebe6
    //CIPHERTEXT = f026a14f98b798a715e752e077d96fe7
    //PLAINTEXT = 0dcbfe9155e43df0868ced69766fa6da
    unsigned char __attribute__((aligned)) TDESKey[]        =
                                                  { 0x08, 0x04, 0x40, 0xae, 0xf1, 0xc1, 0xfd, 0xef,
                                                    0x7c, 0xcd, 0xfe, 0xb5, 0x98, 0x0b, 0xcb, 0xf8,
                                                    0x08, 0x04, 0x40, 0xae, 0xf1, 0xc1, 0xfd, 0xef
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0x1d, 0xce, 0x10, 0xf8, 0x2e, 0xf0, 0xeb, 0xe6
                                                  };

    unsigned char cipher_text[]    =       { 0xf0, 0x26, 0xa1, 0x4f, 0x98, 0xb7, 0x98, 0xa7,
                                                    0x15, 0xe7, 0x52, 0xe0, 0x77, 0xd9, 0x6f, 0xe7
                                                  };

    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numPlainBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    //unsigned char * plain_text       = (unsigned char*)malloc(sizeof(cipher_text));
    unsigned char plain_text[sizeof(cipher_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB_Decrypt (handle, plain_text, &numPlainBytes, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START);

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
        unsigned char expected_result[] =
                                                      { 0x0d, 0xcb, 0xfe, 0x91, 0x55, 0xe4, 0x3d, 0xf0,
                                                        0x86, 0x8c, 0xed, 0x69, 0x76, 0x6f, 0xa6, 0xda
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

void TDESCFB_cfb8mmt3_encrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[encrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //  COUNT = 1
    //  KEY1 = 0e86265407f71323
    //  KEY2 = 91c425087f29b36e
    //  KEY3 = c16768764a43b051
    //  IV = d7802ba95caac0f4
    //  PLAINTEXT = c2ad
    //  CIPHERTEXT = 02fc
    unsigned char __attribute__((aligned)) TDESKey[]        =
                                                  { 0x0e, 0x86, 0x26, 0x54, 0x07, 0xf7, 0x13, 0x23,
                                                    0x91, 0xc4, 0x25, 0x08, 0x7f, 0x29, 0xb3, 0x6e,
                                                    0xc1, 0x67, 0x68, 0x76, 0x4a, 0x43, 0xb0, 0x51
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0xd7, 0x80, 0x2b, 0xa9, 0x5c, 0xaa, 0xc0, 0xf4
                                                  };

    unsigned char plain_text[]     =       { 0xc2, 0xad
                                                  };

    BLOCK_CIPHER_16BV1_CFB8_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numCipherBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    unsigned char cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB8_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB8_Encrypt (handle, cipher_text, &numCipherBytes, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START);

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
        static unsigned char expected_result[] =
                                                      { 0x02, 0xfc
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


void TDESCFB_cfb8mmt3_decrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[decrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //    COUNT = 1
    //    KEY1 = da2ac7b94373ae08
    //    KEY2 = f43e52f17adf299d
    //    KEY3 = 19a8d65d8ce98552
    //    IV = a0a985fba6f0e287
    //    CIPHERTEXT = eed6
    //    PLAINTEXT = 1f38

    unsigned char __attribute__((aligned)) TDESKey[]        =
                                                  { 0xda, 0x2a, 0xc7, 0xb9, 0x43, 0x73, 0xae, 0x08,
                                                    0xf4, 0x3e, 0x52, 0xf1, 0x7a, 0xdf, 0x29, 0x9d,
                                                    0x19, 0xa8, 0xd6, 0x5d, 0x8c, 0xe9, 0x85, 0x52
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0xa0, 0xa9, 0x85, 0xfb, 0xa6, 0xf0, 0xe2, 0x87
                                                  };

    unsigned char cipher_text[]    =       { 0xee, 0xd6
                                                  };

    BLOCK_CIPHER_16BV1_CFB8_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numPlainBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    //unsigned char * plain_text       = (unsigned char*)malloc(sizeof(cipher_text));
    unsigned char plain_text[sizeof(cipher_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB8_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB8_Decrypt (handle, plain_text, &numPlainBytes, cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START);

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
        static unsigned char expected_result[] =
                                                      { 0x1f, 0x38
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

void TDESCFB_cfb1mmt3_encrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[encrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //  COUNT = 1
    //    KEY1 = 7c0eb07902f1f149
    //    KEY2 = 735e024c76d938ef
    //    KEY3 = ae83581686e99d29
    //    IV = 88e8ce3a0b0aa445
    //    PLAINTEXT = 00
    //    CIPHERTEXT = 11
    unsigned char __attribute__((aligned)) TDESKey[]        =
                                                  { 0x7c, 0x0e, 0xb0, 0x79, 0x02, 0xf1, 0xf1, 0x49,
                                                    0x73, 0x5e, 0x02, 0x4c, 0x76, 0xd9, 0x38, 0xef,
                                                    0xae, 0x83, 0x58, 0x16, 0x86, 0xe9, 0x9d, 0x29
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0x88, 0xe8, 0xce, 0x3a, 0x0b, 0x0a, 0xa4, 0x45
                                                  };

    unsigned char plain_text[]     =       { 0b00
                                                  };

    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numCipherBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    unsigned char cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CFB_Encrypt (handle, cipher_text, &numCipherBytes, (void *) plain_text, 2, BLOCK_CIPHER_OPTION_STREAM_START);

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
        static unsigned char expected_result[] =
                                                      { 0b11
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


void TDESCFB_cfb1mmt3_decrypt_count1(BLOCK_CIPHER_HANDLE handle)
{
    //This example comes from count=1[decrypt] of TCFB64MMT2.rsp from the Triple-DES
    //  Multiblock Message Test (MMT) sample vector files found on the NIST
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    //    COUNT = 1
    //    KEY1 = df645b0ea770436d
    //    KEY2 = 6d0d67da68ab166d
    //    KEY3 = 1f43c7204c4c2aa4
    //    IV = c81b538414f1dff2
    //    CIPHERTEXT = 01
    //    PLAINTEXT = 10

    unsigned char __attribute__((aligned)) TDESKey[]        =
                                                  { 0xdf, 0x64, 0x5b, 0x0e, 0xa7, 0x70, 0x43, 0x6d,
                                                    0x6d, 0x0d, 0x67, 0xda, 0x68, 0xab, 0x16, 0x6d,
                                                    0x1f, 0x43, 0xc7, 0x20, 0x4c, 0x4c, 0x2a, 0xa4
                                                  };

    unsigned char initialization_vector[] =
                                                  { 0xc8, 0x1b, 0x53, 0x84, 0x14, 0xf1, 0xdf, 0xf2
                                                  };

    unsigned char cipher_text[]    =       { 0b10
                                                  };
    BLOCK_CIPHER_16BV1_CFB_CONTEXT context;
    BLOCK_CIPHER_STATE state;
    uint32_t numPlainBytes;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    //unsigned char * plain_text       = (unsigned char*)malloc(sizeof(cipher_text));
    unsigned char plain_text[sizeof(cipher_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CFB_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, (uint8_t *)initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Decrypt the data
    BLOCK_CIPHER_16BV1_CFB_Decrypt (handle, plain_text, &numPlainBytes, cipher_text, 2, BLOCK_CIPHER_OPTION_STREAM_START);

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
        unsigned char expected_result[] =
                                                      { 0b01
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
