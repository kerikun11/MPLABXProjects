/********************************************************************
 FileName:		drv_smart_card_uart1.c
 Dependencies:	        See INCLUDES section
 Processor:		PIC24 Microcontrollers
 Hardware:		This demo is natively intended to be used on Exp 16 board.
 			This demo can be modified for use on other hardware platforms.
 Complier:  	        Microchip C30 (for PIC24)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the ?Company?) for its PIC? Microcontroller is intended and
 supplied to you, the Company?s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "smart_card_cfg.h"
#include "drv_smart_card_uart1.h"

#define RETRY_COUNT 4
#define SMART_CARD_REF_CLK 4000000

uint32_t baudRate;
uint32_t scReferenceClock;
uint8_t parityErrorFlag = 0;
uint8_t cwtExceeded = 0;
volatile uint8_t emvDelayLapsedFlag = 0;
uint8_t TC1 = 0x00;
volatile uint8_t delayLapsedFlag = 0;
DRV_SMARTCARD_ATR_CONFIG gATRParams;


uint8_t gtcFlag = 0;
uint8_t wtcFlag = 0;
uint8_t rxrptFlag = 0;
uint8_t txrptFlag = 0;

uint8_t dataReceived = 0;
uint8_t receivedData=0;
/*******************************************************************************
  Function:
    void DRV_SMARTCARD_Initialize(void)

  Description:
    This function initializes the UART module with 7816-3 Smart card support.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_Initialize(void)
{
   SMARTCARD_Drv_SetSwitchCardReset(0); //keep card in reset state
   SMARTCARD_Drv_ResetPin_Direction(0);	//set Smart Card Reset Pin as output
   
   #ifdef SMARTCARD_ENABLE_POWER_THROUGH_PORT_PIN      //Micro controller powers Smarr Card through port pin
		SMARTCARD_Drv_SetSwitchCardPower(0);	//Turn off power to smart card
		SMARTCARD_Drv_PowerPin_Direction(0);	//Setting the port pin which powers smart card as output
   #endif


   SMARTCARD_Drv_CardPresent_Direction(1);              //Input Card Present - SmartCard Conn Active Hi
   SMARTCARD_Drv_SimPresent_Direction(1);               //RG12 Input Card Present - SimCard Conn Active Low


   SMARTCARD_Drv_ClockSet();                            //Set clock to the Smart Card

   MapUART1RxPin();		// Map UART1 Rx pin
   MapUART1TxPin();		// Map UART1 Tx pin

   scReferenceClock = SMART_CARD_REF_CLK;

   baudRate = scReferenceClock/372;

   U1BRG = (unsigned int)((unsigned long)((unsigned long)(FCY/4)/baudRate) - 1);
   
   U1MODEbits.STSEL	= 0;	        //1 stop bit
   U1MODEbits.BRGH	= 1;            //High speed mode
   U1STALbits.URXEN = 1;
   U1STALbits.UTXEN =1;

   // Enable Delay Timer Interrupts for future use
   SMARTCARD_Drv_EnableDelayTimerIntr();
}

    /*******************************************************************************
  Function:
    void DRV_SMARTCARD_DeInitialize(void)

  Description:
    This function deinitializes the UART module with 7816-3 Smart card support.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_DeInitialize(void)
{
  U1MODEbits.UARTEN = 0;  // Turn off UART
  U1STALbits.OERR = 0;
  IEC4bits.U1ERIE = 0;

//  delayLapsedFlag = 1;
//  emvDelayLapsedFlag = 1;
//  SCdrv_DisableDelayTimer45();
//  SCdrv_DisableDelayTimer();

  // Disable Pull-ups at Tx & Rx pins
  SMARTCARD_Drv_DisableTxPinPullUp();
  SMARTCARD_Drv_DisableRxPinPullUp();
}

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_BRG_Set(uint16_t brg)

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
void DRV_SMARTCARD_BRGSet(uint16_t brg)
{
    U1BRG = brg;
}

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_ATR_ConfigSet(uint16_t brg)

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
void DRV_SMARTCARD_ATR_ConfigSet(DRV_SMARTCARD_ATR_CONFIG atrParams)
{
   gATRParams = atrParams;
}

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_UART1_IntrEnable()

  Summary:
    Sets baud rate.

  Description:
    This function enables smart card and all the smart card interrupts.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_UART1_IntrEnable()
{
   IFS0bits.U1RXIF = 0;
   IEC0bits.U1RXIE = 1;

  // IFS0bits.U1TXIF = 0;
 //  IEC0bits.U1TXIE = 1;

   IFS4bits.U1ERIF = 0;        // Clear error flag before enable
   IEC4bits.U1ERIE = 1;        // Enable error interrupt
   U1SCINTbits.GTCIF = 0;
   U1SCINTbits.GTCIE = 1;             //Guard Time Counter Interrupt enabled
   U1SCINTbits.WTCIF = 0;
   U1SCINTbits.WTCIE = 1;             //Waiting Time Counter Interrupt Enabled
   U1STALbits.PERR = 0;               // Clear Parity error flag (Optional)
   U1MODEbits.UARTEN = 1;
   //U1SCINTbits.PARIE = 1;            // Enable RX parity error interrupt (Optional)
   U1SCCONbits.SCEN = 1;
}
/*******************************************************************************
  Function:
    bool DRV_SMARTCARD_UART1_DataGet( uint8_t* pData, uint32_t timeOutInMicroSeconds)

  Description:
    This function receives one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    pData - pointer to Data byte to be recieved
    timeOutETUs - maximum etu time within which the data byte is
                  is expected to be recieved

  Return Values:
    None

  Example:
    <code>
        {
            //during ATR receive the TS byte;
            uint8_t ts;
            uint32_t atrDelay = 10080;
	    SMARTCARD_7816_3_DataGet( &ts , atrDelay );
            // Do something else...
        }
    </code>
  Remarks:
    None.
  *****************************************************************************/
