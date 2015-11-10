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
#include "internal_resource_main.h"
#include "external_resource_main.h"
#include "internal_resource_an1136.h"
#include "internal_resource_an1182.h"
#include "an1136_demo.h"
#include "an1182_demo.h"
#include "an1227_demo.h"
#include "an1246_demo.h"
#include "driver/touch_screen/drv_touch_screen.h"


// *****************************************************************************
// Local Prototypes
// *****************************************************************************
uint16_t APP_CreateSelectMenu(void);
uint16_t APP_CreateMainMenu();
uint16_t APP_CreateStyleSchemes(void);
void     APP_CreateStyleSchemesAndBackground(void);
bool     APP_CheckExternalFlashHex(void);

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

// *****************************************************************************
// Application Variables
// *****************************************************************************
GFX_GOL_OBJ_SCHEME  demoScheme;         // alternative style scheme
GFX_GOL_OBJ_SCHEME  demoBackScheme;     // alternative style scheme
GFX_GOL_OBJ_SCHEME  selectScreenScheme; // select screen style scheme

GFX_RESOURCE_HDR    *pIconPressed   = (GFX_RESOURCE_HDR *)&MCHPFolderFile_8bpp_72x72;
GFX_RESOURCE_HDR    *pIconReleased  = (GFX_RESOURCE_HDR *)&MCHPFolderEmpty_8bpp_72x72;
GFX_RESOURCE_HDR    *pAppFont; 

GFX_XCHAR           *pLabels[5], *pStringStart;
APP_BACKGROUND_INFO backgroundInfo;

// current state of main demo state mashine
APP_SCREEN_STATES   screenState;
APP_SCREEN_STATES   nextTargetState;
bool                useExternalData;
bool                backgroundImageisSmallerThanScreen;

GFX_XCHAR  msgStrInvalidData[] = { 'E','x','t','e','r','n','a','l',' ','d','a','t','a',' ','i','n','v','a','l','i','d',0xa,0xa,
                                   'R','u','n','n','i','n','g',' ','t','h','e',' ','d','e','m','o',0xa,
                                   'w','i','t','h',' ','r','e','s','o','u','r','c','e','s',' ','f','r','o','m',0xa,
                                   'i','n','t','e','r','n','a','l',' ','f','l','a','s','h','.',0};

#ifdef USE_COMM_PKT_MEDIA_USB
GFX_XCHAR   msgStrProgramming[] = { 'P','r','o','g','r','a','m',' ','E','x','t','e','r','n','a','l',' ','D','a','t','a',0xa,0xa,
                                    'P','l','e','a','s','e',' ','s','e','n','d',' ','d','a','t','a',' ','u','s','i','n','g',0xa,
                                    '"','E','x','t','e','r','n','a','l',' ','M','e','m','o','r','y',0xa,
                                    'P','r','o','g','r','a','m','m','e','r','"',' ','u','t','i','l','i','t','y',0xa,
                                    'N','o','w',' ','w','a','i','t','i','n','g',' ','f','o','r',' ','d','a','t','a',0xa,
                                    'v','i','a',' ','U','S','B','.','.','.',0};
#else
GFX_XCHAR   msgStrProgramming[] = { 'P','r','o','g','r','a','m',' ','E','x','t','e','r','n','a','l',' ','D','a','t','a',0xa,0xa,
                                    'P','l','e','a','s','e',' ','s','e','n','d',' ','d','a','t','a',' ','u','s','i','n','g',0xa,
                                    '"','E','x','t','e','r','n','a','l',' ','M','e','m','o','r','y',0xa,
                                    'P','r','o','g','r','a','m','m','e','r','"',' ','u','t','i','l','i','t','y',0xa,
                                    'N','o','w',' ','w','a','i','t','i','n','g',' ','f','o','r',' ','d','a','t','a',0xa,
                                    'v','i','a',' ','U','A','R','T','.','.','.',0};
#endif


