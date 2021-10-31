#pragma once
#include<SolidKernel.h>


class SampleApplication{
    private:
    HardWare::Computer *COM;
    HardWare::SSD1306 *SSD1306_M;

    public:
    SampleApplication()=default;
    ~SampleApplication()=default;

    void Init(){
        SystemClock::Clock(Clock_Speed::HighSpeed); //配置为高速的系统时钟(目前也只实现了高速).

        COM = new HardWare::Computer(0,115200);     //PA9,PA10
        Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
            COM->Send(Info,InterruptCnt);           //发送Debug信息
        });                                         


        Debug_StartDebug("SSD1306_M");              //如果不需要Debug信息可以删除(需要成对出现)
        SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
        Debug_EndDebug();
    }
    
    void Run(){
        while(1){
            if(SSD1306_M->ON){
                SSD1306_M->Clear();
                SSD1306_M->DrawString(0,0 ,"Sample Program");
                SSD1306_M->Refresh();
            }
        }
    }

};