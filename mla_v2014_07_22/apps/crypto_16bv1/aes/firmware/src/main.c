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

#include <stdlib.h>
#include "system_config.h"
#include "crypto_16bv1/crypto_16bv1.h"

/** CONFIGURATION Bits **********************************************/
// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF               // General Segment Write Protect (Write to program memory allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (Disabled)

// CONFIG2
#pragma config POSCMD = NONE              // Primary Oscillator Select (HS Oscillator Enabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = ON            // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as port I/O (RA3))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Primary Oscillator with PLL module (XTPLL,HSPLL, ECPLL))
#pragma config ALTRB6 = APPEND          // Alternate RB6 pin function enable bit (Append the RP6/ASCL1/PMPD6 functions of RB6 to RA1 pin functions)
#pragma config ALTCMPI = CxINC_RB       // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
#pragma config WDTCMX = WDTCLK          // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config VBTBOR = OFF             // VBAT BOR Enable Bit (VBAT BOR is disabled)
#pragma config IESO = OFF               // Internal External Switchover (Disabled)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = ON             // SOSC Selection bits (SOSC circuit selected)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config BOREN = OFF              // Brown-out Reset Enable (Brown-out Reset Disabled)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (DSBOR Disabled)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (DSWDT Disabled)
#pragma config DSSWEN = OFF             // DSEN Bit Enable (Deep Sleep operation is always disabled)
#pragma config PLLDIV = DIVIDE2         // USB 96 MHz PLL Prescaler Select bits (Oscillator input divided by 2 (8 MHz input))
#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)


void AES_CBC_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_CTR_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_ECB_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_OFB_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_CFB_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_GCM_Examples(BLOCK_CIPHER_HANDLE handle);
void AES_OTP_Examples(BLOCK_CIPHER_HANDLE handle);

#if defined(__C30__) || defined(__C32__)
int main(void)
#else
void main(void)
#endif
{
    SYS_MODULE_OBJ sysObject;
    BLOCK_CIPHER_HANDLE handle;
    
    //Multiple_Thread_Test ();

    // Initialize the AES module.  There is no initialization required for the pure software AES module; this function
    // is used in this instance to create code that will be more easily portable to a hardware AES implementation.
    // For the software implementation, BLOCK_CIPHER_INDEX is defined as '0' since there aren't multiple instances of it, as
    // there might be in hardware.  Hardware AES modules may have multiple encryption/decryption engines; in this case,
    // the BLOCK_CIPHER_16BV1_Initialize function would be used to indicate which one to use, and different macros would be defined
    // by the AES module drivers (e.g. BLOCK_CIPHER_INDEX_0 and BLOCK_CIPHER_INDEX_1 if there were two AES hardware modules).
    sysObject = BLOCK_CIPHER_16BV1_Initialize(BLOCK_CIPHER_INDEX, NULL);
    if (sysObject != SYS_MODULE_OBJ_STATIC)
    {
        return false;
    }

    handle = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }
    
    AES_ECB_Examples(handle);

    AES_CBC_Examples(handle);

    AES_CFB_Examples(handle);

    AES_OFB_Examples(handle);

    AES_CTR_Examples(handle);

    AES_GCM_Examples(handle);

    /* WARNING: uncommenting out the below line will cause the OTP in the part
     * to be written.  These demos show how to program the OTP and use OTP based
     * keys.  The keys can't be reprogrammed after this operation. */
    //AES_OTP_Examples(handle);

    while(BLOCK_CIPHER_16BV1_GetState(handle) != BLOCK_CIPHER_STATE_IDLE)
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    // Close our drive handle and de-initialize the AES module.
    BLOCK_CIPHER_16BV1_Close (handle);

    BLOCK_CIPHER_16BV1_Deinitialize (sysObject);

    while(1){}
}