/*******************************************************************************
 Demo Notes:
 *******************************************************************************

    During startup, this demo has a sequence to check
    for the following user options:
    - Run the demo with internal resources
    - Run the demo with external resources
    - Program External Resources
    The choices are shown on the first screen that comes up after the
    demo is started.

    The following is the logical flow of the start up selection sequence:
    1. At power up board is initialized, drivers are initialized,
       and Graphics Library is initialized.
       When user, holds the screen, while initializing the
       touch driver, the touch screen clibration will automatically
       be performed. When the touch screen info is invalid it will
       also launch the touch screen calibration.
    2. Once everything is initialized, go to step 3
    3. Show selection screen with 3 buttons (Uses Button Objects):
            A. Run Demo with Internal Resources
            B. Run Demo with External Resources
            C. Program External Resources
       Go to step 4.
    4. User selects option.
        4.1 Select A – go to step 7
        4.2 Select B – go to step 5
        4.3 Select C – go to step 6

    5. Check if the external memory contains the correct external data
        5.1 If external data is invalid, go to step 7
        5.2 If external data is valid, go to step 9

    6. Perform external resource programming, then reset the device.

    7. Show screen “Running Demo with internal resources”, go to step 8.
    8. Run the demo with internal resources.
    9. Run the demo with external resources.

    Once the selection has been made, the demo is initialized to use external
    or internal resources. The following resources are set to external or
    internal resources:
    - background image
    - filtered font used in the labels for main demo screen icons

    The rest of the demo uses internal images and fonts.

*******************************************************************************/

/*******************************************************************************
    Main
*******************************************************************************/
int main(void)
{
    // GOL message structure to interact with GOL
    GFX_GOL_MESSAGE msg;

    // step 1: Initialize board, drivers and graphics library
    SYSTEM_InitializeBoard();
    GFX_Initialize();

    // set the message callback function pointer
    GFX_GOL_MessageCallbackSet(APP_ObjectMessageCallback);
    // set the draw callback function pointer
    GFX_GOL_DrawCallbackSet(APP_ObjectDrawCallback);

    // clear the screen with the given color
    GFX_ColorSet(BLACK);
    GFX_ScreenClear();

    // enable the transparent color feature for GFX_ImageDraw()
    // and GFX_ImagePartialDraw() functions
    GFX_TransparentColorEnable(APP_TRANSPARENT_COLOR);
    useExternalData = false;

    // call the function that creates the selection screen menu
    APP_CreateSelectMenu();
    pStringStart = (msgStrInvalidData + 23);
    screenState = CREATE_SELECTMENU;

    // turn on the backlight
    DisplayBacklightOn();

    while(1)
    {
        // Draw GOL objects
        if(GFX_GOL_ObjectListDraw() == GFX_STATUS_SUCCESS)
        {

            if (screenState == DISPLAY_AN1227)
            {
                APP_AN1227ProcessKeyBoard();
            }

            TouchGetMsg(&msg);              // Get message from touch screen
            GFX_GOL_ObjectMessage(&msg);    // Process message

        }
    }

}

