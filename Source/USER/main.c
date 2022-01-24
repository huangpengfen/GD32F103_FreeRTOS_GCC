#define GLOBALVAR_EXTERN
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "../BSP/LED/bsp_led.h"
#include "../BSP/BspSystick/systick.h"
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		256  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define COM_TASK_PRIO		2
//任务堆栈大小	
#define COM_STK_SIZE 		256  
//任务句柄
TaskHandle_t ComTask_Handler;
//任务函数
void com_task(void *pvParameters);

//任务优先级
#define MICRO_TASK_PRIO		3
//任务堆栈大小	
#define MICRO_STK_SIZE 		256  
//任务句柄
TaskHandle_t MicroTask_Handler;
//任务函数
void micro_task(void *pvParameters);


#define    Message_Uart_NUM    4

QueueHandle_t Message_Queue_Uart;	//

SemaphoreHandle_t BinarySemaphore_Analyse; // Pressure Temp
SemaphoreHandle_t BinarySemaphore_Current; // Current

#define FREE(p) myfree((void **)&p)  // 防止内存泄漏
void myfree(void ** point)
{
	if(*point != NULL)
	{
    	free(*point);
    	*point = NULL;
	}
}

//--------------------------------------------------------------------------
//描述:
//参数:
//返回:
//--------------------------------------------------------------------------
int main(void)
{
#ifndef DF_RELEASE
    //DBGMCU_CR
    //    注意其中的DBG_WWDG_STOP和DBG_IWDG_STOP位,这两个位允许配置内核停止时停
    //    止看门狗时钟,达到停止看门狗的目的
    *(unsigned long *)0xe0042004 = 0xFFFFFFFF;
#endif
    SystemInit();
    systick_config();
    COM_init();
    LED_Init();
	
    //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度

}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区

    //创建串口响应任务
    xTaskCreate((TaskFunction_t )com_task,     	
                (const char*    )"com_task",   	
                (uint16_t       )COM_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )COM_TASK_PRIO,	
                (TaskHandle_t*  )&ComTask_Handler);
    //创建微控制任务
    xTaskCreate((TaskFunction_t )micro_task,     
                (const char*    )"micro_task",   
                (uint16_t       )MICRO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )MICRO_TASK_PRIO,
                (TaskHandle_t*  )&MicroTask_Handler);


    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//串口响应处理任务函数
void com_task(void *pvParameters)
{

    while (1)
    {
        Run_DebugLED();
        vTaskDelay(200);
    }
}

//微控制处理任务函数
void micro_task(void *pvParameters)
{
    while (1)
    {
		Run_DebugLED();
        vTaskDelay(300);
    }
}

