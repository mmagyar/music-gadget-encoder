/*
 * mux.h
 *
 *  Created on: Apr 14, 2019
 *      Author: coder
 */

#ifndef MUX_H_
#define MUX_H_
#include "../util/types.h"
#include "../util/safe_array.h"
#include "inputs.h"

volatile u32 cpu_cycles;
volatile u32 percentage;
extern const GPIO_TypeDef * mux_port[10];
extern const u16 mux_pin[10];
u8 current_mux;



void mux_off();



typedef enum TS {
    TRANSFER_WAIT, TRANSFER_COMPLETE, TRANSFER_ERROR
} TS;



#endif /* MUX_H_ */