// *****************************************************************************
/*  Function:
    void APP_CreateStyleSchemesAndBackground(void)

    Summary:
        Function that creates style schemes for the main screen
        and sub-demos. This also initializes the fonts used in
        icons and background image used for each screen.

    Parameters:
        None.

    Returns:
        None.

*/
// *****************************************************************************
void APP_CreateStyleSchemesAndBackground(void)
{
    // set the background image and other common parameters
    // need to check if the background dimension exceeds the display dimension
    if (useExternalData == true)
    {
        backgroundInfo.pImage = (GFX_RESOURCE_HDR*)&background_fern_16bpp_480x272;
        pAppFont              = (GFX_RESOURCE_HDR *)&DroidSans_Bold_14_ext;
        pLabels[0]            = (GFX_XCHAR*)AN1136Str_ext;
        pLabels[1]            = (GFX_XCHAR*)AN1182Str_ext;
        pLabels[2]            = (GFX_XCHAR*)AN1227Str_ext;
        pLabels[3]            = (GFX_XCHAR*)AN1246Str_ext;
        pLabels[4]            = (GFX_XCHAR*)MainStr_ext;

    }
    else
    {
        backgroundInfo.pImage = (GFX_RESOURCE_HDR*)&background_abstract_light_weave_4bpp_480x272;
        pAppFont              = (GFX_RESOURCE_HDR *)&DroidSans_Bold_14;
        pLabels[0]            = (GFX_XCHAR*)AN1136Str;
        pLabels[1]            = (GFX_XCHAR*)AN1182Str;
        pLabels[2]            = (GFX_XCHAR*)AN1227Str;
        pLabels[3]            = (GFX_XCHAR*)AN1246Str;
        pLabels[4]            = (GFX_XCHAR*)MainStr;
    }

    backgroundInfo.width      = GFX_ImageWidthGet(backgroundInfo.pImage);
    backgroundInfo.height     = GFX_ImageHeightGet(backgroundInfo.pImage);

    // set the background image size flag
    if ((backgroundInfo.width  < GFX_MaxXGet()) ||
        (backgroundInfo.height < GFX_MaxYGet()))
    {
        backgroundImageisSmallerThanScreen = true;
    }
    else
    {
        backgroundImageisSmallerThanScreen = false;
    }


    if (backgroundInfo.width > (GFX_MaxXGet() + 1))
    {
        backgroundInfo.width = (GFX_MaxXGet() + 1);
        backgroundInfo.left = 0;
    }
    else
    {
        // note sequence in important
        backgroundInfo.left   = ( GFX_MaxXGet() + 1 -
                                  backgroundInfo.width)  >> 1;
    }

    if (backgroundInfo.height > (GFX_MaxYGet() + 1))
    {
        backgroundInfo.height = (GFX_MaxYGet() + 1);
        backgroundInfo.top    = 0;
    }
    else
    {
        backgroundInfo.top    = ( GFX_MaxYGet() + 1 -
                                backgroundInfo.height) >> 1;
    }

    // ///////////////////////////////////////
    // initialize the alternative style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeEmbossSet(&demoScheme,
                            GFX_RGBConvert(0x1E, 0x00, 0xE5),
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            0);

    GFX_GOL_SchemeTextColorSet(
                            &demoScheme,
                            BRIGHTBLUE,
                            WHITE,
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &demoScheme,
                            GFX_RGBConvert(0xFF, 0x81, 0x00),
                            GFX_RGBConvert(0xFF, 0xBA, 0x73),
                            GFX_RGBConvert(0xB6, 0xD2, 0xFB));

    GFX_GOL_SchemeFontSet(&demoScheme, pAppFont);

    // set the background information on the style scheme
    GFX_GOL_SchemeBackgroundImageSet(
                            &demoScheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &demoScheme,
                            GFX_BACKGROUND_IMAGE);

    GFX_GOL_SchemeBackgroundColorSet(&demoScheme, BLACK);

    // Since alpha blending a gradient fill is not supported we do
    // some checks here to make sure we do not enable gradient fills
    // when alpha blending is set in a style scheme
#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)

    GFX_GOL_SchemeFillStyleSet(&demoScheme, GFX_FILL_STYLE_ALPHA_COLOR);
    GFX_GOL_SchemeAlphaPrecentSet(&demoScheme, 50);

#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeFillStyleSet(&demoScheme, GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
    GFX_GOL_SchemeGradientColorSet(
                            &demoScheme,
                            GFX_RGBConvert(0x2B, 0x55, 0x87),
                            GFX_RGBConvert(0xD4, 0xE4, 0xF7));
#else
    GFX_GOL_SchemeFillStyleSet(&demoScheme, GFX_FILL_STYLE_COLOR);
#endif

    // ///////////////////////////////////////
    // initialize style scheme for the back button
    // ///////////////////////////////////////

    GFX_GOL_SchemeEmbossSet(&demoBackScheme,
                            GFX_RGBConvert(0x1E, 0x00, 0xE5),
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            0);

    GFX_GOL_SchemeTextColorSet(
                            &demoBackScheme,
                            BRIGHTBLUE,
                            WHITE,
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &demoBackScheme,
                            GFX_RGBConvert(0xFF, 0x81, 0x00),
                            GFX_RGBConvert(0xFF, 0xBA, 0x73),
                            GFX_RGBConvert(0xB6, 0xD2, 0xFB));

    GFX_GOL_SchemeFontSet(&demoBackScheme, pAppFont);
    GFX_GOL_SchemeBackgroundColorSet(&demoScheme, BLACK);

    // set the background information on the style scheme
    GFX_GOL_SchemeBackgroundImageSet(
                            &demoBackScheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &demoBackScheme,
                            GFX_BACKGROUND_IMAGE);

