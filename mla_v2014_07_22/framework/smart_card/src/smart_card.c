/********************************************************************
 FileName:		smart_card_lib.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18,PIC24,PIC32 & dsPIC33F Microcontrollers
 Hardware:		This demo is natively intended to be used on Exp 16, LPC
 				& HPC Exp board. This demo can be modified for use on other hardware
 				platforms.
 Complier:  	Microchip C18 (for PIC18), C30 (for PIC24 & dsPIC) & C32 (for PIC32) 
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/
#include <string.h>
#include <stdint.h>
#include <xc.h>
#include "smart_card_layer3.h"
#include "system_config.h"
#include "drv_smart_card_sw.h"


#define MAX_ATR_LEN                     ( uint8_t ) 33
#define ENVELOPE_INS                    ( uint8_t ) 0xC2
#define GET_RESPONSE_INS                ( uint8_t ) 0xC0
#define SMARTCARD_ATR_INTERVAL_10080    ( uint16_t ) 10080
#define CHECK_BIT( var, pos )           ( (var & (1 << pos)) == (1 << pos) )
#ifdef EMV_SUPPORT
extern volatile uint8_t emvDelayLapsedFlag;
extern volatile uint8_t delayLapsedFlag;
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Global Declarations of variables.
// *****************************************************************************
// *****************************************************************************
/* Smart Card General definitions:

  Summary:
    Definition of various general definitions used under smart card

  Description:
    During the protocol transaction  operations,communication bytes would be exchanged.
 These are aggregated in this enumeration data type

  Remarks:
    None
 */
typedef enum
{
    SMARTCARD_LRC_TYPE_EDC              = 0,    // Longitudinal Redundancy Check(LRC) type is used for EDC in Epilogue Field
    SMARTCARD_CRC_TYPE_EDC              = 1,    // Cyclic Redundancy Check(CRC) type is used for EDC in Epilogue Field
    SMARTCARD_RESYNC_REQ                = 0xC0, // PCB byte for Resync Request of T1 Protocol
    SMARTCARD_RESYNC_RESPONSE           = 0xE0, // PCB byte for Resync Response of T1 Protocol
    SMARTCARD_ABORT_REQUEST             = 0xC2, // PCB byte for Abort Request of T1 Protocol
    SMARTCARD_ABORT_RESPONSE            = 0xE2, // PCB byte for Abort Response of T1 Protocol
    SMARTCARD_IFS_REQUEST               = 0xC1, // PCB byte for IFS Request of T1 Protocol
    SMARTCARD_IFS_RESPONSE              = 0xE1, // PCB byte for IFS Response of T1 Protocol
    SMARTCARD_VPP_ERROR_RESPONSE        = 0x04,
    SMARTCARD_WAIT_TIME_EXT_REQUEST     = 0xC3,
    SMARTCARD_WAIT_TIME_EXT_RESPONSE    = 0xE3,
    SMARTCARD_INVERSE_CONVENTION        = 0x03,
    SMARTCARD_DIRECT_CONVENTION         = 0x3B,
    SMARTCARD_CHECK_TA1_PRESENCE        = 0x10,
    SMARTCARD_MIN_DLY_OF_12_ETU_T1      = 0xFF,
    SMARTCARD_MIN_CHAR_TO_CHAR_DURATN_T1= 0x0B,
    SMARTCARD_NULL_NAD_ADDRESS          = 0x00,
    SMARTCARD_STATUS_BYTE_T0_60         = 0x60,
    SMARTCARD_STATUS_BYTE_T0_90         = 0x90,
    SMARTCARD_SECOND_PROC_BYTE_6C       = 0x6C,
    SMARTCARD_SECOND_PROC_BYTE_61       = 0x61,
    SMARTCARD_S_BLOCK_IDENTIFIER        = 0xC0,
    SMARTCARD_I_BLOCK_IDENITFIER        = 0x00,
    SMARTCARD_WI                        = 0x0A, // DEFAULT Value of WI Indicator used in calculation of WWT for T=0 protocol
    SMARTCARD_CWI                       = 0x0C, // DEFAULT Value of CWI Indicator used in calculation of CWT for T=1 protocol
    SMARTCARD_BWI                       = 0x04, // DEFAULT Value of BWI Indicator used in calculation of BWT for T=1 protocol
    SMARTCARD_CLK_CONV_INTEGER_372      = 0x11, // Smart card Frequency selection
    SMARTCARD_TERMINAL_ACCEPT_ATR       = 0x0A
} SMARTCARD_PROTOCOL_RELATED_DEFINITIONS;

uint8_t                             factorDNumerator = 1;
uint8_t                             factorDdenominator = 1;
uint8_t                             scCardATR[MAX_ATR_LEN];
uint8_t                             scATRLength = 0;
uint8_t                             scTA1PresentFlag, scTB1PresentFlag;
uint8_t                             scTA2PresentFlag, scTB2PresentFlag, scTC2PresentFlag, scTD2PresentFlag;
uint8_t                             scTA3PresentFlag, scTB3PresentFlag, scTC3PresentFlag;
uint8_t                             inverseConventionFlag;
uint8_t                             scTS, scT0, scTCK;
uint8_t                             scTA1 = 0x11, scTA2, scTA3 = 0x20;
uint8_t                             scTB1, scTB2, scTB3;
uint8_t                             scTC1, scTC2 = 0x0A, scTC3;
uint8_t                             scTD1, scTD2, scTD3;

uint8_t                             *scATR_HistoryBuffer = NULL;
uint8_t                             scATR_HistoryLength = 0;
uint8_t                             errType = 0;
uint8_t                             invalidBlock = 0;
uint8_t                             scPPSResponseLength;
uint8_t                             scPPSResponse[7];
uint8_t                             deactivationEnabled = 0;
uint8_t                             resyncEnabled = 0;
uint8_t                             abortResponseBeforeDeactivation = 0;
uint8_t                             deactivateLengthIblkFF = 0;
uint8_t                             etraATRCharSupported = 0;

uint16_t                            atrDelayETUs;
uint16_t                            factorF = 372;

SMARTCARD_STATUS                    gCardState = SMARTCARD_UNKNOWN;

// Work Wait time for T=0 Protocol in units of etu's
uint32_t                            t0WWTetu;

static uint8_t                      isIBlockReceived = 0;
static uint8_t                      isRBlockReceived = 0;
static uint8_t                      seqNumOfFirstIBlock = 0;
static uint8_t                      lastRecvdSeqNumOfIBlk = 0;
static uint8_t                      prevRecvdSeqNumOfIBlk = 0;
static uint8_t                      IBlkCount = 0;

static void                         SMARTCARD_FindFDvalues( uint8_t tA1Type );
static void                         SMARTCARD_CalculateWaitTime( void );
static void                         SMARTCARD_ColdReset( void );
static void                         SMARTCARD_WarmReset( void );
static void                         SMARTCARD_InitATR_Variables( void );

#ifdef SMARTCARD_SUPPORT_IN_HARDWARE
DRV_SMARTCARD_ATR_CONFIG            atrConfig;
#endif
static SMARTCARD_TRANSACTION_STATUS scTransactionStatus = SMARTCARD_TRANSACTION_SUCCESSFUL;

#ifdef SMARTCARD_PROTO_T1
    #define R_BLOCK_IDENTIFIER  ( uint8_t ) 0x80
    #define S_BLOCK_IDENTIFIER  ( uint8_t ) 0xC0
    #define M_BIT_SET           ( uint8_t ) 0x20
    #define M_BIT_CLR           ( uint8_t ) 0xDF
    #define S_BIT_SET           ( uint8_t ) 0x40
    #define S_BIT_CLR           ( uint8_t ) 0xBF
    #define S_BIT_POSITION      ( uint8_t ) 0x40

uint32_t                            t1BWTetu;
uint16_t                            t1CWTetu;
uint32_t                            currT1BWTetu;

uint8_t                             t1BGTetu = 22;

uint8_t                             edcType = ( uint8_t ) SMARTCARD_LRC_TYPE_EDC;
uint8_t                             maxSegmentLength = 0x20;
uint8_t                             txSbit = 1;
SMARTCARD_T1BLOCK_TYPES             currentT1RxBlockType;

    #if !defined( EMV_SUPPORT )
static uint16_t                     SMARTCARD_UpdateCRC( uint8_t data, uint16_t crc );
static void                         SMARTCARD_UpdateEDC( uint8_t data, uint16_t *edc );
    #endif
static void                         SMARTCARD_SendT1Block( uint8_t nad, uint8_t pcb, uint8_t length, uint8_t *buffer );
static uint8_t                      SMARTCARD_ReceiveT1Block( uint8_t *rxNAD, uint8_t *rxPCB, uint8_t *rxLength,
                                                              uint8_t *buffer );
#endif

// Character Guard Time for T=0 & T=1 Protocol
uint16_t                            cgtETU;
uint16_t                            cgtInMicroSeconds;
uint16_t                            oppTimeInMicroSeconds;

static uint8_t                      prevIFS = 0;
extern uint8_t                      countfunc;

extern uint32_t                     baudRate;
extern uint32_t                     scReferenceClock;

extern uint8_t                      parityErrorFlag;
extern uint8_t                      cwtExceeded;

// CLA set to '00' = no command chaining,
//                   no secure messaging,
//					 basic logical channel.

/*******************************************************************************
  Function:
    void SMARTCARD_Initialize(void)
	
  Description:
    This function initializes the smart card library

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
	
  Remarks:
    None
  *****************************************************************************/
void SMARTCARD_Initialize( void )
{
    //Initialize the low level driver
    DRV_SMARTCARD_Initialize();
    #ifdef SMARTCARD_PROTO_T1

    // Initialize smart card library variables
    txSbit = 1;
    #endif
}

#if 0

// ISO standard based function

/*******************************************************************************
  Function:
	uint8_t SMARTCARD_PowerOnATR(SMARTCARD_RESET_TYPE resetRequest)
  
  Description:
    This function performs the power on sequence of the SmartCard and 
	interprets the Answer-to-Reset data received from the card.

  Precondition:
    SMARTCARD_Initialize() is called, and card is present

  Parameters:
    resetRequest: type of reset requested by the card

  Return Values:
    1 if Answer to Reset (ATR) was successfuly received and processed
	
  Remarks:
    None
  *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS SMARTCARD_PowerOnATR( SMARTCARD_RESET_TYPES resetRequest )
{
    SMARTCARD_InitATR_Variables();

    //check whether card is present before doing power on reset to the card
    if( !SMARTCARD_Drv_CardPresent() )
    {
        scTransactionStatus = SMARTCARD_ERROR_CARD_NOT_PRESENT;
        return ( scTransactionStatus );
    }

    scTransactionStatus = SMARTCARD_TRANSACTION_SUCCESSFUL;

        #ifdef EMV_SUPPORT

    // Wait for maximum of 42,000 smard card clock cycles
    // to get an ATR from card.The number of clock cycles is converted
    // into etu's for easier usage in the code.
    atrDelayETUs = ( uint16_t ) ( (42000UL * baudRate) / scReferenceClock );

        #else

    // Wait for maximum of 40,000 smard card clock cycles
    // to get an ATR from card.The number of clock cycles is converted
    // into etu's for easier usage in the code.
    atrDelayETUs = ( uint16_t ) ( (40000UL * baudRate) / scReferenceClock );
        #endif
    if( resetRequest == SMARTCARD_WARM_RESET )
    {
        SMARTCARD_WarmReset();
    }
    else
    {
        SMARTCARD_ColdReset();
    }

        #ifdef EMV_SUPPORT

    //The terminal shall be able to receive an ATR having a duration of less than or equal to 20160 initial etus.
    SMARTCARD_Drv_EnableDelayTimerIntr45();

    SMARTCARD_Drv_SetDelayTimerCnt45( ((FCY / baudRate) * 20160UL) );

    SMARTCARD_Drv_EnableDelayTimer45();
        #endif
    if( DRV_SMARTCARD_DataGet(&scCardATR[scATRLength], atrDelayETUs) )
    {
        scATRLength++;

            #ifdef EMV_SUPPORT
        atrDelayETUs = SMARTCARD_ATR_INTERVAL_10080;
            #else
        atrDelayETUs = ( uint16_t ) 9600;
            #endif

        // Read Answer to RESET
            #ifdef EMV_SUPPORT
        while( emvDelayLapsedFlag == 0 )
                #else
            while( 1 )
                    #endif
            {
                //wait for data byte from CARD
                if( DRV_SMARTCARD_DataGet(&scCardATR[scATRLength], atrDelayETUs) )
                {
                    scATRLength++;

                    if( scATRLength == MAX_ATR_LEN )
                    {
                        break;
                    }
                }
                else
                {
                    break;      //no data
                }
            }
    }

        #ifdef EMV_SUPPORT
    SMARTCARD_Drv_DisableDelayTimer45();
    emvDelayLapsedFlag = 0;
        #endif

    //decode the ATR values
        #ifdef EMV_SUPPORT
    if( (scATRLength >= 3) && !parityErrorFlag )
            #else
        if( scATRLength >= 3 )  //min TS, T0 and setup byte
                #endif
        {
            uint8_t T0 = scCardATR[1];
            uint8_t atrIdx = 2;

            //Extract Interface bytes TAx TBx TCx and TDx from ATR
            scTA1 = 0x11;
            scTB1 = scTC1 = scTD1 = 0;
            scTA2 = scTB2 = scTD2 = 0;
            scTA3 = 0x20;
            scTC2 = 0x0A;
            scTB3 = scTC3 = scTD3 = 0;

            // Read the global interface bytes
            if( T0 & 0x10 )
            {
                scTA1 = scCardATR[atrIdx++];
            }

            if( T0 & 0x20 )
            {
                scTB1 = scCardATR[atrIdx++];
            }

            if( T0 & 0x40 )
            {
                scTC1 = scCardATR[atrIdx++];
            }

            if( T0 & 0x80 )
            {
                scTD1 = scCardATR[atrIdx++];
            }

            //read the next set of interface bytes if present
            if( scTD1 & 0xF0 )
            {
                if( scTD1 & 0x10 )
                {
                    scTA2 = scCardATR[atrIdx++];
                    scTA2PresentFlag = 1;
                }

                if( scTD1 & 0x20 )
                {
                    scTB2 = scCardATR[atrIdx++];
                }

                if( scTD1 & 0x40 )
                {
                    scTC2 = scCardATR[atrIdx++];
                }

                if( scTD1 & 0x80 )
                {
                    scTD2 = scCardATR[atrIdx++];
                }

                if( scTD2 & 0xF0 )
                {
                    if( scTD2 & 0x10 )
                    {
                        scTA3 = scCardATR[atrIdx++];

                        if( (scTA3 < 0x10) || (scTA3 == 0xFF) )
                        {
                            SMARTCARD_Shutdown();
                            scTransactionStatus = SMARTCARD_ERROR_ATR_DATA;
                            return ( scTransactionStatus );
                        }

                            #ifdef SC_PROTO_T1
                        maxSegmentLength = scTA3;
                            #endif
                    }

                    if( scTD2 & 0x20 )
                    {
                        scTB3 = scCardATR[atrIdx++];
                    }

                    if( scTD2 & 0x40 )
                    {
                        scTC3 = scCardATR[atrIdx++];

                            #ifdef SC_PROTO_T1
                        edcType = ( scTC3 & 0x01 ) ? ( uint8_t ) SMARTCARD_CRC_TYPE_EDC : ( uint8_t ) SMARTCARD_LRC_TYPE_EDC;
                            #endif
                    }

                    if( scTD2 & 0x80 )
                    {
                        scTD3 = scCardATR[atrIdx++];
                    }
                }
            }

            scATR_HistoryLength = T0 & 0x0F;
            scATR_HistoryBuffer = ( scATR_HistoryLength ) ? ( &scCardATR[atrIdx] ) : NULL;

            // Calculate the protocol wait times for default values
            SMARTCARD_CalculateWaitTime();
            gCardState = SMARTCARD_ATR_ON;
            atrConfig.cardState = SMARTCARD_ATR_ON;

            return ( scTransactionStatus );
        }
        else
        {
            // Not a Valid ATR Reponse
            scTransactionStatus = SMARTCARD_ERROR_NO_ATR_RESPONSE;
            SMARTCARD_Shutdown();
            return ( scTransactionStatus );
        }
}

#endif

/*******************************************************************************
  Function:
	static void SMARTCARD_InitATR_Variables(void)
  
  Description:
    This function performs the power on sequence of the SmartCard and 
	interprets the Answer-to-Reset data received from the card.

  Precondition:
    SMARTCARD_Initialize() is called, and card is present

  Parameters:
    resetRequest: type of reset requested by the card

  Return Values:
    1 if Answer to Reset (ATR) was successfuly received and processed
	
  Remarks:
    None
  *****************************************************************************/
