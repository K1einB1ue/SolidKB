#include<VirtualHardWare.h>

HardWare::SSD1306 *SSD1306_M;
//HardWare::OV7725 *OV7725_M;
HardWare::AD7705 *AD7705_M;
//HardWare::MPU6050 *MPU6050_M;
HardWare::Computer *COM;

void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);         //配置为高速的系统时钟(目前也只实现了高速).

    COM = new HardWare::Computer(0,115200);             //使用串口2,115200波特率作为电脑端口.
    Debug::DebugCallback=[&](std::string Info){         //使用电脑端口的输出作为Debug信息的回调方式.
        COM->Send(Info);
    };
    
    //MPU6050_M =new HardWare::MPU6050(0,5,0,7);
    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    
    //OV7725_M = new HardWare::OV7725(0,0,0,1,6,9,6,15);
    //OV7725_M->Set_Contrast();
    Debug::StartDebug("AD7705");
    AD7705_M = new HardWare::AD7705(0,0,0,1,0,4,0,5,0,6);
    Debug::EndDebug();

    SSD1306_M->__GraphicInit(128,64);

    
}


int main(){
    HardWareInit();



    
    while(1){   
        //MPU6050_M->Refresh_Temperature();
        Debug::InterruptSend(std::to_string(AD7705_M->Get_Channel1_mV()));
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            SSD1306_M->DrawString(10,10,"qwq");
            //SSD1306_M->DrawMemory(25,16,th[0],4,3);
            //SSD1306_M->DrawString(30,20,std::to_string(MPU6050_M->Temperature));
            //SSD1306_M->DrawPixel(10,10);
            //SSD1306_M->DrawString(10,10,"qwq");
            SSD1306_M->Refresh();
        }  
        
    }
    
    return 0;
}