#if !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeGradientColorSet(
                            &demoBackScheme,
                            GFX_RGBConvert(0xFF, 0x81, 0x00),
                            WHITE);
    GFX_GOL_SchemeFillStyleSet(
                            &demoBackScheme,
                            GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
#else
    GFX_GOL_SchemeFillStyleSet(
                            &demoBackScheme,
                            GFX_FILL_STYLE_COLOR);
#endif

}

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
uint16_t APP_CreateBackButton(void)
{
    GFX_GOL_BUTTON *pObj;

    pObj = GFX_GOL_ButtonCreate (
                        ID_BACK,    
                        20, 10,
                        70, 36, 0,
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL, NULL,
                        (GFX_XCHAR*)pLabels[4],
                        GFX_ALIGN_HCENTER | GFX_ALIGN_VCENTER,
                        &demoBackScheme
                     );
                     
    if(pObj == NULL)
        return (0);        
        
    return 1;
    
}    

// *****************************************************************************
/*  Function:
    uint16_t APP_CreateSelectMenu(void)

    Summary:
        Function that creates the startup selection menu. Three buttons
        are used to select the following:
        - Use Internal Resources
        - Use External Resources - not all resources are set to be
          located in external memory.
        - Program External Resources - this prompts the programming
          the external memory.

    Parameters:
        None.

    Returns:
        0 - when the objects are not created.
        1 - when the objects are created.

*/
// *****************************************************************************
uint16_t APP_CreateSelectMenu(void)
{

    // ///////////////////////////////////////
    // initialize select screen style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeTextColorSet(
                            &selectScreenScheme,
                            WHITE,
                            BRIGHTBLUE,
                            GFX_RGBConvert( 245,  245,  220));

    GFX_GOL_SchemeColorSet(
                            &selectScreenScheme,
                            BLACK,
                            GFX_RGBConvert(0x7F, 0x81, 0x7E),
                            GFX_RGBConvert(0xB6, 0xD2, 0xFB));

    GFX_GOL_SchemeEmbossSet(&selectScreenScheme,
                            WHITE,
                            WHITE,
                            3);

    GFX_GOL_SchemeBackgroundColorSet(&selectScreenScheme, BLACK);

    GFX_GOL_SchemeFontSet(
                            &selectScreenScheme,
                            (GFX_RESOURCE_HDR *)&DroidSans_Bold_14);

    GFX_GOL_SchemeFillStyleSet(
                            &selectScreenScheme,
                            GFX_FILL_STYLE_COLOR);


    // ///////////////////////////////////////
    // create the select buttons
    // ///////////////////////////////////////

    if (GFX_GOL_ButtonCreate (
                            ID_SELECT_INTERNAL,
                            SelectLeft(0), SelectTop(0),
                            SelectRight(0), SelectBottom(0),
                            SELECT_HEIGHT >> 1,
                            GFX_GOL_BUTTON_DRAW_STATE,
                            NULL, NULL,
                            (GFX_XCHAR*)UseInternalResourceStr,
                            GFX_ALIGN_CENTER,
                            &selectScreenScheme) == NULL)
    {
        return 0;
    };

    if (GFX_GOL_ButtonCreate (
                            ID_SELECT_EXTERNAL,
                            SelectLeft(0), SelectTop(1),
                            SelectRight(0), SelectBottom(1),
                            SELECT_HEIGHT >> 1,
                            GFX_GOL_BUTTON_DRAW_STATE,
                            NULL, NULL,
                            (GFX_XCHAR*)UseExternalResourceStr,
                            GFX_ALIGN_CENTER,
                            &selectScreenScheme) == NULL)
    {
        return 0;
    };

    if (GFX_GOL_ButtonCreate (
                            ID_SELECT_PROGRAM,
                            SelectLeft(0), SelectTop(2),
                            SelectRight(0), SelectBottom(2),
                            SELECT_HEIGHT >> 1,
                            GFX_GOL_BUTTON_DRAW_STATE,
                            NULL, NULL,
                            (GFX_XCHAR*)UseProgramExternalResourceStr,
                            GFX_ALIGN_CENTER,
                            &selectScreenScheme) == NULL)
    {
        return 0;
    };

    return 1;
}

