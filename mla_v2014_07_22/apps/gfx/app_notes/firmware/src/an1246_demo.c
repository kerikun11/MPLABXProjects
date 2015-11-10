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

#include <stdlib.h>
#include <string.h>
#include "xc.h"
#include "system.h"
#include "gfx/gfx.h"
#include "main.h"
#include "an1246_demo.h"

/////////////////////////////////////////////////////////////////////////////
//                            DEMO STATES
/////////////////////////////////////////////////////////////////////////////
typedef enum
{
    ENTER_SECURE_ST = 0,
    RESET_SECURE_ST,
    CLEAR_SECURE_ST,
    SHOW_SECURE_ST,
} SECURE_STATE;

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void            APP_CheckCalibration(void);         // check if calibration is needed
void            APP_initKeys(void);                 // initializes the keys
void            APP_SetCommandKeys(GFX_GOL_TEXTENTRY *pTe); // add commands to keys
void            APP_CreateKeyPad(void);             // creates the KeyEntry object

// GFX_XCHAR string compare
int             APP_XcharStrCmp(GFX_XCHAR *pCmp1, GFX_XCHAR *pCmp2, int len);

// callback utility for the object
bool            APP_SecurityMsgCallback(uint16_t objMsg,
                                        GFX_GOL_OBJ_HEADER *pObj,
                                        GFX_GOL_MESSAGE *pMsg);

SECURE_STATE    ViewState = RESET_SECURE_ST; 

/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
GFX_GOL_OBJ_SCHEME          AN1246Scheme;       // style scheme
GFX_GOL_TEXTENTRY           *pTe;               // pointer to the text entry object


GFX_XCHAR       delKey[] = {'d','e','l',0};
GFX_XCHAR       spaceKey[] = {'s','p','c',0};
GFX_XCHAR       enterKey[] = {'e','n','t','e','r',0};
GFX_XCHAR       exitKey[] = {'M','a','i','n',0};
GFX_XCHAR       key1[] = {'1',0};
GFX_XCHAR       key2[] = {'2',0};
GFX_XCHAR       key3[] = {'3',0};
GFX_XCHAR       key4[] = {'4',0};
GFX_XCHAR       key5[] = {'5',0};
GFX_XCHAR       key6[] = {'6',0};
GFX_XCHAR       key7[] = {'7',0};
GFX_XCHAR       key8[] = {'8',0};
GFX_XCHAR       key9[] = {'9',0};
GFX_XCHAR       key0[] = {'0',0};
GFX_XCHAR       keystar[] = {'*',0};
GFX_XCHAR       keypound[] = {'#',0};

GFX_XCHAR       *pKeyNames[] = { key1,    key2, key3,     delKey,
                                 key4,    key5, key6,     spaceKey,
                                 key7,    key8, key9,     enterKey,
                                 keystar, key0, keypound, exitKey
                               };


const GFX_XCHAR TESTEnterCodeText1[] = {'1','2','3',0};
const GFX_XCHAR TESTEnterCodeText2[] = {'1','2','3',0,'1','2','3',0};
GFX_XCHAR       EnterCodeText[TEBUFFERSIZE] = {'E','n','t','e','r',' ','I','D',' ','C','o','d','e', 0};
GFX_XCHAR       ErrorCodeText[TEBUFFERSIZE] = {'I','n','v','a','l','i','d',' ','c','o','d','e',0};
GFX_XCHAR       CorrectCodeText[TEBUFFERSIZE] = {'C','o','d','e',' ','a','c','c','e','p','t','e','d',0};
GFX_XCHAR       PassWord[PASSWORD_LEN + 1] = {'3','6','5','4',0};

// this is the user entered keys buffer
GFX_XCHAR       CodeEntered[TEBUFFERSIZE] = {0};

/////////////////////////////////////////////////////////////////////////////

