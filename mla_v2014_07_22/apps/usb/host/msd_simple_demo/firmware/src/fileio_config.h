/******************************************************************************
 *
 *                Microchip Memory Disk Drive File System
 *
 ******************************************************************************
 * FileName:        FSconfig.h
 * Processor:       PIC18/PIC24/dsPIC30/dsPIC33/PIC32
 * Dependencies:    None
 * Compiler:        C18/C30/C32
 * Company:         Microchip Technology, Inc.
 * Version:         1.3.0
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PICmicro� Microcontroller is intended and
 * supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
*****************************************************************************/

#ifndef _FS_DEF_
#define _FS_DEF_

// Macro indicating how many drives can be mounted simultaneously.
#define FILEIO_CONFIG_MAX_DRIVES        1

// Defines a character to use as a delimiter for directories.  Forward slash ('/') or backslash ('\\') is recommended.
#define FILEIO_CONFIG_DELIMITER '/'

// Macro defining the maximum supported sector size for the FILEIO module.  This value should always be 512 , 1024, 2048, or 4096 bytes.
// Most media uses 512-byte sector sizes.
#define FILEIO_CONFIG_MEDIA_SECTOR_SIZE 		512

/* *******************************************************************************************************/
/************** Compiler options to enable/Disable Features based on user's application ******************/
/* *******************************************************************************************************/

/**********************************************************************
  Define FILEIO_CONFIG_FUNCTION_SEARCH to disable the functions used to
  search for files.                                                    
  **********************************************************************/
//#define FILEIO_CONFIG_SEARCH_DISABLE

// Define FILEIO_CONFIG_FUNCTION_WRITE to disable the functions that write to a drive.  Disabling this feature will
// force the file system into read-only mode.
//#define FILEIO_CONFIG_WRITE_DISABLE

// Define FILEIO_CONFIG_FUNCTION_FORMAT to disable the function used to format drives.
//#define FILEIO_CONFIG_FORMAT_DISABLE

// Define FILEIO_CONFIG_FUNCTION_DIRECTORY to disable use of directories on your drive.  Disabling this feature will
// limit you to performing all file operations in the root directory.
//#define FILEIO_CONFIG_DIRECTORY_DISABLE

// Define FILEIO_CONFIG_FUNCTION_DRIVE_PROPERTIES to disable the FILEIO_DrivePropertiesGet function.  This function
// will determine the properties of your device, including unused memory.
//#define FILEIO_CONFIG_DRIVE_PROPERTIES_DISABLE

// Define FILEIO_CONFIG_MULTIPLE_BUFFER_MODE_DISABLE to disable multiple buffer mode.  This will force the library to
// use a single instance of the FAT and Data buffer.  Otherwise, it will use one FAT buffer and one data buffer per drive
// (defined by FILEIO_CONFIG_MAX_DRIVES).  If you are only using one drive in your application, this option has no effect.
#define FILEIO_CONFIG_MULTIPLE_BUFFER_MODE_DISABLE

#endif
