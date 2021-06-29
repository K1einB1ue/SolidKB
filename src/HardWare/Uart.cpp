#include<HardWare/Uart.h>
#include<AbstractDependency/_AbstractHardWare.h>

Uart::Uart(uint32_t Uartx,uint32_t Bound){
   this->Uartx=Uartx;
   this->Bound=Bound;
}

Uart::~Uart(){
    
}
void Uart::Send(std::string Info){
    Override::Uart_Send(this,Info);
}
