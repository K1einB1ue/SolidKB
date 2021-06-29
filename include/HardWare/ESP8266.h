#pragma once
#include<HardWare/Usart.h>
#include<SoftHardWare/SystemClock.h>

namespace HardWare{
    //WIFI模块
    //Type:[X]
    class ESP8266:public Usart{
        public:
        ESP8266(uint32_t Usartx);
    };

}