// *****************************************************************************
/*  Function:
    uint16_t APP_CreateMainMenu(void)

    Summary:
        Function that creates the four icons on the main screen
        of the demo.
        - AN1136
        - AN1182
        - AN1227
        - AN1246

    Parameters:
        None.

    Returns:
        0 - when the objects are not created.
        1 - when the objects are created.

*/
// *****************************************************************************
uint16_t APP_CreateMainMenu(void)
{
    uint16_t    i, state;
    int16_t     left = 0, top = 0, right = 0, bottom = 0, radius = 15;

    // since the background on the main screen is an image, it is best to
    // use translucent anti-aliasing mode
    GFX_FontAntiAliasSet(GFX_FONT_ANTIALIAS_TRANSLUCENT);

    // draw the object after creation with
    // text drawn at the bottom and no panel
#if !defined (GFX_CONFIG_ALPHABLEND_DISABLE)
    state = GFX_GOL_BUTTON_DRAW_STATE;
#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    state = GFX_GOL_BUTTON_DRAW_STATE;
#else
    state = GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_NOPANEL_STATE;
#endif

    // loop to create the four icons
    for (i=0; i<4; i++)
    {
        switch (i)
        {
            case 0:
                top    = IconTop(0);
                bottom = IconBottom(0);
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 1:
                top    = IconTop(0);
                bottom = IconBottom(0);
                left   = IconLeft(1);
                right  = IconRight(1);      
                break;
            case 2:
                top    = IconTop(1);
                bottom = IconBottom(1);
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 3:
                top    = IconTop(1);
                bottom = IconBottom(1);
                left   = IconLeft(1);
                right  = IconRight(1);      
                break;
            default: break;    
        }    

        if (!GFX_GOL_ButtonCreate (
                        ID_ICON1 + i,   // objects ID
                        left, top,
                        right, bottom,  // dimension
                        radius,         // radius if rounded edge
                        state,
                        pIconPressed,   // use this image for press state
                        pIconReleased,  // use this image for release state
                        pLabels[i],     // use this text
                        GFX_ALIGN_BOTTOM | GFX_ALIGN_HCENTER,
                        &demoScheme      
                        )
            )
            return 0;
   
    }
    return 1;
    
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
    uint16_t objID;

    objID = GFX_GOL_ObjectIDGet(pObject);

    switch (screenState)
    {
        case DISPLAY_AN1136:
        case DISPLAY_AN1182:
        case DISPLAY_AN1227:
        case DISPLAY_AN1246:

            // check first if we need to exit the selected demo (if applicable)
            if (    (objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED) &&
                    (objID == ID_BACK))
            {
                // check if the button is indeed pressed
                if (GFX_GOL_ObjectStateGet(pObject,
                                           GFX_GOL_BUTTON_PRESSED_STATE))
                {
                    if (backgroundImageisSmallerThanScreen == false)
                    {
                        nextTargetState = CREATE_MAINMENU;
                        screenState = TRANSITION_STATE_HIDE_OBJECTS;
                        GFX_GOL_ObjectListHide();
                    }
                    else
                    {
                        GFX_GOL_ObjectListFree();
                        screenState = CREATE_MAINMENU;
                    }

                    return true;
                }
            }
            break;

        default:
                break;
    }
      
    // process messages for demo screens
    switch(screenState)
    {
        case DISPLAY_SELECTMENU:
            if (    (objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED) &&
                    (objID         == ID_SELECT_INTERNAL))
            {
                useExternalData = false;
                screenState = DISPLAY_INTERNAL_MESSAGE;
            }

            else if ((objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED) &&
                     (objID         == ID_SELECT_EXTERNAL))
            {
                screenState = DISPLAY_EXTERNAL_MEMORY_CHECK;
            }

            else if ((objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED) &&
                     (objID         == ID_SELECT_PROGRAM))
            {
                screenState = DISPLAY_EXTERNAL_PROGRAMMING;
            }
            break;

        case DISPLAY_MAINMENU:

            // In this portion, all management of the Button states are 
            // done here. This portion will always return 0 to inhibit
            // the button default message processing to take place.
                        
            objID = GFX_GOL_ObjectIDGet(pObject);
            if ((objID == ID_ICON1) || (objID == ID_ICON2) ||
                (objID == ID_ICON3) || (objID == ID_ICON4))
            {    
                if(objectMessage == GFX_GOL_BUTTON_ACTION_PRESSED)
                {   
                    // check if button is pressed and show pressed icon
                    GFX_GOL_ObjectStateSet(pObject, GFX_GOL_BUTTON_PRESSED_STATE);
                }
                else if(objectMessage == GFX_GOL_BUTTON_ACTION_RELEASED)
                {

                    // hide the current contents of the screen
                    GFX_GOL_ObjectListHide();

                    // check if button is released and show release icon
                    GFX_GOL_ObjectStateClear(pObject, GFX_GOL_BUTTON_PRESSED_STATE);
                    switch (objID)
                    {
                        case ID_ICON1:
                            nextTargetState = CREATE_AN1136;
                            screenState = TRANSITION_STATE_HIDE_OBJECTS;
                            GFX_GOL_ObjectListHide();

                            break;
                        case ID_ICON2:
                            nextTargetState = CREATE_AN1182;
                            screenState = TRANSITION_STATE_HIDE_OBJECTS;
                            GFX_GOL_ObjectListHide();
                            break;
                        case ID_ICON3:
                            nextTargetState = CREATE_AN1227;
                            screenState = TRANSITION_STATE_HIDE_OBJECTS;
                            GFX_GOL_ObjectListHide();
                            break;
                        case ID_ICON4:
                            nextTargetState = CREATE_AN1246;
                            screenState = TRANSITION_STATE_HIDE_OBJECTS;
                            GFX_GOL_ObjectListHide();
                            break;
                        default:
                            // this should not happen
                            screenState = DISPLAY_MAINMENU;
                            break;
                    }

                }
                else if(objectMessage == GFX_GOL_BUTTON_ACTION_STILLPRESSED)
                {
                    // do not do anything since it is already pressed
                    return false;
                }    
                else
                {
                    // reset pressed
                    GFX_GOL_ObjectStateClear(pObject, GFX_GOL_BUTTON_PRESSED_STATE);
                }            
                
                // cancel all focus here since this is the main menu
                // we do not want to show the focus on the icons
                GFX_GOL_ObjectStateClear(pObject, GFX_GOL_DRAW_FOCUS | GFX_GOL_FOCUSED);
                GFX_GOL_ObjectStateSet(pObject, GFX_GOL_DRAW);
                return false;
            }
            break;

        case DISPLAY_AN1136:
            return (APP_MsgAN1136Callback(objectMessage, pObject, pMessage));

        case DISPLAY_AN1182:
            return (APP_MsgAN1182Callback(objectMessage, pObject, pMessage));

        case DISPLAY_AN1227:
            return (APP_MsgAN1227Callback(objectMessage, pObject, pMessage));

        case DISPLAY_AN1246:
            if(((GFX_GOL_TEXTENTRY_KEYMEMBER*)
                    ((GFX_GOL_TEXTENTRY *)pObject)->pActiveKey)->index ==
                    EXITKEYINDEX)
            {
                if (objectMessage == GFX_GOL_TEXTENTRY_ACTION_ENTER)
                {
                    // exit the AN1246 Demo

                    nextTargetState = CREATE_MAINMENU;
                    screenState = TRANSITION_STATE_HIDE_OBJECTS;
                    GFX_GOL_ObjectListHide();
                }
            }
            else
            {
                return (APP_MsgAN1246Callback(
                            objectMessage, pObject, pMessage));
            }
        
        default:
            break;
    }        

    return (true);
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
        case CREATE_SELECTMENU:
            // step 3. Show selection screen with 3 buttons
            screenState = DISPLAY_SELECTMENU;
            prevTick = tick;

            break;

        case DISPLAY_SELECTMENU:

            // this is a timeout for the select screen
            // when the timeout has expired, the demo
            // will try for the use of external resource
            if((tick - prevTick) > APP_SS_TIMEOUT)
            {
                screenState = DISPLAY_EXTERNAL_MEMORY_CHECK;
            }

            break;

        case DISPLAY_INTERNAL_MESSAGE:

            // step 7: Show screen “Running Demo with internal resources”

            GFX_ColorSet(BLACK);
            GFX_ScreenClear();

            GFX_ColorSet(WHITE);
            GFX_FontSet((GFX_RESOURCE_HDR*)&APP_DEMO_FONT);

            // displayed message will vary if coming from a selection
            // of using external data but data is invalid.
            while(GFX_TextStringBoxDraw( 0, 0,
                                         GFX_MaxXGet(), GFX_MaxYGet(),
                                         pStringStart,
                                         0, GFX_ALIGN_CENTER) !=
                    GFX_STATUS_SUCCESS);

            DisplayBacklightOn();

            // clear the list so we do not need to respond to any
            // touch on objects on the screen
            GFX_GOL_ObjectListFree();
            prevTick = tick;
            screenState = DISPLAY_INTERNAL_MESSAGE_DELAY;

            break;

        case DISPLAY_INTERNAL_MESSAGE_DELAY:

            // delay for a few seconds
            // This is a timeout for the internal resource message
            // screen to allow the user to read the screen contents.
            if((tick - prevTick) > (APP_SS_TIMEOUT >> 1))
            {
                screenState = CREATE_BACKGROUND;
                DisplayBacklightOff();
            }
            break;

        case DISPLAY_EXTERNAL_MEMORY_CHECK:

            // step 5: Check if the external memory contains 
            //         the correct external data
            useExternalData = APP_CheckExternalFlashHex();
            
            if (useExternalData == false)
            {
                // the external data is invalid
                // run the demo using internal resources
                screenState = DISPLAY_INTERNAL_MESSAGE;
            }
            else
            {
                DisplayBacklightOff();
                screenState = CREATE_BACKGROUND;
            }
            break;

        case CREATE_BACKGROUND:

                GFX_GOL_ObjectListFree();
                APP_CreateStyleSchemesAndBackground();

                // draw the background image
                // use the partial rendering in case the image
                // is larger than the screen size.
                GFX_ImagePartialDraw(   demoScheme.CommonBkLeft,
                                        demoScheme.CommonBkTop,
                                        0, 0,
                                        backgroundInfo.width,
                                        backgroundInfo.height,
                                        demoScheme.pCommonBkImage);

                DisplayBacklightOn();
                screenState = CREATE_MAINMENU;
                break;

        case DISPLAY_EXTERNAL_PROGRAMMING:

            // step 6: Perform external resource programming,
            //         then reset the device.
            
            GFX_ColorSet(BLACK);
            GFX_ScreenClear();

            GFX_ColorSet(WHITE);
            GFX_FontSet((GFX_RESOURCE_HDR*)&APP_DEMO_FONT);

            while( GFX_TextStringBoxDraw( 0, 0,
                                          GFX_MaxXGet(), GFX_MaxYGet(),
                                          msgStrProgramming,
                                          0, GFX_ALIGN_CENTER) !=
                    GFX_STATUS_SUCCESS);

            DisplayBacklightOn();

            // Call the external flash programming routine defined in system.c
            SYSTEM_ProgramExternalMemory();

            // Force Reset to force the checking of the flash memory
            // if programming was a success
            asm("reset");

        case CREATE_MAINMENU:
            GFX_GOL_ObjectListFree();

            // When there is a full screen background do not perform this
            // to save time.
            if (backgroundImageisSmallerThanScreen == true)
            {
                GFX_ColorSet(GFX_RGBConvert(0x7F, 0x81, 0x7E));
                GFX_ScreenClear();
                
                // draw the background image
                // use the partial rendering in case the image
                // is larger than the screen size.
                while(GFX_ImagePartialDraw(
                            demoScheme.CommonBkLeft,
                            demoScheme.CommonBkTop,
                            0, 0,
                            backgroundInfo.width,
                            backgroundInfo.height,
                            demoScheme.pCommonBkImage) != GFX_STATUS_SUCCESS);

            }
#ifndef GFX_CONFIG_DOUBLE_BUFFERING_DISABLE
            GFX_DoubleBufferEnable();
#endif

            GFX_TransparentColorEnable(APP_TRANSPARENT_COLOR);
            APP_CreateMainMenu();
            
            screenState = DISPLAY_MAINMENU;       // switch to next state
            break;
            
        case DISPLAY_MAINMENU:
            break;
            
        case CREATE_AN1136:
#ifndef GFX_CONFIG_DOUBLE_BUFFERING_DISABLE
            GFX_DoubleBufferDisable();
#endif
            GFX_TransparentColorDisable();
            APP_CreateBackButton();
            APP_CreateAN1136();

            screenState = DISPLAY_AN1136;         // switch to next state
            break;
            
        case DISPLAY_AN1136:
            APP_DrawAN1136Callback();
            break;

        case CREATE_AN1182:
            APP_CreateBackButton();
            APP_CreateAN1182();

            screenState = DISPLAY_AN1182;         // switch to next state
            break;
            
        case DISPLAY_AN1182:
            APP_DrawAN1182Callback();
            break;

        case CREATE_AN1227:
            GFX_TransparentColorDisable();
            APP_CreateBackButton();
            APP_CreateAN1227();
            
            screenState = DISPLAY_AN1227;         // switch to next state
            break;
            
        case DISPLAY_AN1227:
            APP_DrawAN1227Callback();
            break;

        case CREATE_AN1246:
            GFX_TransparentColorDisable();
            APP_CreateAN1246();
            screenState = DISPLAY_AN1246;         // switch to next state
            break;
            
        case DISPLAY_AN1246:
            APP_DrawAN1246Callback();
            break;

       case TRANSITION_STATE_HIDE_OBJECTS:
            screenState = TRANSITION_STATE_FREE_OBJECTS;
            break;

       case TRANSITION_STATE_FREE_OBJECTS:
            GFX_GOL_ObjectListFree();
            screenState = nextTargetState;
            break;

        default: 
            break;    
    }    
    return (true);
}

