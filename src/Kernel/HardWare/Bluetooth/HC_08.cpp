#include<HardWare/Bluetooth/Modules/HC_08.h>


#if __Enable_Uart

namespace HardWare{
    namespace HC_Modules{
        

        HC_08::HC_08(uint32_t Uartx,uint32_t Bound):Peripheral_UART(Uartx,Bound){
            this->BluetoothDecoder.Set_Container_Size(200);
            this->BindCallback([&](char chr){
                this->BluetoothDecoder.StreamIn(chr);
            });
        }

        void HC_08::BluetoothSend(const std::string &Info,unsigned int* ptr){
            this->Send(Info,ptr);
        }


    }
}

#endif