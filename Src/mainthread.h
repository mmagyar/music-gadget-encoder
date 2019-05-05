#ifndef MAINTHREAD_H_
#define MAINTHREAD_H_



#include "system/uart.h"
#include "util/error_log.h"
#include "util/types.h"
#include "util/safe_array.h"
typedef void (*Run_task)();
typedef struct Task {
    u16 id;
    bool needs_run;
    bool dont_reset_needs_run;
    Run_task task;
    u32 repeat_ms;
    u32 last_run_ms;
    volatile u32 start_ms;
    volatile u32 start_clk;
    volatile u32 end_ms;
    volatile u32 end_clk;
    /* Last execution time in us */
    volatile u64 last_time;
    volatile u64 avg_time;
} Task;

#define max_task_count 16

const u8 TASK_INDEX_LED_UPDATE;
Task tasks[max_task_count];

void main_thread();

#endif /* MAINTHREAD_H_ */
