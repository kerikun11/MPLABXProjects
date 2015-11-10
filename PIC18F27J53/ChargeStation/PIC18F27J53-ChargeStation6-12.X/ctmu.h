/* 
 * File:   ctmu.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 9:16
 */

#ifndef CTMU_H
#define	CTMU_H

#include <xc.h>
#include <stdint.h>
#include <My_button.h>

extern button_t ctmu_m;
extern uint16_t ctmu_value_m;
extern uint8_t ctmu_ratio;
extern uint8_t ctmu_sampling_flag;

extern uint8_t cut_time_flag;

void ctmu_set_ratio(uint8_t percentage);
// タッチセンサのサンプリング
void ctmu_sampling(void);
void ctmu_loop(void);
#endif	/* CTMU_H */

