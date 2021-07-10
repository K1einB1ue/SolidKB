#pragma once
#include<SoftHardWare/I2C_Component.h>
#include<Abstract/DisplayAbstract.h>

namespace HardWare{
    class AD7705:protected I2C_Component{
        private:
        PIN CS,RST,DRDY;
        void WriteByte(u_char data);
        void Write3Byte(u_int data);
        void WriteReg(u_char regID,u_int regValue);
        u_char ReadByte();
        u_short Read2Byte();
        u_int Read3Byte();
        u_int ReadReg(u_char regID);
        void WaitDRDY();

        public:     
        enum class ADC_Channel{
            Ch1,
            Ch2
        };
        AD7705(
            uint32_t DOUT_GPIOx ,uint32_t DOUT_PINx,
            uint32_t SCL_GPIOx  ,uint32_t SCL_PINx,
            uint32_t CS_GPIOx   ,uint32_t CS_PINx,
            uint32_t RST_GPIOx  ,uint32_t RST_PINx,
            uint32_t DRDY_GPIOx ,uint32_t DRDY_PINx
        );

        void Reset();
        void Sync();
        void CalibSelf(ADC_Channel channel);
        void SystemCalibZero(ADC_Channel channel);
        void SystemCalibFull(ADC_Channel channel);
        u_short ReadChannel1();
        u_short ReadChannel2();
        int Get_Channel1_mV();
        int Get_Channel2_mV();
    };
}