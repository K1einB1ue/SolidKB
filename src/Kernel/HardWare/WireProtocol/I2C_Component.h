#pragma once
#include"../Peripheral/Peripheral_PIN.h"

#if __Enable_PIN&&__Enable_SystemClock

#define I2C_PIN_Pack    uint32_t SDA_GPIOx,uint32_t SDA_PINx,\
                        uint32_t SCL_GPIOx,uint32_t SCL_PINx

#define I2C_PIN_Data    SDA_GPIOx,SDA_PINx,\
                        SCL_GPIOx,SCL_PINx

#define I2C_PIN_Data_NoPull     SDA_GPIOx,SDA_PINx,\
                                SCL_GPIOx,SCL_PINx,true

class I2C_Component{
    private:
        uint TimeWait=1;
    public:      
        I2C_Component(I2C_PIN_Pack);
        I2C_Component(I2C_PIN_Pack,bool __NoNeedPullUp__);
        void setAddress(u_char address);
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
        bool    Send_Len(u_char len,const u_char *buf);
        bool    Send_Reg(u_char reg,u_char txd);
        bool    Read_Len(u_char reg,u_char len,u_char *buf);
        u_char  Read_Reg(u_char reg);
};

#endif