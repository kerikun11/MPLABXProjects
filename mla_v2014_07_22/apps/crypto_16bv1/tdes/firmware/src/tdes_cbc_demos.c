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

void TDES_CBCEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle);
void TDES_CBCDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle);

void TDES_CBC_Examples(BLOCK_CIPHER_HANDLE handle)
{
    TDES_CBCEncrypt_header_example1(handle);
    TDES_CBCDecrypt_header_example1(handle);
}

void TDES_CBCEncrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from count=1 of TCBCMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    static unsigned char TDESKey[] = {  0x70, 0xa8, 0x8f, 0xa1, 0xdf, 0xb9, 0x94, 0x2f,
                                        0xa7, 0x7f, 0x40, 0x15, 0x7f, 0xfe, 0xf2, 0xad,
                                        0x70, 0xa8, 0x8f, 0xa1, 0xdf, 0xb9, 0x94, 0x2f
                                                  };

    static unsigned char initialization_vector[] = 
                                                  { 0xec, 0xe0, 0x8c, 0xe2, 
                                                    0xfd, 0xc6, 0xce, 0x80
                                                  };

    static unsigned char plain_text[]     =       { 0xbc, 0x22, 0x53, 0x04, 
                                                    0xd5, 0xa3, 0xa5, 0xc9, 
                                                    0x91, 0x8f, 0xc5, 0x00, 
                                                    0x6c, 0xbc, 0x40, 0xcc
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    unsigned long num_bytes_encrypted;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    unsigned char * cipher_text       = (unsigned char*)malloc(sizeof(plain_text));
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CBC_Encrypt (handle, cipher_text, &num_bytes_encrypted, (void *) plain_text, sizeof(plain_text), BLOCK_CIPHER_OPTION_STREAM_START | BLOCK_CIPHER_OPTION_STREAM_COMPLETE | BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x27, 0xf6, 0x7d, 0xc8, 
                                                        0x7a, 0xf7, 0xdd, 0xb4, 
                                                        0xb6, 0x8f, 0x63, 0xfa, 
                                                        0x7c, 0x2d, 0x45, 0x4a                         
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


void TDES_CBCDecrypt_header_example1(BLOCK_CIPHER_HANDLE handle)
{
    //Example variables.  The key and initialization vector information
    //  should be customized for the target application.

    //This example comes from count=1[decrypt] of TCBCMMT2.rsp from the Triple-DES 
    //  Multiblock Message Test (MMT) sample vector files found on the NIST 
    //  website (http://csrc.nist.gov/groups/STM/cavp/documents/des/tdesmmt.zip)
    static unsigned char TDESKey[] =  { 0x46, 0x40, 0x92, 0xcd, 0xbf, 0x73, 0x6d, 0x38,
                                        0xfb, 0x1f, 0xe6, 0xa1, 0x2a, 0x94, 0xae, 0x0e,
                                        0x46, 0x40, 0x92, 0xcd, 0xbf, 0x73, 0x6d, 0x38     
                                      };

    static unsigned char initialization_vector[] = 
                                                  { 0x54, 0x23, 0x45, 0x5f, 
                                                    0x00, 0x02, 0x3b, 0x01
                                                  };

    static unsigned char cipher_text[]    =       { 0x3f, 0x60, 0x50, 0xb7, 
                                                    0x4e, 0xd6, 0x44, 0x16, 
                                                    0xbc, 0x23, 0xd5, 0x3b, 
                                                    0x04, 0x69, 0xed, 0x7a                          
                                                  };

    BLOCK_CIPHER_16BV1_CBC_CONTEXT context;
    unsigned long num_bytes_decrypted;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.  In this example we will
    //  malloc a buffer the same size as the input since it is a fixed size.
    //  In a real example this buffer can be created statically and can be
    //  of any size as long as it is larger than TDES_BLOCK_SIZE
    unsigned char * plain_text       = (unsigned char*)malloc(sizeof(cipher_text));
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_CBC_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_TDES, CRYPTO_16BV1_ALGORITHM_TDES, TDES_BLOCK_SIZE, initialization_vector, &TDESKey[0], CRYPTO_KEY_SOFTWARE, CRYPTO_64DES_3_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_CBC_Decrypt (handle, plain_text, &num_bytes_decrypted, (void *) cipher_text, sizeof(cipher_text), BLOCK_CIPHER_OPTION_STREAM_START | BLOCK_CIPHER_OPTION_STREAM_COMPLETE | BLOCK_CIPHER_OPTION_PAD_NONE);

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
                                                      { 0x9c, 0xbe, 0x7d, 0x1b, 
                                                        0x5c, 0xdd, 0x18, 0x64, 
                                                        0xc3, 0x09, 0x5b, 0xa8, 
                                                        0x10, 0x57, 0x59, 0x60
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
