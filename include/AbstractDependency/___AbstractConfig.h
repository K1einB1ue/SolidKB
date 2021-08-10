#pragma once

#include<Chip_Lib/STM32F407ZG_Dependency.h>

#define __Enable_Debug 1


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

    #define __Enable_TIM 1

    #define __Enable_PWM 1

    #define __Enable_Encoder 1

#else
    #error The chip has not been selected
#endif

#if __Enable_Debug
    #define Debug_BindCallback(x)               Debug::BindCallback(x);
    #define Debug_InterruptSend(x)              Debug::InterruptSend(x);
    #define Debug_InterruptSendCharPtr(x,y)     Debug::InterruptSend(x,y);
    #define Debug_StaticSend(x)                 Debug::StaticSend(x);
    #define Debug_Error(x)                      Debug::Error(x);
    #define Debug_Warning(x)                    Debug::Warning(x);
    #define Debug_Info(x)                       Debug::Info(x);
    #define Debug_StartDebug(x)                 Debug::StartDebug(x);
    #define Debug_EndDebug(x)                   Debug::EndDebug();
    #define Debug_StartBlock(x)                 Debug::StartBlock(x);
    #define Debug_EndBlock(x)                   Debug::EndBlock();
    #define Debug_EndBlockTitle(x)              Debug::EndBlockTitle(x);
    #define Debug_EndOK(x)                      Debug::EndOK();
    #define Debug_EndFAIL(x)                    Debug::EndFAIL();
#else
    #define Debug_BindCallback(x) 
    #define Debug_InterruptSend(x)
    #define Debug_InterruptSendCharPtr(x,y)
    #define Debug_StaticSend(x)   
    #define Debug_Error(x)                      while(true)
    #define Debug_Warning(x)      
    #define Debug_Info(x)         
    #define Debug_StartDebug(x)   
    #define Debug_EndDebug(x)     
    #define Debug_StartBlock(x)   
    #define Debug_EndBlock(x)     
    #define Debug_EndBlockTitle(x)
    #define Debug_EndOK(x)        
    #define Debug_EndFAIL(x)      
#endif

