#pragma once
#include<HardWare/Peripheral_PIN.h>



class SCCB_Component{
    public:
        PIN SDA,SCL;
        SCCB_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx);
        virtual ~SCCB_Component();
    protected:
        void    Start();
        void    Stop();
        bool    Send_Byte(u_char txd);
        u_char  Read_Byte();    
        void    NAck();       
        bool    Send_Reg(u_char add,u_char reg,u_char txd);
        u_char  Read_Reg(u_char add,u_char reg);
};