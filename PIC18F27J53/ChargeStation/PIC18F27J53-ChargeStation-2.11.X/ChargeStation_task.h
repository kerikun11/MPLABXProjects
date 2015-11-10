/* 
 * File:   ChargeStation_task.h
 * Author: kerikun11
 *
 * Created on 2015/09/17, 9:38
 */

#ifndef CHARGESTATION_TASK_H
#define	CHARGESTATION_TASK_H

#include <xc.h>
#include <stdint.h>
#include <My_button.h>
#include <My_ringbuf.h>
#include "io.h"

typedef struct {
    button_t ctmu;
    uint16_t ctmu_value;
    uint16_t current;
    uint32_t integrated_current_sec;
    uint32_t integrated_current;
    uint32_t integrated_time;
    uint16_t cut_cnt;

    union {
        uint8_t flags;

        struct {
            uint8_t auto_cut_ON : 1;
            uint8_t led_indicator_ON : 1;
            uint8_t out_flag : 1;
            uint8_t led_flag : 1;
        } flag;
    };
} port_t;

extern port_t port[NUM_PORT];
extern uint8_t terminal_data_out;
extern uint8_t terminal_data_out_flag;


// 充電中に充電電流に応じて各ポートのLEDを点滅させる
void LED_indicator(void);
// Auto cut each port
void Auto_cut(void);
// integrate currents of each port
void integrate_current(void);
void integrate_time(void);
void port_button_loop(void);
void normal_loop(void);
void sleep_loop(void);
void bootload(void);
void terminal_operation(ringbuf_t *tx, char *op0, char *op1, char *op2, char *op3);
void data_out(ringbuf_t *tx);

#endif	/* CHARGESTATION_TASK_H */
