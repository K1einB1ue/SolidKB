#pragma once
#include<Kernel/HardWare/WireProtocol/I2C_Component.h>

#if __Enable_PIN&&__Enable_SystemClock

namespace HardWare{
    class MPU6050:public I2C_Component{
        enum class Gyro_Fsr:u_char{
            Fsr_250dps  =0b10001,
            Fsr_500dps  =0b10010,
            Fsr_1000dps =0b10100,
            Fsr_2000dps =0b11000,
        };
        enum class Accel_Fsr:u_char{
            Fsr_2g      =0b0001,
            Fsr_4g      =0b0010,
            Fsr_8g      =0b0100,
            Fsr_16g     =0b1000,
        };

        private:
        uint32_t Cnt=0;
        void WeakUp();
        void ID_Check();
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
        void Set_Gyro_Fsr(Gyro_Fsr Fsr);
        //设置MPU6050加速度传感器满量程范围
        void Set_Accel_Fsr(Accel_Fsr Fsr);
        //设置MPU6050的数字低通滤波器
        void Set_LPF(u_short Lpf);
        //设置MPU6050的采样率(4~1000)
        void Set_Rate(u_short Rate);

        void Refresh_Temperature();
        void Refresh_Gyroscope();
        void Refresh_Accelerometer();
        void Refresh(uint32_t Div);
        void Refresh_KalmanFilter(uint32_t Div);
    };



}

#endif