bool DRV_SMARTCARD_DataGet( uint8_t* pData , uint32_t waitingTimeInETU)
{
  *pData = 0;
  dataReceived = 0;
  bool retVal = 0;
  //U1STALbits.UTXEN = 0;
  //Set gauard time
  U1GTC = gATRParams.characterGuardTime;
  //Program the value CWT when T=1 /WWT when T=0 to U1WTC
  U1WTCL = (waitingTimeInETU & 0x0000FFFF); //Character waiting time for T=1 and work waiting time for T=0
  U1WTCH = (waitingTimeInETU >> 16);
  U1SCINTbits.GTCIE = 1;
  U1SCINTbits.WTCIE = 1;
  
  U1STALbits.URXEN = 1;
  #ifdef EMV_SUPPORT
  if(!gATRParams.cardState)
  {
      while(!(dataReceived) && !(wtcFlag) && !(emvDelayLapsedFlag) && !(delayLapsedFlag));
  }
  else
  {
      while(!(dataReceived) && !(wtcFlag) && !(emvDelayLapsedFlag));
  }
  #else
    //wait for data byte
    while(!U1STALbits.URXDA && !(U1SCINTbits.WTCIF );
  #endif
 // if(U1STALbits.URXDA)
  {
    if(U1STALbits.PERR )
    {
     *pData = receivedData;
      dataReceived = 0;
     if(!gATRParams.cardState)
     {
         U1STALbits.PERR = 0;
         retVal = true;
     }
      if(U1SCCONbits.PTRCL == 0x01)
      {
          //Need to set parity error varaible here
          retVal = false;
      }
    }
    else
    {
       *pData = receivedData;
        retVal = true;
    }
  }

  if(U1SCCONbits.PTRCL == 0x00)
  {
    if(((rxrptFlag) == 0x01) || (emvDelayLapsedFlag == 0x01) || (wtcFlag==0x01))
      retVal = false;
  }


  //Need to handle GTCIF and WTCIF here
  gtcFlag = 0;
  wtcFlag =  0;
  rxrptFlag =0;

  return retVal;
}


/*******************************************************************************
  Function:
    bool DRV_SMARTCARD_DataSend(BYTE data, uint8_t isLastByte)

  Description:
    This function transmits one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    data - Data byte to be transmitted
    isLastByte - this tells whether the data byte is the last byte of the data structure
 
  Return Values:
    uint8_t : returns success or failure

   Example:
    <code>
        {
  	  //Send the Command Bytes: CLA INS P1 P2
          uint8_t isLastByte = 0;
          apduCommandBuffer[0] = CLA;
          apduCommandBuffer[1] = INS;
          apduCommandBuffer[2] = P1;
          apduCommandBuffer[3] = P2;
	  for( index = 0; index < 4; index++ )
	  {
		DRV_SMARTCARD_7816_3_DataSend( apduCommandBuffer[index] ,isLastByte );
	  }
          // Do something else...
        }
	</code>

  Remarks:
    None.
  *****************************************************************************/
bool DRV_SMARTCARD_DataSend( uint8_t data ,uint8_t isLastByte )
{
  uint8_t temp;
  bool retVal = true;
  U1STALbits.URXEN = 0;
  U1TXREGbits.LAST = 0;

  U1GTC = gATRParams.characterGuardTime - 1;
  U1WTCL = (gATRParams.workWaitingTime & 0x0000FFFF);
  U1WTCH = (gATRParams.workWaitingTime >> 16);
  //U1SCINTbits.GTCIE = 0;
 #if 0
  //Set gauard time
  U1GTC = gATRParams.characterGuardTime;
  U1SCINTbits.GTCIF = 0;
  U1SCINTbits.GTCIE = 1;
  //Program the value BWT to U1WTC
  if(U1SCCONbits.PTRCL == 0x01)
  {
     U1WTCL = (blockWaitingTime & 0x0000FFFF);
     U1WTCH = (blockWaitingTime >> 16);
     U1SCINTbits.WTCIF = 0;
     U1SCINTbits.WTCIE = 1;
  }
  //Program work waiting time
  if(U1SCCONbits.PTRCL == 0x00)
  {
     U1WTCL = (gATRParams.workWaitingTime & 0x0000FFFF);
     U1WTCH = (gATRParams.workWaitingTime >> 16);
     U1SCINTbits.WTCIE = 1;
  }

#endif

  U1STALbits.UTXEN = 1; //UART Transmit enable
  //Write the data to the transmit register
  U1TXREG = data;
  //Set the U1TXREGbits.LAST to 1 if the data byte is the last byte to be sent
  if(isLastByte == 0x01)
  {
    U1TXREGbits.LAST = 1;
  }

   // check for transmit empty flag
  while( !U1STALbits.TRMT )
    Nop();


  //Disable UART transmit
  U1STALbits.UTXEN = 0;
  U1STALbits.OERR = 0;	        //clear any overflow error that we cause
  U1STALbits.URXEN = 1;

	while(1)	// remove rx data recvd from our Tx line
	{
		if( U1STALbits.URXDA )
			temp = U1RXREG;
		else
			break;
	}


  if(U1SCCONbits.PTRCL == 0x00)
  {
    if(txrptFlag == 0x01)
      retVal = false;
    else
      retVal = true;
  }

  gtcFlag = 0;
  txrptFlag = 0;
  //wtcFlag = 0;
  return retVal;
}

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
void DRV_SMARTCARD_UART1_T0Config()
{
     U1MODEbits.RXINV = 0;
     U1STALbits.UTXINV = 0;
     U1STALbits.URXISEL = 0x00;
     U1SCCONbits.PTRCL = 0;             //T0 operation selected
     U1SCCONbits.T0PD = 1; //2 ETU Pull-Down duration for T = 0 error handling bit
    // U1SCCONbits.CONV = gATRParams.logicConvention;  //Logic convention direct or indirect
     U1SCCONbits.TXRPT  = (uint8_t)RETRY_COUNT;  //Number of retries in case of error

     U1GTC = gATRParams.characterGuardTime - 1;
     U1SCINTbits.GTCIF = 0;
     U1SCINTbits.GTCIE = 1;             //Guard Time Counter Interrupt enabled


     U1WTCL = (gATRParams.workWaitingTime & 0x0000FFFF);
     U1WTCH = (gATRParams.workWaitingTime >> 16);
     U1SCINTbits.WTCIF = 0;
     U1SCINTbits.WTCIE = 1;             //Waiting Time Counter Interrupt Enabled

     
     U1STALbits.PERR = 0;               // Clear Parity error flag (Optional)
     //U1SCINTbits.PARIE = 1;            // Enable RX parity error interrupt (Optional)

     U1SCINTbits.TXRPTIE =1;            //Transmit Repeat Interrupt Enabled
     U1SCINTbits.RXRPTIE = 1;           //Receive Repeat Interrupt Enabled

     IFS4bits.U1ERIF = 0;        // Clear error flag before enable
     IEC4bits.U1ERIE = 1;        // Enable error interrupt

     U1STALbits.UTXISEL1 = 1;
     U1STALbits.UTXISEL0 = 0;

    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;

  //  IFS0bits.U1TXIF = 0;
   // IEC0bits.U1TXIE = 1;
    
     //U1STALbits.URXEN = 0;
     //U1SCCONbits.SCEN = 1;               //Enable Smart card mode
     U1MODEbits.UARTEN = 1;              //Enable UART

}
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
		DRV_SMARTCARD_7816_3_T1_OperationConfig();
	  }
          // Do something else...
        }
	</code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_SMARTCARD_UART1_T1Config()
{
     U1SCCONbits.SCEN = 1;               //Enable Smart card mode
     U1MODEbits.RXINV = 0;
     U1STALbits.UTXINV = 0;
     U1SCCONbits.CONV = gATRParams.logicConvention;  //Logic convention direct or indirect
     U1SCCONbits.PTRCL = 1;             //T1 operation selected

     U1GTC = gATRParams.characterGuardTime;        //Set gauard time
     U1SCINTbits.GTCIE = 1;             //Guard Time Counter Interrupt Enabled

}
/*******************************************************************************
  Function:
    void DRV_SMARTCARD_UART1_ProtocolTypeGet()

  Summary:
    Gets the selected protocol.

  Description:
    This function retrieves the type of the protocol selected.

  Precondition:
    None.

  Parameters:
    None

  Return Values:
    Protocol selected. 0 for T0 , 1 for T1

   Example:
        <code>
        {

           uint8_t protooclType = DRV_SMARTCARD_7816_3_ProtocolTypeGet();
          // Do something else...
        }
	</code>

  Remarks:
    None.
  *****************************************************************************/
