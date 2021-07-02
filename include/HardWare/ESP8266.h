#pragma once
#include<HardWare/Uart.h>
#include<SoftHardWare/SystemClock.h>

namespace HardWare{
    //WIFI模块
    //Type:[X]
    class ESP8266:public Uart{
        public:
        ESP8266(uint32_t Uartx);
    };

}

