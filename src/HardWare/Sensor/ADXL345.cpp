#include<HardWare/Sensor/Modules/ADXL345.h>
#include<SoftHardWare/SystemClock.h>

#if __Enable_PIN&&__Enable_SystemClock

enum class RW_DATA_FORMAT:u_char{

};

namespace HardWare{

    ADXL345::ADXL345(
        uint32_t SDA_GPIOx  ,uint32_t SDA_PINx, 
        uint32_t SDO_GPIOx  ,uint32_t SDO_PINx,
        uint32_t SCK_GPIOx  ,uint32_t SCK_PINx,
        uint32_t CS_GPIOx   ,uint32_t CS_PINx
    ):SPI_Component(SDA_GPIOx,SDA_PINx,SDO_GPIOx,SDO_PINx,SCK_GPIOx,SCK_PINx,CS_GPIOx,CS_PINx){
        __SPI_CS_Active(0);
        __SPI_Mode(1,1);
        Debug_StartBlock("Init");
        if(this->Read_Reg((u_char)Reg::R_DEVID,0x01)==0b11100101){
            Debug_Info("Ok");
        }else{
            Debug_Warning("Fail");
        }
        this->Send_Reg((u_char)Reg::RW_DATA_FORMAT  ,0x0B);   //测量范围,正负16g，13位模式
        this->Send_Reg((u_char)Reg::RW_BW_RATE      ,0x08);   //速率设定为12.5 参考pdf13页
        this->Send_Reg((u_char)Reg::RW_POWER_CTL    ,0x08);   //选择电源模式   参考pdf24页
        this->Send_Reg((u_char)Reg::RW_INT_ENABLE   ,0x80);   //使能 DATA_READY 中断
        this->Send_Reg((u_char)Reg::RW_OFSX         ,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
        this->Send_Reg((u_char)Reg::RW_OFSY         ,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
        this->Send_Reg((u_char)Reg::RW_OFSZ         ,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAX0,0x01)));
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAX1,0x01)));
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAY0,0x01)));
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAY1,0x01)));
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAZ0,0x01)));
        Debug_Info(std::to_string(this->Read_Reg((u_char)Reg::R_DATAZ1,0x01)));

        Debug_EndBlock();
    }


    ADXL345::~ADXL345(){
        

    }

}

#endif