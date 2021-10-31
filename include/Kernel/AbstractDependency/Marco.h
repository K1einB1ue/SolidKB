#pragma once
#include"./AbstractConfig.h"
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


#define __Match__ true


// #define TPARAMS(n) TPARAMSX(n,T)
// #define TPARAMSX(n,t) REPEAT(n,TPARAM,TPARAM_END,t)
// #define TPARAM(n,t) typename t##n,
// #define TPARAM_END(n,t) typename t##n
// #define REPEAT(n,m,l,p) APPEND(RAPEAT_,DEC(n))(m,l,p) APPEND(LAST_REPEAT_,n)(l,p)
// #define APPEND( x, y ) APPEND1(x,y)
// #define APPEND1( x, y ) x ## y
// #define DEC(n) APPEND(CNTDEC_, n)
// #define CNTDEC_1 0
// #define REPEAT_0(m,l,p)
// #define LAST_REPEAT_1(m,p) m(1,p)
// #define TPARAM_END(n,t) typename t##n



// template< typename R,TPARAMS(n) >
// struct test{};

#define DEFSELS(x,y) using _##x = _##y
#define DEFSEL(x)enum class _##x:u_char
#define USESEL(x)(u_char)_##x


#define BIT7 0b10000000
#define BIT6 0b01000000
#define BIT5 0b00100000
#define BIT4 0b00010000
#define BIT3 0b00001000
#define BIT2 0b00000100
#define BIT1 0b00000010
#define BIT0 0b00000001

#define DEFREG  enum class REG:u_char
#define USEREG  (u_char)REG
#define DEFDAT  enum class DAT:u_char
#define USEDAT  (u_char)DAT
#define DEFCMD  enum class CMD:u_char
#define USECMD  (u_char)CMD