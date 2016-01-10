/*********************************************************************
 *
 *   Microchip USB HID Bootloader v1.01 for PIC18F46J50 Family Devices
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        MPLAB C18 3.46+ or XC8 v1.21+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") for its PIC(R) Microcontroller is intended and
 * supplied to you, the Company's customer, for use solely and
 * exclusively on Microchip PIC Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS"CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * File Version  Date       Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1.0           06/19/2008 Original Version.  Adapted from 
 *                          MCHPFSUSB v2.1 HID Bootloader
 *                          for PIC18F87J50 Family devices.
 * 2.9j          06/10/2013 Improved software entry point into bootloader
 *                          at 0x001C.  Some other enhancements.
 *                          Changed LED blink pattern to use only 1 LED and
 *                          consume less code space.  Added #define option to
 *                          disable LED blinking and I/O pushbutton entry
 *                          altogether.  See usb_config.h settings.
 * 2.9j+         09/23/2013 Modified project to be buildable with XC8 v1.21
 *                          or later compiler (as well as C18 v3.46+). Also
 *                          re-organized and renamed several files to make this
 *                          project look more like other projects in the MLA.
 ********************************************************************/

/*********************************************************************
IMPORTANT NOTE: This code is currently configured to work with the
PIC18F46J50 FS USB Demo Board.  It can be readily adapted to
work with other members of the PIC18F46J50 Family of USB microcontrollers 
as well ('F' and 'LF' versions of PIC18F24J50/25J50/26J50/44J50/45J50/46J50).

However, the default device that is currently selected in the project
may not be the device you are interested.  To change the device:

Replace the linker script with an appropriate version, and
click "Configure --> Select Device" and select the proper
microcontroller.  Also double check to verify that the HardwareProfile.h and
usb_config.h are properly configured to match your desired application
platform.

Verify that the configuration bits are set correctly for the intended
target application, and fix any build errors that result from either
the #error directives, or due to I/O pin count mismatch issues (such
as when using a 28-pin device, but without making sufficient changes
to the HardwareProfile.h file)


-------------------------------------------------------------------
NOTE FOR BUILDING WITH C18 COMPILER:
-------------------------------------------------------------------
This project needs to be built with the full compiler optimizations
enabled, and using the Default storage class "Static" or the total
code size will be too large to fit within the program memory
range 0x000-0xFFF.  The default linker script included
in the project has this range reserved for the use by the bootloader,
but marks the rest of program memory as "PROTECTED".  If you try to
build this project with the compiler optimizations turned off, or
you try to modify some of this code, but add too much code to fit
within the 0x000-0xFFF region, a linker error like that below may occur:

Error - section '.code' can not fit the section. Section '.code' length=0x00000020
To fix this error, either optimize the program to fit within 0x000-0xFFF
(such as by turning on all compiler optimizations, and making sure the
"default storage class" is set to "Static"), or modify the linker
and vector remapping (as well as the application projects) to allow this
bootloader to use more program memory.

-------------------------------------------------------------------
NOTE FOR BUILDING THIS BOOTLOADER FIRMWARE WITH THE XC8 COMPILER:
-------------------------------------------------------------------
To build this code with the XC8 compiler, make sure to use the linker
option:
ROM ranges: default,-1000-XXXXXX   //Where "XXXXXX" is the last implemented flash memory
address, excluding the config bit region (ex: "default,-1000-FFF7" for the 64kB PIC18F46J50)
This setting is found in the XC8 compiler linker settings, Option category: Memory Model.

If any errors are encountered relating to "cannot find space", this
presumably means that either the compiler was configured to build the
code in Free or Standard mode, or that modifications have been made to
the code that have increased the code size to exceed the 0x000-0xFFF program
memory region.  If this error is encountered, make sure to build the project
with all PRO mode optimizations enabled, and/or optimize any user added code
that is causing the project size to exceed the 0x000-0xFFF region.

----------------------------------------------------------------------
NOTE FOR BUILDING APPLICATION FIRMWARE PROJECTS WITH THE XC8 COMPILER:
----------------------------------------------------------------------
When building the application project that is meant to be programmed by this
bootloader, you must use different XC8 linker settings as this project.
For application projects, two linker settings are required:

ROM ranges: default,-0-FFF,-1006-1007,-1016-1017
Codeoffset: 0x1000

When the above settings are implemented, the application firmware will no longer work
without the bootloader present.  Therefore, it is recommended to add the bootloader
firmware output (from this bootloader project) .hex file as a "Loadable" into
the application firmware project.  This will allow the "HEXMATE" tool to run
after building  the application firmware project, which will merge the application
output .hex file contents with the bootloader output .hex file contents (which was
added as a loadable file).

However, in some cases you may encounter build errors during the hex merge operation.
This will occur if there are any overlapping regions in the bootloader firmware
.hex file, with the application firmware .hex file, when the contents of these
overlapping regions are not 100% exact matches to each other.  Normally, only the
configuration bit settings will be overlapping between the two projects.

Therefore, to prevent build errors, the configuration bit settings between the
bootloader firmware project and the application firmware project must be set to
100% exactly identical values (or they must only be set in one of the projects,
to eliminate the overlapping region altogether).


----------------------Bootloader Entry------------------------------------------
Entry into this bootloader firmware can be done by either of two possible
ways:

1.  I/O pin check at power up/after any reset.  and/or:
2.  Software entry via absolute jump to address 0x001C.

The I/O pin check method is the most rugged, since it does not require the 
application firmware image to be intact (at all) to get into the bootloader
mode.  However, software entry is also possible and may be more convenient
in applications that do not have user exposed pushbuttons available.

When the "application" image is executing, it may optionally jump into
bootloader mode, by executing a _asm goto 0x001C _endasm instruction.  
Before doing so however, the firwmare should configure the current
clock settings to be compatible with USB module operation, in they
are not already.  Once the goto 0x001C has been executed the USB device 
will detach from the USB bus (if it was previously attached), and will 
re-enumerate as a HID class device with a new VID/PID (adjustable via 
usb_dsc.c settings), which can communicate with the associated
USB host software that loads and programs the new .hex file.


--------------------------------------------------------------------------------
Anytime that an application implements flash self erase/write capability, 
special care should be taken to make sure that the microcontroller is operated 
within all datasheet ratings, especially those associated with voltage versus 
frequency.

Operating the device at too high of a frequency (for a given voltage, ex: by
operating at 48MHz at 2.1V, while the device datasheet indicates some higher
value such as 2.35V+ is required) can cause unexpected code operation.  This
could potentially allow inadvertent execution of bootloader or other self
erase/write routines, causing corruption of the flash memory of the application.

To avoid this, all applications that implement self erase/write capability 
should make sure to prevent execution during overclocked/undervolted conditions.

For this reason, enabling and using the microcontroller hardware Brown-out-Reset 
feature is particularly recommended for applications using a bootloader.  If 
BOR is not used, or the trip threshold is too low for the intended application 
frequency, it is suggested to add extra code in the application to detect low 
voltage conditions, and to intentionally clock switch to a lower frequency 
(or put the device to sleep) during the low voltage condition.  Hardware
modules such as the ADC, comparators, or the HLVD (high/low voltage detect)
can often be used for this purpose.


--------------------------------------------------------------------------------
This bootloader supports reprogramming of the microcontroller configuration bits,
however, it is strongly recommended never to do so, unless absolutely necessary.
Reprogramming the config bits is potentially risky, since it requires that the
new configuration bits be 100% compatible with USB operation (ex: oscillator
settings, etc.).  If a .hex file with incorrect config bits is programmed
into this device, it can render the bootloader inoperable.  Additionally,
unexpected power failure or device detachment during the reprogramming of the
config bits could result in unknown values getting stored in the config bits,
which could "brick" the application.

Normally, the application firmware project and this bootloader project should
be configured to use/set the exact same configuration bit values.  Only one set
of configuration bits actually exists in the microcontroller, and these values
must be shared between the bootloader and application firmware.

If the bootloader will not be used to program the configuration
words page, the application firmware's linker script should mark
the entire page as PROTECTED to prevent the linker from inadvertently
placing code on the same erase page as the configuration bits.
*********************************************************************/



