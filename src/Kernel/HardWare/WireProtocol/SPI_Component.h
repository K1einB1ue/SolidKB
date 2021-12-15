#pragma once
#include"../Peripheral/Peripheral_PIN.h"

#if __Enable_PIN

#define SPI_PIN_Pack        uint32_t MOSI_GPIOx,uint32_t MOSI_PINx,\
                            uint32_t MISO_GPIOx,uint32_t MISO_PINx,\
                            uint32_t SCK_GPIOx,uint32_t SCK_PINx,\
                            uint32_t CS_GPIOx,uint32_t CS_PINx


#define SPI_PIN_Data        MOSI_GPIOx,MOSI_PINx,\
                            MISO_GPIOx,MISO_PINx,\
                            SCK_GPIOx,SCK_PINx,\
                            CS_GPIOx,CS_PINx

class SPI_Component{
    private:
        void        __SPI_Mode(bool CPOL,bool CPHA);
        void        __SPI_CS_Active(bool CS);

        void      Fast_SPI_Start_Mode0();
        void      Fast_SPI_Start_Mode1();
        void      Fast_SPI_Start_Mode2();
        void      Fast_SPI_Start_Mode3();

        void      Fast_SPI_W_Mode0(u_char txd);
        void      Fast_SPI_W_Mode1(u_char txd);
        void      Fast_SPI_W_Mode2(u_char txd);
        void      Fast_SPI_W_Mode3(u_char txd);

        u_char    Fast_SPI_R_Mode0();
        u_char    Fast_SPI_R_Mode1();
        u_char    Fast_SPI_R_Mode2();
        u_char    Fast_SPI_R_Mode3();


        

        bool      CS_Acitve=false;
        PIN       MOSI,MISO,SCK,CS;

    public:   

        enum class SPI_type{
            I,O,IO
        };
        
        struct SPI_Detail{
            bool CPOL,CPHA,CS_Active;
        };
        
        
        std::function<void(void)>       Start=nullptr;
        std::function<void(u_char)>     Send_Byte=nullptr;
        std::function<u_char(void)>     Read_Byte=nullptr;   
        void                            End();

        SPI_Component(SPI_PIN_Pack,SPI_type type,const SPI_Detail &detail);

        virtual     ~SPI_Component();
        
        u_char      Read_Reg(u_char reg);  
        void        Read_Reg(u_char reg,u_char count,u_char *dest);
        void        Send_Reg(u_char reg,u_char txd);
        void        Send_Reg(u_char reg,u_char count,u_char *sour);
        void        Send_Len(u_char len,u_char *buf);
        void        Send_Single(u_char txd);
};  //class SPI_Component

#endif