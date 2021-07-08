#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<Abstract/IOAbstract.h>

class Peripheral_UART{
    private:
    std::function<void(char*,int)>* Callback=nullptr;
    public:

    uint32_t Bound;
    uint32_t Uartx;

    Peripheral_UART(uint32_t Uartx,uint32_t Bound);
    virtual ~Peripheral_UART();
    void BindCallback(std::function<void(char*,int)> Callback);

    //用于提前绑定函数
    void Enable();
    void Open();
    void Close();

    void DefaultSend(std::string Info);
    u_char RX_Buffer[20];
    virtual void NonReciveSend(std::string Info);
    virtual void Send(std::string Info);

    
    void Recive(u_char* chr_ptr,unsigned int size);
    void Recive(u_char* chr_ptr);
    u_char Recive();
};


class IO_Uart:public Peripheral_UART,public IOAbstract{
    public:
    IO_Uart(uint32_t Uartx,uint32_t Bound);
    virtual ~IO_Uart();

    protected:
    virtual void Send_char(u_char chr);
    virtual void Recv_char(u_char* chr_ptr);
    virtual void Pre_Send();
    virtual void Pre_Recv();
};