static void SMARTCARD_InitATR_Variables( void )
{
    gCardState = SMARTCARD_UNKNOWN; // intializing to Zero
    scTA2PresentFlag = 0;
    parityErrorFlag = 0;
    inverseConventionFlag = 0;

    memset( scCardATR, 0x00, sizeof(scCardATR) );

    scATR_HistoryLength = 0;
    scATR_HistoryBuffer = NULL;
    scATRLength = 0;

    scTA1PresentFlag = scTB1PresentFlag = 0;
    scTA2PresentFlag = scTB2PresentFlag = scTC2PresentFlag = scTD2PresentFlag = 0;
    scTA3PresentFlag = scTB3PresentFlag = scTC3PresentFlag = 0;

    scTA1 = ( uint8_t ) SMARTCARD_CLK_CONV_INTEGER_372;
    scTB1 = scTC1 = scTD1 = 0;
    scTA2 = scTB2 = scTD2 = 0;
    scTC2 = ( uint8_t ) SMARTCARD_TERMINAL_ACCEPT_ATR;      // Terminal accepts an ATR TC2=0x0A
    scTA3 = 0x20;
    scTB3 = scTC3 = scTD3 = 0;
}

/*******************************************************************************
  Function:
	SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_ATRProcess(SMARTCARD_RESET_TYPE resetRequest)
  
  Description:
    This function checks and validates the Answer-To-Reset(ATR) command
    bytes  and accordingly calls the functions.

  Precondition:
    SMARTCARD_Initialize() is called, and card is present

  Parameters:
    resetRequest: type of reset requested by the card

  Return Values:
    1 if Answer to Reset (ATR) was successfuly received and processed
	
  Remarks:
    None
  *****************************************************************************/
#ifdef EMV_SUPPORT
SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_ATRProcess( SMARTCARD_RESET_TYPES resetRequest )
{
    uint16_t    brg = 0;
    uint64_t    tempAtrDelay = 0;
    uint8_t     expectedMinATRLength = 0;
    uint8_t     atrIdx = 0;
    uint8_t     calculationDummyByte1 = 0;
    uint8_t     index = 0;
    uint8_t     continueFlag = 0;

        #ifdef SMARTCARD_SUPPORT_IN_HARDWARE

    //Enabling SMART card and related interrupts
    DRV_SMARTCARD_UART1_IntrEnable();
        #endif

    // Default FD Values
    SMARTCARD_FindFDvalues( (uint8_t) SMARTCARD_CLK_CONV_INTEGER_372 );

    // Calculate the new baud rate
    baudRate = ( uint64_t )
        (
            (uint64_t) ((uint64_t) scReferenceClock * factorDNumerator) / (uint32_t)
                (factorF * (uint32_t) factorDdenominator)
        );

    // Configure UART for new baud rate
    brg = ( uint16_t ) ( (uint32_t) ((uint32_t) (FCY / 4) / baudRate) - 1 );
    DRV_SMARTCARD_BRGSet( brg );

    while( 1 )
    {
        if( resetRequest == SMARTCARD_WARM_RESET )
        {
            // Default FD Values
            SMARTCARD_FindFDvalues( (uint8_t) SMARTCARD_CLK_CONV_INTEGER_372 );

            // Calculate the new baud rate
            baudRate = ( uint64_t )
                (
                    (uint64_t) ((uint64_t) scReferenceClock * factorDNumerator) / (uint32_t)
                        (factorF * (uint32_t) factorDdenominator)
                );

            // Configure UART for new baud rate
            brg = ( uint16_t ) ( (uint32_t) ((uint32_t) (FCY / 4) / baudRate) - 1 );
            DRV_SMARTCARD_BRGSet( brg );
        }

        continueFlag = 0;
        expectedMinATRLength = 2;
        atrIdx = 2;
        SMARTCARD_Drv_SetParity( 3 );
            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        U1SCCONbits.CONV = atrConfig.logicConvention;
            #endif
        SMARTCARD_InitATR_Variables();

        scTransactionStatus = SMARTCARD_TRANSACTION_SUCCESSFUL;

        //The terminal shall be able to receive an ATR having a duration of less than or equal to 20160
        //initial etus.
        SMARTCARD_Drv_EnableDelayTimerIntr45();

        // Wait for maximum of 42,000 smard card clock cycles
        // to get an ATR from card.The number of clock cycles is converted
        // into etu's for easier usage in the code.
        tempAtrDelay = ( (FCY / baudRate) * 20240 ) + 1920; //(1488 * 10080); //20160 + 1920(error value)
        atrDelayETUs = ( unsigned short int ) ( (46000UL * baudRate) / scReferenceClock ) + 1;

        //atrDelayETUs = 134;
        if( resetRequest == SMARTCARD_WARM_RESET )
        {
            SMARTCARD_WarmReset();
        }
        else
        {
            SMARTCARD_ColdReset();
        }

        SMARTCARD_Drv_SetDelayTimerCnt45( tempAtrDelay );   //((FCY/baudRate) *  20160UL));
        SMARTCARD_Drv_EnableDelayTimer45();

            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        SMARTCARD_Drv_SetDelayTimerCnt( initATRDelayETU );

        delayLapsedFlag = 0;
        SMARTCARD_Drv_EnableDelayTimer();
            #endif
        if( DRV_SMARTCARD_DataGet(&scCardATR[scATRLength], atrDelayETUs) )
        {
                #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            SMARTCARD_Drv_DisableDelayTimer();
            delayLapsedFlag = 0;
                #endif
            scATRLength++;

            atrDelayETUs = SMARTCARD_ATR_INTERVAL_10080;

            scTS = scCardATR[0];

            // InDirect Convention
            if( scTS == (uint8_t) SMARTCARD_INVERSE_CONVENTION )
            {
                    #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                SMARTCARD_Drv_SetParity( 1 );
                SMARTCARD_Drv_SetDataConvention( 1 );
                    #else
                SMARTCARD_Drv_SetParity( 2 );
                inverseConventionFlag = 1;
                    #endif
            }
            else if( scTS == (uint8_t) SMARTCARD_DIRECT_CONVENTION )
            {
                SMARTCARD_Drv_SetParity( 1 );
                    #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                SMARTCARD_Drv_SetDataConvention( 0 );
                    #endif
            }
            else
            {
                break;
            }

            // Read Answer to RESET
            while( emvDelayLapsedFlag == 0 )
            {
                //wait for data byte from CARD
                if( DRV_SMARTCARD_DataGet(&scCardATR[scATRLength], atrDelayETUs) )
                {
                    scATRLength++;

                    if( scATRLength == MAX_ATR_LEN )
                    {
                        break;
                    }
                }
                else
                {
                    break;  //no data
                }
            }
        }

        SMARTCARD_Drv_DisableDelayTimer45();
        emvDelayLapsedFlag = 0;

        if( (scATRLength < 2) || parityErrorFlag )
        {
            break;
        }

        scT0 = scCardATR[1];
        calculationDummyByte1 = scCardATR[1];
        index = 0;
        while( 1 )
        {
            // Check for the present of TA1 byte
            if( calculationDummyByte1 & (uint8_t) SMARTCARD_CHECK_TA1_PRESENCE )
            {
                expectedMinATRLength++;

                if( index == 0 )
                {
                    scTA1PresentFlag = 1;
                    scTA1 = scCardATR[atrIdx++];
                }
                else if( index == 1 )
                {
                    scTA2PresentFlag = 1;
                    scTA2 = scCardATR[atrIdx++];

                    if( (scTA2 & 0x10) == 0x00 )
                    {
                        if( ((scTA1 > 0x10) && (scTA1 < 0x14)) || (scTA1 == 0xD6) )
                        {
                            SMARTCARD_FindFDvalues( scTA1 );

                            // Calculate the new baud rate
                            baudRate = ( uint64_t )
                                (
                                    (uint64_t) ((uint64_t) scReferenceClock * factorDNumerator) / (uint32_t)
                                        (factorF * (uint32_t) factorDdenominator)
                                );

                            // Configure UART for new baud rate
                            DRV_SMARTCARD_BRGSet( (uint16_t) ((uint32_t) ((uint32_t) (FCY / 4) / baudRate) - 1) );
                            SMARTCARD_CalculateWaitTime();
                                #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            DRV_SMARTCARD_ATR_ConfigSet( atrConfig );
                                #endif
                        }
                        else if( resetRequest == SMARTCARD_WARM_RESET )
                        {
                            // Not a Valid ATR Reponse
                            SMARTCARD_Shutdown();
                            scTransactionStatus = SMARTCARD_ERROR_NO_ATR_RESPONSE;
                            return ( scTransactionStatus );
                        }
                        else
                        {
                            resetRequest = SMARTCARD_WARM_RESET;
                            continueFlag = 1;
                            break;
                        }
                    }
                }
                else if( index == 2 )
                {
                    scTA3PresentFlag = 1;
                    scTA3 = scCardATR[atrIdx++];
                        #ifdef SMARTCARD_PROTO_T1
                    maxSegmentLength = scTA3;
                        #endif
                }
            }

            // Check for the presence of TB1
            if( calculationDummyByte1 & 0x20 )
            {
                expectedMinATRLength++;

                if( index == 0 )
                {
                    scTB1PresentFlag = 1;
                    scTB1 = scCardATR[atrIdx++];
                }
                else if( index == 1 )
                {
                    scTB2PresentFlag = 1;
                    scTB2 = scCardATR[atrIdx++];
                }
                else if( index == 2 )
                {
                    scTB3PresentFlag = 1;
                    scTB3 = scCardATR[atrIdx++];
                }
            }

            // Check for the present of TC1
            if( calculationDummyByte1 & 0x40 )
            {
                expectedMinATRLength++;

                if( index == 0 )
                {
                    scTC1 = scCardATR[atrIdx++];
                }
                else if( index == 1 )
                {
                    scTC2PresentFlag = 1;
                    scTC2 = scCardATR[atrIdx++];
                }
                else if( index == 2 )
                {
                    scTC3PresentFlag = 1;
                    scTC3 = scCardATR[atrIdx++];
                        #ifdef SMARTCARD_PROTO_T1
                    edcType = ( scTC3 & 0x01 ) ? SMARTCARD_CRC_TYPE_EDC : ( uint8_t ) SMARTCARD_LRC_TYPE_EDC;
                        #endif
                }
            }

            // Check for the presence of TD1
            if( calculationDummyByte1 & 0x80 )
            {
                calculationDummyByte1 = scCardATR[expectedMinATRLength];
                expectedMinATRLength++;

                if( index == 0 )
                {
                    scTD1 = scCardATR[atrIdx++];
                        #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
                    SetProtocolSelected( scTD1 );
                        #endif
                }
                else if( index == 1 )
                {
                    scTD2PresentFlag = 1;
                    scTD2 = scCardATR[atrIdx++];
                }
                else if( index == 2 )
                {
                    scTD3 = scCardATR[atrIdx++];
                }
            }
            else
            {
                break;
            }

            index++;
        }

        if( continueFlag )
        {
            continue;
        }

        expectedMinATRLength = expectedMinATRLength + ( scT0 & 0x0F );

        if( scATRLength == expectedMinATRLength )
        {
            if( ((scTD1 & 0x0F) == 0x01) || ((scTD2 & 0x0F) == 0x01) )
            {
                break;
            }
        }
        else if( scATRLength == (expectedMinATRLength + 1) && (etraATRCharSupported == 0) )
        {
            calculationDummyByte1 = scT0;
            for( atrIdx = 2; atrIdx < scATRLength; atrIdx++ )
            {
                calculationDummyByte1 = calculationDummyByte1 ^ scCardATR[atrIdx];
            }

            if( calculationDummyByte1 )
            {
                break;
            }
        }
        else
        {
            if( resetRequest == SMARTCARD_WARM_RESET )
            {
                break;
            }

            if( SMARTCARD_ProtocolTypeGet() == SMARTCARD_T1_TYPE )
            {
                resetRequest = SMARTCARD_WARM_RESET;
            }
            else
            {
                if( etraATRCharSupported )
                {
                    resetRequest = SMARTCARD_WARM_RESET;
                }
            }

            continue;
        }

        if( ((scTD1 & 0x0F) == 0x01) || ((scTD2 & 0x0F) == 0x01) )
        {
            atrIdx = scTB3 & 0x0F;
            calculationDummyByte1 = 1;
            while( atrIdx-- )
            {
                calculationDummyByte1 = calculationDummyByte1 * 2;
            }

            if( scTC1 == 0xFF )
            {
                atrIdx = 0;
            }
            else
            {
                atrIdx = scTC1 + 1;
            }

            if( !scTB3PresentFlag || ((scTB3 & 0xF0) > 0x40) || ((scTB3 & 0x0F) > 0x05) ||
                (calculationDummyByte1 <= atrIdx) )
            {
                if( resetRequest == SMARTCARD_WARM_RESET )
                {
                    break;
                }

                resetRequest = SMARTCARD_WARM_RESET;
                continue;
            }
        }

        if( (((scTB1 != 0x00) || !scTB1PresentFlag) && (resetRequest == SMARTCARD_COLD_RESET)) ||
            (((scTD1 & 0x0F) != 0x00) && ((scTD1 & 0x0F) != 0x01)) ||
            ((((scTA2 & 0x0F) != (scTD1 & 0x0F)) || ((scTA2 & 0x10) != 0x00)) && scTA2PresentFlag) || scTB2PresentFlag ||
            (scTC2PresentFlag && (scTC2 == 0x00)) || (scTD2PresentFlag && (
                (((scTD1 & 0x0F) == 0x01) && ((scTD2 & 0x0F) != 0x01)) ||
            (((scTD1 & 0x0F) == 0x00) && ((scTD2 & 0x0F) != 0x0E) && ((scTD2 & 0x0F) != 0x01)))) ||
            (scTA3PresentFlag && ((scTA3 < 0x10) || (scTA3 == 0xFF))) || (scTC3PresentFlag && (scTC3 != 0x00)) )
        {
            if( resetRequest == SMARTCARD_WARM_RESET )
            {
                resetRequest = SMARTCARD_COLD_RESET;
                break;      /*uncommented for T0*/
            }
            else
            {
                resetRequest = SMARTCARD_WARM_RESET;
                continue;
            }
        }

        scATR_HistoryLength = scT0 & 0x0F;
        scATR_HistoryBuffer = ( scATR_HistoryLength ) ? ( &scCardATR[atrIdx] ) : NULL;

        // Calculate the protocol wait times for default values
        SMARTCARD_CalculateWaitTime();
        gCardState = SMARTCARD_ATR_ON;
            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        atrConfig.cardState = SMARTCARD_ATR_ON;
        DRV_SMARTCARD_ATR_ConfigSet( atrConfig );
            #endif
        return ( scTransactionStatus );
    }

    // Not a Valid ATR Reponse
    SMARTCARD_Shutdown();
    scTransactionStatus = SMARTCARD_ERROR_NO_ATR_RESPONSE;
    return ( scTransactionStatus );
}

