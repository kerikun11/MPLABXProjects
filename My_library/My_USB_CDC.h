/*******************************************************************
 * Microchip PIC, USB-CDC Library
 * Author:  @Ryokeri14
 * Date:    2016.01.10
 *******************************************************************/
#ifndef MY_USB_CDC_H
#define MY_USB_CDC_H

/** INCLUDES *******************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <My_ringbuf.h>

#include "usb/usb_config.h"

#include <usb/usb.h>
#include <usb/usb_device.h>
#include <usb/usb_device_cdc.h>

/** VALUES *********************************************************/
#define USB_TX_BUFFER_SIZE 1000
#define USB_RX_BUFFER_SIZE 100

/** VARIABLES ******************************************************/
extern ringbuf_t usb_rx;
extern ringbuf_t usb_tx;

/** USER FUNCTIONS *************************************************/
void USB_CDC_init(void);
void USB_CDC_ISR(void);
void USB_CDC_task(void);

/** FUNCTIONS ******************************************************/
static void USB_CDC_buffer_init(void);
static void USB_CDC_send(uint16_t length);
static uint8_t USB_CDC_get(void);

static void APP_DeviceCDCBasicDemoInitialize();
bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size);

#endif
