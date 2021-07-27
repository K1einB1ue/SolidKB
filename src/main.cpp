#include<VirtualHardWare.h>

HardWare::SSD1306 *SSD1306_M;
//HardWare::AD7705 *AD7705_M;
HardWare::TOF10120 *TOF10120_M;
HardWare::ADXL345 *ADXL345_M;
HardWare::Computer *COM;
HardWare::ESP8266 *ESP8266_M;
PWM *PWM0_M,*PWM1_M,*PWM2_M,*PWM3_M;

void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);                                                 //配置为高速的系统时钟(目前也只实现了高速).

    COM = new HardWare::Computer(0,115200);
    Debug::BindCallback([&](std::string Info,unsigned int *InterruptCnt){
        COM->Send(Info,InterruptCnt);
    });

    //Debug::StartDebug("AD7705_M");
    //AD7705_M = new HardWare::AD7705(0,0,0,1,0,4,0,5,0,6,0,7);
    //Debug::EndDebug();
    Debug::StartDebug("SSD1306_M");
    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    Debug::EndDebug();

    Debug::StartDebug("PWM0_M");
    PWM0_M = new PWM(4,168-1,1000-1);
    PWM1_M = new PWM(5,168-1,1000-1);
    PWM2_M = new PWM(6,168-1,1000-1);
    //PWM3_M = new PWM(3,168-1,1000-1);
    Debug::EndDebug();

    *PWM0_M=0.5;
    *PWM1_M=0.7;
    *PWM2_M=0.4;
    //*PWM3_M=0.3;

    Debug::StartDebug("TOF10120_M");
    TOF10120_M = new UART::TOF10120(1);
    Debug::EndDebug();

    //*PWM0_M=300;

    // Debug::StartDebug("ESP8266_M");
    // ESP8266_M = new HardWare::ESP8266(1);
    // ESP8266_M->Wifi_Reset();
    // ESP8266_M->Set_WIFI_Mode(Wifi::Mode::SoftAP_Station);
    // ESP8266_M->Set_WIFI_Connection(Wifi::Connection::Single);
    // ESP8266_M->Refresh_WIFIList();
    // ESP8266_M->Display_WIFIList();
    // ESP8266_M->Connect_WIFI("CMCC-ZH12A-519");
    // ESP8266_M->ping("10.248.43.89");
    // ESP8266_M->Socket_Start("10.248.43.89",5000,Socket::Type::TCP);
    // ESP8266_M->Socket_Send("Test");
    // ESP8266_M->Socket_End();
    // Debug::EndDebug();

    
    

}


int main(){
    HardWareInit();
    
    while(1){
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            SSD1306_M->DrawString(10,10,std::to_string(TOF10120_M->distance)+"mm");
            SSD1306_M->Refresh();
        }  
    }
    
    return 0;
}