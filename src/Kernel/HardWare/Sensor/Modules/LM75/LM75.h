#pragma once
#include"../../Common.hpp"

#if __Enable_PIN&&__Enable_SystemClock

namespace HardWare{

    class LM75:protected I2C_Component{
        public:
        LM75(I2C_PIN_Pack);

        float getTemperature();
    };
}

#endif