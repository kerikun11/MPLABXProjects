/**
  @Company
    Microchip Technology Inc.

  @File Name
    drv_smart_card_uart1.h

  @Summary
    This is the header file for the smart card 7816-3 module.

  @Description
    This file contains the driver API's for devices which has hardware support for
    7816-3 smart card module.
 */

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <year> released Microchip Technology Inc.  All rights reserved.

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

#ifndef _DRV_SMART_CARD_UART1_H
#define	_DRV_SMART_CARD_UART1_H

#include <stdbool.h>
#include "smart_card_pps_macro.h"

//If hardware supports smart card feature
#define SMARTCARD_SUPPORT_IN_HARDWARE
// *****************************************************************************

/* ATR parameters which are required during initialization phase(T=0 or T=1)

  Summary:
    This  Structure defines  ATR parameters required during initialization

  Description:
    None
 *
  Remarks:
    None
 */
typedef struct {
    uint16_t characterGuardTime; // Character Guard Time
    uint32_t workWaitingTime; // Work Waiting Time
    uint32_t blockWaitingTime; // Block Waiting Time
    uint32_t characterWaitingTime; // Character Waiting Time
    uint8_t paritySelection; // Parity selection
    uint8_t cardState; // holds the state of the card
    uint8_t logicConvention; // tells Direct or inverse Convention 
} DRV_SMARTCARD_ATR_CONFIG;


/*******************************************************************************
  Function:
    void DRV_SMARTCARD_Initialize(void)

  Summary:
    Initializes the smart card module.

  Description:
    This function initializes the 7816-3 Smart card supported UART module.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
 *****************************************************************************/
void DRV_SMARTCARD_Initialize(void);


/*******************************************************************************
  Function:
    void DRV_SMARTCARD_DeInitialize(void)

  Summary:
    De-initializes the smart card module.

  Description:
    This function de-initializes 7816-3 Smart card supported UART module.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
 *****************************************************************************/
void DRV_SMARTCARD_DeInitialize(void);

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_BRGSet(uint16_t brg)

  Summary:
    Sets baud rate.
 
  Description:
    This function sets the UART baud rate as per the speed code used in ISO 7816
    standard communication.

  Precondition:
    None

  Parameters:
    brg : baud rate to be set

  Return Values:
    None

  Remarks:
    None
 *****************************************************************************/
void DRV_SMARTCARD_BRGSet(uint16_t brg);

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_ATR_ConfigSet(DRV_SMARTCARD_ATR_PARAM *pATRParams)

  Summary:
    Initializes/saves the ATR parameters used during initialization.
 
  Description:
    This function initializes/saves the ATR values which are used during initialization.

  Precondition:
    None

  Parameters:
    pATRParams : structure containing values of required ATR parameters

  Return Values:
    None

  Remarks:
    None
 *****************************************************************************/
void DRV_SMARTCARD_ATR_ConfigSet(DRV_SMARTCARD_ATR_CONFIG atrParams);


/*******************************************************************************
  Function:
    bool DRV_SMARTCARD_DataGet( uint8_t* pData, uint32_t waitingTimeInETU)

  Summary:
    Receives a byte of data.

  Description:
    This function receives one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    pData - pointer to Data byte to be received
    timeOutInETU - waiting timei ETU
 
  Return Values:
    Returns TRUE on success else returs FALSE

  Example:
        <code>
        {
            //during ATR receive the TS byte;
            uint8_t ts;
            uint32_t atrDelay = 10080;
            DRV_SMARTCARD_DataGet( &ts );
            // Do something else...
        }
        </code>
 
  Remarks:
    None.
 *****************************************************************************/
bool DRV_SMARTCARD_DataGet(uint8_t* pData, uint32_t waitingTimeInETU);

/*******************************************************************************
  Function:
    bool DRV_SMARTCARD_UART1_DataSend(uint8_t data ,uint8_t isLastByte)

  Summary:
    Sends a byte of data.

  Description:
    This function transmits one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    data - Data byte to be transmitted
    isLastByte - whether data is last byte of the data structure or not.
  Return Values:
    Returns TRUE on success else returs FALSE 

   Example:
        <code>
        {
          //Send the Command Bytes: CLA INS P1 P2
          apduCommandBuffer[0] = CLA;
          apduCommandBuffer[1] = INS;
          apduCommandBuffer[2] = P1;
          apduCommandBuffer[3] = P2;
          uint8_t isLastByte = 0;
          for( index = 0; index < 4; index++ )
          {
                if(index == 3)
                {
                  isLastByte = 1;
                }
                DRV_SMARTCARD_UART1_DataSend( apduCommandBuffer[index] );
          }
          // Do something else...
        }
        </code>

  Remarks:
    None.
 *****************************************************************************/
bool DRV_SMARTCARD_DataSend(uint8_t data, uint8_t isLastByte);

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_UART1_T0Config()

  Summary:
    Configures the 7816-3 module for T0 operation.
 
  Description:
    This function configures the 7816-3 module for T0 protocol operation.

  Precondition:
    None.

  Parameters:
    None

  Return Values:
    None

   Example:
        <code>
        {
          //
          for( ptotocolType == T0_PROTOCOL )
          {
                //Configure T0 operation
                DRV_SMARTCARD_UART1_T0Config();
          }
          // Do something else...
        }
        </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_SMARTCARD_UART1_T0Config();


/*******************************************************************************
  Function:
    void DRV_SMARTCARD_UART1_T1Config()

  Summary:
    Configures the 7816-3 module for T0 operation.
 
  Description:
    This function configures the 7816 module for T1 protocol operation.

  Precondition:
    None.

  Parameters:
    None

  Return Values:
    None

   Example:
        <code>
        {
          //
          for( ptotocolType == T1_PROTOCOL )
          {
                //Configure T0 operation
                DRV_SMARTCARD_UART1_T1Config();
          }
          // Do something else...
        }
        </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_SMARTCARD_UART1_T1Config();

#endif	/* DRV_SMART_CARD_UART1 */

