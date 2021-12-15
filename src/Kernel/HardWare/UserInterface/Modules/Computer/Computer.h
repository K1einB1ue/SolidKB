#pragma once
#include"../../Common.hpp"

#if __Enable_Uart

namespace HardWare{
    //电脑串口
    //Type:[X]
    class Computer:public Peripheral_UART{
        public:
        Computer(uint32_t Uartx,uint32_t Bound);
    };

}

#endif