/** I N C L U D E S **********************************************************/
#include "usb.h"                         
#include "HardwareProfile.h"
#include "boot_18fxxjxx.h"



/** C O N F I G U R A T I O N ************************************************/
// Note: For a complete list of the available config pragmas and their values, 
// see the compiler documentation, and/or click "Help --> Topics..." and then 
// select "PIC18 Config Settings" in the Language Tools section.

#if defined(PIC18F27J53_PIM)
    // CONFIG1L
    #pragma config WDTEN = OFF, PLLDIV = 2, CFGPLLEN = ON, STVREN = OFF, XINST = OFF
    // CONFIG1H
    #pragma config CPUDIV = OSC1, CP0 = OFF
    // CONFIG2L
    #pragma config OSC = INTOSCPLL, SOSCSEL = LOW, CLKOEC = OFF, FCMEN = OFF, IESO = OFF
    // CONFIG2H
    #pragma config WDTPS = 1024
    // CONFIG3L
    #pragma config DSWDTOSC = T1OSCREF, RTCOSC = T1OSCREF, DSBOREN = OFF, DSWDTEN = OFF, DSWDTPS = G2
    // CONFIG3H
    #pragma config IOL1WAY = OFF, ADCSEL = BIT12, MSSP7B_EN = MSK7
    // CONFIG4L
    #pragma config WPFP = PAGE_127, WPCFG = OFF
    // CONFIG4H
    #pragma config WPDIS = OFF, WPEND = PAGE_WPFP, LS48MHZ = SYS48X8

