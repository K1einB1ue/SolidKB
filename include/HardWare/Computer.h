#pragma once
#include<HardWare/Uart.h>
#include<SoftHardWare/SystemClock.h>

namespace HardWare{
    //电脑串口
    //Type:[X]
    class Computer:public IO_Uart{
        public:
        Computer(uint32_t Uartx,uint32_t Bound);
    };

}


