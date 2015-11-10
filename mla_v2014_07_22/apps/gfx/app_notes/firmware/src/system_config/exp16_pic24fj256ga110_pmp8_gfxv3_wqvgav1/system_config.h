/*******************************************************************************
  System Specific Definitions

  Company:
    Microchip Technology Inc.

  File Name:
    system.h

  Summary:
    System level definitions for the specific Microchip Development Board used.

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

#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H

/*********************************************************************
* PIC Device Specific includes
*********************************************************************/
#include "gfx_config.h"

#define USE_8BIT_PMP
#define GFX_USE_DISPLAY_CONTROLLER_SSD1926

/*********************************************************************
* DISPLAY PARAMETERS 
*********************************************************************/
/*
    The following are the parameters required for the 
    different display drivers that is supported.
    When adding support to a new display controller or display panel,
    follow the parameterization of the driver for reusability of the
    driver.

    Display Parameter Macros Descriptions:
    
    1. DISP_ORIENTATION - defines the display rotation with
            respect to its native orientation. For example, if the display 
            has a resolution specifications that says 240x320 (QVGA), the
            display is natively in portrait mode. If the application
            uses the display in landscape mode (320x240), then the 
            orientation musts be defined as 90 or 180 degree rotation.
            The Graphics Library will calculate the actual pixel location
            to rotate the contents of the screen. So when users view the 
            display, the image on the screen will come out in the correct
            orientation.
            
            Valid values: 0, 90, 180 and 270
            Example: #define DISP_ORIENTATION 90

    2. DISP_HOR_RESOLUTION - defines the horizontal dimension in pixels. This 
            is the native horizontal dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_HOR_RESOLUTION
            of 320.
            
            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_HOR_RESOLUTION 320 

    3. DISP_VER_RESOLUTION - defines the vertical dimension in pixels. This 
            is the native vertical dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_VER_RESOLUTION
            of 240.
            
            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_VER_RESOLUTION 240 

    4. COLOR_DEPTH - (NOTE: Define this macro in the GraphicsConfig.h 
             This defines the vertical dimension in pixels. 
            
            Valid Values: 1, 4, 8, 16, 24 (note 24 bpp is only used if you are 
                          using a Display Driver that supports 24 bpp color depth.
            Example: #define COLOR_DEPTH 16 

    5. DISP_DATA_WIDTH - this defines the display controller physical interface 
            to the display panel. 

            Valid Values: 1, 4, 8, 16, 18, 24 
                          1, 4, 8 are usually used in MSTN and CSTN displays
                          16, 18 and 24 are usually used in TFT displays.
            Example: #define DISP_DATA_WIDTH 18 
    
    6. DISP_INV_LSHIFT - this indicates that the color data is sampled in the
            falling edge of the pixel clock. 

            Example: #define DISP_INV_LSHIFT - define this to sample the
                          color data in the falling edge of the pixel clock.
    
    7. DISP_HOR_PULSE_WIDTH - this defines the horizontal sync signal pulse width. 

            Valid Values: See display panel data sheet                           
            Example: #define DISP_HOR_PULSE_WIDTH 25 
  
    8. DISP_VER_PULSE_WIDTH - this defines the vertical sync signal pulse width. 

            Valid Values: See display panel data sheet                           
            Example: #define DISP_VER_PULSE_WIDTH 4
            
    9. DISP_HOR_BACK_PORCH - this defines the horizontal back porch. 
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet                           
            Example: #define DISP_HOR_BACK_PORCH 5

    10. DISP_HOR_FRONT_PORCH - this defines the horizontal front porch. 
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet                           
            Example: #define DISP_HOR_FRONT_PORCH 10

    11. DISP_VER_BACK_PORCH - this defines the vertical back porch. 
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet                           
            Example: #define DISP_VER_BACK_PORCH 0

    12. DISP_VER_FRONT_PORCH - this defines the horizontal front porch. 
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet                           
            Example: #define DISP_VER_FRONT_PORCH 2
            
    13. GFX_LCD_TYPE - this defines the type of display glass used. 
            
            Valid Values: Dependent on the display controller supported LCD types.
                          GFX_LCD_TFT  // Type TFT Display 
                          GFX_LCD_CSTN // Type Color STN Display 
                          GFX_LCD_MSTN // Type Mono STN Display 
                          GFX_LCD_OLED // Type OLED Display

            Example: #define GFX_LCD_TYPE GFX_LCD_TFT

    14. GFX_DISPLAYENABLE_ENABLE - this enables the use of the Display Enable Port 
            (GEN) when using the Microchip Graphics Module. The signal required when 
            using a display panel that supports DATA ENABLE Mode. DATA ENABLE Mode 
            is used when the display panel do not have sync (HSYNC and VSYNC) signals.
            
            Example: #define GFX_DISPLAYENABLE_ENABLE

    15. GFX_DISPLAYENABLE_POLARITY - this sets the polarity of the Display Enable Port 
            (GEN) when using the Microchip Graphics Module. 
            
            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYENABLE_POLARITY GFX_ACTIVE_HIGH
            
    16. GFX_HSYNC_ENABLE - this enables the use of the Display Horizontal Synchronization 
            Port (HSYNC) when using the Microchip Graphics Module. The signal required when 
            using a display panel that supports SYNC Mode. SYNC Mode 
            is used when the display panel has sync (HSYNC and VSYNC) signals.
            
            Example: #define GFX_HSYNC_ENABLE

    17. GFX_HSYNC_POLARITY - this sets the polarity of the Display Horizontal Synchronization 
            Port (HSYNC)when using the Microchip Graphics Module. 
            
            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_HSYNC_POLARITY GFX_ACTIVE_LOW

    18. GFX_VSYNC_ENABLE - this enables the use of the Display Vertical Synchronization 
            Port (VSYNC) when using the Microchip Graphics Module. The signal required when 
            using a display panel that supports SYNC Mode. SYNC Mode 
            is used when the display panel has sync (HSYNC and VSYNC) signals.
            
            Example: #define GFX_VSYNC_ENABLE

    19. GFX_VSYNC_POLARITY - this sets the polarity of the Display Vertical Synchronization
            Port (VSYNC)when using the Microchip Graphics Module. 
            
            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_VSYNC_POLARITY GFX_ACTIVE_LOW

    20. GFX_DISPLAYPOWER_ENABLE - this enables the use of the Display Power Sequencer 
            Control Port (GPWR) when using the Microchip Graphics Module. The signal 
            can be used to control the display power circuitry. The Graphics Module
            can manage the powering up and powering down of the display since 
            power up and power down sequence in display panels is essential to 
            extend display life cycle.
            
            Example: #define GFX_DISPLAYPOWER_ENABLE
            
    21. GFX_DISPLAYPOWER_POLARITY - this sets the polarity of the Display Power Sequencer 
            Control Port (GPWR) when using the Microchip Graphics Module. 
            
            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYPOWER_POLARITY GFX_ACTIVE_HIGH
            
    22. GFX_CLOCK_POLARITY - this sets the polarity of the Display Glass Clock Port (GCLK) 
            when using the Microchip Graphics Module. 
            
            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_CLOCK_POLARITY GFX_ACTIVE_HIGH
            
    
    There are two major types of controllers enumerated here:
    1. Controllers in Smart Displays - these are display modules that have  
       built in display controller. Interface to the PIC device(s) 
       are usually through parallel interface or serial interface.
       
       Required parameters:
       #define DISP_ORIENTATION 
       #define DISP_HOR_RESOLUTION 
       #define DISP_VER_RESOLUTION 
       
    2. Controller that drives the RGB Glass directly - these are display 
       controllers that comes in a separate package or built into the
       microcontrollers.
    
       Required parameters:
       #define DISP_ORIENTATION 
       #define DISP_HOR_RESOLUTION 
       #define DISP_VER_RESOLUTION 
       #define DISP_DATA_WIDTH			
       #define DISP_HOR_PULSE_WIDTH    
       #define DISP_HOR_BACK_PORCH     
       #define DISP_HOR_FRONT_PORCH    
       #define DISP_VER_PULSE_WIDTH    
       #define DISP_VER_BACK_PORCH     
       #define DISP_VER_FRONT_PORCH    

       Optional parameters:       
       #define DISP_INV_LSHIFT

       When using Microchip Graphics Module (mchpGfxDrv) required parameters:
       #define GFX_DISPLAYENABLE_ENABLE
       #define GFX_DISPLAYENABLE_POLARITY          
       
       or 
       
       #define GFX_HSYNC_ENABLE
       #define GFX_VSYNC_ENABLE
       #define GFX_HSYNC_POLARITY                  
       #define GFX_VSYNC_POLARITY                  

       #define GFX_CLOCK_POLARITY                  

       When using Microchip Graphics Module (mchpGfxDrv) Optional parameters:       
       #define GFX_DISPLAYPOWER_ENABLE
       #define GFX_DISPLAYPOWER_POLARITY           
      
    
*/
// -----------------------------------
// For RGB GLASS
// -----------------------------------
// Using TFT_PH480272T_005_I11Q  Display Panel.

