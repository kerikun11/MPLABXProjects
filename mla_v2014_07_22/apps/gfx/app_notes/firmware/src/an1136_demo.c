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
#include "an1136_demo.h"
#include "internal_resource_an1136.h"

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define ID_BTN1                 10
#define ID_BTN2                 11
#define ID_SLD1                 20
#define ID_GB                   30

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT DIMENSIONS
/////////////////////////////////////////////////////////////////////////////

#define SLDR_XSTART             30
#define SLDR_YSTART             105
#define SLDR_WIDTH              (GFX_MaxXGet()-(SLDR_XSTART<<1))
#define SLDR_HEIGHT             45
#define SLDR_MAX_VALUE          100

#define BTN_WIDTH               120
#define BTN_YSTART		160
#define BTN1_XSTART		SLDR_XSTART
#define BTN2_XSTART		(SLDR_XSTART + SLDR_WIDTH) - BTN_WIDTH
#define BTN_HEIGHT		42

#define BAR_4A_CONSTANT         160

#define BAR_XSTART		((GFX_MaxXGet()-200) >> 1)
#define BAR_XEND                (GFX_MaxXGet() - BAR_XSTART + 3)
#define BAR_YEND                (SLDR_YSTART - 3)
#define BAR_YSTART              (BAR_YEND - ((SLDR_MAX_VALUE*SLDR_MAX_VALUE)/BAR_4A_CONSTANT))
#define BAR_WIDTH		4


/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
GFX_GOL_OBJ_SCHEME          AN1136Scheme;              // style scheme
GFX_GOL_SCROLLBAR           *pSld;                     // pointer to the slider object
uint16_t                    update = 0;                // variable to update customized graphics
uint16_t                    prevValue = 0;

const GFX_XCHAR             LeftStr[] = {'L','E','F','T',0};
const GFX_XCHAR             RightStr[] = {'R','I','G','H','T',0};

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t APP_CreateAN1136(void)
// Input: None
// Output: Returns non-zero if the objects are created 
//         returns 0 when one of the objects was not created.
// Overview: Creates the AN1136 Demo screen.
/////////////////////////////////////////////////////////////////////////////
uint16_t APP_CreateAN1136(void)
{
    uint16_t state;

    // ///////////////////////////////////////
    // initialize style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeTextColorSet(
                            &AN1136Scheme,
                            BLACK,
                            BRIGHTBLUE,
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &AN1136Scheme,
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            GFX_RGBConvert(0x26, 0xC7, 0xF2),
                            GFX_RGBConvert(0xB6, 0xD2, 0xFB));

    GFX_GOL_SchemeEmbossSet(&AN1136Scheme,
                            GFX_RGBConvert(0x2B, 0x55, 0x87),
                            GFX_RGBConvert(0xD4, 0xE4, 0xF7),
                            1);

    GFX_GOL_SchemeBackgroundColorSet(
                            &AN1136Scheme,
                            GFX_RGBConvert(0xD4, 0xED, 0xF7));

    GFX_GOL_SchemeFontSet(
                            &AN1136Scheme,
                            (GFX_RESOURCE_HDR*)&APP_DEMO_FONT);

    GFX_GOL_SchemeBackgroundImageSet(
                            &AN1136Scheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &AN1136Scheme,
                            GFX_BACKGROUND_IMAGE);

#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)
    if (backgroundImageisSmallerThanScreen == false)
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1136Scheme,
                            GFX_FILL_STYLE_ALPHA_COLOR);
        GFX_GOL_SchemeAlphaPrecentSet(&AN1136Scheme, 75);

    }
    else
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1136Scheme,
                            GFX_FILL_STYLE_COLOR);
    }

