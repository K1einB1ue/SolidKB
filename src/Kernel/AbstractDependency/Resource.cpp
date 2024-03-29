#include"./Resource.h"




namespace Resource{
    #if CFG_GPIO_Size&&CFG_PIN_Size
    unsigned int GPIO_Enable_Map    [CFG_GPIO_Size];
    bool PIN_Enable_Map             [CFG_GPIO_Size][CFG_PIN_Size];

    bool PIN_Resource::Cover(uint32_t GPIOx,uint32_t PINx,std::string Info){
        if(GPIOx<CFG_GPIO_Size&&PINx<CFG_PIN_Size){
            if(PIN_Enable_Map[GPIOx][PINx]){
                Debug_Warning("Cover Error! GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
                PIN_Enable_Map[GPIOx][PINx]=true;
                if(!GPIO_Enable_Map[GPIOx]++){
                    Override::GPIOx_PreEnable(GPIOx);
                }
                return true;
            }
        }
        Debug_Warning("Out of Range! GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
        return false;
    }
    bool PIN_Resource::Uncover(uint32_t GPIOx,uint32_t PINx,std::string Info){
        if(GPIOx<CFG_GPIO_Size&&PINx<CFG_PIN_Size){
            if(!PIN_Enable_Map[GPIOx][PINx]){
                Debug_Warning("Uncover Error! GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
                PIN_Enable_Map[GPIOx][PINx]=false;
                if(!--GPIO_Enable_Map[GPIOx]){
                    Override::GPIOx_PreDisable(GPIOx);
                }
                return true;
            }
        }
        Debug_Warning("Out of Range! GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx)+"  Info:"+Info);
        return false;
    }
    bool PIN_Resource::Check(uint32_t GPIOx,uint32_t PINx){
        if(GPIOx<CFG_GPIO_Size&&PINx<CFG_PIN_Size){
            return PIN_Enable_Map[GPIOx][PINx];
        }else{
            Debug_Warning("Check Out of Range! GPIOx:"+std::to_string(GPIOx)+"  PINx:"+std::to_string(PINx));
            return true;
        }
    }
    #endif

    #if CFG_TIM_Size
    bool TIM_Enable_Map             [CFG_TIM_Size];

    bool TIM_Resource::Cover(uint32_t TIMx,std::string Info){
        if(TIMx<CFG_TIM_Size){
            if(TIM_Enable_Map[TIMx]){
                Debug_Warning("Cover Error! TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
                TIM_Enable_Map[TIMx]=true;
                return true;
            }
        }
        Debug_Warning("Out of Range! TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
        return false;
    }
    bool TIM_Resource::Uncover(uint32_t TIMx,std::string Info){
        if(TIMx<CFG_TIM_Size){
            if(!TIM_Enable_Map[TIMx]){
                Debug_Warning("Uncover Error! TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
                TIM_Enable_Map[TIMx]=false;
                return true;
            }
        }
        Debug_Warning("Out of Range! TIMx:"+std::to_string(TIMx)+"  Info:"+Info);
        return false;
    }
    bool TIM_Resource::Check(uint32_t TIMx){
        if(TIMx<CFG_TIM_Size){
            return TIM_Enable_Map[TIMx];
        }else{
            Debug_Warning("Check Out of Range! TIMx:"+std::to_string(TIMx));
            return true;
        }
    }
    #endif

    #if CFG_PWM_Size
    bool PWM_Enable_Map             [CFG_PWM_Size];
    bool PWM_Resource::Cover(uint32_t PWMx,std::string Info){
        if(PWMx<CFG_PWM_Size){
            if(PWM_Enable_Map[PWMx]){
                Debug_Warning("Cover Error! PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
                PWM_Enable_Map[PWMx]=true;
                return true;
            }
        }
        Debug_Warning("Out of Range! PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
        return false;
    }
    bool PWM_Resource::Uncover(uint32_t PWMx,std::string Info){
        if(PWMx<CFG_PWM_Size){
            if(!PWM_Enable_Map[PWMx]){
                Debug_Warning("Uncover Error! PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
                PWM_Enable_Map[PWMx]=false;
                return true;
            }
        }
        Debug_Warning("Out of Range! PWMx:"+std::to_string(PWMx)+"  Info:"+Info);
        return false;
    }
    bool PWM_Resource::Check(uint32_t PWMx){
        if(PWMx<CFG_PWM_Size){
            return PWM_Enable_Map[PWMx];
        }else{
            Debug_Warning("Check Out of Range! PWMx:"+std::to_string(PWMx));
            return true;
        }
    }
    #endif

    #if CFG_DCMI_Size
    bool DCMI_Enable_Map            [CFG_DCMI_Size];
    bool DCMI_Resource::Cover(uint32_t DCMIx,std::string Info){
        if(DCMIx<CFG_DCMI_Size){
            if(DCMI_Enable_Map[DCMIx]){
                Debug_Warning("Cover Error! DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
                DCMI_Enable_Map[DCMIx]=true;
                return true;
            }
        }
        Debug_Warning("Out of Range! DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
        return false;
    }
    bool DCMI_Resource::Uncover(uint32_t DCMIx,std::string Info){
        if(DCMIx<CFG_DCMI_Size){
            if(!DCMI_Enable_Map[DCMIx]){
                Debug_Warning("Uncover Error! DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
                DCMI_Enable_Map[DCMIx]=false;
                return true;
            }
        }
        Debug_Warning("Out of Range! DCMIx:"+std::to_string(DCMIx)+"  Info:"+Info);
        return false;
    }
    bool DCMI_Resource::Check(uint32_t DCMIx){
        if(DCMIx<CFG_DCMI_Size){
            return DCMI_Enable_Map[DCMIx];
        }else{
            Debug_Warning("Check Out of Range! DCMIx:"+std::to_string(DCMIx));
            return true;
        }
    }
    #endif
    
    #if CFG_Uart_Size
    bool UART_Enable_Map            [CFG_Uart_Size];
    bool UART_Resource::Cover(uint32_t UARTx,std::string Info){
        if(UARTx<CFG_Uart_Size){
            if(UART_Enable_Map[UARTx]){
                Debug_Warning("Cover Error! UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
                UART_Enable_Map[UARTx]=true;
                return true;
            }
        }
        Debug_Warning("Out of Range! UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
        return false;
    }
    bool UART_Resource::Uncover(uint32_t UARTx,std::string Info){
        if(UARTx<CFG_Uart_Size){
            if(!UART_Enable_Map[UARTx]){
                Debug_Warning("Uncover Error! UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
                UART_Enable_Map[UARTx]=false;
                return true;
            }
        }
        Debug_Warning("Out of Range! UARTx:"+std::to_string(UARTx)+"  Info:"+Info);
        return false;
    }
    bool UART_Resource::Check(uint32_t UARTx){
        if(UARTx<CFG_Uart_Size){
            return UART_Enable_Map[UARTx];
        }else{
            Debug_Warning("Check Out of Range! UARTx:"+std::to_string(UARTx));
            return true;
        }
    }
    #endif


    #if CFG_Encoder_Size
    bool Encoder_Enable_Map            [CFG_Encoder_Size];
    bool Encoder_Resource::Cover(uint32_t Encoderx,std::string Info){
        if(Encoderx<CFG_Encoder_Size){
            if(Encoder_Enable_Map[Encoderx]){
                Debug_Warning("Cover Error! Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Cover Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
                Encoder_Enable_Map[Encoderx]=true;
                return true;
            }
        }
        Debug_Warning("Out of Range! Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
        return false;
    }
    bool Encoder_Resource::Uncover(uint32_t Encoderx,std::string Info){
        if(Encoderx<CFG_Encoder_Size){
            if(!Encoder_Enable_Map[Encoderx]){
                Debug_Warning("Uncover Error! Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
                return false;
            }else{
                Debug_Info("Uncover Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
                Encoder_Enable_Map[Encoderx]=false;
                return true;
            }
        }
        Debug_Warning("Out of Range! Encoderx:"+std::to_string(Encoderx)+"  Info:"+Info);
        return false;
    }
    bool Encoder_Resource::Check(uint32_t Encoderx){
        if(Encoderx<CFG_Encoder_Size){
            return Encoder_Enable_Map[Encoderx];
        }else{
            Debug_Warning("Check Out of Range! Encoderx:"+std::to_string(Encoderx));
            return true;
        }
    }
    #endif
}
