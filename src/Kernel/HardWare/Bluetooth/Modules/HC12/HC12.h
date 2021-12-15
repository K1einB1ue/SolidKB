#pragma once
#include"../../Common.hpp"

#if __Enable_Uart&&__Enable_SystemClock

namespace HardWare{
        namespace HC_Modules{
        
        class HC_12:protected Peripheral_UART,protected DecoderContainer<char>{
            private:
            PIN SET;
            bool Wait();
            bool ATmode=false;
            HC::State State=HC::State::NONE;

            u_char Channel=0;
            HC::FUx FuxState=HC::FUx::None;
            u_char Power=0;

            public:
            DecoderContainer<char> BluetoothDecoder;
            
            HC_12(uint32_t Uartx,uint32_t SET_GPIOx,uint32_t SET_PINx);
            void StartAT();
            void EndAT();
            void SetFUx(HC::FUx fux);
            void SetChannel(u_char channel);
            void SetPower(u_char power);
            void BluetoothSend(const std::string &Info);
        };
    }
}

#endif