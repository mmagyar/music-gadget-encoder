#include "../system/inputs.h"

#include "../system/mux.h"
const Encoder_pins encoder_pins[ENCODER_COUNT] = {
        {
                { ENC_A_0_GPIO_Port, ENC_A_0_Pin },
                { ENC_B_0_GPIO_Port, ENC_B_0_Pin },
                { ENC_S_0_GPIO_Port, ENC_S_0_Pin }
        },
        {
                { ENC_A_1_GPIO_Port, ENC_A_1_Pin },
                { ENC_B_1_GPIO_Port, ENC_B_1_Pin },
                { ENC_S_1_GPIO_Port, ENC_S_1_Pin }
        },
        {
                { ENC_A_2_GPIO_Port, ENC_A_2_Pin },
                { ENC_B_2_GPIO_Port, ENC_B_2_Pin },
                { ENC_S_2_GPIO_Port, ENC_S_2_Pin }
        },
        {
                { ENC_A_3_GPIO_Port, ENC_A_3_Pin },
                { ENC_B_3_GPIO_Port, ENC_B_3_Pin },
                { ENC_S_3_GPIO_Port, ENC_S_3_Pin }
        }
};

Encoder_data encoders[ENCODER_COUNT] = {
        { 0xFF, 4, 0x00, 0, 0, 0, 0 , 0, 0, 0, 0 },
        { 0xFF, 2, 0x00, 0, 0, 0, 0 , 0, 0, 0, 0  },
        { 0xFF, 4, 0x00, 0, 0, 0, 0 , 0, 0, 0, 0  },
        { 0xFF, 4, 0x00, 0, 0, 0, 0 , 0, 0, 0, 0  } };

inline void process_encoder_button(Encoder_data * encoder) {
    if (encoder->reset_button) {
        if (encoder->s) {
            encoder->reset_button = false;
            encoder->button_presses++;
        }
    } else if (!encoder->s) {
        encoder->reset_button = true;
    }
}
inline void process_encoder(Encoder_data * encoder) {
    /* reset means that we are ready to receive a new input */
    if (encoder->reset_encoder) {
        /* Decode gray code */
        /* A before B means increment, this needs to be first for PEC12R-4225F-S0024 encoder */
        if (encoder->a && encoder->direction == 0) {
            encoder->direction = 1;
            encoder->encoder_step++;
        } else
        /*B before A means decrement */
        if (encoder->b && encoder->direction == 0) {
            encoder->direction = -1;
            encoder->encoder_step--;
        }

        /* When both values are high, it means that we completed an input */
        if (encoder->direction) {
            if (encoder->direction == 1) {

                encoder->data += encoder->data_increment;
                if (encoder->data > encoder->max_data) {
                    encoder->data = encoder->max_data;
                }
            } else {
                if (encoder->data >= encoder->data_increment) {
                    encoder->data -= encoder->data_increment;
                } else {
                    encoder->data = 0;
                }

            }
            encoder->direction = 0;
            encoder->reset_encoder = false;
        }
    } else {
        //When both of them are off, we are ready to receive the next input
        if (!encoder->a && !encoder->b) {
            encoder->reset_encoder = true;
        }
    }

    process_encoder_button(encoder);
}

/**
 * Read current encoder data into the least significant bit, and shift previous data right
 */
inline void read_encoder_inputs() {
    loop (i, ENCODER_COUNT)
    {

        encoders[i].a = (encoders[i].a << 1)
                | !(encoder_pins[i].a.port->IDR & encoder_pins[i].a.pin);
        encoders[i].b = (encoders[i].b << 1)
                | !(encoder_pins[i].b.port->IDR & encoder_pins[i].b.pin);
        encoders[i].s = (encoders[i].s << 1)
                | !(encoder_pins[i].s.port->IDR & encoder_pins[i].s.pin);

//        encoders[i].a = (encoders[i].a << 1)
//                | !HAL_GPIO_ReadPin(encoder_pins[i].a.port,
//                        encoder_pins[i].a.pin);
//        encoders[i].b = (encoders[i].b << 1)
//                | !HAL_GPIO_ReadPin(encoder_pins[i].b.port,
//                        encoder_pins[i].b.pin);
//        encoders[i].s = (encoders[i].s << 1)
//                | !HAL_GPIO_ReadPin(encoder_pins[i].s.port,
//                        encoder_pins[i].s.pin);

        process_encoder(&encoders[i]);
    }

}
u8 button_pressed[6] = { 0 };
u8 muxed_button[6] = { 0 };
bool muxed_button_ready[6] = { 0 };

inline void mux_button_read() {
    volatile u16 read = LL_GPIO_ReadInputPort(BUTTONS_GPIO_Port);
    volatile u16 binary = read & BUTTONS_Pin;
    bool input = !(binary);

    if (current_mux > 3) {
        u8 c = (6 - (current_mux - 3));
        if (c > 5) {

            return;
        }
        muxed_button[c] = (muxed_button[c] << 1) | input;
        //If don't have anything in the register, we are ready for a new button press
        if (!muxed_button[c]) muxed_button_ready[c] = true;
        //If something is in the register (previous evaluated to false) and we are ready for a button press, increment the press counter
        else if (muxed_button_ready[c]) {
            muxed_button_ready[c] = false;
            button_pressed[c]++;

        }
    }
}
