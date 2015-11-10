/********************************************************************
 FileName:		SCpic24.c
 Dependencies:	See INCLUDES section
 Processor:		PIC24 Microcontrollers
 Hardware:		This demo is natively intended to be used on Exp 16 board.
 				This demo can be modified for use on other hardware platforms.
 Complier:  	Microchip C30 (for PIC24)
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

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0      Initial release
  1.01     Cleaned up unnecessary variables
  1.02     Modified to Support PIC24H microcontrollers
  1.02.2   Removed recursive function calls and added delay functions.
           Modified the code in more structured way.
  1.02.6  The variable 'delayLapsedFlag' is declared as 'volatile' type,
          as it is modified in the Interrupt Service Routine.
********************************************************************/
#include <stdint.h>
#include <system_config.h>
#if defined( __PIC24F__ ) || defined( __PIC24H__ )
    #include "string.h"
    #include <stdbool.h>
    #include <system.h>
    #include "drv_smart_card_sw.h"



uint32_t            baudRate;
uint32_t            scReferenceClock;   // Smart Card Reference Clock
uint32_t            rxETUtimeDivisorFactor;
uint16_t            oneETUtimeinMicroSeconds;

uint16_t            point3ETUtimeinMicroSeconds;
uint16_t            point05ETUtimeinMicroSeconds;
uint16_t            point02ETUtimeinMicroSeconds;

volatile uint8_t    delayLapsedFlag = 0;

#ifdef EMV_SUPPORT
volatile uint8_t    emvDelayLapsedFlag = 0;
uint8_t             parityErrorFlag = 0;
uint8_t             TC1 = 0x00;
uint8_t             cwtExceeded = 0;
uint8_t             protocolSelected = 0;
extern uint8_t      inverseConventionFlag;
#endif
uint8_t             lookupInverseConvention[16] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

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
    if( microSec > 1 )
    {
        // Clear the delay flag
        delayLapsedFlag = 0;

        // Set the Timer Count as per the delay needed
        SMARTCARD_Drv_SetDelayTimerCnt( microSec * SMARTCARD_TIMER23_SINGLE_COUNT_MICRO_SECONDS );

        // Enable the delay timer
        SMARTCARD_Drv_EnableDelayTimer();

        // Wait until the delay is elapsed
        while( !delayLapsedFlag );
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
    while( ms-- )
    {
        WaitMicroSec( 1000 );
    }
}

/*******************************************************************************
  Function:
    bool DRV_SMARTCARD_DataSend(uint8_t data)

  Description:
    This function transmits one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    data - Data byte to be transmitted
    isLastByte : Not used , added to be in consistent with the GB204 driver
  Return Values:
    None

  Remarks:
    None.
  *****************************************************************************/
bool DRV_SMARTCARD_DataSend( uint8_t data, uint8_t isLastByte )
{
    uint16_t    temp;
    uint8_t     txRetryCounter;
    uint8_t     lowState;
    uint8_t     index;

    if( inverseConventionFlag )
    {
        data = ( (lookupInverseConvention[(data & 0x0F)] << 4) + lookupInverseConvention[(data & 0xF0) >> 4] ) ^ 0xFF;
    }

    // Try to trasmit the byte for 5 times before giving up...
    for( txRetryCounter = 0; txRetryCounter < 5; txRetryCounter++ )
    {
        U1STAbits.UTXEN = 1;
        U1TXREG = data;

        // check for transmit empty flag
        while( !U1STAbits.TRMT )
        {
            Nop();
        }

        U1STAbits.UTXEN = 0;

        // Disable UART Module
        U1MODEbits.UARTEN = 0;

        if( TC1 == 0xFF )
        {
            WaitMicroSec( point02ETUtimeinMicroSeconds );
        }
        else
        {
             #if defined( __PIC24FJ256GB110__ )
            WaitMicroSec( point3ETUtimeinMicroSeconds );    // 0.5 Bit time delay
                #elif defined( __PIC24FJ128GB204__ ) || ( __PIC24FJ128GA204__ )
            WaitMicroSec( ((oneETUtimeinMicroSeconds * 2) / 10) );  // 0.5 Bit time delay
                #endif
        }

        index = 10;
        lowState = 0;
        while( index-- )
        {
            if( SMARTCARD_Drv_GetRxPinData() == 0 )
            {
                lowState++;
            }

            if( TC1 == 0xFF )
            {
                WaitMicroSec( point02ETUtimeinMicroSeconds );
            }
            else
            {
                    #if defined( __PIC24FJ256GB110__ )
                WaitMicroSec( point05ETUtimeinMicroSeconds );
                    #elif defined( __PIC24FJ128GB204__ ) || ( __PIC24FJ128GA204__ )
                WaitMicroSec( point05ETUtimeinMicroSeconds / 2 );
                    #endif
            }
        }

        if( lowState < 2 )
        {
            break;
        }
        else
        {
            while( SMARTCARD_Drv_GetRxPinData() == 0 );
            U1MODEbits.UARTEN = 1;
            WaitMicroSec( 3 * oneETUtimeinMicroSeconds );
        }
    }

    U1MODEbits.UARTEN = 1;  // Enable UART Module
    U1STAbits.OERR = 0;     //clear any overflow error that we caused
    while( 1 )              // remove rx data recvd from our Tx line
    {
        if( U1STAbits.URXDA )
        {
            temp = U1RXREG;
        }
        else
        {
            break;
        }
    }

    if( txRetryCounter == 5 )
    {
        return ( false );
    }
    else
    {
        return ( true );
    }
}

