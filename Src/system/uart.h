#ifndef SYSTEM_UART_H_
#define SYSTEM_UART_H_
#include "../util/types.h"
#include "../util/circular_buffer.h"
#include "../util/error_log.h"

int print(char* input);

void send_buffer_uart_3(Circular_buffer * uart_3);
void send_data_uart_4(u8 data);
#endif /* SYSTEM_UART_H_ */
