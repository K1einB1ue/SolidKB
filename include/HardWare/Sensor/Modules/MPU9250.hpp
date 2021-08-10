#pragma once
#include<SoftHardWare/I2C_Component.h>

#if __Enable_PIN&&__Enable_SystemClock

namespace HardWare{
    class MPU9250:protected I2C_Component{
        public:
        MPU9250():I2C_Component(){};
        ~MPU9250()=default;
    };
}

#endif