/* 
 * File:   my_usb_cdc.h
 * Author: kerikun11
 *
 * Created on 2015/06/07, 21:38
 */

#ifndef MY_USB_CDC_H
#define	MY_USB_CDC_H

#include <usb/usb.h>
#include <usb/usb_device.h>
#include <usb/usb_device_cdc.h>

void init_usb_cdc(void);
int put_string_usb(char *s);
int get_string_usb(char *s, int len);

#endif	/* MY_USB_CDC_H */

