#include "control.h"
#include "../system/inputs.h"
#include "../util/midi/midi.h"
#include "../util/midi/midi_enums.h"
#include "../system/led_update.h"
#include "../util/counter.h"
#include "../system/intercom.h"
#define MIDI_ON false
Control_encoder_config encoder_config[8] = {
        { CT_INCREMENT, 0, 16 /* maybe 80 */, 1, 65, { CT_TOGGLE, 0, 32, 0 }, 0 },
        { CT_INCREMENT, 0, 17 /* maybe 81 */, 1, 65, { CT_TOGGLE, 0, 33, 0 }, 0 },
        { CT_INCREMENT, 0, 18 /* maybe 82 */, 1, 65, { CT_TOGGLE, 0, 34, 0 }, 0 },
        { CT_INCREMENT, 0, 19 /* maybe 83 */, 1, 65, { CT_TOGGLE, 0, 35, 0 }, 0 },
        { CT_INCREMENT, 0, 20, 1, 65, { CT_TOGGLE, 0, 36, 0 }, 0 },
        { CT_INCREMENT, 0, 21, 1, 65, { CT_TOGGLE, 0, 37, 0 }, 0 },
        { CT_INCREMENT, 0, 22, 1, 65, { CT_TOGGLE, 0, 38, 0 }, 0 },
        { CT_INCREMENT, 0, 23, 1, 65, { CT_TOGGLE, 0, 39, 0 }, 0 },
};

Control_button_config buttons[6] = {
        { CT_PRESS, 0, 93, 0 }, /* STOP */
        { CT_PRESS, 0, 94, 0 }, /* PLAY */
        { CT_PRESS, 0, 8, 0 }, /* SOLO 1 */
        { CT_PRESS, 0, 9, 0 }, /* SOLO 2 */
        { CT_PRESS, 0, 10, 0 }, /* SOLO 3 */
        { CT_PRESS, 0, 11, 0 }, /* SOLO 4 */
};

Counter encs[4] = {
        { 31, OFB_SATURATE, 0 }, { 31, OFB_SATURATE, 0 },
        { 31, OFB_SATURATE, 0 }, { 31, OFB_SATURATE, 0 } };
bool btns[6] = { 0 };

void led_update() {
    loop(x,4)
    {
        u8 data = encs[x].data * 8;
        led_calculate_bar_16(data ? data + 6 : 0, display.encoders[x].red_precise);
    }

    loop(x,4)
    {
        led_calculate_bar_16(buttons[x].button_state * 2, display.encoders[x].green_precise);
    }

    loop(x,2)
    {
        led_calculate_bar_16(buttons[x + 4].button_state * 2, display.top_bar_precise);
    }
}

void process_control() {
    //TODO LED control
    //TODO midi input
    loop(i,6)
    {
        if (button_pressed[i]) {
            button_pressed[i]--;
            Control_button_config * btn = &buttons[i];
            if (btn->type == CT_TOGGLE) {
                btn->button_state = btn->button_state ? 0 : 127;
                if (MIDI_ON) send_note_on((Midi_channel) btn->channel, btn->button_note,
                        btn->button_state);

            } else {
                btn->button_state = btn->button_state ? 0 : 127;
                if (MIDI_ON) send_note_on((Midi_channel) btn->channel, btn->button_note, 127);
            }
            Button_press bp = { i };
            icom_send_button_press(&bp);
        }
    }

    loop(x,4)
    {

        Control_encoder_config * encoder = &encoder_config[x];

        s16 * step = &encoders[x].encoder_step;
        bool changed = *step ? true : false;
        while(encoders[x].button_presses){
            encoders[x].button_presses--;
            icom_send_broadcast_request();
        }
        if (encoder->type == CT_INCREMENT) {
            while (*step != 0) {
                if (*step > 0) {
                    *step -= 1;
                    if (MIDI_ON) send_cc((Midi_channel) encoder->channel,
                            (Midi_cc_number) encoder->cc,
                            encoder->increment_value);
                    counter_inc(&encs[x]);

                } else {
                    *step += 1;
                    counter_dec(&encs[x]);
                    if (MIDI_ON) send_cc((Midi_channel) encoder->channel,
                            (Midi_cc_number) encoder->cc,
                            encoder->decrement_value);
                }
            }

        } else if (encoder->type == CT_VALUE) {
            while (*step != 0) {
                if (*step > 0) {
                    *step -= 1;
                    if (encoder->data <= 127) encoder->data++;
                } else {
                    *step += 1;
                    if (encoder->data) encoder->data--;
                }

            }
            counter_set(encoder->data, &encs[x]);
            if (MIDI_ON) send_cc((Midi_channel) encoder->channel, (Midi_cc_number) encoder->cc,
                    encoder->data);
        }

        if (changed) {
            Control_change ch = { x, encs[x].data };
            icom_send_control_change(&ch);
        }
    }

    led_update();
}