/*******************************************************************************
  Function:
    uint8_t DRV_SMARTCARD_DataGet( uint8_t* pDat, uint32_t timeOutInMicroSeconds)

  Description:
    This function recieves one byte of data as per ISO-7816 standard

  Precondition:
    None.

  Parameters:
    pDat - pointer to Data byte to be recieved
    timeOutETUs - maximum etu time within which the data byte is
                  is expected to be recieved

  Return Values:
    None

  Remarks:
    None.
  *****************************************************************************/
bool DRV_SMARTCARD_DataGet( uint8_t *pDat, uint32_t timeOutETUs )
{
    uint32_t    timerCountValue = timeOutETUs * rxETUtimeDivisorFactor;
    uint8_t     rxRetryCounter;

    // If any error occured while recieving the byte, give chance to smart card
    // to send the corrected byte within 5 attempts
    for( rxRetryCounter = 0; rxRetryCounter < 5; rxRetryCounter++ )
    {
        delayLapsedFlag = 0;

        // Set the Timer Count as per the delay needed
        SMARTCARD_Drv_SetDelayTimerCnt( timerCountValue );

        // Enable the delay timer
        SMARTCARD_Drv_EnableDelayTimer();

            #ifdef EMV_SUPPORT
        if( !SMARTCARD_StateGet() )
        {
            while( !U1STAbits.URXDA && !delayLapsedFlag && !emvDelayLapsedFlag );
        }
        else
        {   //wait for data byte
            while( !U1STAbits.URXDA && !delayLapsedFlag );
        }

            #else

        //wait for data byte
        while( !U1STAbits.URXDA && !delayLapsedFlag );
            #endif
        if( delayLapsedFlag && (U1STAbits.URXDA == 0) )
        {
            cwtExceeded = 1;
        }

        // Disable Timer if it is still running
        SMARTCARD_Drv_DisableDelayTimer();

        if( U1STAbits.URXDA )
        {
            if( U1STAbits.PERR )    //Parity Error detected
            {
                //Read the data from UART to clear the error flag
                *pDat = U1RXREG;
                if( inverseConventionFlag )
                {
                    *pDat =
                        (
                            (lookupInverseConvention[(*pDat & 0x0F)] << 4) +
                            lookupInverseConvention[(*pDat & 0xF0) >> 4]
                        ) ^
                        0xFF;
                }

                if( protocolSelected == T1_PROTOCOL )
                {
                    parityErrorFlag = 1;
                    return ( true );
                }
                else
                {
                    WaitMicroSec( oneETUtimeinMicroSeconds / 12 );  // 0.25 Bit time delay

                    // Disable UART Module
                    SMARTCARD_Drv_TxPin_Direction( 0 );
                    SMARTCARD_Drv_SetTxPinData( 0 );

                        #if defined( __PIC24F__ )
                    U1MODEbits.RXINV = 1;                       //do not recognize this low state as a valid start bit
                        #elif defined( __PIC24H__ )
                    U1MODEbits.URXINV = 1;                      //do not recognize this low state as a valid start bit
                        #endif
                    SMARTCARD_Drv_DisableTxPinPullUp();

                    WaitMicroSec( oneETUtimeinMicroSeconds );   // 1 Bit time delay
                    WaitMicroSec( oneETUtimeinMicroSeconds / 4 );   // 0.25 Bit time delay
                    SMARTCARD_Drv_TxPin_Direction( 1 );             //release RD10. Card should retransmit now.
                    SMARTCARD_Drv_EnableTxPinPullUp();

                        #if defined( __PIC24F__ )
                    U1MODEbits.RXINV = 0;
                        #elif defined( __PIC24H__ )
                    U1MODEbits.URXINV = 0;
                        #endif
                    if( SMARTCARD_StateGet() == 0x00 )
                    {
                        parityErrorFlag = 1;
                        break;
                    }
                }
            }
            else
            {
                //Read the data from UART
                *pDat = U1RXREG;

                if( inverseConventionFlag )
                {
                    *pDat =
                        (
                            (lookupInverseConvention[(*pDat & 0x0F)] << 4) +
                            lookupInverseConvention[(*pDat & 0xF0) >> 4]
                        ) ^
                        0xFF;
                }

                return ( true );
            }
        }
        else
        {
            break;
        }
    }

    return ( false );
}

