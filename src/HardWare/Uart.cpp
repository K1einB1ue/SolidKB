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
    this->DefaultSend(Info);
    this->Open();
}
void Uart::NonReciveSend(std::string Info){
    this->Close();
    this->DefaultSend(Info);
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

void Uart::DefaultSend(std::string Info){
    Override::Uart_Send(this,(u_char*)Info.c_str(),Info.size());
}

void Uart::Recive(u_char* chr_ptr,unsigned int size){
    Override::Uart_Recv(this,chr_ptr,size);
}

void Uart::Recive(u_char* chr_ptr){
    Override::Uart_Recv(this,chr_ptr,1);
}

u_char Uart::Recive(){
    u_char chr;
    Override::Uart_Recv(this,&chr,1);
    return chr;
}





IO_Uart::IO_Uart(uint32_t Uartx,uint32_t Bound):Uart(Uartx,Bound),IOAbstract(){

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

