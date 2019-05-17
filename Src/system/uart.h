#ifndef SYSTEM_UART_H_
#define SYSTEM_UART_H_
#include "../util/types.h"
#include "../util/circular_buffer.h"
#include "../util/error_log.h"

u32 receive_uarts;

Circular_buffer uart_1_rx_buffer;
Circular_buffer uart_2_rx_buffer;
Circular_buffer uart_3_rx_buffer;
Circular_buffer uart_4_rx_buffer;


void send_data_uart_1(u8 data);
void send_data_uart_2(u8 data);
void send_data_uart_3(u8 data);
void send_data_uart_4(u8 data);
void send_data_uart_all(u8 data);
#endif /* SYSTEM_UART_H_ */
