#include "My_usb_cdc.h"

void USB_ISR(void) {
    USBDeviceTasks();
}

void USB_init(void) {
    USBDeviceInit();
    USBDeviceAttach();
}

bool is_usb_available(void) {
    return !(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended() == true);
}

int put_string_usb(char *s, int len) {
    if (!is_usb_available()) {
        //USBCBSendResume();
        return 1;
    }
    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    putUSBUSART(s, len);
    CDCTxService();
    return 0;
}

int get_string_usb(char *s, int len) {
    int rx_len;
    if (!is_usb_available()) {
        //USBCBSendResume();
        return 0;
    }
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

void USBCBSendResume(void) {
    static WORD delay_count;
    USBResumeControl = 1; // Start RESUME signaling    
    delay_count = 1800U; // Set RESUME line for 1-13 ms
    do {
        delay_count--;
    } while (delay_count);
    USBResumeControl = 0;
}
