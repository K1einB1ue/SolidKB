#include<HardWare/Computer.h>
#include<AbstractDependency/_AbstractHardWare.h>

namespace HardWare{

    Computer::Computer(uint32_t Uartx,uint32_t Bound):Uart(Uartx,Bound){}

    void Computer::SetIO_PUT(){
        IO::PUT=[&](int chr){
            this->Send(std::to_string(chr));
        };
    }

    void Computer::SetIO_GET(){
        IO::GET=[&](u_char* chr_a){

        };
    }

}


