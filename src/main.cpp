#include<VirtualHardWare.h>

HardWare::SSD1306 *SSD1306_M;
HardWare::AD7705 *AD7705_M;
HardWare::TOF10120 *TOF10120_M;
//HardWare::ADXL345 *ADXL345_M;
HardWare::Computer *COM;
HardWare::ESP8266 *ESP8266_M;
HardWare::TB6612FNG *TB6612FNG_M;
Peripheral_Encoder *Encoder0_M,*Encoder2_M;


void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);                                                 //配置为高速的系统时钟(目前也只实现了高速).

    COM = new HardWare::Computer(0,115200);
    Debug::BindCallback([&](std::string Info,unsigned int *InterruptCnt){
        COM->Send(Info,InterruptCnt);
    });
    
    

    Debug::StartDebug("SSD1306_M");
    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    Debug::EndDebug();

    Debug::StartDebug("AD7705_M");
    AD7705_M = new HardWare::AD7705(0,0,0,1,0,4,0,5,0,6,0,7);
    Debug::EndDebug();

    /*
    Debug::StartDebug("Encoder_M");
    Encoder0_M = new Peripheral_Encoder(0);
    Encoder2_M = new Peripheral_Encoder(2);
    Debug::EndDebug();

    Debug::StartDebug("TOF10120_M");
    TOF10120_M = new UART::TOF10120(1);
    Debug::EndDebug();  

    Debug::StartDebug("TB6612FNG_M");
    TB6612FNG_M = new HardWare::TB6612FNG(0,7,2,5,0,6,0,4,0,1);
    Debug::EndDebug();
    */
   
    /*
    Debug::StartDebug("ESP8266_M");
    ESP8266_M = new HardWare::ESP8266(2);
    ESP8266_M->Wifi_Reset();
    ESP8266_M->Set_WIFI_Mode(Wifi::Mode::SoftAP_Station);
    ESP8266_M->Set_WIFI_Connection(Wifi::Connection::Single);
    ESP8266_M->Refresh_WIFIList();
    ESP8266_M->Display_WIFIList();
    ESP8266_M->Connect_WIFI("OnePlus 8","12345678");
    ESP8266_M->ping("120.77.148.70");
    ESP8266_M->ping("10.200.18.118");
    ESP8266_M->Socket_Start("10.200.18.118",5000,Socket::Type::TCP);
    ESP8266_M->Socket_Send("Test");
    ESP8266_M->Socket_End();
    Debug::EndDebug();
    */



}


int main(){
    HardWareInit();
    while(1){
        //double temp =TOF10120_M->distance/200.0;

        
        //TB6612FNG_M->Motor_Speed((TOF10120_M->distance/200.0),-(TOF10120_M->distance/200.0));
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            //SSD1306_M->DrawString(10,10,std::to_string(TOF10120_M->distance)+"mm");
            SSD1306_M->DrawString(10,20,std::to_string(AD7705_M->Get_Channel1_mV()));
            SSD1306_M->DrawString(10,30,std::to_string(AD7705_M->Get_Channel2_mV()));
            //SSD1306_M->DrawString(10,20,std::to_string(*Encoder0_M));
            //SSD1306_M->DrawString(10,30,std::to_string(*Encoder2_M));
            SSD1306_M->Refresh();
        }
        
    } return 0;
}