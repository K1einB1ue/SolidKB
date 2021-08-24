#pragma once
#include<HardWare/Peripheral_PWM.h>
#include<HardWare/Peripheral_PIN.h>

#if __Enable_PIN&&__Enable_PWM

namespace HardWare{
    class TB6612FNG{
        private:
        PIN AIN1,AIN2,BIN1,BIN2;
        PWM PWMA,PWMB;
        public:
        TB6612FNG(
            uint32_t AIN1_GPIOx,uint32_t AIN1_PINx,
            uint32_t AIN2_GPIOx,uint32_t AIN2_PINx,
            uint32_t BIN1_GPIOx,uint32_t BIN1_PINx,
            uint32_t BIN2_GPIOx,uint32_t BIN2_PINx,
            uint32_t PWMA_PWMx ,uint32_t PWMB_PWMx
        );
        
        void MotorA_Speed(double speed);
        void MotorB_Speed(double speed);
        void Motor_Speed(double speedA,double speedB);
        
    };
}

#endif