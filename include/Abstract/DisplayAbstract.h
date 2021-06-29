#pragma once
#include<AbstractDependency/__AbstractDependency.h>

enum class CMD{
    ToClose,
    ToOpen,
};

class DisplayBITAbstract
{
    private:
        bool OutRam=false;
        

    public:
    
        u_char **GRAM;
        unsigned int width,height;

        DisplayBITAbstract();

        void __GraphicInit(unsigned int width, unsigned int height);
        void __GraphicInit(u_char **GRAM,unsigned int width, unsigned int height);

        void DrawPixel(unsigned int x, unsigned int y);
        void ClearPixel(unsigned int x, unsigned int y);
        void DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
        void DrawCircle(unsigned int x, unsigned int y, unsigned int radius);
        void DrawChar(unsigned int x, unsigned int y,const char chr, u_char fontSize=12);
        void DrawString(unsigned int x, unsigned int y,const std::string &str, u_char fontSize=12);

        virtual void Refresh();
        void Clear();
        
        ~DisplayBITAbstract();
};

