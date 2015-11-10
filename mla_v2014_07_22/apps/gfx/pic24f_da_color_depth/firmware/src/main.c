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

// *****************************************************************************
// Section: Includes
// *****************************************************************************
#include "system.h"
#include "gfx/gfx.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "driver/touch_screen/drv_touch_screen.h"

// *****************************************************************************
// Local Prototypes
// *****************************************************************************

/* Required callback functions (note: function name can be any name since
   the callbacks are initialized using:
   - GFX_GOL_MessageCallbackSet(function_name);
   - GFX_GOL_DrawCallbackSet(function_name);
 */
bool APP_ObjectMessageCallback(
                                GFX_GOL_TRANSLATED_ACTION objectMessage,
                                GFX_GOL_OBJ_HEADER *pObject,
                                GFX_GOL_MESSAGE *pMessage);
bool APP_ObjectDrawCallback(void);

/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////
void BoardInit(void);
void TickInit(void);                                        // starts tick counter
void GraphicsInit();

/////////////////////////////////////////////////////////////////////////////
//                            DEMO STATES
/////////////////////////////////////////////////////////////////////////////
typedef enum
{
    CREATE_SCREEN1 = 0,             // create screen 1 components with screen 1 palette
    DISPLAY_SCREEN1,                // display screen 1
    CREATE_SCREEN2,                 // create screen 2 components with screen 2 palette
    DISPLAY_SCREEN2,                // display screen 2
    HIDE_SCREEN,                    // state to disable the displat or turn the screen to BLACK
    SHOW_SCREEN,                    // state to enable the display
} SCREEN_STATES;

/////////////////////////////////////////////////////////////////////////////
//                       GLOBAL VARIABLES FOR DEMO
/////////////////////////////////////////////////////////////////////////////

const GFX_GOL_OBJ_SCHEME demoScheme =
                    {
                        0, 1,                   // emboss colors
                        0, 1, 0,                // text colors
                        0, 1, 0,                // generic colors
                        (GFX_RESOURCE_HDR *)&DEMO_FONT,             // font
                        GFX_FILL_STYLE_NONE,    // fill style
                        0, 0, 0,                // common background info
                        GFX_BACKGROUND_NONE,
                        NULL,
                        1                       // emboss
                    };

SCREEN_STATES       screenState = HIDE_SCREEN;              // current state of demo state machine
SCREEN_STATES       targetScreenState = CREATE_SCREEN1;     // indicates which screen to show after enabling back the display
GFX_GOL_OBJ_SCHEME  *pDemoScheme;                           // style scheme used

/*******************************************************************************
    Main
*******************************************************************************/
int main(void)
{
    // GOL message structure to interact with GOL
    GFX_GOL_MESSAGE msg;

    // Initialize board, drivers and graphics library
    SYSTEM_InitializeBoard();
    GFX_Initialize();

    // set the palette color depth and initialize the palette used
    GFX_PaletteSet(
            (void*)&SCR1_PALETTE,
            0,
            SCR1_PALETTE.resource.palette.numberOfEntries);

    // set the message callback function pointer
    GFX_GOL_MessageCallbackSet(APP_ObjectMessageCallback);
    // set the draw callback function pointer
    GFX_GOL_DrawCallbackSet(APP_ObjectDrawCallback);

    // clear the screen with the given color
    GFX_ColorSet(BLACK);
    GFX_ScreenClear();

    pDemoScheme = (GFX_GOL_OBJ_SCHEME*)&demoScheme;
    
    // turn on the backlight
    DisplayBacklightOn();

    while(1)
    {
        // Draw GOL objects
        if(GFX_GOL_ObjectListDraw() == GFX_STATUS_SUCCESS)
        {

            TouchGetMsg(&msg);              // Get message from touch screen
            GFX_GOL_ObjectMessage(&msg);    // Process message

        }
    }

}

// *****************************************************************************
/*  Function:
    bool APP_ObjectMessageCallback(
                                GFX_GOL_TRANSLATED_ACTION objectMessage,
                                GFX_GOL_OBJ_HEADER *pObject,
                                GFX_GOL_MESSAGE *pMessage)

    Summary:
        Required application layer function. GFX_GOL_ObjectMessage()
        function calls this function each time a valid message for the
        object is received. See GFX_GOL_MessageCallbackSet()
        documentation in the Graphics Library Help file for details.

    Parameters:
        objectMessage - translated message for the object,
        pObject - pointer to the object,
        pMessage - pointer to the non-translated, raw GOL message

    Returns:
        true  - The message will be processed using default settings
        false - The message will not be processed by object layer
                and application may or may not process the message.

*/
// *****************************************************************************
bool APP_ObjectMessageCallback(
                                GFX_GOL_TRANSLATED_ACTION objectMessage,
                                GFX_GOL_OBJ_HEADER *pObject,
                                GFX_GOL_MESSAGE *pMessage)
{

    // process messages for demo screens
    switch(screenState)
    {
        case DISPLAY_SCREEN1:

            if (GFX_GOL_ObjectIDGet(pObject) == SCR1_BTNID)
            {
                if(objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED)
                {
                    screenState = HIDE_SCREEN;
                    targetScreenState = CREATE_SCREEN2;
                }
            }
            break;

        case DISPLAY_SCREEN2:
            if (GFX_GOL_ObjectIDGet(pObject) == SCR2_BTNID)
            {
                if(objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED)
                {
                    screenState = HIDE_SCREEN;
                    targetScreenState = CREATE_SCREEN1;
                }
            }
            break;

        default:
            break;
    }


    return true;
}

