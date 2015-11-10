#include "my_usb_cdc.h"

void interrupt SYS_InterruptHigh(void) {
    ISR();
    USBDeviceTasks();
}

void init_usb_cdc(void) {
    USBDeviceInit();
    USBDeviceAttach();
}

bool is_usb_available(void) {
    return !(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended() == true);
}

int put_string_usb(char *s) {
    if (!is_usb_available()) return 1;
    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    putrsUSBUSART(s);
    CDCTxService();
    return 0;
}

int get_string_usb(char *s, int len) {
    int rx_len;
    if (!is_usb_available()) return 0;
    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    rx_len = getsUSBUSART(s, len);
    CDCTxService();
    return rx_len;
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size) {
    switch ((int) event) {
        case EVENT_CONFIGURED:
            CDCInitEP();
            break;
        case EVENT_EP0_REQUEST:
            USBCheckCDCRequest();
            break;
    }
    return true;
}