#endif

/*******************************************************************************
  Function:
	void SMARTCARD_ColdReset(void)
  
  Description:
    The function does the cold reset of smart card module.

  Precondition:
    None

  Parameters:
 None

  Return Values:
 None
	
  Remarks:
    None
  *****************************************************************************/
static void SMARTCARD_ColdReset( void )
{
    #ifdef SMARTCARD_ENABLE_POWER_THROUGH_PORT_PIN
    SMARTCARD_Drv_SetSwitchCardPower( 1 );  //Turn off power to smart card
    #endif
    WaitMicroSec( 100 );

    SMARTCARD_Drv_EnableUART();
    SMARTCARD_Drv_EnableTxPinPullUp();

    WaitMicroSec( 100 );

    //Start the clock
    SMARTCARD_Drv_EnableClock();

    // Wait for atleast 400 Clock Cycles after applying reference clock to card.
    WaitMilliSec( 10 );

    //Release card reset line. set to high state
    SMARTCARD_Drv_SetSwitchCardReset( 1 );
}

/*******************************************************************************
  Function:
    void SMARTCARD_WarmReset(void)
  
  Description:
    This function does the warm Reset.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
	
  Remarks:
    None
  *****************************************************************************/
static void SMARTCARD_WarmReset( void )
{
    //make sure card is in reset
    SMARTCARD_Drv_SetSwitchCardReset( 0 );

    // Wait for atleast 400 Clock Cycles after applying reference clock to card.
    WaitMilliSec( (int32_t) 10 );

    //Release card reset line. set to high state
    SMARTCARD_Drv_SetSwitchCardReset( 1 );
}

/*******************************************************************************
  Function:
    SMARTCARD_PPS_SUPPORT_STATUS SMARTCARD_Is_PPS_Supported(void)
  
  Description:
    This function tells whether PPS exchange is supported or not.

  Precondition:
    SMARTCARD_PowerOnATR was success

  Parameters:
    None

  Return Values:
    Returns SMARTCARD_PPS_SUPPORT_STATUS
	
  Remarks:
    This function is called when SMARTCARD_PowerOnATR() returns 1.
  *****************************************************************************/
SMARTCARD_PPS_SUPPORT_STATUS SMARTCARD_IsPPSSupported( void )
{
    SMARTCARD_PPS_SUPPORT_STATUS    ppsSupportStatus;

    if( scTA2PresentFlag )
    {
        if( scTA2 & 0x80 )
        {   // Specific Mode Only
            ppsSupportStatus = SMARTCARD_PPS_NOT_ALLOWED;
        }
        else
        {   // Specifc Mode, But is capable to change the mode
            ppsSupportStatus = SMARTCARD_PPS_ALLOWED_AFTER_WARM_RESET;
        }
    }
    else
    {       // Negotiable Mode
        ppsSupportStatus = SMARTCARD_PPS_ALLOWED;
    }

    return ( ppsSupportStatus );
}

/*******************************************************************************
  Function:
	SMARTCARD_TRANSACTION_STATUS SMARTCARD_PPS(uint8_t *ppsPtr)
  
  Description:
    This function does the PPS exchange with the smart card & configures the baud 
    rate of the PIC UART module as per the PPS response from the smart card.

  Precondition:
    SMARTCARD_PowerOnATR was success

  Parameters:
    Input is pointer to PPS string

  Return Values:
    Returns SMARTCARD_TRANSACTION_STATUS
	
  Remarks:
    This function is called when SMARTCARD_PowerOnATR() returns 1.
  *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS SMARTCARD_PPSExchange( uint8_t *ppsPtr )
{
    uint8_t     isLastByte = 0;
    uint8_t     ppsn[3] = { 0, 0, 0 };
    uint8_t     index1;
    uint8_t     index2 = 0x10;
    uint8_t     index3 = 2;
    uint8_t     ppsStrLength = 3;
    uint8_t     pckByte = 0x00;
    uint16_t    ppsCGTinMicroSeconds;

    // For PPS exchange GT = 12 ETUs
    ppsCGTinMicroSeconds = ( 12 * 1000000UL ) / baudRate;

    scTransactionStatus = SMARTCARD_ERROR_PPS;

    // Calculate the length of PPS request and store PPS1, PPS2 and PPS3
    // in local variables for future calculations
    for( index1 = 0; index1 < 3; index1++ )
    {
        if( ppsPtr[1] & index2 )
        {
            ppsStrLength++;
            ppsn[index1] = ppsPtr[index3];
            index3++;
        }

        index2 = index2 << 1;
    }

    // Check for the conditions whether PPS can be done to the card...
    scPPSResponseLength = 0;
    if( !SMARTCARD_Drv_CardPresent() || (gCardState != SMARTCARD_ATR_ON) || (scTD1 & 0x10) )
    {
        SMARTCARD_Shutdown();
        return ( scTransactionStatus );
    }

    // Send PPS request to the card
    index1 = 0;
    while( ppsStrLength-- )
    {
        #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        if( ppsStrLength == 1 )
        {
            isLastByte = 1;
        }

        #else
        WaitMicroSec( ppsCGTinMicroSeconds );
        #endif
        DRV_SMARTCARD_DataSend( ppsPtr[index1++], isLastByte );
    }

    // Recieve PPS response from the smart card
    index1 = 0;
    while( 1 )
    {
        #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        SMARTCARD_Drv_SetDelayTimerCnt45( ((FCY / baudRate) * 9600UL) );
        SMARTCARD_Drv_EnableDelayTimer45();
        #endif

        //wait for data byte from CARD
        if( DRV_SMARTCARD_DataGet(&scPPSResponse[index1], 9600) )
        {
            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            SMARTCARD_Drv_DisableDelayTimer45();
            emvDelayLapsedFlag = 0;
            #endif
            if( ++index1 == 7 )
            {
                SMARTCARD_Shutdown();
                return ( scTransactionStatus );
            }
        }
        else
        {
            break;
        }
    }

    // If PPS response length is greater or equal to 3 bytes and PPSS byte is 0xFF and lower
    // nibble of PPS0 byte of PPS response matches with the PPS request then proceed for
    // further calculation or else exit...
    if( (index1 > 2) && (scPPSResponse[0] == 0xFF) && ((ppsPtr[1] & 0x0F) == (scPPSResponse[1] & 0x0F)) )
    {
        index2 = 2;
        if( scPPSResponse[1] & 0x10 )
        {
            // Check PPS1 Response is identical to PPS1 Request.
            if( scPPSResponse[index2] != ppsn[0] )
            {
                SMARTCARD_Shutdown();
                return ( scTransactionStatus );
            }

            index2++;
        }

        if( scPPSResponse[1] & 0x20 )
        {
            // Check PPS1 Response is identical to PPS1 Request.
            if( scPPSResponse[index2] != ppsn[1] )
            {
                SMARTCARD_Shutdown();
                return ( scTransactionStatus );
            }

            index2++;
        }

        if( scPPSResponse[1] & 0x40 )
        {
            // Check PPS1 Response is identical to PPS1 Request.
            if( scPPSResponse[index2] != ppsn[2] )
            {
                SMARTCARD_Shutdown();
                return ( scTransactionStatus );
            }
        }

        // Calculate PCK for the PPS response and ex-or it with recieved PCK byte
        pckByte = 0x00;
        for( index2 = 0; index2 < index1; index2++ )
        {
            pckByte = pckByte ^ scPPSResponse[index2];
        }

        // If the final vaue is non-zero then exit...
        if( pckByte )
        {
            SMARTCARD_Shutdown();
            return ( scTransactionStatus );
        }

        // If baud rate modification request has been accepted by the smart card,
        // change the UART baud rate and other wait time constants
        if( scPPSResponse[1] & 0x10 )
        {
            SMARTCARD_FindFDvalues( scPPSResponse[2] );

            // Calculate the new baud rate
            baudRate = ( uint64_t )
                (
                    (uint64_t) ((uint64_t) scReferenceClock * factorDNumerator) / (uint32_t)
                        (factorF * (uint32_t) factorDdenominator)
                );

            // Configure UART for new baud rate
            DRV_SMARTCARD_BRGSet( (uint16_t) ((uint32_t) ((uint32_t) (FCY / 4) / baudRate) - 1) );
            SMARTCARD_CalculateWaitTime();
            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            DRV_SMARTCARD_ATR_ConfigSet( atrConfig );
            #endif
        }

        // Store the PPS response length in global variable
        scPPSResponseLength = index1;
        scTransactionStatus = SMARTCARD_TRANSACTION_SUCCESSFUL;
    }

    return ( scTransactionStatus );
}

/*******************************************************************************
 Function:
    bool SMARTCARD_IsPresent(void)

  Description:
    This function returns the true or false depending on  card is present/not present.

  Precondition:
    SMARTCARD_Initialize is called.

  Parameters:
    None

  Return Values:
    True of False

  Remarks:
    None
  *****************************************************************************/
bool SMARTCARD_IsPresent( void )
{
    return ( SMARTCARD_Drv_CardPresent() );
}

/*******************************************************************************
  Function:
    SMARTCARD_STATUS SMARTCARD_StateGet(void)
	
  Description:
    This function returns the current state of SmartCard

  Precondition:
    SMARTCARD_Initialize is called.

  Parameters:
    None

  Return Values:
    SMARTCARD_UNKNOWN:  No Card Detected
    SMARTCARD_ATR_ON:       Card is powered and ATR received
	
  Remarks:
    None
  *****************************************************************************/
SMARTCARD_STATUS SMARTCARD_StateGet( void )
{
    return ( gCardState );
}

/*******************************************************************************
  Function:
    void SMARTCARD_Shutdown(void)
	
  Description:
    This function Performs the Power Down sequence of the SmartCard

  Precondition:
    SMARTCARD_Initialize is called.

  Parameters:
    None

  Return Values:
    None
	
  Remarks:
    None
  *****************************************************************************/
void SMARTCARD_Shutdown( void )
{
    //Bring reset line low
    SMARTCARD_Drv_SetSwitchCardReset( 0 );

    WaitMilliSec( 1 );

    // Turn off external Clock given to the card
    SMARTCARD_Drv_DisableClock();

    // Shut down UART and remove any pullups
    DRV_SMARTCARD_DeInitialize();

    WaitMicroSec( 100 );

    SMARTCARD_Drv_SetSwitchCardPower( 0 );
    SMARTCARD_Drv_SetSwitchCardPower( 0 );

    // Turn Off Card Power
    //#ifdef SMARTCARD_ENABLE_POWER_THROUGH_PORT_PIN
    SMARTCARD_Drv_SetSwitchCardPower( 0 );

    //#endif
    gCardState = SMARTCARD_UNKNOWN;
}

/*******************************************************************************
  Function:
    SMARTCARD_TRANSACTION_TYPES SMARTCARD_ProtocolTypeGet(void)

  Description:
    This function gets the type of the protocol supported by the card.

  Precondition:
    SMARTCARD_PowerOnATR was success

  Parameters:
    None

  Return Values:
    SMARTCARD_T0_TYPE, //T=0, Protocol is supported
    SMARTCARD_T1_TYPE  //T=1, Protocol is supported

  Remarks:
    None
 *****************************************************************************/
SMARTCARD_TRANSACTION_TYPES SMARTCARD_ProtocolTypeGet( void )
{
    SMARTCARD_TRANSACTION_TYPES scProtocolType = SMARTCARD_INVALID_TYPE;
    if( (scTD1 & 0x1) == SMARTCARD_T1_TYPE )
    {
        scProtocolType = SMARTCARD_T1_TYPE;
    }
    else if( (scTD1 & 0x1) == SMARTCARD_T0_TYPE )
    {
        scProtocolType = SMARTCARD_T0_TYPE;
    }

    return ( scProtocolType );
}

/*******************************************************************************
  Function:
    void SMARTCARD_FindFDvalues(uint8_t tA1Type)
	
  Description:
    This function finds the clock rate and baud rate adjustment integers(F,D)

  Precondition:
    SMARTCARD_PowerOnATR is called.

  Parameters:
    Input byte as encoded in TA1 character

  Return Values:
    None
	
  Remarks:
  *****************************************************************************/
