#include "seq.h"
#include "../util/safe_array.h"
#include "../mcu_util/led_update.h"
#include "../mcu_util/inputs.h"
#include "stdint.h"
#include "arm_math.h"

Seq seq = {
        {
                7,
                OFB_WRAP_AROUND
        },
        { 31 },
        { SEQ_LEVELS - 1 },
        true,
        120
};

#define max_parts 8

u16 bpm_to_4th_ms(u8 bpm) {
    return 60000 / bpm;
}

inline void seq_next_part() {
    counter_inc(&seq.cursor);
}

inline void seq_prev_part() {
    counter_dec(&seq.cursor);
}

inline void seq_next_level() {
    counter_inc(&seq.current_level);
}

inline void seq_prev_level() {
    counter_dec(&seq.current_level);
}

void animate_top_bar() {
    if (anim.need_run) {
        u32 current_time = (u32) seq.current_ms & 0xFFFFFFFF;
        if (!anim.start_time) {
            anim.start_time = current_time;
        }
        u32 run_time = current_time - anim.start_time;
        u16 speed = anim.speed * 10;
        u16 current_frame = run_time / speed;
        bool show = true;

        switch (anim.anim) {
        case SEQ_ANIM_SHOW_NUM:
            loop(x,32)
            {
                display.top_bar_precise[x] = x >> 2 == anim.data ? IN_HIGH : IN_OFF;
            }
            break;
        case SEQ_ANIM_FLASH_NUM:
            if (current_frame % 2) show = false;
            loop(x, 32)
            {
                display.top_bar_precise[x] =
                        x >> 2 == anim.data && show && (anim.light_pattern & (1 << (x % 4))) ?
                                IN_HIGH : IN_OFF;
            }
            break;
        }

        if (anim.start_time + (anim.length * 10) <= current_time) {
            anim.start_time = 0;
            anim.need_run = false;
        }

    }
}

void update_seq_position() {
    if (seq.current_ms < seq.start_ms) {
        printf("Invalid sequencer status, current behind start ms, resetting start to current\r\n");
        seq.start_ms = seq.current_ms;
    }
    u16 sixteenth = bpm_to_4th_ms(seq.bpm) / 4;
    u32 playback_ms = seq.current_ms - seq.start_ms;
    u16 current_pos = playback_ms / sixteenth;
    if (current_pos >= 32) {

        seq.start_ms += sixteenth * 32;
        update_seq_position();
    } else {
        counter_set(current_pos, &seq.position);
    }
}
void update_seq() {

    if (seq.playing) {
        update_seq_position();
    }
    //TODO indicate part change
    if (button_pressed[5]) {
        button_pressed[5]--;
        seq_next_part();
        animate_flash(seq.cursor.data, &anim, false);
    }

    if (button_pressed[2]) {
        button_pressed[2]--;
        seq_prev_part();
        animate_flash(seq.cursor.data, &anim, false);
    }

    if (button_pressed[3]) {
        button_pressed[3]--;
        seq_prev_level();
        animate_flash(seq.current_level.data, &anim, true);
    }

    if (button_pressed[4]) {
        button_pressed[4]--;
        seq_next_level();
        animate_flash(seq.current_level.data, &anim, true);
    }

    loop(x,4)
    {
        s16 * step = &encoders[x].encoder_step;

        if (!encoders[x].s) {
            s16 increment = 64;
            u8 * velo = &seq.points[seq.current_level.data][x + (seq.cursor.data * 4)].velocity;
            while (*step) {
                if (*step > 0) {
                    if (((u32) (*velo)) + increment > 0xFF) *velo = UINT8_MAX;
                    else *velo += increment;
                    *step -= 1;
                } else {
                    if (((s32) (*velo)) - increment < 0) *velo = 0x00;
                    else *velo -= increment;
                    *step += 1;
                }
            }
        } else {
            s8 * pitch = &seq.points[seq.current_level.data][x + (seq.cursor.data * 4)].pitch;
            s16 increment = 16;
            while (*step) {
                if (*step > 0) {
                    if (((s32) (*pitch)) + increment > INT8_MAX) *pitch = INT8_MAX;
                    else *pitch += increment;
                    *step -= 1;
                } else {
                    if (((s32) (*pitch)) - increment < INT8_MIN) *pitch = INT8_MIN;
                    else *pitch -= increment;
                    *step += 1;
                }
            }
            //Close enough to zero to be considered 0;
            if (*pitch < 0 + (increment / 2) && *pitch > 0 - (increment / 2)) {
                *pitch = 0;
            }
        }
    }

    loop(x, 32)
    {
        Intensity intensity = IN_OFF;
        u8 vel = seq.points[seq.current_level.data][x].velocity;
        if (vel) {
            if (vel < 64) {
                intensity = IN_LOW;
            } else if (vel < 128) {
                intensity = IN_LOW_MED;
            } else if (vel < 192) {
                intensity = IN_HIGH_MED;
            } else {
                intensity = IN_HIGH;
            }
        }

        display.top_bar_precise[x] = intensity;

        if (seq.playing) {
            if (seq.position.data == x) {
                if (display.top_bar_precise[x] != IN_LOW) {
                    display.top_bar_precise[x] = IN_LOW;
                } else {
                    display.top_bar_precise[x] = IN_HIGH_MED;
                }
            }
        }
    }

    loop(x,4)
    {
        Seq_event * seq_event = &seq.points[seq.current_level.data][x + (seq.cursor.data * 4)];
        led_calculate_bar_16(seq_event->velocity, display.encoders[x].red_precise);
        led_calculate_bar_signed_16(seq_event->pitch, display.encoders[x].green_precise);
        loop(y,16)
        {

        }
    }

    animate_top_bar();
}

void animate_flash(u8 data, Seq_animation * anim, bool light_variant) {
    anim->need_run = true;
    anim->data = data;
    anim->speed = 7;
    anim->length = 50;
    anim->start_time = 0;
    anim->light_pattern = light_variant ? 0xF : 0x9;
    anim->anim = SEQ_ANIM_FLASH_NUM;

}

