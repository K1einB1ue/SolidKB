#pragma once
#include<AbstractDependency/__AbstractDependency.h>



class Uart{
    public:

    uint32_t Bound;
    uint32_t Uartx;

    Uart(uint32_t Uartx,uint32_t Bound);
    ~Uart();
    
    u_char RX_Buffer[20];
    void Send(std::string Info);
};
