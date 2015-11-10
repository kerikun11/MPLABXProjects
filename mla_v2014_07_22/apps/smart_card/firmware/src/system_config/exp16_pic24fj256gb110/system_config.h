/*******************************************************************************
  System Specific Definitions

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    System level definitions for the specific Microchip Development Board used.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H
#include "system.h"
#include "smart_card_config.h"
#include <xc.h>

	    

	
		// Enable Port Pin of Micro as Vcc for Smart Card
		#define  SMARTCARD_ENABLE_POWER_THROUGH_PORT_PIN

		// Set Clock Freq to drive Smart Card
		#define SMARTCARD_Drv_ClockSet()            (REFOCON = 0x0300)

		//Enable UART
		#define SMARTCARD_Drv_EnableUART()	    	(U1MODEbits.UARTEN = 1)

		// Enable Clock to drive Smart Card
		#define SMARTCARD_Drv_EnableClock()	    	(REFOCONbits.ROON = 1)

		// Disable Clock used to drive Smart Card
		#define SMARTCARD_Drv_DisableClock()	    (REFOCONbits.ROON = 0)

		// Set Clock Freq to drive Smart Card
		#define SMARTCARD_Drv_EnableDelayTimerIntr()   (IPC2bits.T3IP = 4,IFS0bits.T3IF = 0,T2CONbits.T32 = 1,IEC0bits.T3IE = 1)

		// One count of timer 2/3 corresponds to how much micro seconds...
		#define SMARTCARD_TIMER23_SINGLE_COUNT_MICRO_SECONDS	(uint8_t)(FCY/1000000UL)

		// Enable Clock to drive Smart Card
		#define SMARTCARD_Drv_SetDelayTimerCnt(count)	    (PR2 = count,PR3 = (count >> 16))

		// Enable Clock to drive Smart Card
		#define SMARTCARD_Drv_EnableDelayTimer()			(TMR2 = 0,TMR3 = 0,T2CONbits.TON = 1)

		// Disable Clock used to drive Smart Card
		#define SMARTCARD_Drv_DisableDelayTimer()	    	(T2CONbits.TON = 0,IFS0bits.T3IF = 0)

		#ifdef EMV_SUPPORT

			#define SMARTCARD_Drv_EnableDelayTimerIntr45()   (IPC7bits.T5IP = 4,IFS1bits.T5IF = 0,T4CONbits.T32 = 1,IEC1bits.T5IE = 1)

			// One count of timer 2/3 corresponds to how much micro seconds...
			#define SMARTCARD_TIMER45_SINGLE_COUNT_MICRO_SECONDS	(uint8_t)(FCY/1000000UL)

			// Enable Clock to drive Smart Card
			#define SMARTCARD_Drv_SetDelayTimerCnt45(count)	    (PR4 = count,PR5 = (count >> 16))

			// Enable Clock to drive Smart Card
			#define SMARTCARD_Drv_EnableDelayTimer45()	    	(TMR4 = 0,TMR5 = 0,T4CONbits.TON = 1)

			// Disable Clock used to drive Smart Card
			#define SMARTCARD_Drv_DisableDelayTimer45()	    	(T4CONbits.TON = 0,IFS1bits.T5IF = 0)

		#endif

		//Reference Clock Circuit - Input Clock
		#define SMARTCARD_REF_CLOCK_CIRCUIT_INPUT_CLK    		SYS_CLK_FrequencySystemGet()

		//Reference Clock Circuit - Input Clock
		#define SMARTCARD_REF_CLOCK_POWER2_VALUE      		(uint8_t)REFOCONbits.RODIV

		//Reference Clock Circuit - Input Clock
		#define SMARTCARD_REF_CLOCK_DIVISOR_VALUE      		(uint8_t)0

		// Frequency of clock given to smart card
		#define SMARTCARD_REF_CLOCK_TO_SMART_CARD     ((unsigned long)(SYS_FREQ/(pow(2,REFOCONbits.RODIV))))

		//Turn on 1/off 0 card power
		#define SMARTCARD_Drv_SetSwitchCardPower(x) 			(LATBbits.LATB9=(x))

		//set reset state to the value x
		#define SMARTCARD_Drv_SetSwitchCardReset(x) 			(LATEbits.LATE8=(x))

		//set tx pin to the value x
		#define SMARTCARD_Drv_SetTxPinData(x) 					(LATFbits.LATF2=(x))

		//set tx pin to the value x
		#define SMARTCARD_Drv_SetRxPinData(x) 					(LATFbits.LATF3=(x))

		//Get Smart Card Present status
		#define SMARTCARD_Drv_CardPresent()	      				  (PORTBbits.RB0 || !PORTBbits.RB1)

		//Get Rx Pin Data
		#define SMARTCARD_Drv_GetRxPinData()               		(PORTCbits.RC4)

		//Set Tx Pin direction
		#define SMARTCARD_Drv_TxPin_Direction(flag)    			(TRISFbits.TRISF2 = flag)

		//Set Rx Pin direction
		#define SMARTCARD_Drv_RxPin_Direction(flag)    			(TRISFbits.TRISF3 = flag)

		//Set Power Pin direction connected to the smart card
		#define SMARTCARD_Drv_PowerPin_Direction(flag) 			(TRISBbits.TRISB9 = flag)

		//Set Reset Pin direction connected to the smart card
		#define SMARTCARD_Drv_ResetPin_Direction(flag) 			(TRISEbits.TRISE8 = flag)

		//Set Card Present Pin direction connected to the smart card
		#define SMARTCARD_Drv_CardPresent_Direction(flag) 		(TRISBbits.TRISB0 = flag)

		//Set Sim Present Pin direction connected to the smart card
		#define SMARTCARD_Drv_SimPresent_Direction(flag) 		(TRISBbits.TRISB1 = flag)

		// Enable Pull up at Tx Pin
		#define SMARTCARD_Drv_EnableTxPinPullUp()				(_CN48PUE = 1)

		// Enable Pull up at Rx Pin
		#define SMARTCARD_Drv_EnableRxPinPullUp()				(_CN70PUE = 1)

		// Enable Pull up for SMART_CARD_DETECTION
		#define SMARTCARD_Drv_EnableCardPresentPinPullUp()		(_CN2PUE = 1)

		// Enable Pull up for SIM_CARD_DETECTION
		#define SMARTCARD_Drv_EnableSimPresentPinPullUp()		(_CN3PUE = 1)

		// Disable Pull up at Tx Pin
		#define SMARTCARD_Drv_DisableTxPinPullUp()				(_CN48PUE = 0)

		// Disable Pull up at Rx Pin
		#define SMARTCARD_Drv_DisableRxPinPullUp()				(_CN70PUE = 0)

                //Set data parity
                #define SMARTCARD_Drv_SetParity(parity)              (U1MODEbits.PDSEL = parity)

		// MAP UART Rx Pin
		#define MapUART1RxPin()							PPSIn( RPI41, U1RX_FUNC )

		// MAP UART Tx Pin
		#define MapUART1TxPin()							PPSOut( RP30, U1TX_FUNC )
      

		#define UART_Tx_REMAP_Reg   ( _RP17R )  //UART2
		#define UART_Tx_TRIS_Pin    ( _TRISF5 )

#endif 




