#pragma once
#include<SolidKernel.h>

class T2{
    private:
    PIN *KEY[4],*LED[4];
    bool LightTable[4]={false};
    public:
    void Init(){
        for(u_char i=0;i<4;i++){
            LED[i]=new PIN(0,4+i,PIN_Mode::Fast);
            KEY[i]=new PIN(0,i,PIN_Mode::Fast);
            KEY[i]->F_ReadMode();
        }
    }

    void Run(){
        while(1){
            for(u_char i=0;i<4;i++){
                if(*KEY[i]){
                    while(*KEY[i]);
                    LightTable[i]=!LightTable[i];
                    *LED[i]=LightTable[i];
                }
            }
        }
    }
};