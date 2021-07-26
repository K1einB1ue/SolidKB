#pragma once
#include<SoftHardWare/SPI_Component.h>


namespace HardWare{
    class ADXL345:protected SPI_Component{
        
        private:
        enum class Reg:u_char{
            R_DEVID                 =0x00,      //设备ID,默认状态下复位为:0b11100101
            RW_THRESH_TAP           =0x1D,      //敲击状态触发阈值
            RW_OFSX                 =0x1E,      //X轴偏移
            RW_OFSY                 =0x1F,      //Y轴偏移
            RW_OFSZ                 =0x20,      //Z轴偏移
            RW_DUR                  =0x21,      //敲击持续时间
            RW_Latent               =0x22,      //敲击延迟
            RW_Windowed             =0x23,      //敲击窗口
            RW_THRESH_ACT           =0x24,      //活动阈值
            RW_THRESH_INACT         =0x25,      //静止阈值
            RW_TIME_INACT           =0x26,      //静止时间
            RW_ACT_INACT_CTL        =0x27,      //轴使能控制活动和静止检测
            RW_THRESH_FF            =0x28,      //自由落体阈值
            RW_TIME_FF              =0x29,      //自由落体时间
            RW_TPA_AXES             =0x2A,      //单击/双击轴控制
            R_ACT_TAP_STATUS        =0x2B,      //单击/双击源
            RW_BW_RATE              =0x2C,      //数据速率及功率模式控制
            RW_POWER_CTL            =0x2D,      //省电特性控制
            RW_INT_ENABLE           =0x2E,      //中断使能控制
            RW_INT_MAP              =0x2F,      //中断映射控制
            R_INT_SOURCE            =0x30,      //中断源
            RW_DATA_FORMAT          =0x31,      //数据格式控制
            R_DATAX0                =0x32,      //X轴数据0
            R_DATAX1                =0x33,      //X轴数据1
            R_DATAY0                =0x34,      //Y轴数据0
            R_DATAY1                =0x35,      //Y轴数据1
            R_DATAZ0                =0x36,      //Z轴数据0
            R_DATAZ1                =0X37,      //Z轴数据1
            RW_FIFO_CTL             =0x38,      //FIFO控制
            R_FIFO_STATUS           =0x39       //FIFO状态
        };   
        
        public:

        ADXL345(
            uint32_t SDA_GPIOx  ,uint32_t SDA_PINx, 
            uint32_t SDO_GPIOx  ,uint32_t SDO_PINx,
            uint32_t SCK_GPIOx  ,uint32_t SCK_PINx,
            uint32_t CS_GPIOx   ,uint32_t CS_PINx
        );

        ~ADXL345();
        
        
    };
}