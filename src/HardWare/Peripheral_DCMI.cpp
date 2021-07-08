#include<HardWare/Peripheral_DCMI.h>
#include<AbstractDependency/_AbstractHardWare.h>


namespace HardWare{
    std::function<void(void)> Peripheral_DCMI::DCMI_Callback=nullptr;

    Peripheral_DCMI::Peripheral_DCMI():
    D0   (0, 4,PIN_Mode::AF_DCMI),
    D1   (0, 6,PIN_Mode::AF_DCMI),
    D2   (1, 7,PIN_Mode::AF_DCMI),
    D3   (2, 6,PIN_Mode::AF_DCMI),
    D4   (2, 7,PIN_Mode::AF_DCMI),
    D5   (2, 8,PIN_Mode::AF_DCMI),
    D6   (2, 9,PIN_Mode::AF_DCMI),
    D7   (2,11,PIN_Mode::AF_DCMI),
    VSYNC(4, 6,PIN_Mode::AF_DCMI),
    HREF (4, 5,PIN_Mode::AF_DCMI),
    PCLK (1, 6,PIN_Mode::AF_DCMI){
    Override::DCMI_Init();
    Override::DCMI_Enable();
    }
    Peripheral_DCMI::~Peripheral_DCMI(){
        Override::DCMI_Disable();
    }

    void Peripheral_DCMI::Enable(){
        Override::DCMI_Enable();
    }
    void Peripheral_DCMI::Disable(){
        Override::DCMI_Disable();
    }
    void Peripheral_DCMI::EnableDMA(){

    }
    void Peripheral_DCMI::DisableDMA(){

    }
};