uint8_t DRV_SMARTCARD_UART1_ProtocolTypeGet()
{
    return U1SCCONbits.PTRCL;
}
/*******************************************************************************
  Function:
    void WaitMicroSec(void)

  Description:
    This function provides the approximate delay in microseconds.The delay
    sometimes may not be exact delay as per 'microsec' input value, but
    is approximately the same. This approximatation is sufficient for
    smart card stack requirement.

  Precondition:
    None

  Parameters:
    microSec - Number of microseconds delay required

  Return Values:
    None

  Remarks:
    This function supports upto 10000's and more of micro seconds delay.
    For higher time values use 'WaitMilliSec' function.
  *****************************************************************************/

void WaitMicroSec( int32_t microSec )
{
    if(microSec > 1)
    {
	// Clear the delay flag
	delayLapsedFlag = 0;

	// Set the Timer Count as per the delay needed
	SMARTCARD_Drv_SetDelayTimerCnt(microSec * TIMER23_SINGLE_COUNT_MICRO_SECONDS);

	// Enable the delay timer
	SMARTCARD_Drv_EnableDelayTimer();

	// Wait until the delay is elapsed
	while(!delayLapsedFlag);
    }
}

/*******************************************************************************
  Function:
    void WaitMilliSec(void)

  Description:
    This function provides the approximate delay in milliseconds.The delay
    sometimes may not be exact delay as per 'ms' input value, but is
    approximately the same. This approximatation is sufficient for
    smart card stack requirement.

  Precondition:
    None

  Parameters:
    ms - Number of milliseconds delay required

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/

void WaitMilliSec( int32_t ms )
{
	while(ms--)
		WaitMicroSec((int32_t)1000);
}

/*********************************************************************
 * Function:        void LowISR(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Timer 4 overflow interrupt.
 *
 * Note:            None
 ********************************************************************/
