/*******************************************************************************
 Microchip Graphics Library Application Demo

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Application demo for Graphics Library Primitive Layer.

  Description:
    This demo shows the Primitive Layer rendering features of the Microchip
    Graphics Library.
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

// *****************************************************************************
// Section: Includes
// *****************************************************************************
#include <stdint.h>
#include <stdlib.h>
#include "system.h"
#include "gfx/gfx.h"
#include "gfx/gfx_colors_x11.h"
#include "internal_resource.h"

// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
void APP_DrawLinesAndCircleScreen(void);
void APP_DrawLineTypesScreen(void);
void APP_DrawRoundedRectanglesScreen(GFX_LINE_STYLE lineStyle);
void APP_DrawRectangleScreen(void);
void APP_DrawPolygonScreen(void);
void APP_DrawBasicFontScreen(void);
void APP_DrawAntiAliasedFontsScreen(void);
void APP_DrawPutImageScreen(void);
void APP_DrawImageRLE8bppScreen(void);
void APP_DrawImageRLE4bppScreen(void);
void APP_CalculatePaletteColor(GFX_COLOR *red, GFX_COLOR *green, GFX_COLOR *blue, uint16_t pos);

// *****************************************************************************
// Section: Macros
// *****************************************************************************
#define APP_WaitUntilFinished(x)    while(!x)
// *****************************************************************************
// Section: Defines
// *****************************************************************************
#define APP_SCREEN_DELAY_MS         (1000)
// *****************************************************************************
// Section: Constants
// *****************************************************************************
const int16_t polyPoints[] =
{
    (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)/4,
    (GFX_MaxXGet()+1)*3/4,  (GFX_MaxYGet()+1)/2,
    (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)*3/4,
    (GFX_MaxXGet()+1)/4,    (GFX_MaxYGet()+1)/2,
    (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)/4,
};
// *****************************************************************************
// int main(void)
// *****************************************************************************
int main(void)
{
    
    // initialize hardware components and peripherals
    SYSTEM_InitializeBoard();
    
    GFX_Initialize();

    // Turn on the display backlight.
    // this is called here so we do not see the screen in a state
    // where the display buffer has not been initialized
    DisplayBacklightOn();

    while(1)
    {
        APP_DrawLinesAndCircleScreen();
        APP_DrawLineTypesScreen();
        APP_DrawRoundedRectanglesScreen(GFX_LINE_STYLE_THIN_SOLID);
        APP_DrawRoundedRectanglesScreen(GFX_LINE_STYLE_THICK_SOLID);
        APP_DrawRectangleScreen();
        APP_DrawPolygonScreen();
        APP_DrawBasicFontScreen();
        APP_DrawAntiAliasedFontsScreen();

        // draw pictures in the screen with different bits per pixel
        APP_DrawPutImageScreen();

        // RLE Demonstration starts here
        APP_DrawImageRLE8bppScreen();
        APP_DrawImageRLE4bppScreen();
    }
}
// *****************************************************************************
// void APP_DrawLinesAndCircleScreen(void)
// *****************************************************************************
void APP_DrawLinesAndCircleScreen(void)
{
    uint16_t    counter, trueXPos, z;
    uint16_t    centerX, centerY, radius;
    GFX_COLOR   red = 0, blue = 0, green = 0;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    // draw border lines to show the limits of the
    // left, right, top and bottom pixels of the screen
    // draw the top most horizontal line
    GFX_ColorSet(GFX_X11_RED);
    APP_WaitUntilFinished(GFX_LineDraw(0,0,GFX_MaxXGet(),0));
    // draw the right most vertical line
    GFX_ColorSet(GFX_X11_YELLOW);
    APP_WaitUntilFinished(GFX_LineDraw(GFX_MaxXGet(),0,GFX_MaxXGet(),GFX_MaxYGet()));
        // draw the bottom most horizontal line
    GFX_ColorSet(GFX_X11_GREEN);
    APP_WaitUntilFinished(GFX_LineDraw(0,GFX_MaxYGet(),GFX_MaxXGet(),GFX_MaxYGet()));
    // draw the left most vertical line
    GFX_ColorSet(GFX_X11_BLUE);
    APP_WaitUntilFinished(GFX_LineDraw(0,0,0,GFX_MaxYGet()));

    __delay_ms(APP_SCREEN_DELAY_MS * 2);

    // draw lines across the screen with RGB colors
    for(counter = 0; counter <= GFX_MaxXGet()-2; counter++)
    {
        APP_CalculatePaletteColor(&red, &green, &blue, counter);
        trueXPos = counter + 1;

        GFX_ColorSet(GFX_RGBConvert(red, green, blue));
        APP_WaitUntilFinished(GFX_LineDraw(trueXPos, 1, trueXPos, GFX_MaxYGet()-1));
    }

    __delay_ms(APP_SCREEN_DELAY_MS * 3);

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    // draw circles randomly on the screen
    for(counter = 0; counter <= GFX_MaxXGet(); counter++)
    {
        APP_CalculatePaletteColor(&red, &green, &blue, counter);
        trueXPos = counter + 1;
        
        for(z = 0; z <= 2; z++)
        {

            GFX_ColorSet(GFX_RGBConvert(red, green, blue));
            centerX = rand() % GFX_MaxXGet();
            centerY = rand() % GFX_MaxYGet();
            radius  = rand() & 0x1E;

            if (centerX < radius)
                centerX = radius + 1;
            if (centerX > (GFX_MaxXGet()-radius))
                centerX = (GFX_MaxXGet()-radius)-1;
            if (centerY < radius)
                centerY = radius + 1;
            if (centerY > (GFX_MaxYGet()-radius))
                centerY = (GFX_MaxYGet()-radius)-1;

            APP_WaitUntilFinished(GFX_CircleDraw(centerX, centerY, radius));
            __delay_ms(3);
        }
    }

    __delay_ms(APP_SCREEN_DELAY_MS);

    // draw filled circles randomly on the screen
    for(counter = 0; counter <= GFX_MaxXGet(); counter++)
    {
        APP_CalculatePaletteColor(&red, &green, &blue, counter);
        trueXPos = counter + 1;

        for(z = 0; z <= 2; z++)
        {

            GFX_ColorSet(GFX_RGBConvert(red, green, blue));
            centerX = rand() % GFX_MaxXGet();
            centerY = rand() % GFX_MaxYGet();
            radius  = rand() & 0x1E;

            if (centerX < radius)
                centerX = radius + 1;
            if (centerX > (GFX_MaxXGet()-radius))
                centerX = (GFX_MaxXGet()-radius)-1;
            if (centerY < radius)
                centerY = radius + 1;
            if (centerY > (GFX_MaxYGet()-radius))
                centerY = (GFX_MaxYGet()-radius)-1;

            APP_WaitUntilFinished(GFX_CircleFillDraw(centerX, centerY, radius));
            __delay_ms(3);
        }
    }

    __delay_ms(APP_SCREEN_DELAY_MS);
    
}
// *****************************************************************************
// void APP_DrawRoundedRectanglesScreen(GFX_LINE_STYLE lineStyle)
// *****************************************************************************
void APP_DrawRoundedRectanglesScreen(GFX_LINE_STYLE lineStyle)
{
    uint16_t    centerX, centerY;
    uint16_t    rad, counter;
    uint16_t    left, top, right, bottom;
    uint16_t    width, height;
    GFX_COLOR   red, green, blue;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    GFX_LineStyleSet(lineStyle);

    // draw rounded rectangles shapes randomly on the screen
    for(counter = 0; counter <= 300; counter += 1)
    {
        APP_CalculatePaletteColor(&red, &green, &blue, counter);
        GFX_ColorSet(GFX_RGBConvert(red, green, blue));
        centerX = rand() % GFX_MaxXGet();
        centerY = rand() % GFX_MaxYGet();

        width   = rand() & 0x1E;
        height  = rand() & 0x1E;

        rad = 5;

        left   = centerX - (width  >> 1);
        top    = centerY - (height >> 1);
        right  = centerX + (width  >> 1);
        bottom = centerY + (height >> 1);

        // check if the shape goes beyond the screen
        if ((int16_t)(left - rad) <= 0)
        {
            left  = (rad + 1);
            right = left + width + 1;
        }
        if (right + rad > GFX_MaxXGet())
        {
            right = GFX_MaxXGet() - (rad + 1);
            left  = right - width + 1;
        }
        if ((int16_t)(top - rad) <= 0)
        {
            top    = (rad + 1);
            bottom = top + height + 1;
        }
        if (bottom + rad > GFX_MaxYGet())
        {
            bottom = GFX_MaxYGet() - (rad + 1);
            top    = bottom - height + 1;
        }

        APP_WaitUntilFinished
        (
            GFX_RectangleRoundDraw
            (
                left, top, right, bottom,
                rad
            )

        );
         __delay_ms(10);
    }

    __delay_ms(APP_SCREEN_DELAY_MS);

    // reset line style
    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
    
}

// *****************************************************************************
// void APP_DrawRectangleScreen(void)
// *****************************************************************************
void APP_DrawRectangleScreen(void)
{
    uint16_t    count1, count2, width, height, left, top;
    GFX_COLOR   red, green, blue;
    uint16_t    seed;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    seed = rand();

    // draw rectangles and bars
    for(count1 = 0; count1 < 2; count1++)
    {
        srand(seed);
        for(count2 = 0; count2 < 8000; count2++)
        {

            // generate light colors
            red   = (rand() & 0x7F) + 0x80;
            green = (rand() & 0x7F) + 0x80;
            blue  = (rand() & 0x7F) + 0x80;
            GFX_ColorSet(GFX_RGBConvert(red, green, blue));

            // generate the random rectangle
            width   = rand() & 0x1F;
            height  = rand() & 0x1F;
            left    = rand() % GFX_MaxXGet();
            top     = rand() % GFX_MaxYGet();
            if ((left + width) > GFX_MaxXGet())
                width = GFX_MaxXGet() - left;
            if ((top + height) > GFX_MaxYGet())
                height = GFX_MaxYGet() - top;

            if (count1 == 0)
            {
                APP_WaitUntilFinished
                (
                    GFX_RectangleDraw
                        (
                            left,
                            top,
                            left + width,
                            top + height
                        )
                );
            }
            else
            {
                APP_WaitUntilFinished
                (
                    GFX_BarDraw
                        (
                            left,
                            top,
                            left + width,
                            top + height
                        )
                );
            }
        }
        __delay_ms(APP_SCREEN_DELAY_MS);
        GFX_ColorSet(GFX_X11_BLACK);
        GFX_ScreenClear();
    }

}

// *****************************************************************************
// void APP_DrawLineTypesScreen(void)
// *****************************************************************************
void APP_DrawLineTypesScreen(void)
{
    uint16_t        count1, count2, width, height, left, top;
    GFX_COLOR       red, green, blue;
    GFX_LINE_STYLE  lineStyle = GFX_LINE_STYLE_THIN_SOLID;
    uint16_t        lineSize;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    // draw rectangles and bars
    for(count1 = 0; count1 <= 2; count1++)
    {
        lineSize = ((rand() & 0x1) << 4);

        switch (count1 + lineSize)
        {
            case 0x00 : lineStyle = GFX_LINE_STYLE_THIN_SOLID;  break;
            case 0x01 : lineStyle = GFX_LINE_STYLE_THIN_DOTTED; break;
            case 0x02 : lineStyle = GFX_LINE_STYLE_THIN_DASHED; break;
            case 0x10 : lineStyle = GFX_LINE_STYLE_THICK_SOLID;  break;
            case 0x11 : lineStyle = GFX_LINE_STYLE_THICK_DOTTED; break;
            case 0x12 : lineStyle = GFX_LINE_STYLE_THICK_DASHED; break;
            default: break;
        }

        GFX_LineStyleSet(lineStyle);

        for(count2 = 0; count2 < 2000; count2++)
        {
            // generate light colors
            red   = (rand() & 0x7F) + 0x80;
            green = (rand() & 0x7F) + 0x80;
            blue  = (rand() & 0x7F) + 0x80;
            GFX_ColorSet(GFX_RGBConvert(red, green, blue));

            // generate the random rectangle
            width   = rand() & 0x1F;
            height  = rand() & 0x1F;
            left    = rand() % GFX_MaxXGet();
            top     = rand() % GFX_MaxYGet();
            if ((left + width) > GFX_MaxXGet())
                width = GFX_MaxXGet() - left;
            if ((top + height) > GFX_MaxYGet())
                height = GFX_MaxYGet() - top;

            APP_WaitUntilFinished
            (
                GFX_RectangleDraw
                    (
                        left,
                        top,
                        left + width,
                        top + height
                    )
            );
            __delay_ms(1);
        }
        __delay_ms(APP_SCREEN_DELAY_MS);
        GFX_ColorSet(GFX_X11_BLACK);
        GFX_ScreenClear();
    }
    // reset the line style to default
    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

}

// *****************************************************************************
// void APP_DrawImagePolygonScreen(void)
// *****************************************************************************
void APP_DrawPolygonScreen(void)
{
    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    // draw ploygon shape in the middle of the screen
    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
    GFX_ColorSet(GFX_X11_WHITE);
    APP_WaitUntilFinished(GFX_PolygonDraw(4, (uint16_t *)polyPoints));

    __delay_ms(APP_SCREEN_DELAY_MS * 2);

}
// *****************************************************************************
// void APP_DrawImageBasicFontScreen(void)
// *****************************************************************************
void APP_DrawBasicFontScreen(void)
{
    
    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

            // draw fonts in the screen
    GFX_FontSet((GFX_RESOURCE_HDR*) &Font25);
    GFX_ColorSet(GFX_X11_GREEN);
    
    GFX_TextStringBoxDraw(
            0, 0, GFX_MaxXGet(), GFX_MaxYGet(),
            (GFX_XCHAR *)"Microchip Technology Inc.",
            0, GFX_ALIGN_CENTER);

    __delay_ms(APP_SCREEN_DELAY_MS * 4);

}
// *****************************************************************************
// void APP_DrawImageAntiAliasedFontsScreen(void)
// *****************************************************************************
void APP_DrawAntiAliasedFontsScreen(void)
{
    int16_t             width, height, y1, counter;
    GFX_RESOURCE_HDR    *pFont;
    GFX_COLOR           red = 0, blue = 0, green = 0;
    uint16_t            trueXPos;

    // draw the background with RGB colors
    for(counter = 0; counter <= GFX_MaxXGet()-2; counter++)
    {
        APP_CalculatePaletteColor(&red, &green, &blue, counter);
        trueXPos = counter + 1;

        GFX_ColorSet(GFX_RGBConvert(red, green, blue));
        APP_WaitUntilFinished(GFX_LineDraw(trueXPos, 1, trueXPos, GFX_MaxYGet()-1));
    }


    pFont = (GFX_RESOURCE_HDR*)&Font33;
    GFX_FontSet(pFont);
    GFX_ColorSet(BLACK);
    width = GFX_TextStringWidthGet((GFX_XCHAR *)"NON-ANTIALIASED", pFont);
    height = GFX_TextStringHeightGet(pFont);

    y1 = GFX_MaxYGet() / 9;

    while(  GFX_TextStringBoxDraw(
            0, y1,
            GFX_MaxXGet(), height,
            (GFX_XCHAR *)"NON-ANTIALIASED",
            0, GFX_ALIGN_CENTER) != GFX_STATUS_SUCCESS);

    // Display Antialised (Opaque)
    pFont = (GFX_RESOURCE_HDR*)&Font33_Antialiased;
    GFX_FontSet(pFont);
    y1 += (height + (height >> 1));
    height = GFX_TextStringHeightGet(pFont);

    while(  GFX_TextStringBoxDraw(
                0, y1,
                GFX_MaxXGet(), height,
                (GFX_XCHAR *)AntialisedText,
                0, GFX_ALIGN_CENTER) != GFX_STATUS_SUCCESS);

    pFont = (GFX_RESOURCE_HDR*)&Font25;
    GFX_FontSet(pFont);

    while(  GFX_TextStringBoxDraw(
                0, y1 + height,
                GFX_MaxXGet(), height,
                (GFX_XCHAR *)"(Opaque)",
                0, GFX_ALIGN_CENTER) != GFX_STATUS_SUCCESS);

    // Display Antialised (Translucent)
    pFont = (GFX_RESOURCE_HDR*)&Font33_Antialiased;
    GFX_FontSet(pFont);
    GFX_FontAntiAliasSet(GFX_FONT_ANTIALIAS_TRANSLUCENT);
    y1 += ((height << 1)  + (height >> 1));

    while(  GFX_TextStringBoxDraw(
                0, y1,
                GFX_MaxXGet(), height,
                (GFX_XCHAR *)AntialisedText,
                0, GFX_ALIGN_CENTER) != GFX_STATUS_SUCCESS);

    pFont = (GFX_RESOURCE_HDR*)&Font25;
    GFX_FontSet(pFont);

    while(  GFX_TextStringBoxDraw(
                0, y1 + height,
                GFX_MaxXGet(), height,
                (GFX_XCHAR *)"(Translucent)",
                0, GFX_ALIGN_CENTER) != GFX_STATUS_SUCCESS);

    __delay_ms(6*APP_SCREEN_DELAY_MS);

}
// *****************************************************************************
// void APP_DrawImagePutImageScreen(void)
// *****************************************************************************
void APP_DrawPutImageScreen(void)
{
    int16_t             width, height, textWidth;
    int16_t             x,y;
    GFX_RESOURCE_HDR    *pFont;

    pFont = (GFX_RESOURCE_HDR*)&Font25;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    width = GFX_ImageWidthGet((GFX_RESOURCE_HDR*) &flower1bit);
    height = GFX_ImageHeightGet((GFX_RESOURCE_HDR*) &flower1bit);

    x = (GFX_MaxXGet() + 1) / 2 - width;
    y = (GFX_MaxYGet() + 1) / 2 - height;
    textWidth = GFX_TextStringWidthGet((GFX_XCHAR *)"1BPP", pFont);
    APP_WaitUntilFinished(GFX_ImageDraw(x, y, (GFX_RESOURCE_HDR*) &flower1bit));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( x - textWidth,
                        y,
                        (GFX_XCHAR *)"1BPP",
                        0);
    __delay_ms(APP_SCREEN_DELAY_MS);

    x = (GFX_MaxXGet() + 1) / 2;
    y = (GFX_MaxYGet() + 1) / 2 - height;
    textWidth = GFX_TextStringWidthGet((GFX_XCHAR *)"4BPP", pFont);
    APP_WaitUntilFinished(GFX_ImageDraw(x, y, (GFX_RESOURCE_HDR*) &flower4bit));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( x + width ,
                        y,
                        (GFX_XCHAR *)"4BPP",
                        0);
    __delay_ms(APP_SCREEN_DELAY_MS);

    x = (GFX_MaxXGet() + 1) / 2 - width;
    y = (GFX_MaxYGet() + 1) / 2;
    textWidth = GFX_TextStringWidthGet((GFX_XCHAR *)"8BPP", pFont);
    APP_WaitUntilFinished(GFX_ImageDraw(x, y, (GFX_RESOURCE_HDR*) &flower8bit));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( x - textWidth ,
                        y,
                        (GFX_XCHAR *)"8BPP",
                        0);
    __delay_ms(APP_SCREEN_DELAY_MS);

    x = (GFX_MaxXGet() + 1) / 2;
    y = (GFX_MaxYGet() + 1) / 2;
    textWidth = GFX_TextStringWidthGet((GFX_XCHAR *)"16BPP", pFont);
    APP_WaitUntilFinished(GFX_ImageDraw(x, y, (GFX_RESOURCE_HDR*) &flower16bit));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( x + width,
                        y,
                        (GFX_XCHAR *)"16BPP",
                        0);
    __delay_ms(APP_SCREEN_DELAY_MS*3);

}
// *****************************************************************************
// void APP_DrawImageRLE8bppScreen(void)
// *****************************************************************************
void APP_DrawImageRLE8bppScreen(void)
{
    int16_t       width, height;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    /* RLE Demonstration starts here */
    width = GFX_ImageWidthGet((GFX_RESOURCE_HDR*) &Sun8bit_RLE);
    height = GFX_ImageHeightGet((GFX_RESOURCE_HDR*) &Sun8bit_RLE);

    GFX_ColorSet(GFX_X11_WHITE);
    GFX_FontSet((GFX_RESOURCE_HDR*) &Font25);
    GFX_TextStringDraw( 0,
                        0,
                        (GFX_XCHAR *)"RLE Compression of 8BPP Image",
                        0);
    APP_WaitUntilFinished(GFX_ImageDraw(0, 40, (GFX_RESOURCE_HDR*) &Sun8bit));
    APP_WaitUntilFinished(GFX_ImageDraw(width + 60, 40, (GFX_RESOURCE_HDR*) &Sun8bit_RLE));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( 0,
                        height + 60,
                        (GFX_XCHAR *)"Original",
                        0);
    GFX_TextStringDraw( width + 60,
                        height + 60,
                        (GFX_XCHAR *)"RLE compressed",
                        0);
    GFX_TextStringDraw( 0,
                        height + 90,
                        (GFX_XCHAR *)"(5702 Bytes)",
                        0);
    GFX_TextStringDraw( width + 60,
                        height + 90,
                        (GFX_XCHAR *)"(3997 Bytes)",
                        0);

    __delay_ms(APP_SCREEN_DELAY_MS*3);

}
// *****************************************************************************
// void APP_DrawImageRLE4bpp(void)
// *****************************************************************************
void APP_DrawImageRLE4bppScreen(void)
{
    int16_t       width, height;

    GFX_ColorSet(GFX_X11_BLACK);
    GFX_ScreenClear();

    /* RLE Demonstration starts here */
    width = GFX_ImageWidthGet((GFX_RESOURCE_HDR*) &Gaming4bit_RLE);
    height = GFX_ImageHeightGet((GFX_RESOURCE_HDR*) &Gaming4bit_RLE);

    GFX_ColorSet(GFX_X11_WHITE);
    GFX_FontSet((GFX_RESOURCE_HDR*) &Font25);
    GFX_TextStringDraw( 0,
                        0,
                        (GFX_XCHAR *)"RLE Compression of 4BPP Image",
                        0);
    APP_WaitUntilFinished(GFX_ImageDraw(0, 40, (GFX_RESOURCE_HDR*) &Gaming4bit));
    APP_WaitUntilFinished(GFX_ImageDraw(width + 60, 40, (GFX_RESOURCE_HDR*) &Gaming4bit_RLE));
    GFX_ColorSet(GFX_X11_WHITE);
    GFX_TextStringDraw( 0,
                        height + 60,
                        (GFX_XCHAR *)"Original",
                        0);
    GFX_TextStringDraw( width + 60,
                        height + 60, (GFX_XCHAR *)"RLE compressed",
                        0);
    GFX_TextStringDraw( 0,
                        height + 90,
                        (GFX_XCHAR *)"(2630 Bytes)",
                        0);
    GFX_TextStringDraw( width + 60,
                        height + 90,
                        (GFX_XCHAR *)"(1378 Bytes)",
                        0);

    __delay_ms(APP_SCREEN_DELAY_MS*3);

}


