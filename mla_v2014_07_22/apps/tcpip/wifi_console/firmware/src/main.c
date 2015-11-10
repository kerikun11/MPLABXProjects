/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Module for Microchip TCP/IP Stack
    -Demonstrates how to call and use the Microchip TCP/IP stack
    -Reference: Microchip TCP/IP Stack Help (TCPIP Stack Help.chm)

  Description:
    Main Application Entry Point and TCP/IP Stack Demo

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <2014> released Microchip Technology Inc.  All rights reserved.

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

/*
 * This macro uniquely defines this file as the main entry point.
 * There should only be one such definition in the entire project,
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

// Include all headers for any enabled TCPIP Stack functions
#include "tcpip/tcpip.h"
#include "driver/wifi/mrf24w/src/drv_wifi_easy_config.h"

#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
#include "tcpip/zero_conf_link_local.h"
#endif
#if defined(STACK_USE_ZEROCONF_MDNS_SD)
#include "tcpip/zero_conf_link_multicast_dns.h"
#endif

// Include functions specific to this stack application
#include "main.h"

// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO

// Declare AppConfig structure and some other supporting stack variables
APP_CONFIG AppConfig;
static unsigned short wOriginalAppConfigChecksum;   // Checksum of the ROM defaults for AppConfig
uint8_t AN0String[8];

// Private helper functions.
// These may or may not be present in all applications.
static void InitAppConfig(void);
/*static */void InitializeBoard(void);

#if defined(WF_CS_TRIS)
    void WF_Connect(void);
#if !defined(MRF24WG)
    extern bool gRFModuleVer1209orLater;
#endif  /* !defined(MRF24WG) */
#if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
tPassphraseReady g_WpsPassphrase;
#endif  /* defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) */
#endif  /* defined(WF_CS_TRIS) */

#if !defined(STACK_USE_UART)
#error "Must have STACK_USE_UART defined for the console demo"
#endif

//
// PIC18 Interrupt Service Routines
//
#if defined(__XC8)
    void interrupt low_priority LowISR(void)
    {
        TickUpdate();
    }

    void interrupt HighISR(void)
    {
        #if defined(STACK_USE_UART2TCP_BRIDGE)
            UART2TCPBridgeISR();
        #endif

        #if defined(WF_CS_TRIS)
            WFEintISR();
        #endif // WF_CS_TRIS
    }

