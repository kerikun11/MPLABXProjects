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

/** INCLUDES *******************************************************/
#include <usb/usb.h>

#include <usb/usb_device_generic.h>

#include <system.h>
#include <system_config.h>

#include <app_led_usb_status.h>

#include <stdint.h>

/** DECLARATIONS ***************************************************/

/** TYPE DEFINITIONS ************************************************/

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(__18CXX)
        #pragma udata VendorBasicDemo_IN_DATA=VENDOR_BASIC_DEMO_IN_DATA_BUFFER_ADDRESS
            //User application buffer for sending IN packets to the host
            unsigned char INPacket[USBGEN_EP_SIZE];

        #pragma udata VendorBasicDemo_OUT_DATA=VENDOR_BASIC_DEMO_OUT_DATA_BUFFER_ADDRESS
            //User application buffer for receiving and holding OUT packets sent from the host
            unsigned char OUTPacket[USBGEN_EP_SIZE];
        #pragma udata
    #elif defined(__XC8)
        //User application buffer for sending IN packets to the host
        unsigned char INPacket[USBGEN_EP_SIZE] VENDOR_BASIC_DEMO_IN_DATA_BUFFER_ADDRESS;

        //User application buffer for receiving and holding OUT packets sent from the host
        unsigned char OUTPacket[USBGEN_EP_SIZE] VENDOR_BASIC_DEMO_OUT_DATA_BUFFER_ADDRESS;
    #endif
#else
    //User application buffer for sending IN packets to the host
    unsigned char INPacket[USBGEN_EP_SIZE];

    //User application buffer for receiving and holding OUT packets sent from the host
    unsigned char OUTPacket[USBGEN_EP_SIZE];
#endif


static USB_HANDLE USBGenericOutHandle;  //USB handle.  Must be initialized to 0 at startup.
static USB_HANDLE USBGenericInHandle;   //USB handle.  Must be initialized to 0 at startup.

/*********************************************************************
* Function: void APP_DeviceVendorBasicDemoInitialize(void);
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
void APP_DeviceVendorBasicDemoInitialize(void)
{  
    //initialize the variable holding the handle for the last
    // transmission
    USBGenericOutHandle = 0;
    USBGenericInHandle = 0;

    //Enable the application endpoints
    USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Arm the application OUT endpoint, so it can receive a packet from the host
    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(uint8_t*)&OUTPacket,USBGEN_EP_SIZE);
}//end UserInit

/*********************************************************************
* Function: void APP_DeviceVendorBasicDemoTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceVendorBasicDemoInitialize() and APP_DeviceVendorBasicDemoStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceVendorBasicDemoTasks(void)
{  
    //User Application USB tasks below.
    //Note: The user application should not begin attempting to read/write over the USB
    //until after the device has been fully enumerated.  After the device is fully
    //enumerated, the USBDeviceState will be set to "CONFIGURED_STATE".
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    //As the device completes the enumeration process, the USBCBInitEP() function will
    //get called.  In this function, we initialize the user application endpoints (in this
    //example code, the user application makes use of endpoint 1 IN and endpoint 1 OUT).
    //The USBGenRead() function call in the USBCBInitEP() function initializes endpoint 1 OUT
    //and "arms" it so that it can receive a packet of data from the host.  Once the endpoint
    //has been armed, the host can then send data to it (assuming some kind of application software
    //is running on the host, and the application software tries to send data to the USB device).

    //If the host sends a packet of data to the endpoint 1 OUT buffer, the hardware of the SIE will
    //automatically receive it and store the data at the memory location pointed to when we called
    //USBGenRead().  Additionally, the endpoint handle (in this case USBGenericOutHandle) will indicate
    //that the endpoint is no longer busy.  At this point, it is safe for this firmware to begin reading
    //from the endpoint buffer, and processing the data.  In this example, we have implemented a few very
    //simple commands.  For example, if the host sends a packet of data to the endpoint 1 OUT buffer, with the
    //first byte = 0x80, this is being used as a command to indicate that the firmware should "Toggle LED(s)".
    if(!USBHandleBusy(USBGenericOutHandle))		//Check if the endpoint has received any data from the host.
    {
        switch(OUTPacket[0])					//Data arrived, check what kind of command might be in the packet of data.
        {
            case 0x80:  //Toggle LED(s) command from PC application.
                LED_Toggle(LED_DEVICE_VENDOR_BASIC_DEMO);
                break;
            case 0x81:  //Get push button state command from PC application.
				//Now check to make sure no previous attempts to send data to the host are still pending.  If any attemps are still
				//pending, we do not want to write to the endpoint 1 IN buffer again, until the previous transaction is complete.
				//Otherwise the unsent data waiting in the buffer will get overwritten and will result in unexpected behavior.
                if(!USBHandleBusy(USBGenericInHandle))
                {
                    //The endpoint was not "busy", therefore it is safe to write to the buffer and arm the endpoint.
                    INPacket[0] = 0x81;				//Echo back to the host PC the command we are fulfilling in the first byte.  In this case, the Get Pushbutton State command.
                    if(BUTTON_IsPressed(BUTTON_DEVICE_VENDOR_BASIC_DEMO) == false)					//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
                    {
                        INPacket[1] = 0x01;
                    }
                    else							//sw2 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                        INPacket[1] = 0x00;
                    }
                    
                    //The USBGenWrite() function call "arms" the endpoint (and makes the handle indicate the endpoint is busy).
                    //Once armed, the data will be automatically sent to the host (in hardware by the SIE) the next time the
                    //host polls the endpoint.  Once the data is successfully sent, the handle (in this case USBGenericInHandle)
                    //will indicate the the endpoint is no longer busy.
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM,(uint8_t*)&INPacket,USBGEN_EP_SIZE);
                }
                break;
        }

        //Re-arm the OUT endpoint for the next packet:
        //The USBGenRead() function call "arms" the endpoint (and makes it "busy").  If the endpoint is armed, the SIE will
        //automatically accept data from the host, if the host tries to send a packet of data to the endpoint.  Once a data
        //packet addressed to this endpoint is received from the host, the endpoint will no longer be busy, and the application
        //can read the data which will be sitting in the buffer.
        USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(uint8_t*)&OUTPacket,USBGEN_EP_SIZE);
    }

}//end ProcessIO


