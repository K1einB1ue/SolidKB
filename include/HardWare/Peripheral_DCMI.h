#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<SoftHardWare/PIN.h>

namespace HardWare{
    class Peripheral_DCMI{
        private:
        PIN D0,D1,D2,D3,D4,D5,D6,D7,VSYNC,HREF,PCLK;
        public:
        static std::function<void(void)> DCMI_Callback;
        Peripheral_DCMI();
        ~Peripheral_DCMI();
        void EnableDMA();
        void DisableDMA();
    };
};