#else
    #error "Double click this message and add your device specific configuration bit settings."
    //Make sure that the oscillator settings in particular are compatible with USB operation.
    //If the oscillator settings are incorrect/incompatible, this will usually result
    //in either no device showing up on the host, or an "Unknown device" showing up,
    //instead of the proper HID class device.
#endif

/** V A R I A B L E S ********************************************************/
//NOTE: You must not use initalized variables in this bootloader project.  This
//firmware project does not rely on the standard C initializer, which is 
//responsible for setting up initialized variables in RAM.  Therefore, all
//variables will be non-initialized/random at start up.
#ifndef __XC8__
#pragma udata
#endif
unsigned int uint_delay_counter;


//------------------------------------------------------------------------------
//Private prototypes
//------------------------------------------------------------------------------
void main(void);
void BootMain(void);
void LowVoltageCheck(void);
void InitializeSystem(void);
void BlinkUSBStatus(void);



//Special "flash signature" located in the application program memory space (not
//part of the bootloader firmware program space).  This flash signature is used
//to improve application recoverability/robustness, in the event the user unplugs
//the USB cable or AC power is lost during an erase/program/verify sequence.
#ifdef __XC8__
    const unsigned int __at(APP_SIGNATURE_ADDRESS) FlashSignatureWord = APP_SIGNATURE_VALUE;
#else
    #pragma romdata FLASH_SIG_SECTION = APP_SIGNATURE_ADDRESS
    ROM unsigned int FlashSignatureWord = APP_SIGNATURE_VALUE;
    #pragma code
#endif


//Special handling for modified linker script.
#ifndef __XC8__
//Note: This project uses a modified linker script, which does not include the
//c018i.o standard C initializer for C18 projects.  Therefore, we must manually 
//place a goto main() at the hardware reset vector.
#pragma code _entry_scn=0x000000        //Reset vector is at 0x00.  Device begins executing code from 0x00 after a reset or POR event
void _entry (void)
{
    _asm  goto main _endasm
}
#pragma code
#endif



