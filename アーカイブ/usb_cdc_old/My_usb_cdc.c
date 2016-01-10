#include "My_usb_cdc.h"

// ringbuffer of usb tx/rx
ringbuf_t usb_tx;
ringbuf_t usb_rx;

void USB_ISR(void) {
}

void USB_init(void) {
    USBDeviceInit();
    USBDeviceAttach();
    CDCSetBaudRate(115200);
}

bool is_usb_available(void) {
    return !(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended() == true);
}

void usb_char_send(char c) {
    if (!is_usb_available()) {
        //USBCBSendResume();
        return;
    }
    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    putUSBUSART(&c, 1);
    CDCTxService();
}

uint8_t usb_char_get(char *c) {
    if (!is_usb_available()) {
        //USBCBSendResume();
        return 0;
    }
    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    uint8_t ans;
    ans = getsUSBUSART(c, 1);
    CDCTxService();
    return ans;
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

void USB_task(void) {
    char data;
    // rx operation
    while (usb_char_get(&data)) {
        ringbuf_put(&usb_rx, data);
    }
    // tx operation
    while (ringbuf_num(&usb_tx)) {
        data = ringbuf_pop(&usb_tx);
        usb_char_send(data);
    }
    USBDeviceTasks();
}
