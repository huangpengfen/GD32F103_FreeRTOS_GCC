#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#ifdef BSP_LED_EXTERN
#    define BSP_LED_EXT
#else
#    define BSP_LED_EXT extern
#endif

BSP_LED_EXT void LED_Init(void);
BSP_LED_EXT void Run_DebugLED(void);

#endif