/************************************************************************
 Function: void APP_CalculatePaletteColor(  GFX_COLOR *red,
                                            GFX_COLOR *green,
                                            GFX_COLOR *blue,
                                            uint16_t pos)

 Overview: Function that calculates the corresponding color based on the
 		   touched area on the palette.

 Input: *red - pointer to the red value
        *green - pointer to the green value
        *blue - pointer to the blue value
        pos - the position of the touch in the palette.

 Output: none
************************************************************************/
void APP_CalculatePaletteColor(GFX_COLOR *red, GFX_COLOR *green, GFX_COLOR *blue, uint16_t pos)
{
    #define DIVISION        ((GFX_MaxXGet() - 2)/6)
    #define REDMAX          255
    #define GREENMAX        255
    #define BLUEMAX         255


    uint16_t    temp, loc;

    // calculate the effect of x location
    loc = pos / DIVISION;   // gets the location in the palette
    temp = pos % DIVISION;  // calculates the x position in each division
    switch(loc)
    {
        case 0:
            *red = (temp * REDMAX) / DIVISION;                  // red here is increasing as x increases
            *green = 0;
            *blue = BLUEMAX;
            break;

        case 1:
            *red = REDMAX;
            *green = 0;
            *blue = BLUEMAX - ((temp * BLUEMAX) / DIVISION);    // blue here is decreasing as x increases
            break;

        case 2:
            *red = REDMAX;
            *green = (temp * GREENMAX) / DIVISION;              // green here is increasing as x increases
            *blue = 0;
            break;

        case 3:
            *red = REDMAX - ((temp * REDMAX) / DIVISION);       // red here is decreasing as x increases
            *green = GREENMAX;
            *blue = 0;
            break;

        case 4:
            *red = 0;
            *green = GREENMAX;
            *blue = (temp * BLUEMAX) / DIVISION;                // blue here is increasing as x increases
            break;

        case 5:
            *red = 0;
            *green = GREENMAX - ((temp * GREENMAX) / DIVISION); // green here is decreasing as x increases
            *blue = BLUEMAX;
            break;

        default:
            break;
    }
}