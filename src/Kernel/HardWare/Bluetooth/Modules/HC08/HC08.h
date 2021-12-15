#pragma once
#include"../../Common.hpp"

#if __Enable_Uart

namespace HardWare{
    namespace HC_Modules{
        
        class HC_08:protected Peripheral_UART{
            public:
            DecoderContainer<char> BluetoothDecoder;
            
            HC_08(uint32_t Uartx,uint32_t Bound);

            void BluetoothSend(const std::string &Info,unsigned int* ptr);
        };
    }
    
    namespace HC_Factories{
        class HC_08_Factory:protected Peripheral_UART{
            public:
            HC_08_Factory(uint32_t Uartx,uint32_t Bound);

            void Init(std::string Name,HC::ROLE Role,uint32_t Bound);
        };
    }
}

#endif