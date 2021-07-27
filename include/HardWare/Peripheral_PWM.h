#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<HardWare/Peripheral_PIN.h>



class PWM
{
private:
    
    static bool PWM_Enable_Map           [CFG_PWM_Size];
    
    uint32_t PWMx;uint32_t Period;uint32_t Prescaler;
public:

    volatile unsigned long* Pulse=nullptr;

    PWM(uint32_t PWMx,uint32_t Period,uint32_t Prescaler);
    PWM(uint32_t PWMx);

    uint32_t GetPWM();
    uint32_t GetPeriod();
    uint32_t GetPrescaler();

    // void ReMode(PIN_Mode PINmode);
    virtual ~PWM();

	void operator=(double Index) {
        if(Index>=1){
            *Pulse=this->Period;
        }else if(Index<0){
            *Pulse=0;
        }else{
            *Pulse=(uint32_t)(Index*this->Period);
        }
	}

};

