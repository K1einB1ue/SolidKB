#pragma once
#include<HardWare/Bluetooth/Common.hpp>

#if __Enable_Uart

namespace HardWare{
        namespace HC_Modules{
        
        class HC_08:protected Peripheral_UART{
            public:
            DecoderContainer<char> BluetoothDecoder;
            
            HC_08(uint32_t Uartx);

            void BluetoothSend(const std::string &Info,unsigned int* ptr);
        };
    }
}

#endif