#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeGradientColorSet(
                            &AN1136Scheme,
                            GFX_RGBConvert(0x2B, 0x55, 0x87),
                            GFX_RGBConvert(0xD4, 0xE4, 0xF7));
    GFX_GOL_SchemeFillStyleSet(
                            &AN1136Scheme,
                            GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
#else
    GFX_GOL_SchemeFillStyleSet(
                            &AN1136Scheme,
                            GFX_FILL_STYLE_COLOR);
#endif

    update = 1;                     // to initialize the user graphics
    prevValue = 0;

    if (!GFX_GOL_ButtonCreate
    (
        ID_BTN1,                    // object's ID
        BTN1_XSTART,
        BTN_YSTART,
        BTN1_XSTART+BTN_WIDTH,
        BTN_YSTART+BTN_HEIGHT,      // object's dimension
        0,                          // radius of the rounded edge
        GFX_GOL_BUTTON_DRAW_STATE,                   // draw the object after creation
        (void *) &shifted_green_left_arrow,     // press image used
        NULL,                       // no release image used
        (GFX_XCHAR*)LeftStr,        // use this text
        GFX_ALIGN_HCENTER|GFX_ALIGN_VCENTER,
        &AN1136Scheme
    ))
        return 0;                              

    if (!GFX_GOL_ButtonCreate
    (
    	ID_BTN2, 
    	BTN2_XSTART, 
    	BTN_YSTART, 
    	BTN2_XSTART+BTN_WIDTH, 
    	BTN_YSTART+BTN_HEIGHT, 
    	0, 
    	GFX_GOL_BUTTON_DRAW_STATE,
        (void *) &shifted_green_right_arrow,    // press image used
        NULL,                       // no release image used
    	(GFX_XCHAR*)RightStr,
        GFX_ALIGN_HCENTER|GFX_ALIGN_VCENTER,
        &AN1136Scheme
    ))
        return 0;

    state = GFX_GOL_SCROLLBAR_DRAW_STATE|GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE;

    if (!(pSld = GFX_GOL_ScrollBarCreate
        (
            ID_SLD1,                // object�s ID
            SLDR_XSTART,
            SLDR_YSTART,
            SLDR_XSTART+SLDR_WIDTH,
            SLDR_YSTART+SLDR_HEIGHT,// object's dimension
            state,                  // draw the object after creation
            SLDR_MAX_VALUE,         // range
            5,                      // page
            50,                     // initial position
            &AN1136Scheme
        )))
        return 0;      

    // this object will be used only to refresh the area of the
    // primitive bar animation, this will be hidden and will
    // be passive
    if (!(GFX_GOL_GroupboxCreate
        (
            ID_GB,
            BAR_XSTART,
            BAR_YSTART,
            BAR_XEND,
            BAR_YEND,
            GFX_GOL_GROUPBOX_HIDE_STATE | GFX_GOL_SCROLLBAR_DISABLED_STATE,
            NULL,
            GFX_ALIGN_CENTER,
            &AN1136Scheme
        )))
        return 0;

    return 1;
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_MsgAN1136Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns true the message will be processed
//         by default
// Overview: This is called by GOLMsgCallback() to determine if 
//           a valid message for objects in this demo needs to be processed.
/////////////////////////////////////////////////////////////////////////////
bool APP_MsgAN1136Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t           objectID;
    GFX_GOL_SCROLLBAR  *pSldObj;
    GFX_GOL_BUTTON     *pBtnObj;

    objectID = GFX_GOL_ObjectIDGet(pObj);

    if(objectID == ID_BTN1)
    {
        pBtnObj = (GFX_GOL_BUTTON*) pObj;
        
        // check if button is pressed
        if(objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
        {
            // move the text to the right
            GFX_GOL_ButtonTextAlignmentSet(pBtnObj, GFX_ALIGN_RIGHT);
            // find slider pointer
            pSldObj = (GFX_GOL_SCROLLBAR *)GFX_GOL_ObjectFind(ID_SLD1);

            // decrement the slider position
            GFX_GOL_ScrollBarPositionDecrement(pSldObj);
            // redraw only the thumb
            GFX_GOL_ObjectStateSet(pSldObj, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
        }
        else
        {
            // place the text back in the middle
            GFX_GOL_ButtonTextAlignmentSet(pBtnObj, GFX_ALIGN_CENTER);
        }

        update = 1;
    }

    if(objectID == ID_BTN2)
    {
        pBtnObj = (GFX_GOL_BUTTON*) pObj;
        if(objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
        {
            // move the text to the left
            GFX_GOL_ButtonTextAlignmentSet(pBtnObj, GFX_ALIGN_LEFT);
            // find slider pointer
            pSldObj = (GFX_GOL_SCROLLBAR *)GFX_GOL_ObjectFind(ID_SLD1);    

            // increment the slider position
            GFX_GOL_ScrollBarPositionIncrement(pSldObj);
            // redraw only the thumb
            GFX_GOL_ObjectStateSet(pSldObj, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
        }
        else
        {
            // place the text back in the middle
            GFX_GOL_ButtonTextAlignmentSet(pBtnObj, GFX_ALIGN_CENTER);
        }

        update = 1;
    }

    if(objectID == ID_SLD1)
    {
        if((objMsg == GFX_GOL_SCROLLBAR_ACTION_INC) || (objMsg == GFX_GOL_SCROLLBAR_ACTION_DEC))
        {
            update = 1;
        }
    }

    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_DrawAN1136Callback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: GOLDrawCallback() calls this function for demo specific drawing 
//           requirements.
/////////////////////////////////////////////////////////////////////////////
bool APP_DrawAN1136Callback(void)
{
    uint16_t  value, y, x;    // variables for the slider position
    uint16_t  left, top, right, bottom, width, height;

    if(update)
    {

        /* User defined graphics:	
            This draws a series of bars indicating the value/position of the
            slider's thumb. The height of the bars follows the equation of a
            parabola "(y-k)^2 = 4a(x-h) with vertex at (k, h) at (60,100) on
            the display. The value BAR_4A_CONSTANT is the 4*a constant.
            x & y are calculated based on the value of the slider thumb. The
            bars are drawn from 60 to 260 in the x-axis and 10 to 100 in the
            y-axis. Bars are drawn every 6 pixels with width of 4 pixels.

            Only the bars that are added or removed are drawn. Thus resulting
            in an efficient customized drawing.
        */

        // check the value of slider
        value = GFX_GOL_ScrollBarPositionGet(pSld);

        if(value < prevValue)
        {
            while(prevValue > value)
            {

                // get the height of the bar to be removed
                y = (prevValue * prevValue) / BAR_4A_CONSTANT;

                // bars are drawn every 6 pixels with width = 4 pixels.
                x = (prevValue * 2);
                x = x - (x % 6);

                left   = (x+BAR_XSTART);
                top    = BAR_YEND - y;
                right  = (x+BAR_XSTART+BAR_WIDTH);
                bottom = BAR_YEND;

                width  = (right - left + 1);
                height = (bottom - top + 1);

                while((GFX_ImagePartialDraw(
                        left, top,
                        left - pSld->hdr.pGolScheme->CommonBkLeft,
                        top - pSld->hdr.pGolScheme->CommonBkTop,
                        width, height,
                        pSld->hdr.pGolScheme->pCommonBkImage))
                    != GFX_STATUS_SUCCESS);

                // decrement by three since we are drawing every 6 pixels
                prevValue -= 3;
            }
        }

        // Draw bars if there the new value is greater
        // than the previous
        else
        {
            while(prevValue < value)
            {
                if(prevValue < 60)
                {
                    GFX_ColorSet(BRIGHTGREEN);
                }
                else if((prevValue < 80) && (prevValue >= 60))
                {
                    GFX_ColorSet(BRIGHTYELLOW);
                }
                else if(prevValue >= 80)
                {
                    GFX_ColorSet(BRIGHTRED);
                }

                // get the height of the bar to be drawn
                y = (prevValue * prevValue) / BAR_4A_CONSTANT;

                // bars are drawn every 6 pixels with width = 4 pixels.
                x = (prevValue * 2);
                x = x - (x % 6);

#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)
                GFX_AlphaBlendingValueSet(pSld->hdr.pGolScheme->AlphaValue);
                GFX_FillStyleSet(GFX_FILL_STYLE_ALPHA_COLOR);
#endif
                // draw a bar to increase in value
                while(!GFX_BarDraw(x+BAR_XSTART, BAR_YEND-y, x+BAR_XSTART+BAR_WIDTH, BAR_YEND));

                // increment by three since we are drawing every 6 pixels
                prevValue += 3;
            }
        }

        // prevValue will have the current value after drawing or removing bars.
        // reset the update flag
        update = 0;
    }

    return (true);
}


