#include<HardWare/TOF10120.h>

namespace HardWare{
    TOF10120::TOF10120(){}
    void TOF10120::RefDistance_mm(){}
    void TOF10120::RefReciveMode(){}
    void TOF10120::SetReciveMode(InfoMode mode){}
    void TOF10120::RefOffset_mm(){}
    void TOF10120::SetOffset_mm(int offset){}
    void TOF10120::RefInterval_ms(){}
    void TOF10120::SetInterval_ms(uint interval){}
    void TOF10120::RefFilter_en(){}
    void TOF10120::SetFilter_en(bool enable){}
    void TOF10120::RefMaxRange_mm(){}
    void TOF10120::SetMaxRange_mm(uint maxrange){}
    void TOF10120::RefI2C_Address(){}
    void TOF10120::SetI2C_Address(u_char Address){}
}




#if __Enable_Uart

namespace UART{
    TOF10120::TOF10120(uint32_t Uartx):Peripheral_UART(Uartx,9600){
        this->End("\r\n",2);
        this->End_Clear(true);
        this->End_Decoder([&](char* Data,unsigned int Size){          
            std::string Num;
            if(Data[0]>='0'&&Data[0]<='9'){
                Num+=Data[0];
                for(unsigned int i=1;i<Size;i++){
                    if(Data[0]>='0'&&Data[0]<='9'){
                        Num+=Data[i];
                    }else{
                        break;
                    }
                }
                this->distance=std::stoi(Num);
                if(this->DistanceCallBack){
                    this->DistanceCallBack(this->distance);
                }
                return;
            }
            if(Data[0]=='o'&&Data[1]=='k'){
                Debug::InterruptSend("[TOF10120]ok!");
                return;
            }
            if(Data[0]=='f'&&Data[1]=='a'&&Data[2]=='i'&&Data[3]=='l'){
                Debug::InterruptSend("[TOF10120]fail!");
                return;
            }
            bool EqualFlag=false;     
            for(unsigned int i=0;i<Size;i++){
                if(EqualFlag&&Data[i]<='9'&&Data[i]>='0'){
                    Num+=Data[i];
                }else if(Data[i]=='='){
                    EqualFlag=true;
                }
                if(Data[i]=='#'){
                    break;
                }
            }
            if(EqualFlag){
                switch (Data[0]){
                    case 'D':this->offset=std::stoi(Num);return;

                    case 'T':this->interval=std::stoi(Num);return;

                    case 'M':if(Data[1]=='a'){this->maxrange=std::stoi(Num);return;}
                    else{this->enable=std::stoi(Num);return;}


                    case 'S':if(std::stoi(Num)==0){
                        this->mode=InfoMode::UART;
                    }else{this->mode=InfoMode::UART_I2C;}
                    return;

                    case 'L':this->distance=std::stoi(Num);return;

                    case 'I':this->Address=std::stoi(Num);return;

                    default:Debug::InterruptSend("[TOF10120]Error Call!");return;
                }
            }
        });

        this->BindCallback([&](char chr){
            this->StreamIn(chr);
        });
        
        this->SetReciveMode(InfoMode::UART);
    }

    void TOF10120::RefDistance_mm(){
        this->Send("r6#\r\n");
    }
    
    void TOF10120::RefReciveMode(){
        this->Send("r5#\r\n");
    }

    void TOF10120::SetReciveMode(InfoMode mode){
        switch (mode){
        case InfoMode::UART:
            this->Send("s5-0#\r\n");
            break;
        case InfoMode::UART_I2C:
            this->Send("s5-1#\r\n");
            break;
        case InfoMode::None:
        break;
        }
    }

    void TOF10120::RefOffset_mm(){
        this->Send("r1#\r\n");
    }

    void TOF10120::SetOffset_mm(int offset){
        if(offset>=0){
            this->Send("s1+"+std::to_string(offset)+"#\r\n");
        }else{
            this->Send("s1-"+std::to_string(-offset)+"#\r\n");
        }
    }

    void TOF10120::RefInterval_ms(){
        this->Send("r2#\r\n");
    }

    void TOF10120::SetInterval_ms(uint interval){
        if(interval>=10000){
            interval=9999;
            Debug::Warning("interval Range:10~9999ms!");
        }else if(interval<10){
            interval=10;
            Debug::Warning("interval Range:10~9999ms!");
        }
        this->Send("s2-"+std::to_string(interval)+"#\r\n");
    }

    void TOF10120::RefFilter_en(){
        this->Send("r3#\r\n");
    }

    void TOF10120::SetFilter_en(bool enable){
        this->Send("s3-"+std::to_string(enable?0:1)+"#\r\n");
    }

    void TOF10120::RefMaxRange_mm(){
        this->Send("r6#\r\n");
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
        this->Send("s4-"+std::to_string(maxrange)+"#\r\n");
    }
    void TOF10120::RefI2C_Address(){
        this->Send("r7#\r\n");
    }
    void TOF10120::SetI2C_Address(u_char Address){
        this->Send("s7-"+std::to_string(Address)+"#\r\n");
    }
}

#endif