#define DISP_ORIENTATION                0
#define DISP_HOR_RESOLUTION             480
#define DISP_VER_RESOLUTION             272
#define DISP_DATA_WIDTH                 24
#define DISP_HOR_PULSE_WIDTH            41
#define DISP_HOR_BACK_PORCH             2
#define DISP_HOR_FRONT_PORCH            2
#define DISP_VER_PULSE_WIDTH            10
#define DISP_VER_BACK_PORCH             2
#define DISP_VER_FRONT_PORCH            2
#define GFX_LCD_TYPE                    GFX_LCD_TFT

// -----------------------------------
// Default font to be used in the demo
// -----------------------------------
#define APP_DEMO_FONT Gentium27

/*********************************************************************
* DISPLAY PARALLEL INTERFACE 
*********************************************************************/
/*
   Select the correct Parallel Master Port Interface Driver.
   This selection is valid only for parallel interface. When using
   display drivers that uses serial interface, this portion should be
   commented out or removed.
*/
#define USE_GFX_PMP

/*********************************************************************
* PARALLEL MASTER PORT INTERFACE TIMING 
*********************************************************************/
	// When using the Parallel Master Port (or Enhanced Parallel Master Port) the 
	// PMP timing must be defined for the following:
	// PMP_DATA_SETUP_TIME or EPMPCSx_DATA_SETUP (for DWAITB) 
	// PMP_DATA_WAIT_TIME or EPMPCSx_DATA_WAIT_TIME (for DWAITM) 
	// and PMP_DATA_HOLD_TIME or EPMPCSx_DATA_HOLD_TIME (for DWAITE)
    // where x is 1 or 2 (EPMP has 2 chip selects)
	// All values are timing parameters in ns.
	// The timing is dependent on the display controller sampling period if 
	// interfacing with the display controller or device AC timing requirements
	// if interfacing with a device (such as SRAM or Parallel Flash memory).
	// Refer to your specific display controller or device to determine the 
	// optimum (fastest) timing requirement for your interface. 

