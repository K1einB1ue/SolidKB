#pragma once
#include<HardWare/Peripheral_UART.h>
#include<SoftHardWare/SystemClock.h>

#if __Enable_Uart

namespace HardWare{
    //声音合成模块(有点小拉跨说实话)
    //Type:[X]
    class SYN6288:public Peripheral_UART{
        public:
        SYN6288(uint32_t Uartx);
        virtual void Send(std::string Info);
        virtual void NonReciveSend(std::string Info);

        void NoUTF8_Send(std::string Info);
        void NoUTF8_NonReciveSend(std::string Info);
    };
}


#endif
