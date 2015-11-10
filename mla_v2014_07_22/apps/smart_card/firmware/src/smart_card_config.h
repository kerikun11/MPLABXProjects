/********************************************************************
 FileName:	smart_card_config.h
 Dependencies:	See INCLUDES section
 Processor:	PIC24 Microcontrollers
 Hardware:	This demo is natively intended to be used on Exp 16,
                This demo can be modified for use on other hardware platforms.
 Complier:  	Microchip PIC24
 Company:	Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the ?Company?) for its PIC® Microcontroller is intended and
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

#ifndef SMART_CARD_CONFIG_H
#define SMART_CARD_CONFIG_H


/* 

  Summary:
    To Support the EMV standard part of the code

  Description:
    Support the EMV functionality in the code.

  Remarks:
    None
 */
	#define		EMV_SUPPORT

/* 

  Summary:
    To enable the T1 protocol.

  Description:
    Support the T1 part of protocol in the code.

  Remarks:
    None
 */
	#define		SMARTCARD_PROTO_T1

/*

  Summary:
     Define the Buffer size of Application Protocol Data Unit (APDU).

  Description:
    Maximum size of the buffer of APDU

  Remarks:
    None
 */
	#define		SMARTCARD_APDU_BUFF_SIZE		256

/*

  Summary:
     Define the Maximum Buffer size for T1 Protocol.

  Description:
     Modify the T1 block buffer size as per the RAM size of the chosen micro & project requirement

  Remarks:
    None
 */

	#define		SMARTCARD_T1_PROTOCOL_MAX_BUFF_SIZE		256

   

#endif //smart_card_config
