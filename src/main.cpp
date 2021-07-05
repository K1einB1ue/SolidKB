#include<VirtualHardWare.h>

HardWare::SSD1306 *SSD1306_M;
HardWare::OV7725 *OV7725_M;
HardWare::Computer *COM;


void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);

    COM = new HardWare::Computer(1,115200);
    Debug::DebugCallback=[&](std::string Info){
        COM->Send(Info);
    };


    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    OV7725_M = new HardWare::OV7725(3,7,3,6,6,9,6,15);
    //OV7725_M->Set_Contrast();
    
    SSD1306_M->__GraphicInit(128,64);

}


int main(){
    
    HardWareInit();

    
    while(1){   
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            SSD1306_M->DrawString(10,10,"QAQ");
            SSD1306_M->DrawString(10,30,"qwq");
            SSD1306_M->Refresh();
        }  
    }

    return 0;
}