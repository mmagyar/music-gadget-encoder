#include "mainthread.h"
#include "mcu_util/led_update.h"
#include "stm32g070xx.h"
#include "tim.h"
#include "mcu_util/inputs.h"
#include "util/error_log_code_text.h"
#include  <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO
#include "lib/printf.h"
#include "seq/seq.h"

Task tasks[max_task_count] = { };
u32 ms_counter = 0;
u32 ms_last = 0;
const u8 TASK_INDEX_LED_UPDATE = 0;
const u8 TASK_INDEX_SEQ_UPATE = 1;
void calculate_task_time(Task * task);

void init_tasks() {
    tasks[TASK_INDEX_LED_UPDATE].task = &update_display;
    tasks[TASK_INDEX_SEQ_UPATE].task = &update_seq;
    tasks[TASK_INDEX_SEQ_UPATE].repeat_ms = 16;

}
char chr = 0;

void main_thread() {

    init_tasks();
    printf("\n\rSTARTING UP %d", 4);
    print("START CTRL");

    while (1) {

        if (ms_counter != ms_last) {
            loop(task_i, max_task_count)
            {
                u32 repeat = tasks[task_i].repeat_ms;
                if (repeat) {
                    if (ms_counter > repeat + tasks[task_i].last_run_ms) {
                        tasks[task_i].needs_run = true;
                    }
                }
            }

            ms_last = ms_counter;
        }
        loop(task_i, max_task_count)
        {
            Task * task = &tasks[task_i];
            if (task->needs_run && task->task != NULL) {
                task->start_clk = TIM3->CNT;
                task->start_ms = ms_counter;
                task->task();

                if (!task->dont_reset_needs_run) {
                    task->needs_run = false;
                }
                task->last_run_ms = ms_counter;
                task->end_clk = TIM3->CNT;
                task->end_ms = ms_counter;

                calculate_task_time(task);

            }

        }

        if (button_pressed[0]) {
            button_pressed[0]--;
            printf("HELLO, loop time of led update: %d\r\n", (int) tasks[0].avg_time);
        }

        if (error_count) {
            loop(ec, error_count)
            {
                Error * e = &error_log[ec];
                if (e->error_code) {
                    char to_print[128];
                    sprintf(to_print, "ERR %d - %c : %s", e->error_code, e->identifier,
                            error_code_text[(u8) e->error_code]);
                    print(to_print);
                    e->error_code = 0;
                    e->identifier = 0;
                }

            }
            error_count = 0;
        }
    }

}

void calculate_task_time(Task * task) {
    u32 ms_diff = task->end_ms - task->start_ms;
    if (ms_diff) {
        //Add the passed milliseconds
        task->last_time = (ms_diff - 1) * (u64) 1000;
        //Add the remaining part from the start part
        task->last_time += (1000 - task->start_clk);
        //Add the ticks passed since the last ms
        task->last_time += task->end_clk;
    } else {
        task->last_time = task->end_clk - task->start_clk;
    }

    u64 last_avg = task->avg_time;
    u8 avgs = 8;
    u64 new_avg = 0;
    loop(avg_i, (avgs - 1))
    {
        new_avg += last_avg;
    }
    task->avg_time = (new_avg + task->last_time) / avgs;
}

/**
 * Elapsed_time_counter
 */
void TIM3_IRQHandler(void)
{
    ms_counter++;
    seq.current_ms = ms_counter;
    LL_TIM_ClearFlag_UPDATE(TIM3);
}



/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */

    LL_SPI_TransmitData16(SPI1, 0xAAAA);
    mux_off();

    volatile int b = 0;
    volatile int a_max = 0xFFFFF >> 1;
    volatile int a = a_max;
    volatile int p = 0;
    /* USER CODE END HardFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        LL_GPIO_WriteOutputPort((GPIO_TypeDef *) mux_port[p],
                mux_port[p]->ODR & ~mux_pin[p]);

        LL_GPIO_WriteOutputPort((GPIO_TypeDef *) mux_port[p],
                mux_port[p]->ODR | mux_pin[p]);

        a++;
        p++;
        if (p > 9) p = 0;
        if (a > a_max) {
            a = 0;
            LL_SPI_TransmitData16(SPI1, b > 0 ? (b > 1 ? 0xAAAA : 0xFFFF) : 0x5555);
            b++;
            if (b > 2) b = 0;
        }
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}
