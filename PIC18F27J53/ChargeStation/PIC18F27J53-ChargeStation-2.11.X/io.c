#include "io.h"

#include "ChargeStation_task.h"

// Power Output

void OUT(uint8_t b, uint8_t value) {
    port[b].flag.out_flag = value;
    switch (b) {
        case PORT_L:
            OUT0 = value;
            break;
        case PORT_C:
            OUT1 = value;
            break;
        case PORT_R:
            OUT2 = value;
            break;
    }
}
// return analog pin number

uint8_t ANALOG_IN(uint8_t b) {
    switch (b) {
        case PORT_L:
            return ADC0;
        case PORT_C:
            return ADC1;
        case PORT_R:
            return ADC2;
    }
    return 0;
}
// LED Output

void LED_output(uint8_t b, uint8_t value) {
    port[b].flag.led_flag = value;
    switch (b) {
        case PORT_L:
            LED0 = value;
            break;
        case PORT_C:
            LED1 = value;
            break;
        case PORT_R:
            LED2 = value;
            break;
    }
}