/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This is the first code that executes during boot up of
 *                  the microcontroller.  This code checks to see if execution
 *                  should stay in the "bootloader" mode, or if it should jump
 *                  into the "application" (non-bootloder) execution mode.
 *                  No other unrelated code should be added to this function.
 *
 * Note:            THIS FUNCTION EXECUTES PRIOR TO INITIALIZATION OF THE C
 *                  STACK.  NO C INITIALIZATION OF STATIC VARIABLES OR RESOURCES
 *                  WILL OCCUR, PRIOR TO EXECUTING THIS FUNCTION.  THEREFORE, 
 *                  THE CODE IN THIS FUNCTION MUST NOT CALL OTHER FUNCTIONS OR
 *                  PERFORM ANY OPERATIONS THAT WILL REQUIRE C INITIALIZED
 *                  BEHAVIOR.
 *****************************************************************************/
void main(void)
{
    //Assuming the I/O pin check entry method is enabled, check the I/O pin value
    //to see if we should stay in bootloader mode, or jump to normal applicaiton 
    //execution mode.
    #ifdef ENABLE_IO_PIN_CHECK_BOOTLOADER_ENTRY
        //Need to make sure the I/O pin is configured for digital mode so we
        //can sense the digital level on the input pin.
        mInitSwitch2();
        
        //Check Bootload Mode Entry Condition from the I/O pin (ex: place a  
        //pushbutton and pull up resistor on the pin)
        if(sw2 == 1)    
        {
            //If we get to here, the user is not pressing the pushbutton.  We
            //should default to jumping into application run mode in this case.
            //Restore default "reset" value of registers we may have modified temporarily.
            mDeInitSwitch2();
    
            //Before going to application image however, make sure the image
            //is properly signed and is intact.
            goto DoFlashSignatureCheck;
        }
        else
        {
            //User is pressing the pushbutton.  We should stay in bootloader mode
            BootMain();
        }       
    #endif //#ifdef ENABLE_IO_PIN_CHECK_BOOTLOADER_ENTRY    

DoFlashSignatureCheck:    
    //Check if the application region flash signature is valid
    if(*(ROM unsigned int*)APP_SIGNATURE_ADDRESS == APP_SIGNATURE_VALUE)
    {
        //The flash signature was valid, implying the previous
        //erase/program/verify operation was a success.

        //Also make sure the first WORD of program memory in the app space
        //is not blank, meaning there is an application image programmed into the device.
        if(*(ROM unsigned int*)REMAPPED_APPLICATION_RESET_VECTOR != 0xFFFF)
        {
            //Go ahead and jump out of bootloader mode into the application run mode
            #ifdef __XC8__
                #asm
                    goto REMAPPED_APPLICATION_RESET_VECTOR
                #endasm
            #else   //Must be C18 instead
                _asm goto REMAPPED_APPLICATION_RESET_VECTOR _endasm
            #endif
        }
    }
    //else the application image is missing or corrupt.  In this case, we
    //need to stay in the bootloader mode, so the user has the ability to
    //try (again) to re-program a valid application image into the device.

    //We should stay in bootloader mode
    BootMain();

}//end UninitializedMain



/******************************************************************************
 * Function:        void BootMain(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This is the main function for this bootloader mode firmware.
 *                  if execution gets to this function, it is assumed that we
 *                  want to stay in bootloader mode for now.
 *
 * Note:            If adding code to this function, make sure to add it only
 *                  after the C initializer like code at the top of this function.
 *                  Additionally, code written in this project should not assume
 *                  any variables or registers have been initialized by the C
 *                  compiler (since they may not have been, if the user jumped
 *                  from the application run mode into bootloader mode directly).
 *****************************************************************************/
