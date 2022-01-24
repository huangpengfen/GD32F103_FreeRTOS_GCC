#define BSP_UART_EXTERN
#include <stdlib.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "../../USER/globalvar.h"
#include "../../../Libraries/CMSIS/GD/GD32F10x/Include/gd32f10x.h"
#include "bsp_uart.h"

//???????��???,???printf????,??????????use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//????????????????                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//????_sys_exit()???????e???????    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//?????fputc???? 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//???????,??????????   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}
#else
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
	usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
	return ch;
}
#endif 

static void usart_nvic_config(void);
static void usart_config(void);
static void usart_dma_config(void);


UINT8 UART_BUFF[2*1024];
UINT16 UART_LEN;


void COM_init(void)
{
    usart_nvic_config();
    usart_dma_config();
    usart_config();
	
	/*wait IDLEF set and clear it*/
    //while(RESET == usart_flag_get(USART0, USART_FLAG_IDLEF));
    usart_flag_clear(USART0, USART_FLAG_IDLEF);
    usart_interrupt_enable(USART0, USART_INT_IDLE);

}

static void usart_nvic_config(void)
{
    nvic_irq_enable(USART0_IRQn, 5, 0);
}

static void usart_config(void)
{
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);
    
    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(USART0, USART_DENR_ENABLE);
    usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
    usart_enable(USART0);
}

static void usart_dma_config(void)
{
    dma_parameter_struct dma_init_struct;
    
    rcu_periph_clock_enable(RCU_DMA0);
    
    /* deinitialize DMA channel4 (USART0 rx) */
    dma_deinit(DMA0, DMA_CH4);
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr = (uint32_t)UART_BUFF;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 1024;
    dma_init_struct.periph_addr = USART0_RDATA_ADDRESS;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA0, DMA_CH4, &dma_init_struct);
    /* configure DMA mode */
    dma_circulation_disable(DMA0, DMA_CH4);
    /* enable DMA channel4 */
    dma_channel_enable(DMA0, DMA_CH4);
}

/* retarget the C library printf function to the USART */
//int fputc(int ch, FILE *f)
//{
//    usart_data_transmit(USART0, (uint8_t)ch);
//    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
//    return ch;
//}

extern QueueHandle_t Message_Queue_Uart;	//


void UART_Debug_ISR(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    

    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE))
	{
        /* clear IDLE flag */
        usart_data_receive(USART0);
        
        /* number of data received */
        UART_LEN = 1024 - (dma_transfer_number_get(DMA0, DMA_CH4));
        
        /* disable DMA and reconfigure */
        dma_channel_disable(DMA0, DMA_CH4);
        dma_transfer_number_config(DMA0, DMA_CH4, 1024);
        dma_channel_enable(DMA0, DMA_CH4);
    }
}


UINT8 UART_Debug_SendStr(UINT8 *str, UINT16 len)
{
	
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		usart_data_transmit(USART0, *str++);
		while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
	}
	return len;
}