static void SMARTCARD_FindFDvalues( uint8_t tA1Type )
{
    uint8_t ta1Code = 0;

    ta1Code = tA1Type & 0x0F;

    factorDNumerator = 1;
    factorDdenominator = 1;

    //TA1 encodes the indicated value of the clock rate conversion integer Fi, the indicated value of the baud rate
    //adjustment integer Di and the maximum value of the frequency supported by the card. The default
    //values are Fi = 372, Di = 1 and f (max.) = 5 MHz.
    // Calculate Factor 'D' from TA1 value as per ISO 7816-3 specifications
    switch( ta1Code )
    {
        // Case 0,1 and 7 F(i)= 372  and f(Max)=4Mhz
        case 0x00:
        case 0x07:
        case 0x01:
            break;

        // Case 2: F(i)= 558  and f(Max)=6Mhz
        case 0x02:
            factorDNumerator = 2;
            break;

        // Case 3: F(i)= 744  and f(Max)=8Mhz
        case 0x03:
            factorDNumerator = 4;
            break;

        // Case 4: F(i)= 558  and f(Max)=6Mhz
        case 0x04:
            factorDNumerator = 8;
            break;

        // Case 5: F(i)= 1488  and f(Max)=16Mhz
        case 0x05:
            factorDNumerator = 16;
            break;

        // Case 6: F(i)= 1860  and f(Max)=20Mhz
        case 0x06:
            factorDNumerator = 32;
            break;

        // Case 8: Reserved Value
        case 0x08:
            factorDNumerator = 12;
            break;

        // Case 9: F(i)= 512  and f(Max)=5Mhz
        case 0x09:
            factorDNumerator = 20;
            break;

        // Case 0x0A: F(i)= 768  and f(Max)=7Mhz/6Mhz
        case 0x0A:
            factorDdenominator = 2;
            break;

        // Case 0x0B: F(i)= 1024  and f(Max)=10Mhz
        case 0x0B:
            factorDdenominator = 4;
            break;

        // Case 0x0C: F(i)= 1536  and f(Max)=15Mhz
        case 0x0C:
            factorDdenominator = 8;
            break;

        // Case 0x0D: F(i)= 2048  and f(Max)=20Mhz
        case 0x0D:
            factorDdenominator = 16;
            break;

        // Case 0x0E/0xoF: Reserved Frequency, could be any value
        case 0x0E:
            factorDdenominator = 32;
            break;

        case 0x0F:
            factorDdenominator = 64;
            break;
    }

    ta1Code = ( tA1Type & 0xF0 ) >> 4;

    factorF = 372;

    // Calculate Factor 'F' from TA1 value as per ISO 7816-3 specifications
    // Baudrate value of Adjustment integer is choosen in the following switch case
    // statements.
    switch( ta1Code )
    {
        case 0x00:
        case 0x07:
        case 0x08:
        case 0x0E:
        case 0x0F:
        case 0x01:
            break;

        case 0x02:
            factorF = 558;
            break;

        case 0x03:
            factorF = 744;
            break;

        case 0x04:
            factorF = 1116;
            break;

        case 0x05:
            factorF = 1488;
            break;

        case 0x06:
            factorF = 1860;
            break;

        case 0x09:
            factorF = 512;
            break;

        case 0x0A:
            factorF = 768;
            break;

        case 0x0B:
            factorF = 1024;
            break;

        case 0x0C:
            factorF = 1536;
            break;

        case 0x0D:
            factorF = 2048;
            break;
    }
}

/*******************************************************************************
  Function:
    void SMARTCARD_CalculateWaitTime(void)
	
  Description:
    This function calculates the wait time values for T=0 and T=1 Protocol

  Precondition:
    SMARTCARD_PowerOnATR is called.

  Parameters:
    None

  Return Values:
    None
	
  Remarks:
  *****************************************************************************/
static void SMARTCARD_CalculateWaitTime( void )
{
    uint8_t     tempVariable1;
    #ifdef SMARTCARD_PROTO_T1
    uint8_t     tb2Code;
    uint8_t     index;
    uint16_t    tempVariable2 = 1;
    uint8_t     tempVarCGT = 12;
    #endif

    // Calculate Character Guard Time ETU
    if( scTC1 != (uint8_t) SMARTCARD_MIN_DLY_OF_12_ETU_T1 )
    {
        cgtETU = 12 + scTC1;
    }

    // Check whether T=0 or T=1 protocol ?
    switch( scTD1 & 0x0F )
    {
        // For T = 1 protocol
        case 1:
            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
            DRV_SMARTCARD_TC1Set( scTC1 );
            #endif

            // Calculate Character Guard Time in ETU's for T=1 Protocol
            if( scTC1 == (uint8_t) SMARTCARD_MIN_DLY_OF_12_ETU_T1 )
            {
                // For T=1, cgtETU=0x0B
                cgtETU = ( uint8_t ) SMARTCARD_MIN_CHAR_TO_CHAR_DURATN_T1;
                tempVarCGT = ( uint8_t ) SMARTCARD_MIN_CHAR_TO_CHAR_DURATN_T1;
            }

            #ifdef SMARTCARD_PROTO_T1
            if( scTB2PresentFlag )
            {
                tb2Code = scTB2 & 0x0F;

                tempVariable1 = ( scTB2 & 0xF0 ) >> 4;
            }
            else
            {
                if( scTB3PresentFlag )
                {
                    if( scTB3PresentFlag )
                    {
                        tb2Code = scTB3 & 0x0F;
                        tempVariable1 = ( scTB3 & 0xF0 ) >> 4;
                    }
                    else
                    {
                        tb2Code = ( uint8_t ) SMARTCARD_CWI;
                        tempVariable1 = ( uint8_t ) SMARTCARD_BWI;
                    }
                }
                else
                {
                    tb2Code = ( uint8_t ) SMARTCARD_CWI;
                    tempVariable1 = ( uint8_t ) SMARTCARD_BWI;
                }
            }

            for( index = 0; index < tb2Code; index++ )
            {
                tempVariable2 = tempVariable2 * 2;
            }

            // Calculate Character Wait Time in ETU's for T=1 Protocol as set in the card
            t1CWTetu = 11 + tempVariable2;
                #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            atrConfig.characterWaitingTime = t1CWTetu;
                #endif
            tempVariable2 = 1;

            for( index = 0; index < tempVariable1; index++ )
            {
                tempVariable2 = tempVariable2 * 2;
            }

            // Calculate Block Wait Time in ETU's for T=1 Protocol as set in the card
            //t1BWTetu = 11 + (uint16_t)((uint32_t)tempVariable2 * (((357120UL * factorDNumerator)/factorF)/factorDdenominator));
            t1BWTetu = 11 + ( (uint32_t) (tempVariable2 * (960UL * factorDNumerator)) + (factorDNumerator * (960UL)) );
                #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            atrConfig.blockWaitingTime = t1BWTetu;
                #endif
            #endif
            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE

            // Convert CGT etu value in terms of microseconds
            cgtInMicroSeconds = ( cgtETU * 1000000UL ) / baudRate;
            oppTimeInMicroSeconds = cgtInMicroSeconds;
            if( scTC1 == 0xFF )
            {
                oppTimeInMicroSeconds = oppTimeInMicroSeconds + ( 1000000UL ) / baudRate;
            }

            cgtInMicroSeconds = cgtInMicroSeconds - ( tempVarCGT * ((1000000UL / baudRate)) );
            if( scTC1 > 1 && scTC1 != 0xFF )
            {
                cgtInMicroSeconds = cgtInMicroSeconds - 6;  /*Comapansate error*/
            }

            if( cgtInMicroSeconds <= 10 )
            {
                cgtInMicroSeconds = 0;
            }

            #endif
            break;

        // For T = 0 Protocol
        case 0:
        default:
            // Calculate Character Guard Time in ETU's for T=0 Protocol
            if( scTC1 == 0xFF )
            {
                cgtETU = ( uint8_t ) 12;
            }

            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            atrConfig.characterGuardTime = cgtETU;
            #endif

            // If scTC2 is transmitted by the card then calculate work wait time
            // or else use default value
            if( scTC2PresentFlag )
            {
                tempVariable1 = scTC2;
            }
            else
            {
                tempVariable1 = ( uint8_t ) SMARTCARD_WI;
            }

            // Calculate Wait Time used for T = 0 protocol
            t0WWTetu = ( uint32_t ) ( (uint32_t) (tempVariable1 * 960UL * factorDNumerator) / factorDdenominator );
            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
            atrConfig.workWaitingTime = t0WWTetu;           // Convert CGT etu value in terms of microseconds
            #else

            // Convert CGT etu value in terms of microseconds
            cgtInMicroSeconds = ( cgtETU * 1000000UL ) / baudRate;
            #endif
            break;
    }
}

#if 0

// Function is not used, In Future of ISO implementation could be used.
// Hence commented and retained the code

/*******************************************************************************
  Function:
	uint8_t SMARTCARD_ISO_TransactT0(SMARTCARD_APDU_COMMAND* apduCommand, SMARTCARD_APDU_RESPONSE* apduResponse, uint8_t* apduDataBuffer)
  
  Description:
    This function Sends/recieves the ISO 7816-4 compaliant APDU commands to the card.

  Precondition:
    SMARTCARD_PPS was success or SMARTCARD_PPS functionality not called

  Parameters:
    SMARTCARD_APDU_COMMAND* apduCommand	- Pointer to APDU Command Structure
	SMARTCARD_APDU_RESPONSE* pResp - Pointer to APDU Response structure
			uint8_t* pResp - Pointer to the Command/Response Data buffer

  Return Values:
    1 if transaction was success, and followed the ISO 7816-4 protocol.
	
  Remarks:
    In the APDU command structure, the LC field defines the number of data bytes to 
	be transmitted to the card. This array can hold max of 256 bytes, which 
	can be redefined by the user.  The LE field in APDU command defines the number
	of bytes expected to be received from the card.  This array can hold max 256 bytes,
	which can be redefined by the user.	
  *****************************************************************************/
uint8_t SMARTCARD_ISO_TransactT0( SMARTCARD_APDU_COMMAND *apduCommand, SMARTCARD_APDU_RESPONSE *apduResponse,
                                  uint8_t *apduDataBuffer )
{
    uint8_t *apduCommandBuffer;
    uint8_t index;
    uint8_t lc = apduCommand->LC;
    uint8_t le = apduCommand->LE;
    uint8_t ins = apduCommand->INS;
    uint8_t rx_char;
    uint8_t lcLength = 0;
    uint8_t leLength = 0;

    // Return False if there is no Card inserted in the Slot
    if( !SMARTCARD_Drv_CardPresent() || gCardState != SMARTCARD_ATR_ON )
    {
        scTransactionStatus = SMARTCARD_ERROR_CARD_NOT_PRESENT;
        return ( 0 );
    }

    // Clear APDU Response data if present before getting the new one's
    memset( apduResponse, 0, sizeof(SMARTCARD_APDU_RESPONSE) );

    apduCommandBuffer = ( uint8_t * ) apduCommand;

    //Send the Command Bytes: CLA INS P1 P2
    for( index = 0; index < 4; index++ )
    {
        DRV_SMARTCARD_DataSend( apduCommandBuffer[index] );
        WaitMicroSec( cgtInMicroSeconds );
    }

    //Now transmit LE or LC field if non zero
    if( lc )
    {
        DRV_SMARTCARD_DataSend( lc );
    }
    else if( le )
    {
        DRV_SMARTCARD_DataSend( le );
    }
    else
    {
        DRV_SMARTCARD_DataSend( 0x00 );
    }

    while( 1 )
    {
        // Get Procedure byte
        if( !DRV_SMARTCARD_DataGet(&rx_char, t0WWTetu) )    //wait for data byte from CARD
        {
            scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
            return ( 0 );                   //no response received
        }

        // Process Procedure Byte
        if( rx_char == 0x60 )
        {
            // Do Nothing
        }
        else if( ((rx_char & 0xF0) == 0x60) || ((rx_char & 0xF0) == 0x90) )
        {
            // SW1, get SW2
            apduResponse->SW1 = rx_char;    //save SW1

            //now receive SW2
            if( DRV_SMARTCARD_DataGet(&rx_char, t0WWTetu) ) //wait for data byte from CARD
            {
                apduResponse->SW2 = rx_char;
            }
            else
            {
                scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
                return ( 0 );           //no response received
            }

            break;
        }
        else if( rx_char == ins )
        {
            // Send all remaining bytes
            if( lcLength < lc )         //transmit app data if any
            {
                WaitMicroSec( cgtInMicroSeconds );

                for( ; lcLength < lc; lcLength++ )
                {
                    DRV_SMARTCARD_DataSend( apduDataBuffer[lcLength] );
                    WaitMicroSec( cgtInMicroSeconds );
                }
            }
            else
            {
                // Recive all remaining bytes
                for( ; leLength < le; leLength++ )
                {
                    if( DRV_SMARTCARD_DataGet(&rx_char, t0WWTetu) )
                    {                   //wait for data byte from CARD
                        apduDataBuffer[leLength] = rx_char;
                    }
                    else
                    {
                        scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
                        return ( 0 );   //no response received
                    }
                }
            }
        }
        else if( rx_char == ~ins )
        {
            // ACK, send one byte if remaining
            if( lcLength < lc )
            {
                WaitMicroSec( cgtInMicroSeconds );

                DRV_SMARTCARD_DataSend( apduDataBuffer[lcLength++] );
            }
            else
            {
                //wait for data byte from CARD or timeout
                if( DRV_SMARTCARD_DataGet(&rx_char, t0WWTetu) )
                {
                    apduDataBuffer[leLength++] = rx_char;
                }
                else
                {
                    scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
                    return ( 0 );       //no response received
                }
            }
        }
        else
        {
            // Do Nothing
        }
    }

    // Store the number of recieved data bytes including the
    // status codes to make the life of Smart Card Reader easier
    apduResponse->rxDataLen = leLength;

    return ( 1 );
}

#endif
#ifdef SMARTCARD_PROTO_T1

/*******************************************************************************
  Function:
    static uint16_t SMARTCARD_UpdateCRC(uint8_t data,uint16_t crc)
	
  Description:
    This function calculates 16 bit CRC for T=1 Protocol

  Precondition:
    Initial value of crc should be 0xFFFF.

  Parameters:
    uint8_t data - Data that has to be used to update CRC.
	uint16_t crc - current crc value

  Return Values:
    uint16_t - updated CRC
	
  Remarks:
    CRC 16 - X^16 + X^12 + X^5 + 1

  *****************************************************************************/
    #if !defined( EMV_SUPPORT )
static uint16_t SMARTCARD_UpdateCRC( uint8_t data, uint16_t crc )
{
    uint8_t     index;
    uint16_t    tempData = ( uint16_t ) data << 8;

    // Update the CRC & return it Back
    for( index = 0; index < 8; index++ )
    {
        if( (crc ^ tempData) & 0x8000 )
        {
            crc <<= 1;
            crc ^= ( uint16_t ) 0x1021; // X^12 + X^5 + 1
        }
        else
        {
            crc <<= 1;
        }

        tempData <<= 1;
    }

    return ( crc );
}

    #endif

/*******************************************************************************
  Function:
    static void SMARTCARD_UpdateEDC(uint8_t data,uint16_t *edc)
	
  Description:
    This function updates Error Data Check value depending on the EDC type
    for T=1 Protocol

  Precondition:
    None.

  Parameters:
    uint8_t data - Data that has to be used to update EDC.
	uint16_t *edc - Pointer to EDC

  Return Values:
    None
	
  Remarks:
    None

*****************************************************************************/
    #if !defined( EMV_SUPPORT )
