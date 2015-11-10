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
#include "an1182_demo.h"
#include "internal_resource_an1182.h"

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define ID_BTNA 10                                      // Button 1 ID
#define ID_BTNB 11                                      // Button 2 ID
#define ID_STXT 20                                      // Static text ID

#define APP_EMBOSS_SIZE 3

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT DIMENSIONS DEFINES
/////////////////////////////////////////////////////////////////////////////
// static text dimension
#define WIDTH_ADJ   40
#define STXWIDTH    GFX_MaxXGet()-(WIDTH_ADJ<<1)                    // static text width
#define STXHEIGHT   60                                              // static text height
#define STXXPOS     WIDTH_ADJ                                       // static text left/top pos
#define STXYPOS     ((GFX_MaxYGet()-STXHEIGHT-ARROWHEIGHT+3) >> 1)

// string select buttons dimensions
#define SELBTNYPOS  STXYPOS + STXHEIGHT + 3                         // button left/top pos
#define SELBTNXPOS  STXXPOS
#define ARROWHEIGHT (40 + (APP_EMBOSS_SIZE * 2))        // button height
#define ARROWWIDTH  (45 + (APP_EMBOSS_SIZE * 2))        // button width

// slider dimensions
#define SLIDERXPOS      (STXXPOS + ARROWWIDTH)                      // slider left/top pos
#define SLIDERYPOS      (STXYPOS + STXHEIGHT + 3)
#define SLIDERWIDTH     (STXWIDTH - (ARROWWIDTH << 1))              // slider width
#define HWDATAMAX       9                                           // # of "Hello World" strings
#define HELLOWORLDDELAY 30                                          // default animation delay
    
    
/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void APP_InitHWData (void);                     // initialize string struct arrays
void APP_CreateHelloWorld(void);                // create the components

/////////////////////////////////////////////////////////////////////////////
//                       GLOBAL VARIABLES FOR DEMO
/////////////////////////////////////////////////////////////////////////////
//SCREEN_STATES   screenState = SS_CREATE_HELLOWORLD; // current state of main demo state mashine
GFX_GOL_OBJ_SCHEME  AN1182Scheme;                     // style scheme
GFX_GOL_STATICTEXT  *pSt;                             // pointer to the static text object
uint16_t            helloDelay = HELLOWORLDDELAY;

// strings that will use the GOL default font.
const GFX_XCHAR EnglishStr[] = {'H','e','l','l','o',' ','W','o','r','l','d','!',0};
const GFX_XCHAR FrenchStr[] = {'B','o','n','j','o','u','r',' ','M','o','n','d','e','!',0};
const GFX_XCHAR GermanStr[] = {'H','a','l','l','o',' ','W','e','l','t','!',0};
const GFX_XCHAR ItalianStr[] = {'C','i','a','o',' ','M','o','n','d','o','!',0};
const GFX_XCHAR DutchStr[] = {'H','e','l','l','o',' ','W','e','r','e','l','d','!',0};

// structure used to rotate around the used fonts and "Hello World" strings	
typedef struct
{
    GFX_RESOURCE_HDR    *pHWFont;   // pointer to the font used
    GFX_XCHAR           *pHWStr;    // pointer to the string
    void                *pHWPrev;   // pointer to the previous list member
    void                *pHWNext;   // pointer to the next list member
} HWDATA;

// array of structures that will hold the strings and its pointers to corresponding font tables.
// this will be configured as a ringed linked list
HWDATA  HWLang[HWDATAMAX];

