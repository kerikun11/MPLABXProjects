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
********************************************************************/
#include <usb/usb.h>
#include <usb/usb_device_generic.h>
#include <stdbool.h>

/** VARIABLES ******************************************************/
//NOTE:  The below endpoint buffers need to be located in a section of
//system SRAM that is accessible by the USB module.  The USB module on all
//currently existing Microchip USB microcontrollers use a dedicated DMA
//interface for reading/writing USB data into/out of main system SRAM.

//On some USB PIC microcontrollers, all of the microcontroller SRAM is dual
//access, and therefore all of it can be accessed by either the USB
//module or the microcontroller core.  On other devices, only a certain
//portion of the SRAM is accessible by the USB module. Therefore, on some
//devices, it is important to place USB data buffers in certain sections of
//SRAM, while on other devices, the buffers can be placed anywhere.

#if defined(COMPILER_MPLAB_C18) //PIC18 devices
    #pragma udata USB_VARIABLES1 = USB_VARS_1
    USB_VOLATILE uint8_t EP1OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP1OUTOddBuffer[64];
    #pragma udata USB_VARIABLES2 = USB_VARS_2
    USB_VOLATILE uint8_t EP2OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP2OUTOddBuffer[64];
    USB_VOLATILE uint8_t EP3OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP3OUTOddBuffer[64];
#elif defined(__XC8) && defined(FIXED_ADDRESS_MEMORY)
    USB_VOLATILE uint8_t EP1OUTEvenBuffer[64] @ EP1_EVEN_DATA_BUFFER_ADDRESS;
    USB_VOLATILE uint8_t EP1OUTOddBuffer[64]  @ EP1_ODD_DATA_BUFFER_ADDRESS;
    USB_VOLATILE uint8_t EP2OUTEvenBuffer[64] @ EP2_EVEN_DATA_BUFFER_ADDRESS;
    USB_VOLATILE uint8_t EP2OUTOddBuffer[64]  @ EP2_ODD_DATA_BUFFER_ADDRESS;
    USB_VOLATILE uint8_t EP3OUTEvenBuffer[64] @ EP3_EVEN_DATA_BUFFER_ADDRESS;
    USB_VOLATILE uint8_t EP3OUTOddBuffer[64]  @ EP3_ODD_DATA_BUFFER_ADDRESS;
#else
    //All PIC24, dsPIC, and PIC32 parts
    USB_VOLATILE uint8_t EP1OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP1OUTOddBuffer[64];
    USB_VOLATILE uint8_t EP2OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP2OUTOddBuffer[64];
    USB_VOLATILE uint8_t EP3OUTEvenBuffer[64];
    USB_VOLATILE uint8_t EP3OUTOddBuffer[64];
#endif

//The below variables are only accessed by the CPU and can be placed anywhere in RAM.
#if defined(COMPILER_MPLAB_C18)
    #pragma udata
#endif

USB_HANDLE EP1OUTEvenHandle;
USB_HANDLE EP2OUTEvenHandle;
USB_HANDLE EP3OUTEvenHandle;
USB_HANDLE EP1OUTOddHandle;
USB_HANDLE EP2OUTOddHandle;
USB_HANDLE EP3OUTOddHandle;
bool EP1OUTEvenNeedsServicingNext;	//true means even need servicing next, false means odd needs servicing next
bool EP2OUTEvenNeedsServicingNext;	//true means even need servicing next, false means odd needs servicing next
bool EP3OUTEvenNeedsServicingNext;	//true means even need servicing next, false means odd needs servicing next

