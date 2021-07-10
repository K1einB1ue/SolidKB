#include<SoftHardWare/PIN.h>
#include<AbstractDependency/_AbstractHardWare.h>

namespace std{
    static string PIN_Mode_Table[]={"Fast","FastPullUp","AF_DCMI"};
    string& to_string(PIN_Mode mode){
        return PIN_Mode_Table[(unsigned int)mode];
    };
}

unsigned int PIN::GPIO_Enable_Map  [CFG_GPIO_Size];
bool PIN::PIN_Enable_Map           [CFG_GPIO_Size][CFG_PIN_Size]={false};

PIN::PIN(uint32_t GPIOx,uint32_t PINx,PIN_Mode PINmode){
    if(!PIN_Enable_Map[GPIOx][PINx]){
        this->GPIOx=GPIOx;
        this->PINx=PINx;
        this->PINmode=PINmode;
        if(!PIN::GPIO_Enable_Map[GPIOx]++){
            Override::GPIOx_PreEnable(GPIOx);
        }
        Override::PINPrototypes[PINmode](this);
        PIN_Enable_Map[GPIOx][PINx]=true;
        Debug::Info("GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx)+",PINMode:"+std::to_string(PINmode));
    }else{
        Debug::Warning("PIN is occupied!GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx)+",PINMode:"+std::to_string(PINmode));
    }
}


uint32_t PIN::GetGPIO(){
    return this->GPIOx;
}
uint32_t PIN::GetPIN(){
    return this->PINx;
}

void PIN::ReMode(PIN_Mode PINmode){
    Override::PINPrototypes[PINmode](this);
}

PIN::~PIN(){
    if(PIN_Enable_Map[GPIOx][PINx]){
        if(!--PIN::GPIO_Enable_Map[GPIOx]){
            Override::GPIOx_PreDisable(GPIOx);
        }
        PIN_Enable_Map[GPIOx][PINx]=false;
    }
}
//尝试遮盖PIN脚使其无法被PIN实例化,且持久地持有GPIOEnable.
bool PIN::CoverPIN(uint32_t GPIOx,uint32_t PINx){
    if(!PIN_Enable_Map[GPIOx][PINx]){
        PIN_Enable_Map[GPIOx][PINx]=true;
        if(!PIN::GPIO_Enable_Map[GPIOx]++){
            Override::GPIOx_PreEnable(GPIOx);
        }
        Debug::Info("PIN is covered.GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx));
        return true;
    }
    Debug::Warning("PIN cover failed!GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx));
    return false;
}


bool PIN::UncoverPIN(uint32_t GPIOx,uint32_t PINx){
    if(PIN_Enable_Map[GPIOx][PINx]){
        PIN_Enable_Map[GPIOx][PINx]=false;
        if(!--PIN::GPIO_Enable_Map[GPIOx]){
            Override::GPIOx_PreDisable(GPIOx);
        }
        Debug::Info("PIN is uncovered.GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx));
        return true;
    }
    Debug::Warning("PIN uncover failed!GPIO:"+std::to_string(GPIOx)+",PIN:"+std::to_string(PINx));
    return false;
}


