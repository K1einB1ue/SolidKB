#pragma once
#include<AbstractDependency/__AbstractDependency.h>


//注意!只可生成 extern
//1.std::map<enum,std::function<void<ptr>>>
//2.void func(Object obj)


#if __Enable_PIN
    class PIN;
    enum class PIN_Mode;
    
    namespace Override{
        extern std::map<PIN_Mode,std::function<void(PIN*)>> PINPrototypes;
        extern void GPIOx_PreEnable(uint32_t GPIOx);
        extern void GPIOx_PreDisable(uint32_t GPIOx);
    }
#endif


#if __Enable_SystemClock
    class SystemClock;
    enum class Clock_Speed;

    namespace Override{
        //实现Clock映射初始化
        extern std::map<Clock_Speed,std::function<void(void)>> ClockPrototypes;

        extern void Delay_Prototype(uint32_t us);
    }

    
#endif



#if __Enable_Uart

    class Uart;

    namespace Override{

        //映射Usart回调函数
        extern std::vector<std::pair<u_char*,std::function<void(char*,int)>&>> UsartOccupation;
        //映射Uart回调函数
        extern std::vector<std::pair<u_char*,std::function<void(char*,int)>&>> UartOccupation;

        
        //extern void Usartx_PreEnable(Usart* Usart);
        extern void Uartx_PreEnable(Uart* Uart);
       
        //extern void Usartx_PreDisable(Usart* Usart);
        extern void Uartx_PreDisable(Uart* Uart);
        
        //extern void Usart_Send(Usart* Usart,std::string Info);
        extern void Uart_Send(Uart* Uart,std::string Info);

        extern void Uart_Close(Uart* Uart);
        
        extern void Uart_Open(Uart* Uart);
        
        // extern void Usart_Close(Usart* Usart);
        // extern void Usart_Open (Usart* Usart);
        
    }

#endif