bool Multiple_Thread_Test ( void )
{
    SYS_MODULE_OBJ sysObject;
    BLOCK_CIPHER_HANDLE handle1;
    BLOCK_CIPHER_HANDLE handle2;
    BLOCK_CIPHER_HANDLE handle3;
    BLOCK_CIPHER_HANDLE handle4;
    BLOCK_CIPHER_HANDLE handle5;

     static uint8_t AESKey1281[]      =       { 0x2b, 0x7e, 0x15, 0x16,
                                                    0x28, 0xae, 0xd2, 0xa6,
                                                    0xab, 0xf7, 0x15, 0x88,
                                                    0x09, 0xcf, 0x4f, 0x3c
                                                  };

    static uint8_t plain_text1[]     =       { 0x6b, 0xc1, 0xbe, 0xe2,
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

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context1;
    uint32_t num_bytes_encrypted1;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t cipher_text1[sizeof(plain_text1)];

    static uint8_t AESKey2562[]      =       { 0xdd, 0xe0, 0x79, 0x37,
                                                    0x11, 0x33, 0xeb, 0xd6,
                                                    0x8d, 0xf0, 0x61, 0xb5,
                                                    0x6f, 0x0e, 0xfd, 0x3a,
                                                    0x14, 0xc1, 0x37, 0xce,
                                                    0xd3, 0x5a, 0x30, 0xe0,
                                                    0xeb, 0x68, 0x42, 0x2c,
                                                    0xb9, 0x24, 0xdc, 0x3d
                                                  };

    static uint8_t cipher_text2[]    =       { 0xea, 0x1f, 0xd2, 0xf0,
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

    BLOCK_CIPHER_16BV1_ECB_CONTEXT context2;
    uint32_t num_bytes_decrypted2;

    //We need a buffer to contain the resulting data.
    //  This buffer can be created statically or dynamically and can be
    //  of any size as long as it is larger than or equal to AES_BLOCK_SIZE
    uint8_t plain_text2[sizeof(cipher_text2)];

    // Initialize the AES module.  There is no initialization required for the pure software AES module; this function
    // is used in this instance to create code that will be more easily portable to a hardware AES implementation.
    // For the software implementation, BLOCK_CIPHER_INDEX is defined as '0' since there aren't multiple instances of it, as
    // there might be in hardware.  Hardware AES modules may have multiple encryption/decryption engines; in this case,
    // the BLOCK_CIPHER_16BV1_Initialize function would be used to indicate which one to use, and different macros would be defined
    // by the AES module drivers (e.g. BLOCK_CIPHER_INDEX_0 and BLOCK_CIPHER_INDEX_1 if there were two AES hardware modules).
    sysObject = BLOCK_CIPHER_16BV1_Initialize(BLOCK_CIPHER_INDEX, NULL);
    if (sysObject != SYS_MODULE_OBJ_STATIC)
    {
        return false;
    }

    handle1 = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle1 == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }
    handle2 = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle2 == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }
    handle3 = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle3 == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }
    handle4 = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle4 == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }
    handle5 = BLOCK_CIPHER_16BV1_Open(BLOCK_CIPHER_INDEX, DRV_IO_INTENT_SHARED);
    if (handle5 == BLOCK_CIPHER_HANDLE_INVALID)
    {
        return false;
    }

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle1, &context1, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey1281[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_128_KEY);

    //Encrypt the data
    BLOCK_CIPHER_16BV1_ECB_Encrypt (handle1, cipher_text1, &num_bytes_encrypted1, (void *) plain_text1, sizeof(plain_text1), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE|BLOCK_CIPHER_OPTION_PAD_NONE);

    // Initialize the Block Cipher context
    BLOCK_CIPHER_16BV1_ECB_Initialize (handle2, &context2, CRYPTO_16BV1_ALGORITHM_AES, CRYPTO_16BV1_ALGORITHM_AES, AES_BLOCK_SIZE, &AESKey2562[0], CRYPTO_KEY_SOFTWARE, CRYPTO_AES_256_KEY);

    //Decrypt the data
    BLOCK_CIPHER_16BV1_ECB_Decrypt (handle2, plain_text2, &num_bytes_decrypted2, cipher_text2, sizeof(cipher_text2), BLOCK_CIPHER_OPTION_STREAM_START|BLOCK_CIPHER_OPTION_STREAM_COMPLETE);

    while((BLOCK_CIPHER_16BV1_GetState(handle1) != BLOCK_CIPHER_STATE_IDLE) ||\
          (BLOCK_CIPHER_16BV1_GetState(handle2) != BLOCK_CIPHER_STATE_IDLE))
    {
        BLOCK_CIPHER_16BV1_Tasks();
    }

    static uint8_t expected_result1[] =
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

    for(i=0;i<sizeof(plain_text1);i++)
    {
        if(cipher_text1[i] != expected_result1[i])
        {
            //Error: results don't match what was expected
            while(1){};
        }
    }

    static uint8_t expected_result2[] =
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

    for(i=0;i<sizeof(cipher_text2);i++)
    {
        if(plain_text2[i] != expected_result2[i])
        {
            //Error: results don't match what was expected
            while(1){};
        }
    }


    // Close our drive handle and de-initialize the AES module.
    BLOCK_CIPHER_16BV1_Close (handle1);
    BLOCK_CIPHER_16BV1_Close (handle2);
    BLOCK_CIPHER_16BV1_Close (handle3);
    BLOCK_CIPHER_16BV1_Close (handle4);
    BLOCK_CIPHER_16BV1_Close (handle5);

    BLOCK_CIPHER_16BV1_Deinitialize (sysObject);
    
    return true;
}