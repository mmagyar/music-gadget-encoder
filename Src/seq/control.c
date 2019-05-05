#include "control.h"
#include "../system/inputs.h"
#include "../util/midi/midi.h"
#include "../util/midi/midi_enums.h"

Control_encoder_config encoder_config[8] = {
        { CT_INCREMENT, 0, 16 /* maybe 80 */, 1, 65, { CT_TOGGLE, 0, 32 } },
        { CT_INCREMENT, 0, 17 /* maybe 81 */, 1, 65, { CT_TOGGLE, 0, 33 } },
        { CT_INCREMENT, 0, 18 /* maybe 82 */, 1, 65, { CT_TOGGLE, 0, 34 } },
        { CT_INCREMENT, 0, 19 /* maybe 83 */, 1, 65, { CT_TOGGLE, 0, 35 } },
        { CT_INCREMENT, 0, 20, 1, 65, { CT_TOGGLE, 0, 36 } },
        { CT_INCREMENT, 0, 21, 1, 65, { CT_TOGGLE, 0, 37 } },
        { CT_INCREMENT, 0, 22, 1, 65, { CT_TOGGLE, 0, 38 } },
        { CT_INCREMENT, 0, 23, 1, 65, { CT_TOGGLE, 0, 39 } },
};

Control_button_config buttons[6] = {
        { CT_PRESS, 0, 93 }, /* STOP */
        { CT_PRESS, 0, 94 }, /* PLAY */
        { CT_PRESS, 0, 8 }, /* SOLO 1 */
        { CT_PRESS, 0, 9 }, /* SOLO 2 */
        { CT_PRESS, 0, 10 }, /* SOLO 3 */
        { CT_PRESS, 0, 11 }, /* SOLO 4 */
};

void process_control() {
    //TODO LED control
    //TODO midi input
    loop(i,6)
    {
        if (button_pressed[i]) {
            Control_button_config * btn = &buttons[i];
            if (btn->type == CT_TOGGLE) {
                btn->button_state = btn->button_state ? 0 : 127;
                send_note_on((Midi_channel) btn->channel, btn->button_note, btn->button_state);
            } else {
                send_note_on((Midi_channel) btn->channel, btn->button_note, 127);
            }
        }
    }

    loop(x,4)
    {

        Control_encoder_config * encoder = &encoder_config[x];

        s16 * step = &encoders[x].encoder_step;
        if (encoder->type == CT_INCREMENT) {
            while (*step != 0) {
                if (*step > 0) {
                    *step -= 1;
                    send_cc((Midi_channel) encoder->channel, (Midi_cc_number) encoder->cc,
                            encoder->increment_value);
                } else {
                    *step += 1;
                    send_cc((Midi_channel) encoder->channel, (Midi_cc_number) encoder->cc,
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
            send_cc((Midi_channel) encoder->channel, (Midi_cc_number) encoder->cc,
                    encoder->data);
        }
    }

}

