#pragma once
#include<HardWare/Peripheral_PIN.h>

#if __Enable_PIN&&__Enable_SystemClock
class I2C_Component{
    private:
        uint TimeWait=1;
    public:      
        I2C_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx);
        I2C_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx,bool __NoNeedPullUp__);
        u_char address=0;
        virtual ~I2C_Component();
    protected:
        PIN SDA,SCL;
        void    __FrequencyInit(uint frequency);
        void    Start();
        void    Stop();
        void    Send_Byte(u_char txd);
        u_char  Read_Byte(bool ack);    
        u_char  Read_Byte();

        void    Fast_Send_Byte(u_char txd);
        u_char  Fast_Read_Byte(bool ack);    
        u_char  Fast_Read_Byte();

        bool    Wait_Ack();
        void    Fast_Ack();
        void    Ack();
        void    NAck();       
        bool    Send_Reg(u_char reg,u_char txd);
        bool    Read_Len(u_char reg,u_char len,u_char *buf);
        u_char  Read_Reg(u_char reg);
};

#endif