static void SMARTCARD_UpdateEDC( uint8_t data, uint16_t *edc )
{
    // Store the updated LRC/CRC in the EDC
    if( edcType == (uint8_t) SMARTCARD_CRC_TYPE_EDC )   // type = CRC
    {
        *edc = SMARTCARD_UpdateCRC( data, *edc );
    }
    else    // type = LRC
    {
        *edc = *edc ^ data;
    }
}

    #endif

/*******************************************************************************
  Function:
    static void SMARTCARD_SendT1Block(uint8_t nad,uint8_t pcb,uint8_t length,uint8_t *buffer)
	
  Description:
    This function transmits a T=1 formatted block

  Precondition:
    Complete ATR...

  Parameters:
    uint8_t nad - NAD to be transmitted to the card
    uint8_t pcb - PCB to be transmitted to the card
    uint8_t length - Length of I-Field transmitted to the card
    uint8_t *buffer - Pointer to data that is to be transmitted to the card

  Return Values:
    None
	
  Remarks:
    None

*****************************************************************************/
static void SMARTCARD_SendT1Block( uint8_t nad, uint8_t pcb, uint8_t length, uint8_t *buffer )
{
    uint8_t     index = 0;
    uint16_t    edc = 0;    // Error Detection and Correction Word

    // Choose the initial value of edc depending upon LRC or CRC
        #if defined( EMV_SUPPORT )
    edc = pcb ^ length;

    // Update the edc for the data to be transmitted
    for( index = 0; index < length; index++ )
    {
        edc = edc ^ buffer[index];
    }

    // Transmit Node Address, by default is 00. Generally the EMV standard does not
    // support any node address.
            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
    WaitMicroSec( oppTimeInMicroSeconds + 93 );
            #endif
    DRV_SMARTCARD_DataSend( (uint8_t) SMARTCARD_NULL_NAD_ADDRESS, 0 );

        #else
    if( edcType == (uint8_t) SMARTCARD_CRC_TYPE_EDC )
    {
        edc = 0xFFFF;
    }
    else
    {
        edc = 0x0000;
    }

    // Update the edc for Node Address Data Byte
    SMARTCARD_UpdateEDC( nad, &edc );

    // Update the edc for Protocol Control Byte
    SMARTCARD_UpdateEDC( pcb, &edc );

    // Update the edc for length of tx Bytes
    SMARTCARD_UpdateEDC( length, &edc );

    // Update the edc for the data to be transmitted
    for( index = 0; index < length; index++ )
    {
        SMARTCARD_UpdateEDC( buffer[index], &edc );
    }

    // Transmit Node Address
    DRV_SMARTCARD_DataSend( nad );
        #endif
        #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
    WaitMicroSec( cgtInMicroSeconds );
        #endif

    // Transmit Protocol Control Byte	
    DRV_SMARTCARD_DataSend( pcb, 0 );

    // Transmit length of Data Byte
        #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
    WaitMicroSec( cgtInMicroSeconds );
        #endif
    DRV_SMARTCARD_DataSend( length, 0 );

        #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
    WaitMicroSec( cgtInMicroSeconds );
        #endif

    // Transmit Data Bytes
    for( index = 0; index < length; index++ )
    {
        DRV_SMARTCARD_DataSend( buffer[index], 0 );
            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
        WaitMicroSec( cgtInMicroSeconds );
            #endif
    }

    // Transmit EDC
    DRV_SMARTCARD_DataSend( (uint8_t) edc, 1 );

        #if !defined( EMV_SUPPORT )
    if( edcType == (uint8_t) SMARTCARD_CRC_TYPE_EDC )
    {
        WaitMicroSec( cgtInMicroSeconds );
        DRV_SMARTCARD_DataSend( edc >> 8 );
    }

        #endif
}

/*******************************************************************************
  Function:
    void SMARTCARD_ReceiveT1Block(void)
	
  Description:
    This function receives a T=1 formatted block

  Precondition:
    Transmit a block before expecting the response...

  Parameters:
    uint8_t *rxNAD - Pointer to NAD recieved from the card
    uint8_t *rxPCB - Pointer to PCB recieved from the card
    uint8_t *rxLength - Pointer to Length of I-Field recieved from the card
    uint8_t *buffer - Pointer to data recieved from the card
	uint32_t blockWaitTime - value of Block Wait Time

  Return Values:
    1 if block recieve is successful, and follows the ISO 7816-4 protocol.
	
  Remarks:
    None
*****************************************************************************/
static uint8_t SMARTCARD_ReceiveT1Block( uint8_t *rxNAD, uint8_t *rxPCB, uint8_t *rxLength, uint8_t *buffer )
{
    uint16_t    edc = 0;
    uint16_t    index = 0;
    uint8_t     expectedLength = 0;
    errType = 0;
    currentT1RxBlockType = SMARTCARD_INVALID_BLOCK;
    parityErrorFlag = 0;
    cwtExceeded = 0;
    *rxNAD = 0;
    *rxPCB = 0;
    *rxLength = 0;

    // Get NAD
    if( !DRV_SMARTCARD_DataGet(rxNAD, currT1BWTetu) )
    {
        scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
        currentT1RxBlockType = SMARTCARD_NO_BLOCK;
        errType = 0x02;
        return ( 0 );
    }

    // Get PCB
    if( !DRV_SMARTCARD_DataGet(rxPCB, (t1CWTetu + 4)) )
    {
        scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
        errType = 0x01;
        return ( 0 );
    }

    // Get Length	
    if( !DRV_SMARTCARD_DataGet(rxLength, (t1CWTetu + 4)) )
    {
        scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
        errType = 0x02;;
        return ( 0 );
    }

    // Add one to the expected length for LRC
    if( *rxLength == 0xFF )
    {
        expectedLength = 0xFE;
    }
    else
    {
        expectedLength = *rxLength;
    }

    expectedLength = expectedLength + 1;

    // Add additional byte to the length if using CRC
        #if !defined( EMV_SUPPORT )
    if( edcType == (uint8_t) SMARTCARD_CRC_TYPE_EDC )
    {
        expectedLength++;
    }

        #endif

    // Get all the data bytes plus EDC (1 or 2 bytes at end)
    for( index = 0; index < expectedLength; )
    {
        if( !DRV_SMARTCARD_DataGet(buffer + index, (t1CWTetu + 4)) )
        {
            scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
            if( expectedLength == 0xFF || ((index + 1) == expectedLength) )
            {
                errType = 0x02;
            }
            else
            {
                errType = 0x01;
            }

            return ( 0 );
        }

        ++index;
    }

    // Check for the LRC Error
    if( edcType == (uint8_t) SMARTCARD_LRC_TYPE_EDC )
    {
        edc = 0;
        edc = edc ^ *rxNAD;
        edc = edc ^ *rxPCB;
        edc = edc ^ *rxLength;

        for( index = 0; index < expectedLength; )
        {
            edc = edc ^ buffer[index];
            ++index;
        }

        if( edc != 0 )
        {
            scTransactionStatus = SMARTCARD_ERROR_RECEIVE_LRC;
            errType = 0x01;
            return ( 0 );
        }
    }

    if( parityErrorFlag )
    {
        currentT1RxBlockType = SMARTCARD_INVALID_BLOCK;
        errType = 0x01;
        return ( 0 );
    }

        #if !defined( EMV_SUPPORT )
    else    // // Check for the CRC Error
    {
        edc = 0xFFFF;
        edc = SMARTCARD_UpdateCRC( *rxNAD, edc );
        edc = SMARTCARD_UpdateCRC( *rxPCB, edc );
        edc = SMARTCARD_UpdateCRC( *rxLength, edc );

        for( index = 0; index < (expectedLength - 2); )
        {
            edc = SMARTCARD_UpdateCRC( buffer[index], edc );
            ++index;
        }

        if( ((edc >> 8) != buffer[expectedLength - 2]) || ((edc & 0xFF) != buffer[expectedLength - 1]) )
        {
            scTransactionStatus = SMARTCARD_ERROR_RECEIVE_CRC;
            return ( 0 );
        }
    }

        #endif

    // Determine the type of Block recieved from the card
    if( ((*rxPCB & 0x80) == 0x00) && (*rxNAD == 0) && (*rxLength < 0xFF) )
    {
        // I-Block
        currentT1RxBlockType = SMARTCARD_I_BLOCK;
    }
    else if( ((*rxPCB & 0xC0) == 0xC0) && ((*rxPCB & 0x1C) == 0) && (*rxNAD == 0) &&
             (*rxLength == 1 || *rxLength == 0) // &&  (buffer[0] >= 0x10 &&  buffer[0] < 0xFF))
            )
    {
        // parity error checking
        if( (*rxPCB == 0xC1) && (buffer[0] < 0x10 || buffer[0] >= 0xFF) )
        {
            errType = 0x02;

            //currentT1RxBlockType = INVALID_BLOCK;
        }
        else
        {
            // S-Block
            currentT1RxBlockType = SMARTCARD_S_BLOCK;
            if( (*rxPCB == 0xE1) || (*rxPCB == 0xC1) )
            {
                if( (*rxLength == 0x00) || (*rxLength == 0xFF) )
                {
                    errType = 0x02;
                }
            }
        }
    }
    else if( (*rxPCB & 0xC3) == 0x80 && *rxLength == 0 && *rxNAD == 0 && (*rxPCB & 0x20) == 0 )
    {
        // R-Block
        if( (*rxPCB & 0x10) == 0x00 )
        {
            isRBlockReceived = 1;
        }

        currentT1RxBlockType = SMARTCARD_R_BLOCK;
    }
    else if( ((*rxPCB & 0xC3) == 0x80) && ((*rxLength != 0) || (*rxNAD != 0) || (*rxPCB & 0x20) != 0) )
    {
        errType = 0x02;
    }
    else if( (*rxPCB & 0xC0) == 0xC0 && (*rxLength != 1 || *rxLength != 0 || buffer[0] < 0x10 || buffer[0] == 0xFF) )
    {
        errType = 0x02;
    }
    else if( (*rxPCB & 0x80) == 0x00 && (*rxNAD != 0 || *rxLength >= 0xFF) )
    {
        errType = 0x02;
        invalidBlock = 1;
    }
    else if( (((*rxPCB & 0x93) == 0x81) || ((*rxPCB & 0x93) == 0x82) || ((*rxPCB & 0x93) == 0x81) ||
             ((*rxPCB & 0x93) == 0x91) || ((*rxPCB & 0x93) == 0x92) || ((*rxPCB & 0x93) == 0x91)) && (*rxNAD == 0x00) &&
             (*rxLength == 0x00) )
    {
        currentT1RxBlockType = SMARTCARD_R_BLOCK;
        if( (*rxPCB & 0x10) == 0x00 )
        {
            isRBlockReceived = 1;
        }

        if( *rxNAD == 0x00 && *rxLength == 0 && ((*rxPCB & 0x20) == 0x00) && isRBlockReceived )
        {
            if( (*rxPCB & 0x03) == 0x01 )
            {
                errType = 0x01;
            }
            else if( (*rxPCB & 0x03) == 0x02 )
            {
                errType = 0x02;
            }
            else
            {
                errType = 0x03;
            }

            currentT1RxBlockType = SMARTCARD_R_BLOCK;
        }
        else
        {
            errType = 0x02;
        }
    }
    else if( (*rxPCB & 0x80) == 0x00 && *rxLength == 0xFF )
    {
        errType = 0x03;
    }
    else if( (((*rxPCB & 0x80) == 0x80) && (*rxNAD != 0x00)) || (*rxLength != 0) )
    {
        errType = 0x02;
    }

    // Return 1 if there is no LRC or CRC error & data bytes are recieved sucessfully
    return ( 1 );
}

#endif

