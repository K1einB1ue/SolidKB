#pragma once
#include<Kernel/SolidKernel.h>

class Application{
    private:
    HardWare::Computer *COM;
    HardWare::SSD1306 *SSD1306_M;
    // HardWare::AD7705 *AD7705_M;
    // HardWare::TOF10120 *TOF10120_M;
    // HardWare::ADXL345 *ADXL345_M;
    HardWare::ESP8266 *ESP8266_M;
    // HardWare::TB6612FNG *TB6612FNG_M;
    // Peripheral_Encoder *Encoder0_M,*Encoder2_M;
    // HardWare::OV7725 *OV7725_M;
    // HardWare::MPU6050 *MPU6050_M;


    // HardWare::HC_Modules::HC_12 *HC_12_M1,*HC_12_M2;
    // HardWare::HC_Modules::HC_08 *HC_08_M;

    // HardWare::Servo *Servo_M;

    HardWare::ST7735 *ST7735_M;
    unsigned int Cnt=0;
    //Image::Image_RGB565 Camera(120,80);
    //Image::Image_Binary* Binary;

    //SolidGL::Draw::RGB565::Pen ImagePen;
    //SolidGL::Components::Canvas<SolidGL::Draw::RGB565> Canvas0 = SolidGL::Components::Canvas<SolidGL::Draw::RGB565>(20,20);
    //SolidGL::Components::TextField<SolidGL::Draw::RGB565> TextField0;
    SolidGL::Draw::Bit::Pen ImagePen;
    uint Size=5;
    public:
    Application()=default;
    ~Application()=default;

    std::string ConnectionPack = EncodeFormats::Mqtt::MqttPacks::ConnectionPack("cbbe114775e2464a9d5c9d5cd9418825","Klein_Blue","123456789");
    std::string PingReqPack = EncodeFormats::Mqtt::MqttPacks::PingReqPack();
    std::string TestPublishPack = EncodeFormats::Mqtt::MqttPacks::PublishPack("test","qwq",EncodeFormats::Mqtt::MsgQos::Type0,false);

    void Init(){
       
        SystemClock::Clock(Clock_Speed::HighSpeed);//配置为高速的系统时钟(目前也只实现了高速).

        //HC_08_M = new HardWare::HC_Modules::HC_08(0,115200);
        COM = new HardWare::Computer(0,115200);
        Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
            COM->Send(Info,InterruptCnt);
        });

        Debug_StartDebug("SSD1306_M");
        SSD1306_M = new SPI::SSD1306(0,0,0,1,0,4,0,5,0,6);
        Debug_EndDebug();
        //设置绘制工具为暗色
        ImagePen.color=1;
        //设置背景色为亮色
        SSD1306_M->canvas->recBackgroundColor.Byte=0;
        
        //Debug_StartDebug("MPU6050_M");
        //MPU6050_M = new HardWare::MPU6050(0,0,0,1);
        //Debug_EndDebug();

        //TextField0.recBackgroundColor.Bytes=0x0000; 
        //TextField0.pen.color.Bytes=0xFFFF;
        /*
        Canvas0 = new SolidGL::Components::Canvas<SolidGL::Draw::RGB565>(12,12);
        Canvas0->recBackgroundColor.Bytes=0xFFFF;
        Canvas0->recBackgroundColor.R(colorR);
        Canvas0->recBackgroundColor.G(0b000000);
        Canvas0->recBackgroundColor.B(0b11111);
        Canvas0->recTransform.Position.x=0;
        Canvas0->recTransform.Position.y=0;
        */
        // Canvas0.recTransform.Position.x=0;
        // Canvas0.recTransform.Position.y=0;
        // Canvas0.recBackgroundColor.R(0b00000);
        // Canvas0.recBackgroundColor.G(0b111111);
        // Canvas0.recBackgroundColor.B(0b11111);
        // Canvas0.Clear();
        //ImagePen.color.Bytes=0x0000;

        //Debug_StartDebug("ST7735_M");
        //ST7735_M = new HardWare::ST7735(0,0,0,1,0,4,0,5,0,6,0,7);
        //ST7735_M->__GraphicInit(80,80);
        //Debug_EndDebug();
        
        
        Debug_InterruptSend("Mqtt::ConnectionPack="+std::Hexlize(ConnectionPack));

        Debug_StartDebug("ESP8266_M");
        ESP8266_M = new HardWare::ESP8266(2);
        ESP8266_M->TryExitPassThrough();
        ESP8266_M->Wifi_Reset();
        ESP8266_M->Set_WIFI_Mode(Wifi::Mode::SoftAP_Station);
        ESP8266_M->Set_WIFI_Connection(Wifi::Connection::Single);
        ESP8266_M->Set_WIFI_SendMode(Wifi::SendMode::Normal);
        ESP8266_M->Ref2Dis_WIFIList();
        ESP8266_M->Connect_WIFI("OnePlus 8","12345678");
        //ESP8266_M->Connect_WIFI("CMCC-ZH12A-519");
        ESP8266_M->Display_THISAddr();
        ESP8266_M->ping("106.14.95.2");
        //ESP8266_M->ping("10.248.43.21");
        ESP8266_M->Socket_Start("106.14.95.2",1883,Socket::Type::TCP);
        //ESP8266_M->Socket_Start("10.248.43.21",1883,Socket::Type::TCP);
        ESP8266_M->Set_WIFI_SendMode(Wifi::SendMode::Passthrough);
        ESP8266_M->StreamCallback=[&](char chr){
            COM->Send(std::Hexlize(chr));
        };
        SystemClock::Delay(100000);
        ESP8266_M->Socket_Send(ConnectionPack);
        ESP8266_M->Socket_Send(TestPublishPack);
        
        /*
        ESP8266_M->SocketCallback=[&](auto Link_ID,auto Str,auto Size){
            std::string tmp(Str,Size);
            ESP8266_M->Socket_Send(tmp,Link_ID);
        };
        */

        
        
        //ESP8266_M->Socket_End();
        Debug_EndDebug();
        
    }

    
    void Run(){
        unsigned int timeCounter=0;
        while(1){
            SSD1306_M->canvas->Clear();
            SSD1306_M->canvas->DrawString(50,0,"qwq",ImagePen);
            SSD1306_M->Refresh();
            if(timeCounter++==50000){
                timeCounter=0;
                ESP8266_M->Socket_Send(PingReqPack);
            }
        }
    }
};