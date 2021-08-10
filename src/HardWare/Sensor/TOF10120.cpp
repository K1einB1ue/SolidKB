#include<HardWare/Sensor/Modules/TOF10120.h>

#if __Enable_Uart

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

#endif


#if __Enable_Uart

namespace UART{
    TOF10120::TOF10120(uint32_t Uartx):Peripheral_UART(Uartx,9600){
        this->Set_Container_Size(20);
        this->End("\r\n",2);
        this->End_Clear(true);
        this->End_Decoder([&](char* Data,unsigned int Size){  
            unsigned int ptr=0;        
            if(Data[0]>='0'&&Data[0]<='9'){   
                this->distance=std::Getint(Data,&ptr);
                if(this->DistanceCallBack){
                    this->DistanceCallBack(this->distance);
                }
                return;
            }


            if(std::strcmp(Data,Size,"ok",2)){
                //Debug_InterruptSend("[TOF10120] OK");
                return;
            }else if(std::strcmp(Data,Size,"fail",4)){
                //Debug_InterruptSend("[TOF10120] FAIL");
                return;
            }
            
            int Num=std::Getint(Data,&ptr); 
                     
            switch (Data[0]){
                case 'D':this->offset=Num;return;

                case 'T':this->interval=Num;return;

                case 'M':if(Data[1]=='a'){this->maxrange=Num;return;}
                else{this->enable=Num;return;}


                case 'S':if(Num==0){
                    this->mode=InfoMode::UART;
                }else{this->mode=InfoMode::UART_I2C;}
                return;

                case 'L':this->distance=Num;return;

                case 'I':this->Address=Num;return;
            }
            
        });

        this->BindCallback([&](char chr){
            this->StreamIn(chr);
        });
        SystemClock::Delay(100000);
        this->SetReciveMode(InfoMode::UART);

        SystemClock::Delay(100000);
        this->SetInterval_ms(10);
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
            Debug_Warning("interval Range:10~9999ms!");
        }else if(interval<10){
            interval=10;
            Debug_Warning("interval Range:10~9999ms!");
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
            Debug_Warning("maxrange Range:100~2000mm!");
        }else if(maxrange<100){
            maxrange=100;
            Debug_Warning("maxrange Range:100~2000mm!");
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