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
#include <usb/usb_device_hid.h>

#include <string.h>

#include <system.h>


/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #else defined(__XC8)
        unsigned char ReceivedDataBuffer[64] @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

/** DEFINITIONS ****************************************************/
typedef enum
{
    COMMAND_TOGGLE_LED = 0x80,
    COMMAND_GET_BUTTON_STATUS = 0x81,
    COMMAND_READ_POTENTIOMETER = 0x37
} CUSTOM_HID_DEMO_COMMANDS;

/** FUNCTIONS ******************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,(uint8_t*)&ReceivedDataBuffer,64);
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks()
{   
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false)
    {   
        //We just received a packet of data from the USB host.
        //Check the first uint8_t of the packet to see what command the host
        //application software wants us to fulfill.
        switch(ReceivedDataBuffer[0])				//Look at the data the host sent, to see what kind of application specific command it sent.
        {
            case COMMAND_TOGGLE_LED:  //Toggle LEDs command
                LED_Toggle(LED_USB_DEVICE_HID_CUSTOM);
                break;
            case COMMAND_GET_BUTTON_STATUS:  //Get push button state
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    ToSendDataBuffer[0] = 0x81;				//Echo back to the host PC the command we are fulfilling in the first uint8_t.  In this case, the Get Pushbutton State command.
                    if(BUTTON_IsPressed(BUTTON_USB_DEVICE_HID_CUSTOM) == false)	//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
                    {
                            ToSendDataBuffer[1] = 0x01;
                    }
                    else									//sw3 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                            ToSendDataBuffer[1] = 0x00;
                    }
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
                break;

            case COMMAND_READ_POTENTIOMETER:	//Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host
                {
                    uint16_t pot;

                    //Check to make sure the endpoint/buffer is free before we modify the contents
                    if(!HIDTxHandleBusy(USBInHandle))
                    {
                        //Use ADC to read the I/O pin voltage.  See the relevant HardwareProfile - xxxxx.h file for the I/O pin that it will measure.
                        //Some demo boards, like the PIC18F87J50 FS USB Plug-In Module board, do not have a potentiometer (when used stand alone).
                        //This function call will still measure the analog voltage on the I/O pin however.  To make the demo more interesting, it
                        //is suggested that an external adjustable analog voltage should be applied to this pin.

                        pot = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);

                        ToSendDataBuffer[0] = 0x37;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
                        ToSendDataBuffer[1] = (uint8_t)pot; //LSB
                        ToSendDataBuffer[2] = pot >> 8;     //MSB


                        //Prepare the USB module to send the data packet to the host
                        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                    }
                }
                break;
        }
        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer, 64);
    }
}