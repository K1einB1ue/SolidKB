#include<AbstractDependency/_AbstractHardWare.h>
#include<SolidKernel.h>

#define __Implement_Code__ static_assert(false,"No Implement");

#ifdef __ANY_CHIP__ 
    #if __Enable_PIN
        std::map<PIN_Mode,std::function<void(PIN*)>> Override::PINPrototypes{
            {PIN_Mode::Fast,[](PIN* PIN){__Implement_Code__}},
            {PIN_Mode::FastPullUp,[](PIN* PIN){__Implement_Code__}}
        };
        
        void Override::GPIOx_PreEnable(uint32_t GPIOx){__Implement_Code__}

        void Override::GPIOx_PreDisable(uint32_t GPIOx){__Implement_Code__}
    #endif

    #if __Enable_SystemClock
        std::map<Clock_Speed,std::function<void(void)>> Override::ClockPrototypes{
            {Clock_Speed::HighSpeed,[](){__Implement_Code__}},
        };

        void Override::Delay_Prototype(uint32_t us){__Implement_Code__};
    #endif

    #ifdef __Enable_Uart
        u_char Uart_RxBuffer[CFG_Uart_Size][CFG_Uart_Buf_Size];
        
        void Override::Uartx_PreEnable(Peripheral_UART* Uart){__Implement_Code__}

        void Override::Uartx_PreDisable(Peripheral_UART* Uart){__Implement_Code__}
    
        std::vector<std::function<void(char)>> Override::UartCallback(CFG_Uart_Size);

        void Override::Uart_Close(Peripheral_UART* Uart){__Implement_Code__}

        void Override::Uart_Open(Peripheral_UART* Uart){__Implement_Code__}

        void Override::Uart_Send(Peripheral_UART* Uart,u_char* chr_ptr,unsigned int size,unsigned int *ptr){__Implement_Code__}    
    #endif


    #ifdef __Enable_DCMI
        std::vector<std::function<void(void)>> Override::DCMICallback(CFG_DCMI_Size);

        void Override::DCMIx_PreEnable(Peripheral_DCMI* Peripheral_DCMI){__Implement_Code__}

        void Override::DCMIx_Wrok(Peripheral_DCMI* Peripheral_DCMI){__Implement_Code__}

        void Override::DCMIx_Stop(Peripheral_DCMI* Peripheral_DCMI){__Implement_Code__}

        void Override::DCMIx_PreDisable(Peripheral_DCMI* Peripheral_DCMI){__Implement_Code__}
    #endif

    #ifdef __Enable_TIM
        std::vector<std::function<void(void)>> Override::TIMCallback(CFG_TIM_Size);

        void Override::TIMx_PreEnable(Peripheral_TIM* TIM){__Implement_Code__}

        void Override::TIMx_PreDisable(Peripheral_TIM* TIM){__Implement_Code__}
    #endif

    #ifdef __Enable_PWM
        ResourcePack<CFG_PWM_Size> Override::PWMPack={};

        void Override::PWMx_PreEnable(PWM* PWM){__Implement_Code__}

        void Override::PWMx_PreDisable(PWM* PWM){__Implement_Code__}
    #endif

    #if __Enable_Encoder
        void Override::Encoderx_PreEnable(Peripheral_Encoder* Encoder){__Implement_Code__}
        
        void Override::ResetCounter(Peripheral_Encoder* Encoder){__Implement_Code__}

        void Override::Encoderx_PreDisable(Peripheral_Encoder* Encoder){__Implement_Code__}
    #endif
#endif
