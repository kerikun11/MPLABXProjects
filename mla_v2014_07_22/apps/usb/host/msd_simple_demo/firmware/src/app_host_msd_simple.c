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
#include "system_config.h"

#include <stdint.h>
#include <stdbool.h>

#include <system.h>

#include <usb/usb.h>

#include "fileio/fileio.h"

#include "app_host_msd_simple.h"

static FILEIO_OBJECT myFile;

typedef enum
{
    WAITING_FOR_ATTACH,
    WRITING_TO_DEVICE,
    WAITING_FOR_DETACH
} USB_HOST_MSD_SIMPLE_DEMO_STATE;

static USB_HOST_MSD_SIMPLE_DEMO_STATE demoState;
static uint8_t deviceAddress = 0;

// Placeholder function for the File I/O driver structure's IO Initialize function
void USBDummyIOInitialize (void * mediaParameters);
void USBDummyIOInitialize (void * mediaParameters) {}

// Declare a FILEIO_DRIVE_CONFIG structure to describe which functions the File I/O library will use to communicate with the media
const FILEIO_DRIVE_CONFIG gUSBDrive =
{
    (FILEIO_DRIVER_IOInitialize)USBDummyIOInitialize,                     // Function to initialize the I/O pins used by the driver.
    (FILEIO_DRIVER_MediaDetect)USBHostMSDSCSIMediaDetect,                   // Function to detect that the media is inserted.
    (FILEIO_DRIVER_MediaInitialize)USBHostMSDSCSIMediaInitialize,           // Function to initialize the media.
    (FILEIO_DRIVER_MediaDeinitialize)USBHostMSDSCSIMediaReset,              // Function to de-initialize the media.
    (FILEIO_DRIVER_SectorRead)USBHostMSDSCSISectorRead,                     // Function to read a sector from the media.
    (FILEIO_DRIVER_SectorWrite)USBHostMSDSCSISectorWrite,                   // Function to write a sector to the media.
    (FILEIO_DRIVER_WriteProtectStateGet)USBHostMSDSCSIWriteProtectState,    // Function to determine if the media is write-protected.
};

/*********************************************************************
* Function: void APP_HostMSDSimpleInitialize(void);
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
void APP_HostMSDSimpleInitialize()
{
    demoState = WAITING_FOR_ATTACH;
}

void APP_MountDrive(uint8_t address)
{
    if (demoState == WAITING_FOR_ATTACH)
    {
        deviceAddress = address;
        demoState = WRITING_TO_DEVICE;
    }
}

/*********************************************************************
* Function: void APP_HostMSDSimpleTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized via
*   the APP_HostMSDSimpleInitialize()  
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostMSDSimpleTasks()
{
    switch(demoState)
    {
        case WAITING_FOR_ATTACH:
            break;

        case WRITING_TO_DEVICE:
            if(FILEIO_MediaDetect(&gUSBDrive, &deviceAddress) == true)
            {
                //Now that we've found a device, we can try to write to it.
                demoState = WRITING_TO_DEVICE;
            }
            else
            {
                break;
            }

            // Attempt to mount the drive described by gUSBDrive as drive 'A'
            // The deviceAddress parameter describes the USB address of the device; it is initialized by the application in the 
            // USB_ApplicationEventHandler function when a new device is detected.
            if(FILEIO_DriveMount ('A', &gUSBDrive, &deviceAddress) == FILEIO_ERROR_NONE)
            {
                // Opening a file with the FILEIO_OPEN_WRITE option allows us to write to the file.
                // Opening a file with the FILEIO_OPEN_CREATE file will create the file if it does not already exist.
                // Opening a file with the FILEIO_OPEN_TRUNCATE file will truncate it to a 0-length file if it already exists.
                if(FILEIO_Open(&myFile, "TEST.TXT", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_TRUNCATE) == FILEIO_RESULT_FAILURE)
                {
                    //Opening the file failed.  Since we can't write to the
                    //  device, abort the write attempt and wait for the device
                    //  to be removed.
                    demoState = WAITING_FOR_DETACH;
                    break;
                }

                //Write some data to the new file.
                FILEIO_Write("This is a test.", 1, 15, &myFile);

                //Always make sure to close the file so that the data gets
                //  written to the drive.
                FILEIO_Close(&myFile);

                // Unmount the drive since it is no longer in use.
                FILEIO_DriveUnmount ('A');

                //Now that we are done writing, we can do nothing until the
                //  drive is removed.
                demoState = WAITING_FOR_DETACH;
            }
            break;

        case WAITING_FOR_DETACH:
            if(FILEIO_MediaDetect(&gUSBDrive, &deviceAddress) == false)
            {
                //The device has been removed.  Now we should wait for a new
                //  device to be attached.
                demoState = WAITING_FOR_ATTACH;
            }
            break;
    }
}
