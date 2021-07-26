#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<HardWare/Peripheral_PIN.h>



class PWM
{
private:
    
    static bool PWM_Enable_Map           [CFG_PWM_Size];
    
    uint32_t PWMx;
public:

    PWM(uint32_t PWMx);

    uint32_t GetPWM();
    // uint32_t GetPIN();

    // void ReMode(PIN_Mode PINmode);
    virtual ~PWM();

    static bool CoverPWM(uint32_t PWMx);
    static bool UncoverPWM(uint32_t PWMx);

	// void operator=(float Index) {
	// 	*OUT = Index;
	// }

};

