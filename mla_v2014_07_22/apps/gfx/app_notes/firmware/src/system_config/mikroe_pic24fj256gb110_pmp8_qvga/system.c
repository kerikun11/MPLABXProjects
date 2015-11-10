/*******************************************************************************
  System Specific Initializations

  Company:
    Microchip Technology Inc.

  File Name:
    system.c

  Summary:
    System level initializations for the specific Microchip Development Board used.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// Section: Includes
// *****************************************************************************
#include <xc.h>
#include <stdlib.h>
#include <system.h>
#include <usb/usb.h>
#include "driver/spi/drv_spi.h"
#include "driver/gfx/drv_gfx_display.h"
#include "driver/gfx/drv_gfx_tft003.h"
#include "driver/nvm/drv_nvm_flash_spi_m25p80.h"
#include "driver/touch_screen/drv_touch_screen.h"
#include "memory_programmer/flash_programmer.h"

// *****************************************************************************
// Configuration bits
// *****************************************************************************

// PIC24FJ256GB110 Configuration Bit Settings

// CONFIG3
#pragma config WPFP = WPFP511           // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable bit (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT oscillator mode selected)
#pragma config DISUVREG = ON            // Internal USB 3.3V Regulator Disable bit (Regulator is enabled)
#pragma config IOL1WAY = OFF            // IOLOCK One-Way Set Enable bit (Unlimited Writes To RP Registers)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSCO functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary oscillator (XT, HS, EC) with PLL module (XTPLL,HSPLL, ECPLL))
#pragma config PLL_96MHZ = ON           // 96MHz PLL Disable (Enabled)
#pragma config PLLDIV = DIV2            // USB 96 MHz PLL Prescaler Select bits (Oscillator input divided by 2 (8MHz input))
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-speed start-up)disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator functions are shared with PGEC2/PGED2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// *****************************************************************************
// System Settings and Variables
// *****************************************************************************
volatile uint32_t  tick = 0, prevTick;     // tick counter,


// *****************************************************************************
/*  Function:
    void SYSTEM_InitializeBoard(void)

    Summary:
        This function initializes the system board modules and
        peripheral ports.

    Description:
        This function initializes the system board modules and
        peripheral ports that is specific to the PIC device
        used in this configuration.

*/
// *****************************************************************************
void SYSTEM_InitializeBoard(void)
{
    const DRV_SPI_INIT_DATA SPI_Init_Data = {2, 3, 7, 0, SPI_BUS_MODE_3, 0};

    // ---------------------------------------------------------
    // Make sure the display DO NOT flicker at start up
    // ---------------------------------------------------------
    DisplayBacklightConfig();
    DisplayPowerConfig();
    DisplayBacklightOff();

    // ---------------------------------------------------------
    // mikroe Board
    // SPI-Flash Device pins
    // ---------------------------------------------------------
    // chip select pin
    TRISCbits.TRISC2 = 0;
    LATCbits.LATC2   = 1;
    // spi-clock pin
    TRISGbits.TRISG6 = 0;
    // spi-output pin
    TRISGbits.TRISG8 = 0;
    // spi-intput pin
    TRISGbits.TRISG7 = 1;


    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    // set SPI pins
    RPOR10bits.RP21R = 11;                  // assign RP21 for SCK2
    RPOR9bits.RP19R = 10;                   // assign RP19 for SDO2
    RPINR22bits.SDI2R = 26;                 // assign RP26 for SDI2

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    // ---------------------------------------------------------
    // Initialize the Display Driver
    // ---------------------------------------------------------
    DRV_GFX_Initialize();

    DRV_NVM_M25P80_Initialize((DRV_SPI_INIT_DATA*)&SPI_Init_Data);

    // initialize system tick counter
    SYSTEM_TickInit();

    // initialize the components for Resistive Touch Screen
    TouchInit(NVMWrite, NVMRead, NVMSectorErase, NULL);


}

// *****************************************************************************
/*  Function:
    void _USB1Interrupt(void)

    Summary:
        This function is the USB ISR for the application.

    Description:
        This function is the USB ISR for the application.

*/
// *****************************************************************************
#if defined(USB_INTERRUPT)
void __attribute__((interrupt,auto_psv)) _USB1Interrupt()
{
    USBDeviceTasks();
}
#endif

