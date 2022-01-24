#ifndef __BSP_UART_H__
#define __BSP_UART_H__ 1

#ifdef BSP_UART_EXTERN
#   define BSP_UART_EXT
#else
#   define BSP_UART_EXT extern
#endif

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

#define UART_STAT_IDEL              0   // 空闲状�?
#define UART_STAT_Rcving            1   // 接收�?
#define UART_STAT_RcvEnd            2   // 接收完成
#define UART_STAT_Snding            3   // 发送中

BSP_UART_EXT void COM_init(void);

BSP_UART_EXT void UART_Debug_Init(void);
BSP_UART_EXT UINT8 UART_Debug_SendStr(UINT8 *str, UINT16 len);
BSP_UART_EXT void UART_Debug_ISR(void);
BSP_UART_EXT void UART_Wifi_Init(void);
BSP_UART_EXT UINT8 UART_Wifi_SendStr(UINT8 *str, UINT16 len);
BSP_UART_EXT void UART_Wifi_ISR(void);
#endif
