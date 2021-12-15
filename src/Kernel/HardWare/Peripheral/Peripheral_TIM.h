#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"



class Peripheral_TIM
{
private:
    
    static bool TIM_Enable_Map           [CFG_TIM_Size];
    
    uint32_t TIMx;uint32_t AutoReload;uint32_t Prescale;
public:

    Peripheral_TIM(uint32_t TIMx);

    uint32_t GetTIM();
    uint32_t GetAutoReload();
    uint32_t GetPrescale();

    // void ReMode(PIN_Mode PINmode);
    virtual ~Peripheral_TIM();

	// void operator=(float Index) {
	// 	*OUT = Index;
	// }
};