#pragma once
#include"../_RenderTarget/RenderTarget.h"
namespace SolidGL{
    namespace Components{
        template<typename T>
        class TextField:public RenderTarget<T>{
            private:
            std::string Text;
            bool Change=false;
            protected:
            virtual bool Refresh(){
                return this->Change;
            }
            public:
            using Pen = typename T::Pen;
            using Color = typename T::Color;
            u_char fontSize=12;
            Pen pen;
            TextField(uint width=240,uint height=240):RenderTarget<T>(width,height){}
            const std::string &GetText(){
                return this->Text;
            }

            void operator =(const std::string &&text){       
                if(text.size()>this->Text.size()){
                    this->Change=true;
                    this->recRender.recSize.x=text.size()*fontSize*2;
                    this->recRender.recSize.y=fontSize*2;
                }else if(text.size()<this->Text.size()){
                    this->Callback=[&](){
                        this->recRender.recSize.x=text.size()*fontSize*2;
                        this->recRender.recSize.y=fontSize*2;
                    };
                    this->Change=true;
                }else{
                    u_int i;
                    for(i=0;i<text.size();i++){
                        if(text[i]!=Text[i]){
                            this->Change=true;
                            break;
                        }
                    }
                    if(i==text.size()){
                        this->Change=false;
                    }
                }
                if(this->Change){
                    Debug_InterruptSend("Test");
                    this->Text=text;
                    this->Clear();
                    this->DrawString(0,0,this->Text,this->pen,this->fontSize);
                }
            }
        };
    }
}