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
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define COM_TASK_PRIO		2
//�����ջ��С	
#define COM_STK_SIZE 		256  
//������
TaskHandle_t ComTask_Handler;
//������
void com_task(void *pvParameters);

//�������ȼ�
#define MICRO_TASK_PRIO		3
//�����ջ��С	
#define MICRO_STK_SIZE 		256  
//������
TaskHandle_t MicroTask_Handler;
//������
void micro_task(void *pvParameters);


#define    Message_Uart_NUM    4

QueueHandle_t Message_Queue_Uart;	//

SemaphoreHandle_t BinarySemaphore_Analyse; // Pressure Temp
SemaphoreHandle_t BinarySemaphore_Current; // Current

#define FREE(p) myfree((void **)&p)  // ��ֹ�ڴ�й©
void myfree(void ** point)
{
	if(*point != NULL)
	{
    	free(*point);
    	*point = NULL;
	}
}

//--------------------------------------------------------------------------
//����:
//����:
//����:
//--------------------------------------------------------------------------
int main(void)
{
#ifndef DF_RELEASE
    //DBGMCU_CR
    //    ע�����е�DBG_WWDG_STOP��DBG_IWDG_STOPλ,������λ���������ں�ֹͣʱͣ
    //    ֹ���Ź�ʱ��,�ﵽֹͣ���Ź���Ŀ��
    *(unsigned long *)0xe0042004 = 0xFFFFFFFF;
#endif
    SystemInit();
    systick_config();
    COM_init();
    LED_Init();
	
    //������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������

}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���

    //����������Ӧ����
    xTaskCreate((TaskFunction_t )com_task,     	
                (const char*    )"com_task",   	
                (uint16_t       )COM_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )COM_TASK_PRIO,	
                (TaskHandle_t*  )&ComTask_Handler);
    //����΢��������
    xTaskCreate((TaskFunction_t )micro_task,     
                (const char*    )"micro_task",   
                (uint16_t       )MICRO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )MICRO_TASK_PRIO,
                (TaskHandle_t*  )&MicroTask_Handler);


    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//������Ӧ����������
void com_task(void *pvParameters)
{

    while (1)
    {
        Run_DebugLED();
        vTaskDelay(200);
    }
}

//΢���ƴ���������
void micro_task(void *pvParameters)
{
    while (1)
    {
		Run_DebugLED();
        vTaskDelay(300);
    }
}

