/********************************************************************
 FileName:	smart_card_demo_main.c
 Dependencies:	See INCLUDES section
 Processor:	PIC24 Microcontrollers
 Hardware:	This demo is natively intended to be used on Exp 16, 
 Complier:  	XC16 compiler for PIC24F
 Company:	Microchip Technology, Inc.

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

 *********************************************************************************/
#include "string.h"
#include "system_config.h"
#include "smart_card.h"
#include "smart_card_layer3.h"
#include <stdint.h>
#include <stdlib.h>
#include <xc.h>


/*Configuration used for UART for displaying the result*/
#define BAUDRATE    ( 9600 )
#define BRGVAL      ( (FCY / BAUDRATE) / 16 ) - 1


/*Function Prototypes*/
static void ConfigureUART( void );
static void Print_Text(char *header );
static void Uart_Newline_Char( void );

SMARTCARD_TRANSACTION_STATUS EMV_PowerOn( SMARTCARD_RESET_TYPES resetType );
static void PrintAsciiToHex( char a );
static void TransmitData( unsigned char Data );
SMARTCARD_TRANSACTION_STATUS ApplicationSelectionByAID( int aidType );
///////////////
extern void                 WaitMilliSec( unsigned long int ms );
extern uint8_t              scCardATR[33];
extern uint8_t              scATRLength;

// APDU Command to the Card
SMARTCARD_T1PROLOGUE_FIELD  prologueField;
uint8_t                     apduCmd[256];

// APDU Response from the Card
SMARTCARD_APDU_RESPONSE     demo_CardResponse;
uint32_t                    apduCommandLength = 0;

// PPS Request to the card
// PPS Request to the card
uint8_t                     ppsString[4] = { 0xFF, // PPSS byte
    0x11, // PPS0 byte
    0x13, // PPS1 byte
    0xFD // PCK byte
};

//Enable doPPS(change value to 1) if PPS is supported by the card
uint8_t                     doPPS = 0;

// Store the APDU Command/Response Data in a 256 bytes register bank(RAM)
uint8_t                     apduData[SMARTCARD_APDU_BUFF_SIZE];

/*******************************************************************************
  Function:
            int main(void)

  Description:
            This is the main function ford demo program

  Precondition:
            Nil

  Parameters:
            Nil

  Return Values:
            return 0
  Remarks:
    
 *****************************************************************************/
