#pragma once

#include<Interface/STM32F407ZGT/STM32F407ZGT.h>

#define __Enable_Debug 1
#define __Enable_Resource 1


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

    #if CFG_Core_Size
        #define __Enable_Core 1
    #endif

#else
    #error The chip has not been selected
#endif
















#define StaticDebugMode 0

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

#if __Enable_Resource
    #if __Enable_PIN
        #define Resource_PIN_Cover(x,y,z)       Resource::PIN_Resource::Cover(x,y,z)
        #define Resource_PIN_Uncover(x,y,z)     Resource::PIN_Resource::Uncover(x,y,z)
        #define Resource_PIN_Check(x,y)         Resource::PIN_Resource::Check(x,y)
    #endif
    #if __Enable_TIM
        #define Resource_TIM_Cover(x,y)         Resource::TIM_Resource::Cover(x,y)
        #define Resource_TIM_Uncover(x,y)       Resource::TIM_Resource::Uncover(x,y)
        #define Resource_TIM_Check(x)           Resource::TIM_Resource::Check(x)
    #endif
    #if __Enable_PWM
        #define Resource_PWM_Cover(x,y)         Resource::PWM_Resource::Cover(x,y)
        #define Resource_PWM_Uncover(x,y)       Resource::PWM_Resource::Uncover(x,y)
        #define Resource_PWM_Check(x)           Resource::PWM_Resource::Check(x)
    #endif
    #if __Enable_DCMI
        #define Resource_DCMI_Cover(x,y)        Resource::DCMI_Resource::Cover(x,y)
        #define Resource_DCMI_Uncover(x,y)      Resource::DCMI_Resource::Uncover(x,y)
        #define Resource_DCMI_Check(x)          Resource::DCMI_Resource::Check(x)
    #endif
    #if __Enable_Uart
        #define Resource_UART_Cover(x,y)        Resource::UART_Resource::Cover(x,y)
        #define Resource_UART_Uncover(x,y)      Resource::UART_Resource::Uncover(x,y)
        #define Resource_UART_Check(x)          Resource::UART_Resource::Check(x)
    #endif
    #if __Enable_Encoder
        #define Resource_Encoder_Cover(x,y)     Resource::Encoder_Resource::Cover(x,y)
        #define Resource_Encoder_Uncover(x,y)   Resource::Encoder_Resource::Uncover(x,y)
        #define Resource_Encoder_Check(x)       Resource::Encoder_Resource::Check(x)
    #endif
#else
    #if __Enable_PIN
        #define Resource_PIN_Cover(x,y,z)       true
        #define Resource_PIN_Uncover(x,y,z)     true
        #define Resource_PIN_Check(x,y)         false
    #endif
    #if __Enable_TIM
        #define Resource_TIM_Cover(x,y)         true
        #define Resource_TIM_Uncover(x,y)       true
        #define Resource_TIM_Check(x)           false
    #endif
    #if __Enable_PWM
        #define Resource_PWM_Cover(x,y)         true
        #define Resource_PWM_Uncover(x,y)       true
        #define Resource_PWM_Check(x)           false
    #endif
    #if __Enable_DCMI
        #define Resource_DCMI_Cover(x,y)        true
        #define Resource_DCMI_Uncover(x,y)      true
        #define Resource_DCMI_Check(x)          false
    #endif
    #if __Enable_Uart
        #define Resource_UART_Cover(x,y)        true
        #define Resource_UART_Uncover(x,y)      true
        #define Resource_UART_Check(x)          false
    #endif
    #if __Enable_Encoder
        #define Resource_Encoder_Cover(x,y)     true
        #define Resource_Encoder_Uncover(x,y)   true
        #define Resource_Encoder_Check(x)       false
    #endif
#endif

#define DEFCOM  enum class __Commands:u_char
#define USECOM (u_char)__Commands
