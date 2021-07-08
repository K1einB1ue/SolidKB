#include<HardWare/Peripheral_UART.h>
#include<AbstractDependency/_AbstractHardWare.h>


Peripheral_UART::Peripheral_UART(uint32_t Uartx,uint32_t Bound){
    this->Uartx=Uartx;
    this->Bound=Bound;
    this->Callback=&Override::UartOccupation[this->Uartx].second;
    this->Enable();
}

Peripheral_UART::~Peripheral_UART(){
    
}

void Peripheral_UART::Enable(){
    Override::Uartx_PreEnable(this);
}
void Peripheral_UART::Send(std::string Info){
    this->Close();
    this->DefaultSend(Info);
    this->Open();
}
void Peripheral_UART::NonReciveSend(std::string Info){
    this->Close();
    this->DefaultSend(Info);
}
void Peripheral_UART::Open(){
    Override::Uart_Open(this);
}
void Peripheral_UART::Close(){
    Override::Uart_Close(this);
}

void Peripheral_UART::BindCallback(std::function<void(char*,int)> Callback){
    *this->Callback=Callback;
}

void Peripheral_UART::DefaultSend(std::string Info){
    Override::Uart_Send(this,(u_char*)Info.c_str(),Info.size());
}

void Peripheral_UART::Recive(u_char* chr_ptr,unsigned int size){
    Override::Uart_Recv(this,chr_ptr,size);
}

void Peripheral_UART::Recive(u_char* chr_ptr){
    Override::Uart_Recv(this,chr_ptr,1);
}

u_char Peripheral_UART::Recive(){
    u_char chr;
    Override::Uart_Recv(this,&chr,1);
    return chr;
}





IO_Uart::IO_Uart(uint32_t Uartx,uint32_t Bound):Peripheral_UART(Uartx,Bound),IOAbstract(){

}
IO_Uart::~IO_Uart(){

}
void IO_Uart::Pre_Send(){
    this->Close();
}
void IO_Uart::Pre_Recv(){
    this->Open();
}
void IO_Uart::Send_char(u_char chr){
    Override::Uart_Send(this,&chr,1);
}
void IO_Uart::Recv_char(u_char* chr_ptr){
    Override::Uart_Recv(this,chr_ptr,1);
}

