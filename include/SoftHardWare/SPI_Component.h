#pragma once
#include<SoftHardWare/PIN.h>


class SPI_Component{
    private:
        std::function<u_char(u_char)>   SOFT_SPI_RW_Func=nullptr;
        std::function<void(u_char)>     SOFT_SPI_W_Func=nullptr;
        std::function<u_char(void)>     SOFT_SPI_R_Func=nullptr;

        u_char    SOFT_SPI_RW_Mode0(u_char txd);
        u_char    SOFT_SPI_RW_Mode1(u_char txd);
        u_char    SOFT_SPI_RW_Mode2(u_char txd);
        u_char    SOFT_SPI_RW_Mode3(u_char txd);

        void      SOFT_SPI_W_Mode0(u_char txd);
        void      SOFT_SPI_W_Mode1(u_char txd);
        void      SOFT_SPI_W_Mode2(u_char txd);
        void      SOFT_SPI_W_Mode3(u_char txd);

        u_char    SOFT_SPI_R_Mode0();
        u_char    SOFT_SPI_R_Mode1();
        u_char    SOFT_SPI_R_Mode2();
        u_char    SOFT_SPI_R_Mode3();

        void      Fast_SPI_Start_Mode0();
        void      Fast_SPI_Start_Mode1();
        void      Fast_SPI_Start_Mode2();
        void      Fast_SPI_Start_Mode3();

        void      Fast_SPI_W_Type0(u_char txd);
        void      Fast_SPI_W_Type1(u_char txd);

        u_char    Fast_SPI_R_Type0();
        u_char    Fast_SPI_R_Type1();

        

        bool      CS_Acitve=false;
        PIN       MOSI,MISO,SCK,CS;

    protected:
        
        

    public:   
        std::function<void(void)>       Start=nullptr;
        void      End();
        std::function<void(u_char)>     Send_Byte=nullptr;
        std::function<u_char(void)>     Read_Byte=nullptr;   

        SPI_Component(
            uint32_t MOSI_GPIOx,uint32_t MOSI_PINx,
            uint32_t MISO_GPIOx,uint32_t MISO_PINx,
            uint32_t SCK_GPIOx,uint32_t SCK_PINx,
            uint32_t CS_GPIOx,uint32_t CS_PINx);

        virtual ~SPI_Component();
        u_char      SOFT_SPI_RW(u_char txd);
        void        SOFT_SPI_W(u_char txd);
        u_char      SOFT_SPI_R();
        void        __SPI_Mode(bool CPOL,bool CPHA);
        void        __SPI_CS_Active(bool CS);
        u_char      Read_Reg(u_char reg);  
        u_char      Read_Reg(u_char reg,u_char spare);
        void        Send_Reg(u_char reg,u_char txd);

        void        PreRead_Reg(u_char reg);
        u_char      ConRead_Reg(u_char reg);
        u_char      EndRead_Reg();
    
        
};  //class SPI_Component