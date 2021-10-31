#include<HardWare/Peripheral_PIN.h>
#include<AbstractDependency/_AbstractHardWare.h>

#ifdef __Enable_PIN
namespace std{
    static string PIN_Mode_Table[]={"Fast","FastPullUp","AF_DCMI"};
    string& to_string(PIN_Mode mode){
        return PIN_Mode_Table[(unsigned int)mode];
    };
}

PIN::PIN(uint32_t GPIOx,uint32_t PINx,PIN_Mode PINmode,std::string InfoMode){
    this->GPIOx=GPIOx;
    this->PINx=PINx;
    this->PINmode=PINmode;

    if(Resource::PIN_Resource::Cover(GPIOx,PINx,InfoMode+"  PINMode:"+std::to_string(PINmode))){
        Override::PINPrototypes[PINmode](this);
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
    Resource::PIN_Resource::Uncover(this->GPIOx,this->PINx,"Clear");
}



#endif