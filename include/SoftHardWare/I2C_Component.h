#pragma once
#include<SoftHardWare/PIN.h>


class I2C_Component{
    public:
        PIN SDA,SCL;
        I2C_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx);
        virtual ~I2C_Component();
    protected:
        void    Start();
        void    Stop();
        void    Send_Byte(u_char txd);
        u_char  Read_Byte(bool ack);    
        bool    Wait_Ack();
        void    Fast_Ack();
        void    Ack();
        void    NAck();       
};