// *****************************************************************************
/*  Function:
    bool APP_ObjectDrawCallback(void)

    Summary:
        Required application layer function. GFX_GOL_ObjectListDraw()
        function calls it each time when object layer drawing is completed.
        User drawing should be done here. See GFX_GOL_DrawCallbackSet()
        documentation in the Graphics Library Help file for details.

    Parameters:
        None.

    Returns:
        true  - When rendering control will be passed back to object layer
                rendering of the Graphics Library.
        false - When rendering control stays with the application.
                Do this when application needs more time to render.

*/
// *****************************************************************************
bool APP_ObjectDrawCallback(void)
{

   switch(screenState)
    {
        case CREATE_SCREEN1:

            GFX_GOL_ObjectListFree();

            GFX_FontSet((void*)&DEMO_FONT);
            GFX_ColorSet(TEXT_COLOR);
            GFX_TextStringDraw(TEXT_POSX, TEXT_POSY, LABEL_TEXT, 0);

            GFX_PaletteSet(
                    (void*)&SCR1_PALETTE,
                    0,
                    SCR1_PALETTE.resource.palette.numberOfEntries);


            // Note: The style scheme set to the button is not used
            //       since the button is set to have no panel
            GFX_GOL_ButtonCreate(  SCR1_BTNID,
                        SCR1_BTNX, SCR1_BTNY,
                        SCR1_BTNX + BTN_WIDTH,
                        SCR1_BTNY + BTN_HEIGHT, 0,
                        GFX_GOL_BUTTON_DRAW_STATE |
                        GFX_GOL_BUTTON_NOPANEL_STATE,
                        SCR1_BTN_IMAGE_PRESSED,
                        SCR1_BTN_IMAGE,
                        NULL, 0, pDemoScheme);

            GFX_GOL_PictureControlCreate( SCR1_PICTID,
                        SCR1_PICTX, SCR1_PICTY,
                        SCR1_PICTX + PICT_WIDTH,
                        SCR1_PICTY + PICT_HEIGHT,
                        GFX_GOL_PICTURECONTROL_DRAW_STATE,
                        1, SCR1_IMAGE, pDemoScheme);

            screenState = SHOW_SCREEN;
            targetScreenState = DISPLAY_SCREEN1;
            break;

        case CREATE_SCREEN2:
            GFX_GOL_ObjectListFree();

            GFX_PaletteSet(
                    (void*)&SCR2_PALETTE,
                    0,
                    SCR2_PALETTE.resource.palette.numberOfEntries);

            // Note: The style scheme set to the button is not used
            //       since the button is set to have no panel
            GFX_GOL_ButtonCreate(  SCR2_BTNID,
                        SCR2_BTNX, SCR2_BTNY,
                        SCR2_BTNX + BTN_WIDTH,
                        SCR2_BTNY + BTN_HEIGHT, 0,
                        GFX_GOL_BUTTON_DRAW_STATE |
                        GFX_GOL_BUTTON_NOPANEL_STATE,
                        SCR2_BTN_IMAGE_PRESSED,
                        SCR2_BTN_IMAGE,
                        NULL, 0, pDemoScheme);

            GFX_GOL_PictureControlCreate( SCR2_PICTID,
                        SCR2_PICTX, SCR2_PICTY,
                        SCR2_PICTX + PICT_WIDTH,
                        SCR2_PICTY + PICT_HEIGHT,
                        GFX_GOL_PICTURECONTROL_DRAW_STATE,
                        1, SCR2_IMAGE, pDemoScheme);

            screenState = SHOW_SCREEN;
            targetScreenState = DISPLAY_SCREEN2;
            break;

        case HIDE_SCREEN:

            // this turns on the TEST Mode in the graphics module where the data sent
            // to the screen is all BLACK color data
            SetBlackScreen();
            screenState = targetScreenState;
            break;

        case SHOW_SCREEN:
            SetNormalScreen();
            screenState = targetScreenState;
            break;

        case DISPLAY_SCREEN1:
        case DISPLAY_SCREEN2:
            break;

        default:
            break;
    }

    return true;
}






