#include "My_usb_cdc.h"

// ringbuffer of usb tx/rx
ringbuf_t usb_tx;
ringbuf_t usb_rx;

void USB_ISR(void) {
    USBDeviceTasks();
}

void USB_init(void) {
    USBDeviceInit();
    USBDeviceAttach();
    CDCSetBaudRate(115200);
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
    static int delay_count;
    USBResumeControl = 1; // Start RESUME signaling    
    delay_count = 1800U; // Set RESUME line for 1-13 ms
    do {
        delay_count--;
    } while (delay_count);
    USBResumeControl = 0;
}

void USB_loop(void) {
    char data;
    int rx_len;
    rx_len = get_string_usb(&data, 1);
    if (rx_len) {
        ringbuf_put(&usb_rx, data);
    }
    if (ringbuf_num(&usb_tx)) {
        data = ringbuf_pop(&usb_tx);
        put_string_usb(&data, 1);
    }
}
