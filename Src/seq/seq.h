#ifndef SEQ_SEQ_H_
#define SEQ_SEQ_H_
#include "../lib/printf.h"
#include "../util/types.h"
#include "../util/counter.h"
#define ARM_MATH_CM0PLUS
#define SEQ_LEVELS 4
typedef struct {
    u8 velocity;
    s8 pitch;
} Seq_event;

typedef struct {
    Counter cursor;
    Counter position;
    Counter current_level;
    bool playing;
    u8 bpm;
    u32 current_ms; /* This parameter needs to be incremented in a timer interrupt every ms*/
    u32 start_ms;

    Seq_event points[SEQ_LEVELS][32];
} Seq;

typedef enum {
    SEQ_ANIM_SHOW_NUM,
    SEQ_ANIM_FLASH_NUM
} Seq_anim_type;

typedef struct {
    u8 data;
    u8 speed;
    u8 length;
    u8 light_pattern;
    u32 start_time;
    bool need_run;

    Seq_anim_type anim;
} Seq_animation;


Seq seq;
void update_seq();

void send_midi();
#endif /* SEQ_SEQ_H_ */
