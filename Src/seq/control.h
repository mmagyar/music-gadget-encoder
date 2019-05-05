#ifndef SEQ_CONTROL_H_
#define SEQ_CONTROL_H_
#include "../util/types.h"

typedef enum {
    CT_VALUE,
    CT_INCREMENT
} Control_encoder_type;

typedef enum {
    CT_TOGGLE,
    CT_PRESS
} Control_button_type;


typedef struct Control_button_config {
    Control_button_type type;
    u8 channel;
    u8 button_note;
    u8 button_state;
} Control_button_config;


typedef struct Control_config {
    Control_encoder_type type;
    u8 channel;
    u8 cc;
    u8 increment_value;
    u8 decrement_value;
    Control_button_config button_config;

    u8 data;
} Control_encoder_config;

Control_encoder_config encoder_config[8];
Control_button_config buttons[6];

void process_control();
#endif /* SEQ_CONTROL_H_ */
