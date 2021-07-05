#pragma once
#include<SoftHardWare/SCCB_Component.h>
#include<HardWare/Peripheral_DCMI.h>



namespace HardWare{
    class OV7725:public SCCB_Component,public Peripheral_DCMI{
        public:
        enum class Light_Mode{
            Auto,
            Sunny,
            Cloudy,
            Office,
            Home,
            Night,
        };
        PIN SGM,RST;
        OV7725(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx,uint32_t SGM_GPIOx,uint32_t SGM_PINx,uint32_t RST_GPIOx,uint32_t RST_PINx);

        bool Send_Reg_WithDefaultAdress(u_char reg,u_char txd);
        u_char Read_Reg_WithDefaultAdress(u_char reg);

        void Set_Light_Mode(Light_Mode mode);
        void Set_Color_Saturation(int8_t sat);
        void Set_Brightness(int8_t bright);
        void Set_Contrast(int8_t contrast);
        void Set_Special_Effects(u_char eft);
        void Set_Window(u_short width,u_short height,u_char mode);
    };
}