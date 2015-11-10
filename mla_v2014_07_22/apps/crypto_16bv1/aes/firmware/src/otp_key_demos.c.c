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
#include <stdint.h>
#include <crypto_16bv1/crypto_16bv1.h>
#include <string.h>

extern void CRYPTO_OTP_WriteStart(void);

uint8_t DEMO_OTP_AES128KeyProgram(void);
void DEMO_OTP_AES128Key1Test(BLOCK_CIPHER_HANDLE handle);
void DEMO_OTP_AES128Key2Test(BLOCK_CIPHER_HANDLE handle);
void DEMO_OTP_AES128Key3Test(BLOCK_CIPHER_HANDLE handle);
void DEMO_OTP_AES128Key4Test(BLOCK_CIPHER_HANDLE handle);

void AES_OTP_Examples(BLOCK_CIPHER_HANDLE handle)
{
    uint8_t error;

    error = DEMO_OTP_AES128KeyProgram();
    if(error != 0)
    {
        /* There was an error in the key programming */
        while(1){}
    }

    DEMO_OTP_AES128Key1Test(handle);
    DEMO_OTP_AES128Key2Test(handle);
    DEMO_OTP_AES128Key3Test(handle);
    DEMO_OTP_AES128Key4Test(handle);
}


/* Select 4 different keys */
static uint8_t key1[] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F
};

static uint8_t key2[] = {
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B,
    0x1C, 0x1D, 0x1E, 0x1F
};

static uint8_t key3[] = {
    0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B,
    0x2C, 0x2D, 0x2E, 0x2F
};

static uint8_t key4[] = {
    0x30, 0x31, 0x32, 0x33,
    0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0x3E, 0x3F
};

