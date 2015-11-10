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

#ifndef _AN1246DEMO_H
    #define _AN1246DEMO_H

    #include "gfx/gfx.h"
    

    uint16_t APP_CreateAN1246(void);
    bool     APP_DrawAN1246Callback(void);
    bool     APP_MsgAN1246Callback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

    /////////////////////////////////////////////////////////////////////////////
    //                              OBJECT'S IDs
    /////////////////////////////////////////////////////////////////////////////
    #define ID_TE1  20
    
    /////////////////////////////////////////////////////////////////////////////
    //                              USED MACROS
    /////////////////////////////////////////////////////////////////////////////
    #define PASSWORD_LEN    4                       // Password length
    #define DELCHKEYINDEX   3                       // index number of the enter key
    #define SPACEKEYINDEX   7                       // index number of the enter key
    #define ENTERKEYINDEX   11                      // index number of the enter key
    #define MODEKEYINDEX    12                      // index number of the mode key
    #define EXITKEYINDEX    15                      // index number of the exit key
    #define CLEARKEYINDEX   14                      // index number of the clear display key
    #define TEBUFFERSIZE    15                      // buffer size used in the text entry
    #define CHECKDELAY      20000
      

#endif
