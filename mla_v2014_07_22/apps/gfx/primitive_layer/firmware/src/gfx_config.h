/*******************************************************************************
 Module for Microchip Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    graphics_config.h

  Summary:
    This header file defines the Graphics Library configurations
    that are enabled. 
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

#ifndef _GRAPHICS_CONFIG_H
    #define _GRAPHICS_CONFIG_H

//////////////////// COMPILE OPTIONS ////////////////////

/*********************************************************************
  Overview: Blocking and Non-Blocking configuration selection.
            Non-Blocking is enabled by default. To disable the
            non-blocking feature, this macro must be enabled.

  GFX_CONFIG_NONBLOCKING_DISABLE
********************************************************************/
//#define GFX_CONFIG_NONBLOCKING_DISABLE

/*********************************************************************
  Overview: To disable support for Alpha Blending.
            Alpha blending is feature available to certain fill
            functions.

  GFX_CONFIG_ALPHABLEND_DISABLE
*********************************************************************/
//#define GFX_CONFIG_ALPHABLEND_DISABLE

/*********************************************************************
  Overview: Filling of shapes can be optionally set to fill with
            gradient colors. This feature is by default enabled.
            To disable this feature to reduce code size, define
            this macro at build time.

  GFX_CONFIG_GRADIENT_DISABLE
*********************************************************************/
//#define GFX_CONFIG_GRADIENT_DISABLE

/*********************************************************************
  Overview: Using Palettes, different colors can be used with the same
            bit depth.

  GFX_CONFIG_PALETTE_DISABLE
********************************************************************/
#define GFX_CONFIG_PALETTE_DISABLE

/*********************************************************************
  Overview: Palettes can also be specified to reside in external memory
            similar to fonts and images. Use this when the palette is
            located in external memory.

  GFX_CONFIG_PALETTE_EXTERNAL_DISABLE
********************************************************************/
#define GFX_CONFIG_PALETTE_EXTERNAL_DISABLE

/*********************************************************************
  Overview: To enable support for unicode fonts, GFX_CONFIG_FONT_CHAR_SIZE
            must be defined as 16 (size is 16 bits). For standard ascii
            fonts, this can be defined as 8. This changes the
            GFX_XCHAR definition. See GFX_XCHAR for details.

  GFX_CONFIG_FONT_CHAR_SIZE
*********************************************************************/
#define GFX_CONFIG_FONT_CHAR_SIZE 8

/*********************************************************************
  Overview: Font data can be placed in multiple locations. They can be
            placed in FLASH memory, RAM and external memory.
            To reduce code size, any one of these locations, when not
            used, can be disabled by defining the macros at build time.
            - GFX_CONFIG_FONT_FLASH_DISABLE - Disable font in internal
                                              flash memory support.
            - GFX_CONFIG_FONT_EXTERNAL_DISABLE - Disable font in
                                              external memory support.
            - GFX_CONFIG_FONT_RAM_DISABLE - Disable font in RAM
                                            support.
*********************************************************************/
//#define GFX_CONFIG_FONT_FLASH_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_FONT_RAM_DISABLE

/*********************************************************************
  Overview: Images can be placed in multiple locations. They can be
            placed in FLASH memory, RAM and external memory.
            To reduce code size, any one of these locations, when not
            used, can be disabled by defining the macros at build time.
            - GFX_CONFIG_IMAGE_FLASH_DISABLE - Disable images in internal
                                               flash memory support.
            - GFX_CONFIG_IMAGE_EXTERNAL_DISABLE - Disable images in
                                                  external memory support.
            - GFX_CONFIG_IMAGE_RAM_DISABLE - Disable images in RAM
                                             support.
*********************************************************************/
//#define GFX_CONFIG_IMAGE_FLASH_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
#define GFX_CONFIG_IMAGE_RAM_DISABLE

/*********************************************************************
  Overview: Specifies the color depth used in the demo.

  GFX_CONFIG_COLOR_DEPTH
*********************************************************************/
#define GFX_CONFIG_COLOR_DEPTH 16

/*********************************************************************
  Overview: To disable support for double buffering. Use this feature only
            if the display driver used can support double buffering.

  GFX_CONFIG_DOUBLE_BUFFERING_DISABLE
*********************************************************************/
#define GFX_CONFIG_DOUBLE_BUFFERING_DISABLE

/*********************************************************************
  Overview: Images with 8 and 4 BPP color depths can be optionally
            compressed with RLE. This feature is by default enabled.
            To disable this feature to reduce code size if none of the
            images are compressed with RLE, define this macro at
            build time.

  GFX_CONFIG_RLE_DECODE_DISABLE
*********************************************************************/
//#define GFX_CONFIG_RLE_DECODE_DISABLE

/*********************************************************************
  Overview: When using PIC24FJ256DA210, IPU compression can be
            enabled for images.This feature is by default enabled.
            To disable this feature to reduce code size if none of the
            images are compressed with IPU, define this macro at
            build time.

  GFX_CONFIG_IPU_DECODE_DISABLE
*********************************************************************/
//#define GFX_CONFIG_IPU_DECODE_DISABLE


#endif // _GRAPHICS_CONFIG_H
