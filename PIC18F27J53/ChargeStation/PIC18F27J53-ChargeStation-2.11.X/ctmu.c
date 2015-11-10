#include "ctmu.h"

#include <My_PIC.h>
#include "ChargeStation_task.h"
#include "io.h"

button_t ctmu_m;
uint16_t ctmu_value_m;
uint8_t ctmu_ratio;
uint8_t ctmu_sampling_flag;

uint8_t cut_time_flag;

void ctmu_set_ratio(uint8_t percentage) {
    port[0].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU0) / 100;
    port[1].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU1) / 100;
    port[2].ctmu_value = (uint16_t) percentage * CTMU_read(CTMU2) / 100;
    ctmu_value_m = (uint16_t) percentage * CTMU_read(CTMUM) / 100;
}
// タッチセンサのサンプリング

void ctmu_sampling(void) {
    button_timer_interrupt(&port[0].ctmu, !(CTMU_read(CTMU0) / port[0].ctmu_value));
    button_timer_interrupt(&port[1].ctmu, !(CTMU_read(CTMU1) / port[1].ctmu_value));
    button_timer_interrupt(&port[2].ctmu, !(CTMU_read(CTMU2) / port[2].ctmu_value));
    button_timer_interrupt(&ctmu_m, !(CTMU_read(CTMUM) / ctmu_value_m));
}

void ctmu_task(void) {
    if (ctmu_sampling_flag) {
        ctmu_sampling_flag = 0;
        ctmu_sampling();
    }
}
