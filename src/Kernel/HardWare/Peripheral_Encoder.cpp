#include<HardWare/Peripheral_Encoder.h>
#include<AbstractDependency/_AbstractHardWare.h>

Peripheral_Encoder::Peripheral_Encoder(uint32_t Encoderx){
    this->Encoderx=Encoderx;
    Override::Encoderx_PreEnable(this);
}

uint32_t Peripheral_Encoder::GetEncoder(){
    return this->Encoderx;
}

void Peripheral_Encoder::ResetCounter(){
    Override::ResetCounter(this);
}