/*********************************************************************
* PARALLEL MASTER PORT INTERFACE TIMING AND POLARITIES
*********************************************************************/
/*
    This portion sets up the EPMP port timing when Graphics Module is
    used as a Alternate Master in EPMP (See Family Reference Manual (FRM)
    Section 42. Enhanced Parallel Master Port (EPMP)) for details.

    Macros to define the access timing of the parallel device in EPMP chip
	selects.  This value is used to calculate the AMWAIT cycles needed in EPMP
	Alternate Master I/Os direct access (EPMP bypass mode) (MSTSEL = 0x3).
	When in this mode the Alternate Master (in this case Graphics Module)
	will use the clock specified by the G1CLKSEL bits of CLKDIV register
	in the oscillator module. There are two possible values: 48 Mhz and
	96 Mhz. The equation used is:
	    temp = (1000000000ul) / ((CLKDIVbits.G1CLKSEL == 1)? 960000000ul : 480000000);

		if (EPMPCSx_ACCESS_TIME <= (temp*3))
		    PMCSxMDbits.AMWAIT = 0;
		else if (EPMPCSx_ACCESS_TIME > temp)
	    {
            PMCSxMDbits.AMWAIT = (EPMPCSx_ACCESS_TIME / temp);
            if ((EPMPCSx_ACCESS_TIME % temp) > 0)
                PMCSxMDbits.AMWAIT += 1;
        }

        where:
            x = 1 for CS1
            x = 2 for CS2
            the factor of 3 is used because of the fact that an AMWAIT of 0 means
            that 3 alternate master cycles are used per read/write.
            Actual cycles used is 3 + AMWAIT cycles per read/write access.

*/