// PIC24 and PIC32 Exception Handlers
// If your code gets here, you either tried to read or write
// a NULL pointer, or your application overflowed the stack
// by having too many local variables or parameters declared.
#elif defined(__XC16)

    #if defined(STACK_USE_UART)
      #define UART2PrintString    putrsUART
    #else
      #define UART2PrintString(x)
    #endif

    void __attribute__((interrupt, auto_psv)) _DefaultInterrupt(void)
    {
      UART2PrintString( "!!! Default interrupt handler !!!\r\n" );
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }

    void __attribute__((interrupt, auto_psv)) _OscillatorFail(void)
    {
      UART2PrintString( "!!! Oscillator Fail interrupt handler !!!\r\n" );
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _AddressError(void)
    {
      UART2PrintString( "!!! Address Error interrupt handler !!!\r\n" );
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _StackError(void)
    {
      UART2PrintString( "!!! Stack Error interrupt handler !!!\r\n" );
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }
    void __attribute__((interrupt, auto_psv)) _MathError(void)
    {
      UART2PrintString( "!!! Math Error interrupt handler !!!\r\n" );
      while (1)
      {
          Nop();
          Nop();
          Nop();
      }
    }

#elif defined(__XC32)
    void _general_exception_handler(unsigned cause, unsigned status)
    {
        Nop();
        Nop();
    }
#endif

#ifdef WF_CS_TRIS
// Global variables
uint8_t ConnectionProfileID;
#endif  /* WF_CS_TRIS */

#if defined(HOST_CM_TEST)
extern uint8_t g_event;
#endif

//
// Main application entry point.
//
#if defined(__XC8)
void main(void)
#else
int main(void)
#endif
{
    static uint32_t t = 0;
    static uint32_t dwLastIP = 0;

#if defined(HOST_CM_TEST)
    uint32_t t1 = 0;
    char st[80];
    bool host_scan = false;
    uint16_t scan_count = 0;
#endif

    // Initialize application specific hardware
    InitializeBoard();

    #if defined(USE_LCD)
    // Initialize and display the stack version on the LCD
    LCDInit();
    DelayMs(100);
    strcpypgm2ram((char*)LCDText, "TCPStack " TCPIP_STACK_VERSION "  "
        "                ");
    LCDUpdate();
    #endif

    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();
    #if defined(STACK_USE_MPFS2)
    MPFSInit();
    #endif

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    // Initiates board setup process if button is depressed
    // on startup
    if(BUTTON0_IO == 0u)
    {
        #if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        // Invalidate the EEPROM contents if BUTTON0 is held down for more than 4 seconds
        uint32_t StartTime = TickGet();
        LED_PUT(0x00);

        while(BUTTON0_IO == 0u)
        {
            if(TickGet() - StartTime > 4*TICK_SECOND)
            {
                #if defined(EEPROM_CS_TRIS)
                XEEBeginWrite(0x0000);
                XEEWrite(0xFF);
                XEEWrite(0xFF);
                XEEEndWrite();
                #elif defined(SPIFLASH_CS_TRIS)
                SPIFlashBeginWrite(0x0000);
                SPIFlashWrite(0xFF);
                SPIFlashWrite(0xFF);
                #endif

                #if defined(STACK_USE_UART)
                putrsUART("\r\n\r\nBUTTON0 held for more than 4 seconds.  Default settings restored.\r\n\r\n");
                #endif

                LED_PUT(0x0F);
                while((int32_t)(TickGet() - StartTime) <= (int32_t)(9*TICK_SECOND/2));
                LED_PUT(0x00);
                while(BUTTON0_IO == 0u);
                Reset();
                break;
            }
        }
        #endif

        #if defined(STACK_USE_UART)
        DoUARTConfig();
        #endif
    }

    // Initialize core stack layers (MAC, ARP, TCP, UDP) and
    // application modules (HTTP, etc.)
    StackInit();

    #if defined(WF_CS_TRIS)
    #if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
        g_WpsPassphrase.valid = false;
    #endif  /* defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) */
    WF_Connect();
    #endif

    // Initialize any application-specific modules or functions/
    // For this demo application, this only includes the
    // UART 2 TCP Bridge
    #if defined(STACK_USE_UART2TCP_BRIDGE)
    UART2TCPBridgeInit();
    #endif

    #if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
        ZeroconfLLInitialize();
    #endif

    #if defined(STACK_USE_ZEROCONF_MDNS_SD)
    mDNSInitialize(MY_DEFAULT_HOST_NAME);
    mDNSServiceRegister(
        (const char *) "DemoWebServer", // base name of the service
        "_http._tcp.local",             // type of the service
        80,                             // TCP or UDP port, at which this service is available
        ((const uint8_t *)"path=/index.htm"),   // TXT info
        1,                                  // auto rename the service when if needed
        NULL,                               // no callback function
        NULL                                // no application context
        );

        mDNSMulticastFilterRegister();
    #endif

    // Now that all items are initialized, begin the co-operative
    // multitasking loop.  This infinite loop will continuously
    // execute all stack-related tasks, as well as your own
    // application's functions.  Custom functions should be added
    // at the end of this loop.
    // Note that this is a "co-operative mult-tasking" mechanism
    // where every task performs its tasks (whether all in one shot
    // or part of it) and returns so that other tasks can do their
    // job.
    // If a task needs very long time to do its job, it must be broken
    // down into smaller pieces so that other tasks can have CPU time.

    while(1)
    {

#if defined(HOST_CM_TEST)
       switch (g_event)
        {
            case WF_EVENT_CONNECTION_PERMANENTLY_LOST:
            case WF_EVENT_CONNECTION_FAILED:
                g_event = 0xff;             // clear current event
                // if host scan is active, it can be forced inactive by connection/re-connection process
                // so just reset host scan state to inactive.
                host_scan = false;          // host scan inactive
                #if defined(STACK_USE_UART)
                putrsUART("Reconnecting....\r\n");
                #endif
                WF_CMConnect(ConnectionProfileID);
                break;
            case WF_EVENT_CONNECTION_SUCCESSFUL:
                g_event = 0xff;             // clear current event
                // if host scan is active, it can be forced inactive by connection/re-connection process
                // so just reset host scan state to inactive.
                host_scan = false;          // host scan inactive
                break;
            case WF_EVENT_SCAN_RESULTS_READY:
                g_event = 0xff;             // clear current event
                host_scan = false;          // host scan inactive
                // Scan results are valid - OK to retrieve
                if (SCANCXT.numScanResults > 0)
                {
                    SCAN_SET_DISPLAY(SCANCXT.scanState);
                    SCANCXT.displayIdx = 0;
                    while (IS_SCAN_STATE_DISPLAY(SCANCXT.scanState))
                         WFDisplayScanMgr();
                }
                break;
           case WF_EVENT_CONNECTION_TEMPORARILY_LOST:
                // This event can happened when CM in module is enabled.
                g_event = 0xff;         // clear current event
                // if host scan is active, it can be forced inactive by connection/re-connection process
                // so just reset host scan state to inactive.
                host_scan = false;      // host scan inactive
                break;
            default:
                //sprintf(st,"skip event = %d\r\n",g_event);
                //putrsUART(st);
                break;
        }

        // Do host scan
        if(TickGet() - t1 >= TICK_SECOND*20)
        {
            t1 = TickGet();
            if (!host_scan)             // allow host scan if currently inactive
            {
                sprintf(st,"%d Scanning ..... event = %d\r\n",++scan_count, g_event);
                #if defined(STACK_USE_UART)
                putrsUART(st);
                #endif
                host_scan = true;       // host scan active
                WF_Scan(0xff);          // scan on all channels
            }
        }
#endif  //HOST_CM_TEST

        // Blink LED0 (right most one) every second.
        if(TickGet() - t >= TICK_SECOND/2ul)
        {
            t = TickGet();
            LED0_IO ^= 1;
        }

        // If mixed mode is not supported, security mode needs to be downgraded
        if (AppConfig.changeSecurityModeFlag == 1)
        {
            #if defined(STACK_USE_UART)
                putrsUART("\r\nNow the security mode will be downgraded to: WPA with key\r\n\r\n");
            #endif
            WF_Connect();
            AppConfig.changeSecurityModeFlag = 0;
        }

        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();

        #if defined(WF_CS_TRIS)
        #if !defined(MRF24WG)
        if (gRFModuleVer1209orLater)
        #endif
            WiFiTask();
        #endif

        // This tasks invokes each of the core stack application tasks
        StackApplications();

        #if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
        ZeroconfLLProcess();
        #endif

        #if defined(STACK_USE_ZEROCONF_MDNS_SD)
        mDNSProcess();
        // Use this function to exercise service update function
        // HTTPUpdateRecord();
        #endif

        // Process application specific tasks here.
        // For this demo app, this will include the Generic TCP
        // client and servers, and the Ping
        // demos.  Following that, we will process any IO from
        // the inputs on the board itself.
        // Any custom modules or processing you need to do should
        // go here.

        #if defined(STACK_USE_AUTOUPDATE_TCPCLIENT) && defined (MRF24WG)
        AutoUpdate_TCPClient();
        #endif

#if defined(STACK_USE_AUTOUPDATE_UART)
        #if defined (MRF24WG)
            AutoUpdate_UartXMODEM_24G();
        #else
                #if !defined(MRF24WG) && defined( __XC32 )
                    AutoUpdate_UartXMODEM_Roadrunner();
                #endif
        #endif
#endif
        #if defined(STACK_USE_FTP_CLIENT)
        FTPClient();
        #endif

        #if defined(STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE)
        GenericTCPClient();
        #endif

        #if defined(STACK_USE_GENERIC_TCP_SERVER_EXAMPLE)
        GenericTCPServer();
        #endif

        #if defined(STACK_USE_SMTP_CLIENT)
        SMTPDemo();
        #endif

        #if defined(STACK_USE_ICMP_CLIENT)
        PingDemo();
        PingConsole();
        #endif

        #if defined(STACK_USE_BERKELEY_API)
        BerkeleyTCPClientDemo();
        BerkeleyTCPServerDemo();
        BerkeleyUDPClientDemo();
        #endif

        // If the local IP address has changed (ex: due to DHCP lease change)
        // write the new IP address to the LCD display, UART, and Announce
        // service
        if(dwLastIP != AppConfig.MyIPAddr.Val)
        {
            dwLastIP = AppConfig.MyIPAddr.Val;

            #if defined(STACK_USE_UART)
                putrsUART((ROM char*)"\r\nNew IP Address: ");
            #endif

            DisplayIPValue(AppConfig.MyIPAddr);

            #if defined(STACK_USE_UART)
                putrsUART((ROM char*)"\r\n");
            #endif

            #if defined(STACK_USE_ANNOUNCE)
                AnnounceIP();
            #endif

            #if defined(STACK_USE_ZEROCONF_MDNS_SD)
                mDNSFillHostRecord();
            #endif
        }

        #if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) && defined (MRF24WG)
            if (g_WpsPassphrase.valid) {
                WF_ConvPassphrase2Key(g_WpsPassphrase.passphrase.keyLen, g_WpsPassphrase.passphrase.key,
                g_WpsPassphrase.passphrase.ssidLen, g_WpsPassphrase.passphrase.ssid);
                WF_SetPSK(g_WpsPassphrase.passphrase.key);
                g_WpsPassphrase.valid = false;
            }
        #endif  /* defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) */

        if(AppConfig.hibernateFlag == 1) AppConfig.hibernateFlag = 0;
    }
}

#if defined(WF_CS_TRIS)
/*****************************************************************************
 * FUNCTION: WF_Connect
 *
 * RETURNS:  None
 *
 * PARAMS:   None
 *
 *  NOTES:   Connects to an 802.11 network.  Customize this function as needed
 *           for your application.
 *****************************************************************************/
void WF_Connect(void)
{
    uint8_t ConnectionState;
    uint8_t channelList[] = MY_DEFAULT_CHANNEL_LIST;

    if (AppConfig.changeSecurityModeFlag == 1)
    {
        /* We will re-use the current profile */
        WF_CMGetConnectionState(&ConnectionState, &ConnectionProfileID);
        WF_CPSetSecurity(ConnectionProfileID, WF_SECURITY_WPA_WITH_KEY,
                0, AppConfig.SecurityKey, 32);
        WF_CMConnect(ConnectionProfileID);
        return;
    }

    /* create a Connection Profile */
    WF_CPCreate(&ConnectionProfileID);

    AppConfig.passPhraseToKeyFlag = 0;

    WF_SetRegionalDomain(MY_DEFAULT_DOMAIN);

    WF_CPSetSsid(ConnectionProfileID,
                 AppConfig.MySSID,
                 AppConfig.SsidLength);

    WF_CPSetNetworkType(ConnectionProfileID, MY_DEFAULT_NETWORK_TYPE);

    WF_CASetScanType(MY_DEFAULT_SCAN_TYPE);

    WF_CASetChannelList(channelList, sizeof(channelList));

    // The Retry Count parameter tells the WiFi Connection manager how many attempts to make when trying
    // to connect to an existing network.  In the Infrastructure case, the default is to retry forever so that
    // if the AP is turned off or out of range, the radio will continue to attempt a connection until the
    // AP is eventually back on or in range.  In the Adhoc case, the default is to retry 3 times since the
    // purpose of attempting to establish a network in the Adhoc case is only to verify that one does not
    // initially exist.  If the retry count was set to WF_RETRY_FOREVER in the AdHoc mode, an AdHoc network
    // would never be established.
    WF_CASetListRetryCount(MY_DEFAULT_LIST_RETRY_COUNT);

    WF_CASetEventNotificationAction(MY_DEFAULT_EVENT_NOTIFICATION_LIST);

    WF_CASetBeaconTimeout(MY_DEFAULT_BEACON_TIMEOUT);

    #if !defined(MRF24WG)
        if (gRFModuleVer1209orLater)
        {
           // If WEP security is used, set WEP Key Type.  The default WEP Key Type is Shared Key.
            if (AppConfig.SecurityMode == WF_SECURITY_WEP_40 || AppConfig.SecurityMode == WF_SECURITY_WEP_104)
            {
                WF_CPSetWepKeyType(ConnectionProfileID, MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE);
            }
        }
        // if earlier version than 1209, use WEP Open Key default in module.
    #else
        {
            // If WEP security is used, set WEP Key Type.  The default WEP Key Type is Shared Key.
            if (AppConfig.SecurityMode == WF_SECURITY_WEP_40 || AppConfig.SecurityMode == WF_SECURITY_WEP_104)
            {
                WF_CPSetWepKeyType(ConnectionProfileID, MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE);
            }
        }
    #endif

    #if defined(MRF24WG)
        // Error check items specific to WPS Push Button mode
        #if (MY_DEFAULT_WIFI_SECURITY_MODE==WF_SECURITY_WPS_PUSH_BUTTON)
            #if !defined(WF_P2P)
                WF_ASSERT(strlen(AppConfig.MySSID) == 0);  // SSID must be empty when using WPS
                WF_ASSERT(sizeof(channelList)==11);        // must scan all channels for WPS
            #endif

            #if (MY_DEFAULT_NETWORK_TYPE == WF_P2P)
                WF_ASSERT(strcmp((char *)AppConfig.MySSID, "DIRECT-") == 0);
                WF_ASSERT(sizeof(channelList) == 3);
                WF_ASSERT(channelList[0] == 1);
                WF_ASSERT(channelList[1] == 6);
                WF_ASSERT(channelList[2] == 11);
            #endif

        #endif

    #endif /* MRF24WG */

    #if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
        if (AppConfig.SecurityMode == WF_SECURITY_WPA_WITH_PASS_PHRASE
            || AppConfig.SecurityMode == WF_SECURITY_WPA2_WITH_PASS_PHRASE
            || AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE) {
            WF_ConvPassphrase2Key(AppConfig.SecurityKeyLength, AppConfig.SecurityKey,
                AppConfig.SsidLength, AppConfig.MySSID);
            AppConfig.SecurityMode--;
            AppConfig.SecurityKeyLength = 32;
            AppConfig.passPhraseToKeyFlag = 1;
                }
    #if defined (MRF24WG)
        else if (AppConfig.SecurityMode == WF_SECURITY_WPS_PUSH_BUTTON
                    || AppConfig.SecurityMode == WF_SECURITY_WPS_PIN) {
            WF_YieldPassphrase2Host();
        }
    #endif  /* defined (MRF24WG) */
    #endif  /* defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST) */

    #if !defined(MRF24WG)
        Delay10us(10);  //give time to Roadrunner to clean message buffer, because Security message is a big data package
    #endif

    WF_CPSetSecurity(ConnectionProfileID,
                     AppConfig.SecurityMode,
                     AppConfig.WepKeyIndex,   /* only used if WEP enabled */
                     AppConfig.SecurityKey,
                     AppConfig.SecurityKeyLength);

    #if MY_DEFAULT_PS_POLL == WF_ENABLED
        WF_PsPollEnable(true);
    #if !defined(MRF24WG)
        if (gRFModuleVer1209orLater)
            WFEnableDeferredPowerSave();
    #endif  /* !defined(MRF24WG) */
    #else   /* MY_DEFAULT_PS_POLL != WF_ENABLED */
        WF_PsPollDisable();
    #endif  /* MY_DEFAULT_PS_POLL == WF_ENABLED */

    #if defined(STACK_USE_UART)
        WF_OutputConnectionInfo(&AppConfig);
    #endif

    #if defined(DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE)
        WF_DisableModuleConnectionManager();
    #endif

    #if defined(MRF24WG)
    WFEnableDebugPrint(ENABLE_WPS_PRINTS | ENABLE_P2P_PRINTS);
    #endif

    WF_CMConnect(ConnectionProfileID);
}
#endif /* WF_CS_TRIS */

// Writes an IP address to the LCD display and the UART as available
void DisplayIPValue(IP_ADDR IPVal)
{
//  printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    uint8_t IPDigit[4];
    uint8_t i;
#ifdef USE_LCD
    uint8_t j;
    uint8_t LCDPos=16;
#endif

    for(i = 0; i < sizeof(IP_ADDR); i++)
    {
        uitoa((uint16_t)IPVal.v[i], IPDigit);

        #if defined(STACK_USE_UART)
            putsUART((char *) IPDigit);
        #endif

        #ifdef USE_LCD
            for(j = 0; j < strlen((char*)IPDigit); j++)
            {
                LCDText[LCDPos++] = IPDigit[j];
            }
            if(i == sizeof(IP_ADDR)-1)
                break;
            LCDText[LCDPos++] = '.';
        #else
            if(i == sizeof(IP_ADDR)-1)
                break;
        #endif

        #if defined(STACK_USE_UART)
            while(BusyUART());
            WriteUART('.');
        #endif
    }

    #ifdef USE_LCD
        if(LCDPos < 32u)
            LCDText[LCDPos] = 0;
        LCDUpdate();
    #endif
}

/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware.  It is a generic initialization
    routine for many of the Microchip development boards, using definitions
    in system_config.h to determine specific initialization.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
/*static*/ void InitializeBoard(void)
{
    // LEDs
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
    LED6_TRIS = 0;
    LED7_TRIS = 0;
    LED_PUT(0x00);

#if defined(__XC8)
    // Enable 4x/5x/96MHz PLL on PIC18F87J10, PIC18F97J60, PIC18F87J50, etc.
    OSCTUNE = 0x40;

    // Set up analog features of PORTA
    ADCON0 = 0x01;      // ADON, Channel 0, Vdd/Vss is +/-REF
    WDTCONbits.ADSHR = 1;
    ANCON0 = 0xFC;      // AN0 (POT) and AN1 (temp sensor) are anlog
    ANCON1 = 0xFF;
    WDTCONbits.ADSHR = 0;
    ADCON2 = 0xBE;      // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

    // Enable internal PORTB pull-ups
    INTCON2bits.RBPU = 0;

    // Configure USART
    TXSTA = 0x20;
    RCSTA = 0x90;

    // See if we can use the high baud rate setting
    #if ((GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1) <= 255
        SPBRG = (GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1;
        TXSTAbits.BRGH = 1;
    #else   // Use the low baud rate setting
        SPBRG = (GetPeripheralClock()+8*BAUD_RATE)/BAUD_RATE/16 - 1;
    #endif

    // Enable Interrupts
    RCONbits.IPEN = 1;      // Enable interrupt priorities
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    // Do a calibration A/D conversion
    ADCON1bits.ADCAL = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    ADCON1bits.ADCAL = 0;

#else   // 16-bit C30 and and 32-bit C32
    #if defined(__XC32)
    {
        // Enable multi-vectored interrupts
        INTEnableSystemMultiVectoredInt();

        // Enable optimal performance
        SYSTEMConfigPerformance(GetSystemClock());
        mOSCSetPBDIV(OSC_PB_DIV_1);             // Use 1:1 CPU Core:Peripheral clocks

        // Disable JTAG port so we get our I/O pins back, but first
        // wait 50ms so if you want to reprogram the part with
        // JTAG, you'll still have a tiny window before JTAG goes away.
        // The PIC32 Starter Kit debuggers use JTAG and therefore must not
        // disable JTAG.
        DelayMs(50);
        #if !defined(__MPLAB_DEBUGGER_PIC32MXSK) && !defined(__MPLAB_DEBUGGER_FS2)
            DDPCONbits.JTAGEN = 0;
        #endif
        LED_PUT(0x00);              // Turn the LEDs off

        CNPUESET = 0x00098000;      // Turn on weak pull ups on CN15, CN16, CN19 (RD5, RD7, RD13), which is connected to buttons on PIC32 Starter Kit boards
    }
    #endif

    #if defined(__PIC24F__)
        CLKDIVbits.RCDIV = 0;       // Set 1:1 8MHz FRC postscalar
    #endif

    // ADC
    AD1CHS = 0;                 // Input to AN0 (potentiometer)
    AD1PCFGbits.PCFG4 = 0;      // Disable digital input on AN4 (TC1047A temp sensor)
    #if defined(__32MX460F512L__) || defined(__32MX795F512L__)  // PIC32MX460F512L and PIC32MX795F512L PIMs has different pinout to accomodate USB module
        AD1PCFGbits.PCFG2 = 0;      // Disable digital input on AN2 (potentiometer)
    #else
        AD1PCFGbits.PCFG5 = 0;      // Disable digital input on AN5 (potentiometer)
    #endif

    // ADC
    AD1CON1 = 0x84E4;           // Turn on, auto sample start, auto-convert, 12 bit mode (on parts with a 12bit A/D)
    AD1CON2 = 0x0404;           // AVdd, AVss, int every 2 conversions, MUXA only, scan
    AD1CON3 = 0x1003;           // 16 Tad auto-sample, Tad = 3*Tcy
    #if defined(__32MX460F512L__) || defined(__32MX795F512L__)  // PIC32MX460F512L and PIC32MX795F512L PIMs has different pinout to accomodate USB module
        AD1CSSL = 1<<2;             // Scan pot
    #else
        AD1CSSL = 1<<5;             // Scan pot
    #endif

    // UART
    #if defined(STACK_USE_UART)
        UARTTX_TRIS = 0;
        UARTRX_TRIS = 1;
        UMODE = 0x8000;         // Set UARTEN.  Note: this must be done before setting UTXEN

        #if defined(__XC16)
            USTA = 0x0400;      // UTXEN set
            #define CLOSEST_UBRG_VALUE ((GetPeripheralClock()+8ul*BAUD_RATE)/16/BAUD_RATE-1)
            #define BAUD_ACTUAL (GetPeripheralClock()/16/(CLOSEST_UBRG_VALUE+1))
        #else   //defined(__XC32)
            USTA = 0x00001400;      // RXEN set, TXEN set
            #define CLOSEST_UBRG_VALUE ((GetPeripheralClock()+8ul*BAUD_RATE)/16/BAUD_RATE-1)
            #define BAUD_ACTUAL (GetPeripheralClock()/16/(CLOSEST_UBRG_VALUE+1))
        #endif

        #define BAUD_ERROR ((BAUD_ACTUAL > BAUD_RATE) ? BAUD_ACTUAL-BAUD_RATE : BAUD_RATE-BAUD_ACTUAL)
        #define BAUD_ERROR_PRECENT  ((BAUD_ERROR*100+BAUD_RATE/2)/BAUD_RATE)
        #if (BAUD_ERROR_PRECENT > 3)
            #warning UART frequency error is worse than 3%
        #elif (BAUD_ERROR_PRECENT > 2)
            #warning UART frequency error is worse than 2%
        #endif

        UBRG = CLOSEST_UBRG_VALUE;
    #endif

#endif

// Deassert all chip select lines so there isn't any problem with
// initialization order.  Ex: When ENC28J60 is on SPI2 with Explorer 16,
// MAX3232 ROUT2 pin will drive RF12/U2CTS ENC28J60 CS line asserted,
// preventing proper 25LC256 EEPROM operation.
#if defined(ENC_CS_TRIS)
    ENC_CS_IO = 1;
    ENC_CS_TRIS = 0;
#endif
#if defined(ENC100_CS_TRIS)
    ENC100_CS_IO = (ENC100_INTERFACE_MODE == 0);
    ENC100_CS_TRIS = 0;
#endif
#if defined(EEPROM_CS_TRIS)
    EEPROM_CS_IO = 1;
    EEPROM_CS_TRIS = 0;
#endif
#if defined(SPIRAM_CS_TRIS)
    SPIRAM_CS_IO = 1;
    SPIRAM_CS_TRIS = 0;
#endif
#if defined(SPIFLASH_CS_TRIS)
    SPIFLASH_CS_IO = 1;
    SPIFLASH_CS_TRIS = 0;
#endif
#if defined(WF_CS_TRIS)
    WF_CS_IO = 1;
    WF_CS_TRIS = 0;
#endif

#if defined(__PIC24FJ256GB110__)
    __builtin_write_OSCCONL(OSCCON & 0xBF);  // Unlock PPS

    // Configure SPI1 PPS pins (ENC28J60/ENCX24J600/MRF24W or other PICtail Plus cards)
    RPOR0bits.RP0R = 8;     // Assign RP0 to SCK1 (output)
    RPOR7bits.RP15R = 7;    // Assign RP15 to SDO1 (output)
    RPINR20bits.SDI1R = 23; // Assign RP23 to SDI1 (input)

    // Configure SPI2 PPS pins (25LC256 EEPROM on Explorer 16)
    RPOR10bits.RP21R = 11;  // Assign RG6/RP21 to SCK2 (output)
    RPOR9bits.RP19R = 10;   // Assign RG8/RP19 to SDO2 (output)
    RPINR22bits.SDI2R = 26; // Assign RG7/RP26 to SDI2 (input)

    // Configure UART2 PPS pins (MAX3232 on Explorer 16)
    #if !defined(ENC100_INTERFACE_MODE) || (ENC100_INTERFACE_MODE == 0) || defined(ENC100_PSP_USE_INDIRECT_RAM_ADDRESSING)
    RPINR19bits.U2RXR = 10; // Assign RF4/RP10 to U2RX (input)
    RPOR8bits.RP17R = 5;    // Assign RF5/RP17 to U2TX (output)
    #endif

    // Configure INT1 PPS pin (MRF24W Wi-Fi PICtail Plus interrupt signal when in SPI slot 1)
    RPINR0bits.INT1R = 33;  // Assign RE8/RPI33 to INT1 (input)

    // Configure INT3 PPS pin (MRF24W Wi-Fi PICtail Plus interrupt signal when in SPI slot 2)
    RPINR1bits.INT3R = 40;  // Assign RC3/RPI40 to INT3 (input)

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS
#endif

#if defined(SPIRAM_CS_TRIS)
    SPIRAMInit();
#endif
#if defined(EEPROM_CS_TRIS)
    XEEInit();
#endif
#if defined(SPIFLASH_CS_TRIS)
    SPIFlashInit();
#endif
}

/*********************************************************************
 * Function:        void InitAppConfig(void)
 *
 * PreCondition:    MPFSInit() is already called.
 *
 * Input:           None
 *
 * Output:          Write/Read non-volatile config variables.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
// MAC Address Serialization using a MPLAB PM3 Programmer and
// Serialized Quick Turn Programming (SQTP).
// The advantage of using SQTP for programming the MAC Address is it
// allows you to auto-increment the MAC address without recompiling
// the code for each unit.  To use SQTP, the MAC address must be fixed
// at a specific location in program memory.  Uncomment these two pragmas
// that locate the MAC address at 0x1FFF0.  Syntax below is for MPLAB C
// Compiler for PIC18 MCUs. Syntax will vary for other compilers.
//#pragma romdata MACROM=0x1FFF0
static ROM uint8_t SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
//#pragma romdata

static void InitAppConfig(void)
{
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    unsigned char vNeedToSaveDefaults = 0;
#endif

    while(1)
    {
        // Start out zeroing all AppConfig bytes to ensure all fields are
        // deterministic for checksum generation
        memset((void*)&AppConfig, 0x00, sizeof(AppConfig));

        #if defined ENABLE_STATIC_IP
            AppConfig.Flags.bIsDHCPEnabled = false;

            AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
            AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
            AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
            AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
            AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
            AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
            AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;
        #elif defined ENABLE_DHCP_IP
            AppConfig.Flags.bIsDHCPEnabled = true;

            AppConfig.MyIPAddr.Val = 0;
            AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
            AppConfig.MyMask.Val = 0;
            AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
            AppConfig.MyGateway.Val = 0;
            AppConfig.PrimaryDNSServer.Val = 0;
            AppConfig.SecondaryDNSServer.Val = 0;
        #endif

        AppConfig.Flags.bInConfigMode = true;

        #if defined MY_DEFAULT_MAC_ADDRESS
            // Use application MAC address
            AppConfig.MyMACAddr.v[0] = 0x00;
            AppConfig.MyMACAddr.v[1] = 0x1e;
            AppConfig.MyMACAddr.v[2] = 0xc0;
            AppConfig.MyMACAddr.v[3] = 0x11;
            AppConfig.MyMACAddr.v[4] = 0x22;
            AppConfig.MyMACAddr.v[5] = 0x33;
        #else
            // Use default MAC address of the module
            memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
    //      {
    //          _prog_addressT MACAddressAddress;
    //          MACAddressAddress.next = 0x157F8;
    //          _memcpy_p2d24((char*)&AppConfig.MyMACAddr, MACAddressAddress, sizeof(AppConfig.MyMACAddr));
    //      }
        #endif

//      AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
//      AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
//      AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
//      AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
//      AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
//      AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
//      AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);

        #if defined(WF_CS_TRIS)
            // Load the default SSID Name
            WF_ASSERT(sizeof(MY_DEFAULT_SSID_NAME)-1 <= sizeof(AppConfig.MySSID));
            memcpypgm2ram(AppConfig.MySSID, (ROM void*)MY_DEFAULT_SSID_NAME, sizeof(MY_DEFAULT_SSID_NAME));
            AppConfig.SsidLength = sizeof(MY_DEFAULT_SSID_NAME) - 1;

            AppConfig.SecurityMode = MY_DEFAULT_WIFI_SECURITY_MODE;

            #if (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_OPEN)
                memset(AppConfig.SecurityKey, 0x00, sizeof(AppConfig.SecurityKey));
                AppConfig.SecurityKeyLength = 0;

            #elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_40
                AppConfig.WepKeyIndex = 0; // This is the only WEP key index we currently support
                memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_WEP_KEYS_40, sizeof(MY_DEFAULT_WEP_KEYS_40) - 1);
                AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_WEP_KEYS_40) - 1;

            #elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_104
                AppConfig.WepKeyIndex = 0; // This is the only WEP key index we currently support
                memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_WEP_KEYS_104, sizeof(MY_DEFAULT_WEP_KEYS_104) - 1);
                AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_WEP_KEYS_104) - 1;

            #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_WITH_KEY)       || \
                  (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA2_WITH_KEY)      || \
                  (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_KEY)
                memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_PSK, sizeof(MY_DEFAULT_PSK) - 1);
                AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_PSK) - 1;

            #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_WITH_PASS_PHRASE)     || \
                  (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA2_WITH_PASS_PHRASE)    || \
                  (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
                memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_PSK_PHRASE, sizeof(MY_DEFAULT_PSK_PHRASE) - 1);
                AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_PSK_PHRASE) - 1;
            #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPS_PUSH_BUTTON)
                memset(AppConfig.SecurityKey, 0x00, sizeof(AppConfig.SecurityKey));
                AppConfig.SecurityKeyLength = 0;
            #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPS_PIN)
                memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_WPS_PIN, sizeof(MY_DEFAULT_WPS_PIN) - 1);
                AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_WPS_PIN) - 1;
            #else
                #error "No security defined"
            #endif /* MY_DEFAULT_WIFI_SECURITY_MODE */

        #endif

        // Compute the checksum of the AppConfig defaults as loaded from ROM
        wOriginalAppConfigChecksum = CalcIPChecksum((uint8_t*)&AppConfig, sizeof(AppConfig));

        #if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        {
            NVM_VALIDATION_STRUCT NVMValidationStruct;

            // Check to see if we have a flag set indicating that we need to
            // save the ROM default AppConfig values.
            if(vNeedToSaveDefaults)
                SaveAppConfig(&AppConfig);

            // Read the NVMValidation record and AppConfig struct out of EEPROM/Flash
            #if defined(EEPROM_CS_TRIS)
            {
                XEEReadArray(0x0000, (uint8_t*)&NVMValidationStruct, sizeof(NVMValidationStruct));
                XEEReadArray(sizeof(NVMValidationStruct), (uint8_t*)&AppConfig, sizeof(AppConfig));
            }
            #elif defined(SPIFLASH_CS_TRIS)
            {
                SPIFlashReadArray(0x0000, (uint8_t*)&NVMValidationStruct, sizeof(NVMValidationStruct));
                SPIFlashReadArray(sizeof(NVMValidationStruct), (uint8_t*)&AppConfig, sizeof(AppConfig));
            }
            #endif

            // Check EEPROM/Flash validitity.  If it isn't valid, set a flag so
            // that we will save the ROM default values on the next loop
            // iteration.
            if((NVMValidationStruct.wConfigurationLength != sizeof(AppConfig)) ||
               (NVMValidationStruct.wOriginalChecksum != wOriginalAppConfigChecksum) ||
               (NVMValidationStruct.wCurrentChecksum != CalcIPChecksum((uint8_t*)&AppConfig, sizeof(AppConfig))))
            {
                // Check to ensure that the vNeedToSaveDefaults flag is zero,
                // indicating that this is the first iteration through the do
                // loop.  If we have already saved the defaults once and the
                // EEPROM/Flash still doesn't pass the validity check, then it
                // means we aren't successfully reading or writing to the
                // EEPROM/Flash.  This means you have a hardware error and/or
                // SPI configuration error.
                if(vNeedToSaveDefaults)
                {
                    while(1);
                }

                // Set flag and restart loop to load ROM defaults and save them
                vNeedToSaveDefaults = 1;
                continue;
            }

            // If we get down here, it means the EEPROM/Flash has valid contents
            // and either matches the ROM defaults or previously matched and
            // was run-time reconfigured by the user.  In this case, we shall
            // use the contents loaded from EEPROM/Flash.
            break;
        }
        #endif
        break;
    }
}

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
void SaveAppConfig(const APP_CONFIG *ptrAppConfig)
{
    NVM_VALIDATION_STRUCT NVMValidationStruct;

    // Ensure adequate space has been reserved in non-volatile storage to
    // store the entire AppConfig structure.  If you get stuck in this while(1)
    // trap, it means you have a design time misconfiguration in tcpip_config.h.
    // You must increase MPFS_RESERVE_BLOCK to allocate more space.
    #if defined(STACK_USE_MPFS2)
        if(sizeof(NVMValidationStruct) + sizeof(AppConfig) > MPFS_RESERVE_BLOCK)
            while(1);
    #endif

    // Get proper values for the validation structure indicating that we can use
    // these EEPROM/Flash contents on future boot ups
    NVMValidationStruct.wOriginalChecksum = wOriginalAppConfigChecksum;
    NVMValidationStruct.wCurrentChecksum = CalcIPChecksum((uint8_t*)ptrAppConfig, sizeof(APP_CONFIG));
    NVMValidationStruct.wConfigurationLength = sizeof(APP_CONFIG);

    // Write the validation struct and current AppConfig contents to EEPROM/Flash
    #if defined(EEPROM_CS_TRIS)
        XEEBeginWrite(0x0000);
        XEEWriteArray((uint8_t*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        XEEWriteArray((uint8_t*)ptrAppConfig, sizeof(APP_CONFIG));
    #else
        SPIFlashBeginWrite(0x0000);
        SPIFlashWriteArray((uint8_t*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        SPIFlashWriteArray((uint8_t*)ptrAppConfig, sizeof(APP_CONFIG));
    #endif
}

#endif
