#include<VirtualHardWare.h>




HardWare::ESP8266 *ESP8266_M;
HardWare::SSD1306 *SSD1306_M;

int NextStop=0;

void Decoder(std::string Code){
    if(Code=="8"){
        if(SSD1306_M->ON){
            SSD1306_M->Close();
        }else{
            SSD1306_M->Open();
        }
    }
}


void HardWareInit(){
    SystemClock::Clock(Clock_Speed::HighSpeed);

    SSD1306_M = new SPI::SSD1306(0,8,0,11,0,12,0,13,0,14);
    ESP8266_M = new HardWare::ESP8266(0);

    SSD1306_M->__GraphicInit(128,64);

    ESP8266_M->BindCallback([](char* Str,unsigned int Size){
        bool Flag0=false,Flag1=false;
        std::string LenStr,InfoStr;
        int DotCnt=0,Len=0;
        if(Size<=10){
            return;
        }

        for(unsigned int i=0;i<Size;i++){
            if(Str[i]==','&&!Flag0){
                DotCnt++;
                if(DotCnt==2){
                    Flag0=true;
                }  
            }else if(Flag0){
                if(Str[i]==':'&&!Flag1){
                    Flag1=true;
                    Len=std::stoi(LenStr);
                }else if(!Flag1){
                    LenStr+=Str[i];
                }else if(Flag1){
                    if(Len){
                        Len--;
                        InfoStr+=Str[i];
                    }else{
                        Decoder(InfoStr);
                        return;
                    }
                }
            }
        }
    });


}


int main(){
    
    HardWareInit();
    
    
    while(1){      
        if(SSD1306_M->ON){
            SSD1306_M->Clear();
            SSD1306_M->DrawString(10,10,"Test2");
            SSD1306_M->Refresh();
        }  
    }

    return 0;
}