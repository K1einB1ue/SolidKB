#include"./LM75.h"

#if __Enable_PIN&&__Enable_SystemClock


DEFREG{
    //温度寄存器 R
    //包含2个8位的数据字节
    Temp        = 0x00,
    //配置寄存器 R/W
    //包含1个8位的数据字节
    Conf        = 0x01,
    //滞后寄存器 R/W
    //包含2个8位的数据字节,用于保存之后Thyst限制值,默认为75℃
    Thyst       = 0x02,
    //过热关断阈值寄存器 R/W
    //包含2个8位的数据字节,用于保存过热关断Tos限制值,默认为80℃
    Tos         = 0x03,
};

namespace HardWare{
    LM75::LM75(I2C_PIN_Pack):I2C_Component(I2C_PIN_Data){
        this->setAddress(0x90>>1);
    }

    float LM75::getTemperature(){
        u_char buffer[2];
        this->Read_Len(USEREG::Temp,2,buffer);
        //this->Read_Len_Directly(2,buffer);
        u_int16_t temputerature_16=buffer[0]<<8;
        temputerature_16+=buffer[1];
        temputerature_16>>=5;
        if(temputerature_16&0x0400){
            return -(~(temputerature_16&0x03FF)+1)*0.125;
        }else{
            return (float)temputerature_16*0.125;
        }
    }
}

#endif