#ifdef __XC8__
void __at(0x30) BootMain(void)
#else
#pragma code BOOT_MAIN_SECTION=0x30
void BootMain(void)
#endif
{
    //NOTE: The c018.o file is not included in the linker script for this project.
    //The C initialization code in the c018.c (comes with C18 compiler in the src directory)
    //file is instead modified and included here manually.  This is done so as to provide
    //a more convenient entry method into the bootloader firmware.  Ordinarily the _entry_scn
    //program code section starts at 0x00 and is created by the code of c018.o.  However,
    //the linker will not work if there is more than one section of code trying to occupy 0x00.
    //Therefore, must not use the c018.o code, must instead manually include the useful code
    //here instead.

    //Make sure interrupts are disabled for this code (could still be on,
    //if the application firmware jumped into the bootloader via software methods)
    INTCON = 0x00;  

    //Initialize the C stack pointer, and other compiler managed items as 
    //normally done in the c018.c file (applicable when using C18 compiler)
    #ifndef __XC8__
        _asm
            lfsr 1, _stack
            lfsr 2, _stack
            clrf TBLPTRU, 0
        _endasm
    #endif

    //Clear the stack pointer, in case the user application jumped into 
    //bootloader mode with excessive junk on the call stack
    STKPTR = 0x00;  

    // End of the important parts of the C initializer.  This bootloader firmware does not use
    // any C initialized user variables (idata memory sections).  Therefore, the above is all
    // the initialization that is required.



    //Call other initialization code and (re)enable the USB module
    InitializeSystem();     //Some USB, I/O pins, and other initialization
    
    //Execute main loop
    while(1)
    {
        ClrWdt();
        
        //Need to call USBDeviceTasks() periodically.  This function takes care of
        //processing non-USB application related USB packets (ex: "Chapter 9" 
        //packets associated with USB enumeration)
        USBDeviceTasks();

        BlinkUSBStatus();   //When enabled, blinks LEDs on the board, based on USB bus state
        
        LowVoltageCheck();  //Regularly monitor voltage to make sure it is sufficient
                            //for safe operation at full frequency and for erase/write
                            //operations.       
        
        ProcessIO();        //This is where all the actual bootloader related data transfer/self programming takes
                            //place see ProcessIO() function in the BootPIC[xxxx].c file.
    }//end while    
}    


#ifndef __XC8__
#pragma code
#endif
/******************************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization routine.
 *                  All required USB initialization routines are called from
 *                  here.
 *
 *                  User application initialization routine should also be
 *                  called from here.                  
 *
 * Note:            None
 *****************************************************************************/
