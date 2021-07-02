#pragma once
#include<HardWare/Uart.h>
#include<Abstract/IOAbstract.h>
#include<SoftHardWare/SystemClock.h>

namespace HardWare{
    //电脑回传
    //Type:[X]
    class Computer:public Uart,public IOAbstract{
        public:
        Computer(uint32_t Uartx,uint32_t Bound);
        virtual void SetIO_PUT();
        virtual void SetIO_GET();
    };

}


