#define BSP_LED_EXTERN
#include "../../../Libraries/CMSIS/GD/GD32F10x/Include/gd32f10x.h"

void LED_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
}

void Run_DebugLED(void)
{
    GPIO_OCTL(GPIOC) ^= (uint32_t)GPIO_PIN_10;
}
