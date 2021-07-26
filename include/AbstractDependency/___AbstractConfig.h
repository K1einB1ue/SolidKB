#pragma once

#include<Chip_Lib/STM32F407ZG_Dependency.h>



#ifdef CHIP_SELECT

    #define __Enable_SystemClock 1

    #if CFG_GPIO_Size&&(CFG_PIN_Size)
        #define __Enable_PIN 1
    #endif

    #if __Enable_PIN&&(CFG_Uart_Size)
        #define __Enable_Uart 1
    #endif

    #if __Enable_PIN&&__Enable_SystemClock
        #define __Enable_I2C_Component 1
        #define __Enable_SCCB_Component 1
    #endif

    #if __Enable_SCCB_Component&&(CFG_DCMI_Size)
        #define __Enable_DCMI 1
    #endif

    #define __Enable_TIM 1

    #define __Enable_PWM 1

    

#else
    #error The chip has not been selected
#endif

