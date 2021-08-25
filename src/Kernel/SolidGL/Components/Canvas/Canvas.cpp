#include"./Canvas.h"


namespace SolidGL{
    namespace Components{
        template<>
        void Canvas<Draw::Bit>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recTexture.get()[x+this->recSize.x*y].Byte=pen.color.Byte;
        }
        template<>
        void Canvas<Draw::RGB332>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recTexture.get()[x+this->recSize.x*y].Byte=pen.color.Byte;
        }
        template<>
        void Canvas<Draw::RGB565>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recTexture.get()[x+this->recSize.x*y].Bytes=pen.color.Bytes;
        }
        template<>
        void Canvas<Draw::ARGB8888>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recTexture.get()[x+this->recSize.x*y].Bytes=pen.color.Bytes;
        }

        template<>
        void Canvas<Draw::Bit>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recTexture.get()[x+this->recSize.x*y].Byte=color.Byte;
        }
        template<>
        void Canvas<Draw::RGB332>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recTexture.get()[x+this->recSize.x*y].Byte=color.Byte;
        }
        template<>
        void Canvas<Draw::RGB565>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recTexture.get()[x+this->recSize.x*y].Bytes=color.Bytes;
        }
        template<>
        void Canvas<Draw::ARGB8888>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recTexture.get()[x+this->recSize.x*y].Bytes=color.Bytes;
        }


        template<>
        void Canvas<Draw::Bit>::Clear(){      
            for(uint i=0;i<(this->recSize.x*this->recSize.y);i++){
                this->recTexture.get()[i].Byte=recBackgroundColor.Byte;
            }
        }

        template<>
        void Canvas<Draw::RGB332>::Clear(){
            for(uint i=0;i<(this->recSize.x*this->recSize.y);i++){            
                this->recTexture.get()[i].Byte=recBackgroundColor.Byte;
            }
        }

        template<>
        void Canvas<Draw::RGB565>::Clear(){
            for(uint i=0;i<(this->recSize.x*this->recSize.y);i++){
                this->recTexture.get()[i].Bytes=recBackgroundColor.Bytes;
            }
        }

        template<>
        void Canvas<Draw::ARGB8888>::Clear(){
            for(uint i=0;i<(this->recSize.x*this->recSize.y);i++){
                this->recTexture.get()[i].Bytes=recBackgroundColor.Bytes;
            }
        }
    }
}