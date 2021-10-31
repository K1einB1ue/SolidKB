#pragma once
#include<Kernel/HardWare/WireProtocol/SPI_Component.h>

#if __Enable_PIN&&__Enable_SystemClock
namespace HardWare{
    class MPU9250:public SPI_Component{
        private:
        void Send_Reg_AK8963(u_char reg,u_char txd);
        void Read_Reg_AK8963(u_char reg,u_char count,u_char *dest);
        void Check_AK8963();
        void Check();

        u_char buffer[21];
        u_char mag_adjust[3];
        
        int16_t Accel_Buffer[3],Gyro_Buffer[3]; 
        float Accel_Scale=0,Gyro_Scale=0,Accel_Bottom=0,Gyro_Bottom=0;

        public:
        enum class AccelScale{
            _2G,_4G,_8G,_16G
        };
        enum class GyroScale{
            _250DPS,_500DPS,_1000DPS,_2000DPS
        };

        float Gyro_x_Offset=0,Gyro_y_Offset=0,Gyro_z_Offset=0;

        float Accel_x=0,Accel_y=0,Accel_z=0;
        float Gyro_x=0,Gyro_y=0,Gyro_z=0;
        float Roll_temp=0,Pitch_temp=0;
        float Roll=0,Pitch=0;

        MPU9250(SPI_PIN_Pack);
        void SetAccel_Scale(AccelScale Scale);
        void SetGyro_Scale(GyroScale Scale);
        void RefAccel();
        void RefGyro();
        void Initialize_Gyro_ZeroDrift();

        void Initialize_KalmanFilter();
        void RefKalmanFilter();
    };
}

#endif