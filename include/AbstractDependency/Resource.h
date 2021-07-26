#pragma once
#include<AbstractDependency/__AbstractDependency.h>

namespace Override{
    extern void GPIOx_PreEnable(uint32_t GPIOx);
    extern void GPIOx_PreDisable(uint32_t GPIOx);
}

namespace Resource{
    #if CFG_GPIO_Size&&CFG_PIN_Size
    namespace PIN_Resource{
        extern bool Cover(uint32_t GPIOx,uint32_t PINx,std::string Info);
        extern bool Uncover(uint32_t GPIOx,uint32_t PINx,std::string Info);
        extern bool Check(uint32_t GPIOx,uint32_t PINx);
    }
    #endif

    #if CFG_TIM_Size
    namespace TIM_Resource{
        extern bool Cover(uint32_t TIMx,std::string Info);
        extern bool Uncover(uint32_t TIMx,std::string Info);
        extern bool Check(uint32_t TIMx);
    }
    #endif

    #if CFG_PWM_Size
    namespace PWM_Resource{
        extern bool Cover(uint32_t PWMx,std::string Info);
        extern bool Uncover(uint32_t PWMx,std::string Info);
        extern bool Check(uint32_t PWMx);
    }
    #endif

    #if CFG_DCMI_Size
    namespace DCMI_Resource{
        extern bool Cover(uint32_t DCMIx,std::string Info);
        extern bool Uncover(uint32_t DCMIx,std::string Info);
        extern bool Check(uint32_t DCMIx);
    }
    #endif

    #if CFG_Uart_Size
    namespace UART_Resource{
        extern bool Cover(uint32_t UARTx,std::string Info);
        extern bool Uncover(uint32_t UARTx,std::string Info);
        extern bool Check(uint32_t UARTx);
    }
    #endif
}

