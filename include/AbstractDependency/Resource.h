#pragma once
#include<AbstractDependency/__AbstractDependency.h>

template<int Size>
class ResourcePack :public std::vector<u_char>
{
    private:
    const int Sum = Size;
    public:
    ResourcePack(const std::initializer_list<u_char> &v):std::vector<u_char>(v){
        const u_char* ptr = v.begin();
        int sum = 0;
        sum += *ptr;
        while (++ptr != v.end()) {
            sum += *ptr;
        }
        #if __Enable_Debug
        if(sum!=this->Sum){
            Debug_StaticSend("ResourcePack Size Error!");
        }
        #endif
    }



    u_char Unpack(u_char Numx) {
        if (Numx + 1 <= this->Sum) {
            Numx += 1;
            u_char ptr = 0;
            while (Numx > (*this)[ptr]) {
                Numx -= (*this)[ptr++];
            }
            return ptr;
        }else{
            Debug_Error("Out of Range!")
            return 0;
        }
    }

};

namespace Override{
    extern void GPIOx_PreEnable(uint32_t GPIOx);
    extern void GPIOx_PreDisable(uint32_t GPIOx);
}

namespace Resource{

    #if CFG_GPIO_Size&&CFG_PIN_Size
    namespace PIN_Resource{
        extern bool Cover(uint32_t GPIOx,uint32_t PINx,std::string Info);
        extern bool Uncover(uint32_t GPIOx,uint32_t PINx,std::string Info);
        extern bool Check(uint32_t GPIOx,uint32_t PINx);
    }
    #endif

    #if CFG_TIM_Size
    namespace TIM_Resource{
        extern bool Cover(uint32_t TIMx,std::string Info);
        extern bool Uncover(uint32_t TIMx,std::string Info);
        extern bool Check(uint32_t TIMx);
    }
    #endif

    #if CFG_PWM_Size
    namespace PWM_Resource{
        extern bool Cover(uint32_t PWMx,std::string Info);
        extern bool Uncover(uint32_t PWMx,std::string Info);
        extern bool Check(uint32_t PWMx);
    }
    #endif

    #if CFG_DCMI_Size
    namespace DCMI_Resource{
        extern bool Cover(uint32_t DCMIx,std::string Info);
        extern bool Uncover(uint32_t DCMIx,std::string Info);
        extern bool Check(uint32_t DCMIx);
    }
    #endif

    #if CFG_Uart_Size
    namespace UART_Resource{
        extern bool Cover(uint32_t UARTx,std::string Info);
        extern bool Uncover(uint32_t UARTx,std::string Info);
        extern bool Check(uint32_t UARTx);
    }
    #endif

    #if CFG_Encoder_Size
    namespace Encoder_Resource{
        extern bool Cover(uint32_t Encoderx,std::string Info);
        extern bool Uncover(uint32_t Encoderx,std::string Info);
        extern bool Check(uint32_t Encoderx);
    }
    #endif
}

