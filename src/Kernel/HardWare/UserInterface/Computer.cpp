#include<HardWare/UserInterface/Modules/Computer.h>
#include<AbstractDependency/_AbstractHardWare.h>


#if __Enable_Uart

namespace HardWare{

    Computer::Computer(uint32_t Uartx,uint32_t Bound):IO_Uart(Uartx,Bound){

    }

}

#endif

