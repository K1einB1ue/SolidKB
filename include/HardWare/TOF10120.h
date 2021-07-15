#pragma once
#include<HardWare/Peripheral_UART.h>
#include<SoftHardWare/I2C_Component.h>
#include<SoftHardWare/SystemClock.h>


namespace HardWare{
    //测距模块 
    //量程:/5cm~180cm(非常吃反射材料,在最坏情况下为5cm~10cm)
    //Type:[I2C][UART][UART_I2C]
    class TOF10120:protected DecoderContainer<char,20>{
        protected:
        TOF10120();
        public:  
        enum class InfoMode{
            None,
            UART,
            UART_I2C,
        };
        uint            distance=0;
        int             offset=0;
        uint            interval=0;
        bool            enable=0;
        uint            maxrange=0;
        u_char          Address=0;
        InfoMode        mode=InfoMode::None;
        std::function<void(uint)> DistanceCallBack=nullptr;
        virtual void RefDistance_mm();
        virtual void RefReciveMode();
        virtual void SetReciveMode(InfoMode mode);
        virtual void RefOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual void RefInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual void RefFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual void RefMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual void RefI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}
#if __Enable_Uart
namespace UART{
    class TOF10120:public Peripheral_UART,public HardWare::TOF10120{
        public:
        
        TOF10120(uint32_t Uartx);
        virtual void RefDistance_mm();
        virtual void RefReciveMode();
        virtual void SetReciveMode(InfoMode mode);
        virtual void RefOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual void RefInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual void RefFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual void RefMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual void RefI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}
#endif

#if __Enable_PIN

namespace I2C{
    class TOF10120:public I2C_Component,public HardWare::TOF10120{
        public:
        TOF10120(
            uint32_t SDA_GPIOx,uint32_t SDA_PINx,
            uint32_t SCL_GPIOx,uint32_t SCL_PINx
        );
        virtual void RefDistance_mm();
        virtual void RefReciveMode();
        virtual void SetReciveMode(InfoMode mode);
        virtual void RefOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual void RefInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual void RefFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual void RefMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual void RefI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}

#endif

#if __Enable_PIN&&__Enable_Uart
namespace UART_I2C{
    class TOF10120:public UART::TOF10120,public I2C::TOF10120{
        public:
        TOF10120(
            uint32_t Uartx,
            uint32_t SDA_GPIOx,uint32_t SDA_PINx,
            uint32_t SCL_GPIOx,uint32_t SCL_PINx
        );
        virtual void RefDistance_mm();
        virtual void RefReciveMode();
        virtual void SetReciveMode(InfoMode mode);
        virtual void RefOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual void RefInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual void RefFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual void RefMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual void RefI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}

#endif
