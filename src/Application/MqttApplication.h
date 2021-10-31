#pragma once
#include<SolidKernel.h>


namespace Program{
    class MqttProject{
        private:
        HardWare::Computer *COM;
        HardWare::ESP8266 *ESP8266;

        public:
        void Init(){
            SystemClock::Clock(Clock_Speed::HighSpeed);//配置为高速的系统时钟(目前也只实现了高速).

            COM = new HardWare::Computer(0,115200);
            Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
                COM->Send(Info,InterruptCnt);
            });

            ESP8266=new HardWare::ESP8266(1);
        }

        void Run(){
            while(1){

            }
        }
    };
}