// *****************************************************************************
/*  Function:
    __T3_ISR _T3Interrupt(void)

    Summary:
        This function initializes the interrupt used for the tick timer
        of the demo.

    Description:
        This function initializes the interrupt used for the tick timer
        of the demo. This is also used to sample the resistive touch
        screen module.

*/
// *****************************************************************************
#define __T3_ISR    __attribute__((interrupt, shadow, auto_psv))
void __T3_ISR _T3Interrupt(void)
{
    tick++;

    TMR3 = 0;
    // Clear flag
    IFS0bits.T3IF = 0;
    TouchDetectPosition();
}

/*********************************************************************
 * Section: Tick Delay
 *********************************************************************/
#define SAMPLE_PERIOD   500 // us
#define TICK_PERIOD     (SYS_CLK_FrequencyPeripheralGet() * SAMPLE_PERIOD) / 4000000

// *****************************************************************************
/*  Function:
    void SYSTEM_TickInit(void)

    Summary:
        Initializes the tick timer of the demo.

    Description:
        This function initializes the tick timer of the demo.

*/
// *****************************************************************************
void SYSTEM_TickInit(void)
{
    // Initialize Timer3
    TMR3 = 0;
    PR3 = TICK_PERIOD;
    IFS0bits.T3IF = 0;  //Clear flag
    IEC0bits.T3IE = 1;  //Enable interrupt
    T3CONbits.TON = 1;  //Run timer

}

// *****************************************************************************
/*  Function:
    void SYSTEM_ProgramExternalMemory(void)

    Summary:
        Routine that programs the external memory used by the
        application.

    Description:
        This function programs the external memory on the system.
        Use the UART as the module to receive data to program the
        external memory.

*/
// *****************************************************************************
void SYSTEM_ProgramExternalMemory()
{
    // start the external memory programming
    ProgramExternalMemory(DataRead, DataWrite, DataChipErase);

    // delay the reset to have time for the acknowledge data to
    // be sent to the host side
    __delay_ms(100);

}

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_ExternalResourceCallback(
                                GFX_RESOURCE_HDR *pResource,
                                uint32_t offset,
                                uint16_t nCount,
                                void     *pBuffer)

    Summary:
        This function performs data fetch from external memory.

    Description:
        This function must be implemented in the application.
        The library will call this function each time when
        the external memory data will be required. The application
        must copy requested byte quantity into the buffer provided.
        Data start address in external memory is a sum of the address
        in GFX_RESOURCE_HDR structure and offset.

    Precondition:
        None.

    Parameters:
        pResource - Pointer to the external memory resource information.
        offset - offset of the data from the location of the resource
                 in external memory.
        nCount - Number of bytes to be transferred into the buffer.
        buffer - Pointer to the buffer that will hold the retrieved data.

    Returns:
        GFX_STATUS_SUCCESS when all the data was succesfully retrieved.
        GFX_STATUS_FAILURE when partial or no data was retrieved.

    Example:
        None.

*/
// *****************************************************************************
// If there are several memories in the system they can be selected by IDs.
// In this demo ID for memory chip installed on Graphics PICTail board is assumed to be 0.
#define M25P80_MEMORY    0
/* */

GFX_STATUS GFX_ExternalResourceCallback(
                                GFX_RESOURCE_HDR *pResource,
                                uint32_t offset,
                                uint16_t nCount,
                                void     *pBuffer)
{
    uint32_t addr;

    // get the proper address
    switch (pResource->type)
    {
        case GFX_RESOURCE_FONT_EXTERNAL_NONE:
            addr = pResource->resource.font.location.extAddress;
            break;
        case GFX_RESOURCE_MCHP_MBITMAP_EXTERNAL_RLE:
        case GFX_RESOURCE_MCHP_MBITMAP_EXTERNAL_NONE:
            addr = pResource->resource.image.location.extAddress;
            break;
        default:
            // type is incorrect
            return (GFX_STATUS_FAILURE);
    }
    addr += offset;

    if(pResource->ID == M25P80_MEMORY)
    {
        // Read data requested into buffer provided
        DRV_NVM_M25P80_Read(addr, (uint8_t*)pBuffer, nCount);
    }

    return (GFX_STATUS_SUCCESS);
}

