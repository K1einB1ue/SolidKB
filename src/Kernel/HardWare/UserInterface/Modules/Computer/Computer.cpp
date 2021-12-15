#include"./Computer.h"

#if __Enable_Uart

namespace HardWare{

    Computer::Computer(uint32_t Uartx,uint32_t Bound):Peripheral_UART(Uartx,Bound){

    }

}

#endif