/*******************************************************************************
  Function:
	SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_TransactT0(uint8_t* apduCommand, uint32_t apduCommandLength, SMARTCARD_APDU_RESPONSE* apduResponse)
  
  Description:
    This function Sends/recieves the  T = 0 commands to the card.

  Precondition:
    SMARTCARD_PPS was success

  Parameters:
    SMARTCARD_T1_PROLOGUE_FIELD* pfield - Pointer to Prologue Field
	uint8_t* iField - Pointer to the Information Field of Tx/Rx Data
	SMARTCARD_APDU_RESPONSE* apduResponse - Pointer to APDU Response structure

  Return Values:
    1 if transaction was success, and followed the ISO 7816-4 protocol.
	
  Remarks:    	
  *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_DataExchangeT0( uint8_t *apduCommand, uint32_t apduCommandLength,
                                                           SMARTCARD_APDU_RESPONSE *apduResponse )
{
    uint8_t                 isLastByte = 0;
    uint32_t                emvWWTetu = 0;
    SMARTCARD_T0CASE_TYPES  CURRENT_T0_CASE = SMARTCARD_UNKNOWN_CASE;
    uint32_t                dataLength;
    uint32_t                remainingBytesNum;
    uint32_t                case4ResponseLen;
    uint16_t                compareIndex = 0;
    uint16_t                rxCardDataLength = 0;
    uint16_t                txDataLength = 0;
    uint8_t                 tpduCommand[5];
    uint8_t                 index;
    uint8_t                 txIndex = 0;
    uint8_t                 rxIndex = 0;
    uint8_t                 offset;
    uint8_t                 rx_char = 0;
    uint8_t                 ins;
    uint8_t                 complimentedIns;
    uint8_t                 LoopContinue = 1;

    // Return False if there is no card inserted in the Slot or ATR of the card is unsucessful
    if( !SMARTCARD_Drv_CardPresent() || (gCardState != SMARTCARD_ATR_ON) )
    {
        SMARTCARD_Shutdown();
        return ( SMARTCARD_ERROR_CARD_NOT_PRESENT );
    }

    // Calculate Work Waiting Time requirement for EMV Cards
    emvWWTetu = t0WWTetu + ( factorDNumerator * 480UL ) / factorDdenominator;

    // Copy APDU command in temporary TPDU buffer
    tpduCommand[0] = apduCommand[0];
    tpduCommand[1] = apduCommand[1];
    tpduCommand[2] = apduCommand[2];
    tpduCommand[3] = apduCommand[3];
    tpduCommand[4] = apduCommand[4];

    // Determine the case type of command transfer as per ISO 7816-3 specifications, Also
    // modify TPDU buffer accordingly
    if( apduCommandLength == 0x04 )
    {
        tpduCommand[4] = 0x00;
        CURRENT_T0_CASE = SMARTCARD_CASE_1;
    }
    else if( apduCommandLength == 0x05 )
    {
        dataLength = tpduCommand[4];
        CURRENT_T0_CASE = SMARTCARD_CASE_2S;
        if( dataLength == 0x00 )
        {
            dataLength = 256;
        }
    }
    else
    {
        dataLength = tpduCommand[4];
        offset = 5;
        if( apduCommandLength == (5 + apduCommand[4]) )
        {
            CURRENT_T0_CASE = SMARTCARD_CASE_3S;
        }
        else if( apduCommandLength == (6 + apduCommand[4]) )
        {
            CURRENT_T0_CASE = SMARTCARD_CASE_4S;
            case4ResponseLen = apduCommand[apduCommandLength - 1];
            if( case4ResponseLen == 0x00 )
            {
                case4ResponseLen = 256;
            }
        }
    }

    // If the APDU command is none of the case type of ISO 7816 standard then return 0
    if( CURRENT_T0_CASE == SMARTCARD_UNKNOWN_CASE )
    {
        SMARTCARD_Shutdown();
        return ( SMARTCARD_ERROR_CMD_APDU_T0 );
    }

    // Store Case 2, Case 3 or Case 4 bytes expected or bytes to be transmitted in tracking variable
    remainingBytesNum = dataLength;

    //Send the Command Bytes: CLA INS P1 P2 P3
    for( index = 0; index < 5; index++ )
    {
        #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
        if( index == 4 )
        {
            isLastByte = 1;
        }

        #else
        WaitMicroSec( cgtInMicroSeconds );
        #endif
        if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
        {
            SMARTCARD_Shutdown();
            return ( SMARTCARD_ERROR_TRANSMIT );
        }
    }

    // Continue untill you decide something !
    while( LoopContinue )
    {
        isLastByte = 0;

        // Copy Instruction Byte in Local Variable
        ins = tpduCommand[1];
        complimentedIns = ~ins;

        // Get Procedure byte
        if( !DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )               //wait for data byte from CARD
        {
            SMARTCARD_Shutdown();
            return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );                //no response received
        }

        // Process Procedure Byte
        if( rx_char == 0x60 )
        {
            // Do Nothing
        }
        else if( ((rx_char & 0xF0) == (uint8_t) SMARTCARD_STATUS_BYTE_T0_60) ||
                 ((rx_char & 0xF0) == (uint8_t) SMARTCARD_STATUS_BYTE_T0_90) )
        {
            // SW1, get SW2
            apduResponse->SW1 = rx_char;    //save SW1
            txIndex = 0;
            rxIndex = 0;

            //now receive SW2
            if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )
            {   //wait for data byte from CARD
                apduResponse->SW2 = rx_char;
            }
            else
            {
                SMARTCARD_Shutdown();
                return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
            }

            // Execute Based on APDU case command
            switch( CURRENT_T0_CASE )
            {
                case SMARTCARD_CASE_1:
                    // Stop for any of the status codes. You are Done !
                    LoopContinue = 0;
                    break;

                case SMARTCARD_CASE_2S: // Second procedure byte
                    if( apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_6C )
                    {
                        tpduCommand[4] = apduResponse->SW2;

                        //Send the Command Bytes: CLA INS P1 P2 P3
                        for( index = 0; index < 5; index++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );                        //no response received
                            }
                        }
                    }
                    else if( apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_61 )
                    {
                        tpduCommand[0] = 0x00;
                        tpduCommand[1] = GET_RESPONSE_INS;
                        tpduCommand[2] = 0x00;
                        tpduCommand[3] = 0x00;
                        tpduCommand[4] = apduResponse->SW2;

                        //Send the Command Bytes: CLA INS P1 P2 P3
                        for( index = 0; index < 5; index++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );                        //no response received
                            }
                        }
                    }
                    else
                    {
                        LoopContinue = 0;
                    }

                    break;

                case SMARTCARD_CASE_3S:
                    if( ((apduResponse->SW1 == 0x90) && (apduResponse->SW2 == 0x00)) ||
                        ((apduResponse->SW1 == 0x62) && (apduResponse->SW2 == 0x81)) ||
                        ((apduResponse->SW1 == 0x63) && (apduResponse->SW2 != 0x35)) )
                    {
                        LoopContinue = 0;
                    }
                    else if( (apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_61) ||
                             ((apduResponse->SW1 == 0x62) && (ins != 0x82)) || ((apduResponse->SW1 == 0x63) && (ins != 0x82)) ||
                             (((apduResponse->SW1 == 0x9F) && (ins != 0x82)) && (txDataLength == dataLength)) )
                    {
                        txDataLength = dataLength;
                        tpduCommand[0] = 0x00;
                        tpduCommand[1] = GET_RESPONSE_INS;
                        tpduCommand[2] = 0x00;
                        tpduCommand[3] = 0x00;

                        if( apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_61 )
                        {
                            tpduCommand[4] = apduResponse->SW2;
                        }
                        else
                        {
                            tpduCommand[4] = 0x00;
                        }

                        //Send the Command Bytes: CLA INS P1 P2 P3
                        for( index = 0; index < 5; index++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );                        //no response received
                            }
                        }
                    }
                    else if( apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_6C )
                    {
                        tpduCommand[4] = apduResponse->SW2;
                        txDataLength = dataLength;

                        //Send the Command Bytes: CLA INS P1 P2 P3
                        for( index = 0; index < 5; index++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );                        //no response received
                            }
                        }
                    }
                    else
                    {
                        LoopContinue = 0;
                    }

                    break;

                case SMARTCARD_CASE_4S:
                    if( (apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_61) || (apduResponse->SW1 == 0x62) ||
                        (apduResponse->SW1 == 0x63) || (apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_6C) )
                    {
                        if( (apduResponse->SW2) != 0x84 )
                        {
                            if( (apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_61) ||
                                (apduResponse->SW1 == (uint8_t) SMARTCARD_SECOND_PROC_BYTE_6C) )
                            {
                                tpduCommand[4] = apduResponse->SW2;
                            }
                            else if( ((apduResponse->SW1 == 0x62) && (apduResponse->SW2 == 0x81)) ||
                                     ((apduResponse->SW1 == 0x63) && (apduResponse->SW2 != 0x35)) )
                            {
                                LoopContinue = 0;
                                break;
                            }
                            else
                            {
                                tpduCommand[4] = 0x00;
                            }

                            tpduCommand[0] = 0x00;
                            tpduCommand[1] = GET_RESPONSE_INS;
                            tpduCommand[2] = 0x00;
                            tpduCommand[3] = 0x00;

                            dataLength = tpduCommand[4];
                            txDataLength = dataLength;
                        }
                        else
                        {
                            tpduCommand[0] = apduResponse->apduData[0];
                            tpduCommand[1] = apduResponse->apduData[1];
                            tpduCommand[2] = apduResponse->apduData[2];
                            tpduCommand[3] = apduResponse->apduData[3];
                            tpduCommand[4] = apduResponse->apduData[4];
                            rxCardDataLength = 0;
                        }

                        //Send the Command Bytes: CLA INS P1 P2 P3
                        for( index = 0; index < 5; index++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(tpduCommand[index], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );                        //no response received
                            }
                        }
                    }
                    else
                    {
                        LoopContinue = 0;
                    }

                default:
                    break;
            }
        }
        else if( rx_char == ins )
        {
            switch( CURRENT_T0_CASE )
            {
                case SMARTCARD_CASE_2S:
                    // Recive all remaining bytes
                    if( tpduCommand[4] == 0 )
                    {
                        compareIndex = 256;
                    }
                    else
                    {
                        compareIndex = tpduCommand[4];
                    }

                    for( ; rxIndex < compareIndex; rxIndex++ )
                    {
                        if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )
                        {   //wait for data byte from CARD
                            apduResponse->apduData[rxCardDataLength++] = rx_char;
                        }
                        else
                        {
                            SMARTCARD_Shutdown();
                            return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
                        }
                    }

                    rxIndex = 0;
                    break;

                case SMARTCARD_CASE_3S:
                    if( txDataLength < dataLength ) //transmit app data if any
                    {
                        for( ; txIndex < tpduCommand[4]; txIndex++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(apduCommand[offset + txDataLength], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );    //no response received
                            }

                            txDataLength++;
                        }

                        txIndex = 0;
                    }
                    else if( tpduCommand[1] == GET_RESPONSE_INS )
                    {
                        if( tpduCommand[4] == 0 )
                        {
                            compareIndex = 256;
                        }
                        else
                        {
                            compareIndex = tpduCommand[4];
                        }

                        for( ; rxIndex < compareIndex; rxIndex++ )
                        {
                            if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )
                            {   //wait for data byte from CARD
                                apduResponse->apduData[rxCardDataLength++] = rx_char;
                            }
                            else
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
                            }
                        }

                        rxIndex = 0;
                    }

                    break;

                case SMARTCARD_CASE_4S:
                    if( txDataLength < dataLength ) //transmit app data if any
                    {
                        for( ; txIndex < tpduCommand[4]; txIndex++ )
                        {
                            #ifdef SMARTCARD_SUPPORT_IN_HARDWARE
                            if( index == 4 )
                            {
                                isLastByte = 1;
                            }

                            #else
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(apduCommand[offset + txDataLength], isLastByte) )   //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );    //no response received
                            }

                            txDataLength++;
                        }

                        txDataLength = txDataLength + offset;
                        txIndex = 0;
                    }
                    else
                    {
                        if( tpduCommand[4] == 0 )
                        {
                            compareIndex = 256;
                        }
                        else
                        {
                            compareIndex = tpduCommand[4];
                        }

                        for( ; rxIndex < compareIndex; rxIndex++ )
                        {
                            if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )
                            {   //wait for data byte from CARD
                                apduResponse->apduData[rxCardDataLength++] = rx_char;
                            }
                            else
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
                            }
                        }

                        rxIndex = 0;
                    }

                default:
                    break;
            }
        }
        else if( rx_char == complimentedIns )
        {
            switch( CURRENT_T0_CASE )
            {
                case SMARTCARD_CASE_3S:
                    if( txDataLength < dataLength ) //transmit app data if any
                    {
                        if( txIndex < tpduCommand[4] )
                        {
                            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(apduCommand[offset + txDataLength], 1) )    //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );            //no response received
                            }

                            txDataLength++;
                            txIndex++;
                        }
                    }
                    else if( tpduCommand[1] == GET_RESPONSE_INS )
                    {
                        if( tpduCommand[4] == 0 )
                        {
                            compareIndex = 256;
                        }
                        else
                        {
                            compareIndex = tpduCommand[4];
                        }

                        if( rxIndex < compareIndex )
                        {
                            if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )    //wait for data byte from CARD
                            {
                                apduResponse->apduData[rxCardDataLength++] = rx_char;
                                rxIndex++;
                            }
                            else
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
                            }
                        }
                    }

                    break;

                case SMARTCARD_CASE_4S:
                    if( txDataLength < dataLength ) //transmit app data if any
                    {
                        if( txIndex < tpduCommand[4] )
                        {
                            #ifndef SMARTCARD_SUPPORT_IN_HARDWARE
                            WaitMicroSec( cgtInMicroSeconds );
                            #endif
                            if( !DRV_SMARTCARD_DataSend(apduCommand[offset + txDataLength], 1) )    //wait for data byte from CARD
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_TRANSMIT );            //no response received
                            }

                            txDataLength++;
                            txIndex++;
                        }
                    }
                    else
                    {
                    case SMARTCARD_CASE_2S:
                    {
                        if( tpduCommand[4] == 0 )
                        {
                            compareIndex = 256;
                        }
                        else
                        {
                            compareIndex = tpduCommand[4];
                        }

                        if( rxIndex < compareIndex )
                        {
                            if( DRV_SMARTCARD_DataGet(&rx_char, emvWWTetu) )    //wait for data byte from CARD
                            {
                                apduResponse->apduData[rxCardDataLength++] = rx_char;
                                rxIndex++;
                            }
                            else
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );    //no response received
                            }
                        }
                    }
                    }

                default:
                    break;
            }
        }
        else
        {
            SMARTCARD_Shutdown();
            return ( SMARTCARD_ERROR_PROCEDURE_BYTE );  //no response received
        }
    }

    // Store the number of recieved data bytes including the
    // status codes to make the life of Smart Card Reader easier
    apduResponse->rxDataLen = rxCardDataLength;

    return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
}

#if 0
void ResetVariables( void )
{
    isIBlockReceived = 0;
    isRBlockReceived = 0;
    seqNumOfFirstIBlock = 0;
    lastRecvdSeqNumOfIBlk = 0;
    prevRecvdSeqNumOfIBlk = 0;
    IBlkCount = 0;
}

#endif

/*******************************************************************************
  Function:
	SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_TransactT1(SMARTCARD_T1_PROLOGUE_FIELD* pfield,uint8_t* iField,SMARTCARD_APDU_RESPONSE* apduResponse)

  Description:
    This function Sends/recieves  T = 1 commands to the card.

  Precondition:
    SMARTCARD_PPS was success

  Parameters:
    SMARTCARD_T1_PROLOGUE_FIELD* pfield - Pointer to Prologue Field
	uint8_t* iField - Pointer to the Information Field of Tx/Rx Data
	SMARTCARD_APDU_RESPONSE* apduResponse - Pointer to APDU Response structure

  Return Values:
    1 if transaction was success, and followed the ISO 7816-4 protocol.

  Remarks:
  *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS SMARTCARD_EMV_DataExchangeT1( SMARTCARD_T1PROLOGUE_FIELD *pfield, uint8_t *iField,
                                                           SMARTCARD_APDU_RESPONSE *apduResponse )
{
    SMARTCARD_T1BLOCK_TYPES t1TxBlockType;

    uint8_t                 txPCB = 0;
    uint8_t                 rxNAD = 0;
    uint8_t                 rxPCB = 0;
    uint8_t                 rxLEN = 0;
    uint8_t                 txLength = 0;
    uint8_t                 retryR = 0;
    uint8_t                 startCount = 0;
    uint8_t                 retrySync = 0;
    uint8_t                 initialLength = 0;
    uint8_t                 txMbit = 0;
    uint8_t                 rxMbit = 0;
    uint8_t                 rxSbit = 0;
    uint8_t                 *rxField;
    uint8_t                 *txField;
    uint8_t                 t1TransactCompleted = 0;
    uint8_t                 rBlockCount = 0;
    uint16_t                iFieldYetToBeTransmitted = 0;
    uint16_t                rxLength = 0;
    prevIFS = 0;

start:
    iFieldYetToBeTransmitted = pfield->length;
    initialLength = iFieldYetToBeTransmitted;
    txLength = iFieldYetToBeTransmitted;
    txPCB = pfield->PCB;
    txField = iField;
    rxLength = 0;
    retryR = 0, startCount = 0;
    rxField = apduResponse->apduData;
    txMbit = 0;
    rxMbit = 0;
    rxSbit = 0;

    // Determine which type of block is to be transmitted to the card
    if( (txPCB & 0x80) == (uint8_t) SMARTCARD_I_BLOCK_IDENITFIER )
    {
        rBlockCount = 0;

        // I-Block
        t1TxBlockType = SMARTCARD_I_BLOCK;

        if( txSbit )
        {
            txPCB = txPCB & S_BIT_CLR;
            txSbit = 0;
        }
        else
        {
            txPCB = txPCB | S_BIT_SET;
            txSbit = 1;
        }

        // Set/Reset the M bit appropriately
        if( iFieldYetToBeTransmitted > maxSegmentLength )
        {
            txLength = maxSegmentLength;
            txMbit = 1;
            txPCB = txPCB | M_BIT_SET;
        }
        else
        {
            txMbit = 0;
            txPCB = txPCB & M_BIT_CLR;
        }
    }
    else if( (txPCB & (uint8_t) SMARTCARD_S_BLOCK_IDENTIFIER) == (uint8_t) SMARTCARD_S_BLOCK_IDENTIFIER )
    {
        // S-Block
        t1TxBlockType = SMARTCARD_S_BLOCK;
        if( iFieldYetToBeTransmitted > 1 )
        {
            return ( SMARTCARD_ERROR_CMD_APDU_T1 );
        }
    }
    else
    {
        // INVALID BLOCK
        return ( SMARTCARD_ERROR_CMD_APDU_T1 );
    }

    // Initialize the recieved data length packet to zero
    apduResponse->rxDataLen = 0;

    currT1BWTetu = t1BWTetu;

    // Go to appropriate case depending upon the type of block
    switch( t1TxBlockType )
    {
        case SMARTCARD_I_BLOCK:
            rBlockCount = 0;

            // Continue Untill Transaction is Passed or Failed...
            while( 1 )
            {
                invalidBlock = 0;

                //rxMbit = 0;
                // Send block with chaining mode, current sequence number, and maximum length.
                SMARTCARD_SendT1Block( 0x00, txPCB, txLength, txField );

                // Recieve the Block
                if( SMARTCARD_ReceiveT1Block(&rxNAD, &rxPCB, &rxLEN, rxField) )
                {
                    if( currentT1RxBlockType != SMARTCARD_INVALID_BLOCK )
                    {
                        // Determine the type of Block recieved from the card
                        if( currentT1RxBlockType == SMARTCARD_I_BLOCK )
                        {
                            if( isIBlockReceived == 0 )
                            {
                                if( (rxPCB & 0x40) == 0x40 && isIBlockReceived == 0 )
                                {
                                    t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                                    isIBlockReceived = 0;
                                    errType = 0x02;
                                    goto Invalid_Blk;
                                }
                                else
                                {
                                    isIBlockReceived = 1;
                                    seqNumOfFirstIBlock = 1;
                                }
                            }

                            if( (rxPCB & 0x20) == 0x20 )
                            {
                                rxMbit = 1;
                            }
                            else
                            {
                                rxMbit = 0;
                            }

                            if( (rxPCB & 0x40) == 0x40 )
                            {
                                rxSbit = 1;
                            }
                            else
                            {
                                rxSbit = 0;
                            }
                        }
                        else if( currentT1RxBlockType == SMARTCARD_R_BLOCK )
                        {
                            if( txSbit && txMbit && rxSbit )
                            {
                                //do
                            }
                            else
                            {
                                if( ((txPCB & 0x80) == 0x00) && ((rxPCB && 0x80) == 0x80) && (txMbit == 0) )    /*added for 2000_1793(R)*/
                                {
                                    retryR = 0;
                                }

                                /*Changed on 29th Jan evening*/
                                if( ((txPCB & 0x80) == 0x80) && ((rxPCB & 0x80) == 0x80) )
                                {
                                    if( retryR != 0 )
                                    {
                                        retryR--;
                                    }
                                }
                            }

                            if( (rxPCB & 0x10) == 0x10 )
                            {
                                rxSbit = 1;
                            }
                            else
                            {
                                rxSbit = 0;
                            }
                        }
                    }
                }
                else
                {
                    invalidBlock = 1;
                }

                if( cwtExceeded && deactivationEnabled )
                {
                    SMARTCARD_Shutdown();
                    cwtExceeded = 0;
                    return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );
                }

                if( currentT1RxBlockType != SMARTCARD_I_BLOCK && currentT1RxBlockType != SMARTCARD_R_BLOCK &&
                    currentT1RxBlockType != SMARTCARD_S_BLOCK )
                {
                    if( ((rxPCB & 0x10) == 0x10) && ((rxPCB & 0x80) == 0x80) )
                    {
                        rxSbit = 1;
                    }
                    else
                    {
                        rxSbit = 0;
                    }

                    if( ((rxPCB & 0x80) == 0x00) )
                    {
                        if( (rxPCB & 0x40) == 0x40 )
                        {
                            rxSbit = 1;
                        }
                        else
                        {
                            rxSbit = 0;
                        }
                    }
                }

                if( startCount < 6 )
                {
                    startCount++;
                }

                currT1BWTetu = t1BWTetu;

                switch( currentT1RxBlockType )
                {
                    case SMARTCARD_I_BLOCK:
                        rBlockCount = 0;

                        if( isIBlockReceived == 0 )
                        {
                            if( (rxPCB & 0x40) == 0x40 && isIBlockReceived == 0 )
                            {
                                t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                                isIBlockReceived = 0;
                                errType = 0x02;
                                goto Invalid_Blk;
                            }
                            else
                            {
                                isIBlockReceived = 1;
                                seqNumOfFirstIBlock = 1;
                            }
                        }

                        if( (txMbit == 1) && currentT1RxBlockType != SMARTCARD_R_BLOCK )
                        {
                            t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                            errType = 0x02;
                            rxMbit = 0;
                            invalidBlock = 1;
                            goto Invalid_Blk;
                        }

                        retryR = 0;
                        if( IBlkCount == 0 )
                        {
                            prevRecvdSeqNumOfIBlk = 0x01;
                        }
                        else
                        {
                            prevRecvdSeqNumOfIBlk = lastRecvdSeqNumOfIBlk;
                        }

                        lastRecvdSeqNumOfIBlk = ( rxPCB & 0x40 );
                        if( prevRecvdSeqNumOfIBlk != lastRecvdSeqNumOfIBlk )
                        {
                            IBlkCount++;
                            rxField = rxField + ( uint8_t ) rxLEN;
                            rxLength = rxLength + rxLEN;

                            // If More Bit is set by the card, send the apprpriate R Block
                            if( rxMbit )
                            {
                                // Transmit R(N) - Expected Seq
                                txLength = 0x00;

                                if( rxSbit )
                                {
                                    txPCB = 0x80;
                                }
                                else
                                {
                                    txPCB = 0x90;
                                }

                                // R-Block
                                t1TxBlockType = SMARTCARD_R_BLOCK;
                                continue;
                            }
                            else
                            {
                                if( rxLength >= 2 )
                                {
                                    apduResponse->rxDataLen = rxLength - 2;
                                    apduResponse->SW1 = *( apduResponse->apduData + rxLength - 2 );
                                    apduResponse->SW2 = *( apduResponse->apduData + rxLength - 1 );
                                }

                                return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                            }
                        }
                        else
                        {
                            t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                            errType = 0x02;
                            invalidBlock = 1;
                            goto Invalid_Blk;
                        }

                    case SMARTCARD_S_BLOCK:
                        rBlockCount = 0;
                        if( rxPCB == (uint8_t) SMARTCARD_IFS_REQUEST )      // Request IFS Change
                        {
                            txPCB = ( uint8_t ) SMARTCARD_IFS_RESPONSE;
                            txLength = 1;
                            txField = rxField;
                            prevIFS = maxSegmentLength;
                            maxSegmentLength = *rxField;

                            // R-Block
                            t1TxBlockType = SMARTCARD_S_BLOCK;
                            continue;
                        }
                        else if( rxPCB == SMARTCARD_WAIT_TIME_EXT_REQUEST ) // Request Wait time Extension
                        {
                            currT1BWTetu = t1BWTetu **rxField;
                            txPCB = ( uint8_t ) SMARTCARD_WAIT_TIME_EXT_RESPONSE;

                            if( rxLEN == 1 )
                            {
                                txLength = 1;
                                txField = rxField;

                                // R-Block
                                t1TxBlockType = SMARTCARD_S_BLOCK;
                                continue;
                            }
                            else
                            {
                                t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                                errType = 0x02; // Abort Request
                                goto Invalid_Blk;
                            }
                        }
                        else if( rxPCB == (uint8_t) SMARTCARD_WAIT_TIME_EXT_RESPONSE )  // Response Wait time Extension
                        {
                            if( txPCB == SMARTCARD_WAIT_TIME_EXT_REQUEST )
                            {
                                txSbit = 1;
                                goto start;
                            }
                            else
                            {
                                t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                                errType = 0x02; //Abort Request
                                goto Invalid_Blk;
                            }
                        }
                        else if( rxPCB == (uint8_t) SMARTCARD_RESYNC_RESPONSE )     // Resync Response from the card
                        {
                            if( txPCB == (uint8_t) SMARTCARD_RESYNC_REQ )
                            {
                                txSbit = 1;
                                goto start;
                            }
                            else
                            {
                                t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                                errType = 0x02;
                                goto Invalid_Blk;
                            }
                        }
                        else if( rxPCB == (uint8_t) SMARTCARD_ABORT_REQUEST )       // Abort Request
                        {
                            // Deactivate the device
                            if( abortResponseBeforeDeactivation )
                            {
                                txPCB = ( uint8_t ) SMARTCARD_ABORT_RESPONSE;
                                txLength = 0;
                                SMARTCARD_SendT1Block( 0x00, txPCB, txLength, txField );
                            }

                            txSbit = 0;
                            SMARTCARD_Shutdown();
                            return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                        }
                        else if( rxPCB == (uint8_t) SMARTCARD_ABORT_RESPONSE )      // Abort Request
                        {
                            t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                            errType = 0x02;
                            goto Invalid_Blk;
                        }
                        else if( (rxPCB & 0x1F) == SMARTCARD_VPP_ERROR_RESPONSE )   // VPP Error Response
                        {
                            // Deactivate the device
                            txSbit = 0;
                            SMARTCARD_Shutdown();
                            return ( SMARTCARD_ERROR_CARD_VPP );
                        }
                        else if( rxPCB == (uint8_t) SMARTCARD_IFS_RESPONSE )
                        {
                            t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                            errType = 0x02;
                            invalidBlock = 1;
                            goto Invalid_Blk;
                        }

                        break;

                    case SMARTCARD_R_BLOCK:
                        if( (rxPCB & 0x20) == 0 )                       //Bit b6 is not set , if set then block error
                        {
                            // If More Bit is set by the reader
                            if( txMbit )
                            {
                                if( txSbit && txMbit && rxSbit )
                                {
                                    //do nothing
                                }
                                else
                                {
                                    retryR = 0;
                                }

                                if( rxSbit != txSbit )
                                {
                                    // Transmit next segment.
                                    if( prevIFS != 0 )
                                    {
                                        iFieldYetToBeTransmitted = iFieldYetToBeTransmitted - prevIFS;
                                        txField = txField /*changed  from iField to txField*/ + prevIFS;
                                        prevIFS = 0;
                                    }
                                    else
                                    {
                                        iFieldYetToBeTransmitted = iFieldYetToBeTransmitted - maxSegmentLength;
                                        txField = txField /*changed  from iField to txField*/ + maxSegmentLength;
                                    }

                                    // I-Block
                                    t1TxBlockType = SMARTCARD_I_BLOCK;
                                    txPCB = pfield->PCB;

                                    if( txSbit )
                                    {
                                        txPCB = txPCB & S_BIT_CLR;
                                        txSbit = 0;
                                    }
                                    else
                                    {
                                        txPCB = txPCB | S_BIT_SET;
                                        txSbit = 1;
                                    }

                                    // Set/Reset the M bit appropriately
                                    if( iFieldYetToBeTransmitted > maxSegmentLength )
                                    {
                                        txLength = maxSegmentLength;
                                        txMbit = 1;
                                        txPCB = txPCB | M_BIT_SET;
                                    }
                                    else
                                    {
                                        txLength = iFieldYetToBeTransmitted;
                                        txMbit = 0;
                                        txPCB = txPCB & M_BIT_CLR;
                                    }
                                }
                                else
                                {
                                    // Deactivate
                                    // Toggle the Sequence Bit
                                    if( txSbit && txMbit && rxSbit )
                                    {
                                        if( retryR < 2 )
                                        {
                                            txPCB = txPCB;
                                        }
                                        else
                                        {
                                            if( deactivationEnabled && (resyncEnabled == 0) )
                                            {
                                                SMARTCARD_Shutdown();
                                                return ( SMARTCARD_ERROR_T1_RETRY );
                                            }
                                            else
                                            {
                                                txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                                txLength = 0;
                                            }
                                        }

                                        retryR++;
                                    }
                                    else
                                    {
                                        if( txSbit == rxSbit )
                                        {
                                            txPCB = txPCB;
                                        }
                                        else
                                        {
                                            if( txSbit )
                                            {
                                                txPCB = 0x00;
                                            }
                                            else
                                            {
                                                txPCB = 0x40;
                                            }

                                            pfield->PCB = txPCB;
                                            apduResponse->rxDataLen = rxLEN;
                                            return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                                            t1TransactCompleted = 1;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if( rxMbit )
                                {
                                    if( invalidBlock == 1 )
                                    {
                                        txPCB = txPCB;
                                        txLength = 0x00;
                                    }
                                    else
                                    {
                                        txPCB = txPCB;
                                        txLength = 0x00;
                                    }
                                }
                                else
                                {
                                    if( rxSbit && ((rxPCB & 0x90) != (txPCB & 0x90)) )
                                    {
                                        if( (rxPCB & 0x90) == 0x90 && (rBlockCount < 2) )
                                        {
                                            if( lastRecvdSeqNumOfIBlk == 0x40 )
                                            {
                                                if( (txPCB & 0x80) != 0x00 )
                                                {
                                                    txPCB = txPCB;      // | (rxPCB & 0x03);
                                                }
                                                else
                                                {
                                                    if( txSbit )
                                                    {
                                                        txPCB = txPCB;
                                                    }
                                                    else
                                                    {
                                                        txPCB = 0x82;
                                                        txLength = 0x00;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if( IBlkCount >= 1 )
                                                {
                                                    if( txSbit )
                                                    {
                                                        txPCB = txPCB;
                                                    }
                                                    else
                                                    {
                                                        txPCB = 0x92;
                                                        txLength = 0x00;
                                                    }
                                                }
                                                else
                                                {
                                                    if( ((txPCB & 0x80) == 0x00) || ((txPCB & 0xC0) == 0xC0) )
                                                    {
                                                        txPCB = 0x82;
                                                        txLength = 0x00;
                                                    }
                                                    else
                                                    {
                                                        txPCB = txPCB;  /*changed from 0x82 to txPCB for 1772_00*/
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // I-Block
                                            t1TxBlockType = SMARTCARD_I_BLOCK;
                                            txPCB = pfield->PCB;

                                            if( txSbit )
                                            {
                                                txPCB = txPCB | S_BIT_SET;
                                            }
                                            else
                                            {
                                                txPCB = txPCB & S_BIT_CLR;
                                            }

                                            // Set/Reset the M bit appropriately
                                            if( iFieldYetToBeTransmitted > maxSegmentLength )
                                            {
                                                txLength = maxSegmentLength;
                                                txMbit = 1;
                                                txPCB = txPCB | M_BIT_SET;
                                            }
                                            else
                                            {
                                                txLength = iFieldYetToBeTransmitted;
                                                txMbit = 0;
                                                txPCB = txPCB & M_BIT_CLR;
                                            }

                                            if( retryR >= 2 )
                                            {
                                                txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                                txLength = 0;
                                                if( resyncEnabled == 0 )
                                                {
                                                    deactivationEnabled = 1;
                                                }
                                            }

                                            retryR++;
                                        }
                                    }
                                    else if( (rxSbit == 0) && ((rxPCB & 0x90) != (txPCB & 0x90)) )
                                    {
                                        if( txSbit )
                                        {
                                            if( (txPCB & 0x80) == 0x00 )
                                            {
                                                txPCB = 0x92;
                                                txLength = 0x00;
                                            }
                                            else
                                            {
                                                txPCB = txPCB;
                                            }
                                        }
                                        else
                                        {
                                            if( (txPCB & 0x80) == 0x00 )
                                            {
                                                txPCB = txPCB;
                                            }
                                            else
                                            {
                                                txPCB = 0x80 | errType;
                                                txLength = 0x00;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // I-Block
                                        t1TxBlockType = SMARTCARD_I_BLOCK;
                                        txPCB = pfield->PCB;

                                        if( txSbit )
                                        {
                                            txPCB = txPCB | S_BIT_SET;
                                        }
                                        else
                                        {
                                            txPCB = txPCB & S_BIT_CLR;
                                        }

                                        // Set/Reset the M bit appropriately
                                        if( iFieldYetToBeTransmitted > maxSegmentLength )
                                        {
                                            txLength = maxSegmentLength;
                                            txMbit = 1;
                                            txPCB = txPCB | M_BIT_SET;
                                        }
                                        else
                                        {
                                            txLength = iFieldYetToBeTransmitted;
                                            txMbit = 0;
                                            txPCB = txPCB & M_BIT_CLR;
                                        }

                                        if( retryR >= 2 )
                                        {
                                            txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                            txLength = 0;
                                            if( resyncEnabled == 0 )
                                            {
                                                deactivationEnabled = 1;
                                            }
                                        }

                                        //retryR++; /* commented this for 1771_00, 1771_01*/
                                        // }
                                    }
                                }

                                retryR++;           /*Moved this from line number (current line - 6)*/
                                if( retryR >= 3 )   /*Added equal to for test case 2000_1786_00*/
                                {
                                    if( deactivationEnabled && (resyncEnabled == 0) )
                                    {
                                        SMARTCARD_Shutdown();
                                        return ( SMARTCARD_ERROR_T1_RETRY );
                                    }
                                    else
                                    {
                                        txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                        txLength = 0;
                                    }
                                }

                                continue;
                            }
                        }
                        else
                        {
                            t1TxBlockType = SMARTCARD_INVALID_BLOCK;
                            goto Invalid_Blk;
                        }

                        break;
        Invalid_Blk:

                    case SMARTCARD_INVALID_BLOCK:
                    case SMARTCARD_NO_BLOCK:
                        #if 1
                        if( rxLEN >= 0xFF && deactivateLengthIblkFF )
                        {
                            // Deactivate the Device
                            txSbit = 0;
                            SMARTCARD_Shutdown();
                            return ( SMARTCARD_ERROR_T1_RETRY );
                        }
                        else
                        {
                            // If 1st Block transaction itself
                            // is failing transmit R(0)
                            if( rxMbit == 0 )
                            {
                                if( (((txPCB & 0x80) == 0x00)) && txSbit )
                                {
                                    txPCB = 0x90 | errType;
                                    txLength = 0x00;
                                }
                                else if( ((txPCB & 0x80) == 0x00) && (txSbit == 0) )
                                {
                                    txPCB = 0x80 | errType;
                                    txLength = 0x00;
                                }
                                else if( (((rxPCB & 0xC0) == 0x80) || ((rxPCB & 0x80) == 0x00)) )
                                {
                                    if( ((rxPCB & 0x80) == 0x00) || ((rxPCB & 0x80) == 0x80) )
                                    {
                                        if( lastRecvdSeqNumOfIBlk == 0x40 )
                                        {
                                            if( (txPCB & 0x03) != 0 )
                                            {
                                                txPCB = txPCB;
                                            }
                                            else
                                            {
                                                txPCB = 0x80 | errType;
                                            }
                                        }
                                        else
                                        {
                                            if( IBlkCount >= 1 )
                                            {
                                                if( ((txPCB & 0x80)) != 0x00 )
                                                {
                                                    txPCB = txPCB;  // | errType;
                                                }
                                                else
                                                {
                                                    if( txSbit | txMbit | rxSbit )
                                                    {
                                                        txPCB = 0x90 | errType;
                                                    }
                                                    else
                                                    {
                                                        /*this if statement added to fix 2000_1808_6*/
                                                        if( lastRecvdSeqNumOfIBlk == 0x00 && ((rxPCB & 0x80) == 0x00) )
                                                        {
                                                            txPCB = 0x90 | errType;
                                                        }
                                                        else
                                                        {
                                                            txPCB = 0x80 | errType;
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if( txPCB == 0x00 )
                                                {
                                                    txPCB = 0x80 | errType;
                                                }
                                                else
                                                {
                                                    if( (txPCB & 0xC0) != 0xC0 )
                                                    {
                                                        txPCB = txPCB;
                                                    }
                                                    else
                                                    {
                                                        txPCB = 0x80 | errType;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        txPCB = txPCB;
                                    }

                                    errType = 0x00;

                                    if( retryR < 2 )
                                    {
                                        txPCB = txPCB;
                                    }
                                    else if( t1TxBlockType == SMARTCARD_I_BLOCK || t1TxBlockType == SMARTCARD_INVALID_BLOCK )   //(t1TxBlockType == I_BLOCKt1TxBlockType ||)
                                    {
                                        //retryR = 0;
                                        if( deactivationEnabled && (resyncEnabled == 0) )
                                        {
                                            SMARTCARD_Shutdown();
                                            return ( SMARTCARD_ERROR_T1_RETRY );
                                        }
                                        else
                                        {
                                            txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                        }
                                    }
                                    else
                                    {
                                        if( txSbit )
                                        {
                                            txPCB = 0x40;
                                        }
                                        else
                                        {
                                            txPCB = 0x00;
                                        }

                                        txLength = pfield->length;
                                        continue;
                                    }

                                    retrySync = 0;
                                    txLength = 0x00;
                                    retryR++;
                                }
                                else
                                {
                                    if( (rxPCB & 0xC0) == 0xC0 )
                                    {
                                        if( lastRecvdSeqNumOfIBlk == 0x40 )
                                        {
                                            if( (txPCB & 0x80) != 0x00 )
                                            {
                                                txPCB = txPCB;
                                            }
                                            else
                                            {
                                                if( txSbit && (txMbit == 0) && (lastRecvdSeqNumOfIBlk == 0x00) )
                                                {
                                                    txPCB = 0x90 | errType;
                                                }
                                                else
                                                {
                                                    txPCB = 0x80 | errType;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if( IBlkCount >= 1 )
                                            {
                                                /*Added ((txPCB & 0xC0) != 0xC0) to fix 1808_12 to 1808_15*/
                                                if( ((txPCB & 0x80) != 0x00) && ((txPCB & 0xC0) != 0xC0) )
                                                {
                                                    txPCB = txPCB;  // | errType;
                                                }
                                                else
                                                {
                                                    if( txSbit | txMbit )
                                                    {
                                                        txPCB = 0x90 | errType;
                                                    }
                                                    else
                                                    {
                                                        /*this if block added to fix 2000_1808_07to 2000_1808_09*/
                                                        if( lastRecvdSeqNumOfIBlk == 0x00 )
                                                        {
                                                            txPCB = 0x90 | errType;
                                                        }
                                                        else
                                                        {
                                                            txPCB = 0x80 | errType;
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                txPCB = 0x80 | errType;
                                            }
                                        }

                                        errType = 0;
                                    }
                                    else
                                    {
                                        if( txSbit )
                                        {
                                            txPCB = 0x90 | errType;
                                        }
                                        else
                                        {
                                            txPCB = 0x80 | errType;
                                        }

                                        errType = 0x00;
                                    }

                                    if( retryR < 2 )
                                    {
                                        txPCB = txPCB;
                                    }
                                    else if( t1TxBlockType == SMARTCARD_I_BLOCK || t1TxBlockType == SMARTCARD_INVALID_BLOCK )   //(t1TxBlockType == I_BLOCKt1TxBlockType ||)
                                    {
                                        //retryR = 0;
                                        if( deactivationEnabled && (resyncEnabled == 0) )
                                        {
                                            SMARTCARD_Shutdown();
                                            return ( SMARTCARD_ERROR_T1_RETRY );
                                        }
                                        else
                                        {
                                            txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                        }
                                    }
                                    else
                                    {
                                        if( txSbit )
                                        {
                                            txPCB = 0x40;
                                        }
                                        else
                                        {
                                            txPCB = 0x00;
                                        }

                                        txLength = pfield->length;
                                        continue;
                                    }

                                    retrySync = 0;
                                    txLength = 0x00;
                                    retryR++;
                                }
                            }
                            else
                            {
                                //transmitNextSegment = 0;
                                // Try transmitting R(0) twice																															// Try transmitting R(0) twice
                                // before transmitting ReSync
                                // Request to the card
                                if( retryR < 2 )
                                {
                                    if( (rxPCB & 0xC0) == 0xC0 )
                                    {
                                        txPCB = txPCB;
                                        txLength = 0x00;
                                    }
                                    else
                                    {
                                        if( invalidBlock == 1 )
                                        {
                                            txPCB = txPCB;
                                        }
                                        else
                                        {
                                            if( rxMbit )
                                            {
                                                txPCB = 0x90;   /*changed from 82 to 90 for 1784_00*/
                                            }
                                            else
                                            {
                                                txPCB = 0x80;   /*changed from 92 to 80 for 1784_00*/
                                            }
                                        }

                                        txLength = 0x00;
                                        retryR++;
                                        retrySync = 0;
                                    }
                                }
                                else
                                {
                                    txPCB = 0xC0;
                                    txLength = 0x00;
                                    retrySync++;

                                    // Try transmitting R(0) twice																															// Try transmitting R(0) twice
                                    // Try transmitting Resync Request
                                    // thrice before telling error to the
                                    // Smart Card Reader
                                    if( retrySync > 3 )
                                    {
                                        scTransactionStatus = SMARTCARD_ERROR_CARD_NO_RESPONSE;
                                        return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );
                                    }
                                }
                            }

                            if( (retryR == 6) || (startCount == 10) )
                            {
                                // Deactivate the Device
                                txSbit = 0;
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_T1_RETRY );
                            }

                            if( retryR >= 3 )                   /*for 2000_1774_00 changed to 3*/
                            {
                                if( resyncEnabled == 0 )
                                {
                                    deactivationEnabled = 1;
                                }
                            }
                        }

                        continue;

                        break;
                        #endif

                    default:
                        break;
                }   //I Block Switch end
            }       // I Block While end
            break;

        case SMARTCARD_S_BLOCK:
            // Continue Untill Transaction is Passed or Failed...
            while( 1 )
            {
                // Send block with chaining mode, current sequence number, and maximum length.
                SMARTCARD_SendT1Block( 0x00, txPCB, txLength, txField );

                // Recieve the Block
                if( SMARTCARD_ReceiveT1Block(&rxNAD, &rxPCB, &rxLEN, rxField) )
                {
                    if( currentT1RxBlockType == SMARTCARD_S_BLOCK )
                    {
                        retryR = 0;
                        if( rxPCB == (uint8_t) SMARTCARD_IFS_RESPONSE && (*txField != *rxField) )
                        {
                            retryR++;
                            continue;
                        }
                    }
                }

                if( cwtExceeded && deactivationEnabled )
                {
                    SMARTCARD_Shutdown();
                    cwtExceeded = 0;
                    return ( SMARTCARD_ERROR_CARD_NO_RESPONSE );
                }

                switch( currentT1RxBlockType )
                {
                    case SMARTCARD_I_BLOCK:
                    case SMARTCARD_R_BLOCK:
                    case SMARTCARD_INVALID_BLOCK:
                    case SMARTCARD_NO_BLOCK:
                        /*changed this code for test case 2000_1813 and 1814*/
                        if( retryR == 2 )
                        {
                            if( (resyncEnabled == 0) && deactivationEnabled )
                            {
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_T1_RETRY );
                            }
                            else
                            {
                                retryR = 0;
                                txPCB = ( uint8_t ) SMARTCARD_RESYNC_REQ;
                                txLength = 0;
                            }

                            // Deactivate the Card & return 0
                        }
                        else if( retryR > 2 )
                        {
                            // Deactivate the Card & return 0
                            txSbit = 0;
                            return ( SMARTCARD_ERROR_T1_RETRY );
                        }

                        retryR++;

                        continue;

                    case SMARTCARD_S_BLOCK:
                        if( rxPCB & 0x20 )  // Response
                        {
                            if( *txField == *rxField )
                            {
                                apduResponse->rxDataLen = rxLEN;
                                return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                            }
                            else
                            {
                                if( txPCB == 0xC1 && rxPCB == 0xE1 )
                                {
                                    return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                                }
                                else if( txPCB == 0xC0 && rxPCB == 0xE0 )
                                {
                                    return ( SMARTCARD_TRANSACTION_SUCCESSFUL );
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            if( rxPCB == (uint8_t) SMARTCARD_IFS_REQUEST )
                            {
                                /*This needstobe revisited asper the EMV spec. Code changed as required by the test case*/
                                if( *rxField >= 0x10 && *rxField <= 0xFE )
                                {
                                    txPCB = ( uint8_t ) SMARTCARD_IFS_REQUEST;
                                    *txField = 0xFE;
                                }
                                else
                                {
                                    // Deactivate the device
                                    txSbit = 0;
                                    SMARTCARD_Shutdown();
                                    return ( SMARTCARD_ERROR_T1_S_BLOCK_RESPONSE );
                                }
                            }
                            else
                            {
                                // Deactivate the device
                                txSbit = 0;
                                SMARTCARD_Shutdown();
                                return ( SMARTCARD_ERROR_T1_S_BLOCK_RESPONSE );
                            }
                        }
                }   // S Block switch end
            }       // S Block while end	
            break;
        case SMARTCARD_NO_BLOCK:
        case SMARTCARD_R_BLOCK:
        case SMARTCARD_INVALID_BLOCK: break;
    }               // switch end
    return SMARTCARD_ERROR_T1_INVALID_BLOCK;
}                   // function end
