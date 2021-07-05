#pragma once
#include<AbstractDependency/__AbstractDependency.h>

class IOAbstract{
    public:
    IOAbstract();
    virtual ~IOAbstract();
    int Printf(const char *fmt,...);
    int Scanf(const char *fmt,...);
    protected:
    virtual void Send_char(u_char chr);
    virtual void Recv_char(u_char* chr_ptr);
    virtual void Pre_Send();
    virtual void Pre_Recv();
};





