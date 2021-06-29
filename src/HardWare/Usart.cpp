#include<HardWare/Usart.h>
#include<AbstractDependency/_AbstractHardWare.h>


Usart::Usart(uint32_t Usartx,uint32_t Bound){
    this->Usartx=Usartx;
    this->Bound=Bound;
    this->Callback=&Override::UsartOccupation[this->Usartx].second;
    this->Enable();
}

Usart::~Usart(){
    
}

void Usart::Enable(){
    Override::Usartx_PreEnable(this);
}
void Usart::Send(std::string Info){
    this->Close();
    Override::Usart_Send(this,Info);
    this->Open();
}
void Usart::NonReciveSend(std::string Info){
    this->Close();
    Override::Usart_Send(this,Info);
}
void Usart::Open(){
    Override::Usart_Open(this);
}
void Usart::Close(){
    Override::Usart_Close(this);
}

void Usart::BindCallback(std::function<void(char*,int)> Callback){
    *this->Callback=Callback;
}
