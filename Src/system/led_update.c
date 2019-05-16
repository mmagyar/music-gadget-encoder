#include "../system/led_update.h"

#include "tim.h"
#include "../util/safe_array.h"
#include "../mainthread.h"
#include "../system/inputs.h"

u16 led_data[10][intensity_gradients] = { 0 };
Led_display display = { DT_PRECISE, 0, { 0 }, { { { 0 }, { 0 }, 0, 0 } } };

Intensity led_intensity[10][16] = { 0 };
void intensity_calc(u8 column);
inline void intensity_calc(u8 column) {
    Intensity * c_i = led_intensity[column];

    loop(bit,intensity_gradients)
    {
        u16 intens = 0;
        loop(i,16)
        {
            intens |= ((!!(c_i[i] & (1 << bit))) << i);
        }

        led_data[column][bit] = intens;

    }

}

void led_calculate_bar_16(u8 value, Intensity * target) {
    u8 four_bit_value = value >> 4;
    u8 remainder = (value & 0x0F) >> 2;
    loop(i, 16)
    {

        u8 intensity = 0;
        if (four_bit_value > i) {
            intensity = intensity_high;
        } else if (four_bit_value == i) {
            switch (remainder) {
            case 0:
                intensity = intensity_off;
                break;
            case 1:
                intensity = intensity_low;
                break;
            case 2:
                intensity = intensity_low_med;

                break;
            case 3:
                intensity = intensity_high_med;
                break;
            default:
                intensity = intensity_high;
                break;
            }
        }

        target[15 - i] = intensity;

    }

}

void led_calculate_bar_signed_16(s8 signed_value, Intensity * target) {
    u8 value = signed_value > 0 ? signed_value : -signed_value;
    u8 three_bit_value = value >> 4;
    u8 remainder = (value & 0x0F) >> 2;
    loop(i, 8)
    {

        u8 intensity = 0;
        if (three_bit_value > i) {
            intensity = intensity_high;
        } else if (three_bit_value == i) {
            switch (remainder) {
            case 0:
                intensity = intensity_off;
                break;
            case 1:
                intensity = intensity_low;
                break;
            case 2:
                intensity = intensity_low_med;

                break;
            case 3:
                intensity = intensity_high_med;
                break;
            default:
                intensity = intensity_high;
                break;
            }
        }

        if (signed_value > 0) target[7 - (i)] = intensity;
        else if (signed_value < 0) target[i + 8] = intensity;
        else {
            target[i] = intensity_off;
            target[i + 8] = intensity_off;
        }

    }

}

void led_calculate_bar_32(u8 value, u8 led_column_1, u8 led_column_2) {
    u8 five_bit_value = value >> 3;
    u8 remainder = (value & 0x07) >> 1;
    u8 even_count = 0;
    u8 odd_count = 0;
    loop(i, 32)
    {

        u8 intensity = 0;
        if (five_bit_value > i) {
            intensity = intensity_high;
        } else if (five_bit_value == i) {
            switch (remainder) {
            case 0:
                intensity = intensity_off;
                break;
            case 1:
                intensity = intensity_low;
                break;
            case 2:
                intensity = intensity_low_med;
                break;
            case 3:
                intensity = intensity_high_med;
                break;
            default:
                intensity = intensity_high;
                break;
            }
        }

        if (i % 2) {
            led_intensity[led_column_1][odd_count] = intensity;
            odd_count++;
        } else {
            led_intensity[led_column_2][even_count] = intensity;
            even_count++;
        }
    }

    intensity_calc(led_column_1);
    intensity_calc(led_column_2);

}

void update_display() {
    if (display.display_type == DT_VALUE) {
        display.top_bar_value = encoders[1].data;
        loop(x,4)
        {
            display.encoders[x].red_value = encoders[x].data;
        };
        loop(x,4)
        {

            u8 col1 = (x * 2) + 1;
            u8 col2 = x * 2;
            led_calculate_bar_16(display.encoders[x].red_value, led_intensity[col1]);
            led_calculate_bar_16(display.encoders[x].green_value, led_intensity[col2]);
            intensity_calc(col1);
            intensity_calc(col2);
        };

        led_calculate_bar_32(display.top_bar_value, 8, 9);
    } else {

        u8 even_count = 0;
        u8 odd_count = 0;
        loop(x, 32)
        {
            if (x % 2) {
                led_intensity[8][even_count] = display.top_bar_precise[x];
                even_count++;
            } else {
                led_intensity[9][odd_count] = display.top_bar_precise[x];
                odd_count++;
            }
        }

        loop(x, 16)
        {
            loop(y, 4)
            {
                led_intensity[y * 2][x] = display.encoders[y].green_precise[x];
                led_intensity[(y * 2) + 1][x] = display.encoders[y].red_precise[x];
            }
        }

        loop(x, 10)
        {
            intensity_calc(x);
        }
    }

}

/**
 * Update the display
 */
void TIM14_IRQHandler(void)
{
    tasks[TASK_INDEX_LED_UPDATE].needs_run = true;
    LL_TIM_ClearFlag_UPDATE(TIM14);

}