// global pointer to the linked list.
HWDATA  *pHWData;

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t APP_CreateAN1182(void)
// Input: None
// Output: Returns non-zero if the objects are created 
//         returns 0 when one of the objects was not created.
// Overview: Creates the AN1182 Demo screen.
/////////////////////////////////////////////////////////////////////////////
uint16_t APP_CreateAN1182(void)
{

    // initialize the list of Hello World translation
    APP_InitHWData();

    // ///////////////////////////////////////
    // initialize style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeTextColorSet(
                            &AN1182Scheme,
                            BRIGHTBLUE,
                            GFX_RGBConvert(0xFF, 0xFF, 0xFF),
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &AN1182Scheme,
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            GFX_RGBConvert(0x26, 0xC7, 0xF2),
                            GFX_RGBConvert(0xB6, 0xD2, 0xFB));

    GFX_GOL_SchemeEmbossSet(&AN1182Scheme,
                            GFX_RGBConvert(0x2B, 0x55, 0x87),
                            GFX_RGBConvert(0xD4, 0xE4, 0xF7),
                            0);

    GFX_GOL_SchemeBackgroundColorSet(
                            &AN1182Scheme,
                            GFX_RGBConvert(0xD4, 0xED, 0xF7));

    GFX_GOL_SchemeFontSet(
                            &AN1182Scheme,
                            pHWData->pHWFont);

    GFX_GOL_SchemeBackgroundImageSet(
                            &AN1182Scheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &AN1182Scheme,
                            GFX_BACKGROUND_IMAGE);

#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)
    if (backgroundImageisSmallerThanScreen == false)
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1182Scheme,
                            GFX_FILL_STYLE_ALPHA_COLOR);
        GFX_GOL_SchemeAlphaPrecentSet(&AN1182Scheme, 50);

    }
    else
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1182Scheme,
                            GFX_FILL_STYLE_COLOR);
    }

#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeGradientColorSet(
                            &AN1182Scheme,
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            GFX_RGBConvert(0x26, 0xC7, 0xF2));
    GFX_GOL_SchemeFillStyleSet(
                            &AN1182Scheme,
                            GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
#else
    GFX_GOL_SchemeFillStyleSet(
                            &AN1182Scheme,
                            GFX_FILL_STYLE_COLOR);
#endif


    APP_CreateHelloWorld();
    
    return 1;

}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_MsgAN1182Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns true the message will be processed
//         by default
// Overview: This is called by GOLMsgCallback() to determine if 
//           a valid message for objects in this demo needs to be processed.
/////////////////////////////////////////////////////////////////////////////
bool APP_MsgAN1182Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t            objectID;
    GFX_GOL_STATICTEXT  *pSt;

    objectID = GFX_GOL_ObjectIDGet(pObj);
    switch(objectID)
    {
        case ID_BTNA:
            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {   // check if button is pressed
                // adjust global pointer to previous string
                pHWData = pHWData->pHWPrev;
                // get pointer to static text
                pSt = (GFX_GOL_STATICTEXT *)GFX_GOL_ObjectFind(ID_STXT);
                // change font used in static text
                pSt->hdr.pGolScheme->pFont = pHWData->pHWFont;
                // set the new string
                GFX_GOL_StaticTextSet(pSt, pHWData->pHWStr);
                // set redraw state
                GFX_GOL_ObjectStateSet(pSt, GFX_GOL_STATICTEXT_DRAW_STATE);
            }

            break;

        case ID_BTNB:
            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                // adjust global pointer to next string
                pHWData = pHWData->pHWNext;
                // get pointer to static text
                pSt = (GFX_GOL_STATICTEXT *)GFX_GOL_ObjectFind(ID_STXT);
                // change font used in static text
                pSt->hdr.pGolScheme->pFont = pHWData->pHWFont;
                // set the new string
                GFX_GOL_StaticTextSet(pSt, pHWData->pHWStr);
                // set redraw state
                GFX_GOL_ObjectStateSet(pSt, GFX_GOL_STATICTEXT_DRAW_STATE);
            }

            break;

        default:
            break;
    }

    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_DrawAN1182Callback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: GOLDrawCallback() calls this function for demo specific drawing 
