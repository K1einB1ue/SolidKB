#include<HardWare/TB6612FNG.h>
namespace HardWare{
    TB6612FNG::TB6612FNG(
    uint32_t AIN1_GPIOx,uint32_t AIN1_PINx,
    uint32_t AIN2_GPIOx,uint32_t AIN2_PINx,
    uint32_t BIN1_GPIOx,uint32_t BIN1_PINx,
    uint32_t BIN2_GPIOx,uint32_t BIN2_PINx,
    uint32_t PWMA_PWMx ,uint32_t PWMB_PWMx):
    AIN1(AIN1_GPIOx,AIN1_PINx,PIN_Mode::Fast,"AIN1"),
    AIN2(AIN2_GPIOx,AIN2_PINx,PIN_Mode::Fast,"AIN2"),
    BIN1(BIN1_GPIOx,BIN1_PINx,PIN_Mode::Fast,"BIN1"),
    BIN2(BIN2_GPIOx,BIN2_PINx,PIN_Mode::Fast,"BIN2"),
    PWMA(PWMA_PWMx,5000,167),
    PWMB(PWMB_PWMx,5000,167){
        AIN1.F_WriteMode();
        AIN2.F_WriteMode();
        BIN1.F_WriteMode();
        BIN2.F_WriteMode();
        AIN1=0;
        AIN2=0;
        BIN1=0;
        BIN2=0;
    }

    void TB6612FNG::MotorA_Speed(double speed){
        if(speed>ErrorRange){
            this->AIN1=1;
            this->AIN2=0;
            this->PWMA=speed;
        }
        else if(speed<ErrorRange&&speed>-ErrorRange){
            this->AIN1=0;
            this->AIN2=0;
        }else if(speed<-ErrorRange){
            this->AIN1=0;
            this->AIN2=1;
            this->PWMA=-speed;
        }
    }

    void TB6612FNG::MotorB_Speed(double speed){
        if(speed>ErrorRange){
            this->BIN1=1;
            this->BIN2=0;
            this->PWMB=speed;
        }
        else if(speed<ErrorRange&&speed>-ErrorRange){
            this->BIN1=0;
            this->BIN2=0;
        }else if(speed<-ErrorRange){
            this->BIN1=0;
            this->BIN2=1;
            this->PWMB=-speed;
        }
    }

    void TB6612FNG::Motor_Speed(double speedA,double speedB){
        this->MotorA_Speed(speedA);
        this->MotorB_Speed(speedB);
    }
}