/*
    This demo code shows how the TextEntry widget is used. The following 
    definitions of the keys are used:
    del - this is the delete character key
    spc - this key inserts a space character
    enter - this key functions as an enter key to process the entered code
    # - this key clears the text area (or more specifically, it clears the
        buffer that receives the user inputted texts)
    * - this toggles the feature hide echo.
    
    When pressing the "enter" key it compares the current contents of the
    buffer to the predetermined password. See definition of PassWord[] array 
    above. If the contents does not match it outputs the ErrorCodeText[].
    If it matches it outputs the CorrectCodeText[]. After that it reverts to
    EnterCodeText[] and program awaits for user inputs again.
    The key at the lower right corner is a dummy key. It has not function.
*/

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t APP_CreateAN1246(void)
// Input: None
// Output: Returns non-zero if the objects are created 
//         returns 0 when one of the objects was not created.
// Overview: Creates the AN1246 Demo screen.
/////////////////////////////////////////////////////////////////////////////
uint16_t APP_CreateAN1246(void)
{

    // ///////////////////////////////////////
    // initialize style scheme
    // ///////////////////////////////////////
    GFX_GOL_SchemeTextColorSet(
                            &AN1246Scheme,
                            GFX_RGBConvert(0xFF, 0xBB, 0x4C),
                            BRIGHTBLUE,
                            GFX_RGBConvert(0xB8, 0xB9, 0xBC));

    GFX_GOL_SchemeColorSet(
                            &AN1246Scheme,
                            GFX_RGBConvert(0x4C, 0x8E, 0xFF),
                            GFX_RGBConvert(0xFF, 0xBB, 0x4C),
                            GFX_RGBConvert(0x4C, 0x8E, 0xFF));

    GFX_GOL_SchemeEmbossSet(&AN1246Scheme,
                            GFX_RGBConvert(0x1E, 0x00, 0xE5),
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF),
                            1);

    GFX_GOL_SchemeBackgroundColorSet(
                            &AN1246Scheme,
                            GFX_RGBConvert(0x4C, 0x8E, 0xFF));

    GFX_GOL_SchemeFontSet(
                            &AN1246Scheme,
                            (GFX_RESOURCE_HDR*)&APP_DEMO_FONT);

    GFX_GOL_SchemeBackgroundImageSet(
                            &AN1246Scheme,
                            backgroundInfo.left,
                            backgroundInfo.top,
                            backgroundInfo.pImage);

    GFX_GOL_SchemeBackgroundTypeSet(
                            &AN1246Scheme,
                            GFX_BACKGROUND_IMAGE);

#if !defined(GFX_CONFIG_ALPHABLEND_DISABLE)
    if (backgroundImageisSmallerThanScreen == false)
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1246Scheme,
                            GFX_FILL_STYLE_ALPHA_COLOR);
        GFX_GOL_SchemeAlphaPrecentSet(&AN1246Scheme, 50);

    }
    else
    {
        GFX_GOL_SchemeFillStyleSet(
                            &AN1246Scheme,
                            GFX_FILL_STYLE_COLOR);
    }

