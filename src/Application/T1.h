#pragma once
#include<SolidKernel.h>

class T1{
    private:
    PIN *LED;
    public:
    void Init(){
        LED=new PIN(0,0,PIN_Mode::Fast);
    }

    void Run(){
        while(1){
            *LED=0;
            SystemClock::Delay(500000);
            *LED=1;
        }
    }
};