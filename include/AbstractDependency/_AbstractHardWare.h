#pragma once
#include<AbstractDependency/Resource.h>
//注意!只可生成 extern
//1.std::map<enum,std::function<void<ptr>>>
//2.void func(Object obj)


#if __Enable_PIN
    class PIN;
    enum class PIN_Mode;
    
    namespace Override{
        extern std::map<PIN_Mode,std::function<void(PIN*)>> PINPrototypes;

        void GPIOx_PreEnable(uint32_t GPIOx);
        
        void GPIOx_PreDisable(uint32_t GPIOx);
    }
#endif


#if __Enable_SystemClock
    class SystemClock;
    enum class Clock_Speed;

    namespace Override{
        //实现Clock映射初始化
        extern std::map<Clock_Speed,std::function<void(void)>> ClockPrototypes;

        void Delay_Prototype(uint32_t us);
    }

    
#endif



#if __Enable_Uart

    class Peripheral_UART;

    namespace Override{
        //映射Uart回调函数
        extern std::vector<std::function<void(char)>> UartCallback;

        void Uartx_PreEnable(Peripheral_UART* Uart);

        void Uartx_PreDisable(Peripheral_UART* Uart);

        void Uart_Send(Peripheral_UART* Uart,u_char* chr_ptr,unsigned int size,unsigned int *ptr);
    
        void Uart_Close(Peripheral_UART* Uart);

        void Uart_Open(Peripheral_UART* Uart);
    }

#endif


#if __Enable_DCMI

    class Peripheral_DCMI;

    namespace Override{

        void DCMI_Init();

        void DCMI_Enable();

        void DCMI_Disable();
    }

#endif

#if __Enable_TIM

    class Peripheral_TIM;

    namespace Override{

        extern std::vector<std::function<void(void)>> TIMCallback;

        void TIMx_PreEnable(Peripheral_TIM* TIM);

        void TIMx_PreDisable(Peripheral_TIM* TIM);
    }

#endif

#if __Enable_PWM

    class PWM;

    namespace Override{

        void PWMx_PreEnable(PWM* PWM);

        void PWMx_PreDisable(PWM* PWM);
    }

#endif