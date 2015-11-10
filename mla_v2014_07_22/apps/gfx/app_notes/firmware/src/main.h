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

#ifndef _MAIN_H
    #define _MAIN_H

#include <stdint.h>

// *****************************************************************************
// Object ID's
// *****************************************************************************
#define ID_ICON1            0xF010
#define ID_ICON2            0xF011
#define ID_ICON3            0xF012
#define ID_ICON4            0xF013
#define ID_BACK             0xF050

#define ID_SELECT_INTERNAL  0x0AA0
#define ID_SELECT_EXTERNAL  0x0AA1
#define ID_SELECT_PROGRAM   0x0AA2

// *****************************************************************************
// Object Dimensions
// *****************************************************************************
// main screen icons dimensions
#define ICON_WIDTH          (85)
#define ICON_HEIGHT         (85)
#define ICON_COLUMNSNUM     (2)
#define ICON_ROWSNUM        (2)
#define ICON_XINDENT        ((GFX_MaxXGet() - ICON_COLUMNSNUM * ICON_WIDTH) / (ICON_COLUMNSNUM + 1))
#define ICON_YINDENT        ((GFX_MaxYGet() - ICON_ROWSNUM * ICON_HEIGHT) / (ICON_ROWSNUM + 1))
#define IconTop(row)        (((row + 1) * ICON_YINDENT) + (row * ICON_HEIGHT))
#define IconBottom(row)     ((row + 1) * (ICON_YINDENT + ICON_HEIGHT))
#define IconLeft(column)    (((column + 1) * ICON_XINDENT) + (column * ICON_WIDTH))
#define IconRight(column)   ((column + 1) * (ICON_XINDENT + ICON_WIDTH))

// startup selection screen button dimensions
#define SELECT_WIDTH        (130)
#define SELECT_HEIGHT       (60)
#define SELECT_COLUMNSNUM   (1)
#define SELECT_ROWSNUM      (3)
#define SELECT_XINDENT      ((GFX_MaxXGet() - SELECT_COLUMNSNUM * SELECT_WIDTH) / (SELECT_COLUMNSNUM + 1))
#define SELECT_YINDENT      ((GFX_MaxYGet() - SELECT_ROWSNUM * SELECT_HEIGHT) / (SELECT_ROWSNUM + 1))
#define SelectTop(row)      (((row + 1) * SELECT_YINDENT) + (row * SELECT_HEIGHT))
#define SelectBottom(row)   ((row + 1) * (SELECT_YINDENT + SELECT_HEIGHT))
#define SelectLeft(column)  (((column + 1) * SELECT_XINDENT) + (column * SELECT_WIDTH))
#define SelectRight(column) ((column + 1) * (SELECT_XINDENT + SELECT_WIDTH))

#define APP_TRANSPARENT_COLOR    GFX_RGBConvert(0xf9, 0x69, 0xe9)

#define APP_GENERIC_FONT    Gentium27
//#define APP_GENERIC_SCHEME  GOLSchemeDefault

#define APP_SS_TIMEOUT      100000


// *****************************************************************************
// Demo States
// *****************************************************************************
typedef enum
{
    CREATE_SELECTMENU = 0,
    DISPLAY_SELECTMENU,
    DISPLAY_INTERNAL_MESSAGE,
    DISPLAY_INTERNAL_MESSAGE_DELAY,
    DISPLAY_EXTERNAL_MEMORY_CHECK,
    DISPLAY_EXTERNAL_PROGRAMMING,
    CREATE_BACKGROUND,
    CREATE_MAINMENU,
    DISPLAY_MAINMENU,
    CREATE_AN1136,
    DISPLAY_AN1136,
    CREATE_AN1182,
    DISPLAY_AN1182,
    CREATE_AN1227,
    DISPLAY_AN1227,
    CREATE_AN1246,
    DISPLAY_AN1246,
    TRANSITION_STATE_HIDE_OBJECTS,
    TRANSITION_STATE_FREE_OBJECTS,
} APP_SCREEN_STATES;

// *****************************************************************************
// Data Types for demo
// *****************************************************************************
typedef struct
{
    uint16_t            left;
    uint16_t            top;
    uint16_t            width;
    uint16_t            height;
    GFX_RESOURCE_HDR    *pImage;
} APP_BACKGROUND_INFO;

// *****************************************************************************
// Application Variables
// *****************************************************************************
extern APP_BACKGROUND_INFO backgroundInfo;
extern bool                backgroundImageisSmallerThanScreen;
extern uint32_t            tick, prevTick;     // tick counter,


// *****************************************************************************
/*  Function:
    uint16_t APP_CreateBackButton(void)

    Summary:
        Function that creates the back button for the following sub-demo:
        - AN1136
        - AN1182
        - AN1227

    Parameters:
        None.

    Returns:
        0 - when the objects are not created.
        1 - when the objects are created.

*/
// *****************************************************************************
uint16_t APP_CreateBackButton(void);
  

#endif