uint8_t DEMO_OTP_AES128KeyProgram(void)
{
    //Turn module on
    CRYCONLbits.CRYON = 0b1;

    /************************************************************
     * Program Key 1
     ***********************************************************/
    //Clear all registers
    CRYCONH = 0;
    CRYSTAT = 0;
    CRYOTP = 0;

    //point to page 1
    CRYOTPbits.KEYPG = 1;

    memcpy((void*)&CRYTXTC0, &key1[0], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    //point to page 2
    CRYOTPbits.KEYPG = 2;

    memcpy((void*)&CRYTXTC0, &key1[8], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    /************************************************************
     * Program Key 2
     ***********************************************************/
    //Clear all registers
    CRYCONH = 0;
    CRYSTAT = 0;
    CRYOTP = 0;

    //point to page 3
    CRYOTPbits.KEYPG = 3;

    memcpy((void*)&CRYTXTC0, &key2[0], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    //point to page 4
    CRYOTPbits.KEYPG = 4;

    memcpy((void*)&CRYTXTC0, &key2[8], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    /************************************************************
     * Program Key 3
     ***********************************************************/
    //Clear all registers
    CRYCONH = 0;
    CRYSTAT = 0;
    CRYOTP = 0;

    //point to page 5
    CRYOTPbits.KEYPG = 5;

    memcpy((void*)&CRYTXTC0, &key3[0], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    //point to page 6
    CRYOTPbits.KEYPG = 6;

    memcpy((void*)&CRYTXTC0, &key3[8], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    /************************************************************
     * Program Key 4
     ***********************************************************/
    //Clear all registers
    CRYCONH = 0;
    CRYSTAT = 0;
    CRYOTP = 0;

    //point to page 7
    CRYOTPbits.KEYPG = 7;

    memcpy((void*)&CRYTXTC0, &key4[0], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    //point to page 8
    CRYOTPbits.KEYPG = 8;

    memcpy((void*)&CRYTXTC0, &key4[8], 8);

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    //Clear all registers
    CRYCONH = 0;
    CRYSTAT = 0;
    CRYOTP = 0;

    /* Enable 128-bit AES for all pages and lock all pages for modification.
     * 
     *                     Reserved
     *                     |TSTPGM = 1 (OTP has been programmed)
     *                     ||Unimplemented <1:0>
     *                     ||| KEY7TYPE<1:0> = 10 (AES-128)
     *                     ||| | KEY5TYPE<1:0> = 10 (AES-128)
     *                     ||| | | KEY3TYPE<1:0> = 10 (AES-128)
     *                     ||| | | | KEY1TYPE<1:0> = 10 (AES-128)
     *                     ||| | | | | SKENEN = 0 (key 1 used for any operation)
     *                     ||| | | | | |LKYSRC<7:0> = (N/A due to SRCLCK = 0)
     *                     ||| | | | | ||       SRCLCK = 0
     *                     ||| | | | | ||       |WRLOCK8 = 1 (locked)
     *                     ||| | | | | ||       ||WRLOCK7 = 1 (locked)
     *                     ||| | | | | ||       |||WRLOCK6 = 1 (locked)
     *                     ||| | | | | ||       ||||WRLOCK5 = 1 (locked)
     *                     ||| | | | | ||       |||||WRLOCK4 = 1 (locked)
     *                     ||| | | | | ||       ||||||WRLOCK3 = 1 (locked)
     *                     ||| | | | | ||       |||||||WRLOCK2 = 1 (locked)
     *                     ||| | | | | ||       ||||||||WRLOCK1 = 1 (locked)
     *                     ||| | | | | ||       |||||||||WRLOCK0 = 1 (locked)
     *                     ||| | | | | ||       ||||||||||SWKYDIS = 0 (software keys allowed)
                           ||| | | | | ||       |||||||||||  */
    uint32_t otpConfig = 0b01001010101000000000001111111110;

    /*********************/
    /* Configure the OTP */
    /*********************/

    //point to page 0
    CRYOTPbits.KEYPG = 0b0000;

    memcpy((void*)&CRYTXTC0, (uint8_t*)&otpConfig, sizeof(otpConfig));

    __builtin_write_CRYOTP();
    while(CRYOTPbits.CRYWR == 1){}

    CRYOTPbits.CRYREAD = 1;
    while(CRYOTPbits.CRYREAD == 1){}
    
    return 0;
}

void DEMO_OTP_AES128Key1Test(BLOCK_CIPHER_HANDLE handle)
{
    static uint8_t plain_text[] = { 0x00, 0x11, 0x22, 0x33,
                                    0x44, 0x55, 0x66, 0x77,
                                    0x88, 0x99, 0xAA, 0xBB,
                                    0xCC, 0xDD, 0xEE, 0xFF
                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];

    memset(cipher_text, 0x00, sizeof(cipher_text));

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize(
            handle,
            &context,
            CRYPTO_16BV1_ALGORITHM_AES,
            CRYPTO_16BV1_ALGORITHM_AES,
            AES_BLOCK_SIZE,
            NULL,
            CRYPTO_KEY_HARDWARE_OTP_1,
            CRYPTO_AES_128_KEY
    );

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (
            handle,
            cipher_text,
            &num_bytes_encrypted,
            (void *) plain_text,
            sizeof(plain_text),
            BLOCK_CIPHER_OPTION_STREAM_START |
                BLOCK_CIPHER_OPTION_STREAM_COMPLETE |
                BLOCK_CIPHER_OPTION_PAD_NONE
    );

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
        static uint8_t expected_result[] = {    0x69, 0xc4, 0xe0, 0xd8,
                                                0x6a, 0x7b, 0x04, 0x30,
                                                0xd8, 0xcd, 0xb7, 0x80,
                                                0x70, 0xb4, 0xc5, 0x5a
                                           };

        unsigned int i;

        for(i=0;i<sizeof(plain_text);i++)
        {
            if(cipher_text[i] != expected_result[i])
            {
                //Error: results don't match what was expected
                while(1){}
            }
        }
    }
}

void DEMO_OTP_AES128Key2Test(BLOCK_CIPHER_HANDLE handle)
{
    static uint8_t plain_text[] = { 0x00, 0x11, 0x22, 0x33,
                                    0x44, 0x55, 0x66, 0x77,
                                    0x88, 0x99, 0xAA, 0xBB,
                                    0xCC, 0xDD, 0xEE, 0xFF
                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize(
            handle,
            &context,
            CRYPTO_16BV1_ALGORITHM_AES,
            CRYPTO_16BV1_ALGORITHM_AES,
            AES_BLOCK_SIZE,
            NULL,
            CRYPTO_KEY_HARDWARE_OTP_2,
            CRYPTO_AES_128_KEY
    );

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (
            handle,
            cipher_text,
            &num_bytes_encrypted,
            (void *) plain_text,
            sizeof(plain_text),
            BLOCK_CIPHER_OPTION_STREAM_START |
                BLOCK_CIPHER_OPTION_STREAM_COMPLETE |
                BLOCK_CIPHER_OPTION_PAD_NONE
    );

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
        static uint8_t expected_result[] = {    0xe1, 0x8a, 0x55, 0x67,
                                                0x01, 0xfe, 0x93, 0x4a,
                                                0x34, 0xba, 0x4c, 0x02,
                                                0x6b, 0x35, 0xf6, 0xc1
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

void DEMO_OTP_AES128Key3Test(BLOCK_CIPHER_HANDLE handle)
{
    static uint8_t plain_text[] = { 0x00, 0x11, 0x22, 0x33,
                                    0x44, 0x55, 0x66, 0x77,
                                    0x88, 0x99, 0xAA, 0xBB,
                                    0xCC, 0xDD, 0xEE, 0xFF
                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize(
            handle,
            &context,
            CRYPTO_16BV1_ALGORITHM_AES,
            CRYPTO_16BV1_ALGORITHM_AES,
            AES_BLOCK_SIZE,
            NULL,
            CRYPTO_KEY_HARDWARE_OTP_3,
            CRYPTO_AES_128_KEY
    );

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (
            handle,
            cipher_text,
            &num_bytes_encrypted,
            (void *) plain_text,
            sizeof(plain_text),
            BLOCK_CIPHER_OPTION_STREAM_START |
                BLOCK_CIPHER_OPTION_STREAM_COMPLETE |
                BLOCK_CIPHER_OPTION_PAD_NONE
    );

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
        static uint8_t expected_result[] = {    0x85, 0xa8, 0xa0, 0x5c,
                                                0x4a, 0xc5, 0x40, 0x91,
                                                0xe3, 0x8f, 0x3f, 0x03,
                                                0x1e, 0x39, 0x85, 0x04
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

void DEMO_OTP_AES128Key4Test(BLOCK_CIPHER_HANDLE handle)
{
    static uint8_t plain_text[] = { 0x00, 0x11, 0x22, 0x33,
                                    0x44, 0x55, 0x66, 0x77,
                                    0x88, 0x99, 0xAA, 0xBB,
                                    0xCC, 0xDD, 0xEE, 0xFF
                                  };

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context;
    uint32_t num_bytes_encrypted = 0;
    BLOCK_CIPHER_STATE state;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text[sizeof(plain_text)];

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize(
            handle,
            &context,
            CRYPTO_16BV1_ALGORITHM_AES,
            CRYPTO_16BV1_ALGORITHM_AES,
            AES_BLOCK_SIZE,
            NULL,
            CRYPTO_KEY_HARDWARE_OTP_4,
            CRYPTO_AES_128_KEY
    );

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (
            handle,
            cipher_text,
            &num_bytes_encrypted,
            (void *) plain_text,
            sizeof(plain_text),
            BLOCK_CIPHER_OPTION_STREAM_START |
                BLOCK_CIPHER_OPTION_STREAM_COMPLETE |
                BLOCK_CIPHER_OPTION_PAD_NONE
    );

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
        static uint8_t expected_result[] = {    0x8d, 0x7b, 0xb9, 0x5f,
                                                0xf3, 0x03, 0x6f, 0x89,
                                                0x5a, 0x1c, 0x6c, 0x9d,
                                                0xf6, 0xd3, 0x83, 0x1c
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


