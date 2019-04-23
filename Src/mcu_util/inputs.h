#ifndef MCU_UTIL_INPUTS_H_
#define MCU_UTIL_INPUTS_H_

#include "gpio.h"
#include "../util/safe_array.h"

#define ENCODER_COUNT 4
typedef struct {
    GPIO_TypeDef * port;
    u16 pin;
} Pins;

typedef struct {
    Pins a;
    Pins b;
    Pins s;
} Encoder_pins;

typedef struct {
    u32 max_data;
    u32 data_increment;
    u32 data;
    s16 encoder_step;
    u16 a;
    u16 b;
    u16 s;
    u8 button_presses;
    s8 direction;
    bool reset_encoder;
    bool reset_button;
} Encoder_data;

Encoder_data encoders[ENCODER_COUNT];
u8 button_pressed[6];

void process_encoder(Encoder_data * data);
/**
 * Read current encoder data into the least significant bit, and shift previous data right
 */
void read_encoder_inputs();
void mux_button_read();
#endif /* MCU_UTIL_INPUTS_H_ */
