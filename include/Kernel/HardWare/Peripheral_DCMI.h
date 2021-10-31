#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<HardWare/Peripheral_PIN.h>


class Peripheral_DCMI{
    private:
    uint32_t DCMIx;
    void* Dst;
    uint32_t length;
    public:
    std::function<void(void)> *Callback=nullptr;
    Peripheral_DCMI(uint32_t DCMIx,void* Dst,uint32_t length);
    ~Peripheral_DCMI();
    uint32_t GetDCMI();
    uint32_t GetLength();
    void* GetDst();
    void Work();
    void Stop();
};
