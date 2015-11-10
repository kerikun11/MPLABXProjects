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

/* include files */
#include "crypto_sw/crypto_sw.h"

/* internal prototypes */
void AESCreateRoundKey_128bit_example();
void AESCreateRoundKey_192bit_example();
void AESCreateRoundKey_256bit_example();
void AESCreateRoundKey_variableWidth_example();


/* This example code shows how to create round keys 
 * for the various key sizes.
 */
void AES_SW_Key_Examples(void)
{
    AESCreateRoundKey_128bit_example();
    AESCreateRoundKey_192bit_example();
    AESCreateRoundKey_256bit_example();
    AESCreateRoundKey_variableWidth_example();
}

/* This example function shows how to create round keys from
 * a 128-bit key using the smallest storage size possible.
 */
void AESCreateRoundKey_128bit_example()
{
    //This example comes from Appendix F.3.1 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    /* create a place to store this round key */
    AES_SW_ROUND_KEYS_128_BIT round_keys;

    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey128,
                            AES_SW_KEY_SIZE_128_BIT
                       );
}

/* This example function shows how to create round keys from
 * a 192-bit key using the smallest storage size possible.
 */
void AESCreateRoundKey_192bit_example()
{
    //This example comes from Appendix F.3.1 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey192[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    /* create a place to store this round key */
    AES_SW_ROUND_KEYS_192_BIT round_keys;

    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey192,
                            AES_SW_KEY_SIZE_192_BIT
                       );
}

/* This example function shows how to create round keys from
 * a 256-bit key using the smallest storage size possible.
 */
void AESCreateRoundKey_256bit_example()
{
    //This example comes from Appendix F.3.1 of the 
    //  "NIST Special Publication 800-38A: Recommendation for Block Cipher Modes 
    //  of Operation: Methods and Techniques" (sp800-38a.pdf)
    static uint8_t AESKey256[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    /* create a place to store this round key */
    AES_SW_ROUND_KEYS_256_BIT round_keys;

    //Create the round keys.  This only needs to be done once for each key.
    //  This example is here for completeness.
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey256,
                            AES_SW_KEY_SIZE_256_BIT
                       );
}

/* This example function shows how to create round keys from 
 * different key sources of different sizes reusing the same
 * roundkey variable.
 *
 * This type of usage may be useful in systems that use different
 * key sizes that may change.  This method allows for a key of any
 * size to be generated without having to create new round key
 * variables for each key width.
 */
void AESCreateRoundKey_variableWidth_example()
{
    static uint8_t AESKey128[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t AESKey192[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t AESKey256[]      =       { 0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c,
                                                    0x2b, 0x7e, 0x15, 0x16, 
                                                    0x28, 0xae, 0xd2, 0xa6, 
                                                    0xab, 0xf7, 0x15, 0x88, 
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    /* create a place to store this round key */
    AES_SW_ROUND_KEYS round_keys;

    //Create the round keys from a 128-bit source.
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey128,
                            AES_SW_KEY_SIZE_128_BIT
                       );

    /* Create the round keys from a 192-bit source.  This will destroy the
     * keys from the 128-bit key.
     */
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey192,
                            AES_SW_KEY_SIZE_192_BIT
                       );

    /* Create the round keys from a 256-bit source.  This will destroy the
     * keys from the 192-bit key.
     */
    AES_SW_RoundKeysCreate (    &round_keys,
                            (uint8_t*)AESKey256,
                            AES_SW_KEY_SIZE_256_BIT
                       );

}

