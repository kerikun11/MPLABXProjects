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

#include <plib.h>
#include "system.h"
#include "system_config.h"

#define PIC32MX_SPI1_SDO_SCK_MASK_VALUE      (0x00000140)
#define PIC32MX_SPI1_SDI_MASK_VALUE          (0x00000080)
//#define PIC32MX_INT2_MASK_VALUE            (0x00000010)
//#define PIC32MX_INT1_MASK_VALUE            (0x00000008)
#define PIC32MX_INT1_MASK_VALUE              (0x00000100)
/* MAX SPI CLOCK FREQ SUPPORTED FOR MIWI TRANSCIEVER */
#define MAX_SPI_CLK_FREQ_FOR_P2P             (1000000)

#pragma config FPLLMUL = MUL_16, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = XT, FNOSC = PRIPLL, FPBDIV = DIV_4, WDTPS = PS1024


/*********************************************************************
 * Function:        void SYSTEM_Initialize( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Board is initialized for P2P usage
 *
 * Overview:        This function configures the board
 *
 * Note:            This routine needs to be called before the function
 *                  to initialize P2P stack or any other function that
 *                  operates on the stack
 ********************************************************************/

void SYSTEM_Initialize(void)
{

    // Make RB0 as Digital input
    AD1PCFGbits.PCFG2 = 1;

    // set I/O ports
    BUTTON_1_TRIS = 1;
    BUTTON_2_TRIS = 1;
    LED_1_TRIS = 0;
    LED_2_TRIS = 0;

    
    PHY_CS_TRIS = 0;
    PHY_CS = 1;
    PHY_RESETn_TRIS = 0;
    PHY_RESETn = 1;
    

    RF_INT_TRIS = 1;

    SDI_TRIS = 1;
    SDO_TRIS = 0;
    SCK_TRIS = 0;
    SPI_SDO = 0;
    SPI_SCK = 0;

    
    PHY_WAKE_TRIS = 0;
    PHY_WAKE = 1;
    

 


    
   /* Clear SPI1CON register */
   SPI1CONCLR = 0xFFFFFFFF;
   SPI2CONCLR = 0xFFFFFFFF;
   #ifdef HARDWARE_SPI
       unsigned int pbFreq;

       /* Enable SPI1, Set to Master Mode & Set CKE bit : Serial output data changes on transition
          from active clock state to Idle clock state */
       SPI1CON = 0x00008120;
       SPI2CON = 0x00008120;
       /* Peripheral Bus Frequency = System Clock / PB Divider */
       pbFreq = (uint32_t)SYS_CLK_FrequencySystemGet() / (1 << mOSCGetPBDIV() );

       /* PB Frequency can be maximum 40 MHz */
       if( pbFreq > ( 2 * MAX_SPI_CLK_FREQ_FOR_P2P) )
       {
           {
               unsigned int SPI_Clk_Freq;

               unsigned char SPI_Brg = 1;

               /* Continue the loop till you find SPI Baud Rate Register Value */
               while(1)
               {
                  /* SPI Clock Calculation as per PIC32 Manual */
                  SPI_Clk_Freq = pbFreq / ( 2 * ( SPI_Brg + 1) );

                  if( SPI_Clk_Freq <= MAX_SPI_CLK_FREQ_FOR_P2P )
                  {
                      break;
                  }

                  SPI_Brg++;
               }

              mSpiChnSetBrg(1,SPI_Brg);
              mSpiChnSetBrg(2,SPI_Brg);

           }
       }
       else
       {
           /* Set SPI1 Baud Rate */
           mSpiChnSetBrg(1,0);
           mSpiChnSetBrg(2,0);
       }


   #endif


   /* Set the Port Directions of SDO, SDI, Clock & Slave Select Signal */
   mPORTFSetPinsDigitalOut(PIC32MX_SPI1_SDO_SCK_MASK_VALUE);
   mPORTFSetPinsDigitalIn(PIC32MX_SPI1_SDI_MASK_VALUE);

   /* Set the INT1 port pin to input */
   mPORTESetPinsDigitalIn(BIT_8 | BIT_9);

   mPORTBSetPinsDigitalOut(BIT_2 | BIT_4);
   mPORTGSetPinsDigitalOut(BIT_2);

   /* Set the Interrupt Priority */
   mINT1SetIntPriority(4);

   /* Set Interrupt Subpriority Bits for INT1 */
   mINT1SetIntSubPriority(2);

   /* Set INT1 to falling edge */
   mINT1SetEdgeMode(0);


   /* Enable INT1 */
   mINT1IntEnable(1);


   /* Enable Multi Vectored Interrupts */
   INTEnableSystemMultiVectoredInt();
    

    // Make RB0 as Digital input
    AD1PCFGbits.PCFG2 = 1;

    #if defined(ENABLE_NVM)
        EE_nCS_TRIS = 0;
        EE_nCS = 1;
    #endif

   
    RFIF = 0;
    if( RF_INT_PIN == 0 )
    {
        RFIF = 1;
    }
    



    LCD_Initialize();

}





