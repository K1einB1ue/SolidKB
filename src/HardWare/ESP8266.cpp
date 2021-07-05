#include<HardWare/ESP8266.h>
#include<AbstractDependency/_AbstractHardWare.h>

namespace HardWare{

    ESP8266::ESP8266(uint32_t Uartx):Uart(Uartx,115200){

        this->NonReciveSend("AT+RST\r\n");
        SystemClock::Delay(500000);
        
        this->NonReciveSend("AT+CWMODE=2\r\n");
        SystemClock::Delay(500000);

        this->NonReciveSend("AT+CIPMUX=1\r\n");
        SystemClock::Delay(500000);

        this->NonReciveSend("AT+CIPSERVER=1,8080\r\n");
        SystemClock::Delay(500000);
        this->Open();

    }

}


    /*
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
    */