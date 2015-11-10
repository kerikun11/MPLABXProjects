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
#include <stdint.h>
#include <stdbool.h>

#include <system.h>

#include <usb/usb.h>
#include <usb/usb_device_hid.h>

#include "reports.h"

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata DEVICE_HID_UPS_IN_BUFFER=DEVCE_UPS_IN_DATA_BUFFER_ADDRESS
            static unsigned char ReceivedDataBuffer[HID_INT_OUT_EP_SIZE];  //USB packet buffer, must reside in USB module accessible RAM
        #pragma udata DEVICE_HID_UPS_OUT_BUFFER=DEVCE_UPS_OUT_DATA_BUFFER_ADDRESS
            static unsigned char ToSendDataBuffer[HID_INT_IN_EP_SIZE];     //USB packet buffer, must reside in USB module accessible RAM
        #pragma udata DEVICE_HID_UPS_FEATURE_BUFFER=DEVCE_UPS_FEATURE_DATA_BUFFER_ADDRESS
            static uint8_t hid_feature_data[USB_EP0_BUFF_SIZE];
        #pragma udata
    #elif defined(__XC8)
        static unsigned char ReceivedDataBuffer[HID_INT_OUT_EP_SIZE] DEVCE_UPS_IN_DATA_BUFFER_ADDRESS;  //USB packet buffer, must reside in USB module accessible RAM
        static unsigned char ToSendDataBuffer[HID_INT_IN_EP_SIZE] DEVCE_UPS_OUT_DATA_BUFFER_ADDRESS;     //USB packet buffer, must reside in USB module accessible RAM
        static uint8_t hid_feature_data[USB_EP0_BUFF_SIZE] DEVCE_UPS_FEATURE_DATA_BUFFER_ADDRESS;
    #endif
#else
    static unsigned char ReceivedDataBuffer[HID_INT_OUT_EP_SIZE];  //USB packet buffer, must reside in USB module accessible RAM
    static unsigned char ToSendDataBuffer[HID_INT_IN_EP_SIZE];     //USB packet buffer, must reside in USB module accessible RAM
    static uint8_t hid_feature_data[USB_EP0_BUFF_SIZE];
#endif
    
static USB_HANDLE USBOutHandle = 0;    //USB handle.  Must be initialized to 0 at startup.
static USB_HANDLE USBInHandle = 0;     //USB handle.  Must be initialized to 0 at startup.
static uint8_t capacity = 100;
static uint8_t reportToSend = POWER_SUMMARY_STATUS_INFO;
static bool oldButtonState = false;
static USB_VOLATILE uint16_t SOFCount;

#define SOF_COUNT_RESET_VALUE 1000