// *****************************************************************************
/*  Function:
    void APP_CheckExternalFlashHex(void)

    Summary:
        This function to check the contents of the external
        memory if it contains valid resource data for the demo.

    Parameters:
        None.

    Returns:
        true - if the external memory contains valid external
               resource data.
        false - if the external memory do not contain valid
                external resource data.
 
*/
// *****************************************************************************
bool APP_CheckExternalFlashHex(void)
{
    typedef struct
    {
        uint32_t mchpSignature;
        uint32_t mchpCRCData;
    } CRC_CHECK;

    CRC_CHECK externalCRC, expectedCRC;

    // check if the CRC matches the data stored in the external flash memory
    expectedCRC.mchpCRCData = GRC_CRC32_EXTERNAL_MARKER;
    // this is "MCHP" in hex
    expectedCRC.mchpSignature = 0x5048434D;

    // check if the external data exists
    // read the external memory for CRC data
    NVMRead(GRC_CRC32_EXTERNAL_ADDR, (uint8_t *)&externalCRC, 8);

    // check for the presence of external data
    if  ((expectedCRC.mchpCRCData   != externalCRC.mchpCRCData)    || \
         (expectedCRC.mchpSignature != externalCRC.mchpSignature))
    {
        pStringStart = msgStrInvalidData;
        return false;
    }
    else
    {
        return true;
    }
}

/* end of file*/