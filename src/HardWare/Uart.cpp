#include<HardWare/Uart.h>
#include<AbstractDependency/_AbstractHardWare.h>


Uart::Uart(uint32_t Uartx,uint32_t Bound){
    this->Uartx=Uartx;
    this->Bound=Bound;
    this->Callback=&Override::UartOccupation[this->Uartx].second;
    this->Enable();
}

Uart::~Uart(){
    
}

void Uart::Enable(){
    Override::Uartx_PreEnable(this);
}
void Uart::Send(std::string Info){
    this->Close();
    Override::Uart_Send(this,Info);
    this->Open();
}
void Uart::NonReciveSend(std::string Info){
    this->Close();
    Override::Uart_Send(this,Info);
}
void Uart::Open(){
    Override::Uart_Open(this);
}
void Uart::Close(){
    Override::Uart_Close(this);
}

void Uart::BindCallback(std::function<void(char*,int)> Callback){
    *this->Callback=Callback;
}