/*********************************************************************
* Function: void APP_DeviceHIDUPSInitialize(void);
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
void APP_DeviceHIDUPSInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBOutHandle = 0;    //USB handle.  Must be initialized to 0 at startup.
    USBInHandle = 0;     //USB handle.  Must be initialized to 0 at startup.

    capacity = 100;
    reportToSend = POWER_SUMMARY_STATUS_INFO;
    oldButtonState = BUTTON_IsPressed(DEVICE_HID_UPS_SIMULATE_DISCHARGE_BUTTON);

    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(uint8_t*)&ReceivedDataBuffer,64);
}

/*********************************************************************
* Function: void APP_DeviceHIDUPSInitialize(void);
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
void APP_DeviceHIDUPSSOFHandler()
{
    if(SOFCount != 0)
    {
        SOFCount--;
    }
}

/*********************************************************************
* Function: void APP_DeviceHIDUPSTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceHIDUPSInitialize() and APP_DeviceHIDUPSStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceHIDUPSTasks()
{
    bool currentButtonState = BUTTON_IsPressed(DEVICE_HID_UPS_SIMULATE_DISCHARGE_BUTTON);
    uint16_t SOFCountCopy;

    //Safely copy the SOF count to a local
    USBMaskInterrupts();
    SOFCountCopy = SOFCount;
    USBUnmaskInterrupts();

    // If the device is not configured yet, or the device is suspended, then
    //   we don't need to run the demo since we can't send any data.
    if( (USBGetDeviceState() < CONFIGURED_STATE) ||
        (USBIsDeviceSuspended() == true))
    {
        return;
    }

    //If the last transmission is already complete
    if(!HIDTxHandleBusy(USBInHandle))
    {
        //if the button is pressed
        if(currentButtonState != oldButtonState)
        {
            //save the button value
            oldButtonState = currentButtonState;

            //Set the state machine variable to send the
            //  POWER_SUMMARY_STATUS_INFO report
            reportToSend = POWER_SUMMARY_STATUS_INFO;

            SOFCountCopy = 0;  //Reset delay count
        }

        //INTPUT Report sending state machine.
        switch(reportToSend)
        {
            //*********************************************************************
            //  Title:
            //    PresentStatus Report
            //
            //  Description:
            //    The present status report gives information about the current state
            //    of the device.
            //
            //  Format:
            //    byte |       bit 7      |       bit 6       |      bit 5      |       bit 4       |    bit 3    |      bit 2      |           bit 1           |           bit 0             |
            //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
            //      0  |             Report ID = POWER_SUMMARY_STATUS_INFO                                                                                                                    |
            //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
            //      1  | ShutdownImminent | ShutdownRequested | OverTemperature | OverCharged       | Overload    | InternalFailure | Good                      | Present                     |
            //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
            //      2  |  BatteryPresent  | ACPresent         | NeedReplacement | ConditionningFlag | Discharging | Charging        | RemainingTimeLimitExpired | BelowRemainingCapacityLimit |
            //         ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //*********************************************************************
            case POWER_SUMMARY_STATUS_INFO:
                ToSendDataBuffer[0] = reportToSend;

                //Check the pushbutton
                if(currentButtonState == true)
                {
                    //If the button is pressed then simulate that we are
                    //  in a discharge state

                    //If the capacity is less than 5% then indicate that
                    //  a shutdown is imminent and request the computer shutdown
                    if(capacity < 5)
                    {
                        ToSendDataBuffer[1] = 0xC3;
                    }
                    else
                    {
                        ToSendDataBuffer[1] = 0x03;
                    }

                    //Indicate the battery is present but discharging, no AC
                    ToSendDataBuffer[2] = 0x88;
                }
                else
                {
                    //If the button isn't pressed then we are AC powered

                    ToSendDataBuffer[1] = 0x03;

                    if(capacity == 100)
                    {
                        //if capacity is at 100%, we can stop charging the
                        //  battery.
                        ToSendDataBuffer[2] = 0xC0;
                    }
                    else
                    {
                        //if capacity is less than 100%, we need to charge the
                        //  battery
                        ToSendDataBuffer[2] = 0xC4;
                    }
                }

                reportToSend = POWER_SUMMARY_REMAINING_CAPACITY;

                USBInHandle = HIDTxPacket(HID_EP,(uint8_t*)&ToSendDataBuffer[0],3);
                break;

            //*********************************************************************
            //  Title:
            //    RemainingCapacity Report
            //
            //  Description:
            //    RemainingCapacity reflects the capacity left in the battery
            //    in the units specified by the CapacityMode report
            //
            //  Format:
            //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
            //         |---------------------------------------------------------------|
            //      0  |             Report ID = POWER_SUMMARY_REMAINING_CAPACITY      |
            //         |---------------------------------------------------------------|
            //      1  |                         RemainingCapacity                     |
            //         -----------------------------------------------------------------
            //*********************************************************************
            case POWER_SUMMARY_REMAINING_CAPACITY:
                //we are using a counter here to simulate a time delay
                if(SOFCountCopy == 0)
                {
                    //if the counter has expired then send a RemainingCapacity Report
                    ToSendDataBuffer[0] = reportToSend;
                    ToSendDataBuffer[1] = capacity;
                    USBInHandle = HIDTxPacket(HID_EP,(uint8_t*)&ToSendDataBuffer[0],2);

                    //Reset the counter
                    USBMaskInterrupts();
                    SOFCount = SOF_COUNT_RESET_VALUE;
                    USBUnmaskInterrupts();

                    //If the button is pressed
                    if(oldButtonState == true)
                    {
                        //We are discharging - no AC

                        //And we still have capacity left
                        if(capacity != 1)
                        {
                            //Decrease the remaining capacity
                            capacity--;
                        }
                        //Send the run time to empty report next
                        reportToSend = POWER_SUMMARY_RUN_TIME_TO_EMPTY;
                    }
                    else
                    {
                        //if the button isn't pressed (we are line powered)

                        //If we aren't at max capacity (100%)
                        if(capacity != 100)
                        {
                            //increase the capacity
                            capacity++;

                            reportToSend = POWER_SUMMARY_RUN_TIME_TO_EMPTY;
                        }
                        else
                        {
                            //if we are at max capacity we don't need to send
                            //  any more reports until something changes
                            reportToSend = NO_MORE_REPORTS;
                        }
                    }
                }
                break;

            //*********************************************************************
            //  Title:
            //    RunTimeToEmpty Report
            //
            //  Description:
            //    This report sends the number of seconds of capacity
            //
            //  Format:
            //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
            //         |---------------------------------------------------------------|
            //      0  |             Report ID = POWER_SUMMARY_RUN_TIME_TO_EMPTY       |
            //         |---------------------------------------------------------------|
            //      1  |                         RunTimeToEmpty (byte 0)               |
            //         |---------------------------------------------------------------|
            //      2  |                         RunTimeToEmpty (byte 1)               |
            //         -----------------------------------------------------------------
            //      3  |                         RunTimeToEmpty (byte 2)               |
            //         -----------------------------------------------------------------
            //*********************************************************************
            case POWER_SUMMARY_RUN_TIME_TO_EMPTY:
            {
                uint16_t RunTimeToEmpty;

                //RunTimeToEmpty.Val = (60u * 60u * 1u * capacity)/100u;		//Want this but division is expensive, so we do the below instead.
                RunTimeToEmpty = (36u * (uint16_t)capacity);
                //60 sec/min * 60 min/hr * 1hr capacity(typically) * current_capacity/100 = seconds of capacity left

                ToSendDataBuffer[0] = reportToSend;
                ToSendDataBuffer[1] = RunTimeToEmpty & 0x00FF;
                ToSendDataBuffer[2] = ((RunTimeToEmpty & 0xFF00) >> 8);
                ToSendDataBuffer[3] = 0u;

                USBInHandle = HIDTxPacket(HID_EP,(uint8_t*)&ToSendDataBuffer[0],4);

                reportToSend = POWER_SUMMARY_REMAINING_CAPACITY;
                break;
            }

            case NO_MORE_REPORTS:
                //Fall through
            default:
                break;
        }
    }
}

/********************************************************************
 * Function:        void UserGetReportHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If the USBEP0Transmit() function is not called
 *                  in this function then the resulting GET_REPORT
 *                  will be STALLed.
 *
 * Overview:        This function is called by the HID function driver
 *                  in response to a GET_REPORT command.
 *
 * Note:            This function is called from the USB stack in
 *                  response to a class specific control transfer requests
 *                  arriving over EP0.  Therefore, this function executes in the
 *                  same context as the USBDeviceTasks() function executes (which
 *                  may be an interrupt handler, or a main loop context function,
 *                  depending upon usb_config.h options).
 *******************************************************************/
