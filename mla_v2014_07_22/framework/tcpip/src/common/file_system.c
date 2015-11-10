/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    file_system.c

  Summary:
    

  Description:
    File system access interface layer Source File

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <2014> released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#include "tcpip/tcpip.h"

#if defined(STACK_USE_MDD)

int FileSystemInit(void)
{
    #if defined STACK_USE_MPFS2
        MPFSInit();
    #elif defined STACK_USE_MDD
        return FSInit();
    #endif

    return true;
}


FILE_HANDLE FileOpen(const char * fileName, const char *mode)
{
    #if defined STACK_USE_MPFS2
        return MPFSOpen((uint8_t*)fileName);
    #elif defined STACK_USE_MDD
        return FSfopen(fileName, mode);
    #endif
}

FILE_HANDLE FileOpenROM(const char * fileName, const char *mode)
{
    #if defined STACK_USE_MPFS2
        return MPFSOpenROM((uint8_t*)fileName);
    #elif defined STACK_USE_MDD
        return FSfopen(fileName, mode);
    #endif
}

int FileClose(FILE_HANDLE fh)
{
    #if defined STACK_USE_MPFS2
        MPFSClose(fh);
    #elif defined STACK_USE_MDD
        return FSfclose(fh);
    #endif

    return 0;
}

size_t FileRead(void *ptr, size_t size, size_t n, FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        uint16_t length;
        length = size * n;
        return MPFSGetArray(stream, (uint8_t*)ptr, length);
    #elif defined STACK_USE_MDD
        if(ptr == NULL)
        {
            return 0;
        }
        else
        {
            return FSfread(ptr, size, n, stream);
        }
    #endif
}

int FileSeek(FILE_HANDLE stream, long offset, int whence)
{
    #if defined STACK_USE_MPFS2
        bool status;
        status = MPFSSeek(stream, offset, whence);
        if(status == true)
            return 0;
        else
            return -1;

    #elif defined STACK_USE_MDD
        return FSfseek(stream, offset, whence);
    #endif
}

long FileTell(FILE_HANDLE fh)
{
    #if defined STACK_USE_MPFS2
        return MPFSGetPosition(fh);
    #elif defined STACK_USE_MDD
        return FSftell(fh);
    #endif
}

int FileEOF(FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        return MPFSGetBytesRem(stream);
    #elif defined STACK_USE_MDD
        return FSfeof(stream);
    #endif
}

int FileFormat(char mode, long int serialNumber, char *volumeID)
{
    #if defined STACK_USE_MPFS2
        int status;
        status = MPFSFormat();
        if(status == MPFS_INVALID_HANDLE)
            return -1;
        else
            return 0;
    #elif defined STACK_USE_MDD
        return FSformat(mode, serialNumber, volumeID);
    #endif
}

size_t FileWrite(const void *ptr, size_t size, size_t n, FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        uint16_t length;
        length = size * n;
        return MPFSPutArray(stream, (uint8_t*)ptr, length);
    #elif defined STACK_USE_MDD
        return FSfwrite(ptr, size, n, stream);
    #endif
}


size_t FileReadUInt32(uint32_t *ptr, FILE_HANDLE stream)
{
    uint8_t databuff[4];
    *ptr=0x00000000;

    #if defined STACK_USE_MPFS2
        uint16_t retVal;

        retVal=MPFSGetArray(stream, (uint8_t*)ptr, 4);

        if(retVal == 4)//Number of Uints of 4 bytes each Read
        {

            ((uint8_t*)ptr)[3] = databuff[3];
            ((uint8_t*)ptr)[2] = databuff[2];
            ((uint8_t*)ptr)[1] = databuff[1];
            ((uint8_t*)ptr)[0] = databuff[0];

            return 4;//Number of bytes read
        }
        else
            return 0;

    #elif defined STACK_USE_MDD
        size_t retVal;

        retVal= FSfread(databuff, 4, 1, stream);

        if(retVal == 1)//Number of Uints of 4 bytes each Read
        {

            ((uint8_t*)ptr)[3] = databuff[3];
            ((uint8_t*)ptr)[2] = databuff[2];
            ((uint8_t*)ptr)[1] = databuff[1];
            ((uint8_t*)ptr)[0] = databuff[0];

            return 4;//Number of bytes read
        }
        else
            return 0;

    #endif
}

size_t FileReadUInt16(uint16_t *ptr, FILE_HANDLE stream)
{
    uint8_t databuff[2];
    *ptr=0x0000;

    #if defined STACK_USE_MPFS2
        uint16_t retVal;

        retVal=MPFSGetArray(stream, (uint8_t*)ptr, 2);

        if(retVal == 2)//Number of bytes read
        {
            ((uint8_t*)ptr)[1]= databuff[1];
            ((uint8_t*)ptr)[0]= databuff[0];
            return 2;//Number of bytes read
        }
        else
            return 0;

    #elif defined STACK_USE_MDD
        size_t retVal;

        retVal= FSfread(databuff, 2, 1, stream);

        if(retVal == 1)//Number of Uints of 4 bytes each Read
        {
            ((uint8_t*)ptr)[1]= databuff[1];
            ((uint8_t*)ptr)[0]= databuff[0];
            return 2;//Number of bytes read
        }
        else
            return 0;

    #endif
}

#endif //#if defined(STACK_USE_MDD)
