#include "../system/mux.h"

#include "tim.h"
#include "spi.h"

#include "../system/irq_helper.h"
#include "../system/led_update.h"
#include "../util/error_log.h"
const GPIO_TypeDef * mux_port[10] = {
LED_MUX_0_GPIO_Port, LED_MUX_1_GPIO_Port,
LED_MUX_2_GPIO_Port, LED_MUX_3_GPIO_Port, LED_MUX_4_GPIO_Port,
LED_MUX_5_GPIO_Port, LED_MUX_6_GPIO_Port, LED_MUX_7_GPIO_Port,
LED_MUX_8_GPIO_Port, LED_MUX_9_GPIO_Port, };

const u16 mux_pin[10] = {
LED_MUX_0_Pin, LED_MUX_1_Pin, LED_MUX_2_Pin,
LED_MUX_3_Pin, LED_MUX_4_Pin, LED_MUX_5_Pin, LED_MUX_6_Pin,
LED_MUX_7_Pin, LED_MUX_8_Pin, LED_MUX_9_Pin,

};

u8 rotate_c = 0;
u8 current_mux = 0;
u8 current_bit = 0;
s8 can_turn_off = 0;

/* transfer state */
volatile TS wTransferState = TRANSFER_COMPLETE;

static inline void switch_mux(u16 x, bool state) {

    state ? LL_GPIO_WriteOutputPort((GPIO_TypeDef *) mux_port[x],
                    mux_port[x]->ODR | mux_pin[x]) :
            LL_GPIO_WriteOutputPort((GPIO_TypeDef *) mux_port[x],
                    mux_port[x]->ODR & ~mux_pin[x]);
}

static inline void switch_mux_on(u16 x) {
    switch_mux(x, false);
}

static inline void switch_mux_off(u16 x) {
    switch_mux(x, true);
}

inline void mux_off() {
    loop(i, 10)
    {
        switch_mux_off(i);
    }
}

volatile int debug_n = 0;

static inline void previous_mux_off() {

    if (rotate_c == 0) {
        switch_mux_off(9);
    } else {
        switch_mux_off(rotate_c - 1);
    }

}

static inline void send_current_led_data() {
    wTransferState = TRANSFER_WAIT;
    LL_SPI_TransmitData16(SPI1, led_data[rotate_c][current_bit]);
}

static inline void turn_on_current_channel() {
    switch_mux_on(rotate_c);
    current_mux = rotate_c;
    mux_button_read();

    if (rotate_c >= 9) {
        rotate_c = 0;
        current_bit++;
        if (current_bit >= intensity_gradients) current_bit = 0;

    } else {
        rotate_c++;
    }
}
//
//void HAL_SPI_ErrorCallback() {
//    wTransferState = TRANSFER_ERROR;
//}
const u8 global_brightness = 4;

void multiplex() {
    if (wTransferState == TRANSFER_WAIT) {
        return;
    }
    if (can_turn_off > 0) {
        if (can_turn_off == global_brightness) {

            previous_mux_off();
        }
        can_turn_off--;

        return;
    } else if (global_brightness == 0) {

        previous_mux_off();
    }

    /* Turn off all transistors when sending data to the led driver */

    send_current_led_data();

}
static void inline spi_rx_irq() {
    can_turn_off = global_brightness;
    wTransferState = TRANSFER_COMPLETE;
    LL_SPI_ReceiveData16(SPI1);
    turn_on_current_channel();
}

/**
 * Send data to LED driver finished
 */
void SPI1_IRQHandler(void) {
    SPI_RX_ONLY_IRQ(1, {
        spi_rx_irq()
        ;
    })
}

/**
 * Multiplex LEDs
 */
void TIM7_IRQHandler(void) {
    IRQ_COMMON({
            multiplex();
            LL_TIM_ClearFlag_UPDATE(TIM7);
            })
}

/**
 * Read encoders
 */
void TIM6_IRQHandler(void) {
    IRQ_COMMON({
            read_encoder_inputs();
            LL_TIM_ClearFlag_UPDATE(TIM6);
            });
}

