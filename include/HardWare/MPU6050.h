#pragma once
#include<SoftHardWare/I2C_Component.h>

namespace HardWare{
    class MPU6050:public I2C_Component{
        enum class Gyro_Fsr:u_char{
            Fsr_250dps,
            Fsr_500dps,
            Fsr_1000dps,
            Fsr_2000dps,
        };
        enum class Accel_Fsr:u_char{
            Fsr_2g,
            Fsr_4g,
            Fsr_8g,
            Fsr_16g,
        };

        public:
        
        struct Gyroscope{
            short gx=0,gy=0,gz=0;
        }Gyroscope_Pack;

        struct Accelerometer{
            short ax=0,ay=0,az=0;
        }Accelerometer_Pack;

        short Temperature=0;

        MPU6050(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx);

        //设置MPU6050陀螺仪传感器满量程范围
        bool Set_Gyro_Fsr(Gyro_Fsr Fsr);
        //设置MPU6050加速度传感器满量程范围
        bool Set_Accel_Fsr(Accel_Fsr Fsr);
        //设置MPU6050的数字低通滤波器
        bool Set_LPF(u_short Lpf);
        //设置MPU6050的采样率(4~1000)
        bool Set_Rate(u_short Rate);

        bool Refresh_Temperature();
        bool Refresh_Gyroscope();
        bool Refresh_Accelerometer();
    };



}