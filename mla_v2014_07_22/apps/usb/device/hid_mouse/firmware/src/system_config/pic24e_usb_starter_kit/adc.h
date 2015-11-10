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

#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

/*** ADC Channel Definitions *****************************************/
typedef enum
{
    ADC_CHANNEL_POTENTIOMETER
} DEMO_ADC_CHANNEL;

typedef enum
{
    ADC_CONFIGURATION_POTENTIOMETER
} DEMO_ADC_CONFIGURATION;

/*********************************************************************
* Function: APP_ADCReadPercentage(DEMO_ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the percentage 
*            of that conversions result (0-100%).
*
* PreCondition: none
*
* Input: DEMO_ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and 
*        not the names of the ADC pins on the device (as the demo code 
*        may be ported to other boards).
*         i.e. - APP_ADCReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint_fast8_t indicating the percentage of the result 0-100%
*
********************************************************************/
uint_fast8_t APP_ADCReadPercentage(DEMO_ADC_CHANNEL channel);
#define APP_ADCReadPercentage(channel) 50


/*********************************************************************
* Function: APP_ADCRead10bit(DEMO_ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the 10-bit
*           representation of this data.
*
* PreCondition: none
*
* Input: DEMO_ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and
*        not the names of the ADC pins on the device (as the demo code
*        may be ported to other boards).
*         i.e. - APP_ADCReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint_fast16_t the right adjusted 10-bit representation of the ADC
*         channel conversion.
*
********************************************************************/
uint_fast16_t APP_ADCRead10bit(DEMO_ADC_CHANNEL channel);
#define APP_ADCRead10bit(channel) 512

/*********************************************************************
* Function: bool APP_ADCSetConfiguration(DEMO_ADC_CONFIGURATION configuration);
*
* Overview: Configures the ADC module to specified setting
*
* PreCondition: none
*
* Input: DEMO_ADC_CONFIGURATION configuration
*
* Output: bool - TRUE if successfully configured.  FALSE otherwise.
*
********************************************************************/
bool APP_ADCSetConfiguration(DEMO_ADC_CONFIGURATION configuration);
#define APP_ADCSetConfiguration(configuration) 

#endif  //ADC_H