int main( void )
{
    int                             index = 0;
    int                             indexCalc = 0;
    int                             cardNameIndex = 0;
    int                             cardNameLen = 0;
    int                             appPrefNameIndex = 0;
    int                             appPrefNameLen = 0;

    SMARTCARD_TRANSACTION_STATUS    status;
    SMARTCARD_TRANSACTION_TYPES     transactionType;
    BoardConfig();
  
    //ConfigureUART for displaying data on terminal
    ConfigureUART();

    //Start smart card stack
    SMARTCARD_Initialize();

    Print_Text( "***   MICROCHIP'S SMART CARD DEMO    ***\n" );
    Uart_Newline_Char();
    Uart_Newline_Char();

    // Proceed further only after detecting the card
    while( !SMARTCARD_IsPresent() );

    status = EMV_PowerOn( SMARTCARD_COLD_RESET );

    if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
    {
        Print_Text( "***    ATR SUCCESSFUL    ***\n" );
        Uart_Newline_Char();
        for( index = 0; index < scATRLength; index++ )
        {
            PrintAsciiToHex( scCardATR[index] );
            TransmitData( ' ' );
            TransmitData( ' ' );
        }

        Uart_Newline_Char();
        Uart_Newline_Char();

        WaitMilliSec( 20 );

        // IF ATR is succuessful , check for the type of card supported.
        // Appropriately call the function t=0 or t=1,
        transactionType = SMARTCARD_ProtocolTypeGet();

        // If T = 0 protocol supported
        if( transactionType == SMARTCARD_T1_TYPE )
        {
            // If T=1 is defined
            // Write Node Address, Protocol Control Byte & I-Field Length respectively
            //First send a Sblock with IFS request
            prologueField.NAD = 0;
            prologueField.PCB = 0xC1;
            prologueField.length = 0x01;
	        apduCmd[0] = 0xFE;
	        demo_CardResponse.rxDataLen = 0;
            demo_CardResponse.SW1 = 0;
            demo_CardResponse.SW2 = 0;

            // Transact using T=1 protocol
            status = SMARTCARD_EMV_DataExchangeT1( &prologueField, &apduCmd[0], &demo_CardResponse );
            if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
            {
               // Write the APDU command in I field array (Get CPLC Data Command)
               apduData[0] = 0x80;
               apduData[1] = 0xCA;
               apduData[2] = 0x9F;
               apduData[3] = 0x7F;
               apduData[4] = 0x00;
               prologueField.NAD = 0x00;
               prologueField.PCB = 0x00;
               prologueField.length = 0x05;

                status = SMARTCARD_EMV_DataExchangeT1(&prologueField, &apduData[0], &demo_CardResponse);
                if (status == SMARTCARD_TRANSACTION_SUCCESSFUL)
                {
                    if (demo_CardResponse.SW1 == 0x90 && demo_CardResponse.SW2 == 0x00)
                    {
                        Print_Text("CPLC data dump:");
                        for (index = 0; index < demo_CardResponse.rxDataLen; index++)
                        {
                            TransmitData(demo_CardResponse.apduData[index]);
                        }

                        Print_Text("IC Fabricator ID:");
                        TransmitData(demo_CardResponse.apduData[3]);
                        TransmitData(demo_CardResponse.apduData[4]);
                        Print_Text("IC Type:");
                        TransmitData(demo_CardResponse.apduData[5]);
                        TransmitData(demo_CardResponse.apduData[6]);
                    }
                    else
                    {
                        Print_Text("Status Bytes:");
                        PrintAsciiToHex(demo_CardResponse.SW1);
                        TransmitData( ' ' );
                        TransmitData( ' ' );
                        PrintAsciiToHex(demo_CardResponse.SW2);
                    }
                }
            }
        }

        // If T = 0 protocol supported
        if( transactionType == SMARTCARD_T0_TYPE )
        {
            //Execute Card Commands
            // EMV commands
            // APDU command for selecting application
            //Selecting Payment System Environment(PSE) master file "1PAY.SYS.DDF01"
            // -----------------------------------------------------------------------
            //  CLA | INS  |  P1  |  P2  | P3  |   Data |
            // -----------------------------------------------------------------------
            //  0x00| 0xA4 | 0x04 |  0x00| 0x0E | 0x31 0x50.....0x31 |
            // -----------------------------------------------------------------------
            apduCmd[0] = 0x00;
            apduCmd[1] = 0xA4;
            apduCmd[2] = 0x04;
            apduCmd[3] = 0x00;
            apduCmd[4] = 0x0E;
            apduCmd[5] = 0x31;
            apduCmd[6] = 0x50;
            apduCmd[7] = 0x41;
            apduCmd[8] = 0x59;
            apduCmd[9] = 0x2E;
            apduCmd[10] = 0x53;
            apduCmd[11] = 0x59;
            apduCmd[12] = 0x53;
            apduCmd[13] = 0x2E;
            apduCmd[14] = 0x44;
            apduCmd[15] = 0x44;
            apduCmd[16] = 0x46;
            apduCmd[17] = 0x30;
            apduCmd[18] = 0x31;
            apduCmd[19] = 0x00;
            apduCommandLength = 19;

            status = SMARTCARD_EMV_DataExchangeT0( &apduCmd[0], apduCommandLength, &demo_CardResponse );
            if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
            {
                if( demo_CardResponse.SW1 == 0x90 && demo_CardResponse.SW2 == 0x00 )
                {
                    WaitMilliSec( 10 );

                    indexCalc = 3 + demo_CardResponse.apduData[3] + 5;                      //SFI of the directory elementory file

                    //Issue read record command
                    apduCmd[0] = 0x00;
                    apduCmd[1] = 0xB2;
                    apduCmd[2] = 0x01;
                    apduCmd[3] = ( (demo_CardResponse.apduData[indexCalc]) << 3 ) | 0x4;    //Read record P1 i.e first record
                    apduCmd[4] = 0x00;

                    apduCommandLength = 5;

                    status = SMARTCARD_EMV_DataExchangeT0((uint8_t*) &apduCmd, apduCommandLength, &demo_CardResponse );

                    if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
                    {
                        WaitMilliSec( 10 );

                        cardNameIndex = 5 + demo_CardResponse.apduData[5] + 3;
                        cardNameLen = demo_CardResponse.apduData[cardNameIndex - 1];

                        Print_Text( "APPLICATION LABEL:" );
                        for( index = 0; index < cardNameLen; index++ )
                        {
                            TransmitData( demo_CardResponse.apduData[cardNameIndex + index] );
                        }

                        Uart_Newline_Char();
                        Uart_Newline_Char();
                        Print_Text( "APPLICATION PREFFERED NAME:" );
                        appPrefNameIndex = cardNameIndex + cardNameLen + 3;
                        appPrefNameLen = demo_CardResponse.apduData[appPrefNameIndex - 1];
                        for( index = 0; index < appPrefNameLen; index++ )
                        {
                            TransmitData( demo_CardResponse.apduData[appPrefNameIndex + index] );
                        }
                    }
                }
                else if( demo_CardResponse.SW1 == 0x6A && demo_CardResponse.SW2 == 0x82 )
                {
                    status = ApplicationSelectionByAID( 1 );
                    if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
                    {
                        if( demo_CardResponse.SW1 == 0x6A && demo_CardResponse.SW2 == 0x82 )
                        {
                            status = ApplicationSelectionByAID( 2 );
                            if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
                            {
                                if( demo_CardResponse.SW1 == 0x6A && demo_CardResponse.SW2 == 0x82 )
                                {
                                    status = ApplicationSelectionByAID( 3 );
                                    if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
                                    {
                                        if( demo_CardResponse.SW1 == 0x6A && demo_CardResponse.SW2 == 0x82 )
                                        {
                                            status = ApplicationSelectionByAID( 4 );
                                            if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
                                            {
                                                if( demo_CardResponse.SW1 == 0x6A && demo_CardResponse.SW2 == 0x82 )
                                                {
                                                    Print_Text( "FILE OR APPLICATION NOT FOUND...TRY SOME OTHER CARD\n" );
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Shut Down the Card when dont need anything to do with it
        SMARTCARD_Shutdown();
    }

    return ( 0 );
}

/*******************************************************************************
  Function:
    SMARTCARD_TRANSACTION_STATUS EMV_PowerOn(SMARTCARD_RESET_TYPE resetType)

  Description:
    This function does the PPS exchange with the smart card & configures the baud
    rate of the PIC UART module as per the PPS response from the smart card.

  Precondition:
    SMARTCARD_PowerOnATR was success

  Parameters:
    Input is pointer to PPS string

  Return Values:
    1 if PPS exchange is successful

  Remarks:
    This function is called when SMARTCARD_PowerOnATR() returns 1.
 *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS EMV_PowerOn( SMARTCARD_RESET_TYPES resetType )
{
    SMARTCARD_TRANSACTION_STATUS    scStatus;

    scStatus = SMARTCARD_EMV_ATRProcess( SMARTCARD_COLD_RESET );

    //Turn on power to Card and recieve and process Answer-to-Reset
    if( scStatus == SMARTCARD_TRANSACTION_SUCCESSFUL )
    {
        if( resetType == SMARTCARD_WARM_RESET )
        {
            scStatus = SMARTCARD_EMV_ATRProcess( SMARTCARD_WARM_RESET );
        }
    }

    if( scStatus == SMARTCARD_TRANSACTION_SUCCESSFUL )
    {
        if( doPPS )
        {
            if( SMARTCARD_IsPPSSupported() == SMARTCARD_PPS_ALLOWED )
            {
                scStatus = SMARTCARD_PPSExchange( &ppsString[0] );
                if( SMARTCARD_TRANSACTION_SUCCESSFUL != scStatus )
                {
                    return ( scStatus );
                }
            }
        }
    }

    return ( scStatus );
}

/*******************************************************************************
  Function:
    static SMARTCARD_TRANSACTION_STATUS ApplicationSelectionByAID(int aidType)

  Description:
    This function selects an application based on AID(Application Identifier).

  Precondition:
    SMARTCARD_PowerOnATR was success

  Parameters:
   Type of AID to use 1 for Visa , 2 for Maestro , 3 for Amex , 4 for Mastercard

  Return Values:
 None
 *****************************************************************************/
SMARTCARD_TRANSACTION_STATUS ApplicationSelectionByAID( int aidType )
{
    int                             index = 0;
    SMARTCARD_TRANSACTION_STATUS    status;

    //Application Identfier for VISA
    uint8_t                         aid1[8] = { 0x07, 0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10 };

    //Application Identfier for Maestro
    uint8_t                         aid2[8] = { 0x07, 0xA0, 0x00, 0x00, 0x00, 0x04, 0x30, 0x60 };

    //Application Identfier for Amex
    uint8_t                         aid3[8] = { 0x06, 0xA0, 0x00, 0x00, 0x00, 0x25, 0x01 };

    //Application Identifier for Mastercard
    uint8_t                         aid4[8] = { 0x07, 0xA0, 0x00, 0x00, 0x00, 0x04, 0x10, 0x10 };
    int                             cardNameIndex = 0;
    int                             cardNameLen = 0;
    apduCmd[0] = 0x00;
    apduCmd[1] = 0xA4;
    apduCmd[2] = 0x04;
    apduCmd[3] = 0x00;
    if( aidType == 1 )
    {
        memcpy( &apduCmd[4], &aid1[0], aid1[0] + 1 );
    }
    else if( aidType == 2 )
    {
        memcpy( &apduCmd[4], &aid2[0], aid2[0] + 1 );
    }
    else if( aidType == 3 )
    {
        memcpy( &apduCmd[4], &aid3[0], aid3[0] + 1 );
    }
    else if( aidType == 4 )
    {
        memcpy( &apduCmd[4], &aid4[0], aid4[0] + 1 );
    }

    apduCommandLength = apduCmd[4] + 5; //Length is AID bytes + 5 command bytes
    status = SMARTCARD_EMV_DataExchangeT0( &apduCmd[0], apduCommandLength, &demo_CardResponse );
    if( status == SMARTCARD_TRANSACTION_SUCCESSFUL )
    {
        if( demo_CardResponse.SW1 == 0x90 && demo_CardResponse.SW2 == 0x00 )
        {
            // if(demo_CardResponse.apduData[0])
            cardNameIndex = 5 + demo_CardResponse.apduData[3] + 3;
            cardNameLen = demo_CardResponse.apduData[cardNameIndex - 1];

            Print_Text( "APPLICATION LABEL:" );
            for( index = 0; index < cardNameLen; index++ )
            {
                TransmitData( demo_CardResponse.apduData[cardNameIndex + index] );
            }

            Uart_Newline_Char();
            Uart_Newline_Char();
        }
    }

    return ( status );
}

/*******************************************************************************
  Function:
    void  ConfigureUART(void)

  Description:
    This function configures the UART2 for displaying(Printing) the output.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
 *****************************************************************************/
static void ConfigureUART( void )
{
    __builtin_write_OSCCONL( OSCCON & 0xbf );
    UartConfig();
    UART_Tx_TRIS_Pin = 0;

    U2MODE = 0;
    U2STA = 0;

    U2BRG = BRGVAL;         // BAUD Rate Setting for 9600
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;

    while( !U2STAbits.TRMT );
}

/*******************************************************************************
  Function:
    void TransmitData(unsigned char Data)

  Description:
    This function transmits data to the serial port.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
 *****************************************************************************/
static void TransmitData( unsigned char Data )
{
    U2TXREG = Data;
    Nop();
    Nop();
    while( !U2STAbits.TRMT );
}

/*******************************************************************************
  Function:
    void PrintAsciiToHex(char a)

  Description:
    This function sends(prints) the hex value of the given character to the serial terminal.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
 *****************************************************************************/
static void PrintAsciiToHex( char a )
{
    char    hex[3];
    char    c;
    c = ( a >> 4 ) & 0x0f;
    if( c <= 9 )
    {
        c += '0';
    }
    else
    {
        c += 'a' - 10;
    }

    hex[0] = c;
    TransmitData( hex[0] );
    c = a & 0x0f;
    if( c <= 9 )
    {
        c += '0';
    }
    else
    {
        c += 'a' - 10;
    }

    hex[1] = c;
    TransmitData( hex[1] );
}

/*******************************************************************************
  Function:
    void Print_Text(unsigned char *header)

  Description:
    This function sends the given text the serial terminal.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None
 *****************************************************************************/
static void Print_Text( char *header )
{
    volatile unsigned int   hdr_index;
    hdr_index = 0;
    Nop();
    Nop();
    while( header[hdr_index] != '\0' )
    {
        TransmitData( header[hdr_index++] );
    }
}

/******************************************************************************
 * Function:       void Uart_Newline_Char(void)
 *
 * PreCondition:
 *
 * Input:          None
 *
 * Output:         None
 *
 * Side Effects:   None
 *
 * Overview:       Transmit the new line and carriage return character..
 *
 * Note:           None
 *****************************************************************************/
static void Uart_Newline_Char( void )
{
    U2TXREG = '\n';
    while( !U2STAbits.TRMT );
    Nop();
    Nop();
    Nop();
    Nop();
    U2TXREG = '\r';
    while( !U2STAbits.TRMT );
}
