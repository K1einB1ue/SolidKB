#include<SolidKernel.h>


class Application{
    private:
    HardWare::SSD1306 *SSD1306_M;
    HardWare::AD7705 *AD7705_M;
    HardWare::TOF10120 *TOF10120_M;
    //HardWare::ADXL345 *ADXL345_M;
    HardWare::Computer *COM;
    HardWare::ESP8266 *ESP8266_M;
    HardWare::TB6612FNG *TB6612FNG_M;
    Peripheral_Encoder *Encoder0_M,*Encoder2_M;
    HardWare::OV7725 *OV7725_M;
    HardWare::MPU6050 *MPU6050_M;

    HardWare::HC_Modules::HC_12 *HC_12_M1,*HC_12_M2;
    HardWare::HC_Modules::HC_08 *HC_08_M;

    //Image::Image_RGB565 Camera(120,80);
    //Image::Image_Binary* Binary;
    public:
    Application()=default;
    ~Application()=default;

    void Init(){
        SystemClock::Clock(Clock_Speed::HighSpeed);//配置为高速的系统时钟(目前也只实现了高速).

        COM = new HardWare::Computer(0,115200);
        Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
            COM->Send(Info,InterruptCnt);
        });
        
        

        Debug_StartDebug("SSD1306_M");
        SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
        Debug_EndDebug();

        Debug_StartDebug("MPU6050_M");
        MPU6050_M = new HardWare::MPU6050(0,0,0,1);
        Debug_EndDebug();

        /*
        Debug_StartDebug("OV7725_M");
        OV7725_M = new HardWare::OV7725(0,0,0,1,0,7,0,5,0,Camera._Image,80*120);
        Debug_EndDebug();
        */
        
        /*
        Debug_StartDebug("AD7705_M");
        AD7705_M = new HardWare::AD7705(0,0,0,1,0,4,0,5,0,6,0,7);
        Debug_EndDebug();
        */

        /*
        Debug_StartDebug("Encoder_M");
        Encoder0_M = new Peripheral_Encoder(0);
        Encoder2_M = new Peripheral_Encoder(2);
        Debug_EndDebug();

        Debug_StartDebug("TOF10120_M");
        TOF10120_M = new UART::TOF10120(1);
        Debug_EndDebug();  

        Debug_StartDebug("TB6612FNG_M");
        TB6612FNG_M = new HardWare::TB6612FNG(0,7,2,5,0,6,0,4,0,1);
        Debug_EndDebug();
        */

        /*
        Debug_StartDebug("ESP8266_M");
        ESP8266_M = new HardWare::ESP8266(1);
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
        ESP8266_M->SocketCallback=[&](auto Link_ID,auto Str,auto Size){
            std::string tmp(Str,Size);
            ESP8266_M->Socket_Send(tmp,Link_ID);
        };

        ESP8266_M->Socket_End();
        Debug_EndDebug();
        */
    }
    void Run(){
        while(1){
            //double temp =TOF10120_M->distance/200.0;
            //TB6612FNG_M->Motor_Speed((TOF10120_M->distance/200.0),-(TOF10120_M->distance/200.0));  
            
            if(SSD1306_M->ON){
                SSD1306_M->Clear();
                MPU6050_M->Refresh(10);  
                SSD1306_M->DrawString(0,0 ,"gx="+std::to_string(MPU6050_M->Gyroscope_Pack.gx));
                SSD1306_M->DrawString(0,10,"gy="+std::to_string(MPU6050_M->Gyroscope_Pack.gy));
                SSD1306_M->DrawString(0,20,"gz="+std::to_string(MPU6050_M->Gyroscope_Pack.gz));
                SSD1306_M->DrawString(0,30,"qwq");
                //Binary = Camera.Binaryzation([&](u_char R,u_char G,u_char B){return ((R+G+B)<20);},2,Binary);
                //SSD1306_M->DrawImage(0,0,Binary);
                SSD1306_M->Refresh();
            }
        }
    }
};



Application DevelopApp;

void Kernel_Init(){
    DevelopApp.Init();
}

void Kernel_Run(){
    DevelopApp.Run();
}

//void Kernel_Exit(){}

