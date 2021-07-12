#include<HardWare/TOF10120.h>

namespace HardWare{
    TOF10120::TOF10120(){}
    uint TOF10120::Get_Distance_mm(){return 0;}
    void TOF10120::SetReciveMode(InfoMode mode){}
    int  TOF10120::GetOffset_mm(){return 0;}
    void TOF10120::SetOffset_mm(int offset){}
    uint TOF10120::GetInterval_ms(){return 0;}
    void TOF10120::SetInterval_ms(uint interval){}
    bool TOF10120::GetFilter_en(){return 0;}
    void TOF10120::SetFilter_en(bool enable){}
    uint TOF10120::GetMaxRange_mm(){return 0;}
    void TOF10120::SetMaxRange_mm(uint maxrange){}
    u_char TOF10120::GetI2C_Address(){return 0;}
    void TOF10120::SetI2C_Address(u_char Address){}
}




#if __Enable_Uart

namespace UART{
    TOF10120::TOF10120(uint32_t Uartx):Peripheral_UART(Uartx,9600){
        this->BindCallback([&](char* str,int size){
            std::string Buffer;
            bool flag=false;
            Debug::InterruptSend("Recv");
            if(str[0]=='o'&&str[1]=='k'){
                Debug::InterruptSend("TOF10120 ok!");
                return;
            }
            if(str[0]=='f'&&str[1]=='a'&&str[2]=='i'&&str[3]=='l'){
                Debug::InterruptSend("TOF10120 fail!");
                return;
            }
            for(uint i=0;i<size;i++){
                if(str[i]=='='){
                    flag=true;
                }
                if(flag&&str[i]<='9'&&str[i]>='0'){
                    Buffer+=str[i];
                }
            }
            this->NumBuffer=std::stoi(Buffer);
            this->Recvflag=true;
        });
    }
    uint TOF10120::Get_Distance_mm(){
        this->Send("r6#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return NumBuffer;
    }
    void TOF10120::SetReciveMode(InfoMode mode){
        switch (mode){
        case InfoMode::UART:
            this->Send("s5+0#");
            break;
        case InfoMode::UART_I2C:
            this->Send("s5+1#");
            break;
        }
    }
    int  TOF10120::GetOffset_mm(){
        this->Send("r1#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return NumBuffer;
    }
    void TOF10120::SetOffset_mm(int offset){
        if(offset>=0){
            this->Send("s1+"+std::to_string(offset)+"#");
        }else{
            this->Send("s1-"+std::to_string(-offset)+"#");
        }
    }
    uint TOF10120::GetInterval_ms(){
        this->Send("r2#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return !NumBuffer;
    }
    void TOF10120::SetInterval_ms(uint interval){
        if(interval>=10000){
            interval=9999;
            Debug::Warning("interval Range:10~9999ms!");
        }else if(interval<10){
            interval=10;
            Debug::Warning("interval Range:10~9999ms!");
        }
        this->Send("s2-"+std::to_string(interval)+"#");
    }
    bool TOF10120::GetFilter_en(){
        this->Send("r3#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return !NumBuffer;
    }
    void TOF10120::SetFilter_en(bool enable){
        this->Send("s3-"+std::to_string(enable?0:1)+"#");
    }
    uint TOF10120::GetMaxRange_mm(){
        this->Send("r6#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return !NumBuffer;
    }
    //为0则不设置距离
    void TOF10120::SetMaxRange_mm(uint maxrange){
        if(maxrange>2000){
            maxrange=2000;
            Debug::Warning("maxrange Range:100~2000mm!");
        }else if(maxrange<100){
            maxrange=100;
            Debug::Warning("maxrange Range:100~2000mm!");
        }
        this->Send("s4-"+std::to_string(maxrange)+"#");
    }
    u_char TOF10120::GetI2C_Address(){
        this->Send("r7#");
        while(!this->Recvflag);
        this->Recvflag=false;
        return !NumBuffer;
    }
    void TOF10120::SetI2C_Address(u_char Address){
        this->Send("s7-"+std::to_string(Address)+"#");
    }
}

#endif