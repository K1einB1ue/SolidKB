#pragma once
#include<AbstractDependency/__AbstractDependency.h>


class Usart{
    private:
    std::function<void(char*,int)>* Callback=nullptr;
    public:

    uint32_t Bound;
    uint32_t Usartx;

    Usart(uint32_t Usartx,uint32_t Bound);
    ~Usart();
    void BindCallback(std::function<void(char*,int)> Callback);

    //用于提前绑定函数
    void Enable();
    void Open();
    void Close();
    u_char RX_Buffer[20];
    virtual void NonReciveSend(std::string Info);
    virtual void Send(std::string Info);
};