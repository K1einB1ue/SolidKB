#pragma once
#include<HardWare/Peripheral_UART.h>
#include<SoftHardWare/I2C_Component.h>
#include<SoftHardWare/SystemClock.h>


namespace HardWare{
    //测距模块 
    //量程:/5cm~180cm(非常吃反射材料,在最坏情况下为5cm~10cm)
    //Type:[I2C][UART][UART_I2C]
    class TOF10120{
        protected:
        TOF10120();
        public:
        enum class InfoMode{
            UART,
            UART_I2C,
        };
        virtual uint Get_Distance_mm();
        virtual void SetReciveMode(InfoMode mode);
        virtual int  GetOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual uint GetInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual bool GetFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual uint GetMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual u_char GetI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}
#if __Enable_Uart
namespace UART{
    class TOF10120:public Peripheral_UART,public HardWare::TOF10120{
        private:
        enum class RecvCMD{
            Offset,
            Interval,
            Filter,
            MaxRange,
            I2C_Address,
        }RecvCMDs;
        bool Recvflag=false;
        int NumBuffer=0;

        public:
        std::function<void(uint)> DistanceCallBack=nullptr;
        TOF10120(uint32_t Uartx);
        virtual uint Get_Distance_mm();
        virtual void SetReciveMode(InfoMode mode);
        virtual int  GetOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual uint GetInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual bool GetFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual uint GetMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual u_char GetI2C_Address();
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
        virtual uint Get_Distance_mm();
        virtual void SetReciveMode(InfoMode mode);
        virtual int  GetOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual uint GetInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual bool GetFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual uint GetMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual u_char GetI2C_Address();
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
        virtual uint Get_Distance_mm();
        virtual void SetReciveMode(InfoMode mode);
        virtual int  GetOffset_mm();
        virtual void SetOffset_mm(int offset);
        virtual uint GetInterval_ms();
        virtual void SetInterval_ms(uint interval);
        virtual bool GetFilter_en();
        virtual void SetFilter_en(bool enable);
        virtual uint GetMaxRange_mm();
        virtual void SetMaxRange_mm(uint maxrange);
        virtual u_char GetI2C_Address();
        virtual void SetI2C_Address(u_char Address);
    };
}

#endif
