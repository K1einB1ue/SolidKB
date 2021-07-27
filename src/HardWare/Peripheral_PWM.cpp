#include<HardWare/Peripheral_PWM.h>
#include<AbstractDependency/_AbstractHardWare.h>

PWM::PWM(uint32_t PWMx,uint32_t Period,uint32_t Prescaler){
    this->Period=Period;
    this->Prescaler=Prescaler;
    this->PWMx=PWMx;
    Override::PWMx_PreEnable(this);
}
PWM::PWM(uint32_t PWMx){
    this->PWMx=PWMx;
    Override::PWMx_PreEnable(this);
}
PWM::~PWM(){

}

uint32_t PWM::GetPWM(){
    return this->PWMx;
}
uint32_t PWM::GetPeriod(){
    return this->Period;
}
uint32_t PWM::GetPrescaler(){
    return this->Prescaler;
}