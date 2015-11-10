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

#include <string.h>
#include "xc.h"
#include "system.h"
#include "gfx/gfx.h"
#include "main.h"
#include "an1227_demo.h"

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define BUTTON1_ID  1111                // button unique ID
#define BUTTON2_ID  2222                // button unique ID
#define BUTTON3_ID  3333                // button unique ID
    
#define BUTTON_WIDTH        (100)
#define BTN_X_START         ((GFX_MaxXGet() - BUTTON_WIDTH) >> 1)
#define BTN_X_END           (BTN_X_START + BUTTON_WIDTH)
    
const GFX_XCHAR  ReleaseStr[] = {'R','e','l','e','a','s','e','d',0};
const GFX_XCHAR  PressStr[] = {'P','r','e','s','s','e','d',0};
const GFX_XCHAR  Button2Str[] = {'B','u','t','t','o','n',' ','2',0};
const GFX_XCHAR  DisabledStr[] = {'D','i','s','a','b','l','e','d',0};

GFX_GOL_OBJ_SCHEME  AN1227Scheme;       // style scheme

// message for the button presses
GFX_GOL_MESSAGE AN1227msg;                        
    
// filled by the keyboard driver and
// passed to the message manager
GFX_GOL_OBJ_HEADER *pFocusedObj;        // temporary variable for the widget

// receiving the keyboard focus
uint8_t previousKey1State;              // previous state of the button 1
uint8_t previousKey2State;              // previous state of the button 2

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t APP_CreateAN1227(void)
// Input: None
// Output: Returns non-zero if the objects are created 
//         returns 0 when one of the objects was not created.
// Overview: Creates the AN1227 Demo screen.
/////////////////////////////////////////////////////////////////////////////
uint16_t APP_CreateAN1227(void)
{

    // ///////////////////////////////////////
    // initialize style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeTextColorSet(
                            &AN1227Scheme,
                            BRIGHTBLUE,
                            GFX_RGBConvert(0xFF, 0xFF, 0xFF),
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &AN1227Scheme,
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            GFX_RGBConvert(0x26, 0xC7, 0xF2),
                            GFX_RGBConvert(150, 150, 150));


    GFX_GOL_SchemeEmbossSet(&AN1227Scheme,
                            GFX_RGBConvert(0x2B, 0x55, 0x87),
                            GFX_RGBConvert(0xD4, 0xE4, 0xF7),
                            0);

    GFX_GOL_SchemeBackgroundColorSet(
                            &AN1227Scheme,
                            GFX_RGBConvert(0xD4, 0xED, 0xF7));

    GFX_GOL_SchemeFontSet(
                            &AN1227Scheme,
                            (GFX_RESOURCE_HDR*)&APP_DEMO_FONT);

    GFX_GOL_SchemeBackgroundImageSet(
                            &AN1227Scheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &AN1227Scheme,
                            GFX_BACKGROUND_IMAGE);

#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)
    if (backgroundImageisSmallerThanScreen == false)
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1227Scheme,
                            GFX_FILL_STYLE_ALPHA_COLOR);
        GFX_GOL_SchemeAlphaPrecentSet(&AN1227Scheme, 50);

    }
    else
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1227Scheme,
                            GFX_FILL_STYLE_COLOR);
    }

