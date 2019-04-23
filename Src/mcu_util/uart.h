#ifndef MCU_UTIL_UART_H_
#define MCU_UTIL_UART_H_
#include "../util/types.h"
#include "../util/circular_buffer.h"
#include "../util/error_log.h"

int print(char* input);

void send_buffer_uart_3(Circular_buffer * uart_3);
#endif /* MCU_UTIL_UART_H_ */
