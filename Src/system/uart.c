#include "../system/uart.h"

#include "usart.h"
#include "../util/error_log.h"
#include "../lib/printf.h"
#include "../system/irq_helper.h"
#define UART_BUFFER_SIZE 8

def_Circular_buffer(uart_1_rx_buffer, UART_BUFFER_SIZE, '1');
def_Circular_buffer(uart_1_tx_buffer, UART_BUFFER_SIZE, '1');
def_Circular_buffer(uart_2_rx_buffer, UART_BUFFER_SIZE, '2');
def_Circular_buffer(uart_2_tx_buffer, UART_BUFFER_SIZE, '2');
def_Circular_buffer(uart_3_rx_buffer, UART_BUFFER_SIZE, '3');
def_Circular_buffer(uart_3_tx_buffer, UART_BUFFER_SIZE, '3');
def_Circular_buffer(uart_4_rx_buffer, UART_BUFFER_SIZE, '4');
def_Circular_buffer(uart_4_tx_buffer, UART_BUFFER_SIZE, '4');



void send_data_uart_1(u8 data) {
    add_to_buffer(&uart_1_tx_buffer, data);
    LL_USART_EnableIT_TXE_TXFNF(USART1);
}
void send_data_uart_2(u8 data) {
    add_to_buffer(&uart_2_tx_buffer, data);
    LL_USART_EnableIT_TXE_TXFNF(USART2);
}

void send_data_uart_3(u8 data) {
    add_to_buffer(&uart_3_tx_buffer, data);
    LL_USART_EnableIT_TXE_TXFNF(USART3);
}

void send_data_uart_4(u8 data) {
    add_to_buffer(&uart_4_tx_buffer, data);
    LL_USART_EnableIT_TXE_TXFNF(USART4);

}

void send_data_uart_all(u8 data) {
    send_data_uart_1(data);
    send_data_uart_2(data);
    send_data_uart_3(data);
    send_data_uart_4(data);
}

void _putchar(char character) {
    if (!add_to_buffer_if_not_full(&uart_3_tx_buffer, character)) {
        log_error(EC_PRINT_BUFFER_FULL, 'c');
    } else {
        LL_USART_EnableIT_TXE_TXFNF(USART3);
    }
}

#define UART_RX(num) \
        static inline void uart_ ## num ## _rx_fn() { \
        char data = LL_USART_ReceiveData8(USART ## num); \
            if (LL_USART_IsActiveFlag_TXE_TXFNF(USART ## num)) { \
                add_to_buffer(&uart_ ## num ## _rx_buffer, data); \
            } \
        }

#define UART_TX(num) \
      static inline void uart_ ## num ## _tx_fn() { \
        Buffer_read_result result = { 0, false }; \
        get_from_buffer(&uart_ ## num ## _tx_buffer, &result); \
        if (result.readSuccess) { \
            LL_USART_TransmitData8(USART ## num, result.data); \
        } else { \
            /** Disable transmit interrupts when there are no new data to transmit **/ \
            LL_USART_DisableIT_TXE_TXFNF(USART## num); \
        } \
        }

#define UART_HANDLER(NUM, SHOW_UNEXPECTED_ERR) \
        UART_IRQ(NUM, { uart_ ## NUM ## _rx_fn();  }, { uart_## NUM ## _tx_fn(); }, SHOW_UNEXPECTED_ERR)

UART_RX(1)
UART_TX(1)
UART_RX(2)
UART_TX(2)
UART_RX(3)
UART_TX(3)
UART_RX(4)
UART_TX(4)

//void uart_3_rx_fn() {
//    char data = LL_USART_ReceiveData8(USART3);
//    printf("0x%04X\r\n", data);
//}


/**
 * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
 */
void USART1_IRQHandler(void)
{
    UART_HANDLER(1, true);
}

/**
 * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
 */
void USART2_IRQHandler(void)
{
    UART_HANDLER(2, true);
}

volatile int a = 0;
/**
 * @brief This function handles USART3 and USART4 interrupts.
 */
void USART3_4_IRQHandler(void)
{
    if(LL_USART_IsActiveFlag_RXNE(USART4)){
        a++;
    }
    UART_HANDLER(4, false);

    UART_HANDLER(3, false);
}