void InitializeSystem(void)
{
    //Initialize oscillator settings compatible with USB operation.  Note,
    //these may be application specific!

    //On most PIC18FxxJxx USB microcontrollers, the PLL will not power up and be enabled
    //by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
    //This allows the device to power up at a lower initial operating frequency, which can be
    //advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
    //operation.  On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit to
    //power up the PLL.
    #if defined(__18F27J53)

        //Clock switch to primary clock source.  Might not have been running
        //from this if the bootloader is called from the application firmware.
        OSCCON = 0x60;
        OSCTUNEbits.PLLEN = 1;  //Enable the PLL
        //Wait 2+ms until the PLL locks before enabling USB module
		DelayRoutine(0x300);
        //Device switches over automatically to PLL output after PLL is locked and ready.

        //Initialize I/O pins for "lowest" power.  When in USB suspend mode, total +5V VBUS current consumption
        //should reduce to <2.5mA in order to meet USB compliance specifications.

        //Ordinarily, to initialize I/O pins for lowest power, any unused I/O pins would be configured
        //as outputs and driven either high or low.  However, if this code is left unmodified, but is used in a real
        //application, I/O pins as outputs could cause contention with externally connected signals.  Therefore
        //this code does not actually drive unused I/Os as outputs, but uses "softer" methods, like making
        //analog capable pins as analog (to disable the digital input buffer, which wastes power when left floating)

        //This code should be replaced with code more specific to the intended target application I/O pin usage.
        //The below code by itself will not achieve the lowest possible power consumption.

        ANCON0 = 0x00;          //All analog, to disable the digital input buffers
        ANCON1 = 0x00;          //All analog, digital input buffers off, bandgap off

    #else
        #warning "Double Click this message.  Please make sure the InitializeSystem() function correctly configures your hardware platform."
        //Also make sure the correct board is selected in usb_config.h.  If
        //everything is correct, comment out the above "#error ..." line
        //to suppress the error message.
    #endif
    
	
    //The USB specifications require that USB peripheral devices must never source
    //current onto the +5V VBUS pin.  Additionally, USB peripherals should not source
    //current on D+ or D- when the host/hub is not actively powering the VBUS line.
    //When designing a self powered (as opposed to bus powered) USB peripheral
    //device, the firmware should make sure not to turn on the USB module and D+
    //or D- pull up resistor unless Vbus is actively powered.  Therefore, the
    //firmware needs some means to detect when VBUS is being powered by the host.
    //A 5V tolerant I/O pin can be connected to VBUS (through a resistor), and
    //can be used to detect when VBUS is high (host actively powering), or low
    //(host is shut down or otherwise not supplying power - note weak pull down, ex: 100k,
    //should also be placed on the PCB on VBUS to ensure low/non-floating reading).
    //The USB firmware can then periodically poll this I/O pin to know when it is okay
    //to turn on the USB module/D+/D- pull up resistor.  When designing a purely bus powered
    //peripheral device, it is not possible to source current on D+ or D- when the
    //host is not actively providing power on VBUS. Therefore, implementing this
    //bus sense feature is optional.  This firmware can be made to use this bus
    //sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
    //usb_config.h file.
    #if defined(USE_USB_BUS_SENSE_IO)
        tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

    //If the host PC sends a GetStatus (device) request, the firmware must respond
    //and let the host know if the USB peripheral device is currently bus powered
    //or self powered.  See chapter 9 in the official USB specifications for details
    //regarding this request.  If the peripheral device is capable of being both
    //self and bus powered, and it can consume >100mA from VBUS, it should not
    //return a hard coded value for this request.
    //Instead, firmware should check if it is currently self or bus powered, and
    //respond accordingly.  If the hardware has been configured like demonstrated
    //on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
    //currently selected power source.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
    //has been defined in usb_config.h, and that an appropriate I/O pin has been mapped
    //to it in HardwareProfile.h.  This feature is optionional and is not required
    //to be implemented on bus powered only or self/bus powered device that never
    //take more than 100mA from VBUS.
    #if defined(USE_SELF_POWER_SENSE_IO)
        tris_self_power = INPUT_PIN;
    #endif

    UserInit();                 //Initialize bootloader application variables (see Bootxxxx.c file)
    #if defined(ENABLE_USB_LED_BLINK_STATUS)
        mLED1 = 0;      //LED off initially
        mLED1Tris = 0;  //Configure pin as output
    #endif

	//Initialize USB module only after oscillator and other settings are compatible with USB operation
    USBDeviceInit();	//Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem


    


/******************************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs corresponding to
 *                  the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  usb_device_state is declared in usbmmap.c and is modified
 *                  in usb_device.c, usbctrltrf.c, and usb9.c
 *****************************************************************************/
void BlinkUSBStatus(void)
{
    #ifdef ENABLE_USB_LED_BLINK_STATUS
        static unsigned int led_count = 0;

        led_count--;
        if(led_count == 0)
        {
            led_count = 0x4E00;     //Value determines blink interval
            if(USBGetDeviceState() < CONFIGURED_STATE)
            {
                mLED1 = 1;          //Turn on the LED continuously
            }
            else
            {
                mLED1 = !mLED1;     //Toggle the LED state
            }
        }
    #endif //#ifdef ENABLE_USB_LED_BLINK_STATUS
}//end BlinkUSBStatus


//LVDSTAT feature only available on "F" devices (not available in "LF" devices)
#if defined(__18F27J53)
void LowVoltageCheck(void)
{
    //Verify voltage is sufficient for safe bootloader operations.  If the
    //voltage is too low, put microcontroller to sleep to avoid potential
    //overclocking, which could cause unintended code execution (which would
    //be unsafe in a bootloader).
    if(WDTCONbits.LVDSTAT == 0)
    {
        //The voltage is too low for "safe" bootloader operation.
        //Operate at low frequency, and stay in this condition until the voltage
        //has solidly recovered back to a safe level.
        OSCCON = 0x03;          //31kHz Internal oscillator
        UCONbits.SUSPND = 0;
        UCONbits.USBEN = 0;     //Disable USB module
        INTCON = 0x00;          //Make certain interrupts cannot interrupt this code

        //Loop until the voltage has recovered sufficiently
        uint_delay_counter = 0x400;
        while(uint_delay_counter)
		{
            if(WDTCONbits.LVDSTAT == 1)
            {
                uint_delay_counter--;                
            }
            else
            {
                uint_delay_counter = 0x400;
            }
        	ClrWdt();
		}
        //If we get to here, the voltage must have risen above the trip point
        //Go ahead and reset the microcontroller so that is can resume
        //normal operation, now that the voltage is presumably sufficient (again).
        Reset();
    }       
}
#else
void LowVoltageCheck(void)
{
    #warning "Recommended to implement code here to check VDD.  Voltage detection can be done using ADC, HVLD, comparators, or other means."
}    
#endif








// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA* each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.
//
// Note *: The "usb_20.pdf" specs indicate 500uA or 2.5mA, depending upon device classification. However,
// the USB-IF has officially issued an ECN (engineering change notice) changing this to 2.5mA for all
// devices.  Make sure to re-download the latest specifications to get all of the newest ECNs.

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *                  suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *                  mode, the host may wake the device back up by sending non-
 *                  idle state signalling.
 *
 *                  This call back is invoked when a wakeup from USB suspend
 *                  is detected.
 *
 * Note:            Before returning from this function, make sure that the
 *                  oscillator settings are fully compatible with USB module
 *                  operation.
 *                  If using the two-speed startup feature, wakeup and execution
 *                  will occur before the main oscillator + PLL has had a chance
 *                  to start.  Device will run from INTOSC (no PLL).  However, the
 *                  USB module cannot be clocked and receive correct USB data when
 *                  it is not clocked with the correct frequency clock source.
 *                  Therefore, when using two-speed startup, should execute software
 *                  delay to prevent any other code from executing until the main
 *                  oscillator is ready.
 *                  The host will allow at least 10ms for USB "resume recovery", during
 *                  which it will not try to communicate with the device.
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
    //This code delays ~5ms @ 8MHz to execute (using C18 3.21 with full 
    //optimizations enabled), but takes much less time at 48MHz.  This delay
    //is to make sure the PLL is enabled and locked, in case two speed startup
    //was enabled
    DelayRoutine(0x300);  //Device will switch clocks (if using two-speed startup) while executing this delay function
    
    //Primary oscillator and PLL should be running by now.

    //Do not return from this function until the oscillator is correctly configured and
    //running in a USB compatible mode/frequency.


    //Additional code for re-enabling I/O pins and increasing power draw from VBUS
    //may be placed here (up to the maximum of 100mA [when unconfigured] or the
    //amount specified in the configuration descriptor (when configured).
}