void UserSetReportHandler(void)
{
    switch(SetupPkt.W_Value.byte.LB)
    {
        case POWER_SUMMARY_REMAINING_CAPACITY_LIMIT:
            //Receive the EP0 data but set the notification function pointer
            //  to NULL in order to ignore the data.  Note that the contents of
            //  ReceivedDataBuffer will be updated with the SET_REPORT data
            USBEP0Receive((uint8_t*)ReceivedDataBuffer,SetupPkt.wLength,NULL);
            break;
        default:
            break;
    }
}

/********************************************************************
 * Function:        void UserGetReportHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Transmit()
 *                  functions are not called in this function then the
 *                  requesting GET_REPORT will be STALLed
 *
 * Overview:        This function is called by the HID function driver
 *                  in response to a GET_REPORT command.
 *
 * Note:            This function is called from the USB stack in
 *                  response to a class specific control transfer request
 *                  arriving over EP0.  Therefore, this function executes in the
 *                  same context as the USBDeviceTasks() function executes (which
 *                  may be an interrupt handler, or a main loop context function,
 *                  depending upon usb_config.h options).
 *                  If the firmware needs more time to process the request,
 *                  here would be a good place to use the USBDeferStatusStage()
 *                  USB stack API function.
 *******************************************************************/
void UserGetReportHandler(void)
{
    bool currentButtonState = BUTTON_IsPressed(DEVICE_HID_UPS_SIMULATE_DISCHARGE_BUTTON);

    switch(SetupPkt.W_Value.v[0])
    {
        //*********************************************************************
        //  Title:
        //    PowerSummaryID Report
        //
        //  Description:
        //    The PowerSummaryID report provides an ID for the PowerSummary
        //    collection.  This number is arbitrary and can be any constant as
        //    long as it is unique for the device.  Note - the STRING_INDEX()
        //    entry is used in the HID report.  The value returned by this
        //    function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_POWER_SUMMARY_ID        |
        //         |---------------------------------------------------------------|
        //      1  |                         PowerSummaryID                        |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_POWER_SUMMARY_ID:     //PowerSummaryID
            hid_feature_data[0] = POWER_SUMMARY_POWER_SUMMARY_ID;
            hid_feature_data[1] = 1;
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iName Report
        //
        //  Description:
        //    iName is the string index into the string descriptor array that
        //    describes the name of the product.  Note - the STRING_INDEX()
        //    entry is used in the HID report.  The value returned by this
        //    function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_NAME                  |
        //         |---------------------------------------------------------------|
        //      1  |                         iName                                 |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_NAME:
            hid_feature_data[0] = POWER_SUMMARY_I_NAME;
            hid_feature_data[1] = 1;      //iName
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iProduct Report
        //
        //  Description:
        //    iProduct is the string index into the string descriptor array that
        //    describes the product.  Note - the STRING_INDEX()
        //    entry is used in the HID report.  The value returned by this
        //    function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_PRODUCT               |
        //         |---------------------------------------------------------------|
        //      1  |                         iProduct                              |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_PRODUCT:
            hid_feature_data[0] = POWER_SUMMARY_I_PRODUCT;
            hid_feature_data[1] = 2;      //iProduct
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iSerialNumber Report
        //
        //  Description:
        //    iSerialNumber is the string index into the string descriptor array
        //    that gives the products unique serial number.  Note - the STRING_INDEX()
        //    entry is used in the HID report.  The value returned by this
        //    function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_SERIAL_NUMBER         |
        //         |---------------------------------------------------------------|
        //      1  |                         iSerialNumber                         |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_SERIAL_NUMBER:
            hid_feature_data[0] = POWER_SUMMARY_I_SERIAL_NUMBER;
            hid_feature_data[1] = 4;      //iSerialNumber
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iDeviceChemistry Report
        //
        //  Description:
        //    iDeviceChemistry is the string index into the string descriptor
        //    array that describes the chemistry of the battery in use.
        //    Note - the STRING_INDEX() entry is used in the HID report.
        //    The value returned by this function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_DEVICE_CHEMISTRY      |
        //         |---------------------------------------------------------------|
        //      1  |                         iDeviceChemistry                      |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_DEVICE_CHEMISTRY:
            hid_feature_data[0] = POWER_SUMMARY_I_DEVICE_CHEMISTRY;
            hid_feature_data[1] = 3;      //iDeviceChemistery
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iOEMInformation Report
        //
        //  Description:
        //    iOEMInformation is the string index into the string descriptor
        //    array that describes the OEM information about the device
        //    Note - the STRING_INDEX() entry is used in the HID report.
        //    The value returned by this function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_OEM_INFORMATION       |
        //         |---------------------------------------------------------------|
        //      1  |                         iOEMInformation                       |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_OEM_INFORMATION:
            hid_feature_data[0] = POWER_SUMMARY_I_OEM_INFORMATION;
            hid_feature_data[1] = 1;      //iOEMInformation
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iManufacturerName Report
        //
        //  Description:
        //    iManufacturerName is the string index into the string descriptor
        //    array that contains the Manufacturer's name
        //    Note - the STRING_INDEX() entry is used in the HID report.
        //    The value returned by this function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_MANUFACTURER_NAME     |
        //         |---------------------------------------------------------------|
        //      1  |                         iManufacturerName                     |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_MANUFACTURER_NAME:
            hid_feature_data[0] = POWER_SUMMARY_I_MANUFACTURER_NAME;
            hid_feature_data[1] = 1;      //iManufacturerName
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    iManufacturer Report
        //
        //  Description:
        //    iManufacturer is the string index into the string descriptor
        //    array that contains the Manufacturer info
        //    Note - the STRING_INDEX() entry is used in the HID report.
        //    The value returned by this function should match that number
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_I_MANUFACTURER          |
        //         |---------------------------------------------------------------|
        //      1  |                         iManufacturer                         |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_I_MANUFACTURER:
            hid_feature_data[0] = POWER_SUMMARY_I_MANUFACTURER;
            hid_feature_data[1] = 1;      //iManufacturer
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    Voltage Information Report
        //
        //  Description:
        //    This report gives information about the voltage of the device
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_VOLTAGE_INFO            |
        //         |---------------------------------------------------------------|
        //      1  |                         ConfigVoltage (byte 0)                |
        //         |---------------------------------------------------------------|
        //      2  |                         ConfigVoltage (byte 1)                |
        //         |---------------------------------------------------------------|
        //      3  |                         Voltage (byte 0)                      |
        //         |---------------------------------------------------------------|
        //      4  |                         Voltage (byte 1)                      |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_VOLTAGE_INFO:
            hid_feature_data[0] = POWER_SUMMARY_VOLTAGE_INFO;
            hid_feature_data[1] = 0;          //ConfigVoltage - Nominal Voltage
            hid_feature_data[2] = 5;

            hid_feature_data[3] = 0xFF;          //Voltage - Actual Voltage
            hid_feature_data[4] = 4;

            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,5,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    Current Information Report
        //
        //  Description:
        //    This report gives information about the current of the device
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_VOLTAGE_INFO            |
        //         |---------------------------------------------------------------|
        //      1  |                         ConfigCurrent (byte 0)                |
        //         |---------------------------------------------------------------|
        //      2  |                         ConfigCurrent (byte 1)                |
        //         |---------------------------------------------------------------|
        //      3  |                         Current (byte 0)                      |
        //         |---------------------------------------------------------------|
        //      4  |                         Current (byte 1)                      |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_CURRENT_INFO:
            hid_feature_data[0] = POWER_SUMMARY_VOLTAGE_INFO;
            hid_feature_data[1] = 0;          //ConfigCurrent - Nominal Current
            hid_feature_data[2] = 5;

            hid_feature_data[3] = 0xFF;          //Current - Actual Current
            hid_feature_data[4] = 4;

            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,5,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    PresentStatus Report
        //
        //  Description:
        //    The present status report gives information about the current state
        //    of the device.
        //
        //  Format:
        //    byte |       bit 7      |       bit 6       |      bit 5      |       bit 4       |    bit 3    |      bit 2      |           bit 1           |           bit 0             |
        //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_STATUS_INFO                                                                                                                    |
        //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        //      1  | ShutdownImminent | ShutdownRequested | OverTemperature | OverCharged       | Overload    | InternalFailure | Good                      | Present                     |
        //         |----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        //      2  |  BatteryPresent  | ACPresent         | NeedReplacement | ConditionningFlag | Discharging | Charging        | RemainingTimeLimitExpired | BelowRemainingCapacityLimit |
        //         ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_STATUS_INFO:
            hid_feature_data[0] = POWER_SUMMARY_STATUS_INFO;
            //check the pushbutton
            if(currentButtonState == true)
            {
                //if it is pressed then we are simulating a discharge state
                //  no AC present.

                //If the capacity is less than 5%
                if(capacity < 5)
                {
                    //then report that a shutdown is imminent
                    hid_feature_data[1] = 0xC3;
                }
                else
                {
                    hid_feature_data[1] = 0x03;
                }
                hid_feature_data[2] = 0x88;
            }
            else
            {
                //We are AC powered
                hid_feature_data[1] = 0x03;

                //if the capacity is at 100%
                if(capacity == 100)
                {
                    //Then we can say that we are no longer charging
                    hid_feature_data[2] = 0xC0;
                }
                else
                {
                    //otherwise continue charging
                    hid_feature_data[2] = 0xC4;
                }
            }
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,3,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    Capacity Mode Report
        //
        //  Description:
        //    CapacityMode describes in what format all of the other capacity
        //    reports are reported (mAH, mwH, percentage, etc).  See section
        //    4.2.3 of the HID Power device specification (v1) for more information
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_CAPACITY_MODE           |
        //         |---------------------------------------------------------------|
        //      1  |                         CapacityMode                          |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_CAPACITY_MODE:
            hid_feature_data[0] = POWER_SUMMARY_CAPACITY_MODE;
            hid_feature_data[1] = 2;   //CapacityMode
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    DesignCapacity Report
        //
        //  Description:
        //    DesignCapacity reflects the capacity that the battery was designed
        //    for in the units specified by the CapacityMode report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_DESIGN_CAPACITY         |
        //         |---------------------------------------------------------------|
        //      1  |                         DesignCapacity                        |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_DESIGN_CAPACITY:        //DesignCapacity
            hid_feature_data[0] = POWER_SUMMARY_DESIGN_CAPACITY;
            hid_feature_data[1] = 100;
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    RemainingCapacity Report
        //
        //  Description:
        //    RemainingCapacity reflects the capacity left in the battery
        //    in the units specified by the CapacityMode report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_REMAINING_CAPACITY      |
        //         |---------------------------------------------------------------|
        //      1  |                         RemainingCapacity                     |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_REMAINING_CAPACITY:        //RemainingCapacity
            hid_feature_data[0]=POWER_SUMMARY_REMAINING_CAPACITY;
            hid_feature_data[1] = capacity;
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    FullChargeCapacity Report
        //
        //  Description:
        //    FullChargeCapacity reflects the capacity of the battery when it
        //    is fully charged in the units specified by the CapacityMode report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_DESIGN_CAPACITY         |
        //         |---------------------------------------------------------------|
        //      1  |                         FullChargeCapacity                    |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_FULL_CHARGE_CAPACITY:       //full charge capacity
            hid_feature_data[0] = POWER_SUMMARY_FULL_CHARGE_CAPACITY;
            hid_feature_data[1] = 100;
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    RemainingCapacityLimit Report
        //
        //  Description:
        //    RemainingCapacityLimit reflects the capacity at which the battery
        //    will warn the PC that the power is passed the limit.
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |       Report ID = POWER_SUMMARY_REMAINING_CAPACITY_LIMIT      |
        //         |---------------------------------------------------------------|
        //      1  |                         RemainingCapacityLimit                |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_REMAINING_CAPACITY_LIMIT:        //RemainingCapacityLimit
            hid_feature_data[0] = POWER_SUMMARY_REMAINING_CAPACITY_LIMIT;
            hid_feature_data[1] = 0x05;
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    WarningCapacityLimit Report
        //
        //  Description:
        //    WarningCapacityLimit reflects a capacity at which the unit will
        //    warn the PC of a low battery in units specified in the CapacityMode
        //    report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_WARNING_CAPACITY_LIMIT  |
        //         |---------------------------------------------------------------|
        //      1  |                         WarningCapacityLimit                  |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_WARNING_CAPACITY_LIMIT:        //WarningCapacityLimit
            hid_feature_data[0] = POWER_SUMMARY_WARNING_CAPACITY_LIMIT;
            hid_feature_data[1] = 20;       //20%
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    CapacityGranularity1 Report
        //
        //  Description:
        //    CapacityGranularity1 reflects a capacity at which the unit will
        //    warn the PC of a low battery in units specified in the CapacityMode
        //    report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_CAPACITY_GRANULARITY_1  |
        //         |---------------------------------------------------------------|
        //      1  |                         CapacityGranularity1                  |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_CAPACITY_GRANULARITY_1:        //CapacityGranularity1
            hid_feature_data[0] = POWER_SUMMARY_CAPACITY_GRANULARITY_1;
            hid_feature_data[1] = 5;        //5% less
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    CapacityGranularity2 Report
        //
        //  Description:
        //    CapacityGranularity2 reflects a capacity at which the unit will
        //    warn the PC of a low battery in units specified in the CapacityMode
        //    report
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_CAPACITY_GRANULARITY_2  |
        //         |---------------------------------------------------------------|
        //      1  |                         CapacityGranularity2                  |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_CAPACITY_GRANULARITY_2:        //CapacityGranularity2
            hid_feature_data[0] = POWER_SUMMARY_CAPACITY_GRANULARITY_2;
            hid_feature_data[1] = 5;        //5% less
            USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,2,USB_EP0_NO_OPTIONS);
            break;

        //*********************************************************************
        //  Title:
        //    RunTimeToEmpty Report
        //
        //  Description:
        //    This report sends the number of seconds of capacity
        //
        //  Format:
        //    byte | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
        //         |---------------------------------------------------------------|
        //      0  |             Report ID = POWER_SUMMARY_RUN_TIME_TO_EMPTY       |
        //         |---------------------------------------------------------------|
        //      1  |                         RunTimeToEmpty (byte 0)               |
        //         |---------------------------------------------------------------|
        //      2  |                         RunTimeToEmpty (byte 1)               |
        //         -----------------------------------------------------------------
        //      3  |                         RunTimeToEmpty (byte 2)               |
        //         -----------------------------------------------------------------
        //*********************************************************************
        case POWER_SUMMARY_RUN_TIME_TO_EMPTY:
            {
                uint16_t RunTimeToEmpty;

                //RunTimeToEmpty.Val = (60u * 60u * 1u * capacity)/100u;	//Basically want this, but since runtime division is expensive, better to do the below instead.
                RunTimeToEmpty = (36u * (uint16_t)capacity);
                //60 sec/min * 60 min/hr * 1hr capacity(typically) * current_capacity/100 = seconds of capacity left

                hid_feature_data[0] = POWER_SUMMARY_RUN_TIME_TO_EMPTY;
                hid_feature_data[1] = RunTimeToEmpty & 0x00FF;
                hid_feature_data[2] = ((RunTimeToEmpty & 0xFF00) >> 8);
                hid_feature_data[3] = 0u;
                USBEP0SendRAMPtr((uint8_t*)&hid_feature_data,4,USB_EP0_NO_OPTIONS)
            }
            break;

        //Doing nothing will result in all other report IDs to be STALLed
        default:
            break;
    }
}