#define PMP_DATA_SETUP_TIME                (18)    
#define PMP_DATA_WAIT_TIME                 (82)  // based on the minimum pulse width requirement of CS signal of SSD1926     
#define PMP_DATA_HOLD_TIME                 (0)    

/*********************************************************************
* HARDWARE PROFILE FOR DISPLAY CONTROLLER INTERFACE
*********************************************************************/
/* 
    The following defines the different IO signals used to connect
    to the display controller.
    The hardware profile used is dependent on the PIC device 
    and the development board used.
    
    The following are used to control the following signals to the
    Display Controller:
    1. Reset Signal - this signal controls the reset pin of the display
            controller if available.
            
            Example:
            #define DisplayResetConfig()        TRISAbits.TRISA4 = 0    
            #define DisplayResetEnable()        LATAbits.LATA4 = 0
            #define DisplayResetDisable()       LATAbits.LATA4 = 1

    2. Command/Data Signal - this signal indicates to the controller
            if the command or data is being sent to the display controller.

            Example:
            #define DisplayCmdDataConfig()      TRISAbits.TRISA1 = 0
            #define DisplaySetCommand()         LATAbits.LATA1 = 0
            #define DisplaySetData()            LATAbits.LATA1 = 1

    3. Controller Chip Select Signal - this signal controls the chip select
            pin of the display controller is available.

            Example:
            #define DisplayConfig()             TRISBbits.TRISB15 = 0             
            #define DisplayEnable()             LATBbits.LATB15 = 0
            #define DisplayDisable()            LATBbits.LATB15 = 1
            
    4. Display Module Power Control Signal - this signal turns on or off
            the display module if available. In some cases, this can be an 
            IO port that will enable the power circuitry of your 
            display module.

            Example:
            #define DisplayPowerConfig()        TRISAbits.TRISA5 = 0       
            #define DisplayPowerOn()            LATAbits.LATA5 = 1           
            #define DisplayPowerOff()           LATAbits.LATA5 = 0

    5. Display Backlight Brightness Control - this controls the backlight
            brightness or ON or OFF states if available. If brightness is 
            controllable, this signal may be driven by some PWM signal. 

            Example:
            #define DisplayBacklightConfig()    TRISDbits.TRISD0 = 0  
            #define DisplayBacklightOn()        LATDbits.LATD0 = 0
            #define DisplayBacklightOff()       LATDbits.LATD0 = 1               
    
*/

    // Depending on the display panel used, the backlight control may be
    // different. This portion sets up the correct backlight level to 
    // turn on or off the backlight.
#define BACKLIGHT_ENABLE_LEVEL      1
#define BACKLIGHT_DISABLE_LEVEL     0

/* When using the supported PIC24F devices
PIC24FJ128GA010
PIC24FJ256GA110
PIC24FJ256GB110
PIC24FJ256GB210
NOTE: PIC24FJ256DA210 is not on the list since
 this part has a built in display controller
 and it directly interfaces to the display
 panel.
*/

// Definitions for reset pin
#define DisplayResetConfig()        TRISCbits.TRISC1 = 0    
#define DisplayResetEnable()        LATCbits.LATC1 = 0
#define DisplayResetDisable()       LATCbits.LATC1 = 1

// Definitions for RS pin
#define DisplayCmdDataConfig()      TRISCbits.TRISC2 = 0
#define DisplaySetCommand()         LATCbits.LATC2 = 0
#define DisplaySetData()            LATCbits.LATC2 = 1

// Definitions for CS pin
#define DisplayConfig()             TRISDbits.TRISD10 = 0             
#define DisplayEnable()             LATDbits.LATD10 = 0
#define DisplayDisable()            LATDbits.LATD10 = 1