#elif !defined (GFX_CONFIG_GRADIENT_DISABLE)
    GFX_GOL_SchemeGradientColorSet(
                            &AN1246Scheme,
                            GFX_RGBConvert(0x4C, 0x8E, 0xFF),
                            GFX_RGBConvert(0xA9, 0xDB, 0xEF));

    GFX_GOL_SchemeFillStyleSet(
                            &AN1246Scheme,
                            GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
#else
    GFX_GOL_SchemeFillStyleSet(
                            &AN1246Scheme,
                            GFX_FILL_STYLE_COLOR);
#endif

    APP_CreateKeyPad();
    ViewState = ENTER_SECURE_ST;

    return 1;
   
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_MsgAN1246Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns true the message will be processed
//         by default
// Overview: This is called by GOLMsgCallback() to determine if 
//           a valid message for objects in this demo needs to be processed.
/////////////////////////////////////////////////////////////////////////////
bool APP_MsgAN1246Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    
    uint16_t    objectID;

    objectID = GFX_GOL_ObjectIDGet(pObj);

    switch(ViewState)
    {
        case CLEAR_SECURE_ST:
            break;

        case ENTER_SECURE_ST:

            // process key strokes only when in this state
            if(objectID == ID_TE1)
            {
                if(!APP_SecurityMsgCallback(objMsg, pObj, pMsg))
                    return (false);
            }

            break;

        case RESET_SECURE_ST:
            break;

        case SHOW_SECURE_ST:
            break;
    }

    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_DrawAN1246Callback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: it's a user defined function. GOLDraw() function calls it each
//           time when GOL objects drawing is completed. User drawing should be done here.
//           GOL will not change color, line type and clipping region settings while
//           this function returns zero.
/////////////////////////////////////////////////////////////////////////////
bool APP_DrawAN1246Callback(void)
{
    
    GFX_GOL_TEXTENTRY   *pTe = (GFX_GOL_TEXTENTRY *)GFX_GOL_ObjectFind(ID_TE1);

    switch(ViewState)
    {
        case ENTER_SECURE_ST:
            GFX_GOL_TextEntryBufferSet(pTe, CodeEntered, TEBUFFERSIZE);
            return (true);

        case RESET_SECURE_ST:

            // remove the hide feature to show messages
            if(GFX_GOL_ObjectStateGet(pTe, GFX_GOL_TEXTENTRY_ECHO_HIDE_STATE))
                GFX_GOL_ObjectStateClear(pTe, GFX_GOL_TEXTENTRY_ECHO_HIDE_STATE);

            ViewState = CLEAR_SECURE_ST;
            return (true);

        case CLEAR_SECURE_ST:
            if((tick - prevTick) > CHECKDELAY)
            {

                // in this case, we do not restart but rather clear
                // the disabled state, revert the buffer to the user
                // buffer and redraw the object 	
                // return to user buffer to clear the buffer
                GFX_GOL_TextEntryBufferSet(pTe, CodeEntered, TEBUFFERSIZE);
                GFX_GOL_TextEntryBufferClear(pTe);

                // set the message to enter the code
                GFX_GOL_TextEntryBufferSet(pTe, EnterCodeText, TEBUFFERSIZE);
                GFX_GOL_ObjectStateClear(pTe, GFX_GOL_TEXTENTRY_DISABLED_STATE);
                GFX_GOL_ObjectStateSet(pTe, GFX_GOL_TEXTENTRY_DRAW_STATE);

                // set the next state
                ViewState = ENTER_SECURE_ST;
            }
            // re-initialize the keys, this randomizes the key positions
            GFX_GOL_TextEntryKeyMemberListDelete(pTe);
            APP_initKeys();
            GFX_GOL_TextEntryKeyListCreate(pTe, pKeyNames);
            APP_SetCommandKeys(pTe);

            return (true);
        default:
            break;
            
    }

    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: bool APP_SecurityMsgCallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns true the message will be processed by default
// Overview: Called by GFX_GOL_ObjectMessage() and will function similar to GFX_GOL_ObjectMessage().
/////////////////////////////////////////////////////////////////////////////
bool APP_SecurityMsgCallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t    objectID;

    objectID = GFX_GOL_ObjectIDGet(pObj);

    if(objectID == ID_TE1)
    {
        if(objMsg == GFX_GOL_TEXTENTRY_ACTION_ENTER)
        {

            // 	check first if this is for the key with enter label
            if(((GFX_GOL_TEXTENTRY *)pObj)->pActiveKey->index == ENTERKEYINDEX)
            {
                if(APP_XcharStrCmp(GFX_GOL_TextEntryBufferGet((GFX_GOL_TEXTENTRY *)pObj), (GFX_XCHAR *)PassWord, PASSWORD_LEN) == 1)
                {
                    // the code is correct, display the code correct message
                    GFX_GOL_TextEntryBufferSet((GFX_GOL_TEXTENTRY *)pObj, (GFX_XCHAR *)CorrectCodeText, TEBUFFERSIZE);
                }
                else
                {
                    // code not correct, display code incorrect message.
                    GFX_GOL_TextEntryBufferSet((GFX_GOL_TEXTENTRY *)pObj, (GFX_XCHAR *)ErrorCodeText, TEBUFFERSIZE);
                }
                GFX_GOL_ObjectStateSet(pObj, GFX_GOL_TEXTENTRY_DISABLED_STATE |
                                             GFX_GOL_TEXTENTRY_DRAW_STATE);
                prevTick = tick;
                ViewState = RESET_SECURE_ST;
                GFX_GOL_ObjectStateSet(pObj, GFX_GOL_TEXTENTRY_UPDATE_TEXT_STATE);
                return (true);
            }

            // 	check first if this is for the key with mode label
            if(((GFX_GOL_TEXTENTRY *)pObj)->pActiveKey->index == MODEKEYINDEX)
            {
                if(GFX_GOL_ObjectStateGet(pObj, GFX_GOL_TEXTENTRY_ECHO_HIDE_STATE))
                {
                    GFX_GOL_ObjectStateClear(pObj, GFX_GOL_TEXTENTRY_ECHO_HIDE_STATE);
                }
                else
                {
                    GFX_GOL_ObjectStateSet(pObj, GFX_GOL_TEXTENTRY_ECHO_HIDE_STATE);
                }

                GFX_GOL_ObjectStateSet(pObj, GFX_GOL_TEXTENTRY_UPDATE_TEXT_STATE);
                return (true);
            }

            if(((GFX_GOL_TEXTENTRY *)pObj)->pActiveKey->index == CLEARKEYINDEX)
            {
                GFX_GOL_TextEntryBufferClear((GFX_GOL_TEXTENTRY *)pObj);
                GFX_GOL_ObjectStateSet(pObj, GFX_GOL_TEXTENTRY_UPDATE_TEXT_STATE);
                return (true);
            }

        }
    }

    return (true);
}

/////////////////////////////////////////////////////////////////////////////
// Function: void  APP_CreateKeyPad(void)
// Input: none
// Output: none
// Overview: Creates the KeyEntry object and initializes the keys used.
/////////////////////////////////////////////////////////////////////////////
void APP_CreateKeyPad(void)
{
    uint16_t left, top, right, bottom;
    uint16_t state;

    left   = (GFX_MaxXGet() + 1 - 318) >> 1;
    top    = (GFX_MaxYGet() + 1 - 240) >> 1;
    right  = left + 318 - 1;
    bottom = top  + 240 - 1;

    // create the keypad interface
    // initialize the keys
    APP_initKeys();

    // draw the object after creation
    state = GFX_GOL_TEXTENTRY_DRAW_STATE;
    
    // create the object
    pTe = GFX_GOL_TextEntryCreate
        (
            ID_TE1,                         // object's ID
            left, top,
            right, bottom,                  // object's dimension
            state,   
            4,                              // number of horizontal keys
            4,                              // number of vertical keys
            pKeyNames,                      // pointer to the array of key names
            (GFX_XCHAR *)EnterCodeText,     // pointer to the string that
                                            // will be displayed in the object
            GFX_ALIGN_HCENTER,
            TEBUFFERSIZE,
            (GFX_RESOURCE_HDR*)&APP_DEMO_FONT, // pointer to the font of the
                                            // diplayed text
            &AN1246Scheme
        );                          

    // assign command keys
    APP_SetCommandKeys(pTe);
}

/////////////////////////////////////////////////////////////////////////////
// Function: void  APP_XcharStrCmp(GFX_XCHAR *pCmp1, GFX_XCHAR *pCmp2, int len)
// Input: pCmp1 - pointer to first string to compare
//        pCmp1 - pointer to second string to compare
//        len - how many characters to compare
// Output: 1 if the two strings are the same and 0 if not.
// Overview: Similar to StrCmp().
/////////////////////////////////////////////////////////////////////////////
int APP_XcharStrCmp(GFX_XCHAR *pCmp1, GFX_XCHAR *pCmp2, int len)
{
    int counter = 0;

    while(counter < len)
    {
        if(*pCmp1++ != *pCmp2++)
            return (0);
        counter++;
    }

    return (1);
}

/////////////////////////////////////////////////////////////////////////////
// Function: void APP_SetCommandKeys(GFX_GOL_TEXTENTRY *pTe)
// Input: pTe - pointer to the TextEntry object
// Output: none
// Overview: Sets the commands for the selected keys.
/////////////////////////////////////////////////////////////////////////////
void APP_SetCommandKeys(GFX_GOL_TEXTENTRY *pTe)
{
    //assign the 6th key to be a Delete command
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    DELCHKEYINDEX,
                                    GFX_GOL_TEXTENTRY_DELETE_COM);

    //assign the 5th key to be a Space command
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    SPACEKEYINDEX,
                                    GFX_GOL_TEXTENTRY_SPACE_COM);

    //assign the Enter command to Enter key
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    ENTERKEYINDEX,
                                    GFX_GOL_TEXTENTRY_ENTER_COM);
    
    //assign the Enter command to Mode key
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    MODEKEYINDEX,
                                    GFX_GOL_TEXTENTRY_ENTER_COM);
    
    //assign the Enter command to Exit key
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    EXITKEYINDEX,
                                    GFX_GOL_TEXTENTRY_ENTER_COM);

    //assign the Enter command to Clear text key
    GFX_GOL_TextEntryKeyCommandSet( pTe,
                                    CLEARKEYINDEX,
                                    GFX_GOL_TEXTENTRY_ENTER_COM);
    
}

