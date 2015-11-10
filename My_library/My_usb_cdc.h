/* 
 * File:   My_usb_cdc.h
 * Author: kerikun11
 *
 * Created on 2015/06/07, 21:38
 */

#ifndef MY_USB_CDC_H
#define	MY_USB_CDC_H

#include <usb/usb.h>
#include <usb/usb_device.h>
#include <usb/usb_device_cdc.h>
#include <My_ringbuf.h>

// ringbuffer of usb tx/rx
extern ringbuf_t usb_tx;
extern ringbuf_t usb_rx;

void USB_ISR(void);
void USB_init(void);
int put_string_usb(char *s, int len);
int get_string_usb(char *s, int len);
void USBCBSendResume(void);
void USB_task(void);

#endif	/* MY_USB_CDC_H */
