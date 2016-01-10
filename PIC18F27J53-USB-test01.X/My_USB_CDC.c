#include "My_USB_CDC.h"

void USB_CDC_init(void) {
    USBDeviceInit();
    USBDeviceAttach();
}

void USB_CDC_task(void) {
#if defined(USB_POLLING)
    // Interrupt or polling method.  If using polling, must call
    // this function periodically.  This function will take care
    // of processing and responding to SETUP transactions
    // (such as during the enumeration process when you first
    // plug in).  USB hosts require that USB devices should accept
    // and process SETUP packets in a timely fashion.  Therefore,
    // when using polling, this function should be called
    // regularly (such as once every 1.8ms or faster** [see
    // inline code comments in usb_device.c for explanation when
    // "or faster" applies])  In most cases, the USBDeviceTasks()
    // function does not take very long to execute (ex: <100
    // instruction cycles) before it returns.
    USBDeviceTasks();
#endif


    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        /* Jump back to the top of the while loop. */
        continue;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if (USBIsDeviceSuspended() == true) {
        /* Jump back to the top of the while loop. */
        continue;
    }

    //Application specific tasks
    /* Make sure that the CDC driver is ready for a transmission.
     */
    //    if (mUSBUSARTIsTxTrfReady() == true) {
    //        putrsUSBUSART("test\n");
    //    }
    /* Check to see if there is a transmission in progress, if there isn't, then
     * we can see about performing an echo response to data received.
     */
    if (USBUSARTIsTxTrfReady() == true) {
        uint8_t i;
        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof (readBuffer));

        /* For every byte that was read... */
        for (i = 0; i < numBytesRead; i++) {
            switch (readBuffer[i]) {
                    /* If we receive new line or line feed commands, just echo
                     * them direct.
                     */
                case 0x0A:
                case 0x0D:
                    writeBuffer[i] = readBuffer[i];
                    break;

                    /* If we receive something else, then echo it plus one
                     * so that if we receive 'a', we echo 'b' so that the
                     * user knows that it isn't the echo enabled on their
                     * terminal program.
                     */
                default:
                    writeBuffer[i] = readBuffer[i] + 1;
                    break;
            }
        }

        if (numBytesRead > 0) {
            /* After processing all of the received data, we need to send out
             * the "echo" data now.
             */
            putUSBUSART(writeBuffer, numBytesRead);
        }
    }

    CDCTxService();
}

void APP_DeviceCDCBasicDemoInitialize() {
    CDCInitEP();

    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 9600;
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size) {
    switch ((int) event) {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            //APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            //APP_LEDUpdateUSBStatus();
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            //APP_LEDUpdateUSBStatus();
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the 
             * demo code. */
            APP_DeviceCDCBasicDemoInitialize();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}