/////////////////////////////////////////////////////////////////////////////
// Function: void APP_initKeys(void)
// Input: none
// Output: none
// Overview: Randomizes the key positions.
/////////////////////////////////////////////////////////////////////////////
#define MAXITEMS    10
#define MAXENTRY    (MAXITEMS - 1)

/* */
void APP_initKeys(void)
{
    int       randomVal, item, adj;
    GFX_XCHAR *pVarLbl[10] = {
                                (GFX_XCHAR*)key1, (GFX_XCHAR*)key2,
                                (GFX_XCHAR*)key3, (GFX_XCHAR*)key4,
                                (GFX_XCHAR*)key5, (GFX_XCHAR*)key6,
                                (GFX_XCHAR*)key7, (GFX_XCHAR*)key8,
                                (GFX_XCHAR*)key9, (GFX_XCHAR*)key0
                             };

    adj = 0;

    #if 0

    // Use this code to initialize the keys normally
    // randomVal here is not random at all
    for(randomVal = 0; randomVal < MAXITEMS; randomVal++)
    {
        pKeyNames[randomVal + adj] = pVarLbl[randomVal];
        if((randomVal == 5) || (randomVal == 2))
            adj++;
        if(randomVal == 8)
            adj = adj + 2;
    }

    return;
    #else

    // Use this code to randomize the key numbers
    // generate seed for random generation
    srand(tick);

    // this randomizes the positions of the 0-9 keys
    for(item = 0; item < MAXITEMS; item++)
    {

        // random number generator
        randomVal = (rand() % (MAXENTRY - item + 1));

        // assign the key character to a position in the array
        pKeyNames[item + adj] = pVarLbl[randomVal];

        // adjust the list of available pointers
        while(randomVal < (MAXENTRY - item + 1))
        {
            pVarLbl[randomVal] = pVarLbl[randomVal + 1];
            randomVal++;
        }

        // This is to compensate on the position of the keys.
        // The location of the *, #, delete, space and enter characters
        // are fixed. Only the numbers are randomized.
        switch(item)
        {
            case 2:
            case 5:
                adj++;
                break;

            case 8:
                adj = adj + 2;
                break;

            default:
                break;
        }   // end of switch()	
    }       // end of for ()
    #endif
    Nop();
}


