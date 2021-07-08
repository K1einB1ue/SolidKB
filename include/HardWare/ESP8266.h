#pragma once
#include<HardWare/Peripheral_UART.h>
#include<SoftHardWare/SystemClock.h>

namespace HardWare{
    //WIFI模块
    //Type:[X]
    class ESP8266:public Peripheral_UART{
        public:
        ESP8266(uint32_t Uartx);
    };

}

