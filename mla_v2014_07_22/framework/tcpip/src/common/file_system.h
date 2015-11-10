/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    file_system.h

  Summary:
    

  Description:
    File system access interface layer header File

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

#ifndef __FILE_SYSTEM_HEADER_FILE_
#define __FILE_SYSTEM_HEADER_FILE_

#if defined STACK_USE_MPFS2
    #include "mpfs2.h"
    typedef MPFS_HANDLE FILE_HANDLE;
    #define INVALID_FILE_HANDLE MPFS_INVALID_HANDLE
#elif defined STACK_USE_MDD
    #include "MDD File System/FSIO.h"
    typedef FSFILE * FILE_HANDLE;
    #define INVALID_FILE_HANDLE NULL
#endif

// Indicates the method for MPFSSeek
    typedef enum
    {
        FILE_SEEK_START     = 0u,   // Seek forwards from the front of the file
        FILE_SEEK_FORWARD,          // Seek forward from the current position
        FILE_SEEK_END,              // Seek backwards from the end of the file
        FILE_SEEK_REWIND            // See backwards from the current position
    } FILE_SEEK_MODE;

int FileSystemInit(void);

FILE_HANDLE FileOpen(const char * fileName, const char *mode);

FILE_HANDLE FileOpenROM(const char * fileName, const char *mode);

int FileClose(FILE_HANDLE fh);

size_t FileRead(void *ptr, size_t size, size_t n, FILE_HANDLE stream);

int FileSeek(FILE_HANDLE stream, long offset, int whence);

long FileTell(FILE_HANDLE fh);

int FileEOF(FILE_HANDLE stream);

int FileFormat(char mode, long int serialNumber, char *volumeID);

size_t FileWrite(const void *ptr, size_t size, size_t n, FILE_HANDLE stream);

size_t FileReadUInt32(uint32_t *ptr, FILE_HANDLE stream);

size_t FileReadUInt16(uint16_t *ptr, FILE_HANDLE stream);

#endif
