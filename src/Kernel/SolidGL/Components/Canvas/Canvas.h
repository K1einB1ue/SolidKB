#pragma once
#include"../_RenderTarget/RenderTarget.h"



namespace SolidGL{
    namespace Components{
        using namespace Render2D;
        template<typename T>
        class Canvas:public Render_Interface<T,Render2D::RecTexture<T>>{
            public: 
            using Pen = typename T::Pen;
            using Color = typename T::Color;
            Color                       recBackgroundColor=RecRender<T>::BackgroundColor;       
            RecTransform                recTransform;
            Canvas(uint width,uint height,std::shared_ptr<Color> textureRam=nullptr){
                Debug_StartBlock("Canvas");
                    Debug_Info("PixelWidth:"+std::to_string(width));
                    Debug_Info("PixelHeight:"+std::to_string(height));
                this->recRender.recSize.x=width;
                this->recRender.recSize.y=height;
                if(!textureRam){
                    this->recRender.Texture=std::shared_ptr<Color>(new Color[width*height]);
                    Debug_Info("UniqueMemory");
                }else{
                    this->recRender.Texture=textureRam;
                    Debug_Info("SharedMemory");  
                }
                Debug_EndBlock();
            }
            virtual ~Canvas(){} 
            void DrawPixel(unsigned int x, unsigned int y,const Pen& pen);
            void DrawPixel(unsigned int x, unsigned int y,const Color& color);
            void DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,const Pen& pen){
                unsigned int i,k,k1,k2;
                if((x1<0)||(x2>this->recRender.recSize.x)||(y1<0)||(y2>this->recRender.recSize.y)||(x1>x2)||(y1>y2))return;
                if(x1==x2) {
                    for(i=0;i<(y2-y1);i++) {
                        DrawPixel(x1,y1+i,pen);
                    }
                }
                else if(y1==y2) {
                    for(i=0;i<(x2-x1);i++) {
                        DrawPixel(x1+i,y1,pen);
                    }
                }
                else {
                    k1=y2-y1;
                    k2=x2-x1;
                    k=k1*10/k2;
                    for(i=0;i<(x2-x1);i++) {
                        DrawPixel(x1+i,y1+i*k/10,pen);
                    }
                }
            }

            // void DrawChar(unsigned int x, unsigned int y,const char chr,const Pen& pen,u_char fontSize=12){
            //     unsigned int i,m,temp,size2,chr1;
            //     unsigned int y0=y;
            //     size2=(fontSize/8+((fontSize%8)?1:0))*(fontSize/2);     //得到字体一个字符对应点阵集所占的字节数
            //     chr1=chr-' ';                                           //计算偏移后的值

            //     u_char Width;
            //     const u_char* FontTable;
            //     switch(fontSize){
            //         case 12:FontTable=(u_char*)asc2_1206;Width=12;
            //         break;
            //         case 16:FontTable=(u_char*)asc2_1608;Width=16;
            //         break;
            //         case 24:FontTable=(u_char*)asc2_2412;Width=36;
            //         break;
            //         default:return;
            //     }   
                
            //     for(i=0;i<size2;i++){
            //         temp=FontTable[chr1*Width+i];
            //         for(m=0;m<8;m++){
            //             if(temp&0x80){ 
            //                 this->DrawPixel(x,y,pen);
            //             }else{
            //                 this->DrawPixel(x,y,recBackgroundColor);
            //             }
            //             temp<<=1;
            //             y++;
            //             if((y-y0)==fontSize){
            //                 y=y0;
            //                 x++;
            //                 break;
            //             }
            //         }
            //     }
            // }

            // void DrawString(unsigned int x, unsigned int y,const std::string &str,const Pen& pen,u_char fontSize=12){
            //     for(unsigned int i=0;i<str.size();i++) {
            //         if((str[i]>=' ')&&(str[i]<='~')) {
            //             this->DrawChar(x,y,str[i],pen,fontSize);
            //             x+=fontSize/2;
            //             if(x>this->recRender.recSize.x-fontSize) {
            //                 x=0;
            //                 y+=2;
            //             }
            //         }
            //     }
            // }

            void Clear();
            virtual bool Refresh(){return true;}
        };
    }
}