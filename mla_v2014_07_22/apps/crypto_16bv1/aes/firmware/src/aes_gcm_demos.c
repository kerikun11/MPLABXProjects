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

void AES_GCM_Example1(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example2(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example3(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example4(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example5(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example6(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example7(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example8(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example9(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example10(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example11(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example12(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example13(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example14(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example15(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example16(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example17(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example18(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Example19(BLOCK_CIPHER_HANDLE handle);

const uint8_t keyZero128[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t key128[16]     = {0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08};
const uint8_t keyZero192[24] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
const uint8_t key192[24]     = {0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08,0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,};
const uint8_t keyZero256[32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
const uint8_t key256[32]     = {0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08,0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08,};

uint8_t ptNull[0];
uint8_t ptZeros[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t ptFourBlocks[64] = {0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55};
uint8_t ptShort[60] = {0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,};

uint8_t authData[20] = {0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xab,0xad,0xda,0xd2,};

uint8_t ivZeros[12] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t ivValue[12] = {0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88};
uint8_t ivLong[60] = {0x93,0x13,0x22,0x5d,0xf8,0x84,0x06,0xe5,0x55,0x90,0x9c,0x5a,0xff,0x52,0x69,0xaa,0x6a,0x7a,0x95,0x38,0x53,0x4f,0x7d,0xa1,0xe4,0xc3,0x03,0xd2,0xa3,0x18,0xa7,0x28,0xc3,0xc0,0xc9,0x51,0x56,0x80,0x95,0x39,0xfc,0xf0,0xe2,0x42,0x9a,0x6b,0x52,0x54,0x16,0xae,0xdb,0xf5,0xa0,0xde,0x6a,0x57,0xa6,0x37,0xb3,0x9b,};

uint8_t tag[16];
uint8_t cipherText[64];
uint8_t plainText[64];

const uint8_t authTag1[]  = {0x58,0xe2,0xfc,0xce,0xfa,0x7e,0x30,0x61,0x36,0x7f,0x1d,0x57,0xa4,0xe7,0x45,0x5a,};
const uint8_t authTag2[]  = {0xab,0x6e,0x47,0xd4,0x2c,0xec,0x13,0xbd,0xf5,0x3a,0x67,0xb2,0x12,0x57,0xbd,0xdf,};
const uint8_t authTag3[]  = {0x4d,0x5c,0x2a,0xf3,0x27,0xcd,0x64,0xa6,0x2c,0xf3,0x5a,0xbd,0x2b,0xa6,0xfa,0xb4,};
const uint8_t authTag4[]  = {0x5b,0xc9,0x4f,0xbc,0x32,0x21,0xa5,0xdb,0x94,0xfa,0xe9,0x5a,0xe7,0x12,0x1a,0x47,};
const uint8_t authTag5[]  = {0x36,0x12,0xd2,0xe7,0x9e,0x3b,0x07,0x85,0x56,0x1b,0xe1,0x4a,0xac,0xa2,0xfc,0xcb,};
const uint8_t authTag6[]  = {0x61,0x9c,0xc5,0xae,0xff,0xfe,0x0b,0xfa,0x46,0x2a,0xf4,0x3c,0x16,0x99,0xd0,0x50,};
const uint8_t authTag7[]  = {0xcd,0x33,0xb2,0x8a,0xc7,0x73,0xf7,0x4b,0xa0,0x0e,0xd1,0xf3,0x12,0x57,0x24,0x35,};
const uint8_t authTag8[]  = {0x2f,0xf5,0x8d,0x80,0x03,0x39,0x27,0xab,0x8e,0xf4,0xd4,0x58,0x75,0x14,0xf0,0xfb,};
const uint8_t authTag9[]  = {0x99,0x24,0xa7,0xc8,0x58,0x73,0x36,0xbf,0xb1,0x18,0x02,0x4d,0xb8,0x67,0x4a,0x14,};
const uint8_t authTag10[] = {0x25,0x19,0x49,0x8e,0x80,0xf1,0x47,0x8f,0x37,0xba,0x55,0xbd,0x6d,0x27,0x61,0x8c,};
const uint8_t authTag11[] = {0x65,0xdc,0xc5,0x7f,0xcf,0x62,0x3a,0x24,0x09,0x4f,0xcc,0xa4,0x0d,0x35,0x33,0xf8,};
const uint8_t authTag12[] = {0xdc,0xf5,0x66,0xff,0x29,0x1c,0x25,0xbb,0xb8,0x56,0x8f,0xc3,0xd3,0x76,0xa6,0xd9,};
const uint8_t authTag13[] = {0x53,0x0f,0x8a,0xfb,0xc7,0x45,0x36,0xb9,0xa9,0x63,0xb4,0xf1,0xc4,0xcb,0x73,0x8b,};
const uint8_t authTag14[] = {0xd0,0xd1,0xc8,0xa7,0x99,0x99,0x6b,0xf0,0x26,0x5b,0x98,0xb5,0xd4,0x8a,0xb9,0x19,};
const uint8_t authTag15[] = {0xb0,0x94,0xda,0xc5,0xd9,0x34,0x71,0xbd,0xec,0x1a,0x50,0x22,0x70,0xe3,0xcc,0x6c,};
const uint8_t authTag16[] = {0x76,0xfc,0x6e,0xce,0x0f,0x4e,0x17,0x68,0xcd,0xdf,0x88,0x53,0xbb,0x2d,0x55,0x1b,};
const uint8_t authTag17[] = {0x3a,0x33,0x7d,0xbf,0x46,0xa7,0x92,0xc4,0x5e,0x45,0x49,0x13,0xfe,0x2e,0xa8,0xf2,};
const uint8_t authTag18[] = {0xa4,0x4a,0x82,0x66,0xee,0x1c,0x8e,0xb0,0xc8,0xb5,0xd4,0xcf,0x5a,0xe9,0xf1,0x9a,};

const uint8_t cipherText1[0];
const uint8_t cipherText2[16]  = {0x03,0x88,0xda,0xce,0x60,0xb6,0xa3,0x92,0xf3,0x28,0xc2,0xb9,0x71,0xb2,0xfe,0x78,};
const uint8_t cipherText3[64]  = {0x42,0x83,0x1e,0xc2,0x21,0x77,0x74,0x24,0x4b,0x72,0x21,0xb7,0x84,0xd0,0xd4,0x9c,0xe3,0xaa,0x21,0x2f,0x2c,0x02,0xa4,0xe0,0x35,0xc1,0x7e,0x23,0x29,0xac,0xa1,0x2e,0x21,0xd5,0x14,0xb2,0x54,0x66,0x93,0x1c,0x7d,0x8f,0x6a,0x5a,0xac,0x84,0xaa,0x05,0x1b,0xa3,0x0b,0x39,0x6a,0x0a,0xac,0x97,0x3d,0x58,0xe0,0x91,0x47,0x3f,0x59,0x85,};
const uint8_t cipherText4[60]  = {0x42,0x83,0x1e,0xc2,0x21,0x77,0x74,0x24,0x4b,0x72,0x21,0xb7,0x84,0xd0,0xd4,0x9c,0xe3,0xaa,0x21,0x2f,0x2c,0x02,0xa4,0xe0,0x35,0xc1,0x7e,0x23,0x29,0xac,0xa1,0x2e,0x21,0xd5,0x14,0xb2,0x54,0x66,0x93,0x1c,0x7d,0x8f,0x6a,0x5a,0xac,0x84,0xaa,0x05,0x1b,0xa3,0x0b,0x39,0x6a,0x0a,0xac,0x97,0x3d,0x58,0xe0,0x91,};
const uint8_t cipherText5[60]  = {0x61,0x35,0x3b,0x4c,0x28,0x06,0x93,0x4a,0x77,0x7f,0xf5,0x1f,0xa2,0x2a,0x47,0x55,0x69,0x9b,0x2a,0x71,0x4f,0xcd,0xc6,0xf8,0x37,0x66,0xe5,0xf9,0x7b,0x6c,0x74,0x23,0x73,0x80,0x69,0x00,0xe4,0x9f,0x24,0xb2,0x2b,0x09,0x75,0x44,0xd4,0x89,0x6b,0x42,0x49,0x89,0xb5,0xe1,0xeb,0xac,0x0f,0x07,0xc2,0x3f,0x45,0x98,};
const uint8_t cipherText6[60] = {0x8c,0xe2,0x49,0x98,0x62,0x56,0x15,0xb6,0x03,0xa0,0x33,0xac,0xa1,0x3f,0xb8,0x94,0xbe,0x91,0x12,0xa5,0xc3,0xa2,0x11,0xa8,0xba,0x26,0x2a,0x3c,0xca,0x7e,0x2c,0xa7,0x01,0xe4,0xa9,0xa4,0xfb,0xa4,0x3c,0x90,0xcc,0xdc,0xb2,0x81,0xd4,0x8c,0x7c,0x6f,0xd6,0x28,0x75,0xd2,0xac,0xa4,0x17,0x03,0x4c,0x34,0xae,0xe5,};
const uint8_t cipherText7[0];
const uint8_t cipherText8[16]  = {0x98,0xe7,0x24,0x7c,0x07,0xf0,0xfe,0x41,0x1c,0x26,0x7e,0x43,0x84,0xb0,0xf6,0x00,};
const uint8_t cipherText9[64]  = {0x39,0x80,0xca,0x0b,0x3c,0x00,0xe8,0x41,0xeb,0x06,0xfa,0xc4,0x87,0x2a,0x27,0x57,0x85,0x9e,0x1c,0xea,0xa6,0xef,0xd9,0x84,0x62,0x85,0x93,0xb4,0x0c,0xa1,0xe1,0x9c,0x7d,0x77,0x3d,0x00,0xc1,0x44,0xc5,0x25,0xac,0x61,0x9d,0x18,0xc8,0x4a,0x3f,0x47,0x18,0xe2,0x44,0x8b,0x2f,0xe3,0x24,0xd9,0xcc,0xda,0x27,0x10,0xac,0xad,0xe2,0x56,};
const uint8_t cipherText10[60] = {0x39,0x80,0xca,0x0b,0x3c,0x00,0xe8,0x41,0xeb,0x06,0xfa,0xc4,0x87,0x2a,0x27,0x57,0x85,0x9e,0x1c,0xea,0xa6,0xef,0xd9,0x84,0x62,0x85,0x93,0xb4,0x0c,0xa1,0xe1,0x9c,0x7d,0x77,0x3d,0x00,0xc1,0x44,0xc5,0x25,0xac,0x61,0x9d,0x18,0xc8,0x4a,0x3f,0x47,0x18,0xe2,0x44,0x8b,0x2f,0xe3,0x24,0xd9,0xcc,0xda,0x27,0x10,};
const uint8_t cipherText11[60] = {0x0f,0x10,0xf5,0x99,0xae,0x14,0xa1,0x54,0xed,0x24,0xb3,0x6e,0x25,0x32,0x4d,0xb8,0xc5,0x66,0x63,0x2e,0xf2,0xbb,0xb3,0x4f,0x83,0x47,0x28,0x0f,0xc4,0x50,0x70,0x57,0xfd,0xdc,0x29,0xdf,0x9a,0x47,0x1f,0x75,0xc6,0x65,0x41,0xd4,0xd4,0xda,0xd1,0xc9,0xe9,0x3a,0x19,0xa5,0x8e,0x8b,0x47,0x3f,0xa0,0xf0,0x62,0xf7,};
const uint8_t cipherText12[60] = {0xd2,0x7e,0x88,0x68,0x1c,0xe3,0x24,0x3c,0x48,0x30,0x16,0x5a,0x8f,0xdc,0xf9,0xff,0x1d,0xe9,0xa1,0xd8,0xe6,0xb4,0x47,0xef,0x6e,0xf7,0xb7,0x98,0x28,0x66,0x6e,0x45,0x81,0xe7,0x90,0x12,0xaf,0x34,0xdd,0xd9,0xe2,0xf0,0x37,0x58,0x9b,0x29,0x2d,0xb3,0xe6,0x7c,0x03,0x67,0x45,0xfa,0x22,0xe7,0xe9,0xb7,0x37,0x3b,};
const uint8_t cipherText13[0];
const uint8_t cipherText14[16] = {0xce,0xa7,0x40,0x3d,0x4d,0x60,0x6b,0x6e,0x07,0x4e,0xc5,0xd3,0xba,0xf3,0x9d,0x18,};
const uint8_t cipherText15[64] = {0x52,0x2d,0xc1,0xf0,0x99,0x56,0x7d,0x07,0xf4,0x7f,0x37,0xa3,0x2a,0x84,0x42,0x7d,0x64,0x3a,0x8c,0xdc,0xbf,0xe5,0xc0,0xc9,0x75,0x98,0xa2,0xbd,0x25,0x55,0xd1,0xaa,0x8c,0xb0,0x8e,0x48,0x59,0x0d,0xbb,0x3d,0xa7,0xb0,0x8b,0x10,0x56,0x82,0x88,0x38,0xc5,0xf6,0x1e,0x63,0x93,0xba,0x7a,0x0a,0xbc,0xc9,0xf6,0x62,0x89,0x80,0x15,0xad,};
const uint8_t cipherText16[60] = {0x52,0x2d,0xc1,0xf0,0x99,0x56,0x7d,0x07,0xf4,0x7f,0x37,0xa3,0x2a,0x84,0x42,0x7d,0x64,0x3a,0x8c,0xdc,0xbf,0xe5,0xc0,0xc9,0x75,0x98,0xa2,0xbd,0x25,0x55,0xd1,0xaa,0x8c,0xb0,0x8e,0x48,0x59,0x0d,0xbb,0x3d,0xa7,0xb0,0x8b,0x10,0x56,0x82,0x88,0x38,0xc5,0xf6,0x1e,0x63,0x93,0xba,0x7a,0x0a,0xbc,0xc9,0xf6,0x62,};
const uint8_t cipherText17[60] = {0xc3,0x76,0x2d,0xf1,0xca,0x78,0x7d,0x32,0xae,0x47,0xc1,0x3b,0xf1,0x98,0x44,0xcb,0xaf,0x1a,0xe1,0x4d,0x0b,0x97,0x6a,0xfa,0xc5,0x2f,0xf7,0xd7,0x9b,0xba,0x9d,0xe0,0xfe,0xb5,0x82,0xd3,0x39,0x34,0xa4,0xf0,0x95,0x4c,0xc2,0x36,0x3b,0xc7,0x3f,0x78,0x62,0xac,0x43,0x0e,0x64,0xab,0xe4,0x99,0xf4,0x7c,0x9b,0x1f,};
const uint8_t cipherText18[60] = {0x5a,0x8d,0xef,0x2f,0x0c,0x9e,0x53,0xf1,0xf7,0x5d,0x78,0x53,0x65,0x9e,0x2a,0x20,0xee,0xb2,0xb2,0x2a,0xaf,0xde,0x64,0x19,0xa0,0x58,0xab,0x4f,0x6f,0x74,0x6b,0xf4,0x0f,0xc0,0xc3,0xb7,0x80,0xf2,0x44,0x45,0x2d,0xa3,0xeb,0xf1,0xc5,0xd8,0x2c,0xde,0xa2,0x41,0x89,0x97,0x20,0x0e,0xf8,0x2e,0x44,0xae,0x7e,0x3f,};

#define KEY_STREAM_SIZE     (AES_BLOCK_SIZE * 4)

void AES_GCM_Examples(BLOCK_CIPHER_HANDLE handle)
{
    // Examples 1-18 are test vectors provided by the revised GCM specification.
    // http://csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/gcm/gcm-revised-spec.pdf

    AES_GCM_Example1(handle);
    AES_GCM_Example2(handle);
    AES_GCM_Example3(handle);
    AES_GCM_Example4(handle);
    AES_GCM_Example5(handle);
    AES_GCM_Example6(handle);
    AES_GCM_Example7(handle);
    AES_GCM_Example8(handle);
    AES_GCM_Example9(handle);
    AES_GCM_Example10(handle);
    AES_GCM_Example11(handle);
    AES_GCM_Example12(handle);
    AES_GCM_Example13(handle);
    AES_GCM_Example14(handle);
    AES_GCM_Example15(handle);
    AES_GCM_Example16(handle);
    AES_GCM_Example17(handle);
    AES_GCM_Example18(handle);

    // Example 13 tests the GCM module with several usage modes.
    AES_GCM_Example19(handle);
 
}

void AES_GCM_Example1(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;
    
    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, NULL, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText1, 0) != 0) || (memcmp(tag, authTag1, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptNull, 0) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example2(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptZeros, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText2, 16) != 0) || (memcmp(tag, authTag2, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptZeros, 16) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example3(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptFourBlocks, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText3, 64) != 0) || (memcmp(tag, authTag3, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptFourBlocks, 64) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example4(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText4, 60) != 0) || (memcmp(tag, authTag4, 16) != 0))
    {
        while(1);
    }
    
    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example5(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText5, 60) != 0) || (memcmp(tag, authTag5, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example6(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText6, 60) != 0) || (memcmp(tag, authTag6, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key128, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example7(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, NULL, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText7, 0) != 0) || (memcmp(tag, authTag7, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptNull, 0) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example8(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptZeros, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText8, 16) != 0) || (memcmp(tag, authTag8, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptZeros, 16) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example9(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptFourBlocks, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText9, 64) != 0) || (memcmp(tag, authTag9, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptFourBlocks, 64) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example10(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText10, 60) != 0) || (memcmp(tag, authTag10, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example11(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText11, 60) != 0) || (memcmp(tag, authTag11, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example12(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText12, 60) != 0) || (memcmp(tag, authTag12, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key192, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_192_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example13(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, NULL, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText13, 0) != 0) || (memcmp(tag, authTag13, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 0, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptNull, 0) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example14(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptZeros, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText14, 16) != 0) || (memcmp(tag, authTag14, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivZeros, 12, (void *)&keyStream, sizeof(keyStream), &keyZero256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 16, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptZeros, 16) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example15(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptFourBlocks, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText15, 64) != 0) || (memcmp(tag, authTag15, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 64, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptFourBlocks, 64) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example16(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example17(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText17, 60) != 0) || (memcmp(tag, authTag17, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 8, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example18(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    BLOCK_CIPHER_STATE state;

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText18, 60) != 0) || (memcmp(tag, authTag18, 16) != 0))
    {
        while(1);
    }

    // Re-initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivLong, 60, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 4, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-decrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Decrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Decrypt (handle, plainText, &byteCount, cipherText, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the decryption and/or authentication was correct
    if (memcmp (plainText, ptShort, 60) != 0)
    {
        while(1);
    }
}

void AES_GCM_Example19(BLOCK_CIPHER_HANDLE handle)
{
    BLOCK_CIPHER_16BV1_GCM_CONTEXT context;
    //keyStream could also be allocated memory instead of fixed memory
    uint8_t keyStream[KEY_STREAM_SIZE];
    uint8_t i;
    BLOCK_CIPHER_STATE state;

    //*************************************************
    // Test several alternate usage models for GCM
    //*************************************************

    //**************************************************
    // Test encrypting without pre-generating keystream,
    // In this test, 4 ks blocks will be generated by
    // the second call of Encrypt.
    //**************************************************

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }

    //**************************************************
    // Test bytewise encryption.
    //**************************************************

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    for (i = 0; i < 20; i++)
    {
        // Authenticate the non-encrypted data
        if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData + i, 1, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
        {
            // An error occured
            while(1);
        }

        while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
        {
            BLOCK_CIPHER_16BV1_Tasks();
        }

        if (state == BLOCK_CIPHER_STATE_ERROR)
        {
            while(1);
        }
    }

    for (i = 0; i < 59; i++)
    {
        //Encrypt the data
        if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText + i, &byteCount, (uint8_t *)ptShort + i, 1, tag, 16, BLOCK_CIPHER_OPTION_STREAM_CONTINUE) != BLOCK_CIPHER_ERROR_NONE)
        {
            // An error occured
            while(1);
        }

        while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
        {
            BLOCK_CIPHER_16BV1_Tasks();
        }

        if (state == BLOCK_CIPHER_STATE_ERROR)
        {
            while(1);
        }
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText + i, &byteCount, (uint8_t *)ptShort + i, 1, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }

    //**************************************************
    // Test encrypting when generating one block of
    // the keystream at a time.
    //**************************************************

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, 16, &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }

    //**************************************************
    // Test encrypting when pre-generating one block
    // of the keystream and generating one block at
    // a time.
    //**************************************************

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, 16, &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Generate 4 blocks of key stream
    BLOCK_CIPHER_16BV1_GCM_KeyStreamGenerate(handle, 1, 0);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText, &byteCount, (uint8_t *)ptShort, 60, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }

    //**************************************************
    // Test encrypting an odd number of bytes at a time
    // and caching some for later authentication.
    //**************************************************

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_GCM_Initialize (handle, &context, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, (uint8_t *)ivValue, 12, (void *)&keyStream, sizeof(keyStream), &key256, CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Authenticate the non-encrypted data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, NULL, &byteCount, (uint8_t *)authData, 20, NULL, 0, BLOCK_CIPHER_OPTION_AUTHENTICATE_ONLY) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }


    for (i = 0; i < 19; i++)
    {
        //Encrypt the data
        if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText + (i * 3), &byteCount, (uint8_t *)ptShort + (i * 3), 3, tag, 16, BLOCK_CIPHER_OPTION_STREAM_CONTINUE) != BLOCK_CIPHER_ERROR_NONE)
        {
            // An error occured
            while(1);
        }

        while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
        {
            BLOCK_CIPHER_16BV1_Tasks();
        }

        if (state == BLOCK_CIPHER_STATE_ERROR)
        {
            while(1);
        }
    }

    //Encrypt the data
    if (BLOCK_CIPHER_16BV1_GCM_Encrypt (handle, cipherText + (i * 3), &byteCount, (uint8_t *)ptShort + (i * 3), 3, tag, 16, BLOCK_CIPHER_OPTION_STREAM_COMPLETE) != BLOCK_CIPHER_ERROR_NONE)
    {
        // An error occured
        while(1);
    }

    while (((state = BLOCK_CIPHER_16BV1_GetState(handle)) != BLOCK_CIPHER_STATE_IDLE) && (state != BLOCK_CIPHER_STATE_ERROR))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    if (state == BLOCK_CIPHER_STATE_ERROR)
    {
        while(1);
    }

    // Verify that the encryption and/or authentication was correct
    if ((memcmp (cipherText, cipherText16, 60) != 0) || (memcmp(tag, authTag16, 16) != 0))
    {
        while(1);
    }
}