/*********************************************************************
* Function: void APP_DeviceVendorThroughputTestInitialize(void);
*
* Overview: Initializes the demo
*
* PreCondition: Configuration for this app is already set by the USB host.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceVendorThroughputTestInitialize()
{
    EP1OUTEvenHandle = NULL;
    EP2OUTEvenHandle = NULL;
    EP3OUTEvenHandle = NULL;

    EP1OUTOddHandle = NULL;
    EP2OUTOddHandle = NULL;
    EP3OUTOddHandle = NULL;

    //Now that we are configured, enable the endpoints for use in the demo
    //  and start the initial transfers
    USBEnableEndpoint(1,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(2,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(3,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Prepare the OUT endpoints to receive the first packets from the host.
    EP1OUTEvenHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(uint8_t*)&EP1OUTEvenBuffer,64);	//First 64-bytes of data sent to EP1 OUT will arrive in the even buffer.
    EP1OUTOddHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(uint8_t*)&EP1OUTOddBuffer,64);	//Second 64-bytes of data sent to EP1 OUT will arrive in the odd buffer.
    EP1OUTEvenNeedsServicingNext = true;	//Used to keep track of which buffer will contain the next sequential data packet.

    EP2OUTEvenHandle = USBTransferOnePacket(2, OUT_FROM_HOST,(uint8_t*)&EP2OUTEvenBuffer,64);
    EP2OUTOddHandle = USBTransferOnePacket(2, OUT_FROM_HOST,(uint8_t*)&EP2OUTOddBuffer,64);
    EP2OUTEvenNeedsServicingNext = true;	//Used to keep track of which buffer will contain the next sequential data packet.

    EP3OUTEvenHandle = USBTransferOnePacket(3, OUT_FROM_HOST,(uint8_t*)&EP3OUTEvenBuffer,64);
    EP3OUTOddHandle = USBTransferOnePacket(3, OUT_FROM_HOST,(uint8_t*)&EP3OUTOddBuffer,64);
    EP3OUTEvenNeedsServicingNext = true;	//Used to keep track of which buffer will contain the next sequential data packet.
}


/*********************************************************************
* Function: void APP_DeviceVendorThroughputTestTasks(void);
*
* Overview: keeps the demo running.
*
* PreCondition: Demo is initialiized.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceVendorThroughputTestTasks()
{
    //User Application USB tasks below.
    //Note: The user application should not begin attempting to read/write over the USB
    //until after the device has been fully enumerated.  After the device is fully
    //enumerated, the USBDeviceState will be set to "CONFIGURED_STATE".
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    //All currently existing Microchip USB microcontroller use a dedicated Direct
    //Memory Access (DMA) interface allowing the USB module to directly read or
    //write USB packets into or out of microcontroller SRAM.  To receive an "OUT"
    //packet from the host (in USB terminology, OUT and IN are always from the host's
    //perspective), the microcontroller firmware needs to "arm" the Buffer
    //Descriptor Table (BDT) for the endpoint that the data will be received on.
    //The BDT entry is a small set of special function registers (SFRs) that
    //control the operation of the DMA transaction (number of bytes to receive,
    //pointer to where in SRAM the data should be placed, etc.).  Depending upon
    //the USB module configuration, there will be many BDT entries, as each
    //combination of endpoint number, endpoint direction, and endpoint
    //"even/odd-ness" (when ping-pong buffering is enabled), needs a dedicated
    //set of SFRs for controling the DMA behavior when the host tries to read/write
    //to the respective endpoint.

    //As the device completes the enumeration process, the USBCBInitEP() function will
    //get called.  In this function, we initialize the user application endpoints (in this
    //example code, the user application makes use of EP1 OUT, EP2 OUT, EP3 OUT).
    //The USBTransferOnePacket() function calls in the USBCBInitEP() function initializes an endpoint
    //and "arms" it so that it can receive a packet of data from the host.  Once the endpoint
    //has been armed, the host can then send data to it (assuming some kind of application software
    //is running on the host, and the application software tries to send data to the USB device).

    //If the host sends a packet of data to the endpoint 1 OUT buffer, the hardware of the SIE will
    //automatically receives it and stores the data at the memory location pointed to when we called
    //USBTransferOnePacket().  Additionally, the endpoint handle will indicate
    //that the endpoint is no longer busy.  At this point, it is safe for this firmware to begin reading
    //from the endpoint buffer, and processing the data.  In this example, we don't actually do anything
    //with the data that is received from the host, since this demo is simply meant to show high bandwidth
    //USB communication.

    //This demo makes full use of the "ping-pong" buffering features implemented
    //by the USB module hardware.  Ping-pong buffering is like a "DMA FIFO".
    //It enables up to two transactions to be queued up on a single endpoint.
    //While the firmware may be processing and using previously received data,
    //the USB module hardware can be configured to still receive the next packet
    //of data that may be sent from the host.


    //As an example in the below code, if the USB host tries to send 273 bytes
    //to "Endpoint 1 OUT", the following sequence will occur:

    //1. The first set of bytes (0-63) will arrive in the EP1OUTEvenBuffer[].
    //2. The next set of bytes (64-127) will arrive in the EP1OUTOddBuffer[].
    //3. Assuming the firmware re-armed the EP1OUTEven BDT, then the next set of
   	//		bytes (128-191) will arrive in the EP1OUTEvenBuffer[].
    //4. Assuming the firmware re-armed the EP1OUTOdd BDT, then the next set of
   	//		bytes (192-255) will arrive in the EP1OUTOddBuffer[].
    //5. Assuming the firmware re-armed the EP1OUTEven BDT, then the next set of
   	//		bytes (256-272) will arrive in the EP1OUTEvenBuffer[]. This completes
   	//		the transfer, as the host has successfully sent 273 bytes total (0-272).

   	//If after successfully completing the above 273 byte transfer, and the host
   	//wants to start another transfer and send another 75 bytes, the following
   	//will occur:

    //6. Assuming the firmware re-armed the EP1OUTOdd BDT, then bytes (0-63)
    //		will arrive in the EP1OUTOddBuffer[].
    //7. Assuming the firmware re-armed the EP1OUTEven BDT, then the next set of
   	//		bytes (64-74) will arrive in the EP1OUTEvenBuffer[]. This completes
   	//		the transfer, as the host has successfully sent 75 bytes total (0-74).

   	//In the above sequence, if the firmware had not gotten around to re-arming
   	//the EP1OUTEven BDT by step #3, then the EP1 OUT endpoint will continuously
   	//NAK until the firmware eventually does re-arm the EP1OUTEven BDT.  This
   	//NAKing will temporarily halt the data flow, but it does not cause data to
   	//be lost.  The host will continue to retry sending the data until it is
   	//received successfully, or, the host PC application that is sending the data
   	//aborts the operation.  The PC application software can be written to
   	//optionally abort a transfer if it takes too long (or some other event
   	//takes place, such as the user trying to close the application).


    if(EP1OUTEvenNeedsServicingNext == true)	//Check which buffer (even/odd) the next set of data is going to arrive in
    {
        if(!USBHandleBusy(EP1OUTEvenHandle))	//Check if the endpoint has received any data from the host.
        {
            //If the microcontroller core gets to this point, it means that the host has
            //successfully sent data to the EP1 OUT endpoint, and the data in the EP1OUTEvenBuffer[]
            //is currently valid.

            //Insert code here that would do something useful with the EP1OUTEvenBuffer[]
            //data, according to the needs of the application.  For this high-bandwidth
            //example application, we don't do anything with the data, as the
            //objective is to demonstrate maximum data transfer rate only.

            //Now re-arm the EP1OUTEven BDT entry so that the EP1OUTEvenBuffer[] can
            //be prepared to receive the "second to next" data packet that the host
            //sends to EP1 OUT.  The very next data packet sent to EP1 OUT will go
            //into the EP1OUTOdd buffer.  However, we still need to re-arm the
            //EP1OUTEven BDT entry, so that the data packet that arrives after the
            //one going into the EP1OUTOdd buffer has someplace to go.

            //The USBTransferOnePacket() function call "arms" the endpoint (and
            //makes it "busy").  If the endpoint is armed, the SIE will automatically
            //accept data from the host, if the host tries to send a packet of data
            //to the endpoint.  Once a data packet addressed to this endpoint is
            //received from the host, the endpoint will no longer be busy, and the
            //application can read the data which will be sitting in the buffer.
            EP1OUTEvenHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(uint8_t*)&EP1OUTEvenBuffer,64);
            EP1OUTEvenNeedsServicingNext = false;
        }
    }
    else //else EP1OUTOdd needs servicing next
    {
        if(!USBHandleBusy(EP1OUTOddHandle))		//Check if the endpoint has received any data from the host.
        {
                //Insert code here that would do something useful with the data, according to the needs of
                //the application.

            //Re-arm the EP1OUTOdd BDT entry so the EP1OUTOddBuffer[] can receive
            //the second to next data packet sent by the host.
            EP1OUTOddHandle = USBTransferOnePacket(1, OUT_FROM_HOST,(uint8_t*)&EP1OUTOddBuffer,64);
            EP1OUTEvenNeedsServicingNext = true;
        }
    }

    if(EP2OUTEvenNeedsServicingNext == true)
    {
        if(!USBHandleBusy(EP2OUTEvenHandle))		//Check if the endpoint has received any data from the host.
        {
            //Re-arm the OUT endpoint for the next packet:
            EP2OUTEvenHandle = USBTransferOnePacket(2, OUT_FROM_HOST,(uint8_t*)&EP2OUTEvenBuffer,64);
            EP2OUTEvenNeedsServicingNext = false;
        }
    }
    else //else EP2OUTOdd needs servicing next
    {
        if(!USBHandleBusy(EP2OUTOddHandle))		//Check if the endpoint has received any data from the host.
        {
            //Re-arm the OUT endpoint for the next packet:
            EP2OUTOddHandle = USBTransferOnePacket(2, OUT_FROM_HOST,(uint8_t*)&EP2OUTOddBuffer,64);
            EP2OUTEvenNeedsServicingNext = true;
        }
    }

    if(EP3OUTEvenNeedsServicingNext == true)
    {
        if(!USBHandleBusy(EP3OUTEvenHandle))		//Check if the endpoint has received any data from the host.
        {
            //Re-arm the OUT endpoint for the next packet:
            EP3OUTEvenHandle = USBTransferOnePacket(3, OUT_FROM_HOST,(uint8_t*)&EP3OUTEvenBuffer,64);
            EP3OUTEvenNeedsServicingNext = false;
        }
    }
    else //else EP3OUTOdd needs servicing next
    {
        if(!USBHandleBusy(EP3OUTOddHandle))		//Check if the endpoint has received any data from the host.
        {
            //Re-arm the OUT endpoint for the next packet:
            EP3OUTOddHandle = USBTransferOnePacket(3, OUT_FROM_HOST,(uint8_t*)&EP3OUTOddBuffer,64);
            EP3OUTEvenNeedsServicingNext = true;
        }
    }
}