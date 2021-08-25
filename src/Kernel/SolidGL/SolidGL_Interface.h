#pragma once
#include<Kernel/SolidGL/SolidGL_Standard.h>
#include"./Components/GL_Components.h"
enum class Grlib{
    SolidGL,            //使用Solid图形库
    LVGL,               //使用LVGL图形库
};

namespace SolidGL{
    template<typename T>
    class Interface{
        private: 
        uint Screen_Pixel_Width=0,Screen_Pixel_Height=0;
        public:
        using Pen = typename T::Pen;
        using Color = typename T::Color;
        using RenderInterface = typename SolidGL::Components::RenderInterface<T>;
        void Render(RenderInterface &renderInterface){
            if(renderInterface.Refresh()){
                this->RecRender(renderInterface);
                if(renderInterface.Callback){
                    renderInterface.Callback();
                    renderInterface.Callback=nullptr;
                }
            }
        }
        void __GraphicInit(uint width,uint height){
            this->Screen_Pixel_Width=width;
            this->Screen_Pixel_Height=height;
        }
        void __UseGUI(Grlib grlib);
        protected:
        virtual void RecRender(RenderInterface &renderInterface){}
    };
}