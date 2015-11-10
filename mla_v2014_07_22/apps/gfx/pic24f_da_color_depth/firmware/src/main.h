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

    #define DEMO_FONT                   DroidSans_14

    #define BLACK_SCREEN                (1)

    #define SetBlackScreen()            (_DPTEST = BLACK_SCREEN)
    #define SetNormalScreen()           (_DPTEST = 0)

    #define SCR1_BTNID                  0xF1 
    #define SCR2_BTNID                  0xF2 
    #define SCR1_PICTID                 0xB1
    #define SCR2_PICTID                 0xB2

    #define SCR1_PICT_WIDTH             200
    #define SCR1_PICT_HEIGHT            150

    #if (GFX_CONFIG_COLOR_DEPTH == 1)

        #define SCR1_IMAGE              ((void*)&mchp)
        #define SCR1_BTN_IMAGE          ((void*)&homemono1bpp)
        #define SCR1_BTN_IMAGE_PRESSED  ((void*)&homepressedmono1bpp)

        #define SCR2_IMAGE              ((void*)&mchpgraphics)
        #define SCR2_BTN_IMAGE          ((void*)&settingsmono1bpp)
        #define SCR2_BTN_IMAGE_PRESSED  ((void*)&settingspressedmono1bpp)
#ifndef GFX_CONFIG_IPU_DECODE_DISABLE
        #define LABEL_TEXT              ("1 BPP - Compressed")
#else
        #define LABEL_TEXT              ("1 BPP")
#endif
        #define SCR1_PALETTE            (screen_1bpp_palette)
        #define SCR2_PALETTE            (screen_1bpp_palette)

    #elif (GFX_CONFIG_COLOR_DEPTH == 4)

        #define SCR1_IMAGE              ((void*)&scene02mono_4bpp)
        #define SCR1_BTN_IMAGE          ((void*)&homemono4bpp)
        #define SCR1_BTN_IMAGE_PRESSED  ((void*)&homepressedmono4bpp)

        #define SCR2_IMAGE              ((void*)&scene05mono_4bpp)
        #define SCR2_BTN_IMAGE          ((void*)&settingsmono4bpp)
        #define SCR2_BTN_IMAGE_PRESSED  ((void*)&settingspressedmono4bpp)

#ifndef GFX_CONFIG_IPU_DECODE_DISABLE
        #define LABEL_TEXT              ("4 BPP - Compressed")
#else
        #define LABEL_TEXT              ("4 BPP")
#endif

        #define SCR1_PALETTE            (screen1_4bpp_palette)
        #define SCR2_PALETTE            (screen2_4bpp_palette)

    #elif (GFX_CONFIG_COLOR_DEPTH == 8)
    
        #define SCR1_IMAGE              ((void*)&scene02_8bpp)
        #define SCR1_BTN_IMAGE          ((void*)&home8bpp)
        #define SCR1_BTN_IMAGE_PRESSED  ((void*)&homepressed8bpp)

        #define SCR2_IMAGE              ((void*)&scene05_8bpp)
        #define SCR2_BTN_IMAGE          ((void*)&settings8bpp)
        #define SCR2_BTN_IMAGE_PRESSED  ((void*)&settingspressed8bpp)

#ifndef GFX_CONFIG_IPU_DECODE_DISABLE
        #define LABEL_TEXT              ("8 BPP - Compressed")
#else
        #define LABEL_TEXT              ("8 BPP")
#endif

        #define SCR1_PALETTE            (screen1_8bpp_palette)
        #define SCR2_PALETTE            (screen2_8bpp_palette)

    #endif

    #define TEXT_COLOR                  WHITE

    #define TEXT_WIDTH                  (GFX_TextStringWidthGet(LABEL_TEXT, (void *) &DEMO_FONT))
    #define TEXT_HEIGHT                 (GFX_TextStringHeightGet((void *) &DEMO_FONT))

    #define BTN_WIDTH                   80
    #define BTN_HEIGHT                  79

    #define PICT_WIDTH                  140
    #define PICT_HEIGHT                 140

    #define VERTICAL_MARGIN             ((GFX_MaxYGet() - PICT_HEIGHT - BTN_HEIGHT - TEXT_HEIGHT) >> 2)

    #define TEXT_POSX                   ((GFX_MaxXGet() - TEXT_WIDTH) >> 1)
    #define TEXT_POSY                   (VERTICAL_MARGIN)

    #define SCR1_PICTX                  ((GFX_MaxXGet() - PICT_WIDTH) >> 1)
    #define SCR1_PICTY                  (TEXT_POSY + TEXT_HEIGHT + VERTICAL_MARGIN)

    #define SCR2_PICTX                  ((GFX_MaxXGet() - PICT_WIDTH) >> 1)
    #define SCR2_PICTY                  (TEXT_POSY + TEXT_HEIGHT + VERTICAL_MARGIN)

    #define SCR1_BTNX                   ((GFX_MaxXGet() - BTN_WIDTH) >> 1)
    #define SCR1_BTNY                   (SCR1_PICTY + PICT_HEIGHT + VERTICAL_MARGIN)

    #define SCR2_BTNX                   ((GFX_MaxXGet() - BTN_WIDTH) >> 1)
    #define SCR2_BTNY                   (SCR2_PICTY + PICT_HEIGHT + VERTICAL_MARGIN)


#endif //#ifndef _MAIN_H