/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
    static unsigned char OSCCONSave;

    //Configure I/O pins for lowest power.  This will be application specific.
    #ifdef ENABLE_USB_LED_BLINK_STATUS
        mLED1 = 0;  //Turn off LED
    #endif

    //Go to sleep to save power.  However, before doing so, clock switch to FRC 500kHz,
    //so that when we wake back up, we start back at FRC 500kHz, rather than immediately
    //switching from 0Hz to 96MHz PLL.
    OSCCONSave = OSCCON;
    Sleep();            //Go to sleep, wake up when a USB activity event occurs
    //If using the WDT, should go back to sleep if awoke by WDT instead of USBIF
    while((USBIF_FLAG == 0) && (RCONbits.TO == 0))      
    {
        Sleep();        //Entry into sleep clears WDT count, much like executing ClrWdt() instruction
    }
    //We are currently running from the FRC at 500kHz.  Go ahead and initiate
    //switch back to the original clock settings (presumably based on the 96MHz PLL)
    OSCCON = OSCCONSave;    //Initiate clock switch request (note: actual swtich doesn't occur until after the PLL is locked, when switching to a PLL mode)



    //After the USB suspend event ends, you should re-configure your I/O pins
    //for normal operation mode (which is allowed to consume more current).
    //However, it is recommended to put this code in the USBCBWakeFromSuspend()
    //function instead of here (so that this function will work with either
    //sleeping or clock switching to a lower frequency).
}


