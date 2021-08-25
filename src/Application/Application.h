#pragma once
#include<SolidKernel.h>

class Application{
    private:
    HardWare::Computer *COM;
    HardWare::SSD1306 *SSD1306_M;
    // HardWare::AD7705 *AD7705_M;
    // HardWare::TOF10120 *TOF10120_M;
    // HardWare::ADXL345 *ADXL345_M;
    // HardWare::ESP8266 *ESP8266_M;
    // HardWare::TB6612FNG *TB6612FNG_M;
    // Peripheral_Encoder *Encoder0_M,*Encoder2_M;
    // HardWare::OV7725 *OV7725_M;
    // HardWare::MPU6050 *MPU6050_M;


    // HardWare::HC_Modules::HC_12 *HC_12_M1,*HC_12_M2;
    // HardWare::HC_Modules::HC_08 *HC_08_M;

    // HardWare::Servo *Servo_M;

    HardWare::TFTScreen *TFTScreen_M;
    unsigned int Cnt=0;
    //Image::Image_RGB565 Camera(120,80);
    //Image::Image_Binary* Binary;

    SolidGL::Draw::RGB565::Pen ImagePen;
    SolidGL::Components::Canvas<SolidGL::Draw::RGB565>* Canvas0;
    //SolidGL::Components::TextField<SolidGL::Draw::RGB565> TextField0;
    public:
    Application()=default;
    ~Application()=default;

    void Init(){
       
        SystemClock::Clock(Clock_Speed::HighSpeed);//配置为高速的系统时钟(目前也只实现了高速).

        //HC_08_M = new HardWare::HC_Modules::HC_08(0,115200);
        COM = new HardWare::Computer(0,115200);
        Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
            COM->Send(Info,InterruptCnt);
        });

        //Debug_StartDebug("SSD1306_M");
        //SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
        //Debug_EndDebug();

        //Debug_StartDebug("MPU6050_M");
        //MPU6050_M = new HardWare::MPU6050(0,0,0,1);
        //Debug_EndDebug();

        Debug_StartDebug("RenderTarget");
        //TextField0.recBackgroundColor.Bytes=0x0000;
        //TextField0.pen.color.Bytes=0xFFFF;
        Canvas0 = new SolidGL::Components::Canvas<SolidGL::Draw::RGB565>(4,5);
        Canvas0->recBackgroundColor.Bytes=0xFFFF;
        Canvas0->recBackgroundColor.R(0b11111);
        Canvas0->recBackgroundColor.G(0b000000);
        Canvas0->recBackgroundColor.B(0b00000);
        Canvas0->recTransform.Position.x=0;
        Canvas0->recTransform.Position.y=0;
        ImagePen.color.Bytes=0x0000;
        Debug_EndDebug();

        Debug_StartDebug("TFTScreen_M");
        TFTScreen_M = new HardWare::TFTScreen(0,0,0,1,0,4,0,5,0,6);
        TFTScreen_M->__GraphicInit(240,240);
        Debug_EndDebug();


        //TextField0.pen.color.Bytes=0xFFFF;

        /*
        Debug_StartDebug("Servo_M");
        Servo_M = new HardWare::Servo(0);
        Debug_EndDebug();
        */
        /*
        Debug_StartDebug("OV7725_M");`
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
        ESP8266_M->Set_WIFI_SendMode(Wifi::SendMode::Normal);
        ESP8266_M->Ref2Dis_WIFIList();
        ESP8266_M->Connect_WIFI("OnePlus 8","12345678");
        ESP8266_M->Display_THISAddr();
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
            /*
            if(SSD1306_M->ON){
                SSD1306_M->Clear();
                MPU6050_M->Refresh(1000);  
                Cnt++;
                //SSD1306_M->DrawString(0,0 ,"gx="+std::to_string(MPU6050_M->Gyroscope_Pack.gx));
                //SSD1306_M->DrawString(0,10,"gy="+std::to_string(MPU6050_M->Gyroscope_Pack.gy));
                //SSD1306_M->DrawString(0,20,"gz="+std::to_string(MPU6050_M->Gyroscope_Pack.gz));
                SSD1306_M->DrawString(0,30,std::to_string(Cnt),24);
                //Binary = Camera.Binaryzation([&](u_char R,u_char G,u_char B){return ((R+G+B)<20);},2,Binary);
                //SSD1306_M->DrawImage(0,0,Binary);
                SSD1306_M->Refresh();
            }
            */
            //TFTScreen_M->Clear();
            //TFTScreen_M->DrawString(0,0,"qwq",*TFTpen);
            Debug_InterruptSend("RenderIn");

            Canvas0->Clear();
            //Canvas0->DrawString(0,0,"QAQ",ImagePen,24);
            //TFTImage->DrawPixel(0,0,ImagePen);
            //Canvas0->DrawLine(0,0,119,0,ImagePen);
            Canvas0->recTransform.Position.x+=12; 
            if(Canvas0->recTransform.Position.x>=240){
                Canvas0->recTransform.Position.x%=240;
                Canvas0->recTransform.Position.y+=12;
                if(Canvas0->recTransform.Position.y>=240){
                    Canvas0->recTransform.Position.y%=240;
                }
            }
            //Canvas0->DrawLine(0,0,12,12,ImagePen);
            TFTScreen_M->Render(*Canvas0);



            // *TextField0="QAQ";
            // TextField0->recTransform.Position.x=240;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
            // TextField0->recTransform.Position.y=240;
                
            // TFTScreen_M->Render(*TextField0);
            Debug_InterruptSend("RenderOut");

            //Servo_M->Servo_Euler_Degree(90.0);
        }
        
    }
};