#ifndef SYSTEM_IRQ_HELPER_H_
#define SYSTEM_IRQ_HELPER_H_

#include "../util/error_log.h"
#define IRQ_COMMON(IRQ_CODE) \
    LL_TIM_DisableCounter(TIM3); /** Disable timer used to measure task time **/ \
    IRQ_CODE \
    LL_TIM_EnableCounter(TIM3); /** Enable timer used to measure task time **/

#define SPI_ERRORS_IRQ(SPI_NUM) \
    if (LL_SPI_IsActiveFlag_FRE(SPI## SPI_NUM)) { \
        log_error(EC_SPI_## SPI_NUM ##_FRAME_ERROR, 'm'); \
        LL_SPI_ClearFlag_FRE(SPI## SPI_NUM); \
    } else if (LL_SPI_IsActiveFlag_CRCERR(SPI## SPI_NUM)) { \
        log_error(EC_SPI_ ## SPI_NUM ##_CRC_ERROR, 'm'); \
        LL_SPI_ClearFlag_CRCERR(SPI## SPI_NUM); \
    } else if (LL_SPI_IsActiveFlag_OVR(SPI## SPI_NUM)) { \
        log_error(EC_SPI_## SPI_NUM ##_OVERFLOW, 'm'); \
        LL_SPI_ClearFlag_OVR(SPI## SPI_NUM); \
    } else if (LL_SPI_IsActiveFlag_MODF(SPI## SPI_NUM)) { \
        LL_SPI_ClearFlag_MODF(SPI## SPI_NUM); \
        log_error(EC_SPI_## SPI_NUM ##_MODE_FAULT, 'm'); \
    } else { \
        log_error(EC_SPI_## SPI_NUM ##_UNEXPECTED, 'm'); \
    }

#define SPI_RX_ONLY_IRQ(SPI_NUM, RX_CODE) \
 LL_TIM_DisableCounter(TIM3); /** Disable timer used to measure task time **/ \
    if (LL_SPI_IsActiveFlag_RXNE(SPI## SPI_NUM)) { \
        RX_CODE \
    } else if(LL_SPI_IsActiveFlag_TXE(SPI## SPI_NUM)){ \
        log_error(EC_SPI_## SPI_NUM ##_UNHANDLED_TX_IRQ, 'm'); \
        LL_SPI_DisableIT_TXE(SPI## SPI_NUM); \
    } else SPI_ERRORS_IRQ(SPI_NUM) \
    LL_TIM_EnableCounter(TIM3); /** Enable timer used to measure task time **/

#define SPI_IRQ(SPI_NUM, RX_CODE, TX_CODE) \
	IRQ_COMMON({ \
        if (LL_SPI_IsActiveFlag_RXNE(SPI_## SPI_NUM ##)) { \
            RX_CODE \
        } else if(LL_SPI_IsActiveFlag_TXE(SPI_## SPI_NUM ##)){ \
        	TX_CODE \
        } else SPI_ERRORS_IRQ(SPI_NUM) \
    })

#define UART_ERRORS_IRQ(USART_NUM, SHOW_UNEXPECTED_ERR) \
    if (LL_USART_IsActiveFlag_FE(USART ## USART_NUM)) { \
        log_error(EC_UART_## USART_NUM ##_FRAMING_ERROR, 'i'); \
        LL_USART_ClearFlag_FE(USART ## USART_NUM); \
    } else if (LL_USART_IsActiveFlag_NE(USART ## USART_NUM)) { \
        log_error(EC_UART_## USART_NUM ##_NOISE_ERROR, 'i'); \
        LL_USART_ClearFlag_NE(USART ## USART_NUM); \
    } else if (LL_USART_IsActiveFlag_ORE(USART ## USART_NUM)) { \
        log_error(EC_UART_## USART_NUM ##_OVERFLOW, 'i'); \
        LL_USART_ClearFlag_ORE(USART ## USART_NUM); \
    } else if (SHOW_UNEXPECTED_ERR) log_error(EC_UART_## USART_NUM ##_UNEXPECTED, 'i'); \

#define UART_IRQ(USART_NUM, RX_CODE, TX_CODE, SHOW_UNEXPECTED_ERR) \
    IRQ_COMMON({ \
        if (LL_USART_IsActiveFlag_RXNE(USART ## USART_NUM) && LL_USART_IsEnabledIT_RXNE(USART ## USART_NUM)) { \
            RX_CODE \
        } else if (LL_USART_IsActiveFlag_TXE(USART ## USART_NUM) && LL_USART_IsEnabledIT_TXE(USART ## USART_NUM)) { \
            TX_CODE \
        } else UART_ERRORS_IRQ(USART_NUM, SHOW_UNEXPECTED_ERR) \
    })

#endif /* SYSTEM_IRQ_HELPER_H_ */
