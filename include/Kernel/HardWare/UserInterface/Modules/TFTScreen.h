#pragma once
#include<Kernel/HardWare/WireProtocol/I2C_Component.h>
#include<Kernel/SolidGL/SolidGL_Interface.h>

#if __Enable_PIN&&__Enable_SystemClock

namespace HardWare{
    class TFTScreen :public I2C_Component,public SolidGL::Interface<SolidGL::Draw::RGB565>{
        private:
        PIN RES,DC,BLK;
        void TFTScreen_Dat(u_char txd);
        void TFTScreen_Cmd(u_char txd);
        public:      
        TFTScreen(
            uint32_t SDA_GPIOx,uint32_t SDA_PINx,
            uint32_t SCL_GPIOx,uint32_t SCL_PINx,
            uint32_t RES_GPIOx,uint32_t RES_PINx,
            uint32_t DC_GPIOx,uint32_t DC_PINx,
            uint32_t BLK_GPIOx,uint32_t BLK_PINx
        );
        virtual ~TFTScreen()=default;
        virtual void RecRender(RenderTarget &renderTarget);
    };
}

#endif