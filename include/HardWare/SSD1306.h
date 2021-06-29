#pragma once
#include<SoftHardWare/I2C_Component.h>
#include<Abstract/DisplayAbstract.h>

//硬件类需要在初始化系统后被New.
namespace HardWare{
    

    //OLED模块
    //Type:[I2C][SPI]
    class SSD1306:public I2C_Component,public DisplayBITAbstract{
        protected:
        SSD1306(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx);
        std::stack<CMD> CMDs;
        public:
        volatile const bool ON=false;
        virtual ~SSD1306();
        void Open();
        void Close();
        virtual void Refresh();
    };
}
namespace I2C{

    class SSD1306:public HardWare::SSD1306{ 
        public:
            SSD1306(
                uint32_t SDA_GPIOx,
                uint32_t SDA_PINx,
                uint32_t SCL_GPIOx,
                uint32_t SCL_PINx
            );
            virtual ~SSD1306();
            virtual void Refresh();
        
    };

}

namespace SPI{

    class SSD1306:public HardWare::SSD1306{
        private:
            PIN RES,DC,CS;
            void SSD1306_Dat(u_char txd);
            void SSD1306_Cmd(u_char txd);
        public:
            SSD1306(
                uint32_t SDA_GPIOx,
                uint32_t SDA_PINx,
                uint32_t SCL_GPIOx,
                uint32_t SCL_PINx,
                uint32_t RES_GPIOx,
                uint32_t RES_PINx,
                uint32_t DC_GPIOx,
                uint32_t DC_PINx,
                uint32_t CS_GPIOx,
                uint32_t CS_PINx
            );
            virtual ~SSD1306();
            virtual void Refresh();
    };

}