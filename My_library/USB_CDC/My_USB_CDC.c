#include "My_USB_CDC.h"

/** INCLUDES *******************************************************/
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <usb/usb.h>
#include "usb_config.h"

/** VARIABLES ******************************************************/
ringbuf_t usb_rx;
ringbuf_t usb_tx;
static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

void USB_CDC_init(void) {
    USBDeviceInit();
    USBDeviceAttach();
    USB_CDC_buffer_init();
}

static void USB_CDC_buffer_init(void) {
    static uint8_t rxbuf[USB_RX_BUFFER_SIZE];
    ringbuf_init(&usb_rx, rxbuf, sizeof (rxbuf));
    static uint8_t txbuf[USB_TX_BUFFER_SIZE];
    ringbuf_init(&usb_tx, txbuf, sizeof (txbuf));
}

void USB_CDC_ISR(void) {
#if defined(USB_INTERRUPT)
    USBDeviceTasks();
#endif
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
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if (USBIsDeviceSuspended() == true) {
        /* Jump back to the top of the while loop. */
        return;
    }

    // Tx task
    uint16_t length = 0;
    while (ringbuf_num(&usb_tx)) {
        writeBuffer[length++] = ringbuf_pop(&usb_tx);
        if (length >= CDC_DATA_IN_EP_SIZE) {
            break;
        }
    }
    if (length) {
        USB_CDC_send(length);
    }
    // Rx task
    length = USB_CDC_get();
    if (length) {
        for (uint16_t i = 0; i < length; i++) {
            ringbuf_put(&usb_rx, readBuffer[i]);
        }
    }
}

static void USB_CDC_send(uint16_t length) {
    if (mUSBUSARTIsTxTrfReady() == true) {
        putUSBUSART(writeBuffer, length);
    }
    CDCTxService();
}

static uint8_t USB_CDC_get(void) {
    uint8_t numBytesRead;
    if (USBUSARTIsTxTrfReady() == true) {
        numBytesRead = getsUSBUSART(readBuffer, sizeof (readBuffer));
    }
    CDCTxService();
    return numBytesRead;
}

static void APP_DeviceCDCBasicDemoInitialize() {
    CDCInitEP();

    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 115200;
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
