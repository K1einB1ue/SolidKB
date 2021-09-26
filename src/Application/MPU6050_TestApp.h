#pragma once
#include<SolidKernel.h>


namespace TestProgram{
    class MPU6050{
        private:
        HardWare::Computer *COM;
        //HardWare::MPU6050 *MPU6050_M;
        HardWare::MPU9250 *MPU9250_M;
        HardWare::SSD1306 *SSD1306_M;
        public:

        void Init(){
            SystemClock::Clock(Clock_Speed::HighSpeed);//配置为高速的系统时钟(目前也只实现了高速).

            COM = new HardWare::Computer(0,115200);
            Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
                COM->Send(Info,InterruptCnt);
            });

            /*
            Debug_StartDebug("MPU6050_M");
            MPU6050_M = new HardWare::MPU6050(0,0,0,1);
            Debug_EndDebug();
            */

            Debug_StartDebug("MPU9250_M");
            MPU9250_M = new HardWare::MPU9250(0,0,0,1,0,4,0,5);
            Debug_EndDebug();

            Debug_StartDebug("SSD1306_M");
            SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
            Debug_EndDebug();

        }
        void Run(){
            while(1){
                if(SSD1306_M->ON){
                    SSD1306_M->Clear();
                    MPU9250_M->RefAccel();
                    MPU9250_M->RefGyro();
                    SSD1306_M->DrawString(0,0 ,"ax="+std::fto_string(MPU9250_M->Accel_x));
                    SSD1306_M->DrawString(0,10,"ay="+std::fto_string(MPU9250_M->Accel_y));
                    SSD1306_M->DrawString(0,20,"az="+std::fto_string(MPU9250_M->Accel_z));
                    SSD1306_M->DrawString(64,0 ,"gx="+std::fto_string(MPU9250_M->Gyro_x));
                    SSD1306_M->DrawString(64,10,"gy="+std::fto_string(MPU9250_M->Gyro_y));
                    SSD1306_M->DrawString(64,20,"gz="+std::fto_string(MPU9250_M->Gyro_z));
                    SSD1306_M->DrawString(0,30,"Roll="+std::fto_string(MPU9250_M->Roll_temp));
                    SSD1306_M->DrawString(0,40,"Pitch="+std::fto_string(MPU9250_M->Pitch_temp));
                    SSD1306_M->Refresh();
                }
            }
        }
    };
}