// Definitions for FLASH CS pin
#define DisplayFlashConfig()         
#define DisplayFlashEnable()        
#define DisplayFlashDisable()       

// Definitions for POWER ON pin
#define DisplayPowerConfig()        
#define DisplayPowerOn()            
#define DisplayPowerOff()           

// Definitions for backlight control pin
#define DisplayBacklightConfig()    (TRISDbits.TRISD0 = 0)  
#define DisplayBacklightOn()        (LATDbits.LATD0 = BACKLIGHT_ENABLE_LEVEL)
#define DisplayBacklightOff()       (LATDbits.LATD0 = BACKLIGHT_DISABLE_LEVEL)

/*********************************************************************
* HARDWARE PROFILE FOR TIMING CONTROLLER (TCON)
*********************************************************************/

//// Enable SPI channel 2
#define DRV_SPI_CONFIG_CHANNEL_2_ENABLE

// Enable SPI FIFO mode in parts where it is supported
// Enabling the FIFO mode will improve library performance.
// In this demo this definition is sometimes disabled because early versions of the PIC24FJ128GA010s have an errata preventing this feature from being used.
#if defined (__PIC24FJ128GA010__)
#define DRV_SPI_CONFIG_ENHANCED_BUFFER_DISABLE
#endif

#define SST25_CS_TRIS   TRISDbits.TRISD1
#define SST25_CS_LAT    LATDbits.LATD1

#define SST25_SCK_TRIS  TRISGbits.TRISG6
#define SST25_SDO_TRIS  TRISGbits.TRISG8
#define SST25_SDI_TRIS  TRISGbits.TRISG7

/*********************************************************************
* IOS FOR THE RESISTIVE TOUCHSCREEN
*********************************************************************/
// definitions for resistive touch screen
// ADC Input Channel Selector
#define TOUCH_ADC_INPUT_SEL   AD1CHS
// ADC Sample Start
#define TOUCH_ADC_START   AD1CON1bits.SAMP
// ADC Status
#define TOUCH_ADC_DONE   AD1CON1bits.DONE

// potentiometer and temperature sensors
#define ADC_TEMP        4
#define ADC_POT         5

// resistive touch screen analog pins
#define ADC_XPOS        11
#define ADC_YPOS        10

#define ADC_POT_PCFG    AD1PCFGbits.PCFG5
#define ADPCFG_XPOS     AD1PCFGbits.PCFG11
#define ADPCFG_YPOS     AD1PCFGbits.PCFG10

#define RESISTIVETOUCH_ANALOG  0
#define RESISTIVETOUCH_DIGITAL 1

// X port definitions
#define ResistiveTouchScreen_XPlus_Drive_High()         LATBbits.LATB11   = 1
#define ResistiveTouchScreen_XPlus_Drive_Low()          LATBbits.LATB11   = 0
#define ResistiveTouchScreen_XPlus_Config_As_Input()    TRISBbits.TRISB11 = 1
#define ResistiveTouchScreen_XPlus_Config_As_Output()   TRISBbits.TRISB11 = 0

#define ResistiveTouchScreen_XMinus_Drive_High()        LATDbits.LATD9    = 1
#define ResistiveTouchScreen_XMinus_Drive_Low()         LATDbits.LATD9    = 0
#define ResistiveTouchScreen_XMinus_Config_As_Input()   TRISDbits.TRISD9  = 1
#define ResistiveTouchScreen_XMinus_Config_As_Output()  TRISDbits.TRISD9  = 0

// Y port definitions
#define ResistiveTouchScreen_YPlus_Drive_High()         LATBbits.LATB10   = 1
#define ResistiveTouchScreen_YPlus_Drive_Low()          LATBbits.LATB10   = 0
#define ResistiveTouchScreen_YPlus_Config_As_Input()    TRISBbits.TRISB10 = 1
#define ResistiveTouchScreen_YPlus_Config_As_Output()   TRISBbits.TRISB10 = 0

