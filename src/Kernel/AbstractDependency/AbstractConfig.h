#pragma once

#include"../Interface/STM32F407ZGT/STM32F407ZGT.h"

#define __Enable_Debug 1
#define __Enable_Resource 1
#define StaticDebugMode 0


#ifdef CHIP_SELECT

    #define __Enable_SystemClock 1

    #if CFG_GPIO_Size&&CFG_PIN_Size
        #define __Enable_PIN 1
    #endif

    #if CFG_Uart_Size
        #define __Enable_Uart 1
    #endif

    #if CFG_DCMI_Size
        #define __Enable_DCMI 1
    #endif

    #if CFG_TIM_Size
        #define __Enable_TIM 1
    #endif

    #if CFG_PWM_Size
        #define __Enable_PWM 1
    #endif

    #if CFG_Encoder_Size
        #define __Enable_Encoder 1
    #endif

    #if CFG_Core_Size
        #define __Enable_Core 1
    #endif

#else
    #error The chip has not been selected
#endif




