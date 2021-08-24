#include"./RenderTarget.h"


namespace SolidGL{
    namespace Render2D{
        template<>
        RecRender<Draw::Bit>::Color RecRender<Draw::Bit>::BackgroundColor(0);
        template<>
        RecRender<Draw::RGB332>::Color RecRender<Draw::RGB332>::BackgroundColor(0);
        template<>
        RecRender<Draw::RGB565>::Color RecRender<Draw::RGB565>::BackgroundColor(0);
        template<>
        RecRender<Draw::ARGB8888>::Color RecRender<Draw::ARGB8888>::BackgroundColor(0xFF000000);
    }
    namespace Components{
        template<>
        void RenderTarget<Draw::Bit>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Byte=pen.color.Byte;
        }
        template<>
        void RenderTarget<Draw::RGB332>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Byte=pen.color.Byte;
        }
        template<>
        void RenderTarget<Draw::RGB565>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Bytes=pen.color.Bytes;
        }
        template<>
        void RenderTarget<Draw::ARGB8888>::DrawPixel(unsigned int x, unsigned int y,const Pen& pen){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Bytes=pen.color.Bytes;
        }

        template<>
        void RenderTarget<Draw::Bit>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Byte=color.Byte;
        }
        template<>
        void RenderTarget<Draw::RGB332>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Byte=color.Byte;
        }
        template<>
        void RenderTarget<Draw::RGB565>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Bytes=color.Bytes;
        }
        template<>
        void RenderTarget<Draw::ARGB8888>::DrawPixel(unsigned int x, unsigned int y,const Color& color){
            this->recRender.Texture.get()[x+this->recRender.recSize.x*y].Bytes=color.Bytes;
        }


        template<>
        void RenderTarget<Draw::Bit>::Clear(){      
            for(uint i=0;i<(this->recRender.recSize.x*this->recRender.recSize.y);i++){
                this->recRender.Texture.get()[i].Byte=recBackgroundColor.Byte;
            }
        }

        template<>
        void RenderTarget<Draw::RGB332>::Clear(){
            for(uint i=0;i<(this->recRender.recSize.x*this->recRender.recSize.y);i++){            
                this->recRender.Texture.get()[i].Byte=recBackgroundColor.Byte;
            }
        }

        template<>
        void RenderTarget<Draw::RGB565>::Clear(){
            for(uint i=0;i<(this->recRender.recSize.x*this->recRender.recSize.y);i++){
                this->recRender.Texture.get()[i].Bytes=recBackgroundColor.Bytes;
            }
        }

        template<>
        void RenderTarget<Draw::ARGB8888>::Clear(){
            for(uint i=0;i<(this->recRender.recSize.x*this->recRender.recSize.y);i++){
                this->recRender.Texture.get()[i].Bytes=recBackgroundColor.Bytes;
            }
        }
    }
}