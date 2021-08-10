#include<HardWare/Bluetooth/Modules/HC_12.h>


#if __Enable_Uart&&__Enable_SystemClock

namespace HardWare{
    namespace HC_Modules{
        HC_12::HC_12(uint32_t Uartx,uint32_t SET_GPIOx,uint32_t SET_PINx):Peripheral_UART(Uartx,9600),SET(SET_GPIOx,SET_PINx,PIN_Mode::FastPullUp,"SET"){
            SET.F_WriteMode();
            SET=1;
            this->Set_Container_Size(50);
            this->End("\r\n",2);
            this->End_Clear(true);
            this->End_Decoder([&](char* Data,unsigned int Size){
                if(std::strcmp(Data,Size,"OK",2)){
                    this->State=HC::State::OK;
                }
                unsigned int ptr=0;
                if (Size>2){
                    switch (Data[3]){
                    case 'F':
                        ptr=5;
                        this->FuxState=(HC::FUx)std::Getint(Data,&ptr);
                        break;
                    case 'C':
                        ptr=4;
                        this->Channel=std::Getint(Data,&ptr);
                        break;
                    case 'P':
                        ptr=4;
                        this->Power=std::Getint(Data,&ptr);
                        break;
                    default:
                        break;
                    }
                }
                
            });
            this->BindCallback([&](char chr){
                if(this->ATmode) this->StreamIn(chr);
                else this->BluetoothDecoder.StreamIn(chr);
            });

            this->StartAT();
                this->SetFUx(HC::FUx::FU3);
                this->SetChannel(5);
                this->SetPower(8);
            this->EndAT();
        }

        bool HC_12::Wait(){           
            unsigned int i;
            for(i=0;i<4000;i++){
                SystemClock::Delay(1000);
                if(this->State!=HC::State::NONE){
                    break;
                }
            }
            if(i>=4000){
                Debug::Warning("TimeOut!");
                return false;
            }else{
                if(this->State==HC::State::OK){
                    return true;
                }else{
                    Debug::Warning("ERROR");
                    return false;
                }
            }
        }

        void HC_12::StartAT(){        
            if(!this->ATmode){
                SET=0;
                this->ATmode=true;
                Debug::StartBlock("AT Mode");
                SystemClock::Delay(1000000);
            }
        }
        void HC_12::EndAT(){
            if(this->ATmode){
                SET=1;
                this->ATmode=false;
                Debug::EndBlock();
                SystemClock::Delay(1000000);
            }
            
        }

        void HC_12::SetFUx(HC::FUx fux){
            if(!this->ATmode){
                this->StartAT();
            }
            Debug::StartBlock("HC FUx");
            this->State=HC::State::NONE;

            this->Send("AT+FU"+std::to_string((u_char)fux));

            if(this->Wait()){ 
                Debug::Info("Change to "+std::to_string((u_char)fux));
                Debug::EndOK();
            }else{
                Debug::EndFAIL();
            }
            SystemClock::Delay(1000000);
        }

        void HC_12::SetChannel(u_char channel){
            if(!this->ATmode){
                this->StartAT();
            }
            Debug::StartBlock("HC Channel");
            this->State=HC::State::NONE;
            
            channel &= 0b01111111;
            std::string temp=std::to_string(channel);
            if(temp.size()!=3){
                std::string tmp;
                while(temp.size()+tmp.size()<3){
                    tmp+='0';
                }
                this->Send("AT+C"+tmp+temp);
            }else{
                this->Send("AT+C"+temp);
            }
            

            if(this->Wait()){ 
                Debug::Info("Change to "+std::to_string(channel));
                Debug::EndOK();
            }else{
                Debug::EndFAIL();
            }
            SystemClock::Delay(1000000);
        }

        void HC_12::SetPower(u_char power){
            if(!this->ATmode){
                this->StartAT();
            }
            Debug::StartBlock("HC Power");
            this->State=HC::State::NONE;
            
            power--;
            power &= 0b00000111;
            power++;
            this->Send("AT+P"+std::to_string(power));

            if(this->Wait()){ 
                Debug::Info("Change to "+std::to_string(power));
                Debug::EndOK();
            }else{
                Debug::EndFAIL();
            }
            SystemClock::Delay(1000000);
        }

        void HC_12::BluetoothSend(const std::string &Info){
            if(this->ATmode){
                this->EndAT();
            }
            this->Send(Info);
        }
    }
}

#endif