#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeGradientColorSet(
                            &AN1227Scheme,
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            GFX_RGBConvert(0x26, 0xC7, 0xF2));
    GFX_GOL_SchemeFillStyleSet(
                            &AN1227Scheme,
                            GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
#else
    GFX_GOL_SchemeFillStyleSet(
                            &AN1227Scheme,
                            GFX_FILL_STYLE_COLOR);
#endif



    // APP_HardwareButtonInit() to initialize the hardware buttons
    // should be called prior to the call to this function.
    
    /**
     * Carriage Return button
     * Explorer 16 + GFX PICTail    - S3 (8 bit PMP)
     * Explorer 16 + GFX PICTail    - S5 (16 bit PMP)
     * Starter Kit + GFX PICTail    - S0 (8 bit PMP)
     * DA210 Developement Board     - S1
     **/
    previousKey1State = GetHWButtonCR();  // previous state equals the current state
    /**
     * Change Focus button
     * Explorer 16 + GFX PICTail    - S6 (8 bit PMP)
     * DA210 Developement Board     - S2 or S3
     **/
    previousKey2State = GetHWButtonFocus(); // previous state equals the current state

    // create button widgets
    if (!GFX_GOL_ButtonCreate (
        BUTTON1_ID,             // button unique ID
        BTN_X_START, 40,        // left, top corner coordinates
        BTN_X_END, 90,          // right, bottom corner
        0,                      // corner radius is zero, a square button
        GFX_GOL_BUTTON_DRAW_STATE,               // will be dislayed after creation
        NULL, NULL,             // no bitmap
        (GFX_XCHAR*)ReleaseStr, // text for released state
        GFX_ALIGN_HCENTER|GFX_ALIGN_VCENTER,
        (GFX_GOL_OBJ_SCHEME*)&AN1227Scheme
    ))
        return 0;

    if (!GFX_GOL_ButtonCreate (
        BUTTON2_ID,             // button unique ID
        BTN_X_START, 100,       // left, top corner coordinates
        BTN_X_END, 150,         // right, bottom corner
        0,                      // corner radius is zero, a square button
        GFX_GOL_BUTTON_DRAW_STATE,               // will be dislayed after creation
        NULL, NULL,             // no bitmap
        (GFX_XCHAR*)Button2Str, // text
        GFX_ALIGN_HCENTER|GFX_ALIGN_VCENTER,
        &AN1227Scheme
    ))
        return 0;

    if (!GFX_GOL_ButtonCreate (
        BUTTON3_ID,             // button unique ID
        BTN_X_START, 160,       // left, top corner coordinates
        BTN_X_END, 210,         // right, bottom corner
        0,                      // corner radius is zero, a square button
        GFX_GOL_BUTTON_DRAW_STATE |
        GFX_GOL_BUTTON_DISABLED_STATE,           // will be dislayed and disabled after creation
        NULL, NULL,             // no bitmap
        (GFX_XCHAR*)DisabledStr,// text
        GFX_ALIGN_HCENTER|GFX_ALIGN_VCENTER,
        &AN1227Scheme
    ))
        return 0;

    pFocusedObj = NULL;                 // there are no widgets in focus
    
    return (1);
}       

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_MsgAN1227Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns true the message will be processed
//         by default
// Overview: This is called by GOLMsgCallback() to determine if 
//           a valid message for objects in this demo needs to be processed.
/////////////////////////////////////////////////////////////////////////////
bool APP_MsgAN1227Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObject, GFX_GOL_MESSAGE *pMsg)
{
    // Application should process messages here
    if(GFX_GOL_ObjectIDGet(pObject) == BUTTON1_ID)                // if the button with BUTTON_ID is receiving the message
    {
        if(objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
        {
            GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *)pObject, (GFX_XCHAR*)PressStr);  // set text for pressed state
        }

        if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
        {
            GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *)pObject, (GFX_XCHAR*)ReleaseStr); // set text for released state
        }
    }

    return (true); // process the message by default
}               

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_DrawAN1227Callback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: GOLDrawCallback() calls this function for demo specific drawing 
//           requirements.
/////////////////////////////////////////////////////////////////////////////
bool APP_DrawAN1227Callback(void)
{
    return (true);
}               

void APP_AN1227ProcessKeyBoard(void)
{

    // ***************
    // Keyboard driver
    // ***************

    // if there is a widget in focus send a message
    if(GFX_GOL_ObjectFocusGet() != NULL)
    {

        // check if the button has changed its state
        if(GetHWButtonCR() != previousKey1State)
        {
            if(previousKey1State)
            {

                // if GetHWButtonCR equals zero it means the button is pressed
                AN1227msg.type = TYPE_KEYBOARD;
                AN1227msg.uiEvent = EVENT_KEYSCAN;

                // the focused button will receive the message
                AN1227msg.param1 = GFX_GOL_ObjectIDGet(GFX_GOL_ObjectFocusGet());
                AN1227msg.param2 = SCAN_CR_PRESSED;

            }
            else
            {

                // if GetHWButtonCR equals one it means the button is released
                AN1227msg.type = TYPE_KEYBOARD;
                AN1227msg.uiEvent = EVENT_KEYSCAN;

                // the focused button will receive the message
                AN1227msg.param1 = GFX_GOL_ObjectIDGet(GFX_GOL_ObjectFocusGet());
                AN1227msg.param2 = SCAN_CR_RELEASED;
            }                   // end of else

            // state of the button was changed
            previousKey1State = !previousKey1State;

            // pass the message to the graphics library
            GFX_GOL_ObjectMessage(&AN1227msg);
        }                       // end of if
    }                           // end of if

    // check if the button has changed its state
    if(GetHWButtonFocus() != previousKey2State)
    {
        if(previousKey2State)
        {

            // if GetHWButtonFocus() equals zero it means the button is pressed
            // get the object can be focused next
            pFocusedObj = GFX_GOL_ObjectFocusNextGet();

            // move focus
            GFX_GOL_ObjectFocusSet(pFocusedObj);
        }
        else
        {

            // if GetHWButtonFocus()equals one it means the button is released
        }   // end of else

        // state of the button was changed
        previousKey2State = !previousKey2State;

        // pass the message to the graphics library
        GFX_GOL_ObjectMessage(&AN1227msg);
    } // end of if
}         