/*******************************************************************
 * Function:        void USBCBInitEP(uint8_t ConfigurationIndex)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 *                  SET_CONFIGURATION request.  This
 *                  callback function should initialize the endpoints
 *                  for the device's usage according to the current
 *                  configuration.
 *
 * Note:            If the host ever "unconfigures" the device, it will
 *                  set the configuration to '0'.  In this case, this
 *                  callback gets called with ConfigurationIndex == 0, where
 *                  the firmware should disable all non-EP0 endpoints (until
 *                  the next non-zero SET_CONFIGURATION request is received,
 *                  which will cause this callback to execute again).
 *******************************************************************/
void USBCBInitEP(uint8_t ConfigurationIndex)
{
    //Check what configuration "index" the host has requested us to select.
    //Configuration index 0 is special and represents that the device should be
    //un-configured.  However, when the host sets the configuration (with index
    //matching the valid/implemented configuration from the configuration descriptor),
    //the firmware should enable the application endpoints associated with that
    //configuration, and (re)initialize all application state variables associated
    //with the USB application endpoints operation.
    if(ConfigurationIndex == 1)     //This application only implements one configuration, with index == 1.
    {
        //The host sent us a non-zero set configuration index.  In this
        //case we should prepare the application endpoints to be ready
        //to use, and to (re-)initialize any application variables associated
        //with the endpoints.
        HIDInitEP();

        //(Re-)Initialize the application variables associated with the USB interface
        UserInit();                     // See BootPIC[xxxx].c.  Initializes the bootloader firmware state machine variables.
    }
    //else the host set the configuration back to 0 (indicating unconfigured), or
    //to some higher (non-implemented value).  In either case, we don't need to
    //do anything specifically, unless the application requires some kind of
    //"safe shutdown" code to execute after the host has deconfigured the device.

}



/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB stack receives a
 *                  new control transfer SETUP packet from the host.  The
 *                  USB stack handles normal USB "Chapter 9" requests internally,
 *                  but some control transfer requests are class specific.  In
 *                  order to handle these class specific requests, you must call
 *                  the class handler's firmware control transfer handler function.
 *                  If implementing a composite device with multiple classes
 *                  implemented, call each of the handlers in the below callback.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}


//Compiler mode and version check.  This code needs to fit within the [0x000-0xFFF] program
//memory region that is reserved for use by the bootloader.  However, if this
//code is built in XC8 Standard or Free mode (instead of PRO),
//the code may be too large to fit within the region, and a variety of linker
//error messages (ex: "can't find space") will result.  Unfortunately these
//linker error messages can be cryptic to a user, so instead we add a deliberate
//#error to make a more human friendly error appear, in the event the wrong
//compiler mode is attempted to use to build this code.  If you get this error
//message, please upgrade to the PRO compiler, and then use the mode
//(ex: build configuration --> XC8 compiler --> Option Categories: Optimizations --> Operation Mode: PRO)
#ifdef __XC8__
    #if _HTC_EDITION_ < 2   //Check if PRO, Standard, or Free mode
    #error "This bootloader project must be built in PRO mode to fit within the reserved region.  Double click this message for more details."
    #endif
#endif

/** EOF main.c ***************************************************************/