#define ResistiveTouchScreen_YMinus_Drive_High()        LATDbits.LATD8    = 1
#define ResistiveTouchScreen_YMinus_Drive_Low()         LATDbits.LATD8    = 0
#define ResistiveTouchScreen_YMinus_Config_As_Input()   TRISDbits.TRISD8  = 1
#define ResistiveTouchScreen_YMinus_Config_As_Output()  TRISDbits.TRISD8  = 0


// Touch Screen Non-Volatile Memory Storage Macros

// Addresses for calibration and version values in SPI Flash on Graphics PICtail 3 & PIC24FJ256DA210 Development Board.
// Or Addresses for calibration and version values in Parallel Flash on PIC24FJ256DA210 Development Board.

#define ADDRESS_RESISTIVE_TOUCH_VERSION	(unsigned long)0xFFFFFFFE
#define ADDRESS_RESISTIVE_TOUCH_ULX     (unsigned long)0xFFFFFFFC
#define ADDRESS_RESISTIVE_TOUCH_ULY     (unsigned long)0xFFFFFFFA
#define ADDRESS_RESISTIVE_TOUCH_URX     (unsigned long)0xFFFFFFF8
#define ADDRESS_RESISTIVE_TOUCH_URY     (unsigned long)0xFFFFFFF6

#define ADDRESS_RESISTIVE_TOUCH_LLX     (unsigned long)0xFFFFFFF4
#define ADDRESS_RESISTIVE_TOUCH_LLY     (unsigned long)0xFFFFFFF2
#define ADDRESS_RESISTIVE_TOUCH_LRX     (unsigned long)0xFFFFFFF0
#define ADDRESS_RESISTIVE_TOUCH_LRY     (unsigned long)0xFFFFFFEE

// define the functions to call for the non-volatile memory
// check out touch screen module for definitions of the following function pointers
// used: NVM_READ_FUNC, NVM_WRITE_FUNC & NVM_SECTORERASE_FUNC
#define NVMSectorErase                  ((NVM_SECTORERASE_FUNC)&DRV_NVM_SST25VF016_SectorErase)
#define NVMWrite                        ((NVM_WRITE_FUNC      )&DRV_NVM_SST25VF016_Write)
#define NVMRead                         ((NVM_READ_FUNC       )&DRV_NVM_SST25VF016_Read)

// touch screen font definition
#define DRV_TOUCHSCREEN_FONT Gentium27

/*********************************************************************
* EXPLORER 16 EEPROM
*********************************************************************/
// The MCHP25LC256 chip select signal, even if not used must be
// driven to high so it does not interfere with other SPI peripherals
// that uses the same SPI signals.
#define MCHP25LC256_CS_TRIS  TRISDbits.TRISD12
#define MCHP25LC256_CS_LAT   LATDbits.LATD12

/*********************************************************************
* IOS FOR THE SWITCHES (SIDE BUTTONS)
*********************************************************************/
// buttons
#define HardwareButtonInit()
#define GetHWButtonProgram()                (PORTDbits.RD7)
#define GetHWButtonUseInternalResource()    (PORTDbits.RD6)
#define GetHWButtonScanDown()               (PORTDbits.RD13)
#define GetHWButtonScanUp()                 (PORTAbits.RA7)
#define GetHWButtonCR()                     (PORTDbits.RD6)
#define GetHWButtonFocus()                  (PORTDbits.RD7)

/*********************************************************************
* HARDWARE PROFILE for UART to program external memory
*********************************************************************/

#define DataChipErase                  ((FLASH_CHIPERASE_FUNC)&DRV_NVM_SST25VF016_ChipErase)
#define DataWrite                      ((FLASH_WRITE_FUNC    )&DRV_NVM_SST25VF016_Write)
#define DataRead                       ((FLASH_READ_FUNC     )&DRV_NVM_SST25VF016_Read)

#define USE_COMM_PKT_MEDIA_SERIAL_PORT
#define COMM_PKT_RX_MAX_SIZE    (1024)

#define DRV_UART2_CONFIG_BAUD_RATE    115200ul

#define DRV_UART2_TX_BYTEQ_LENGTH 1
#define DRV_UART2_RX_BYTEQ_LENGTH 1

#endif 




