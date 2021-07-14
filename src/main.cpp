#include<VirtualHardWare.h>

HardWare::SSD1306 *SSD1306_M;
//HardWare::AD7705 *AD7705_M;
//HardWare::TOF10120 *TOF10120_M;
HardWare::Computer *COM;

void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);         //配置为高速的系统时钟(目前也只实现了高速).

    COM = new HardWare::Computer(0,115200);             //使用串口2,115200波特率作为电脑端口.
    Debug::DebugCallback=[&](std::string Info){         //使用电脑端口的输出作为Debug信息的回调方式.
        COM->Send(Info);
    };
    
    //Debug::StartDebug("TOF10120_M");
    //TOF10120_M = new UART::TOF10120(1);
    //Debug::EndDebug();

    //Debug::StartDebug("AD7705_M");
    //AD7705_M = new HardWare::AD7705(0,0,0,1,0,4,0,5,0,6,0,7);
    //Debug::EndDebug();

    Debug::StartDebug("SSD1306_M");
    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    Debug::EndDebug();


    
}


int main(){
    HardWareInit();
    //uint temp = TOF10120_M->Get_Distance_mm();
    while(1){   
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            SSD1306_M->DrawString(10,10,std::to_string(0));
            //SSD1306_M->DrawString(10,10,"AD:"+std::to_string(AD7705_M->Get_Channel1_mV())+"mV");
            SSD1306_M->Refresh();
        }  
    }
    
    return 0;
}