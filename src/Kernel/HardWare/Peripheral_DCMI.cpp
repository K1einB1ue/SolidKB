#include<HardWare/Peripheral_DCMI.h>
#include<AbstractDependency/_AbstractHardWare.h>


Peripheral_DCMI::Peripheral_DCMI(uint32_t DCMIx,void* Dst,uint32_t length){
    this->DCMIx=DCMIx;
    this->Dst=Dst;
    this->length=length;
    this->Callback=&Override::DCMICallback[this->DCMIx];
    Override::DCMIx_PreEnable(this);
}

Peripheral_DCMI::~Peripheral_DCMI(){
    Override::DCMIx_PreDisable(this);
}

uint32_t Peripheral_DCMI::GetDCMI(){
    return this->DCMIx;
}

void* Peripheral_DCMI::GetDst(){
    return this->Dst;
}

uint32_t Peripheral_DCMI::GetLength(){
    return this->length;
}

void Peripheral_DCMI::Work(){
    Override::DCMIx_Wrok(this);
}

void Peripheral_DCMI::Stop(){
    Override::DCMIx_Stop(this);
}
