/* 
 * File:   My_usb_cdc.h
 * Author: @Ryokeri14
 *
 * <Nessesary files>
 * 1. "usb" directory and inside files
 * 2. rinbuffer library "My_ringbuf.h" and "My_ringbuf.c"
 * 
 * <Name of variables>
 * 1. usb_tx is a structure of tx data's ringbuffer
 * 2. usb_rx is a structure of rx data's ringbuffer
 * 
 * <How to use USB cdc>
 * 1. Call USB_init(); in the first of main function.
 * 2. Initialize ringbuffers, usb_tx and usb_rx, like this. 
 *      static char tx_buf[SIZE_OF_TX_BUFFER_YOU_NEED];
 *      ringbuf_init(&usb_tx,tx_buf, SIXE_OF_TX_BUFFER_YOU_NEED);
 *      static char rx_buf[SIZE_OF_RX_BUFFER_YOU_NEED];
 *      ringbuf_init(&usb_rx, rx_buf, SIXE_OF_RX_BUFFER_YOU_NEED);
 * 3. Call USB_task(); int the main loop.
 * 4. When you send some data, put data to ringbuffer like this;
 *      ringbuf_put(&usb_tx, data);
 * 5. When you gat data recieved, pop the data from ringbuffer like this:
 *      data = ringbuf_pop(&usb_rx);
 * 6. The data will be sent and received automatically.
 */

#ifndef MY_USB_CDC_H
#define	MY_USB_CDC_H

#include "usb/usb.h"
#include "usb/usb_device.h"
#include "usb/usb_device_cdc.h"
#include "My_ringbuf.h"

/* variables */

// ringbuffer of usb tx/rx
extern ringbuf_t usb_tx;
extern ringbuf_t usb_rx;


/* User Functions */

// Handle USB interrupt
void USB_ISR(void);
// Initialize USB
void USB_init(void);
// Send data or Recieve data
void USB_task(void);


/* Nessesary Functions */

void usb_char_send(char c);
uint8_t usb_char_get(char *c);
void USBCBSendResume(void);

#endif	/* MY_USB_CDC_H */
