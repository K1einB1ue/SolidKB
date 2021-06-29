#pragma once
#include<HardWare/Usart.h>
#include<SoftHardWare/SystemClock.h>



namespace HardWare{
    //声音合成模块(有点小拉跨说实话)
    //Type:[X]
    class SYN6288:public Usart{
        public:
        SYN6288(uint32_t Usartx);
        virtual void Send(std::string Info);
        virtual void NonReciveSend(std::string Info);

        void NoUTF8_Send(std::string Info);
        void NoUTF8_NonReciveSend(std::string Info);
    };
}

