#include "../system/uart.h"

#include "usart.h"
#include "../util/error_log.h"
#include "../lib/printf.h"
#include "../system/irq_helper.h"

def_Circular_buffer(uart_print, 8, 'p');
def_Circular_buffer(uart_cmd, 8, 'c');

Circular_buffer * uart_3_buffer = NULL;
void send_buffer_uart_3(Circular_buffer * uart_3) {
    uart_3_buffer = uart_3;
    LL_USART_EnableIT_TXE_TXFNF(USART3);

}

void send_data_uart_4(u8 data) {
    add_to_buffer(&uart_print, data);
    LL_USART_EnableIT_TXE_TXFNF(USART4);

}

/**
 * Print to UART
 * Returns the number of written bytes
 */
int print(char* input) {
    int written_bytes = 0;
    bool print_buffer_overflow = false;
    for (u16 i = 0; input[i] != 0; i++) {
        if (add_to_buffer_if_not_full(&uart_print, input[i])) written_bytes++;
        else {
            print_buffer_overflow = true;
            break;
        }
    }

    if (print_buffer_overflow) {
        log_error(EC_PRINT_BUFFER_FULL, 'p');
    }

    if (written_bytes) {
        add_to_buffer_if_not_full(&uart_print, '\r');
        add_to_buffer_if_not_full(&uart_print, '\n');
        LL_USART_EnableIT_TXE_TXFNF(USART4);
        written_bytes += 2;
    }
    return written_bytes;
}

void _putchar(char character) {
    if (!add_to_buffer_if_not_full(&uart_print, character)) {
        log_error(EC_PRINT_BUFFER_FULL, 'c');
    } else {
        LL_USART_EnableIT_TXE_TXFNF(USART4);
    }
}

/**
 * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
 */
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */

    /* USER CODE END USART1_IRQn 0 */
    /* USER CODE BEGIN USART1_IRQn 1 */

    /* USER CODE END USART1_IRQn 1 */
}

/**
 * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
 */
void USART2_IRQHandler(void)
{
    /* USER CODE BEGIN USART2_IRQn 0 */

    /* USER CODE END USART2_IRQn 0 */
    /* USER CODE BEGIN USART2_IRQn 1 */

    /* USER CODE END USART2_IRQn 1 */
}

void uart_4_rx() {
    char data = LL_USART_ReceiveData8(USART4);
    if (LL_USART_IsActiveFlag_TXE_TXFNF(USART4)) {
        add_to_buffer(&uart_cmd, data);
    }
}

void uart_4_tx() {
    Buffer_read_result result = { 0, false };
    get_from_buffer(&uart_print, &result);
    if (result.readSuccess) {
        LL_USART_TransmitData8(USART4, result.data);
    } else {
        //Disable transmit interrupts when there are no new data to transmit
        LL_USART_DisableIT_TXE_TXFNF(USART4);
    }
}

void uart_3_rx() {
    char data = LL_USART_ReceiveData8(USART3);
    printf("0x%04X\r\n", data);
}
void uart_3_tx() {
    Buffer_read_result result = { 0, false };
    get_from_buffer(uart_3_buffer, &result);
    if (result.readSuccess) {
        LL_USART_TransmitData8(USART3, result.data);
    } else {
        //Disable transmit interrupts when there are no new data to transmit
        LL_USART_DisableIT_TXE_TXFNF(USART3);
    }
}
/**
 * @brief This function handles USART3 and USART4 interrupts.
 */
void USART3_4_IRQHandler(void)
{
    UART_IRQ(4, {
        uart_4_rx()
        ;
    },
    {
        uart_4_tx()
        ;
    }, false)

    UART_IRQ(3, {
        uart_3_rx()
        ;
    },
    {
        uart_3_tx()
        ;
    },false)

}

