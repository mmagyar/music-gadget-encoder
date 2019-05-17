#include "mainthread.h"
#include "stm32g070xx.h"
#include "tim.h"
#include "util/error_log_code_text.h"
#include  <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO
#include "lib/printf.h"
#include "seq/seq.h"
#include "seq/control.h"
#include "system/inputs.h"
#include "system/led_update.h"
#include "system/mux.h"
#include "util/midi/midi.h"
#include "util/dataframe.h"
#include "system/intercom.h"
#include "system/uart.h"

Task tasks[max_task_count] = { 0 };
u32 ms_counter = 0;
u32 ms_last = 0;
const u8 TASK_INDEX_LED_UPDATE = 0;
const u8 TASK_INDEX_SEQ_UPDATE = 1;
const u8 TASK_INDEX_CONTROL_UPDATE = 2;
const u8 TASK_INDEX_COMM = 3;
const u8 TASK_ERROR_PRINT = 4;

u32 received_frames_count = 0;

void calculate_task_time(Task * task);

Icom_send icom_buffer[4] = { 0 };
Frame_Receive_buffer frame_buffer[4] = { 0 };

volatile int azz = 0;
void test_receive_control_change(Control_change ch) {
    azz++;
}
void test_receive_button_press(Button_press bp) {
    azz++;
}
void test_receive_led_update(Led_update lu) {
    azz++;
}
void read_uart_rx_buffer() {
    Circular_buffer * cb[4] = {
            &uart_1_rx_buffer,
            &uart_2_rx_buffer,
            &uart_3_rx_buffer,
            &uart_4_rx_buffer };

    loop(x, 4)
    {
        Buffer_read_result brr = { 0 };

        pop_from_buffer(cb[x], &brr);

        if (brr.readSuccess) {
            bool frame_end = receive_byte(brr.data, &frame_buffer[x]);
            if (frame_end) {
                received_frames_count++;
                icom_read_message(frame_buffer[x].buffer, frame_buffer[x].message_size,
                        &icom_buffer[x]);
            }
        }
    }

}

void error_print(){
    if (error_count) {
        loop(ec, error_count)
        {
            Error * e = &error_log[ec];
            if (e->error_code) {
            //    printf("\r\nERR 0x%02X - %c : %s\r\n", e->error_code, e->identifier,
            //            error_code_text[(u8) e->error_code]);

                e->error_code = 0;
                e->identifier = 0;
            }

        }
        error_count = 0;
    }
}

volatile int abcd= 0;
void test(){
    Control_change ch = { 1, abcd++ };
    icom_send_control_change(&ch);
}
void crc_feed_stm32(u8 byte) {
    LL_CRC_FeedData8(CRC, byte);
}
u32 crc_get_stm32() {
    u32 data = LL_CRC_ReadData32(CRC);
    LL_CRC_ResetCRCCalculationUnit(CRC);
    /* We need to invert it to get a standard CRC32*/
    return (~data);
}
void init_tasks() {

    icom_receive_control_change = &test_receive_control_change;
    icom_receive_button_press = &test_receive_button_press;
    icom_receive_led_update = &test_receive_led_update;

    //midi_bytes_ready_to_send = send_buffer_uart_3;

    tasks[TASK_INDEX_LED_UPDATE].task = &update_display;

    tasks[TASK_INDEX_SEQ_UPDATE].task = &update_seq;
    tasks[TASK_INDEX_SEQ_UPDATE].repeat_ms = 0;

    /** Configurte this task to run every 16ms (~60hz) **/
    tasks[TASK_INDEX_CONTROL_UPDATE].task = &process_control;
    tasks[TASK_INDEX_CONTROL_UPDATE].repeat_ms = 16;

    /** Configure this task to run on every loop **/
    tasks[TASK_INDEX_COMM].dont_reset_needs_run = true;
    tasks[TASK_INDEX_COMM].needs_run = true;
    tasks[TASK_INDEX_COMM].task = read_uart_rx_buffer;

    tasks[TASK_ERROR_PRINT].task = error_print;
    tasks[TASK_ERROR_PRINT].repeat_ms = 100;
    //tasks[7].repeat_ms = true;
    //tasks[7].task = &test;

    crc_feed = &crc_feed_stm32;
    crc_get = &crc_get_stm32;
}
char chr = 0;
u64 aha = 0;
void main_thread() {

    volatile int asdf[199] = {0};
    init_tasks();
    printf("\r\nSTARTING UP %d\r\n", 4);

    while (1) {
aha++;
asdf[aha] = aha;
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

            if(asdf[aha])
            ms_last = ms_counter;
            else
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
            //  button_pressed[0]--;
            // printf("HELLO, loop time of led update: %d\r\n", (int) tasks[0].avg_time);
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
    loop(avg_i, (avgs - 1U))
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
    printf("HARD FAULT, receive_frame_count: %d , uart bytes: %d",received_frames_count,receive_uarts);
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
