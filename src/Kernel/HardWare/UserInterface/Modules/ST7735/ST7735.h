#pragma once
#include"../../Common.hpp"

#if __Enable_PIN&&__Enable_SystemClock

namespace HardWare{
    class ST7735 :public SPI_Component,public SolidGL::Interface<SolidGL::Draw::RGB565>{
        private:
        PIN RES,DC,BLK;
        void TFTScreen_Dat(u_char txd);
        void TFTScreen_Cmd(u_char txd);
        public:      
        ST7735(
            uint32_t SCL_GPIOx,uint32_t SCL_PINx,
            uint32_t SDA_GPIOx,uint32_t SDA_PINx,
            uint32_t RES_GPIOx,uint32_t RES_PINx,
            uint32_t DC_GPIOx,uint32_t DC_PINx,
            uint32_t CS_GPIOx,uint32_t CS_PINx,
            uint32_t BLK_GPIOx,uint32_t BLK_PINx
        );
        virtual ~ST7735()=default;
        virtual void RecRender(RenderInterface &renderInterface);
    };
    
}

#endif