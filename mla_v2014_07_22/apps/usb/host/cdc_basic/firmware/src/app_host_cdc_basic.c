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

#include <system.h>
#include <usb/usb.h>
#include <usb/usb_host_cdc.h>
#include <usb/usb_host_cdc_interface.h>
#include <string.h>
#include <stdio.h>

// *****************************************************************************
// *****************************************************************************
// Internal Function Prototypes
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Macros
// *****************************************************************************
// *****************************************************************************
#define MAX_NO_OF_IN_BYTES  64
#define MAX_NO_OF_OUT_BYTES 64

// *****************************************************************************
// *****************************************************************************
// Type definitions
// *****************************************************************************
// *****************************************************************************
typedef enum _APP_STATE
{
    DEVICE_NOT_CONNECTED,
    GET_IN_DATA,
    GET_IN_DATA_WAIT,
    ERROR_REPORTED      /* need to add application states for data interface */
} APP_STATE;

// *****************************************************************************
// *****************************************************************************
// Local Variables
// *****************************************************************************
// *****************************************************************************
volatile APP_STATE  demoState;

uint8_t inBuffer[MAX_NO_OF_IN_BYTES];
uint8_t outBuffer[MAX_NO_OF_OUT_BYTES];

bool buttonReleased;

/*********************************************************************
* Function: void APP_HostCDCBasicInitialize(void);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostCDCBasicInitialize()
{
    demoState = DEVICE_NOT_CONNECTED;
    PRINT_ClearScreen();
    buttonReleased = true;
}

/*********************************************************************
* Function: void APP_HostCDCBasicTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized via
*   the APP_HostCDCBasicInitialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostCDCBasicTasks()
{
    uint8_t errorDriver;
    uint8_t numOfBytesRcvd;

    numOfBytesRcvd = 0;

    if(!USBHostCDC_ApiDeviceDetect()) /* true if device is enumerated without error */
    {
        LED_Off(LED_USB_HOST_CDC_BASIC_DEVICE_ATTACHED);
        demoState = DEVICE_NOT_CONNECTED;
    }

    switch(demoState)
    {
        case DEVICE_NOT_CONNECTED:
            if(USBHostCDC_ApiDeviceDetect()) /* true if device is enumerated without error */
            {
                demoState = GET_IN_DATA;
                LED_On(LED_USB_HOST_CDC_BASIC_DEVICE_ATTACHED);
            }
            break;

        case GET_IN_DATA:
            if(USBHostCDC_Api_Get_IN_Data(MAX_NO_OF_IN_BYTES, inBuffer))
            {
                demoState = GET_IN_DATA_WAIT;
            }
            break;

        case GET_IN_DATA_WAIT:
            if(USBHostCDC_ApiTransferIsComplete(&errorDriver, &numOfBytesRcvd))
            {   /* check for error */
                if( (errorDriver == USB_SUCCESS) &&
                    (numOfBytesRcvd != 0) )
                {
                    PRINT_String((char*)inBuffer, numOfBytesRcvd);
                }

                demoState = GET_IN_DATA;
            }
            break;
            
        default:
            break;
    }
}


/*********************************************************************
* Function: bool APP_HostCDCBasicEventHandler( uint8_t address, USB_EVENT event, void *data, uint32_t size );
*
* Overview: Handles USB events for the USB host CDC demo
*
* PreCondition: None
*
* Input: uint8_t - address of the device causing the event
*        USB_EVENT - the event that occured
*        void* - data accociated with the event
*        uint32_t - size of the data for the event
*
* Output: None
*
********************************************************************/
bool APP_HostCDCBasicEventHandler( uint8_t address, USB_EVENT event, void *data, uint32_t size )
{
    switch((int)event)
    {
        case EVENT_CDC_ATTACH:
            SYSTEM_Initialize(SYSTEM_STATE_USB_HOST_CDC_BASIC);
            return true;
            
        case EVENT_CDC_NONE:
        case EVENT_CDC_COMM_READ_DONE:
        case EVENT_CDC_COMM_WRITE_DONE:
        case EVENT_CDC_DATA_READ_DONE:
        case EVENT_CDC_DATA_WRITE_DONE:
        case EVENT_CDC_RESET:
        case EVENT_CDC_NAK_TIMEOUT:
            return true;
            break;
    }

    return false;
}


