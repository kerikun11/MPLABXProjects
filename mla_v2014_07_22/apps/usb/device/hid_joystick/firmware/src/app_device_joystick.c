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

#ifndef USBJOYSTICK_C
#define USBJOYSTICK_C

/** INCLUDES *******************************************************/
#include <usb/usb.h>
#include <usb/usb_device_hid.h>

#include <system.h>

#include <app_led_usb_status.h>

#include <stdint.h>

/** DECLARATIONS ***************************************************/
//http://www.microsoft.com/whdc/archive/hidgame.mspx
#define HAT_SWITCH_NORTH            0x0
#define HAT_SWITCH_NORTH_EAST       0x1
#define HAT_SWITCH_EAST             0x2
#define HAT_SWITCH_SOUTH_EAST       0x3
#define HAT_SWITCH_SOUTH            0x4
#define HAT_SWITCH_SOUTH_WEST       0x5
#define HAT_SWITCH_WEST             0x6
#define HAT_SWITCH_NORTH_WEST       0x7
#define HAT_SWITCH_NULL             0x8

/** TYPE DEFINITIONS ************************************************/
typedef union _INTPUT_CONTROLS_TYPEDEF
{
    struct
    {
        struct
        {
            uint8_t square:1;
            uint8_t x:1;
            uint8_t o:1;
            uint8_t triangle:1;
            uint8_t L1:1;
            uint8_t R1:1;
            uint8_t L2:1;
            uint8_t R2:1;//
            uint8_t select:1;
            uint8_t start:1;
            uint8_t left_stick:1;
            uint8_t right_stick:1;
            uint8_t home:1;
            uint8_t :3;    //filler
        } buttons;
        struct
        {
            uint8_t hat_switch:4;
            uint8_t :4;//filler
        } hat_switch;
        struct
        {
            uint8_t X;
            uint8_t Y;
            uint8_t Z;
            uint8_t Rz;
        } analog_stick;
    } members;
    uint8_t val[7];
} INPUT_CONTROLS;


/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata JOYSTICK_DATA=JOYSTICK_DATA_ADDRESS
            INPUT_CONTROLS joystick_input;
        #pragma udata
    #elif defined(__XC8)
        INPUT_CONTROLS joystick_input @ JOYSTICK_DATA_ADDRESS;
    #endif
#else
    INPUT_CONTROLS joystick_input;
#endif


USB_VOLATILE USB_HANDLE lastTransmission = 0;


/*********************************************************************
* Function: void APP_DeviceJoystickInitialize(void);
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
void APP_DeviceJoystickInitialize(void)
{  
    //initialize the variable holding the handle for the last
    // transmission
    lastTransmission = 0;

    //enable the HID endpoint
    USBEnableEndpoint(JOYSTICK_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
}//end UserInit

/*********************************************************************
* Function: void APP_DeviceJoystickTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceJoystickInitialize() and APP_DeviceJoystickStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceJoystickTasks(void)
{  
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    //If the last transmision is complete
    if(!HIDTxHandleBusy(lastTransmission))
    {
        //If the button is pressed
        if(BUTTON_IsPressed(BUTTON_USB_DEVICE_HID_JOYSTICK) == true)
        {
            //Indicate that the "x" button is pressed, but none others
            joystick_input.members.buttons.x = 1;
            joystick_input.members.buttons.square = 0;
            joystick_input.members.buttons.o = 0;
            joystick_input.members.buttons.triangle = 0;
            joystick_input.members.buttons.L1 = 0;
            joystick_input.members.buttons.R1 = 0;
            joystick_input.members.buttons.L2 = 0;
            joystick_input.members.buttons.R2 = 0;
            joystick_input.members.buttons.select = 0;
            joystick_input.members.buttons.start = 0;
            joystick_input.members.buttons.left_stick = 0;
            joystick_input.members.buttons.right_stick = 0;
            joystick_input.members.buttons.home = 0;

            //Move the hat switch to the "east" position
            joystick_input.members.hat_switch.hat_switch = HAT_SWITCH_EAST;

            //Move the X and Y coordinates to the their extreme values (0x80 is
            //  in the middle - no value).
            joystick_input.members.analog_stick.X = 0;
            joystick_input.members.analog_stick.Y = 0;

            //Send the packet over USB to the host.
            lastTransmission = HIDTxPacket(JOYSTICK_EP, (uint8_t*)&joystick_input, sizeof(joystick_input));

        }
        else
        {
            //Reset values of the controller to default state

            //Buttons
            joystick_input.val[0] = 0x00;
            joystick_input.val[1] = 0x00;

            //Hat switch
            joystick_input.val[2] = 0x08;

            //Analog sticks
            joystick_input.val[3] = 0x80;
            joystick_input.val[4] = 0x80;
            joystick_input.val[5] = 0x80;
            joystick_input.val[6] = 0x80;

            //Send the 8 byte packet over USB to the host.
            lastTransmission = HIDTxPacket(JOYSTICK_EP, (uint8_t*)&joystick_input, sizeof(joystick_input));
        }
    }
    
}//end ProcessIO

#endif
