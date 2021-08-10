#pragma once
#include<AbstractDependency/__AbstractDependency.h>
namespace Image{

    class Image_Binary{
        public:
        u_char *_Image=nullptr;
        const uint32_t Pixel_Width=0,Pixel_Height=0;

        Image_Binary(uint32_t Pixel_Width,uint32_t Pixel_Height){
            this->_Image=new u_char[Pixel_Width*Pixel_Height/8];
            uint32_t *temp = const_cast<uint32_t*>(&this->Pixel_Width);
            *temp=Pixel_Width;
            temp = const_cast<uint32_t*>(&this->Pixel_Height);
            *temp=Pixel_Height;
        }

        void Clear(){
            for(uint32_t i=0;i<Pixel_Width*Pixel_Height/8;i++){
                this->_Image[i]=0;
            }   
        }

        ~Image_Binary(){
            delete[] _Image;
        }

    };

    class Image_RGB565{
        private:
        bool OuterMem=false;
        public:
        uint16_t *_Image=nullptr;
        const uint32_t Pixel_Width=0,Pixel_Height=0;

        Image_RGB565(uint32_t Pixel_Width,uint32_t Pixel_Height){
            uint32_t *temp = const_cast<uint32_t*>(&this->Pixel_Width);
            *temp=Pixel_Width;
            temp = const_cast<uint32_t*>(&this->Pixel_Height);
            *temp=Pixel_Height;
            this->_Image = new uint16_t[Pixel_Width*Pixel_Height];   
            this->OuterMem=false;
        }

        Image_RGB565(void* Mem,uint32_t Pixel_Width,uint32_t Pixel_Height){
            
            uint32_t *temp = const_cast<uint32_t*>(&this->Pixel_Width);
            *temp=Pixel_Width;
            temp = const_cast<uint32_t*>(&this->Pixel_Height);
            *temp=Pixel_Height;
            
            this->_Image=(uint16_t*)Mem;
            this->OuterMem=true;
        }

        ~Image_RGB565(){
            if(this->OuterMem){
                delete[] _Image;
            }
        }
        
        Image_Binary* Binaryzation(std::function<bool(u_char,u_char,u_char)> Match,uint32_t Scale=1,Image_Binary* Image=nullptr){
            if(Image==nullptr){
                Image = new Image_Binary(this->Pixel_Width/Scale,this->Pixel_Height/Scale);
            }else{
                if(Image->Pixel_Height<this->Pixel_Height/Scale||Image->Pixel_Width<this->Pixel_Width/Scale){
                    Debug::StaticSend("Image Stack Overflow!");
                }
                Image->Clear();
            }
            u_char R,G,B;
            uint32_t Binary_Y_offset=0,Binary_Y=0;
            for(uint32_t i=0,BinaryOuter_X=0;i<this->Pixel_Width;i+=Scale,BinaryOuter_X++){            
                for(uint32_t j=0,BinaryOuter_Y=0;j<this->Pixel_Height;j+=Scale,BinaryOuter_Y++){
                    R=(_Image[i+j*this->Pixel_Width]>>11);
                    G=((_Image[i+j*this->Pixel_Width]&0b11111100000)>>5);
                    B=(_Image[i+j*this->Pixel_Width]&0b11111);
                    if(Match(R,G,B)){
                        u_char temp=0;
                        Binary_Y=BinaryOuter_Y/8;
                        Binary_Y_offset=BinaryOuter_Y%8;
                        temp=1<<Binary_Y_offset;
                        Image->_Image[BinaryOuter_X+Binary_Y*Image->Pixel_Width]|=temp;
                        //Debug::InterruptSend(std::to_string(BinaryOuter_X+Binary_Y*Image->Pixel_Width));
                    }
                }        
            }
            return Image;
        }
    };


    

}