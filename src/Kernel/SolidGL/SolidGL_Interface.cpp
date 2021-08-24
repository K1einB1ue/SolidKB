#include"./SolidGL_Interface.h"

namespace SolidGL{
    template<>
    void Interface<Draw::Bit>::__UseGUI(Grlib grlib){

    }
    template<>
    void Interface<Draw::RGB332>::__UseGUI(Grlib grlib){

    }
    template<>
    void Interface<Draw::RGB565>::__UseGUI(Grlib grlib){

    }
    template<>
    void Interface<Draw::ARGB8888>::__UseGUI(Grlib grlib){

    }
}