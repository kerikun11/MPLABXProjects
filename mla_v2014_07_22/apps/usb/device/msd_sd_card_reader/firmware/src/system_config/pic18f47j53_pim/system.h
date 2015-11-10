/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
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
 *******************************************************************/

#if defined(__XC8)
    #include <xc.h>
#else
    #include <p18cxxx.h>
#endif
#include <stdbool.h>
#include <stdint.h>

#include "io_mapping.h"

// Definition for system clock
#define SYS_CLK_FrequencySystemGet()        48000000UL
// Definition for peripheral clock
#define SYS_CLK_FrequencyPeripheralGet()    SYS_CLK_FrequencySystemGet()
// Definition for instruction clock
#define SYS_CLK_FrequencyInstructionGet()   (SYS_CLK_FrequencySystemGet() / 4)

#define MAIN_RETURN void

//Definitions letting SPI driver code know which SPI module to use
//#define DRV_SPI_CONFIG_CHANNEL_1_ENABLE      // Enable SPI channel 1
#define DRV_SPI_CONFIG_CHANNEL_2_ENABLE      // Enable SPI channel 2
//#define DRV_SPI_CONFIG_CHANNEL_3_ENABLE      // Enable SPI channel 3
//#define DRV_SPI_CONFIG_CHANNEL_4_ENABLE      // Enable SPI channel 4

#define USER_SPI_MODULE_NUM   2			//MSSP number used on this device

// Disable SPI FIFO mode in parts where it is not supported
// Enabling the FIFO mode will improve library performance.
// In this demo this definition is sometimes disabled because early versions of the PIC24FJ128GA010s have an errata preventing this feature from being used.
#if defined (__XC8__) || defined (__PIC24FJ128GA010__)
#define DRV_SPI_CONFIG_ENHANCED_BUFFER_DISABLE
#endif

/*********************************************************************
* Function: void SYSTEM_Initialize(void)
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize(void);

/*********************************************************************
* Function: void SYSTEM_Tasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with SYSTEM_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
#define SYSTEM_Tasks()

// User-defined function to set the chip select for our example drive
void USER_SdSpiSetCs_1 (uint8_t a);
// User-defined function to get the card detection status for our example drive
bool USER_SdSpiGetCd_1 (void);
// User-defined function to get the write-protect status for our example drive
bool USER_SdSpiGetWp_1 (void);
// User-defined function to initialize tristate bits for CS, CD, and WP
void USER_SdSpiConfigurePins_1 (void);

// Prototype for low-clock-rate SPI initialize function
void InitSPISlowMode(void * config);
// Prototype for low-clock-rate SPI Get function
uint8_t ReadMediaManual (uint8_t filler);
// Prototype for low-clock-rate SPI Put function
void WriteSPIManual(uint8_t filler, uint8_t data_out);

