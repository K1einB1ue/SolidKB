#pragma once
#include<AbstractDependency/__AbstractDependency.h>


class Peripheral_Encoder{
    private:
    uint32_t Encoderx;
    uint32_t Cnt=0;
    int Previous;
    public:
    volatile uint32_t *Counter = nullptr;
    uint32_t Default;
    Peripheral_Encoder(uint32_t Encoderx);
    uint32_t GetEncoder();
    void ResetCounter();


    int GetSpeed(uint32_t Div){
        
    }
    operator int() {
        int ReturnValue = *this->Counter-this->Default;
        this->ResetCounter();
		return ReturnValue;
	}
};