/*******************************************************************************
  Function:
    void SCdrv_SetBRG()

  Description:
    This function sets the UART baud rate as per the speed code used in ISO 7816
    standard communication.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_BRGSet( uint16_t brg )
{
    U1BRG = brg;    //(uint16_t)((uint32_t)((uint32_t)(FCY/4)/baudRate) - 1);

    // Calculate the recieve ETU divisor which will be used to calculate the timeouts
    // while recieving the data bytes. This calculation is done here because baudrate
    // of ISO 7816 communication is recalculated here.
    oneETUtimeinMicroSeconds = ( uint16_t ) ( 1000000UL / baudRate );
    point3ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 3 ) / 10;
    point05ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 5 ) / 100;
    point02ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 2 ) / 100;
    rxETUtimeDivisorFactor = FCY / baudRate;
}

/*This function needs to be eliminated , added as temporary fix*/
void DRV_SMARTCARD_TC1Set( uint8_t scTC1 )
{
    TC1 = scTC1;
    point02ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 2 ) / 100;
}

/*This function needs to be eliminated , added as temporary fix*/
void SetProtocolSelected( uint8_t scT0 )
{
    protocolSelected = ( scT0 & 0x01 );
}

/*This function needs to be eliminated , added as temporary fix*/
uint8_t DRV_SMARTCARD_ProtocolTypeGet( void )
{
    return ( protocolSelected );
}

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_DeInitialize(void)

  Description:
    This function closes the UART used for ISO 7816 standard communication

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_DeInitialize( void )
{
    U1MODEbits.UARTEN = 0;  // Turn off UART
    U1STAbits.OERR = 0;;

    // Disable Pull-ups at Tx & Rx pins
    SMARTCARD_Drv_DisableTxPinPullUp();
    SMARTCARD_Drv_DisableRxPinPullUp();
}

/*******************************************************************************
  Function:
    void DRV_SMARTCARD_Initialize(void)

  Description:
    This function initializes the UART used for ISO 7816 standard communication

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  *****************************************************************************/
void DRV_SMARTCARD_Initialize( void )
{
    #if defined( __PIC24FJ256GB110__ )
    uint16_t    power2Value = 1;
    uint8_t     power2temp;
    #endif

    SMARTCARD_Drv_SetSwitchCardReset( 0 );      //keep card in reset state
    SMARTCARD_Drv_ResetPin_Direction( 0 );      //set RD0 as output for Smart Card Reset Pin
        #ifdef SMARTCARD_ENABLE_POWER_THROUGH_PORT_PIN
    SMARTCARD_Drv_SetSwitchCardPower( 0 );      //Turn off power to smart card
    SMARTCARD_Drv_PowerPin_Direction( 0 );      //set RG8 as output to power the Smart Card
        #endif
    SMARTCARD_Drv_CardPresent_Direction( 1 );   //RD3 Input Card Present - SmartCard Conn Active Hi
    SMARTCARD_Drv_SimPresent_Direction( 1 );    //RG12 Input Card Present - SimCard Conn Active Low
    SMARTCARD_Drv_ClockSet();

    MapUART1RxPin();        // Map UART1 Rx pin
    MapUART1TxPin();        // Map UART1 Tx pin
        #if defined( __PIC24FJ256GB110__ )

    // Initial Baud Rate of Smart Card for external Clock
    power2temp = SMARTCARD_REF_CLOCK_POWER2_VALUE;

    while( power2temp-- )
    {
        power2Value = power2Value * ( uint8_t ) 2;
    }

    scReferenceClock = SMARTCARD_REF_CLOCK_CIRCUIT_INPUT_CLK / ( power2Value + SMARTCARD_REF_CLOCK_DIVISOR_VALUE );
        #elif defined( __PIC24FJ128GB204__ ) || ( __PIC24FJ128GA204__ )
    scReferenceClock = SMART_CARD_REF_CLK;
        #endif
    baudRate = scReferenceClock / 372;

    // Calculate the recieve ETU divisor which will be used to calculate the timeouts
    // while recieving the data bytes. This calculation is done here because baudrate
    // of ISO 7816 communication is calculated here.
    oneETUtimeinMicroSeconds = ( uint16_t ) ( 1000000UL / baudRate );
    point3ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 3 ) / 10;
    point05ETUtimeinMicroSeconds = ( oneETUtimeinMicroSeconds * 5 ) / 100;

    rxETUtimeDivisorFactor = FCY / baudRate;

    U1BRG = ( uint16_t ) ( (uint32_t) ((uint32_t) (FCY / 4) / baudRate) - 1 );

    U1MODEbits.STSEL = 0;   //1 stop bit
    U1MODEbits.BRGH = 1;

    // Enable Delay Timer Interrupts for future use
    SMARTCARD_Drv_EnableDelayTimerIntr();
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
 * Overview:        Timer 1 overflow interrupt.
 *
 * Note:            None
 ********************************************************************/
void _ISRFAST __attribute__ ( (interrupt, auto_psv) ) _T3Interrupt( void )
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
 * Overview:        Timer 1 overflow interrupt.
 *
 * Note:            None
 ********************************************************************/
    #ifdef EMV_SUPPORT
void _ISRFAST __attribute__ ( (interrupt, auto_psv) ) _T5Interrupt( void )
{
    // Clear Timer Interrupt Flag
    IFS1bits.T5IF = 0;
    SMARTCARD_Drv_DisableDelayTimer45();
    emvDelayLapsedFlag = 1;
}

    #endif
#endif //__PIC24F__