//           requirements.
/////////////////////////////////////////////////////////////////////////////
bool APP_DrawAN1182Callback(void)
{
    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: void APP_CreateHelloWorld()
// Output: none
// Overview: Create the objects that will show the Hello World Demo.
// 			 This is composed of two buttons and a static text.
//			 The two buttons will select the string that will be displayed.

//			 The strings are arranged in a linked list configured as a ring.
/////////////////////////////////////////////////////////////////////////////
void APP_CreateHelloWorld(void)
{
    uint16_t state;
    AN1182Scheme.pFont = pHWData->pHWFont;

//    // use the partial rendering in case the image
//    // is larger than the screen size.
//    GFX_ImagePartialDraw(   AN1182Scheme.CommonBkLeft,
//                            AN1182Scheme.CommonBkTop,
//                            0, 0,
//                            backgroundInfo.width,
//                            backgroundInfo.height,
//                            AN1182Scheme.pCommonBkImage);

    state = GFX_GOL_STATICTEXT_DRAW_STATE | GFX_GOL_STATICTEXT_FRAME_STATE;

    GFX_GOL_StaticTextCreate
    (
        ID_STXT,
        STXXPOS,
        STXYPOS,
        STXXPOS + STXWIDTH,
        STXYPOS + STXHEIGHT,
        state,
        pHWData->pHWStr,
        GFX_ALIGN_CENTER,
        &AN1182Scheme
    );

    GFX_GOL_ButtonCreate
    (
        ID_BTNA,                    
        SELBTNXPOS,
        SELBTNYPOS,
        SELBTNXPOS + ARROWWIDTH,
        SELBTNYPOS + ARROWHEIGHT,   
        0,                          
        GFX_GOL_BUTTON_DRAW_STATE,   
        (void *) &redLArrow,
        (void *) &redLArrow,
        NULL,                       
        GFX_ALIGN_CENTER,
        &AN1182Scheme
    );                              
    GFX_GOL_ButtonCreate
    (
        ID_BTNB,
        SLIDERXPOS + SLIDERWIDTH,
        SELBTNYPOS,
        SLIDERXPOS + SLIDERWIDTH + ARROWWIDTH,
        SELBTNYPOS + ARROWHEIGHT,
        0,
        GFX_GOL_BUTTON_DRAW_STATE,
        (void *) &redRArrow,
        (void *) &redRArrow,
        NULL,
        GFX_ALIGN_CENTER,
        &AN1182Scheme
    );                              
}

/////////////////////////////////////////////////////////////////////////////
// Function: void APP_InitHWData()
// Output: none

// Overview: Initialize the ring linked list.
/////////////////////////////////////////////////////////////////////////////
void APP_InitHWData(void)
{
    int    i;
    GFX_RESOURCE_HDR *pFont = (GFX_RESOURCE_HDR *)&APP_DEMO_FONT;

    // Get all the translation of "Hello World" and store them into
    // the list.
    for(i = 0; i < HWDATAMAX; i++)
    {
        switch(i)
        {
            case 0:
                HWLang[i].pHWFont = pFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)EnglishStr;
                break;
            case 1:
                HWLang[i].pHWFont = (GFX_RESOURCE_HDR *)&ChineseFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)ChineseStr;
                break;
            case 2:
                HWLang[i].pHWFont = (GFX_RESOURCE_HDR *) &JapaneseFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)JapaneseStr;
                break;
            case 3:
                HWLang[i].pHWFont = pFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)ItalianStr;
                break;
            case 4:
                HWLang[i].pHWFont = pFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)GermanStr;
                break;
            case 5:
                HWLang[i].pHWFont = pFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)DutchStr;
                break;
            case 6:
                HWLang[i].pHWFont = pFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)FrenchStr;
                break;
            case 7:
                HWLang[i].pHWFont = (GFX_RESOURCE_HDR *) &HindiFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)HindiStr;
                break;
            case 8:
                HWLang[i].pHWFont = (GFX_RESOURCE_HDR *) &ThaiFont;
                HWLang[i].pHWStr  = (GFX_XCHAR *)ThaiStr;
                break;
            default:
                break;
        }

        // make the list a ring list
        if(i == (HWDATAMAX - 1))
        {
            HWLang[i].pHWNext = (void *) &HWLang[0];
            HWLang[i].pHWPrev = (void *) &HWLang[i - 1];
        }
        else if(i == 0)
        {
            HWLang[i].pHWNext = (void *) &HWLang[i + 1];
            HWLang[i].pHWPrev = (void *) &HWLang[HWDATAMAX - 1];
        }
        else
        {
            HWLang[i].pHWNext = (void *) &HWLang[i + 1];
            HWLang[i].pHWPrev = (void *) &HWLang[i - 1];
        }
    }

    pHWData = &HWLang[0];
}