#ifdef EMV_SUPPORT
void _ISRFAST __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
	// Clear Timer Interrupt Flag
	IFS1bits.T5IF = 0;
	SMARTCARD_Drv_DisableDelayTimer45();
	emvDelayLapsedFlag = 1;
}
#endif

/*********************************************************************
 * Function:        void LowISR(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Timer 2 overflow interrupt.
 *
 * Note:            None
 ********************************************************************/
void _ISRFAST __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
	// Clear Timer Interrupt Flag
	IFS0bits.T3IF = 0;
	SMARTCARD_Drv_DisableDelayTimer();
	delayLapsedFlag = 1;
}

/*********************************************************************
 * Function:        void LowISR(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Smart card interrupts.
 *
 * Note:            None
 ********************************************************************/

void _ISRFAST __attribute__((interrupt, auto_psv)) _U1ErrInterrupt(void)
{
    // Clear Interrupt Flags
    if(U1SCINTbits.GTCIF)
    {
      gtcFlag = 1;
      U1SCINTbits.GTCIF = 0;
    }
    if(U1SCINTbits.WTCIF)
    {
      wtcFlag = 1;
      U1SCINTbits.WTCIF = 0;
    }
    if(U1SCINTbits.TXRPTIF)
    {
      txrptFlag = 1;
      U1SCINTbits.TXRPTIF =0;
    }
    if(U1SCINTbits.RXRPTIF)
    {
      rxrptFlag = 1;
      U1SCINTbits.RXRPTIF = 0;
    }
    IFS4bits.U1ERIF = 0;

}


/*********************************************************************
 * void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Smart card interrupts.
 *
 * Note:            None
 ********************************************************************/

void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt(void)
{
    dataReceived = 1;
    receivedData = U1RXREG;
    IFS0bits.U1RXIF = 0;
}
