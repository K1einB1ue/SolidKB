#include"./Peripheral_UART.h"
#include"../../AbstractDependency/_AbstractHardWare.h"


Peripheral_UART::Peripheral_UART(uint32_t Uartx,uint32_t Bound){
    this->Uartx=Uartx;
    this->Bound=Bound;
    this->Callback=&Override::UartCallback[this->Uartx];
    this->Enable();
}

Peripheral_UART::~Peripheral_UART(){
    
}

void Peripheral_UART::Enable(){
    Override::Uartx_PreEnable(this);
}
void Peripheral_UART::Send(const std::string &Info,unsigned int *ptr){
    this->Open();
    this->DefaultSend(Info,ptr);
}
void Peripheral_UART::NonReciveSend(const std::string &Info,unsigned int *ptr){
    this->Close();
    this->DefaultSend(Info,ptr);
}
void Peripheral_UART::Send(const std::string &Info){
    this->Open();
    this->DefaultSend(Info);
}
void Peripheral_UART::NonReciveSend(const std::string &Info){
    this->Close();
    this->DefaultSend(Info);
}
void Peripheral_UART::Open(){
    Override::Uart_Open(this);
}
void Peripheral_UART::Close(){
    Override::Uart_Close(this);
}

void Peripheral_UART::BindCallback(std::function<void(char)> Callback){
    *this->Callback=Callback;
}

void Peripheral_UART::DefaultSend(const std::string &Info,unsigned int *ptr){
    Override::Uart_Send(this,(u_char*)Info.c_str(),Info.size(),ptr);
}

void Peripheral_UART::DefaultSend(const std::string &Info){
    unsigned int temp=0;
    Override::Uart_Send(this,(u_char*)Info.c_str(),Info.size(),&temp);
}







