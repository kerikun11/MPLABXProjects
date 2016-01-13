/* 
 * File:   My_I2C.h
 * Author: kerikun11
 *
 * Created on 2015/02/26, 19:52
 */

#ifndef MY_I2C_H
#define	MY_I2C_H

#include <xc.h>
#include <stdint.h>

#define ACK   0
#define NOACK 1
#define W_0  0
#define R_1  1

extern uint8_t I2C_sent_flag;
extern uint8_t I2C_cfct_flag;
extern uint8_t I2C_busy;

uint8_t I2C_idle_check(uint8_t mask);
void I2C_start(void);
void I2C_restart(void);
void I2C_stop(void);
void I2C_send(uint8_t data);
uint8_t I2C_ack(void);
void I2C_init_new(void);
void I2C_ISR(void);

//*************************** old functions ***************************//
#define I2C_OLD_FUNCTIONS 1

#if I2C_OLD_FUNCTIONS
void I2C_IdleCheck(char mask);
void I2C_init_old(void);
uint8_t I2C_Start(uint8_t adrs, uint8_t rw);
uint8_t I2C_rStart(int adrs, int rw);
void I2C_Stop(void);
uint8_t I2C_Send(uint8_t data);
uint8_t I2C_Receive(uint8_t ack);
#endif

#endif	/* MY_I2C_H */
